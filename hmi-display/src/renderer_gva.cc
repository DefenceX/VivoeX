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
/// \file renderer_gva.cc
///

#include "renderer_gva.h"

#include <math.h> /* sqrt */

#include <array>

#include "debug.h"
#include "screen_gva.h"

namespace gva {

RendererGva::RendererGva(uint32_t width, uint32_t height) : RendererCairo(height, width) {
  config_ = gva::ConfigData::GetInstance();
  touch_.SetResolution(width, height);
}

void RendererGva::DrawIcon(widget::IconType icon, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  double sx;
  double sy;
  std::array arrow{std::array{-4, -10}, std::array{-4, 0}, std::array{-8, 0},  std::array{0, +10},
                   std::array{8, 0},    std::array{+4, 0}, std::array{+4, -10}};

  sx = (width / (double)13);
  sy = (height / (double)15);

  Save();
  DrawColor(HMI_WHITE);
  SetColourBackground(HMI_WHITE);
  SetColourForeground(HMI_WHITE);
  SetLineThickness(1, LineType::kLineSolid);

  Translate(x, y);
  Rotate(M_PI);

  switch (icon) {
    case widget::IconType::kIconDownArrow:
      Rotate(M_PI);
    case widget::IconType::kIconUpArrow:
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (auto point : arrow) {
        DrawPenRaw(point[0], point[1]);
      }
      ClosePath(true);
      break;
    case widget::IconType::kIconDownArrowOutline:
      Rotate(M_PI);
    case widget::IconType::kIconUpArrowOutline:
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (auto point : arrow) {
        DrawPenRaw(point[0], point[1]);
      }
      ClosePath(true);
      break;
    case widget::IconType::kIconRightArrow:
      Rotate(M_PI);
    case widget::IconType::kIconLeftArrow:
      Rotate(M_PI * 1.5);
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (auto point : arrow) {
        DrawPenRaw(point[0], point[1]);
      }
      ClosePath(true);
      break;
    case widget::IconType::kIconRightArrowOutline:
      Rotate(M_PI);
    case widget::IconType::kIconLeftArrowOutline:
      Rotate(M_PI * 1.5);
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (auto point : arrow) {
        DrawPenRaw(point[0], point[1]);
      }
      ClosePath(true);
      break;
    case widget::IconType::kIconPowerOff:
      SetLineThickness(2, LineType::kLineSolid, LineCapEnd::kLineCapRound);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 290, 250);
      MovePenRaw(0, -4);
      DrawPenRaw(0, -10);
      ClosePath(true);
      break;
    case widget::IconType::kIconRotateLeft:
      SetLineThickness(2, LineType::kLineSolid, LineCapEnd::kLineCapRound);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 315, 225);
      MovePenRaw(5, -6);
      DrawPenRaw(5, -1);
      MovePenRaw(5, -6);
      Rotate(M_PI);

      ClosePath(true);
      break;
    case widget::IconType::kIconRotateRight:
      SetLineThickness(2, LineType::kLineSolid, LineCapEnd::kLineCapRound);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 315, 225);
      MovePenRaw(-5, -6);
      DrawPenRaw(-5, -1);
      MovePenRaw(-5, -6);
      DrawPenRaw(-9, -6);
      ClosePath(true);
      break;
    case widget::IconType::kIconPlus:
      SetLineThickness(2, LineType::kLineSolid, LineCapEnd::kLineCapRound);
      Scale(sx, sy);
      MovePenRaw(-10, 0);
      DrawPenRaw(10, 0);
      MovePenRaw(0, -10);
      DrawPenRaw(0, 10);
      ClosePath(true);
      break;
    case widget::IconType::kIconMinus:
      SetLineThickness(2, LineType::kLineSolid, LineCapEnd::kLineCapRound);
      Scale(sx, sy);
      MovePenRaw(-10, 0);
      DrawPenRaw(10, 0);
      ClosePath(true);
      break;
    case widget::IconType::kIconError:
    case widget::IconType::kIconInfo:
    case widget::IconType::kIconWarning:
      Rotate(M_PI);

      SetLineThickness(2, LineType::kLineSolid);
      if (icon == widget::IconType::kIconError) SetColourBackground(HMI_GREEN);
      if (icon == widget::IconType::kIconError) SetColourBackground(HMI_RED);
      if (icon == widget::IconType::kIconWarning) SetColourBackground(HMI_ORANGE);
      Scale(sx, sy);
      MovePenRaw(-10, +10);
      DrawPenRaw(0, -10);
      DrawPenRaw(+10, +10);
      DrawPenRaw(-10, +10);
      ClosePath(true);
      DrawColor(HMI_WHITE);
      MovePenRaw(0, -3);
      DrawPenRaw(0, +3);
      ClosePath(true);
      MovePenRaw(0, +6);
      DrawPenRaw(0, +7);
      ClosePath(true);
      break;
    case widget::IconType::kIconWaterfallSight:
      break;
    case widget::IconType::kIconWCrossSight:
      SetLineThickness(3, LineType::kLineSolid, LineCapEnd::kLineCapSquare);
      Scale(0.4, 0.4);
      // Cross hair
      // Vertical above
      MovePenRaw(0, -10);
      DrawPenRaw(0, -15);
      MovePenRaw(0, -25);
      DrawPenRaw(0, -35);
      // Horizontal right
      MovePenRaw(-10, 0);
      DrawPenRaw(-30, 0);
      MovePenRaw(-30, -10);
      DrawPenRaw(-50, -10);
      MovePenRaw(-30, +10);
      DrawPenRaw(-50, +10);
      MovePenRaw(-70, 0);
      DrawPenRaw(-90, 0);
      // Vertical below
      MovePenRaw(0, +10);
      DrawPenRaw(0, +15);
      MovePenRaw(0, +25);
      DrawPenRaw(0, +35);
      // Horizontal left
      MovePenRaw(+10, 0);
      DrawPenRaw(+30, 0);
      MovePenRaw(+30, +10);
      DrawPenRaw(+50, +10);
      MovePenRaw(+30, -10);
      DrawPenRaw(+50, -10);
      MovePenRaw(+70, 0);
      DrawPenRaw(+90, 0);

      ClosePath(true);
      break;
    default:
      // These have not been implemented yet
      break;
  }
  Restore();
}

void RendererGva::DrawButton(const std::string keyText, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t size) {
  DrawButton(keyText, fontSize, x, y, size, size, widget::CellAlignType::kAlignLeft);
}

void RendererGva::DrawButton(const std::string keyText, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t width,
                             uint32_t height, widget::CellAlignType align) {
  uint32_t textX = 6;

  SetColourForeground(HMI_GREY);
  DrawRoundedRectangle(x, y, width, height, 6, true);
  SetColourForeground(HMI_WHITE);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightBold, config_->GetThemeFont(), fontSize);
  uint32_t textHeight = GetTextHeight("qh", fontSize);
  uint32_t textWidth = GetTextWidth(keyText, fontSize);

  DrawColor(HMI_WHITE);
  if (align == widget::CellAlignType::kAlignCentre) textX = (width / 2) - (textWidth / 2);
  DrawText(x + textX, y + (height - textHeight - 4), keyText);
};

}  // namespace gva
