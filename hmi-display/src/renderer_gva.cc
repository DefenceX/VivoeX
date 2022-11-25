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

void WidgetBase::Draw(uint32_t x, uint32_t y, uint32_t width, uint32_t height, std::string text, uint32_t text_colour) {
  char copy[256];
  char delim[] = ".";
  char *ptr = NULL;

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
    renderer_.DrawRoundedRectangle(x, y, width, height, 6, true);
  } else {
    renderer_.DrawRectangle(x, y, width, height, true);
  }

  renderer_.DrawColor(text_colour);
  renderer_.SetTextFontSize(14);
  if (text.substr(0, 4) == "icon:") {
    if (text.substr(5, 20) == "exit") renderer_.DrawIcon(kIconPowerOff, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "uparrow") renderer_.DrawIcon(kIconUpArrow, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "downarrow") renderer_.DrawIcon(kIconDownArrow, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "rightarrow") renderer_.DrawIcon(ICON_RIGHT_ARROW, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "leftarrow") renderer_.DrawIcon(kIconRightArrorw, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "rotateleft") renderer_.DrawIcon(kIconRotateLeft, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "rotateright")
      renderer_.DrawIcon(kIconRotateRight, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "plus") renderer_.DrawIcon(kIconPlus, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "minus") renderer_.DrawIcon(kIconMinus, x + width / 2, y + height / 2, 20, 20);
  } else {
    strncpy(copy, text.c_str(), 40);
    ptr = strtok(copy, delim);
    if (ptr != NULL) {
      renderer_.DrawText(x + 4, y + 30, ptr);
      ptr = strtok(NULL, delim);
      if (ptr != NULL) renderer_.DrawText(x + 4, y + 10, ptr);
    } else {
      renderer_.DrawText(x + 4, y + 30, text);
    }
  }

  x_ = x;
  y_ = y;
}

void WidgetFunctionKeyToggle::Toggle(const std::string &label1, const std::string &label2) {
  renderer_.SetColourForeground(HMI_DARK_GREEN2);
  renderer_.SetColourBackground(HMI_YELLOW);
  renderer_.SetTextFontSize(14);

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
    renderer_.DrawRoundedRectangle(GetX() + 5, GetY() + 5, 40, 20, 4, true);
  } else {
    renderer_.DrawRectangle(GetX() + 5, GetY() + 5, 40, 20, true);
  }
  renderer_.DrawColor(HMI_BLACK);
  renderer_.DrawText(GetX() + 12, GetY() + 9, label1);
  renderer_.SetColourBackground(HMI_GREY);
  renderer_.SetColourForeground(HMI_DARK_GREY);

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
    renderer_.DrawRoundedRectangle(GetX() + 50, GetY() + 5, 45, 20, 4, true);
  } else {
    renderer_.DrawRectangle(GetX() + 50, GetY() + 5, 45, 20, true);
  }
  renderer_.DrawColor(HMI_BLACK);
  renderer_.SetTextFontSize(14);
  renderer_.DrawText(GetX() + 56, GetY() + 9, label2);
}

// On the left and right of the screen
void RendererGva::DrawFunctionLabels(uint32_t x, const std::array<FunctionKeys::Labels, 6> &labels) {
  uint32_t i = 0;
  uint32_t offset = DEFAULT_HEIGHT - 88;

  setLineType(CAIRO_LINE_JOIN_ROUND);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightNormal, config_->GetThemeFont());

  uint32_t firstKey = (x < DEFAULT_WIDTH / 2) ? int(GvaKeyEnum::kKeyF1) : int(GvaKeyEnum::kKeyF7);
  GvaFunctionGroupEnum group = (x < DEFAULT_WIDTH / 2) ? GvaFunctionGroupEnum::kLeft : GvaFunctionGroupEnum::kRight;

  for (auto label : labels) {
    if (label.state != LabelStates::kLabelHidden) {
      WidgetFunctionKeyToggle *key = new WidgetFunctionKeyToggle(*this);
      SetStateLabel(label.state, config_);

      key->Draw(x, offset - (i * 72), 100, 50, label.text, GetStateTextColour(label.state, config_));
      if (label.state != LabelStates::kLabelDisabled) {
        touch_.Add(group, (uint32_t)(firstKey + i), x, offset - (i * 72), 100, 50);
      }
      if (label.toggleActive) key->Toggle(label.toggleText1, label.toggleText2);
    }
    i++;
  }
}

