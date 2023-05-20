//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer_cairo.h
///

#ifndef HMICORE_RENDERER_CAIRO_H_
#define HMICORE_RENDERER_CAIRO_H_

#include <cairo.h>
#include <gtk/gtk.h>
#include <stdio.h>

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "hmicore/config_reader.h"
#include "hmicore/gva.h"
#include "hmicore/renderer.h"
#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

/// The Command structure
struct Command {
  /// The command type
  DrawType command = DrawType::kCommandUndefined;
  /// The height value
  double height = 0;
  /// The width value
  double width = 0;
  /// Points value
  std::array<PointType, 3> points;
  /// The radius value
  double radius = 0;
  /// The angle1 value
  double angle1 = 0;
  /// The angle2 value
  double angle2 = 0;
  /// The colour value
  ColourType colour = kHmiWhite;
  /// An argument value 1
  int32_t arg1 = 0;
  /// An argument value 2
  int32_t arg2 = 0;
  /// An argument value 3
  int32_t arg3 = 0;
  /// An argument value 4
  int32_t arg4 = 0;
  /// String text
  std::string text = "";
  /// Fill if true
  bool fill = false;
};

/// Struct definition of the image_type
struct image_type {
  /// The images string filename
  std::string name;
  /// The images cairo surface
  cairo_surface_t *image;
  /// True if read from cache
  bool from_cache;
};

/// Struct definition of the LineType
enum class LineCapEnd { kLineCapButt, kLineCapRound, kLineCapSquare };

/// callback typr
typedef void (*CallbackType)(void *io, gpointer data);

/// Class definition of the Renderer Cairo
class RendererCairo : public Renderer {
 public:
  /// Class definition of the HandleType
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
  /// \brief Initalise the renderer with display parameters
  ///
  /// \param width Canvas width in pixels
  /// \param height Canvas height in pixels
  /// \param fullscreen Fullscreen mode when true
  /// \return HandleType* a pointer to the renderer handler
  ///
  HandleType *Init(uint32_t width, uint32_t height, bool fullscreen = false);

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
  /// \param colour The colour to set
  ///
  void SetColourForeground(ColourType colour);

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
  /// \brief Set the Colour Background attribute
  ///
  /// \param colour
  ///
  void SetColourBackground(ColourType colour);

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
  /// \brief Save the current state of the renderer
  ///
  ///
  void Save();

  ///
  /// \brief Restore the last saved state of the renderer
  ///
  ///
  void Restore();

  ///
  /// \brief Scale the renderer
  ///
  /// \param x The x scale
  /// \param y The y scale
  ///
  void Scale(double x, double y);

  ///
  /// \brief Translate the renderer
  ///
  /// \param x The x position to translate to
  /// \param y The y position to translate to
  ///
  void Translate(uint32_t x, uint32_t y);

  ///
  /// \brief Rotate the renderer
  ///
  /// \param radians The angle to rotate by
  ///
  void Rotate(double radians);

  ///
  /// \brief Close drawing path
  ///
  /// \param fill Fill if true
  /// \return uint32_t
  ///
  uint32_t ClosePath(bool fill);

  ///
  /// \brief Draw a circle
  ///
  /// \param x The x position
  /// \param y The y position
  /// \param radius The radius in pixels
  /// \param fill Fill if true
  ///
  void DrawCircle(uint32_t x, uint32_t y, uint32_t radius, bool fill) override;

