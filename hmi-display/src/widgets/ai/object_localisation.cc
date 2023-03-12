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
/// \file object_localisation.cc
///

#include "src/widgets/ai/object_localisation.h"

namespace gva {

WidgetObjectLocalisation::WidgetObjectLocalisation(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetObjectLocalisation), touch_(touch) {}

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
    box_info->dotted ? GetRenderer()->SetLineThickness(3, LineType::kLineDashedMedium)
                     : GetRenderer()->SetLineThickness(3, LineType::kLineSolid);
    GetRenderer()->DrawRoundedRectangle(box_info->xpos, box_info->ypos, box_info->width, box_info->height, 10, false);

    touch_->Add(gva::GvaFunctionGroupEnum::kObjectBoxes, (uint32_t)IdToKey(id), box_info->xpos, box_info->ypos,
                box_info->width, box_info->height);

    // Draw text the label
    if (box_info->label.length() == 0) {
      box_info->label = "Unknown";
    }
    GetRenderer()->SetLineThickness(3, LineType::kLineSolid);
    GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_WEIGHT_NORMAL, widget::WeightType::kWeightNormal,
                               gva::ConfigData::GetInstance()->GetThemeFont(), 8);
    uint32_t text_width = GetRenderer()->GetTextWidth(box_info->label, 8);
    GetRenderer()->DrawRoundedRectangle(box_info->xpos + 10, box_info->ypos - 8, 13 + text_width, 15, 5, true);
    GetRenderer()->DrawColor(HMI_BLACK);
    GetRenderer()->DrawText(box_info->xpos + 15, box_info->ypos + 2, box_info->label);
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
