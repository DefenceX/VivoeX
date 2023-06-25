//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file onscreen_bezel_btns.cc
///

#include "hmicore/widgets/onscreen_bezel_btns.h"

namespace gva {

WidgetOnscreenBezelBtns::WidgetOnscreenBezelBtns(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeBezelButtons), touch_(touch) {}

void WidgetOnscreenBezelBtns::Draw() {
  if (GetVisible()) {
    DrawLabels(0, kMinimumHeight-45, 0, kMinimumWidth-45, *toplabels_, *bottomlabels_, *leftlabels_, *rightlabels_);
  }
}

void WidgetOnscreenBezelBtns::DrawLabels(uint32_t topY, uint32_t bottomY, uint32_t leftX, uint32_t rightX,
                                const std::array<FunctionKeys::Labels, 8>& topLabels,
                                const std::array<FunctionKeys::Labels, 8>& bottomLabels,
                                const std::array<FunctionKeys::Labels, 8>& leftLabels,
                                const std::array<FunctionKeys::Labels, 8>& rightLabels) {
  // Draw top labels
  DrawLabelsRow(topY, topLabels);

  // Draw bottom labels
  DrawLabelsRow(bottomY, bottomLabels);

  // Draw left labels
  DrawLabelsColumn(leftX, leftLabels);

  // Draw right labels
  DrawLabelsColumn(rightX, rightLabels);
}


void WidgetOnscreenBezelBtns::DrawLabelsRow(uint32_t y, const std::array<FunctionKeys::Labels, 8>& labels) {
  uint32_t i = 0;
  uint32_t offset = kMinimumWidth * 0.12;
  uint32_t width = (kMinimumWidth - offset * 2) / 8;
  uint32_t spacing = width * 0.133;

  GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabled());
  GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeLabelBorderThickness(), LineType::kLineSolid);

  for (const auto& label : labels) {
    if (label.state != LabelStates::kLabelDisabled) {
      SetStateLabel(label.state);
      DrawBezelButton((i * width) + offset, y, width - 10, 45, label.text, GetStateTextColour(label.state), label.toggleActive);
      touch_->AddAbsolute(GvaFunctionGroupEnum::kTop, int(GvaKeyEnum::kKeySituationalAwareness) + i,
                          (i * width) + offset, y, (i * width) + width - spacing + offset, y + 10);
    }
    i++;
  }
}

void WidgetOnscreenBezelBtns::DrawLabelsColumn(uint32_t x, const std::array<FunctionKeys::Labels, 8>& labels) {
  uint32_t i = 0;
  uint32_t offset = 0.071 * kMinimumHeight;
  uint32_t height = (kMinimumHeight - offset * 2) / 8;
  uint32_t spacing = height * 0.1;

  GetRenderer()->SetColourForeground(ConfigData::GetInstance()->GetThemeLabelBorderEnabled());
  GetRenderer()->SetColourBackground(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeLabelBorderThickness(), LineType::kLineSolid);

  for (const auto& label : labels) {
    if (label.state != LabelStates::kLabelDisabled) {
      SetStateLabel(label.state);
      DrawBezelButton(x, (i * height) + offset, 45, height - 10, label.text, GetStateTextColour(label.state), label.toggleActive);
      touch_->AddAbsolute(GvaFunctionGroupEnum::kLeft, int(GvaKeyEnum::kKeySituationalAwareness) + i,
                          x, (i * height) + offset, x + 10, (i * height) + height - spacing + offset);
    }
    i++;
  }
}

void WidgetOnscreenBezelBtns::DrawBezelButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const std::string& text,
                            uint32_t text_colour, bool toggle_on) {
  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
    GetRenderer()->DrawRoundedRectangle(x, y, width, height, 6, true);
  } else {
    GetRenderer()->DrawRectangle(x, y, width, height, true);
  }

  GetRenderer()->DrawColor(text_colour);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), 14);

  // icon
  if (text.substr(0, 5) == "icon:") {
    RenderIcon(text, x, y, width, height);
  } 
  // multi-line text
  else if (text.find('.') != std::string::npos)
  {
    std::string first_line = text.substr(0, text.find('.'));
    uint32_t text_width = GetRenderer()->GetTextWidth(first_line, 14);
    GetRenderer()->DrawString(x + (width/2 - text_width/2), y + height/3 + 3, first_line);

    std::string second_line = text.substr(text.find('.') + 1);
    text_width = GetRenderer()->GetTextWidth(second_line, 14);
    GetRenderer()->DrawString(x + (width/2 - text_width/2), y + 2*height/3 + 3, second_line);
  } 
  // Single line text
  else {
    uint32_t text_width = GetRenderer()->GetTextWidth(text, 14);
    GetRenderer()->DrawString(x + (width/2 - text_width/2), y + height/2 + 3, text);

  }
  x_ = x;
  y_ = y;
}


void WidgetOnscreenBezelBtns::SetLabels(std::array<FunctionKeys::Labels, 8>* toplabels, std::array<FunctionKeys::Labels, 8>* bottomlabels, std::array<FunctionKeys::Labels, 8>* leftlabels, std::array<FunctionKeys::Labels, 8>* rightlabels) {
  toplabels_ = toplabels;
  bottomlabels_ = bottomlabels;
  leftlabels_ = leftlabels;
  rightlabels_ = rightlabels;
}

void WidgetOnscreenBezelBtns::RenderIcon(const std::string& text, uint32_t x, uint32_t y, uint32_t width,
                                  uint32_t height) const {
  if (text.substr(5, 20) == "exit")
    GetRenderer()->DrawIcon(widget::IconType::kIconPowerOff, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "uparrow")
    GetRenderer()->DrawIcon(widget::IconType::kIconUpArrow, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "downarrow")
    GetRenderer()->DrawIcon(widget::IconType::kIconDownArrow, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "rightarrow")
    GetRenderer()->DrawIcon(widget::IconType::kIconRightArrow, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "leftarrow")
    GetRenderer()->DrawIcon(widget::IconType::kIconLeftArrow, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "rotateleft")
    GetRenderer()->DrawIcon(widget::IconType::kIconRotateLeft, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "rotateright")
    GetRenderer()->DrawIcon(widget::IconType::kIconRotateRight, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "plus")
    GetRenderer()->DrawIcon(widget::IconType::kIconPlus, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "minus")
    GetRenderer()->DrawIcon(widget::IconType::kIconMinus, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "waterfall")
    GetRenderer()->DrawIcon(widget::IconType::kIconWaterfallSight, x + width / 2, y + height / 2, 20, 20);
  if (text.substr(5, 20) == "cross")
    GetRenderer()->DrawIcon(widget::IconType::kIconWCrossSight, x + width / 2, y + height / 2, 20, 20);
}

}  // namespace gva
