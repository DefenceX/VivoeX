//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file side_labels.cc
///

#include "hmicore/widgets/side_labels.h"

namespace gva {

WidgetSideLabels::WidgetSideLabels(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeCompass), touch_(touch) {}

void WidgetSideLabels::Draw() {
  if (GetVisible()) {
    DrawFunctionLabels();
  }
}

void WidgetSideLabels::Draw(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const std::string& text,
                            uint32_t text_colour, bool toggle_on) {
  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
    GetRenderer()->DrawRoundedRectangle(x, y, width, height, 6, true);
  } else {
    GetRenderer()->DrawRectangle(x, y, width, height, true);
  }

  GetRenderer()->DrawColor(text_colour);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), 14);

  if (text.substr(0, 5) == "icon:") {
    RenderIcon(text, x, y, width, height);
  } else {
    if (text.find('.') != std::string::npos) {
      std::string first_line = text.substr(0, text.find('.'));
      uint32_t text_width = GetRenderer()->GetTextWidth(first_line, 14);
      GetRenderer()->DrawString(x + (98 - text_width) / 2, y + 20, first_line);
      std::string second_line = text.substr(text.find('.') + 1);
      text_width = GetRenderer()->GetTextWidth(second_line, 14);
      GetRenderer()->DrawString(x + (98 - text_width) / 2, y + 40, second_line);
    } else {
      uint32_t text_width = GetRenderer()->GetTextWidth(text, 14);
      if (toggle_on) {
        GetRenderer()->DrawString(x + (98 - text_width) / 2, y + 17, text);

      } else {
        GetRenderer()->DrawString(x + (98 - text_width) / 2, y + 30, text);
      }
    }
  }

  x_ = x;
  y_ = y;
}

void WidgetSideLabels::Toggle(const std::string& label1, const std::string& label2) const {
  int ypos = 25;
  GetRenderer()->SetColourForeground(kHmiDarkGreen2);
  GetRenderer()->SetColourBackground(kHmiYellow);

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
    GetRenderer()->DrawRoundedRectangle(GetX() + 5, GetY() + ypos, 40, 20, 4, true);
  } else {
    GetRenderer()->DrawRectangle(GetX() + 5, GetY() + ypos, 40, 20, true);
  }
  GetRenderer()->DrawColor(kHmiBlack);
  GetRenderer()->DrawString(GetX() + 12, GetY() + ypos + 15, label1);
  GetRenderer()->SetColourBackground(kHmiGrey);
  GetRenderer()->SetColourForeground(kHmiDarkGreen2);

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
    GetRenderer()->DrawRoundedRectangle(GetX() + 50, GetY() + ypos, 45, 20, 4, true);
  } else {
    GetRenderer()->DrawRectangle(GetX() + 50, GetY() + ypos, 45, 20, true);
  }
  GetRenderer()->DrawColor(kHmiBlack);
  GetRenderer()->DrawString(GetX() + 56, GetY() + ypos + 15, label2);
}

// On the left and right of the screen
void WidgetSideLabels::DrawFunctionLabels() {
  uint32_t i = 0;
  uint32_t offset = 38;

  hmiScreenSize& minimumSizeInstance = hmiScreenSize::getInstance();
  std::tuple<int, int> currentScreenSize = minimumSizeInstance.getMinimumSize();
  int width_ = std::get<0>(currentScreenSize);

  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), 14);

  uint32_t firstKey = (GetX() < width_ / 2) ? int(GvaKeyEnum::kKeyF1) : int(GvaKeyEnum::kKeyF7);
  GvaFunctionGroupEnum group =
      (GetX() < width_ / 2) ? GvaFunctionGroupEnum::kLeft : GvaFunctionGroupEnum::kRight;

  for (auto label : *labels_) {
    if (label.state != LabelStates::kLabelHidden) {
      SetStateLabel(label.state);
      Draw(GetX(), offset + (i * 72), 100, 50, label.text, GetStateTextColour(label.state), label.toggleActive);
      if (label.state != LabelStates::kLabelDisabled) {
        touch_->Add(group, firstKey + i, GetX(), offset + (i * 72), 100, 50);
      }
      if (label.toggleActive) Toggle(label.toggleText1, label.toggleText2);
    }
    i++;
  }
}

void WidgetSideLabels::SetLabels(std::array<FunctionKeys::Labels, 6>* labels) { labels_ = labels; }

void WidgetSideLabels::RenderIcon(const std::string& text, uint32_t x, uint32_t y, uint32_t width,
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