  ///
  /// \brief Draw a rectangle
  ///
  /// \param x The x position
  /// \param y The y position
  /// \param width The width in pixels
  /// \param height The height in pixels
  /// \param fill Fill if true
  ///
  void DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool fill) override;

  ///
  /// \brief Draw a rounded rectangle
  ///
  /// \param x The x position
  /// \param y The y position
  /// \param width The width
  /// \param height The height in pixels
  /// \param corner The corner radius
  /// \param fill Fill if true
  ///
  void DrawRoundedRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t corner, bool fill);

  ///
  /// \brief Draw a triangle
  ///
  /// \param x1 The first x position
  /// \param y1 The first y position
  /// \param x2 The second x position
  /// \param y2 The second y position
  /// \param x3 The third x position
  /// \param y3 The third y position
  /// \param fill Fill if true
  ///
  void DrawTriangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3, bool fill);

  ///
  /// \brief Set the Colour object to draw with
  ///
  /// \param colour The colour to draw with
  /// \return uint32_t
  ///
  uint32_t DrawColor(ColourType colour);

  ///
  /// \brief Set the Colour object to draw with
  ///
  /// \param r The red value
  /// \param g The green value
  /// \param b The blue value
  /// \return uint32_t
  ///
  uint32_t DrawColor(uint8_t r, uint8_t g, uint8_t b) override;

  ///
  /// \brief Adds a cubic Bézier spline to the path from the current point to position (x3 , y3 ) in user-space
  /// coordinates, using (x1 , y1 ) and (x2 , y2 ) as the control points. After this call the current point will be (x3
  /// , y3 ).
  ///
  /// \param x1 first point of x in pixels
  /// \param y1 first point of y in pixels
  /// \param x2 second point of x in pixels
  /// \param y2 second point of y in pixels
  /// \param x3 third point of x in pixels
  /// \param y3 third point of y in pixels
  /// \return uint32_t
  ///
  uint32_t CurveTo(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t x3, uint32_t y3);

  ///
  /// \brief Set the draw colour
  ///
  /// \param rgb The colour to draw with, packed RGB
  /// \return uint32_t
  ///
  uint32_t DrawColor(uint32_t rgb);

  ///
  /// \brief Set the Text Font object
  ///
  /// \param slope The font slope
  /// \param weight The font weight
  /// \param font_name The font name
  /// \param size The font size
  ///
  void SetTextFont(uint32_t slope, widget::WeightType weight, std::string_view font_name, double size);

  ///
  /// \brief Push the current state of the renderer
  ///
  ///
  void Push();

  ///
  /// \brief Pop the last saved state of the renderer
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
  uint32_t GetTextWidth(std::string_view str, uint32_t fontSize) const;

  ///
  /// \brief Get the Text Height object
  ///
  /// \param str
  /// \param fontSize
  /// \return uint32_t
  ///
  uint32_t GetTextHeight(std::string_view str, uint32_t fontSize) const;

  ///
  /// \brief Draw some text on the screen
  ///
  /// \param x axis pixel postion
  /// \param y axis pixel postion
  /// \param text
  ///
  void DrawText(uint32_t x, uint32_t y, std::string_view text);

  ///
  /// \brief Draw an on screen label
  ///
  /// \param x axis pixel postion
  /// \param y axis pixel postion
  /// \param text
  ///
  void DrawLabel(uint32_t x, uint32_t y, std::string_view text);

  ///
  /// \brief Draw some text on the screen and centre it
  ///
  /// \param x axis pixel postion
  /// \param text to draw
  /// \param size of the text
  ///
  void DrawTextCentre(uint32_t x, std::string_view text, uint32_t size);

  ///
  /// \brief Set a texture (file) to use as a bitmap
  ///
  /// \param x axis pixel postion
  /// \param y axis pixel postion
  /// \param buffer unused when file set
  /// \param file to load
  /// \return uint32_t the texture id
  ///
  uint32_t TextureRGB(uint32_t x, uint32_t y, unsigned char *buffer, std::string_view file) override;

  ///
  /// \brief Set a texture (file) to use as a bitmap
  ///
  /// \param x axis pixel postion
  /// \param y axis pixel postion
  /// \param buffer to load the image into
  /// \return uint32_t the texture id
  ///
  uint32_t TextureRGB(uint32_t x, uint32_t y, unsigned char *buffer);

  ///
  /// \brief Set a texture (cairo surface) to use as a bitmap
  ///
  /// \param x axis pixel postion
  /// \param y axis pixel postion
  /// \param surface to load the image into
  /// \return uint32_t the texture id
  ///
  uint32_t TextureRGB(uint32_t x, uint32_t y, cairo_surface_t *surface);

  // Cairo specific functions

  ///
  /// \brief Redraw the screen
  ///
  ///
  void Draw();

  ///
  /// \brief Redraw the screen
  ///
  ///
  void Reset() {
    draw_commands_.clear();
    image_list_.clear();
  }

  ///
  /// \brief Set the Height object
  ///
  /// \param height
  ///
  void SetHeight(uint32_t height) const { height_ = height; }

  ///
  /// \brief Set the Width object
  ///
  /// \param width
  ///
  void SetWidth(uint32_t width) const { width_ = width; }

  ///
  /// \brief Get the Height object
  ///
  /// \return uint32_t
  ///
  uint32_t GetHeight() const { return height_; }

  ///
  /// \brief Get the Width object
  ///
  /// \return uint32_t
  ///
  uint32_t GetWidth() const { return height_; }

  ///
  /// \brief Set the Surface attribute, used by application
  ///
  /// \param surface
  ///
  void SetSurface(cairo_surface_t *surface);

  ///
  /// \brief Draw the new cairo surface to the screen
  ///
  /// \return gboolean
  ///
  void DrawSurface(cairo_t *cr);

  ///
  /// \brief Configure the surface to use new dimensions
  ///
  /// \param height
  /// \param width
  ///
  void Configure(uint32_t height, uint32_t width);

  ///
  /// \brief Destroy the current cairo surface, usually called during shutdown
  ///
  ///
  static void DestroySurface();

 private:
  int32_t current_handle_;
  double scale_ = 1.0;

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
  ConfigData *config_;
};

}  // namespace gva

#endif  // HMICORE_RENDERER_CAIRO_H_
