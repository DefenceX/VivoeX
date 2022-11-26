///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief The top of the screen labels widget
///
/// \file top_labels.cc
///

#include "src/widgets/top_labels.h"

#include "src/screen_gva.h"

namespace gva {

WidgetTopLabels::WidgetTopLabels(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, KWidgetTypeCompass), touch_(touch) {}

void WidgetTopLabels::Draw() {
  if (GetVisible()) {
    DrawTopLabels(GetY(), *labels_);
  }
}

void WidgetTopLabels::DrawTopLabels(uint32_t y, const std::array<FunctionSelect::Labels, 8>& labels) {
  uint32_t i = 0;
  uint32_t offset = DEFAULT_WIDTH * 0.02;
  uint32_t width = (DEFAULT_WIDTH - offset * 2) / 8;
  uint32_t spacing = width * 0.1;

  GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabled());
  GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeLabelBorderThickness(), LineType::kLineSolid);

  for (auto label : labels) {
    if (label.state != LabelStates::kLabelDisabled) {
      SetStateLabel(label.state);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
        GetRenderer()->DrawRoundedRectangle((i * width) + offset, y, width - 10, 10, 4, true);
      } else {
        GetRenderer()->DrawRectangle((i * width) + offset, y, width - 10, 10, true);
      }
      touch_->AddAbsolute(GvaFunctionGroupEnum::kTop, int(GvaKeyEnum::KKeySituationalAwareness) + i,
                          (i * width) + offset, y, (i * width) + width - spacing + offset, y + 10);
    }
    i++;
  }
}

void WidgetTopLabels::SetLabels(std::array<FunctionSelect::Labels, 8>* labels) { labels_ = labels; }

void WidgetTopLabels::SetStateLabel(LabelStates state) {
  ConfigData* config = ConfigData::GetInstance();
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do let just return
      break;
    case LabelStates::kLabelDisabled:
      GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderDisabled());
      GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundDisabled());
      GetRenderer()->SetLineThickness(config->GetThemeLabelBorderThickness(), config->GetThemeLabelLineDisabled());
      break;
    case LabelStates::kLabelEnabled:
      GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabled());
      GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
      GetRenderer()->SetLineThickness(config->GetThemeLabelBorderThickness(), config->GetThemeLabelLineEnabled());
      break;
    case LabelStates::kLabelEnabledSelected:
      GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabledSelected());
      GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabledSelected());
      GetRenderer()->SetLineThickness(config->GetThemeLabelBorderThickness(),
                                      config->GetThemeLabelLineEnabledSelected());
      break;
    case LabelStates::kLabelEnabledSelectedChanging:
      GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabledSelectedChanging());
      GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabledSelectedChanging());
      GetRenderer()->SetLineThickness(config->GetThemeLabelBorderThickness(),
                                      config->GetThemeLabelLineEnabledSelectedChanging());
      break;
  }
}

}  // namespace gva
