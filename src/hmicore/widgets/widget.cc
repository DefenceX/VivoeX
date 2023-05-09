//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file widget.cc
///

#include "hmicore/widgets/widget.h"

namespace gva {

WidgetX::WidgetX(const RendererGva& renderer, widget::WidgetEnum widget_type)
    : renderer_(renderer), widget_type_(widget_type) {}

widget::WidgetEnum WidgetX::GetWidgetType() const { return widget_type_; };

void WidgetX::SetVisible(bool visible) { visible_ = visible; }

bool WidgetX::GetVisible() const { return visible_; }

void WidgetX::SetX(uint32_t x) { x_ = x; }

uint32_t WidgetX::GetX() const { return x_; }

void WidgetX::SetY(uint32_t y) { y_ = y; }

uint32_t WidgetX::GetY() const { return y_; }

void WidgetX::SetWidth(uint32_t width) { width_ = width; }

uint32_t WidgetX::GetWidth() const { return width_; }

void WidgetX::SetHeight(uint32_t height) { height_ = height; }

uint32_t WidgetX::GetHeight() const { return height_; }

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
