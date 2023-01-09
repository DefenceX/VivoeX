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
/// \brief The screen manger for the GVA application
///
/// \file screen_gva.h
///

#ifndef HMI_DISPLAY_SRC_SCREEN_GVA_H_
#define HMI_DISPLAY_SRC_SCREEN_GVA_H_
#include <cairo.h>
#include <pthread.h>

#include <map>
#include <memory>
#include <string>

#include "common/log_gva.h"
#include "nmea/nmea.h"
#include "src/gva.h"
#include "src/renderer_gva.h"
#include "widgets/table/table.h"
#include "widgets/widget_types.h"

namespace gva {

struct Canvas {
  bool visible;
  SurfaceType bufferType;
  std::string filename;
  unsigned char *buffer;
  cairo_surface_t *surface;
  bool blackout = false;
};

struct Label {
  bool visible;
  std::string text;
  uint32_t x;
  uint32_t y;
  uint32_t fontSize;
};

struct Message {
  bool visible;
  uint32_t width;
  widget::IconType icon;
  struct {
    std::string text;
    uint32_t fontSize;
  } brief;
  struct {
    std::string text;
    uint32_t fontSize;
  } detail;
};

struct Screen {
  struct {
    /// \brief A textual description of this screen
    std::string name;
    /// \brief The current ScreenMode
    ScreenMode mode;
    /// \brief The tty device connected to GPS
    std::string gpsDevice;
  } info;

  GvaFunctionEnum currentFunction;
  Canvas canvas;
  FunctionSelect *function_top;
  CommonTaskKeys *control;
  StatusBar *status_bar;
  FunctionKeys function_left;
  FunctionKeys function_right;
  Label label;
  Message message;
  LabelModeEnum labels;
};

class ScreenGva;
//
// These are used by the clock thread to update the time and refresh the screen
//
struct ClockArgs {
  std::string clockString;
  std::string locationFormat;
  std::string locationString;
  ScreenGva *screen;
  int *gps;
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

  ScreenGva &operator=(const ScreenGva &a) = delete;

  ScreenGva(const ScreenGva &Other) = default;

  ///
  /// \brief Destroy the Screen Gva object
  ///
  ///
  ~ScreenGva() final;

  ///
  /// \brief Redraw the screen
  ///
  /// \return GvaStatusTypes Status
  ///
  GvaStatusTypes Update();

  ///
  /// \brief Start the clock thread running to update the clock (pthread started)
  ///
  /// \param barData To be used for updating
  ///
  void StartClock(StatusBar *barData);

  ///
  /// \brief Get the Widget object
  ///
  /// \param widget
  /// \return WidgetX*
  ///
  WidgetX *GetWidget(widget::WidgetEnum widget);

 private:
  char *PosDegrees(float lon, float lat);
  Screen *screen_ = nullptr;
  std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>> widget_list_;
  ClockArgs args_;
  int gps_ = 0;
  uint32_t hndl_;
  Screen last_screen_;
  pthread_t clock_thread_;
  nmeaINFO info_;
  nmeaPARSER parser_;
  ConfigData *config_ = nullptr;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_SCREEN_GVA_H_
