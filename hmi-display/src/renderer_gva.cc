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

#define PLOT_CIRCLE_X(x, radius, degree) x + (radius)*cos(((M_PI * 2) / 360) * degree)
#define PLOT_CIRCLE_Y(y, radius, degree) y - (radius)*sin(((M_PI * 2) / 360) * degree)
#define degreesToRadians(angleDegrees) ((angleDegrees)*M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians)*180.0 / M_PI)

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

void FunctionKeySimple::Draw(uint32_t x, uint32_t y, uint32_t width, uint32_t height, std::string text,
                             uint32_t text_colour) {
  char copy[256];
  char delim[] = ".";
  char *ptr = NULL;

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
    renderer_.DrawRoundedRectangle(x, y, width, height, 6, true);
  } else {
    renderer_.DrawRectangle(x, y, width, height, true);
  }

  renderer_.DrawColor(text_colour);

  if (text.substr(0, 4) == "icon:") {
    if (text.substr(5, 20) == "exit") renderer_.DrawIcon(ICON_POWER_OFF, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "uparrow") renderer_.DrawIcon(ICON_UP_ARROW, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "downarrow") renderer_.DrawIcon(ICON_DOWN_ARROW, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "rightarrow") renderer_.DrawIcon(ICON_RIGHT_ARROW, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "leftarrow") renderer_.DrawIcon(ICON_LEFT_ARROW, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "rotateleft") renderer_.DrawIcon(ICON_ROTATE_LEFT, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "rotateright")
      renderer_.DrawIcon(ICON_ROTATE_RIGHT, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "plus") renderer_.DrawIcon(ICON_PLUS, x + width / 2, y + height / 2, 20, 20);
    if (text.substr(5, 20) == "minus") renderer_.DrawIcon(ICON_MINUS, x + width / 2, y + height / 2, 20, 20);
  } else {
    strncpy(copy, text.c_str(), 40);
    ptr = strtok(copy, delim);
    if (ptr != NULL) {
      renderer_.DrawText(x + 4, y + 30, ptr, 14);
      ptr = strtok(NULL, delim);
      if (ptr != NULL) renderer_.DrawText(x + 4, y + 10, ptr, 14);
    } else {
      renderer_.DrawText(x + 4, y + 30, text, 14);
    }
  }

  x_ = x;
  y_ = y;
}

void FunctionKeyToggle::Toggle(const std::string &label1, const std::string &label2) {
  renderer_.SetColourForeground(HMI_DARK_GREEN2);
  renderer_.SetColourBackground(HMI_YELLOW);
  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
    renderer_.DrawRoundedRectangle(GetX() + 5, GetY() + 5, 40, 20, 4, true);
  } else {
    renderer_.DrawRectangle(GetX() + 5, GetY() + 5, 40, 20, true);
  }
  renderer_.DrawColor(HMI_BLACK);
  renderer_.DrawText(GetX() + 12, GetY() + 9, label1, 14);
  renderer_.SetColourBackground(HMI_GREY);
  renderer_.SetColourForeground(HMI_DARK_GREY);

  if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
    renderer_.DrawRoundedRectangle(GetX() + 50, GetY() + 5, 45, 20, 4, true);
  } else {
    renderer_.DrawRectangle(GetX() + 50, GetY() + 5, 45, 20, true);
  }
  renderer_.DrawColor(HMI_BLACK);
  renderer_.DrawText(GetX() + 56, GetY() + 9, label2, 14);
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
      FunctionKeyToggle *key = new FunctionKeyToggle(*this);
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

  SetColourForeground(config_->GetThemeLabelBorderEnabled());
  SetColourBackground(config_->GetThemeLabelBackgroundEnabled());
  setLineType(CAIRO_LINE_JOIN_ROUND);
  SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightNormal, config_->GetThemeFont());

  for (auto label : labels) {
    SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);
    if (label.state != LabelStates::kLabelDisabled) {
      SetStateLabel(label.state, config_);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::LABEL_ROUNDED) {
        DrawRoundedRectangle((i * w) + offset, y, w - 5, 20, 4, true);
      } else {
        DrawRectangle((i * w) + offset, y, w - 5, 20, true);
      }
      SetStateText(label.state, config_);

      touch_.AddAbsolute(GvaFunctionGroupEnum::kBottom, int(GvaKeyEnum::kKeyF13) + i, (i * w) + offset, y,
                         (i * w) + w - 5 + offset, y + 20);
      DrawText((i * w) + offset + 5, y + 6, label.text.c_str(), 12);
      if (i == 4) DrawIcon(ICON_UP_ARROW, (i * w) + offset + 34, y + 11, 15, 8);
      if (i == 5) DrawIcon(ICON_DOWN_ARROW, (i * w) + offset + 34, y + 10, 15, 8);
    }

    i++;
  }
}

