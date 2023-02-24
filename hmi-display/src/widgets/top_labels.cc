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
/// \file top_labels.cc
///

#include "src/widgets/top_labels.h"

#include "src/screen_gva.h"

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
  uint32_t offset = kMinimumWidth * 0.02;
  uint32_t width = (kMinimumWidth - offset * 2) / 8;
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
