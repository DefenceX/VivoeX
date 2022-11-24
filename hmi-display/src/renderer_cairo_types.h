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
/// \brief The data types needed by the 2D vector graphics cairo renderer
///
/// \file renderer_cairo_types.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_CAIRO_TYPES_H_
#define HMI_DISPLAY_SRC_RENDERER_CAIRO_TYPES_H_

namespace gva {

struct gtkType {
  GtkApplication *app;
  GtkWidget *win;
  GtkWidget *draw;
  uint32_t height;
  uint32_t width;
};

#define MAX_COMMANDS 1000
#define MAX_IMAGES 100

class HandleType {
 public:
  uint32_t handle;
  bool inUse;
  bool fullscreen;
  ResolutionType size;
  gtkType win;
  cairo_surface_t *surface;
  cairo_t *cr;
};

enum Draw_type {
  kCommandCircle = 0,
  kCommandArc,
  kCommandColourBackground,
  kCommandColourForeground,
  kCommandImageTexture,
  kCommandImageTexturePersist,
  kCommandLineJoin,
  kCommandPenColour,
  kCommandPenCurve,
  kCommandPenLine,
  kCommandPenDraw,
  kCOmmandPenMove,
  kCommandPenRectangle,
  kCommandPenRoundedRectangle,
  kCommandPenThickness,
  kCommandPenTriangle,
  kCommandSave,
  kCommandRestore,
  kCommandScale,
  kCommandTranslate,
  kCommandRotate,
  kCommandClosePath,
  kCommandTextFont,
  kCommandText
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_CAIRO_TYPES_H_