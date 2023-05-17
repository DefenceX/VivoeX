//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer.h
///

#ifndef HMICORE_RENDERER_H_
#define HMICORE_RENDERER_H_
#include <stdint.h>

#include <string>

#include "hmicore/gva.h"

#define HMI_AMBER 255, 153, 0
#define HMI_WHITE 255, 255, 255
#define HMI_RED 255, 0, 0
#define HMI_GREY 127, 127, 127
#define HMI_MEDIUM_GREY 96, 96, 96
#define HMI_DARK_GREY 64, 64, 64
#define HMI_GREEN 0, 255, 0
#define HMI_DARK_GREEN 0, 128, 0
#define HMI_DARK_GREEN2 0, 75, 0
#define HMI_BLUE 0, 0, 255
#define HMI_CYAN 0, 255, 255
#define HMI_DARK_BLUE 51, 102, 153
#define HMI_LIGHT_BLUE 50, 50, 255
#define HMI_BLACK 0, 0, 0
#define HMI_YELLOW 255, 255, 0

#define HMI_ORANGE 255, 165, 0
#define HMI_NONE -1, -1, -1

namespace gva {

class RendererCairo;

class Renderer {
 public:
  ///
  /// \brief Construct a new Renderer object
  ///
  /// \param width
  /// \param height
  ///
  Renderer(uint32_t width, uint32_t height);

  ///
  /// \brief Destroy the Renderer object
  ///
  ///
  virtual ~Renderer() = default;

  ///
  /// \brief Set the Pixel attribute
  ///
  /// \param x
  /// \param y
  ///
  virtual void SetPixel(uint32_t x, uint32_t y) = 0;

  ///
  /// \brief Set the Colour attribute
  ///
  /// \param red
  /// \param green
  /// \param blue
  ///
  virtual void SetColour(uint8_t red, uint8_t green, uint8_t blue) = 0;

  ///
  /// \brief Set the Colour Foreground attribute
  ///
  /// \param red
  /// \param green
  /// \param blue
  ///
  virtual void SetColourForeground(uint8_t red, uint8_t green, uint8_t blue) = 0;

  ///
  /// \brief Set the Colour Background attribute
  ///
  /// \param red
  /// \param green
  /// \param blue
  ///
  virtual void SetColourBackground(uint8_t red, uint8_t green, uint8_t blue) = 0;

  ///
  /// \brief Get the Width attribute
  ///
  /// \return uint32_t
  ///
  static uint32_t GetWidth() { return width_; }

  ///
  /// \brief Get the Height attribute
  ///
  /// \return uint32_t
  ///
  static uint32_t GetHeight() { return height_; }

  ///
  /// \brief Set the Width attribute
  ///
  /// \param width The width of the renderer
  ///
  static void SetWidth(uint32_t width) { width_ = width; }

  ///
  /// \brief Set the Height attribute
  ///
  /// \param height The height of the renderer
  ///
  static void SetHeight(uint32_t height) { height_ = height; }

  ///
  /// \brief Draw a straight line
  ///
  /// \param x1 The start X position
  /// \param y1 The start Y position
  /// \param x2 The end X position
  /// \param y2 The end Y position
  /// \return uint32_t
  ///
  virtual uint32_t DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) = 0;

  ///
  /// \brief Draw a circle, set filled to true to have solid circle
  ///
  /// \param x The X position
  /// \param y The Y position
  /// \param radius The radius of the circle
  /// \param fill Set to true to have a solid circle
  ///
  virtual void DrawCircle(uint32_t x, uint32_t y, uint32_t radius, bool fill) = 0;

  ///
  /// \brief Draw a rectangle, set filled to true to have solid rectangle
  ///
  /// \param x1 The start X position
  /// \param y1 The start Y position
  /// \param x2 The end X position
  /// \param y2 The end Y position
  /// \param fill Set to true to have a solid rectangle
  ///
  virtual void DrawRectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool fill) = 0;

  ///
  /// \brief Set the draw colour
  ///
  /// \param r The red value
  /// \param g The green value
  /// \param b The blue value
  /// \return uint32_t
  ///
  virtual uint32_t DrawColor(uint8_t r, uint8_t g, uint8_t b) = 0;

  ///
  /// \brief Set the background texture to and RGB buffer (No Alpha channel)
  ///
  /// \param x The X position
  /// \param y The Y position
  /// \param buffer The RGB buffer
  /// \param file The file name
  /// \return uint32_t The number of bytes written
  ///
  virtual uint32_t TextureRGB(uint32_t x, uint32_t y, unsigned char* buffer, std::string_view file) = 0;

  ///
  /// \brief Pack three red, green, blue values
  ///
  /// \param r The red value
  /// \param g The green value
  /// \param b The blue value
  /// \return uint64_t The packed value
  ///
  static uint32_t PackRgb(uint8_t r, uint8_t g, uint8_t b);

  ///
  /// \brief Unpack a red value
  ///
  /// \param rgb
  /// \return uint32_t
  ///
  uint32_t UnpackRed(uint32_t rgb) const { return (rgb & 0xff0000) >> 16; }

  ///
  /// \brief Unpack a green value
  ///
  /// \param rgb
  /// \return uint32_t
  ///
  uint32_t UnpackGreen(uint32_t rgb) const { return (rgb & 0xff00) >> 8; }

  ///
  /// \brief Unpack a blue value
  ///
  /// \param rgb
  /// \return uint32_t
  ///
  uint32_t UnpackBlue(uint32_t rgb) const { return rgb & 0xff; }

  ///
  /// \brief Unpack red, green and blue values
  ///
  /// \param rgb
  /// \return RgbUnpackedType
  ///
  RgbUnpackedType UnpackRgb(uint64_t rgb) const;

 protected:
  /// The height of the renderer
  static uint32_t height_;
  /// The width of the renderer
  static uint32_t width_;

 private:
  /// The foreground colour
  ColourType foreground_colour_;
  /// The background colour
  ColourType background_colour_;
  /// The Cairo renderer
  friend class RendererCairo;
};

}  // namespace gva

#endif  // HMICORE_RENDERER_H_