// Labels along the top of the screen
void RendererGva::DrawTopLabels(uint32_t y, const std::array<FunctionSelect::Labels, 8> &labels) {
  uint32_t i = 0;
  uint32_t offset = DEFAULT_WIDTH * 0.02;
  uint32_t width = (DEFAULT_WIDTH - offset * 2) / 8;
  uint32_t spacing = width * 0.1;

  SetColourForeground(config_->GetThemeLabelBorderEnabled());
  SetColourBackground(config_->GetThemeLabelBackgroundEnabled());
  setLineType(CAIRO_LINE_JOIN_ROUND);
  SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);

  for (auto label : labels) {
    if (label.state != LabelStates::kLabelDisabled) {
      SetStateLabel(label.state, config_);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
        DrawRoundedRectangle((i * width) + offset, y, width - 10, 10, 4, true);
      } else {
        DrawRectangle((i * width) + offset, y, width - 10, 10, true);
      }
      touch_.AddAbsolute(GvaFunctionGroupEnum::kTop, int(GvaKeyEnum::KKeySituationalAwareness) + i,
                         (i * width) + offset, y, (i * width) + width - spacing + offset, y + 10);
    }
    i++;
  }
}

// Control label at the bottom of the screen
void RendererGva::DrawControlLabels(const uint32_t y, const std::array<CommonTaskKeys::Labels, 8> &labels) {
  uint32_t i = 0;
  uint32_t offset = 20;
  uint32_t w = 75;

  setLineType(CAIRO_LINE_JOIN_ROUND);
  SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightNormal, config_->GetThemeFont());
  SetTextFontSize(12);

  for (auto label : labels) {
    SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);
    if (label.state != LabelStates::kLabelDisabled) {
      SetColourForeground(config_->GetThemeLabelBorderEnabled());
      SetColourBackground(config_->GetThemeLabelBackgroundEnabled());

      SetStateLabel(label.state, config_);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
        DrawRoundedRectangle((i * w) + offset, y, w - 5, 20, 4, true);
      } else {
        DrawRectangle((i * w) + offset, y, w - 5, 20, true);
      }
      SetStateText(label.state, config_);

      touch_.AddAbsolute(GvaFunctionGroupEnum::kBottom, int(GvaKeyEnum::kKeyF13) + i, (i * w) + offset, y,
                         (i * w) + w - 5 + offset, y + 20);
      DrawText((i * w) + offset + 5, y + 6, label.text.c_str());
      if (i == 4) DrawIcon(kIconUpArrow, (i * w) + offset + 34, y + 11, 15, 8);
      if (i == 5) DrawIcon(kIconDownArrow, (i * w) + offset + 34, y + 10, 15, 8);
    }

    i++;
  }
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
    case ICON_RIGHT_ARROW:
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
  }
  Restore();
}

void RendererGva::DrawMode() {
  uint32_t offset = DEFAULT_WIDTH * 0.4;
  uint32_t y = DEFAULT_HEIGHT * 0.12;

  SetColourForeground(HMI_WHITE);
  SetColourBackground(HMI_DARK_BLUE);
  SetLineThickness(1, LineType::kLineSolid);

  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightNormal, config_->GetThemeFont());

  uint32_t w = GetTextWidth("Maintinance Mode", 12);
  uint32_t h = GetTextHeight("Maintinance Mode", 12);

  DrawRoundedRectangle(DEFAULT_WIDTH / 2 - (w / 2) - 5, y, w + 10, (h) + 15, 6, true);
  // DrawRectangle(DEFAULT_WIDTH / 2 - (w / 2) - 5, y, w + 10, (h) + 15, true);
  SetTextFontSize(12);
  DrawText(DEFAULT_WIDTH / 2 - (w / 2), y + 8, "Maintinance Mode");
}

