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
///
/// \file gva_application.h
///

#ifndef HMI_DISPLAY_SRC_GVA_APPLICATION_H_
#define HMI_DISPLAY_SRC_GVA_APPLICATION_H_
#include <unistd.h>

#include <iostream>
#include <memory>
#include <string>

#include "common/log_gva.h"
#include "rtp_stream.h"  // NOLINT
#include "src/events_gva.h"
#include "src/gva.h"
#include "src/hmi_gva.h"
#include "src/renderer_map.h"
#include "video/src/gva_video_rtp_yuv.h"
#include "widgets/alarm_indicator.h"
#include "widgets/compass.h"
#include "widgets/keyboard.h"

class GvaApplication {
 public:
  /// \brief Application options
  struct Options {
    bool videoEnabled_ = false;
    bool windowEnabled_ = false;
    std::string config;
  };

  ///
  /// \brief Construct a new Gva Application object
  ///
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
  /// \param key
  ///
  static bool SetKeyPressed(gva::GvaKeyEnum key);

  ///
  /// \brief Create the Key Released event
  ///
  /// \param key
  ///
  static bool SetKeyReleased(gva::HandleType *, gva::GvaKeyEnum key);

  ///
  /// \brief Update the canvas and re-render the screen
  ///
  /// \param arg
  /// \param user_data
  ///
  static void Update(void *arg, gpointer user_data);

  static Options options_;
  static std::unique_ptr<gva::GvaVideoRtpYuv> rtp_stream1_;

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

  std::shared_ptr<gva::EventsGva> io_;
  gva::EventsGva *io_test_ = nullptr;
  static uint32_t update_counter_;
  static bool first_execution_;
};

#endif  // HMI_DISPLAY_SRC_GVA_APPLICATION_H_
