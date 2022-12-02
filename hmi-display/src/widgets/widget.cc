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
/// \brief Template for all widgets
///
/// \file widget.cc
///

#include "src/widgets/widget.h"

namespace gva {

WidgetX::WidgetX(const RendererGva& renderer, widget::WidgetEnum widget_type)
    : renderer_(renderer), widget_type_(widget_type) {}

void WidgetX::SetVisible(bool visible) { visible_ = visible; }

bool WidgetX::GetVisible() const { return visible_; }

void WidgetX::SetX(uint32_t x) { x_ = x; }

uint32_t WidgetX::GetX() const { return x_; }

void WidgetX::SetY(uint32_t y) { y_ = y; }

uint32_t WidgetX::GetY() const { return y_; }

widget::WidgetEnum WidgetX::GetType() const { return widget_type_; }

RendererGva* WidgetX::GetRenderer() const { return const_cast<gva::RendererGva*>(&renderer_); }

void WidgetX::SetStateText(LabelStates state) {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do let just return
      break;
    case LabelStates::kLabelDisabled:
      GetRenderer()->DrawColor(ConfigData::GetInstance()->GetThemeLabelTextDisabled());
      break;
    case LabelStates::kLabelEnabled:
      GetRenderer()->DrawColor(ConfigData::GetInstance()->GetThemeLabelTextEnabled());
      break;
    case LabelStates::kLabelEnabledSelected:
      GetRenderer()->DrawColor(ConfigData::GetInstance()->GetThemeLabelTextEnabledSelected());
      break;
    case LabelStates::kLabelEnabledSelectedChanging:
      GetRenderer()->DrawColor(ConfigData::GetInstance()->GetThemeLabelTextEnabledSelectedChanging());
      break;
  }
}

void WidgetX::SetStateLabel(const LabelStates state) {
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

uint32_t WidgetX::GetStateTextColour(LabelStates state) const {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do but return hidden if requested
      return ConfigData::GetInstance()->GetThemeLabelTextDisabled();
    case LabelStates::kLabelDisabled:
      return ConfigData::GetInstance()->GetThemeLabelTextDisabled();
    case LabelStates::kLabelEnabled:
      return ConfigData::GetInstance()->GetThemeLabelTextEnabled();
    case LabelStates::kLabelEnabledSelected:
      return ConfigData::GetInstance()->GetThemeLabelTextEnabledSelected();
    case LabelStates::kLabelEnabledSelectedChanging:
      return ConfigData::GetInstance()->GetThemeLabelTextEnabledSelectedChanging();
  }
};

}  // namespace gva