void RendererGva::DrawIcon(IconType icon, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
  double sx, sy;
  int32_t arrow[8][2] = {{-5, -10}, {-4, -10}, {-4, 0}, {-8, 0}, {0, +10}, {8, 0}, {+4, 0}, {+4, -10}};

  DrawColor(HMI_WHITE);
  SetColourBackground(HMI_WHITE);
  SetColourForeground(HMI_WHITE);
  SetLineThickness(1, LineType::kLineSolid);

  sx = (width / (double)13);
  sy = (height / (double)15);

  Save();
  Translate(x, y);

  switch (icon) {
    case ICON_DOWN_ARROW:
      Rotate(M_PI);
    case ICON_UP_ARROW:
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(true);
      break;
    case ICON_DOWN_ARROW_OUTLINE:
      Rotate(M_PI);
    case ICON_UP_ARROW_OUTLINE:
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(false);
      break;
    case ICON_RIGHT_ARROW:
      Rotate(M_PI);
    case ICON_LEFT_ARROW:
      Rotate(M_PI * 1.5);
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(true);
      break;
    case ICON_RIGHT_ARROW_OUTLINE:
      Rotate(M_PI);
    case ICON_LEFT_ARROW_OUTLINE:
      Rotate(M_PI * 1.5);
      Scale(sx, sy);
      MovePenRaw(arrow[0][0], arrow[0][1]);
      for (uint16_t i = 1; i < 8; i++) {
        DrawPenRaw(arrow[i][0], arrow[i][1]);
      }
      ClosePath(false);
      break;
    case ICON_POWER_OFF:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 290, 250);
      MovePenRaw(0, -4);
      DrawPenRaw(0, -10);
      ClosePath(false);
      break;
    case ICON_ROTATE_LEFT:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 315, 225);
      MovePenRaw(5, -6);
      DrawPenRaw(5, -1);
      MovePenRaw(5, -6);
      DrawPenRaw(9, -6);
      ClosePath(false);
      break;
    case ICON_ROTATE_RIGHT:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      DrawArcRaw(0, 0, 8, 315, 225);
      MovePenRaw(-5, -6);
      DrawPenRaw(-5, -1);
      MovePenRaw(-5, -6);
      DrawPenRaw(-9, -6);
      ClosePath(false);
      break;
    case ICON_PLUS:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      MovePenRaw(-10, 0);
      DrawPenRaw(10, 0);
      MovePenRaw(0, -10);
      DrawPenRaw(0, 10);
      ClosePath(false);
      break;
    case ICON_MINUS:
      SetLineThickness(2, LineType::kLineSolid, LINE_CAP_ROUND);
      Scale(sx, sy);
      MovePenRaw(-10, 0);
      DrawPenRaw(10, 0);
      ClosePath(false);
      break;
    case ICON_INFO:
    case ICON_ERROR:
    case ICON_WARNING:
      SetLineThickness(2, LineType::kLineSolid);
      if (icon == ICON_INFO) SetColourBackground(HMI_GREEN);
      if (icon == ICON_ERROR) SetColourBackground(HMI_RED);
      if (icon == ICON_WARNING) SetColourBackground(HMI_ORANGE);
      Scale(sx, sy);
      MovePenRaw(-10, -10);
      DrawPenRaw(0, +10);
      DrawPenRaw(+10, -10);
      DrawPenRaw(-10, -10);
      ClosePath(true);
      DrawColor(HMI_WHITE);
      MovePenRaw(0, +3);
      DrawPenRaw(0, -3);
      ClosePath(false);
      MovePenRaw(0, -6);
      DrawPenRaw(0, -7);
      ClosePath(false);
      break;
  }
  Restore();
}

