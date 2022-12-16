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
/// \file alarm_indicator.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_ALARM_INDICATOR_H_
#define HMI_DISPLAY_SRC_WIDGETS_ALARM_INDICATOR_H_

#include <cstdint>
#include <string>

#include "src/gva.h"
#include "src/renderer_cairo_types.h"
#include "src/widgets/widget.h"

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
  /// \param renderer
  ///
  explicit WidgetAlarmIndicator(const RendererGva& renderer, TouchGva* touch);

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
  void SetText(const std::string& text);

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
#endif  // HMI_DISPLAY_SRC_WIDGETS_ALARM_INDICATOR_H_
