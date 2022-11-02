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

#ifndef SCREEN_GVA_H
#define SCREEN_GVA_H
#include <pthread.h>

#include "cairo.h"
#include "gva.h"
#include "log_gva.h"
#include "nmea/nmea.h"
#include "renderer_gva.h"
#include "widgets/table.h"
#include "widgets/widget.h"

namespace gva {
class ScreenGva;

enum LocationEnum { LOCATION_FORMAT_LONG_LAT = 0, LOCATION_FORMAT_MGRS };

enum ScreenMode { MODE_MAINTINENCE = 0, MODE_OPERATIONAL, MODE_BLACKOUT };

enum LabelModeEnum { LABEL_ALL, LABEL_STATUS_ONLY, LABEL_MINIMAL };

typedef struct FunctionSelect {
  bool visible;
  int active;
  int hidden;
} FunctionSelectType;

typedef struct FunctionKeys {
  bool visible;
  int active;
  int hidden;
  int toggleActive;
  int toggleOn;
  char labels[6][40];
} FunctionKeysType;

typedef struct CommonTaskKeys {
  bool visible;
  int active;
  int hidden;
  char labels[8][40];
} CommonTaskKeysType;

typedef struct {
  LocationEnum locationFormat;
  float lat;
  float lon;
} LocationType;

typedef struct StatusBar {
  bool visible;
  int x;
  int y;
  LocationType location;
  char labels[7][80];
} StatusBarType;

enum SurfaceType { SURFACE_NONE = 0, SURFACE_FILE, SURFACE_BUFFER_RGB24, SURFACE_CAIRO, SURFACE_BLACKOUT };

typedef struct Canvas {
  bool visible;
  SurfaceType bufferType;
  char filename[256];
  char *buffer;
  cairo_surface_t *surface;
} CanvasType;

typedef struct Label {
  bool visible;
  char text[256];
  int x;
  int y;
  int fontSize;
} LabelType;

typedef struct Message {
  bool visible;
  int width;
  IconType icon;
  struct {
    char text[256];
    int fontSize;
  } brief;
  struct {
    char text[4096];
    int fontSize;
  } detail;
} MessaGetYpe;

typedef struct Screen {
  struct {
    char name[100];
    ScreenMode mode;
    char gpsDevice[100];
  } info;
  GvaFunctionEnum currentFunction;
  CanvasType canvas;
  FunctionSelectType *function_top;
  CommonTaskKeysType *control;
  StatusBarType *status_bar;
  FunctionKeysType function_left;
  FunctionKeysType function_right;
  TableWidget table;
  LabelType label;
  MessaGetYpe message;
  LabelModeEnum labels;
} ScreenType;

//
// These are used by the clock thread to update the time and refresh the screen
//
typedef struct ArgStruct {
  char *clockString;
  char *locationFormat;
  char *locationString;
  ScreenGva *screen;
  int *gps;
  nmeaINFO *info;
  nmeaPARSER *parser;
  bool active;
  LocationType *location;
} args;

class ScreenGva : public RendererGva {
 public:
  ///
  /// \brief Construct a new Screen Gva object
  ///
  /// \param screen
  /// \param width
  /// \param height
  ///
  ScreenGva(ScreenType *screen, int width, int height);

  ///
  /// \brief Destroy the Screen Gva object
  ///
  ///
  ~ScreenGva();

  ///
  /// \brief Redraw the screen
  ///
  /// \return int
  ///
  int Update();

  ///
  /// \brief Start the clock thread running to update the clock (pthread started)
  ///
  /// \param barData
  ///
  void StartClock(StatusBarType *barData);

  ///
  /// \brief Get the Widget object
  ///
  /// \param widget
  /// \return WidgetX*
  ///
  WidgetX *GetWidget(WidgetEnum widget);

 private:
  char *PosDegrees(float lon, float lat);
  ScreenType *screen_;
  std::vector<WidgetX *> widget_list_;
  args *args_;
  int gps_;
  int hndl_;
  ScreenType last_screen_;
  pthread_t clock_thread_;
  nmeaINFO info_;
  nmeaPARSER parser_;
  gva::ConfigData *config_;
};
}  // namespace gva
#endif
