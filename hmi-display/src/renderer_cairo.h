//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
//
// \file renderer_cairo.h
//

#ifndef HMI_DISPLAY_SRC_RENDERER_CAIRO_H_
#define HMI_DISPLAY_SRC_RENDERER_CAIRO_H_

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/renderer.h"
#include "src/renderer_cairo_types.h"
#include "src/widgets/widget_types.h"

namespace gva {

struct Command {
  DrawType command = DrawType::kCommandUndefined;
  double height = 0;
  double width = 0;
  std::array<PointType, 3> points;
  double radius = 0;
  double angle1 = 0;
  double angle2 = 0;
  ColourType colour = {HMI_WHITE};
  int32_t arg1 = 0;
  int32_t arg2 = 0;
  int32_t arg3 = 0;
  int32_t arg4 = 0;
  std::string text = "";
  bool fill = false;
};

struct image_type {
  std::string name;
  cairo_surface_t *image;
  bool from_cache;
};

enum class LineCapEnd { kLineCapButt, kLineCapRound, kLineCapSquare };

typedef void (*CallbackType)(void *io, gpointer data);

class RendererCairo : public Renderer {
 public:
  static HandleType render_;

  ///
  /// \brief Construct a new Renderer Cairo object
  ///
  /// \param width
  /// \param height
  ///
  RendererCairo(uint32_t width, uint32_t height);

  ///
  /// \brief Destroy the Renderer Cairo object
  ///
  ///
  ~RendererCairo() override;

  ///
  /// \brief Initalise the renderer with simple display parameters
  ///
  /// \param width Canvas width in pixels
  /// \param height Canvas height in pixels
  /// \return uint32_t
  ///
  uint32_t Init(uint32_t width, uint32_t height);

  ///
  /// \brief Initalise the renderer with display parameters
  ///
  /// \param width
  /// \param height
  /// \param fullscreen
  /// \param cb
  /// \param arg
  /// \return uint32_t
  ///
  uint32_t Init(uint32_t width, uint32_t height, bool fullscreen, CallbackType cb, void *arg);

  // Pure Virtual functions
  //
  ///
  /// \param x
  /// \param y
  ///
  void SetPixel(uint32_t x, uint32_t y) override;

  ///
  /// \brief Set the Colour object
  ///
  /// \param red
  /// \param green
  /// \param blue
  ///
  void SetColour(uint8_t red, uint8_t green, uint8_t blue) override;

  ///
  /// \brief Set the Colour object
  ///
  /// \param rgb
  ///
  void SetColour(uint32_t rgb);

  ///
  /// \brief Set the Colour Foreground object
  ///
  /// \param red
  /// \param green
  /// \param blue
  ///
  void SetColourForeground(uint8_t red, uint8_t green, uint8_t blue) override;

  ///
  /// \brief Set the Colour Foreground object
  ///
  /// \param rgb
  ///
  void SetColourForeground(uint32_t rgb);

  ///
  /// \brief Set the Colour Background object
  ///
  /// \param red
  /// \param green
  /// \param blue
  ///
  void SetColourBackground(uint8_t red, uint8_t green, uint8_t blue) override;

  ///
  /// \brief Set the Colour Background object
  ///
  /// \param rgb
  ///
  void SetColourBackground(uint32_t rgb);

  ///
  /// \brief Set the Line Type object
  ///
  /// \param type
  ///
  void SetLineType(uint32_t type);

  ///
  /// \brief Set the Line Thickness object
  ///
  /// \param thickness
  /// \param fill
  ///
  void SetLineThickness(uint32_t thickness, LineType fill);

  ///
  /// \brief Set the Line Thickness object
  ///
  /// \param thickness
  /// \param fill
  /// \param end
  ///
  void SetLineThickness(uint32_t thickness, LineType fill, LineCapEnd end);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \return uint32_t
  ///
  uint32_t MovePen(int32_t x, int32_t y);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param close
  /// \return uint32_t
  ///
  uint32_t DrawPen(uint32_t x, uint32_t y, bool close);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \return uint32_t
  ///
  uint32_t DrawPen(uint32_t x, uint32_t y) { return DrawPen(x, y, false); }

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \return uint32_t
  ///
  uint32_t MovePenRaw(int32_t x, int32_t y);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \return uint32_t
  ///
  uint32_t DrawPenRaw(int32_t x, int32_t y);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param radius
  /// \param angle1
  /// \param angle2
  ///
  void DrawArcRaw(uint32_t x, uint32_t y, uint32_t radius, uint32_t angle1, uint32_t angle2);

  ///
  /// \brief
  ///
  /// \param x1
  /// \param y1
  /// \param x2
  /// \param y2
  /// \return uint32_t
  ///
  uint32_t DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) override;

  ///
  /// \brief
  ///
  ///
  void Save();

  ///
  /// \brief
  ///
  ///
  void Restore();

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  ///
  void Scale(double x, double y);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  ///
  void Translate(uint32_t x, uint32_t y);

  ///
  /// \brief
  ///
  /// \param radians
  ///
  void Rotate(double radians);

