//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file top_labels.cc
///

#include "hmicore/widgets/top_labels.h"

namespace gva {

WidgetTopLabels::WidgetTopLabels(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeCompass), touch_(touch) {}

void WidgetTopLabels::Draw() {
  if (GetVisible()) {
    DrawTopLabels(GetY(), *labels_);
  }
}

void WidgetTopLabels::DrawTopLabels(uint32_t y, const std::array<FunctionSelect::Labels, 8>& labels) {
  uint32_t i = 0;
  hmiScreenSize& hmiScreenSize = hmiScreenSize::getInstance();
  std::tuple<int, int> size = hmiScreenSize.getMinimumSize(); 
  uint32_t offset = std::get<0>(size) * 0.02;
  uint32_t width = (std::get<0>(size) - offset * 2) / 8;
  uint32_t spacing = width * 0.1;

  GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabled());
  GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeLabelBorderThickness(), LineType::kLineSolid);

  for (auto label : labels) {
    if (label.state != LabelStates::kLabelDisabled) {
      SetStateLabel(label.state);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
        GetRenderer()->DrawRoundedRectangle((i * width) + offset, y, width - 10, 10, 4, true);
      } else {
        GetRenderer()->DrawRectangle((i * width) + offset, y, width - 10, 10, true);
      }
      touch_->AddAbsolute(GvaFunctionGroupEnum::kTop, int(GvaKeyEnum::kKeySituationalAwareness) + i,
                          (i * width) + offset, y, (i * width) + width - spacing + offset, y + 10);
    }
    i++;
  }
}

void WidgetTopLabels::SetLabels(std::array<FunctionSelect::Labels, 8>* labels) { labels_ = labels; }

}  // namespace gva
