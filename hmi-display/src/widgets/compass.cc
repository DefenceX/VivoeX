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
/// \brief The vehicle compass widget
///
/// \file compass.cc
///

#include "src/widgets/compass.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "src/gva_functions_common.h"
#include "src/renderer_gva.h"

namespace gva {

WidgetPlanPositionIndicator::WidgetPlanPositionIndicator(const RendererGva& renderer)
    : WidgetX(renderer, widget::KWidgetTypeCompass) {
  mode_ = ConfigData::GetInstance()->GetPpiMode();
}

void WidgetPlanPositionIndicator::Draw() {
  if (GetVisible()) {
    DrawPPI(mode_, GetX(), GetY(), bearing_, bearing_sight_, 0);
  }
}

void WidgetPlanPositionIndicator::DrawModern(uint32_t x, uint32_t y, uint32_t degrees, uint32_t sightAzimuth,
                                             uint32_t weaponAzimuth, bool sight) const {
  double_t radius = 100;
  double_t d = degrees;  // Degrees north

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);
  GetRenderer()->DrawColor(HMI_WHITE);

  // Compass
  GetRenderer()->SetColourBackground(HMI_GREY);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(x, y, radius, true);  // Compass outline
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->DrawCircle(x, y, 80, true);  // Inner circle

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  float step = (M_PI * 2) / 12;
  int64_t c = 0;

  d = degrees;
  for (d = DegreesToRadians(degrees) - 6; d <= DegreesToRadians(degrees) + (M_PI * 2); d += step) {
    c++;
    GetRenderer()->MovePen(x + (radius - 20) * cos(d), y - (radius - 20) * sin(d));
    GetRenderer()->DrawPen(x + (radius)*cos(d), y - (radius)*sin(d), true);
  }

  // Draw Text markers
  d = DegreesToRadians(degrees);
  double_t pos = 10;
  uint32_t font_size = 14;
  uint32_t adjust_x = x - 4;
  uint32_t adjust_y = y - 4;

  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), font_size);

  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI * 2))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI * 2))), "N");
  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI))), "S");
  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI / 2))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI / 2))), "E");
  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI + M_PI / 2))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI + M_PI / 2))), "W");
  // Vehicle outline
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
  GetRenderer()->Save();
  GetRenderer()->DrawColor(HMI_WHITE);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetColourBackground(HMI_GREY);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->MovePen(x - 30, y - 65);
  GetRenderer()->DrawPen(x + 30, y - 65, false);
  GetRenderer()->DrawPen(x + 30, y + 30, false);
  GetRenderer()->DrawPen(x + 22, y + 57, false);
  GetRenderer()->DrawPen(x + 15, y + 67, false);
  GetRenderer()->DrawPen(x - 15, y + 67, false);
  GetRenderer()->DrawPen(x - 22, y + 57, false);
  GetRenderer()->DrawPen(x - 30, y + 30, false);
  GetRenderer()->DrawPen(x - 30, y - 65, false);
  GetRenderer()->ClosePath(true);
  GetRenderer()->Restore();

  // Turret outline
  GetRenderer()->Save();
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetColourBackground(HMI_GREY);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->MovePen(x - 14, y - 57);
  GetRenderer()->DrawPen(x - 25, y - 52, false);
  GetRenderer()->DrawPen(x - 25, y - 20, false);
  GetRenderer()->DrawPen(x - 20, y + 4, false);
  GetRenderer()->DrawPen(x - 8, y + 4, false);
  GetRenderer()->DrawPen(x - 4, y - 10, false);
  GetRenderer()->DrawPen(x - 4, y - 20, false);
  GetRenderer()->DrawPen(x + 25, y - 20, false);
  GetRenderer()->DrawPen(x + 25, y - 52, false);
  GetRenderer()->DrawPen(x + 14, y - 57, false);
  GetRenderer()->ClosePath(true);
  GetRenderer()->DrawRectangle(x - 4, y - 20, 6, 44, true);
  GetRenderer()->Restore();

  if (sight == true) {
    // Sight
    GetRenderer()->Save();
    GetRenderer()->Translate(-14, 0);
    GetRenderer()->Rotate(gva::DegreesToRadians(sightAzimuth));
    GetRenderer()->DrawCircle(x, y, 3, true);
    GetRenderer()->SetColourBackground(HMI_CYAN);
    GetRenderer()->DrawTriangle(x, y, x - 8, y + 16, x + 6, y + 16, true);
    GetRenderer()->SetColourBackground(HMI_DARK_BLUE);
    GetRenderer()->SetColourForeground(HMI_DARK_BLUE);
    GetRenderer()->DrawTriangle(x, y, x - 3, y + 15, x + 1, y + 15, true);
    GetRenderer()->Restore();
  }
  GetRenderer()->Restore();
}

