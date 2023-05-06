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
///
/// \file status_bar.h
///

#ifndef HMICORE_WIDGETS_TABLE_STATUS_BAR_H_
#define HMICORE_WIDGETS_TABLE_STATUS_BAR_H_

#include <stdint.h>

#include <string>

#include "hmicore/widgets/table/table.h"
#include "hmicore/widgets/widget.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

///
/// \brief A widget representing a table of elements
///
///
class WidgetStatusBar : public WidgetTable {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
  ///
  explicit WidgetStatusBar(const RendererGva &renderer, TouchGva *touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetStatusBar() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetStatusBar"; }

  ///
  /// \brief The base class override to draw the table once setup
  ///
  ///
  void Draw() override;

  ///
  /// \brief Update the system clock
  ///
  /// \param clock_string as text
  ///
  void UpdateClock(std::string_view clock_string);

  ///
  /// \brief  Update the location
  ///
  /// \param location as text
  ///
  void UpdateLocation(std::string_view location);

  ///
  /// \brief Set the location format i.e MGRS or Lat/Long
  ///
  /// \param location_format text representation
  ///
  void UpdateLocationFormat(std::string_view location_format);

 private:
  uint16_t warnings_ = 0;
  uint16_t cautions_ = 0;
  uint16_t advisories_ = 0;
  uint16_t overrides_ = 0;

  LocationType location_;
  struct Labels {
    LabelStates state;
    std::string text;
  };
  std::array<Labels, 7> labels_;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_STATUS_BAR_H_
