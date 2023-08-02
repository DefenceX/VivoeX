//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file mode.cc
///

#include "hmicore/widgets/mode.h"

namespace gva {

WidgetMode::WidgetMode(const RendererGva& renderer) : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeMode) {
  SetVisible(false);
}

void WidgetMode::Draw() {
  hmiScreenSize& hmiScreenSize = hmiScreenSize::getInstance();
  std::tuple<int, int> size = hmiScreenSize.getMinimumSize(); 
  
  uint32_t y = std::get<1>(size) - (std::get<1>(size) * 0.12);

  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetColourBackground(kHmiDarkBlue);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), 12);

  uint32_t w = GetRenderer()->GetTextWidth(mode_, 12);
  uint32_t h = GetRenderer()->GetTextHeight(mode_, 12);

  GetRenderer()->DrawRoundedRectangle(std::get<0>(size) / 2 - (w / 2) - 5, y, w + 10, (h) + 15, 6, true);
  GetRenderer()->DrawString(std::get<0>(size) / 2 - (w / 2), y + 16, mode_);
}

void WidgetMode::SetMode(const std::string mode) { mode_ = mode; }

std::string WidgetMode::GetMode() const { return mode_; }

}  // namespace gva