void WidgetPlanPositionIndicator::DrawPPI(widget::ModeEnum mode, uint32_t x, uint32_t y, uint32_t degrees,
                                          uint32_t sightAzimuth, uint32_t weaponAzimuth) {
  double_t radius = 100;
  double_t angle = 45;
  double_t d = 0;
  const uint32_t font_size = 14;

  // Degrees north
  degrees += 270;
  degrees = (degrees >= 360) ? degrees - 360 : degrees;
  sightAzimuth += 270;
  sightAzimuth = (sightAzimuth >= 360) ? sightAzimuth - 360 : sightAzimuth;

  // Set the font for all compass/s
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             gva::ConfigData::GetInstance()->GetThemeFont(), font_size);

  if (mode == widget::ModeEnum::kPpiModernTankWithSights) {
    DrawModern(x, y, degrees, sightAzimuth, 10, true);
    return;
  }
  if (mode == widget::ModeEnum::kPpiModernTankWithoutSights) {
    DrawModern(x, y, degrees, sightAzimuth, 10, false);
    return;
  }

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);

  GetRenderer()->DrawColor(HMI_WHITE);

  // Compass
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(x, y, radius, true);  // Compass

  switch (mode) {
    case widget::ModeEnum::kPpiClassicArrowWithSight:
    case widget::ModeEnum::kPpiClassicArrowWithoutSight:
      // Vehicle outline
      GetRenderer()->Save();
      GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->SetColourBackground(HMI_WHITE);
      GetRenderer()->SetLineThickness(8, LineType::kLineSolid, LineCapEnd::kLineCapButt);
      GetRenderer()->MovePen(x - 22, y - 30);
      GetRenderer()->DrawPen(x, y - 10, false);
      GetRenderer()->DrawPen(x + 22, y - 30, false);
      GetRenderer()->DrawPen(x, y + 50, true);
      GetRenderer()->ClosePath(false);
      GetRenderer()->Restore();
      break;
    case widget::ModeEnum::kPpiClassicTankWithSight:
    case widget::ModeEnum::kPpiClassicTankWithoutSight:
    case widget::ModeEnum::kPpiModernTankWithSights:
    default:
      // Vehicle outline
      GetRenderer()->DrawCircle(x, y, 16, true);  // Inner circle
      GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
      GetRenderer()->Save();
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->SetColourBackground(HMI_WHITE);
      GetRenderer()->SetLineThickness(3, LineType::kLineSolid);
      GetRenderer()->MovePen(x - 30, y - 40);
      GetRenderer()->DrawPen(x + 30, y - 40, false);
      GetRenderer()->DrawPen(x + 30, y + 40, false);
      GetRenderer()->DrawPen(x + 10, y + 40, false);
      GetRenderer()->DrawPen(x + 10, y + 30, false);
      GetRenderer()->DrawPen(x - 10, y + 30, false);
      GetRenderer()->DrawPen(x - 10, y + 40, false);
      GetRenderer()->DrawPen(x - 30, y + 40, false);
      GetRenderer()->DrawPen(x - 30, y - 40, true);
      GetRenderer()->ClosePath(false);
      GetRenderer()->Restore();
      break;
  }

  d = DegreesToRadians(degrees);
  double_t pos = 12;
  uint32_t adjust_x = x - 4;
  uint32_t adjust_y = y - 4;

  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI * 2))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI * 2))), "N");
  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI))), "S");
  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI / 2))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI / 2))), "E");
  GetRenderer()->DrawText((uint32_t)(adjust_x - 3 + (radius - pos) * cos(d + (M_PI + M_PI / 2))),
                          (uint32_t)(adjust_y - 2 - (radius - pos) * sin(d + (M_PI + M_PI / 2))), "W");

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  double step = (M_PI * 2) / 32;
  int64_t p = 24;
  int64_t c = 0;

  d = degrees;
  for (d = DegreesToRadians(degrees); d <= DegreesToRadians(degrees) + (M_PI * 2); d += step) {
    p = c % 4 ? 28 : 20;
    c++;
    GetRenderer()->MovePen((uint32_t)(x + (radius - 35) * cos(d)), (uint32_t)(y - (radius - 35) * sin(d)));
    GetRenderer()->DrawPen((uint32_t)(x + (radius - p) * cos(d)), (uint32_t)(y - (radius - p) * sin(d)), true);
  }

  // Heading (Goes under sight)
  GetRenderer()->Save();
  GetRenderer()->SetColourBackground(HMI_CYAN);
  if ((mode == widget::ModeEnum::kPpiClassicArrowWithSight) ||
      (mode == widget::ModeEnum::kPpiClassicArrowWithoutSight)) {
    GetRenderer()->SetColourForeground(HMI_BLACK);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRectangle(x - 4, y, 8, 73, true);
  } else {
    GetRenderer()->SetColourForeground(HMI_CYAN);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRectangle(x - 2, y + 16, 4, 57, true);
  }
  GetRenderer()->Restore();

  // Mode zero has sight
  if ((mode == widget::ModeEnum::kPpiClassicTankWithSight) || (mode == widget::ModeEnum::kPpiClassicArrowWithSight)) {
    // Sight
    GetRenderer()->SetColourBackground(HMI_WHITE);
    GetRenderer()->SetColourForeground(HMI_WHITE);
    GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
    {
      int64_t x2, y2;

      x2 = PlotCircleX(x, radius - 10, sightAzimuth);
      y2 = PlotCircleY(y, radius - 10, sightAzimuth);
      GetRenderer()->MovePen(x, y);
      GetRenderer()->DrawPen(x2, y2, true);
      GetRenderer()->SetLineThickness(1, LineType::kLineDashed);
      x2 = PlotCircleX(x, radius - 10, (sightAzimuth - (angle / 2)));
      y2 = PlotCircleY(y, radius - 10, (sightAzimuth - (angle / 2)));
      GetRenderer()->MovePen(x, y);
      GetRenderer()->DrawPen(x2, y2, true);
      GetRenderer()->SetLineThickness(1, LineType::kLineDashed);
      x2 = PlotCircleX(x, radius - 10, (sightAzimuth + (angle / 2)));
      y2 = PlotCircleY(y, radius - 10, (sightAzimuth + (angle / 2)));
      GetRenderer()->MovePen(x, y);
      GetRenderer()->DrawPen(x2, y2, true);
    }
  }

  GetRenderer()->Restore();
};

}  // namespace gva