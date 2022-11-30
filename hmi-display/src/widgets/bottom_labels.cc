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
/// \brief The bottom of the screen labels widget
///
/// \file bottom_labels.cc
///

#include "src/widgets/bottom_labels.h"

#include <array>

#include "src/gva.h"
#include "src/screen_gva.h"

namespace gva {

WidgetBottomLabels::WidgetBottomLabels(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::KWidgetTypeCompass), touch_(touch) {
  config_ = ConfigData::GetInstance();
}

void WidgetBottomLabels::Draw() {
  if (GetVisible()) {
    DrawControlLabels();
  }
}

void WidgetBottomLabels::DrawControlLabels() {
  uint32_t i = 0;
  uint32_t offset = 20;
  uint32_t w = 75;

  std::array<std::string, 8> labels = {"Up", "Alarms", "Threats", "Ack", "", "", "Labels", "Enter"};

  GetRenderer()->SetColourForeground(config_->GetThemeLabelBorderEnabled());
  GetRenderer()->SetColourBackground(config_->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             config_->GetThemeFont());

  for (auto label : *labels_) {
    if (label.state_ != LabelStates::kLabelHidden) {
      SetStateLabel(label.state_);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
        GetRenderer()->DrawRoundedRectangle((i * w) + offset, GetY(), w - 5, 20, 4, true);
      } else {
        GetRenderer()->DrawRectangle((i * w) + offset, GetY(), w - 5, 20, true);
      }
      SetStateText(label.state_);

      if (label.state_ != LabelStates::kLabelDisabled) {
        touch_->AddAbsolute(GvaFunctionGroupEnum::kBottom, int(GvaKeyEnum::kKeyF13) + i, (i * w) + offset, GetY(),
                            (i * w) + w - 5 + offset, GetY() + 20);
      }
      GetRenderer()->DrawText((i * w) + offset + 5, GetY() + 6, label.text_.c_str());
      if (i == 4) GetRenderer()->DrawIcon(widget::IconType::kIconUpArrow, (i * w) + offset + 34, GetY() + 11, 15, 8);
      if (i == 5) GetRenderer()->DrawIcon(widget::IconType::kIconDownArrow, (i * w) + offset + 34, GetY() + 10, 15, 8);
    }

    i++;
  }
}

void WidgetBottomLabels::SetStateText(LabelStates state) {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do let just return
      break;
    case LabelStates::kLabelDisabled:
      GetRenderer()->DrawColor(config_->GetThemeLabelTextDisabled());
      break;
    case LabelStates::kLabelEnabled:
      GetRenderer()->DrawColor(config_->GetThemeLabelTextEnabled());
      break;
    case LabelStates::kLabelEnabledSelected:
      GetRenderer()->DrawColor(config_->GetThemeLabelTextEnabledSelected());
      break;
    case LabelStates::kLabelEnabledSelectedChanging:
      GetRenderer()->DrawColor(config_->GetThemeLabelTextEnabledSelectedChanging());
      break;
  }
}

void WidgetBottomLabels::SetLabels(std::array<CommonTaskKeys::Labels, 8>* labels) { labels_ = labels; };

void WidgetBottomLabels::SetStateLabel(const LabelStates state) {
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
};

uint32_t WidgetBottomLabels::GetStateTextColour(LabelStates state) const {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do but return hidden if requested
      return config_->GetThemeLabelTextDisabled();
    case LabelStates::kLabelDisabled:
      return config_->GetThemeLabelTextDisabled();
    case LabelStates::kLabelEnabled:
      return config_->GetThemeLabelTextEnabled();
    case LabelStates::kLabelEnabledSelected:
      return config_->GetThemeLabelTextEnabledSelected();
    case LabelStates::kLabelEnabledSelectedChanging:
      return config_->GetThemeLabelTextEnabledSelectedChanging();
  }
};

}  // namespace gva
