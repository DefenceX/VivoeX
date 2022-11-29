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
/// \brief The Generic Vehicle Architecture (GVA) renderer for complex objects and widgets.
///
/// \file renderer_gva.cc
///

#include "renderer_gva.h"

#include <math.h> /* sqrt */

#include "debug.h"
#include "screen_gva.h"

namespace gva {

uint32_t GvaRow::addCell(GvaCell newcell, uint32_t width) {
  widths_[cells_] = width;
  cell_[cells_++] = newcell;
  return cells_;
};

RendererGva::RendererGva(uint32_t width, uint32_t height) : RendererCairo(height, width) {
  config_ = gva::ConfigData::GetInstance();
  touch_.SetResolution(width, height);
}

void RendererGva::DrawIcon(IconType icon, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  double sx, sy;
  int32_t arrow[8][2] = {{-5, -10}, {-4, -10}, {-4, 0}, {-8, 0}, {0, +10}, {8, 0}, {+4, 0}, {+4, -10}};

  sx = (width / (double)13);
  sy = (height / (double)15);

  Save();
  DrawColor(HMI_WHITE);
  SetColourBackground(HMI_WHITE);
  SetColourForeground(HMI_WHITE);
  SetLineThickness(1, LineType::kLineSolid);

  Translate(x, y);

  switch (icon) {
    case kIconDownArrow:
      Rotate(M_PI);
    case kIconUpArrow:
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(true);
      break;
    case kIconDownArrowOutline:
      Rotate(M_PI);
    case kIconUpArrowOutline:
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(true);
      break;
    case kIconRightArrow:
      Rotate(M_PI);
    case kIconRightArrorw:
      Rotate(M_PI * 1.5);
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(true);
      break;
    case kIconRightArrowOutline:
      Rotate(M_PI);
    case kIconLeftArrorwOutline:
      Rotate(M_PI * 1.5);
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(true);
      break;
    case kIconPowerOff:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 290, 250);
      MovePenRaw(0, -4);
      DrawPenRaw(0, -10);
      ClosePath(true);
      break;
    case kIconRotateLeft:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 315, 225);
      MovePenRaw(5, -6);
      DrawPenRaw(5, -1);
      MovePenRaw(5, -6);
      DrawPenRaw(9, -6);
      ClosePath(true);
      break;
    case kIconRotateRight:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 315, 225);
      MovePenRaw(-5, -6);
      DrawPenRaw(-5, -1);
      MovePenRaw(-5, -6);
      DrawPenRaw(-9, -6);
      ClosePath(true);
      break;
    case kIconPlus:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      MovePenRaw(-10, 0);
      DrawPenRaw(10, 0);
      MovePenRaw(0, -10);
      DrawPenRaw(0, 10);
      ClosePath(true);
      break;
    case kIconMinus:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      MovePenRaw(-10, 0);
      DrawPenRaw(10, 0);
      ClosePath(true);
      break;
    case kIconError:
    case kIconInfo:
    case kIconWarning:
      SetLineThickness(2, LineType::kLineSolid);
      if (icon == kIconError) SetColourBackground(HMI_GREEN);
      if (icon == kIconError) SetColourBackground(HMI_RED);
      if (icon == kIconWarning) SetColourBackground(HMI_ORANGE);
      Scale(sx, sy);
      MovePenRaw(-10, -10);
      DrawPenRaw(0, +10);
      DrawPenRaw(+10, -10);
      DrawPenRaw(-10, -10);
      ClosePath(true);
      DrawColor(HMI_WHITE);
      MovePenRaw(0, +3);
      DrawPenRaw(0, -3);
      ClosePath(true);
      MovePenRaw(0, -6);
      DrawPenRaw(0, -7);
      ClosePath(true);
      break;
    case kIconNone:
    case kIconEnter:
    case kIconLocation:
    case kIconCentre:
    default:
      // These have not been implemented yet
      break;
  }
  Restore();
}

void RendererGva::DrawButton(const std::string keyText, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t size) {
  DrawButton(keyText, fontSize, x, y, size, size, CellAlignType::kAlignLeft);
}

void RendererGva::DrawButton(const std::string keyText, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t width,
                             uint32_t height, CellAlignType align) {
  uint32_t textX = 6;

  SetColourForeground(HMI_GREY);
  DrawRoundedRectangle(x, y, width, height, 6, true);
  SetColourForeground(HMI_WHITE);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightBold, config_->GetThemeFont());
  uint32_t textHeight = GetTextHeight("qh", fontSize);
  uint32_t textWidth = GetTextWidth(keyText, fontSize);

  DrawColor(HMI_WHITE);
  if (align == CellAlignType::kAlignCentre) textX = (width / 2) - (textWidth / 2);
  SetTextFontSize(fontSize);
  DrawText(x + textX, y + (height - textHeight - 4), keyText);
};

}  // namespace gva
