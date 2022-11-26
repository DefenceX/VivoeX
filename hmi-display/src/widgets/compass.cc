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
    : WidgetX(renderer, KWidgetTypeCompass) {}

void WidgetPlanPositionIndicator::Draw() {
  if (GetVisible()) {
    WidgetPlanPositionIndicator::ModeEnum::kPpiClassicTankWithSight;
    DrawPPI(mode_, GetX(), GetY(), bearing_, bearing_sight_);
  }
}

void WidgetPlanPositionIndicator::DrawPPI(ModeEnum mode, uint32_t x, uint32_t y, uint32_t degrees,
                                          uint32_t sightAzimuth) {
  double_t radius = 100;
  double_t angle = 45;
  double_t d;

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);

  GetRenderer()->DrawColor(HMI_WHITE);
  /* Degrees north */
  degrees += 270;
  degrees = (degrees >= 360) ? degrees - 360 : degrees;
  sightAzimuth += 270;
  sightAzimuth = (sightAzimuth >= 360) ? sightAzimuth - 360 : sightAzimuth;
  d = degrees;

  // Compass
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(x, y, radius, true);  // Compass

  switch (mode) {
    case ModeEnum::kPpiClassicArrowWithSight:
    case ModeEnum::kPpiClassicArrowWithoutSight:
      // Vehicle outline
      GetRenderer()->Save();
      GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->SetColourBackground(HMI_WHITE);
      GetRenderer()->SetLineThickness(8, LineType::kLineSolid, LineCapEnd::LINE_CAP_BUTT);
      GetRenderer()->MovePen(x - 22, y - 30);
      GetRenderer()->DrawPen(x, y - 10, false);
      GetRenderer()->DrawPen(x + 22, y - 30, false);
      GetRenderer()->DrawPen(x, y + 50, true);
      GetRenderer()->ClosePath(false);
      GetRenderer()->Restore();
      break;
    case ModeEnum::kPpiClassicTankWithSight:
    case ModeEnum::kPpiClassicTankWithoutSight:
    case ModeEnum::kPpiModernTankWithSights:
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

  d = DegreesToRadians(d);
  double_t pos = 12;
  uint32_t font_size = 14;
  uint32_t adjust_x = x - 4;
  uint32_t adjust_y = y - 4;

  GetRenderer()->SetTextFontSize(font_size);
  GetRenderer()->DrawText(adjust_x - 3 + (radius - pos) * cos(d + (M_PI * 2)),
                          adjust_y - 2 - (radius - pos) * sin(d + (M_PI * 2)), "N");
  GetRenderer()->DrawText(adjust_x - 3 + (radius - pos) * cos(d + (M_PI)),
                          adjust_y - 2 - (radius - pos) * sin(d + (M_PI)), "S");
  GetRenderer()->DrawText(adjust_x - 3 + (radius - pos) * cos(d + (M_PI / 2)),
                          adjust_y - 2 - (radius - pos) * sin(d + (M_PI / 2)), "E");
  GetRenderer()->DrawText(adjust_x - 3 + (radius - pos) * cos(d + (M_PI + M_PI / 2)),
                          adjust_y - 2 - (radius - pos) * sin(d + (M_PI + M_PI / 2)), "W");

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  float step = (M_PI * 2) / 32;
  int64_t p = 24;
  int64_t c = 0;

  d = degrees;
  for (d = DegreesToRadians(degrees); d <= DegreesToRadians(degrees) + (M_PI * 2); d += step) {
    p = c % 4 ? 28 : 20;
    c++;
    GetRenderer()->MovePen(x + (radius - 35) * cos(d), y - (radius - 35) * sin(d));
    GetRenderer()->DrawPen(x + (radius - p) * cos(d), y - (radius - p) * sin(d), true);
  }

  // Heading (Goes under sight)
  GetRenderer()->Save();
  GetRenderer()->SetColourBackground(HMI_CYAN);
  if ((mode == ModeEnum::kPpiClassicArrowWithSight) || (mode == ModeEnum::kPpiClassicArrowWithoutSight)) {
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
  if ((mode == ModeEnum::kPpiClassicTankWithSight) || (mode == ModeEnum::kPpiClassicArrowWithSight)) {
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