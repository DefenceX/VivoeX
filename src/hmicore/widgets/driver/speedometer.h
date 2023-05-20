//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file speedometer.h
///
#ifndef HMICORE_WIDGETS_DRIVER_SPEEDOMETER_H_
#define HMICORE_WIDGETS_DRIVER_SPEEDOMETER_H_

#include <cstdint>
#include <string>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

/// Class defining the mode widget
class WidgetDriverSpeedometer : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Plan Position Indicator object
  ///
  /// \param renderer
  ///
  explicit WidgetDriverSpeedometer(const RendererGva& renderer);

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetDriverSpeedometer"; };

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///
  void Draw() final;

  ///
  /// \brief Set the ValueS
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

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(widget::DialType mode) { mode_ = mode; }

 private:
  const double scale_ = 0.5;
  int16_t value_ = 0;
  bool indicator_left_ = false;
  bool indicator_right_ = false;
  widget::DialType mode_ = widget::DialType::kDialSpeedKph;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_DRIVER_SPEEDOMETER_H_
