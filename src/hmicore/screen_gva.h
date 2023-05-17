//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// The screen manger for the GVA application
///
/// \file screen_gva.h
///

#ifndef HMICORE_SCREEN_GVA_H_
#define HMICORE_SCREEN_GVA_H_
#include <cairo.h>
#include <pthread.h>

#include <map>
#include <memory>
#include <string>

#include "hmicore/gva.h"
#include "hmicore/renderer_gva.h"
#include "nmea/nmea.h"
#include "updater/updater.h"
#include "widgets/table/table.h"
#include "widgets/widget.h"
#include "widgets/widget_types.h"
#include "widgets/widgets.h"

namespace gva {

struct Canvas {
  /// flag indicating if the canvas is visible
  bool visible;
  /// A pointer to the buffer
  unsigned char *buffer;
  /// The cairo surface
  cairo_surface_t *surface;
  /// Set if in blackout mode
  bool blackout = false;
};

struct Label {
  /// Label is visible
  bool visible;
  /// Label text
  std::string text;
  /// The label X position in pixels
  uint32_t x;
  /// The label Y position in pixels
  uint32_t y;
  /// The label font size
  uint32_t fontSize;
};

struct Message {
  /// Message is visible
  bool visible;
  /// The message X position in pixels
  uint32_t width;
  /// The icon to display instead of text
  widget::IconType icon;
  struct {
    /// The label text
    std::string text;
    /// The label font size
    uint32_t fontSize;
  } brief;

  struct {
    /// The message text
    std::string text;
    /// The font size
    uint32_t fontSize;
  } detail;
};

struct Screen {
  struct {
    /// A textual description of this screen
    std::string name;
    /// The current ScreenMode
    ScreenMode mode;
    /// The tty device connected to GPS
    std::string gpsDevice;
  } info;

  GvaFunctionEnum currentFunction;
  Canvas canvas;
  FunctionSelect *function_top;
  CommonTaskKeys *control;
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
  /// Clock string
  std::string clock_string;
  /// Location string format
  std::string location_format;
  /// Location string
  std::string location_string;
  /// The screen to update
  ScreenGva *screen;
  /// GPS handle
  int *gps;
  /// NMEA info
  nmeaINFO *info;
  /// NMEA parser
  nmeaPARSER *parser;
  /// true if active
  bool active;
  /// The status bar widget
  std::shared_ptr<WidgetStatusBar> status_bar;
  /// The location type
  LocationType location;
};

class ScreenGva : public RendererGva {
 public:
  ///
  /// Construct a new Screen Gva object
  ///
  /// \param screen
  /// \param width
  /// \param height
  ///
  ScreenGva(Screen *screen, uint32_t width, uint32_t height);

  ///
  /// \brief Construct a new Screen Gva object
  ///
  /// \param a The argument to copy
  /// \return ScreenGva&
  ///
  ScreenGva &operator=(const ScreenGva &a) = delete;

  ///
  /// \brief Construct a new Screen Gva object
  ///
  /// \param Other  The object to copy
  ///
  ScreenGva(const ScreenGva &Other) = default;

  ///
  /// Destroy the Screen Gva object
  ///
  ///
  ~ScreenGva() final;

  ///
  /// Redraw the screen
  ///
  /// \return GvaStatusTypes Status
  ///
  GvaStatusTypes Update();

  ///
  /// Start the clock thread running to update the clock (pthread started)
  ///
  /// \param barData To be used for updating
  ///
  void StartClock(std::shared_ptr<WidgetX> status_bar_widget);

  ///
  /// Reset the all the widgets to not be visible
  ///
  /// \return WidgetX*
  ///
  void ResetWidgets() const;

  ///
  /// Get the Widget object
  ///
  /// \param widget
  /// \return WidgetX*
  ///
  WidgetX *GetWidget(widget::WidgetEnum widget);

  ///
  /// The thread that reads and updates the clock and status bar info
  ///
  /// \param arg status bar arguments
  /// \return void*
  ///
  static void ClockUpdateThread(ClockArgs *arg);

  ///
  /// \brief The arguments for the clock thread
  ///
  ///
  static ClockArgs args_;

 private:
  ///
  /// \brief The Position in object
  ///
  /// \param lon The position longitude
  /// \param lat The position latitude
  /// \return char*
  ///
  char *PosDegrees(float lon, float lat);

  /// Pointer to the screen
  Screen *screen_ = nullptr;
  /// The widget list
  std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>> widget_list_;
  /// The GPS device handle
  int gps_ = 0;
  /// The serial port handle
  uint32_t handle_;
  /// The last screen
  Screen last_screen_;
  /// The clock update thread
  std::thread clock_thread_;
  /// The GPS information
  nmeaINFO info_;
  /// The GPS parser
  nmeaPARSER parser_;
  /// The pointer to the configuation data
  ConfigData *config_ = nullptr;
  /// The updater for the HMI
  Updater updater_ = Updater(0);
};

}  // namespace gva

#endif  // HMICORE_SCREEN_GVA_H_
