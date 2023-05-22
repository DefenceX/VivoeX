//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// \brief Manage the touch screen events
///
/// \file updater.h
///

#ifndef UPDATER_UPDATER_H_
#define UPDATER_UPDATER_H_

#include <map>
#include <memory>
#include <string>
#include <thread>

#include "updater/updater_base.h"

namespace gva {

/// Class defining the updater
class Updater : public UpdaterBase {
 public:
  ///
  /// \brief Construct a new Updater object
  ///
  /// \param id The HMI identity, will only get updates for this ID.
  ///
  explicit Updater(uint64_t id);

  ~Updater();

  ///
  /// \brief Register the widgets to be updated
  ///
  ///
  void RegisterWidgets(std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>>& widget_list);  // NOLINT

  ///
  /// \brief Update the HMI state
  ///
  /// \param state The new state
  ///
  void UpdateState(std::string state) final;

  ///
  /// \brief Process at HMI event
  ///
  /// \param event
  ///
  void Event(std::string event) final;

  ///
  /// \brief The updater thread
  ///
  /// \param widget_list The widgets list pointer
  /// \return void*
  ///
  static void WidgetUpdaterThread(std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>>* widget_list);

  ///
  /// \brief Set to false to terminate thread
  ///
  ///
  static bool running_;

 private:
  std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>>* widget_list_ = nullptr;
  std::thread thread_;

  ///
  /// \brief Generate a sine wave
  ///
  /// \param sample The sample being requested
  /// \param sampleRate i.e. 44100.0
  /// \param frequency i.e. 440.0;
  /// \return int The sample value. amplitude is 0-100
  ///
  static uint16_t GenerateSineWave(int sample, double sampleRate = 44100, double frequency = 440.0);
};

}  // namespace gva

#endif  //  UPDATER_UPDATER_H_
