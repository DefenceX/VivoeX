//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file alarm_indicator.h
///
#ifndef HMICORE_WIDGETS_ALARM_INDICATOR_H_
#define HMICORE_WIDGETS_ALARM_INDICATOR_H_

#include <cstdint>
#include <string>

#include "hmicore/gva.h"
#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

///
/// \brief A GVA alarm indicator widget
///
///
class WidgetAlarmIndicator : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Alarm Indicator object
  ///
  /// \param renderer the renderer
  /// \param touch the touch object
  ///
  explicit WidgetAlarmIndicator(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetAlarmIndicator"; };

  ///
  /// \brief
  ///
  ///
  void Draw() final;

  ///
  /// \brief Set the Text object
  ///
  /// \param text
  ///
  void SetText(std::string_view text);

  ///
  /// \brief Set the Type object
  ///
  /// \param type
  ///
  void SetType(const GvaAlarmType type);

 private:
  TouchGva* touch_;
  std::string text_;
  GvaAlarmType type_;
};

}  // namespace gva
#endif  // HMICORE_WIDGETS_ALARM_INDICATOR_H_
