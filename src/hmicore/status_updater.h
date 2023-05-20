//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// \brief The screen manger for the GVA application
///
/// \file status_updater.h
///

#ifndef HMICORE_STATUS_UPDATER_H_
#define HMICORE_STATUS_UPDATER_H_
#include <memory>

#include "hmicore/screen_gva.h"
#include "hmicore/widgets/table/status_bar.h"

namespace gva {

/// Class defining the status updater
class StatusUpdater {
 public:
  ///
  /// \brief Construct a new Status Updater object
  ///
  ///
  StatusUpdater() = default;

  ///
  /// \brief Destroy the Status Updater object
  ///
  ///
  ~StatusUpdater() = default;

  ///
  /// \brief Update the clock
  ///
  /// \param args the arguments that need to be updated
  ///
  void ClockUpdate(ClockArgs *args);

  ///
  /// \brief Get the Local Time attribute
  ///
  /// \param localTime (out) the structure containing the time
  ///
  void GetLocalTime(std::tm *localTime) const;

  ///
  /// \brief Update the clock and the rest of the status bar settings
  ///
  /// \param statusBar the stsus bar being updated
  ///
  void UpdateClock(std::shared_ptr<WidgetStatusBar> statusBar) const;

  ///
  /// \brief Parse the GPS data
  ///
  /// \param gps_file_descriptor the GPS file descriptor
  /// \param info the NMEA information
  /// \param parser the current NMEA parser
  /// \param location the location presentation type
  ///
  void ParseGpsData(const int *gps_file_descriptor, nmeaINFO *info, nmeaPARSER *parser,
                    const LocationType &location) const;

  ///
  /// \brief Update the location
  ///
  /// \param statusBar the information being updated
  /// \param info new NMEA information
  /// \param location the location presentation type
  ///
  void UpdateLocation(std::shared_ptr<WidgetStatusBar> statusBar, const nmeaINFO &info,
                      const LocationType &location) const;

 private:
  /// The maximum number of NMEA sentences
  static const int kMaxNmea = 1000;
};
}  // namespace gva

#endif  // HMICORE_STATUS_UPDATER_H_
