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
/// \brief
///
/// \file renderer.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_H_
#define HMI_DISPLAY_SRC_RENDERER_H_
#include <stdint.h>

#include <string>

#include "src/debug.h"

#define MAX_HANDLES 10
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

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

typedef struct {
  uint32_t red;
  uint32_t green;
  uint32_t blue;
} ColourType;

typedef struct {
  int32_t x;
  int32_t y;
} PointType;

typedef struct {
  uint32_t width;
  uint32_t height;
  uint32_t depth;
} ResolutionType;

struct RgbUnpackedType {
  uint32_t r;
  uint32_t g;
  uint32_t b;
};

class RendererCairo;

class Renderer {
 public:
  Renderer(uint32_t width, uint32_t height);
  virtual ~Renderer();
  virtual void SetPixel(uint32_t x, uint32_t y) = 0;
  virtual void SetColour(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual void SetColourForeground(uint8_t red, uint8_t green, uint8_t blue) = 0;
  virtual void SetColourBackground(uint8_t red, uint8_t green, uint8_t blue) = 0;
  static uint32_t GetWidth() { return width_; }
  static uint32_t GetHeight() { return height_; }
  static void SetWidth(uint32_t width) { width_ = width; }
  static void SetHeight(uint32_t height) { height_ = height; }
  virtual uint32_t DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) = 0;
  virtual void DrawCircle(uint32_t x, uint32_t y, uint32_t radius, bool fill) = 0;
  virtual void DrawRectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, bool fill) = 0;
  virtual uint32_t DrawColor(uint8_t r, uint8_t g, uint8_t b) = 0;
  virtual uint32_t TextureRGB(uint32_t x, uint32_t y, void *buffer, std::string file) = 0;
  static uint64_t PackRgb(uint8_t r, uint8_t g, uint8_t b) {
    uint64_t packed = (r << 16) | (g << 8) | b;
    return packed;
  }
  uint32_t UnpackRed(uint32_t rgb) { return (rgb & 0xff0000) >> 16; }
  uint32_t UnpackGreen(uint32_t rgb) { return (rgb & 0xff00) >> 8; }
  uint32_t UnpackBlue(uint32_t rgb) { return rgb & 0xff; }
  RgbUnpackedType UnpackRgb(uint64_t rgb) {
    RgbUnpackedType colour;
    colour.r = (rgb & 0x0000000000ff0000) >> 16;
    colour.g = (rgb & 0x000000000000ff00) >> 8;
    colour.b = (rgb & 0x00000000000000ff);
    return colour;
  }

 protected:
  static uint32_t height_;
  static uint32_t width_;

 private:
  ColourType forground_colour_;
  ColourType background_colour_;
  friend class rendererSdl;
  friend class RendererCairo;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_H_
