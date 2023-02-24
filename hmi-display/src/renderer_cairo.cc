//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files (the 'Software'), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.
// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
///
/// \file renderer_cairo.cc
///

#include "renderer_cairo.h"

#include <glog/logging.h>
#include <gtk/gtk.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "events_gva.h"

namespace gva {

static CallbackType callback_;
static void *arg_;
HandleType RendererCairo::render_;

RendererCairo::RendererCairo(uint32_t width, uint32_t height) : Renderer(width, height) {
  scale_ = 1.0;
  foreground_colour_ = {255, 255, 255};
  background_colour_ = {0, 0, 0};
  texture_ = nullptr;
  config_ = gva::ConfigData::GetInstance();
  render_.size.width = gva::kMinimumWidth;
  render_.size.height = gva::kMinimumHeight;
}

RendererCairo::~RendererCairo() {
  if (texture_) {
    std::free(texture_);
    texture_ = nullptr;
  }
  cairo_destroy(render_.cr);
  g_object_unref(render_.win.app);
  CloseWindow();
}

void RendererCairo::Draw() {
  std::array<double, 1> dashed = {1.0};
  std::array<double, 1> dashed_medium = {4.0};
  std::array<double, 1> dashed_large = {8.0};

  cairo_t *cr = render_.cr;
  // Push the render to prevent flicker, flush when done
  cairo_push_group(cr);

  for (auto currentCmd : draw_commands_) {
    switch (currentCmd.command) {
      case DrawType::kCommandCircle:
        cairo_save(cr);
        cairo_new_path(cr);
        cairo_translate(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        cairo_arc(cr, 0, 0, currentCmd.radius, 0, 2 * M_PI);
        cairo_close_path(cr);
        if (currentCmd.fill) {
          cairo_set_source_rgb(cr, IntToFloat(background_colour_.red), IntToFloat(background_colour_.green),
                               IntToFloat(background_colour_.blue));
          cairo_fill_preserve(cr);
          cairo_set_source_rgb(cr, IntToFloat(foreground_colour_.red), IntToFloat(foreground_colour_.green),
                               IntToFloat(foreground_colour_.blue));
          cairo_stroke(cr);
        } else {
          cairo_stroke(cr);
        }
        cairo_restore(cr);
        break;
      case DrawType::kCommandArc:
        cairo_new_path(cr);
        cairo_arc(cr, currentCmd.points[0].x, currentCmd.points[0].y, currentCmd.radius, currentCmd.angle1,
                  currentCmd.angle2);
        cairo_stroke(cr);
        break;
      case DrawType::kCommandColourBackground:
        background_colour_.red = currentCmd.arg1;
        background_colour_.green = currentCmd.arg2;
        background_colour_.blue = currentCmd.arg3;
        break;
      case DrawType::kCommandColourForeground:
        foreground_colour_.red = currentCmd.arg1;
        foreground_colour_.green = currentCmd.arg2;
        foreground_colour_.blue = currentCmd.arg3;
        break;
      case DrawType::kCommandPenMove:
        if (currentCmd.arg1) cairo_new_path(cr);
        cairo_move_to(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        break;
      case DrawType::kCommandPenDraw:
        cairo_line_to(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        if (currentCmd.arg1 > 0) {
          cairo_close_path(cr);
          cairo_stroke(cr);
        }
        break;
      case DrawType::kCommandPenLine:
        cairo_move_to(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        cairo_line_to(cr, currentCmd.points[1].x, currentCmd.points[1].y);
        cairo_stroke(cr);
        break;
      case DrawType::kCommandPenRectangle:
        cairo_new_path(cr);
        cairo_move_to(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        cairo_rel_line_to(cr, currentCmd.points[1].x - currentCmd.points[0].x, 0);
        cairo_rel_line_to(cr, 0, currentCmd.points[1].y - currentCmd.points[0].y);
        cairo_rel_line_to(cr, currentCmd.points[0].x - currentCmd.points[1].x, 0);
        cairo_rel_line_to(cr, 0, currentCmd.points[0].y - currentCmd.points[1].y);
        cairo_close_path(cr);
#if 1
        if (currentCmd.fill) {
          cairo_set_source_rgb(cr, IntToFloat(background_colour_.red), IntToFloat(background_colour_.green),
                               IntToFloat(background_colour_.blue));
          cairo_fill_preserve(cr);
          cairo_set_source_rgb(cr, IntToFloat(foreground_colour_.red), IntToFloat(foreground_colour_.green),
                               IntToFloat(foreground_colour_.blue));
          cairo_stroke(cr);
        } else {
          cairo_stroke(cr);
        }
#endif
        break;
      case DrawType::kCommandPenRoundedRectangle: {
        double width = currentCmd.arg1;
        double height = currentCmd.arg2;
        double corner_radius = (double)currentCmd.arg3; /* and corner curvature radius */
        double x = currentCmd.points[0].x;
        double y = currentCmd.points[0].y;
        double radius = corner_radius;
        double degrees = M_PI / 180.0;

        cairo_new_sub_path(cr);
        cairo_arc(cr, x + radius, y + radius, radius, 180 * degrees, 270 * degrees);
        cairo_arc(cr, x + width - radius, y + radius, radius, 270 * degrees, 0 * degrees);
        cairo_arc(cr, x + width - radius, y + height - radius, radius, 0 * degrees, 90 * degrees);
        cairo_arc(cr, x + radius, y + height - radius, radius, 90 * degrees, 180 * degrees);
        cairo_close_path(cr);
      }
        if (currentCmd.fill) {
          cairo_set_source_rgb(cr, IntToFloat(background_colour_.red), IntToFloat(background_colour_.green),
                               IntToFloat(background_colour_.blue));
          cairo_fill_preserve(cr);
          cairo_set_source_rgb(cr, IntToFloat(foreground_colour_.red), IntToFloat(foreground_colour_.green),
                               IntToFloat(foreground_colour_.blue));
          cairo_stroke(cr);
        }
        break;
      case DrawType::kCommandPenTriangle:
        cairo_new_path(cr);
        cairo_move_to(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        cairo_rel_line_to(cr, currentCmd.points[1].x - currentCmd.points[0].x,
                          currentCmd.points[1].y - currentCmd.points[0].y);
        cairo_rel_line_to(cr, currentCmd.points[2].x - currentCmd.points[1].x,
                          currentCmd.points[2].y - currentCmd.points[1].y);
        cairo_close_path(cr);

        if (currentCmd.fill) {
          cairo_set_source_rgb(cr, IntToFloat(background_colour_.red), IntToFloat(background_colour_.green),
                               IntToFloat(background_colour_.blue));
          cairo_fill_preserve(cr);
          cairo_set_source_rgb(cr, IntToFloat(foreground_colour_.red), IntToFloat(foreground_colour_.green),
                               IntToFloat(foreground_colour_.blue));
          cairo_stroke(cr);
        } else {
          cairo_stroke(cr);
        }
        break;
      case DrawType::kCommandPenColour:
        cairo_set_source_rgb(cr, IntToFloat(currentCmd.colour.red), IntToFloat(currentCmd.colour.green),
                             IntToFloat(currentCmd.colour.blue));
        break;
      case DrawType::kCommandPenThickness:
        cairo_set_line_width(cr, (cairo_line_join_t)currentCmd.arg1);
        {
          cairo_line_cap_t cap = CAIRO_LINE_CAP_SQUARE;
          switch ((LineCapEnd)currentCmd.arg3) {
            default:
            case LineCapEnd::kLineCapButt:
              cap = CAIRO_LINE_CAP_BUTT;
              break;
            case LineCapEnd::kLineCapRound:
              cap = CAIRO_LINE_CAP_ROUND;
              break;
            case LineCapEnd::kLineCapSquare:
              cap = CAIRO_LINE_CAP_SQUARE;
              break;
          }
          cairo_set_line_cap(cr, cap);
        }
        switch (currentCmd.arg2) {
          case int(LineType::kLineDashed):
            cairo_set_dash(cr, &dashed[0], 1, 0);
            break;
          case int(LineType::kLineDashedMedium):
            cairo_set_dash(cr, &dashed_medium[0], 1, 0);
            break;
          case int(LineType::kLineDashedLarge):
            cairo_set_dash(cr, &dashed_large[0], 1, 0);
            break;
          case int(LineType::kLineSolid):
          default:
            cairo_set_dash(cr, 0, 0, 0);
            break;
        }
        break;
      case DrawType::kCommandSave:
        cairo_save(cr);
        break;
      case DrawType::kCommandRestore:
        cairo_restore(cr);
        break;
      case DrawType::kCommandScale:
        cairo_scale(cr, currentCmd.width, currentCmd.height);
        break;
      case DrawType::kCommandTranslate:
        cairo_translate(cr, currentCmd.arg1, currentCmd.arg2);
        break;
      case DrawType::kCommandRotate:

        cairo_rotate(cr, currentCmd.width);

        break;
      case DrawType::kCommandClosePath:
        cairo_close_path(cr);
        if (currentCmd.arg1 > 0) {
          cairo_set_source_rgb(cr, IntToFloat(background_colour_.red), IntToFloat(background_colour_.green),
                               IntToFloat(background_colour_.blue));
          cairo_fill_preserve(cr);
          cairo_set_source_rgb(cr, IntToFloat(foreground_colour_.red), IntToFloat(foreground_colour_.green),
                               IntToFloat(foreground_colour_.blue));
          cairo_stroke(cr);
        }
        break;
      case DrawType::kCommandLineJoin:
        cairo_set_line_join(cr, (cairo_line_join_t)currentCmd.arg1);
        break;
      case DrawType::kCommandImageTexture:
        cairo_set_source_surface(cr, image_list_[currentCmd.arg1 - 1].image, currentCmd.points[0].x,
                                 currentCmd.points[0].y);
        cairo_paint(cr);
        // // Only free the image if it wasn't from cache. i.e. video
        // if (!image_list_[currentCmd.arg1].from_cache) cairo_surface_destroy(image_list_[currentCmd.arg1].image);
        // break;
      case DrawType::kCommandImageTexturePersist:
        cairo_set_source_surface(cr, image_list_[currentCmd.arg1 - 1].image, currentCmd.points[0].x,
                                 currentCmd.points[0].y);
        cairo_paint(cr);
        break;
      case DrawType::kCommandTextFont:
        cairo_select_font_face(cr, currentCmd.text.c_str(), (cairo_font_slant_t)currentCmd.arg1,
                               (cairo_font_weight_t)currentCmd.arg2);
        cairo_set_font_size(cr, currentCmd.width);

        break;
      case DrawType::kCommandPush:
        cairo_push_group(cr);
        break;
      case DrawType::kCommandPop:
        cairo_pop_group_to_source(cr);
        break;
      case DrawType::kCommandText: {
        cairo_move_to(cr, currentCmd.points[0].x, currentCmd.points[0].y);
        cairo_show_text(cr, currentCmd.text.c_str());
      } break;
      default:
        printf("[GVA] Unrecognised command!!!\n");
        break;
    }
  }
  // Pop the group and flush to display on the screen
  cairo_pop_group_to_source(cr);
  cairo_paint(cr);

  // We did it. Lets empty the buffer of draw commands.
  draw_commands_.clear();
}

uint32_t RendererCairo::Init(uint32_t width, uint32_t height) {
  render_.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  return 0;
}

uint32_t RendererCairo::Init(uint32_t width, uint32_t height, bool fullscreen, CallbackType cb, void *arg) {
  render_.size.width = width;
  render_.size.height = height;

  width_ = width;
  height_ = height;
  callback_ = cb;
  arg_ = arg;
  render_.fullscreen = false;

  render_.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

#if __MINGW64__ || __MINGW32__
  render_.win.app = gtk_application_new("org.gtk.vivoe-lite-hmi", G_APPLICATION_DEFAULT_FLAGS);
#else
  render_.win.app = gtk_application_new("org.gtk.vivoe-lite-hmi", G_APPLICATION_FLAGS_NONE);
#endif

  g_signal_connect(render_.win.app, "activate", G_CALLBACK(Activate), NULL);
  g_timeout_add(40, Callback, &render_);

  render_.fullscreen = fullscreen;

  g_application_run(G_APPLICATION(render_.win.app), 0, 0);
  g_object_unref(render_.win.app);

  return 0;
}

void RendererCairo::SetPixel(uint32_t x, uint32_t y) {}

void RendererCairo::SetColour(uint8_t red, uint8_t green, uint8_t blue) {
  SetColourForeground(red, green, blue);
  SetColourBackground(red, green, blue);
}

void RendererCairo::SetColour(uint32_t rgb) { SetColour((rgb & 0xff0000) >> 16, (rgb & 0xff00) >> 8, rgb & 0xff); }

void RendererCairo::SetColourForeground(uint8_t red, uint8_t green, uint8_t blue) {
  Command command;
  command.command = DrawType::kCommandColourForeground;
  command.arg1 = red;
  command.arg2 = green;
  command.arg3 = blue;
  draw_commands_.push_back(command);
}

void RendererCairo::SetColourForeground(uint32_t rgb) {
  SetColourForeground((rgb & 0xff0000) >> 16, (rgb & 0xff00) >> 8, rgb & 0xff);
}

void RendererCairo::SetColourBackground(uint8_t red, uint8_t green, uint8_t blue) {
  Command command;
  command.command = DrawType::kCommandColourBackground;
  command.arg1 = red;
  command.arg2 = green;
  command.arg3 = blue;
  draw_commands_.push_back(command);
}

void RendererCairo::SetColourBackground(uint32_t rgb) {
  SetColourBackground((rgb & 0xff0000) >> 16, (rgb & 0xff00) >> 8, rgb & 0xff);
}

void RendererCairo::SetLineType(uint32_t type) {
  Command command;
  command.command = DrawType::kCommandLineJoin;
  command.arg1 = type;
  draw_commands_.push_back(command);
}

void RendererCairo::SetLineThickness(uint32_t thickness, LineType fill, LineCapEnd end) {
  Command command;
  command.command = DrawType::kCommandPenThickness;
  command.arg1 = thickness;
  command.arg2 = int(fill);
  command.arg3 = int(end);
  draw_commands_.push_back(command);
}

void RendererCairo::SetLineThickness(uint32_t thickness, LineType fill) {
  SetLineThickness(thickness, fill, LineCapEnd::kLineCapButt);
}

uint32_t RendererCairo::MovePen(int32_t x, int32_t y) {
  Command command;
  command.command = DrawType::kCommandPenMove;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = 1;  // 1 indicates new path
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::MovePenRaw(int32_t x, int32_t y) {
  Command command;
  command.command = DrawType::kCommandPenMove;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = 0;  // 0 indicates no new path
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::DrawPen(uint32_t x, uint32_t y, bool close) {
  Command command;
  command.command = DrawType::kCommandPenDraw;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = close ? 1 : 0;
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::DrawPenRaw(int32_t x, int32_t y) {
  Command command;
  command.command = DrawType::kCommandPenDraw;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = 0;
  draw_commands_.push_back(command);
  return 0;
}

void RendererCairo::Save() {
  Command command;
  command.command = DrawType::kCommandSave;
  draw_commands_.push_back(command);
}

void RendererCairo::Restore() {
  Command command;
  command.command = DrawType::kCommandRestore;
  draw_commands_.push_back(command);
}

void RendererCairo::Scale(double x, double y) {
  Command command;
  command.command = DrawType::kCommandScale;
  command.width = x;
  command.height = y;
  draw_commands_.push_back(command);
}

void RendererCairo::Translate(uint32_t x, uint32_t y) {
  Command command;
  command.command = DrawType::kCommandTranslate;
  command.arg1 = x;
  command.arg2 = y;
  draw_commands_.push_back(command);
}

void RendererCairo::Rotate(double radians) {
  Command command;
  command.command = DrawType::kCommandRotate;
  command.width = radians;
  draw_commands_.push_back(command);
}

uint32_t RendererCairo::ClosePath(bool fill) {
  Command command;
  command.command = DrawType::kCommandClosePath;
  command.arg1 = fill ? 1 : 0;
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
  Command command;
  command.command = DrawType::kCommandPenLine;
  command.points[0].x = x1;
  command.points[0].y = y1;
  draw_commands_.push_back(command);
  return 0;
}

void RendererCairo::DrawCircle(uint32_t x, uint32_t y, uint32_t radius, bool fill) {
  Command command;
  command.command = DrawType::kCommandCircle;
  command.points[0].x = x;
  command.points[0].y = y;
  command.radius = radius;
  command.points[1].x = 1;
  command.points[1].y = 0;
  command.fill = fill ? true : false;
  draw_commands_.push_back(command);
}

void RendererCairo::DrawArcRaw(uint32_t x, uint32_t y, uint32_t radius, uint32_t angle1, uint32_t angle2) {
  Command command;
  command.command = DrawType::kCommandArc;
  command.points[0].x = x;
  command.points[0].y = y;
  command.radius = radius;
  command.angle1 = angle1 * (M_PI / 180.0); /* angles are specified */
  command.angle2 = angle2 * (M_PI / 180.0); /* in radians           */
  draw_commands_.push_back(command);
}

void RendererCairo::DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool fill) {
  width += x;
  height += y;

  Command command;
  command.command = DrawType::kCommandPenRectangle;
  command.points[0].x = x;
  command.points[0].y = y;
  command.points[1].x = width;
  command.points[1].y = height;
  command.fill = fill ? true : false;
  draw_commands_.push_back(command);
}

void RendererCairo::DrawRoundedRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t corner,
                                         bool fill) {
  Command command;
  command.command = DrawType::kCommandPenRoundedRectangle;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = width;
  command.arg2 = height;
  command.arg3 = corner;
  command.fill = fill ? true : false;
  draw_commands_.push_back(command);
}

void RendererCairo::DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3,
                                 bool fill) {
  Command command;
  command.command = DrawType::kCommandPenTriangle;
  command.points[0].x = x1;
  command.points[0].y = y1;
  command.points[1].x = x2;
  command.points[1].y = y2;
  command.points[2].x = x3;
  command.points[2].y = y3;
  command.fill = fill ? true : false;
  draw_commands_.push_back(command);
}

uint32_t RendererCairo::DrawColor(uint8_t r, uint8_t g, uint8_t b) {
  Command command;
  command.command = DrawType::kCommandPenColour;
  command.colour.red = r;
  command.colour.green = g;
  command.colour.blue = b;
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::DrawColor(uint32_t rgb) {
  DrawColor((rgb & 0xff0000) >> 16, (rgb & 0xff00) >> 8, rgb & 0xff);
  return 0;
}

void RendererCairo::SetTextFont(uint32_t slope, widget::WeightType weight, std::string_view fontName, double size) {
  Command command;
  command.command = DrawType::kCommandTextFont;
  command.arg1 = slope;
  command.arg2 = int(weight);
  command.width = size;
  command.text = fontName;
  draw_commands_.push_back(command);
}

void RendererCairo::Push() {
  Command command;
  command.command = DrawType::kCommandPush;
  draw_commands_.push_back(command);
}

void RendererCairo::Pop() {
  Command command;
  command.command = DrawType::kCommandPop;
  draw_commands_.push_back(command);
}

uint32_t RendererCairo::GetTextWidth(std::string_view str, uint32_t fontSize) const {
  cairo_t *cr = render_.cr;
  cairo_text_extents_t extents;

  cairo_select_font_face(cr, config_->GetThemeFont().data(), CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(cr, fontSize);
  cairo_text_extents(cr, str.data(), &extents);
  return (uint32_t)extents.x_advance;
}

uint32_t RendererCairo::GetTextHeight(std::string_view str, uint32_t fontSize) const {
  cairo_t *cr = render_.cr;
  cairo_text_extents_t extents;

  cairo_set_font_size(cr, fontSize);
  cairo_text_extents(cr, str.data(), &extents);
  return (uint32_t)extents.height;
}

void RendererCairo::DrawText(uint32_t x, uint32_t y, std::string_view text) {
  Command command;
  command.command = DrawType::kCommandText;
  command.points[0].x = x;
  command.points[0].y = y;
  command.text = text;
  draw_commands_.push_back(command);
}

void RendererCairo::DrawLabel(uint32_t x, uint32_t y, std::string_view text) {
  y = render_.size.height - y;

  Command command;
  command.command = DrawType::kCommandText;
  command.points[0].x = x;
  command.points[0].y = y;
  command.text = text;
  draw_commands_.push_back(command);
}

void RendererCairo::DrawTextCentre(uint32_t x, std::string_view text, uint32_t size [[maybe_unused]]) {
  DrawText(x, 200, text);
}

uint32_t RendererCairo::TextureRGB(uint32_t x, uint32_t y, unsigned char *buffer, std::string_view file) {
  bool found_in_cache = false;

  image_type new_image;
  image_type *cache_image = nullptr;
  new_image.name = file;

  for (auto &image : cache_image_list_) {
    if (image.name == file) {
      // Found in cache
      found_in_cache = true;
      cache_image = &image;
      break;
    }
  }

  // Set background black, this is needed for transparent .png files
  SetColourForeground(ConfigData::GetInstance()->GetThemeBackground());
  SetColourBackground(ConfigData::GetInstance()->GetThemeBackground());
  DrawRectangle(0, 0, width_, height_, true);

  if (found_in_cache) {
    // Copy from cache
    new_image.name = cache_image->name;
    new_image.image = cache_image->image;
    new_image.from_cache = true;
  } else {
    // Add to cache
    cairo_surface_t *surf = cairo_image_surface_create_from_png(file.data());
    if (cairo_surface_status(surf) != CAIRO_STATUS_SUCCESS) {
      LOG(INFO) << "Could not load file " << file << ", not found!";
      return -1;
    }
    int width = cairo_image_surface_get_width(surf);

    if (int height = cairo_image_surface_get_height(surf);
        (height != gva::kMinimumHeight) || (width != gva::kMinimumWidth)) {
      cairo_surface_set_device_scale(surf, (double)width / kMinimumWidth, (double)height / kMinimumHeight);
    }

    // Add the image to the cache
    new_image.image = surf;
    new_image.name = file;
    new_image.from_cache = true;
    cache_image_list_.push_back(new_image);
  }
  image_list_.push_back(new_image);

  Command command;
  command.command = DrawType::kCommandImageTexture;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = (int32_t)image_list_.size();
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::TextureRGB(uint32_t x, uint32_t y, unsigned char *buffer) {
  image_type new_image;
  new_image.image = cairo_image_surface_create_for_data(buffer, CAIRO_FORMAT_ARGB32, width_, height_,
                                                        cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width_));
  image_list_.push_back(new_image);
  Command command;
  command.command = DrawType::kCommandImageTexture;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = (int32_t)image_list_.size();
  draw_commands_.push_back(command);
  return 0;
}

uint32_t RendererCairo::TextureRGB(uint32_t x, uint32_t y, cairo_surface_t *surface) {
  image_type new_image;

  new_image.name = "not specified";
  new_image.image = surface;
  image_list_.push_back(new_image);

  Command command;
  command.command = DrawType::kCommandImageTexturePersist;
  command.points[0].x = x;
  command.points[0].y = y;
  command.arg1 = (int32_t)image_list_.size();
  draw_commands_.push_back(command);
  return 0;
}

//
// ReDraw the screen from the surface. Note that the ::Draw
// signal receives a ready-to-be-used cairo_t that is already
// clipped to only Draw the exposed areas of the Widget
//
gboolean RendererCairo::DrawCb(GtkWidget *Widget, cairo_t *cr, gpointer data) {
  cairo_set_source_surface(cr, render_.surface, 0, 0);
  cairo_paint(cr);

  gtk_widget_queue_draw(Widget);
  return FALSE;
}

// Create a new surface of the appropriate size to store our HMI
gboolean RendererCairo::ConfigureEventCb(GtkWidget *Widget, GdkEventConfigure *event, gpointer data) {
  render_.surface = gdk_window_create_similar_surface(gtk_widget_get_window(Widget), CAIRO_CONTENT_COLOR,
                                                      gtk_widget_get_allocated_width(Widget),
                                                      gtk_widget_get_allocated_height(Widget));
  render_.cr = cairo_create(render_.surface);
  cairo_scale(render_.cr, (double)gtk_widget_get_allocated_width(Widget) / kMinimumWidth,
              (double)gtk_widget_get_allocated_height(Widget) / kMinimumHeight);
  Renderer::SetWidth(gtk_widget_get_allocated_width(Widget));
  Renderer::SetHeight(gtk_widget_get_allocated_height(Widget));
  gtk_widget_queue_draw(Widget);
  // We've handled the configure event, no need for further processing.
  return TRUE;
}

void RendererCairo::Activate(GtkApplication *app, gpointer user_data) {
  render_.win.win = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(render_.win.win), "HMI vivoe-lite");

  render_.win.draw = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(render_.win.win), render_.win.draw);
  // set a minimum size
  gtk_widget_set_size_request(render_.win.draw, kMinimumWidth, kMinimumHeight);

  //
  // Event signals
  //
  g_signal_connect(render_.win.win, "destroy", G_CALLBACK(CloseWindow), NULL);
  g_signal_connect(render_.win.draw, "button-press-event", G_CALLBACK(gva::EventsGva::ButtonPressEventCb), NULL);
  g_signal_connect(render_.win.draw, "button-release-event", G_CALLBACK(gva::EventsGva::ButtonReleaseEventCb), NULL);
  g_signal_connect(render_.win.win, "key-press-event", G_CALLBACK(gva::EventsGva::KeyPressEventCb), NULL);
  g_signal_connect(render_.win.win, "key-release-event", G_CALLBACK(gva::EventsGva::KeyReleaseEventCb), NULL);

  // Ask to receive events the Drawing area doesn't normally
  // subscribe to. In particular, we need to ask for the
  // button press and motion notify events that want to handle.
  //
  gtk_widget_set_events(render_.win.draw, gtk_widget_get_events(render_.win.draw) | GDK_BUTTON_PRESS_MASK |
                                              GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK);

  //
  // Signals used to handle the backing surface
  //
  g_signal_connect(render_.win.draw, "draw", G_CALLBACK(DrawCb), NULL);
  g_signal_connect(render_.win.draw, "configure-event", G_CALLBACK(ConfigureEventCb), NULL);
  if (render_.fullscreen) gtk_window_fullscreen(GTK_WINDOW(render_.win.win));

  gtk_widget_show_all(render_.win.win);
}

gboolean RendererCairo::Callback(gpointer data) {
  callback_(arg_, data);
  return TRUE;
}

void RendererCairo::CloseWindow(void) {
  if (render_.surface) cairo_surface_destroy(render_.surface);
}
}  // namespace gva
