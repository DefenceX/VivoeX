//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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
  /// \param renderer The underlying renderer, should be cairo
  /// \param touch The touch object
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
  /// The GVA warnings counter
  uint16_t warnings_ = 0;
  /// The GVA cautions counter
  uint16_t cautions_ = 0;
  /// The GVA advisories counter
  uint16_t advisories_ = 0;
  /// The GVA overrides counter
  uint16_t overrides_ = 0;

  /// The vehicle location
  LocationType location_;

  ///
  /// \brief The labels for the status bar
  ///
  ///
  struct Labels {
    /// The label state
    LabelStates state;
    /// The label text
    std::string text;
  };
  /// The labels for the status bar
  std::array<Labels, 7> labels_;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_STATUS_BAR_H_
