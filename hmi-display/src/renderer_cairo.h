///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief The Cairo renderer for drawing on the screen. See https://www.cairographics.org/
///
/// \file renderer_cairo.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_CAIRO_H_
#define HMI_DISPLAY_SRC_RENDERER_CAIRO_H_

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <string>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/renderer.h"
#include "src/renderer_cairo_types.h"
#include "src/widgets/widget_types.h"

namespace gva {

struct command_type {
  Draw_type command;
  double height;
  double width;
  PointType points[3];
  double radius;
  double angle1;
  double angle2;
  ColourType colour;
  int32_t arg1;
  int32_t arg2;
  int32_t arg3;
  int32_t arg4;
  char text[80];
  bool fill;
};

struct image_type {
  char name[255];
  cairo_surface_t *image;
  bool from_cache;
};

typedef enum { LINE_CAP_BUTT, LINE_CAP_ROUND, LINE_CAP_SQUARE } LineCapEnd;

typedef void (*CallbackType)(void *io, gpointer data);

class RendererCairo : public Renderer {
 public:
  static HandleType render_;
  RendererCairo(uint32_t width, uint32_t height);
  ~RendererCairo();
  uint32_t Init(uint32_t width, uint32_t height);
  uint32_t Init(uint32_t width, uint32_t height, bool fullscreen, CallbackType cb, void *arg);
  // Pure Virtual functions
  void SetPixel(uint32_t x, uint32_t y) override;
  void SetColour(uint8_t red, uint8_t green, uint8_t blue) override;
  void SetColour(uint32_t rgb);
  void SetColourForeground(uint8_t red, uint8_t green, uint8_t blue) override;
  void SetColourForeground(uint32_t rgb);
  void SetColourBackground(uint8_t red, uint8_t green, uint8_t blue) override;
  void SetColourBackground(uint32_t rgb);
  void setLineType(uint32_t type);
  void SetLineThickness(uint32_t thickness, LineType fill);
  void SetLineThickness(uint32_t thickness, LineType fill, LineCapEnd end);
  uint32_t MovePen(int32_t x, int32_t y);
  uint32_t DrawPen(uint32_t x, uint32_t y, bool close);
  uint32_t DrawPen(uint32_t x, uint32_t y) { return DrawPen(x, y, false); }
  uint32_t MovePenRaw(int32_t x, int32_t y);
  uint32_t DrawPenRaw(int32_t x, int32_t y);
  void DrawArcRaw(uint32_t x, uint32_t y, uint32_t radius, uint32_t angle1, uint32_t angle2);
  uint32_t DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) override;
  void Save();
  void Restore();
  void Scale(double x, double y);
  void Translate(uint32_t x, uint32_t y);
  void Rotate(double radians);
  uint32_t ClosePath(bool fill);
  void DrawCircle(uint32_t x, uint32_t y, uint32_t radius, bool fill) override;
  void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool fill) override;
  void DrawRoundedRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t courner, bool fill);
  void DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, bool fill);
  uint32_t DrawColor(uint8_t r, uint8_t g, uint8_t b) override;
  uint32_t DrawColor(uint32_t rgb);
  void SetTextFont(uint32_t slope, WeightType weight, std::string fontName);
  void Push();
  void Pop();
  uint32_t GetTextWidth(const std::string str, uint32_t fontSize);
  uint32_t GetTextHeight(const std::string str, uint32_t fontSize);
  void DrawText(uint32_t x, uint32_t y, const std::string text, uint32_t size);
  void DrawLabel(uint32_t x, uint32_t y, const std::string text, uint32_t size);
  void DrawTextCentre(uint32_t x, const std::string text, uint32_t size);
  uint32_t TextureRGB(uint32_t x, uint32_t y, void *buffer, std::string file) override;
  uint32_t TextureRGB(uint32_t x, uint32_t y, void *buffer);
  uint32_t TextureRGB(uint32_t x, uint32_t y, cairo_surface_t *surface);

  // Cairo specific functions
  void Draw();
  void Reset() {
    draw_tail_ = 0;
    image_tail_ = 0;
  }
  gtkType *GetWindow() { return &render_.win; }

  void SetHeight(uint32_t height) {
    height_ = height;
    gtk_widget_set_size_request(render_.win.draw, (gint)width_, (gint)height_);
  }
  void SetWidth(uint32_t width) {
    width_ = width;
    gtk_widget_set_size_request(render_.win.draw, (gint)width_, (gint)height_);
  }
  uint32_t GetHeight() {
    gint h, w;
    gtk_widget_get_size_request(render_.win.draw, &w, &h);
    return static_cast<int>(w);
  }
  uint32_t GetWidth() {
    gint h, w;
    gtk_widget_get_size_request(render_.win.draw, &w, &h);
    return static_cast<int>(h);
  }

 private:
  char *texture_;
  int32_t current_handle_;
  double scale_;
  gtkType root_;

  //
  // Helper Functions
  //
  // double intToFloat(int c) { return (double)1 / 255 * c; }
  double intToFloat(int c) { return static_cast<double>(1) / 255 * c; }

  //
  // Render List
  //
  command_type Draw_commands_[MAX_COMMANDS];
  uint32_t draw_tail_ = 0;

  //
  // Image List
  //
  image_type image_list_[MAX_IMAGES];
  uint32_t image_tail_ = 0;

  //
  // Image Cache
  //
  image_type cache_image_list_[MAX_IMAGES];
  uint32_t cache_image_tail_ = 0;

  static gboolean DrawCb(GtkWidget *Widget, cairo_t *cr, gpointer data);
  static gboolean ConfigureEventCb(GtkWidget *Widget, GdkEventConfigure *event, gpointer data);
  static void Activate(GtkApplication *app, gpointer user_data);
  static gboolean Callback(gpointer user_data);
  static void CloseWindow(void);
  ConfigData *config_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_CAIRO_H_
