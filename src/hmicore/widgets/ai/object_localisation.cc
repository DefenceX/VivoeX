//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file object_localisation.cc
///

#include "hmicore/widgets/ai/object_localisation.h"

namespace gva {

WidgetObjectLocalisation::WidgetObjectLocalisation(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeObjectLocalisation), touch_(touch) {}

void WidgetObjectLocalisation::Draw() {
  if (GetVisible()) {
    DrawFunctionBoundingBoxes();
  }
}

void WidgetObjectLocalisation::AddBoundingBox(int16_t id, const BoxType& box) {
  boxes_[id] = std::make_shared<BoxType>(box);
};

void WidgetObjectLocalisation::DeleteBoundingBox(int16_t id) { boxes_.erase(id); };

void WidgetObjectLocalisation::DeleteAllBoundingBox() { boxes_.clear(); };

void WidgetObjectLocalisation::DrawFunctionBoundingBoxes() const {
  for (auto& [id, box_info] : boxes_) {
    GetRenderer()->SetColourBackground(box_info->rgb_value);
    GetRenderer()->SetColourForeground(box_info->rgb_value);
    box_info->dotted ? GetRenderer()->SetLineThickness(1, LineType::kLineDashedMedium)
                     : GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRoundedRectangle(box_info->xpos, box_info->ypos, box_info->width, box_info->height, 10, false);

    touch_->Add(gva::GvaFunctionGroupEnum::kObjectBoxes, (uint32_t)IdToKey(id), box_info->xpos, box_info->ypos,
                box_info->width, box_info->height);

    // Draw text the label
    if (box_info->label.length() == 0) {
      box_info->label = "Unknown";
    }
    GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
    GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_WEIGHT_NORMAL, widget::WeightType::kWeightNormal,
                               gva::ConfigData::GetInstance()->GetThemeFont(), 8);
    uint32_t text_width = GetRenderer()->GetTextWidth(box_info->label, 8);
    GetRenderer()->DrawRoundedRectangle(box_info->xpos + 10, box_info->ypos - 5, 6 + text_width, 8, 5, true);
    GetRenderer()->DrawColor(kHmiBlack);
    GetRenderer()->DrawString(box_info->xpos + 13, box_info->ypos + 2, box_info->label);
  }
};

GvaKeyEnum WidgetObjectLocalisation::IdToKey(uint16_t id) const {
  switch (id) {
    case 0:
      return GvaKeyEnum::kKeyKeyboard_0;
    case 1:
      return GvaKeyEnum::kKeyKeyboard_1;
    case 2:
      return GvaKeyEnum::kKeyKeyboard_2;
    case 3:
      return GvaKeyEnum::kKeyKeyboard_3;
    case 4:
      return GvaKeyEnum::kKeyKeyboard_4;
    case 5:
      return GvaKeyEnum::kKeyKeyboard_5;
    case 6:
      return GvaKeyEnum::kKeyKeyboard_6;
    case 7:
      return GvaKeyEnum::kKeyKeyboard_7;
    case 8:
      return GvaKeyEnum::kKeyKeyboard_8;
    case 9:
      return GvaKeyEnum::kKeyKeyboard_9;
    default:
      break;
  }
  return GvaKeyEnum::kKeyUnknown;
}

}  // namespace gva
