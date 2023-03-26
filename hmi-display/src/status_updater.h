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

#ifndef HMI_DISPLAY_SRC_STATUS_UPDATER_H_
#define HMI_DISPLAY_SRC_STATUS_UPDATER_H_
#include <memory>

#include "src/screen_gva.h"
#include "src/widgets/table/status_bar.h"

namespace gva {
class StatusUpdater {
 public:
  StatusUpdater() = default;
  ~StatusUpdater() = default;

  void ClockUpdate(ClockArgs *args);
  void GetLocalTime(std::tm &localTime);
  void UpdateClock(std::shared_ptr<WidgetStatusBar> statusBar);
  void ParseGpsData(const int *gpsFd, nmeaINFO *info, nmeaPARSER *parser, const LocationType &location);
  void UpdateLocation(std::shared_ptr<WidgetStatusBar> statusBar, const nmeaINFO &info, const LocationType &location);

 private:
  static const int kMaxNmea = 1000;
};
}  // namespace gva

#endif  // HMI_DISPLAY_SRC_STATUS_UPDATER_H_