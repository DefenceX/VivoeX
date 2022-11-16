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
/// \file screen_gva.h
///

#ifndef HMI_DISPLAY_SRC_SCREEN_GVA_H_
#define HMI_DISPLAY_SRC_SCREEN_GVA_H_
#include <cairo.h>
#include <pthread.h>

#include <memory>
#include <vector>

#include "common/log_gva.h"
#include "nmea/nmea.h"
#include "src/gva.h"
#include "src/renderer_gva.h"
#include "widgets/table.h"
#include "widgets/widget.h"

namespace gva {

class Canvas {
 public:
  bool visible;
  SurfaceType bufferType;
  char filename[256];
  char *buffer;
  cairo_surface_t *surface;
};

class Label {
 public:
  bool visible;
  char text[256];
  uint32_t x;
  uint32_t y;
  uint32_t fontSize;
};

class Message {
 public:
  bool visible;
  uint32_t width;
  IconType icon;
  struct {
    char text[256];
    uint32_t fontSize;
  } brief;
  struct {
    char text[4096];
    uint32_t fontSize;
  } detail;
};

class Screen {
 public:
  struct {
   public:
    char name[100];
    ScreenMode mode;
    char gpsDevice[100];
  } info;
  GvaFunctionEnum currentFunction;
  Canvas canvas;
  FunctionSelectType *function_top;
  CommonTaskKeys *control;
  StatusBar *status_bar;
  FunctionKeys function_left;
  FunctionKeys function_right;
  TableWidget table;
  Label label;
  Message message;
  LabelModeEnum labels;
};

//
// These are used by the clock thread to update the time and refresh the screen
//
class args {
 public:
  char *clockString;
  char *locationFormat;
  char *locationString;
  ScreenGva *screen;
  uint32_t *gps;
  nmeaINFO *info;
  nmeaPARSER *parser;
  bool active;
  LocationType *location;
};

class ScreenGva : public RendererGva {
 public:
  ///
  /// \brief Construct a new Screen Gva object
  ///
  /// \param screen
  /// \param width
  /// \param height
  ///
  ScreenGva(Screen *screen, uint32_t width, uint32_t height);

  ///
  /// \brief Destroy the Screen Gva object
  ///
  ///
  ~ScreenGva();

  ///
  /// \brief Redraw the screen
  ///
  /// \return GvaStatusTypes Status
  ///
  GvaStatusTypes Update();

  ///
  /// \brief Start the clock threa #include <vector>d running to update the clock (pthread started)
  ///
  /// \param barData
  ///
  void StartClock(StatusBar *barData);

  ///
  /// \brief Get the Widget object
  ///
  /// \param widget
  /// \return WidgetX*
  ///
  WidgetX *GetWidget(WidgetEnum widget);

 private:
  char *PosDegrees(float lon, float lat);
  Screen *screen_;
  std::vector<WidgetX *> widget_list_;
  args *args_;
  uint32_t gps_;
  uint32_t hndl_;
  Screen last_screen_;
  pthread_t clock_thread_;
  nmeaINFO info_;
  nmeaPARSER parser_;
  ConfigData *config_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_SCREEN_GVA_H_
