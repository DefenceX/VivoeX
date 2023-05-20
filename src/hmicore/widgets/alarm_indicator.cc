//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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
        GetRenderer()->SetColourBackground(kHmiRed);
        break;
      case GvaAlarmType::kAlarmWarnings:
        GetRenderer()->SetColourBackground(kHmiAmber);
        break;
    }
    GetRenderer()->SetColourForeground(kHmiWhite);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRoundedRectangle(110, 429, 420, 20, 6, true);
    GetRenderer()->DrawColor(kHmiWhite);
    uint32_t width = GetRenderer()->GetTextWidth(text_, 14);
    GetRenderer()->DrawText(110 + (420 / 2) - (width / 2), 444, text_);
    GetRenderer()->SetColourForeground(kHmiWhite);
    GetRenderer()->DrawColor(kHmiWhite);

    touch_->Add(GvaFunctionGroupEnum::kAlarmsIndicator, (uint32_t)(GvaKeyEnum::kKeyF16), 110, 32, 420, 20);
  }
}

void WidgetAlarmIndicator::SetText(std::string_view text) { text_ = text; }

void WidgetAlarmIndicator::SetType(const GvaAlarmType type) { type_ = type; }

}  // namespace gva