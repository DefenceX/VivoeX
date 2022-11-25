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
/// \brief The on screen keyboard widget
///
/// \file keyboard.cc
///

#include "src/widgets/keyboard.h"

#include "src/screen_gva.h"

namespace gva {

WidgetKeyboard::WidgetKeyboard(const RendererGva& renderer) : WidgetX(renderer, KWidgetTypeKeyboard) {}

void WidgetKeyboard::Draw() { DrawKeyboard(mode_); }

void WidgetKeyboard::DrawKeyboard(const KeyboardModeType mode) {
  uint32_t i = 0;
  uint32_t yLocation = 30 + 25;
  uint32_t bSize = 33;
  uint32_t padding = 5;
  uint32_t fontSize = 14;
  std::string keyText;
  std::vector<std::vector<char>> keyboard;

  GetRenderer()->SetColourForeground(HMI_MEDIUM_GREY);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  switch (mode) {
    case KeyboardModeType::kKeyboardUpper:
      keyboard = upperKeys_;
      break;
    case KeyboardModeType::kKeyboardLower:
      keyboard = upperKeys_;
      break;
    case KeyboardModeType::kKeyboardNumbers:
      keyboard = upperKeys_;
      break;
  }

  GetRenderer()->DrawRoundedRectangle(110, yLocation, 420, padding + ((bSize + 5) * 4) + 1, 6, true);
  // DrawRectangle(110, yLocation, 420, padding + ((bSize + 5) * 4) + 1, true);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightBold,
                             gva::ConfigData::GetInstance()->GetThemeFont());

  // Draw keys
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->DrawColor(HMI_WHITE);
  for (i = 0; i < 10; i++) {
    keyText = keyboard[0][i];
    GetRenderer()->DrawButton(keyText, fontSize, 125 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 3, bSize);
  }
  for (i = 0; i < 9; i++) {
    keyText = keyboard[1][i];
    GetRenderer()->DrawButton(keyText, fontSize, 140 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 2, bSize);
  }
  for (i = 0; i < 8; i++) {
    keyText = keyboard[2][i];
    GetRenderer()->DrawButton(keyText, fontSize, 160 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 1, bSize);
  }
  GetRenderer()->DrawIcon(kIconRightArrorw, 426 + bSize / 2, yLocation + padding + (bSize + 5) + bSize / 2, 8, 10);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->SetColourForeground(HMI_WHITE);

  //
  // Space Bar and Mode
  //
  GetRenderer()->DrawButton("123", fontSize, 144, yLocation + 5, bSize + 5, bSize, CellAlignType::kAlignRight);
  GetRenderer()->DrawButton("SPACE", fontSize, 185, yLocation + 5, bSize + 202, bSize, CellAlignType::kAlignCentre);
  GetRenderer()->DrawButton("", fontSize, 426, yLocation + 5, bSize, bSize, CellAlignType::kAlignRight);
  GetRenderer()->DrawIcon(kIconUpArrow, 426 + bSize / 2, yLocation + 5 + bSize / 2 + 2, 12, 11);
  GetRenderer()->SetColourBackground(HMI_DARK_GREY);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->DrawButton("Mode", fontSize, 463, yLocation + 20, 50, 50, CellAlignType::kAlignRight);
}

void WidgetKeyboard::SetMode(const KeyboardModeType mode) { mode_ = mode; }

KeyboardModeType WidgetKeyboard::GetMode() const { return mode_; }

}  // namespace gva