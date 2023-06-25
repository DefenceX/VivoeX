//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file battery_bar.h
///
#ifndef HMICORE_WIDGETS_DRIVER_BATTERY_BAR_H_
#define HMICORE_WIDGETS_DRIVER_BATTERY_BAR_H_

#include <cstdint>
#include <string>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

/// Class defining the mode widget
class WidgetDriverBatteryBar : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Plan Position Indicator object
  ///
  /// \param renderer
  ///
  explicit WidgetDriverBatteryBar(const RendererGva& renderer);

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetDriverBatteryBar"; };

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///
  void Draw() final;

  ///
  /// \brief Set the Value
  ///
  /// \param value the value to set
  ///
  void SetValue(int16_t value) { value_ = value; }

  ///
  /// \brief Get the Value
  ///
  /// \return int16_t
  ///
  int16_t GetValue() const { return value_; }

 private:
  const double scale_ = 0.5;
  int16_t value_ = 0;
  bool indicator_left_ = false;
  bool indicator_right_ = false;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_DRIVER_BATTERY_BAR_H_
