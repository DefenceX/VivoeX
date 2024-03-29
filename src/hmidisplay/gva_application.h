//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file gva_application.h
///

#ifndef HMIDISPLAY_GVA_APPLICATION_H_
#define HMIDISPLAY_GVA_APPLICATION_H_
#include <gtk/gtk.h>
#include <raw/rtpvraw_depayloader.h>
#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>

#include "hmicore/events_gva.h"
#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/renderer_map.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/keyboard.h"
#include "hmicore/widgets/plan_position_indicator.h"
#include "hmidisplay/gva_application_types.h"

/// Class definition of the GvaApplication
class GvaApplication {
 public:
  /// Application options
  struct Options {
    /// Video enabled flag (default false)
    bool videoEnabled_ = false;
    /// Window enabled flag (default false)
    bool windowEnabled_ = false;
    /// The config file location
    std::string config;
  };

  ///
  /// \brief Construct a new Gva Application object
  ///
  /// \param options The application options
  /// \param ipaddr The stream IP address for raw RTP video
  /// \param port The port for the above RTP stream
  ///
  GvaApplication(const Options &options, const std::string &ipaddr, const uint32_t port);

  ///
  /// \brief Destroy the Gva Application object
  ///
  ///
  ~GvaApplication() = default;

  ///
  /// \brief Execute the main processing loop, blocking call
  ///
  ///
  void Exec() const;

  ///
  /// \brief Create the Key Pressed event
  ///
  /// \param key The key being pressed
  ///
  static bool SetKeyPressed(gva::GvaKeyEnum key);

  ///
  /// \brief Create the Key Released event
  ///
  /// \param renderer The renderer
  /// \param key The key being released
  ///
  static bool SetKeyReleased(gva::HandleType *renderer, gva::GvaKeyEnum key);

  ///
  /// \brief Update the GTK application
  ///
  /// \param user_data Pointer to data object
  ///
  static void Update(gpointer user_data);

  /// GTK application options
  static Options options_;
  /// The GTK application
  static gtkType gtk_;

 private:
  ///
  /// \brief Adjust Brightness up by 5%
  ///
  ///
  static void BrightnessUp();

  ///
  /// \brief Adjust Brightness down by 5%
  ///
  ///
  static void BrightnessDown();

  ///
  /// \brief Adjust Brightness by given value
  ///
  /// \param value
  ///
  static void BrightnessAdjust(double value);

  ///
  /// \brief Process the top bezel keys (only).
  ///
  /// \param key
  /// \return true Top key was detected
  /// \return false Was not a top bezel key still needs to be processed
  ///
  static bool ProcessTopKeys(gva::HandleType *render, gva::GvaKeyEnum key);

  ///
  /// \brief Process the function bezel keys (only).
  ///
  /// \param keyboard
  /// \param key
  /// \return true Function key was detected
  /// \return false Was not a function bezel key still needs to be processed
  ///
  static bool ProcessFunctionKeys(gva::WidgetKeyboard *keyboard, gva::GvaKeyEnum key);

  ///
  /// \brief Toggle the GTK application to and from fullscreen
  ///
  /// \param render
  ///
  static void Fullscreen(gva::HandleType *render);

  ///
  /// \brief Dispatch key presses
  ///
  ///
  static void Dispatch(gva::GvaKeyEnum key);

  /// Event data input/output
  static std::shared_ptr<gva::EventsGva> io_;
  ///  Flag indicating first execution of callbacks
  static bool first_execution_;

  ///
  /// \brief GTK3 redraw callback
  ///
  /// \param Widget The widget to draw
  /// \param cr The cairo context
  /// \param data Pointer to data object
  /// \return gboolean
  ///
  static gboolean DrawCb(GtkWidget *Widget, cairo_t *cr, gpointer data);

  ///
  /// \brief GTK3 configure event callback
  ///
  /// \param Widget The widget to draw
  /// \param event The event
  /// \param data Pointer to data object
  /// \return gboolean
  ///
  static gboolean ConfigureEventCb(GtkWidget *Widget, GdkEventConfigure *event, gpointer data);

  ///
  /// \brief GTK3 activate callback
  ///
  /// \param app The GTK application
  /// \param user_data Pointer to data object
  ///
  static void Activate(GtkApplication *app, gpointer user_data);

  ///
  /// \brief Timer callback
  ///
  /// \param user_data Pointer to data object
  /// \return gboolean
  ///
  static gboolean Callback(gpointer user_data);

  ///
  /// \brief Free the rendered canvas
  ///
  ///
  static void CloseWindow(void);
};

#endif  // HMIDISPLAY_GVA_APPLICATION_H_
