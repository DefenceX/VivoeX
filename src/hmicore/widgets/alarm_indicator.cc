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
/// \file alarms_indicator.cc
///

#include "alarm_indicator.h"

namespace gva {

WidgetAlarmIndicator::WidgetAlarmIndicator(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeAlarmIndicator), touch_(touch) {}

void WidgetAlarmIndicator::Draw() {
  if (GetVisible()) {
    GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                               gva::ConfigData::GetInstance()->GetThemeFont(), 14);
    switch (type_) {
      case GvaAlarmType::kAlarmAdvisory:
        GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
        break;
      case GvaAlarmType::kAlarmCaution:
        GetRenderer()->SetColourBackground(HMI_RED);
        break;
      case GvaAlarmType::kAlarmWarnings:
        GetRenderer()->SetColourBackground(HMI_AMBER);
        break;
    }
    GetRenderer()->SetColourForeground(HMI_WHITE);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRoundedRectangle(110, 429, 420, 20, 6, true);
    GetRenderer()->DrawColor(HMI_WHITE);
    uint32_t width = GetRenderer()->GetTextWidth(text_, 14);
    GetRenderer()->DrawText(110 + (420 / 2) - (width / 2), 444, text_);
    GetRenderer()->SetColourForeground(HMI_WHITE);
    GetRenderer()->DrawColor(HMI_WHITE);

    touch_->Add(GvaFunctionGroupEnum::kAlarmsIndicator, (uint32_t)(GvaKeyEnum::kKeyF16), 110, 32, 420, 20);
  }
}

void WidgetAlarmIndicator::SetText(std::string_view text) { text_ = text; }

void WidgetAlarmIndicator::SetType(const GvaAlarmType type) { type_ = type; }

}  // namespace gva