void PlanPositionIndicator::DrawPPI(uint8_t mode, uint32_t x, uint32_t y, uint32_t degrees, uint32_t sightAzimuth) {
  double_t radius = 50;
  double_t angle = 45;
  double_t d;

  renderer_.DrawColor(HMI_WHITE);
  /* Degrees north */
  degrees += 270;
  degrees = (degrees >= 360) ? degrees - 360 : degrees;
  sightAzimuth += 270;
  sightAzimuth = (sightAzimuth >= 360) ? sightAzimuth - 360 : sightAzimuth;
  d = degrees;

  // Compass
  renderer_.SetColourBackground(HMI_BLACK);
  renderer_.SetColourForeground(HMI_WHITE);
  renderer_.SetLineThickness(1, LineType::kLineSolid);
  renderer_.DrawCircle(x, y, radius, true);  // Compass
  renderer_.DrawCircle(x, y, 8, true);       // Compass

  // Vehicle outline
  renderer_.Save();
  renderer_.SetColourForeground(HMI_WHITE);
  renderer_.SetColourBackground(HMI_WHITE);
  renderer_.SetLineThickness(2, LineType::kLineSolid);
  renderer_.MovePen(x - 15, y - 20);
  renderer_.DrawPen(x + 15, y - 20, false);
  renderer_.DrawPen(x + 15, y + 20, false);
  renderer_.DrawPen(x + 5, y + 20, false);
  renderer_.DrawPen(x + 5, y + 15, false);
  renderer_.DrawPen(x - 5, y + 15, false);
  renderer_.DrawPen(x - 5, y + 20, false);
  renderer_.DrawPen(x - 15, y + 20, false);
  renderer_.DrawPen(x - 15, y - 20, true);
  // ClosePath(true);
  renderer_.Restore();

  // Compass Markings
  renderer_.SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightBold, "Courier");
  d = degreesToRadians(d);
  double_t pos = 6;

  renderer_.DrawText(x - 3 + (radius - pos) * cos(d + (M_PI * 2)), y - 2 - (radius - pos) * sin(d + (M_PI * 2)), "N",
                     10);
  renderer_.DrawText(x - 3 + (radius - pos) * cos(d + (M_PI)), y - 2 - (radius - pos) * sin(d + (M_PI)), "S", 10);
  renderer_.DrawText(x - 3 + (radius - pos) * cos(d + (M_PI / 2)), y - 2 - (radius - pos) * sin(d + (M_PI / 2)), "E",
                     10);
  renderer_.DrawText(x - 3 + (radius - pos) * cos(d + (M_PI + M_PI / 2)),
                     y - 2 - (radius - pos) * sin(d + (M_PI + M_PI / 2)), "W", 10);

  renderer_.SetLineThickness(1, LineType::kLineSolid);
  float step = (M_PI * 2) / 32;
  int64_t p = 20;
  int64_t c = 0;

  d = degrees;
  for (d = degreesToRadians(degrees); d <= degreesToRadians(degrees) + (M_PI * 2); d += step) {
    p = c % 4 ? 14 : 10;
    c++;
    renderer_.MovePen(x + (radius - 21) * cos(d), y - (radius - 21) * sin(d));
    renderer_.DrawPen(x + (radius - p) * cos(d), y - (radius - p) * sin(d), true);
  }

  // Mode zero has sight
  if (mode == 0) {
    // Sight
    renderer_.SetLineThickness(2, LineType::kLineSolid);
    renderer_.SetColourBackground(HMI_WHITE);
    renderer_.SetColourForeground(HMI_WHITE);
    {
      int64_t x2, y2;

      x2 = PLOT_CIRCLE_X(x, radius - 10, sightAzimuth);
      y2 = PLOT_CIRCLE_Y(y, radius - 10, sightAzimuth);
      renderer_.MovePen(x, y);
      renderer_.DrawPen(x2, y2, true);
      renderer_.SetLineThickness(1, LineType::kLineDashed);
      x2 = PLOT_CIRCLE_X(x, radius - 10, (sightAzimuth - (angle / 2)));
      y2 = PLOT_CIRCLE_Y(y, radius - 10, (sightAzimuth - (angle / 2)));
      renderer_.MovePen(x, y);
      renderer_.DrawPen(x2, y2, true);
      renderer_.SetLineThickness(1, LineType::kLineDashed);
      x2 = PLOT_CIRCLE_X(x, radius - 10, (sightAzimuth + (angle / 2)));
      y2 = PLOT_CIRCLE_Y(y, radius - 10, (sightAzimuth + (angle / 2)));
      renderer_.MovePen(x, y);
      renderer_.DrawPen(x2, y2, true);
    }
  }

  // Heading
  renderer_.SetLineThickness(1, LineType::kLineSolid);
  renderer_.SetColourBackground(HMI_CYAN);
  renderer_.SetColourForeground(HMI_CYAN);
  renderer_.DrawRectangle(x - 1, y + 8, 1, 35, true);
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
  DrawText(DEFAULT_WIDTH / 2 - (w / 2), y + 8, "Maintinance Mode", 12);
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
      DrawText(pos, table->GetY() - (height * row) + 5, table->row_[row].cell_[column].text, 12);
      offset += tmp;
    }
  }
}

