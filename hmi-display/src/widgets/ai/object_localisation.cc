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

void WidgetObjectLocalisation::AddBoundingBox(int16_t id, const BoxType& box) { boxes_.erase(id); };

void WidgetObjectLocalisation::DeleteBoundingBox(int16_t id) { boxes_.erase(id); };

void WidgetObjectLocalisation::DeleteAllBoundingBox() { boxes_.clear(); };

void WidgetObjectLocalisation::DrawFunctionBoundingBoxes() const {
  // GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeLabelBorderThickness(), LineType::kLineSolid);
  for (auto& [id, box_info] : boxes_) {
    GetRenderer()->SetColourForeground(box_info->rgb_value);
    box_info->dotted ? GetRenderer()->SetLineThickness(3, LineType::kLineDashedMedium)
                     : GetRenderer()->SetLineThickness(3, LineType::kLineSolid);
    GetRenderer()->DrawRoundedRectangle(box_info->xpos, box_info->ypos, box_info->width, box_info->height, 6, false);

    // Draw text the label
    if (box_info->label.length()) {
      GetRenderer()->SetColour(HMI_BLACK);
      GetRenderer()->DrawText(box_info->xpos + 10, box_info->ypos, box_info->label);
    }
  }
};

}  // namespace gva
