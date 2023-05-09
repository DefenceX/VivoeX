//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file keyboard.cc
///

#include "hmicore/widgets/keyboard.h"

#include "hmicore/config_reader.h"

namespace gva {

WidgetKeyboard::WidgetKeyboard(const RendererGva& renderer)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeKeyboard) {
  SetVisible(false);
}

void WidgetKeyboard::Draw() {
  if (GetVisible()) {
    DrawKeyboard(mode_);
  }
}

void WidgetKeyboard::DrawKeyboard(const widget::KeyboardModeType mode) {
  uint32_t i = 0;
  uint32_t yLocation = 265;
  uint32_t bSize = 33;
  uint32_t padding = 5;
  uint32_t fontSize = 14;
  std::string keyText;
  std::vector<std::vector<char>> keyboard;

  GetRenderer()->SetColourForeground(HMI_MEDIUM_GREY);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  switch (mode) {
    case widget::KeyboardModeType::kKeyboardUpper:
      keyboard = upperKeys_;
      break;
    case widget::KeyboardModeType::kKeyboardLower:
      keyboard = lowerKeys_;
      break;
    case widget::KeyboardModeType::kKeyboardNumbers:
      keyboard = numKeys_;
      break;
  }

  GetRenderer()->DrawRoundedRectangle(110, yLocation, 420, padding + ((bSize + 5) * 4) + 1, 6, true);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightBold,
                             gva::ConfigData::GetInstance()->GetThemeFont(), fontSize);

  // Draw keys
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->DrawColor(HMI_WHITE);
  for (i = 0; i < 10; i++) {
    keyText = keyboard[0][i];
    GetRenderer()->DrawButton(keyText, fontSize, 125 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 0, bSize);
  }
  for (i = 0; i < 9; i++) {
    keyText = keyboard[1][i];
    GetRenderer()->DrawButton(keyText, fontSize, 140 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 1, bSize);
  }
  for (i = 0; i < 8; i++) {
    keyText = keyboard[2][i];
    GetRenderer()->DrawButton(keyText, fontSize, 160 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 2, bSize);
  }
  GetRenderer()->DrawIcon(widget::IconType::kIconRightArrow, 426 + bSize / 2,
                          yLocation + padding + (bSize + 5) * 2 + bSize / 2, 8, 10);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->SetColourForeground(HMI_WHITE);

  //
  // Space Bar and Mode
  //
  GetRenderer()->DrawButton("123", fontSize, 144, yLocation + padding + (bSize + 5) * 3, bSize + 5, bSize,
                            widget::CellAlignType::kAlignRight);
  GetRenderer()->DrawButton("SPACE", fontSize, 185, yLocation + padding + (bSize + 5) * 3, bSize + 202, bSize,
                            widget::CellAlignType::kAlignCentre);
  GetRenderer()->DrawButton("", fontSize, 426, yLocation + padding + (bSize + 5) * 3, bSize, bSize,
                            widget::CellAlignType::kAlignRight);
  GetRenderer()->DrawIcon(widget::IconType::kIconUpArrow, 426 + bSize / 2, yLocation + 135, 12, 11);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->DrawButton("Mode", fontSize, 463, yLocation + padding + (bSize + 5) * 3 - 30, 50, 50,
                            widget::CellAlignType::kAlignRight);
}

void WidgetKeyboard::SetMode(const widget::KeyboardModeType mode) { mode_ = mode; }

widget::KeyboardModeType WidgetKeyboard::GetMode() const { return mode_; }

}  // namespace gva