void RendererGva::DrawButton(char *keyText, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t size) {
  DrawButton(keyText, fontSize, x, y, size, size, CellAlignType::kAlignLeft);
}

void RendererGva::DrawButton(char *keyText, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t width, uint32_t height,
                             CellAlignType align) {
  uint32_t textX = 6;

  SetColourForeground(HMI_GREY);
  DrawRoundedRectangle(x, y, width, height, 6, true);
  SetColourForeground(HMI_WHITE);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightBold, config_->GetThemeFont());
  uint32_t textHeight = GetTextHeight("qh", fontSize);
  uint32_t textWidth = GetTextWidth(keyText, fontSize);

  DrawColor(HMI_WHITE);
  if (align == CellAlignType::kAlignCentre) textX = (width / 2) - (textWidth / 2);
  DrawText(x + textX, y + (height - textHeight - 4), keyText, fontSize);
};

void RendererGva::DrawKeyboard(KeyboardModeType mode) {
  uint32_t i = 0;
  uint32_t yLocation = 30 + 25;
  uint32_t bSize = 33;
  uint32_t padding = 5;
  uint32_t fontSize = 14;
  char keyText[5];
  char keyboard[3][10];

  SetColourForeground(HMI_MEDIUM_GREY);
  SetColourBackground(HMI_DARK_GREY);
  SetLineThickness(1, LineType::kLineSolid);

  switch (mode) {
    case KeyboardModeType::kKeyboardUpper:
      memcpy(keyboard, upperKeys_, sizeof(keyboard));
      break;
    case KeyboardModeType::kKeyboardLower:
      memcpy(keyboard, lowerKeys_, sizeof(keyboard));
      break;
    case KeyboardModeType::kKeyboardNumbers:
      memcpy(keyboard, numKeys_, sizeof(keyboard));
      break;
  }

  DrawRoundedRectangle(110, yLocation, 420, padding + ((bSize + 5) * 4) + 1, 6, true);
  // DrawRectangle(110, yLocation, 420, padding + ((bSize + 5) * 4) + 1, true);
  SetColourBackground(HMI_DARK_GREY);
  SetLineThickness(1, LineType::kLineSolid);
  SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightBold, config_->GetThemeFont());

  // Draw keys
  SetColourForeground(HMI_WHITE);
  DrawColor(HMI_WHITE);
  for (i = 0; i < 10; i++) {
    sprintf(keyText, "%c", keyboard[0][i]);
    DrawButton(keyText, fontSize, 125 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 3, bSize);
  }
  for (i = 0; i < 9; i++) {
    sprintf(keyText, "%c", keyboard[1][i]);
    DrawButton(keyText, fontSize, 140 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 2, bSize);
  }
  for (i = 0; i < 8; i++) {
    sprintf(keyText, "%c", keyboard[2][i]);
    DrawButton(keyText, fontSize, 160 + (i * (bSize + 5)), yLocation + padding + (bSize + 5) * 1, bSize);
  }
  DrawIcon(ICON_LEFT_ARROW, 426 + bSize / 2, yLocation + padding + (bSize + 5) + bSize / 2, 8, 10);
  SetColourBackground(HMI_DARK_GREY);
  SetLineThickness(1, LineType::kLineSolid);
  SetColourForeground(HMI_WHITE);

  //
  // Space Bar and Mode
  //
  DrawButton("123", fontSize, 144, yLocation + 5, bSize + 5, bSize, CellAlignType::kAlignRight);
  DrawButton("SPACE", fontSize, 185, yLocation + 5, bSize + 202, bSize, CellAlignType::kAlignCentre);
  DrawButton("", fontSize, 426, yLocation + 5, bSize, bSize, CellAlignType::kAlignRight);
  DrawIcon(ICON_UP_ARROW, 426 + bSize / 2, yLocation + 5 + bSize / 2 + 2, 12, 11);
  SetColourBackground(HMI_DARK_GREY);
  SetLineThickness(1, LineType::kLineSolid);
  SetColourForeground(HMI_WHITE);
  DrawButton("Mode", fontSize, 463, yLocation + 20, 50, 50, CellAlignType::kAlignRight);
}

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
