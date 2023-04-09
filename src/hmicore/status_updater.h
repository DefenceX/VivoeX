//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
/// \file status_updater.h
///

#ifndef HMICORE_STATUS_UPDATER_H_
#define HMICORE_STATUS_UPDATER_H_
#include <memory>

#include "hmicore/screen_gva.h"
#include "hmicore/widgets/table/status_bar.h"

namespace gva {
class StatusUpdater {
 public:
  StatusUpdater() = default;
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
  /// \param gpsFd the GPS file descriptor
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
  static const int kMaxNmea = 1000;
};
}  // namespace gva

#endif  // HMICORE_STATUS_UPDATER_H_