  ///
  /// \brief
  ///
  /// \param fill
  /// \return uint32_t
  ///
  uint32_t ClosePath(bool fill);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param radius
  /// \param fill
  ///
  void DrawCircle(uint32_t x, uint32_t y, uint32_t radius, bool fill) override;

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param width
  /// \param height
  /// \param fill
  ///
  void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool fill) override;

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param width
  /// \param height
  /// \param courner
  /// \param fill
  ///
  void DrawRoundedRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t courner, bool fill);

  ///
  /// \brief
  ///
  /// \param x1
  /// \param y1
  /// \param x2
  /// \param y2
  /// \param x3
  /// \param y3
  /// \param fill
  ///
  void DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, bool fill);

  ///
  /// \brief
  ///
  /// \param r
  /// \param g
  /// \param b
  /// \return uint32_t
  ///
  uint32_t DrawColor(uint8_t r, uint8_t g, uint8_t b) override;

  ///
  /// \brief
  ///
  /// \param rgb
  /// \return uint32_t
  ///
  uint32_t DrawColor(uint32_t rgb);

  ///
  /// \brief Set the Text Font object
  ///
  /// \param slope
  /// \param weight
  /// \param fontName
  ///
  void SetTextFont(uint32_t slope, widget::WeightType weight, std::string fontName, double size);

  ///
  /// \brief
  ///
  ///
  void Push();

  ///
  /// \brief
  ///
  ///
  void Pop();

  ///
  /// \brief Get the Text Width object
  ///
  /// \param str
  /// \param fontSize
  /// \return uint32_t
  ///
  uint32_t GetTextWidth(const std::string str, uint32_t fontSize);

  ///
  /// \brief Get the Text Height object
  ///
  /// \param str
  /// \param fontSize
  /// \return uint32_t
  ///
  uint32_t GetTextHeight(const std::string str, uint32_t fontSize);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param text
  ///
  void DrawText(uint32_t x, uint32_t y, const std::string text);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param text
  ///
  void DrawLabel(uint32_t x, uint32_t y, const std::string text);

  ///
  /// \brief
  ///
  /// \param x
  /// \param text
  /// \param size
  ///
  void DrawTextCentre(uint32_t x, const std::string text, uint32_t size);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param buffer
  /// \param file
  /// \return uint32_t
  ///
  uint32_t TextureRGB(uint32_t x, uint32_t y, unsigned char *buffer, std::string file) override;

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param buffer
  /// \return uint32_t
  ///
  uint32_t TextureRGB(uint32_t x, uint32_t y, unsigned char *buffer);

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param surface
  /// \return uint32_t
  ///
  uint32_t TextureRGB(uint32_t x, uint32_t y, cairo_surface_t *surface);

  // Cairo specific functions

  ///
  /// \brief Redraw the screen
  ///
  ///
  void Draw();

  ///
  /// \brief
  ///
  ///
  void Reset() {
    draw_commands_.clear();
    image_list_.clear();
  }

  ///
  /// \brief Get the Window object
  ///
  /// \return gtkType*
  ///
  gtkType *GetWindow() { return &render_.win; }

  ///
  /// \brief Set the Height object
  ///
  /// \param height
  ///
  void SetHeight(uint32_t height) const {
    height_ = height;
    gtk_widget_set_size_request(render_.win.draw, (gint)width_, (gint)height_);
  }

  ///
  /// \brief Set the Width object
  ///
  /// \param width
  ///
  void SetWidth(uint32_t width) const {
    width_ = width;
    gtk_widget_set_size_request(render_.win.draw, (gint)width_, (gint)height_);
  }

  ///
  /// \brief Get the Height object
  ///
  /// \return uint32_t
  ///
  uint32_t GetHeight() const {
    gint h;
    gint w;
    gtk_widget_get_size_request(render_.win.draw, &w, &h);
    return w;
  }

  ///
  /// \brief Get the Width object
  ///
  /// \return uint32_t
  ///
  uint32_t GetWidth() const {
    gint h;
    gint w;
    gtk_widget_get_size_request(render_.win.draw, &w, &h);
    return h;
  }

 private:
  char *texture_;
  int32_t current_handle_;
  double scale_;
  gtkType root_;

  ///
  /// \brief Convert a standard integer to a double for use with the cairo colour system
  ///
  /// \param c The integer value to convert
  /// \return double
  ///
  double IntToFloat(int c) const { return static_cast<double>(1) / 255 * c; }

  //
  // Render List
  //
  std::vector<Command> draw_commands_;

  //
  // Image List
  //
  std::vector<image_type> image_list_;

  //
  // Image Cache
  //
  std::vector<image_type> cache_image_list_;
  static gboolean DrawCb(GtkWidget *Widget, cairo_t *cr, gpointer data);
  static gboolean ConfigureEventCb(GtkWidget *Widget, GdkEventConfigure *event, gpointer data);
  static void Activate(GtkApplication *app, gpointer user_data);
  static gboolean Callback(gpointer user_data);
  static void CloseWindow(void);
  ConfigData *config_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_CAIRO_H_