void RendererGva::DrawTable(GvaTable *table) {
  uint32_t height = 19;
  uint32_t row = 0;
  uint32_t column = 0;
  uint32_t columns;

  SetLineThickness(config_->GetThemeTableBorderThickness(), LineType::kLineSolid);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightBold, table->fontname_);
  SetColourBackground(gva::ConfigData::GetInstance()->GetThemeBackground());

  for (row = 0; row < table->rows_; row++) {
    uint32_t offset = table->GetX();

    for (column = 0; column < table->row_[row].cells_; column++) {
      uint32_t pos = 0;
      uint32_t tmp = table->row_[row].widths_[column] * ((double)table->GetWidth() / 100);

      SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, table->row_[row].cell_[column].weight, table->fontname_);

      SetColourForeground(table->row_[row].cell_[column].foreground.red,
                          table->row_[row].cell_[column].foreground.green,
                          table->row_[row].cell_[column].foreground.blue);
      SetColourBackground(table->row_[row].cell_[column].background.red,
                          table->row_[row].cell_[column].background.green,
                          table->row_[row].cell_[column].background.blue);
      DrawRectangle(offset, table->GetY() - (height * row), tmp, height, true);

      DrawColor(table->row_[row].cell_[column].textcolour.red, table->row_[row].cell_[column].textcolour.green,
                table->row_[row].cell_[column].textcolour.blue);

      uint32_t w = GetTextWidth(table->row_[row].cell_[column].text, 12);
      uint32_t h = GetTextHeight(table->row_[row].cell_[column].text, 12);

      switch (table->row_[row].cell_[column].align) {
        case CellAlignType::kAlignCentre:
          pos = offset + (tmp / 2 - w / 2);
          break;
        case CellAlignType::kAlignRight:
          pos = offset + (tmp - w - 4);
          break;
        case CellAlignType::kAlignLeft:
        default:
          pos = offset + 4;
          break;
      }
      SetTextFontSize(12);
      DrawText(pos, table->GetY() - (height * row) + 5, table->row_[row].cell_[column].text);
      offset += tmp;
    }
  }
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

void RendererGva::SetStateLabel(LabelStates state, ConfigData *config) {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do let just return
      break;
    case LabelStates::kLabelDisabled:
      SetColourForeground(config->GetThemeLabelBorderDisabled());
      SetColourBackground(config->GetThemeLabelBackgroundDisabled());
      SetLineThickness(config_->GetThemeLabelBorderThickness(), config_->GetThemeLabelLineDisabled());
      break;
    case LabelStates::kLabelEnabled:
      SetColourForeground(config->GetThemeLabelBorderEnabled());
      SetColourBackground(config->GetThemeLabelBackgroundEnabled());
      SetLineThickness(config_->GetThemeLabelBorderThickness(), config_->GetThemeLabelLineEnabled());
      break;
    case LabelStates::kLabelEnabledSelected:
      SetColourForeground(config->GetThemeLabelBorderEnabledSelected());
      SetColourBackground(config->GetThemeLabelBackgroundEnabledSelected());
      SetLineThickness(config_->GetThemeLabelBorderThickness(), config_->GetThemeLabelLineEnabledSelected());
      break;
    case LabelStates::kLabelEnabledSelectedChanging:
      SetColourForeground(config->GetThemeLabelBorderEnabledSelectedChanging());
      SetColourBackground(config->GetThemeLabelBackgroundEnabledSelectedChanging());
      SetLineThickness(config_->GetThemeLabelBorderThickness(), config_->GetThemeLabelLineEnabledSelectedChanging());
      break;
  }
}

void RendererGva::SetStateText(LabelStates state, ConfigData *config) {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do let just return
      break;
    case LabelStates::kLabelDisabled:
      DrawColor(config->GetThemeLabelTextDisabled());
      break;
    case LabelStates::kLabelEnabled:
      DrawColor(config->GetThemeLabelTextEnabled());
      break;
    case LabelStates::kLabelEnabledSelected:
      DrawColor(config->GetThemeLabelTextEnabledSelected());
      break;
    case LabelStates::kLabelEnabledSelectedChanging:
      DrawColor(config->GetThemeLabelTextEnabledSelectedChanging());
      break;
  }
}

uint32_t RendererGva::GetStateTextColour(LabelStates state, ConfigData *config) const {
  switch (state) {
    default:
    case LabelStates::kLabelHidden:
      // Nothing to do but return hidden if requested
      return config->GetThemeLabelTextDisabled();
    case LabelStates::kLabelDisabled:
      return config->GetThemeLabelTextDisabled();
    case LabelStates::kLabelEnabled:
      return config->GetThemeLabelTextEnabled();
    case LabelStates::kLabelEnabledSelected:
      return config->GetThemeLabelTextEnabledSelected();
    case LabelStates::kLabelEnabledSelectedChanging:
      return config->GetThemeLabelTextEnabledSelectedChanging();
  }
}

}  // namespace gva
