//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeCompass) {
  mode_ = ConfigData::GetInstance()->GetPpiMode();
}

void WidgetPlanPositionIndicator::Draw() {
  if (GetVisible()) {
    DrawPPI(mode_, GetX(), GetY(), bearing_, bearing_sight_, 0);
  }
}

// weaponSight for future use, currently unused
void WidgetPlanPositionIndicator::DrawModern(uint32_t x, uint32_t y, uint32_t degrees, uint32_t sightAzimuth,
                                             uint32_t weaponAzimuth [[maybe_unused]], bool sight) const {
  double_t radius = 100;

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);
  GetRenderer()->Translate(x, y);
  GetRenderer()->DrawColor(HMI_WHITE);

  // Compass
  GetRenderer()->SetColourBackground(HMI_GREY);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, (uint32_t)radius, true);  // Compass outline
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->DrawCircle(0, 0, 80, true);  // Inner circle

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  uint32_t step = 360 / 12;

  for (uint32_t d = 0; d <= 360; d += step) {
    double_t r = DegreesToRadians(d + 15 + degrees % 30);
    GetRenderer()->MovePen((int32_t)((radius - 20) * cos(r)), (int32_t)(-(radius - 20) * sin(r)));
    GetRenderer()->DrawPen((int32_t)(radius * cos(r)), (int32_t)(-radius * sin(r)), true);
  }

  uint32_t font_size = 14;
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), font_size);

  // Draw Text markers
  int64_t pos = 10;
  uint32_t adjust_x = -6;
  uint32_t adjust_y = +4;
  step = (uint32_t)(((float)M_PI * 2) / 4);
  std::array<std::string, 4> compass_points = {"S", "W", "N", "E"};

  int32_t c = 0;
  for (uint16_t d = 0; d < 360; d += RadiansToDegrees(step)) {
    auto render_degrees = (uint16_t)(d + degrees);

    GetRenderer()->DrawText((uint32_t)(adjust_x + (radius - (double_t)pos) * sin(DegreesToRadians(render_degrees))),
                            (uint32_t)(adjust_y + (radius - (double_t)pos) * cos(DegreesToRadians(render_degrees))),
                            compass_points[c]);
    c++;
  }

  // Vehicle outline
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
  GetRenderer()->Save();
  GetRenderer()->DrawColor(HMI_WHITE);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetColourBackground(HMI_GREY);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->MovePen(-30, +65);
  GetRenderer()->DrawPen(30, +65, false);
  GetRenderer()->DrawPen(30, -30, false);
  GetRenderer()->DrawPen(22, -57, false);
  GetRenderer()->DrawPen(15, -67, false);
  GetRenderer()->DrawPen(-15, -67, false);
  GetRenderer()->DrawPen(-22, -57, false);
  GetRenderer()->DrawPen(-30, -30, false);
  GetRenderer()->DrawPen(-30, 65, false);
  GetRenderer()->ClosePath(true);
  GetRenderer()->Restore();

  // Turret outline
  GetRenderer()->Save();
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetColourBackground(HMI_GREY);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->MovePen(-14, 57);
  GetRenderer()->DrawPen(-25, 52, false);
  GetRenderer()->DrawPen(-25, 20, false);
  GetRenderer()->DrawPen(-20, -4, false);
  GetRenderer()->DrawPen(-8, -4, false);
  GetRenderer()->DrawPen(-4, 10, false);
  GetRenderer()->DrawPen(-4, 20, false);
  GetRenderer()->DrawPen(25, 20, false);
  GetRenderer()->DrawPen(25, 52, false);
  GetRenderer()->DrawPen(14, 57, false);
  GetRenderer()->ClosePath(true);
  GetRenderer()->DrawRectangle(-4, -20, 6, 44, true);
  GetRenderer()->Restore();

  if (sight == true) {
    // Sight
    GetRenderer()->Save();
    GetRenderer()->Translate(-14, 0);
    GetRenderer()->Rotate(gva::DegreesToRadians(sightAzimuth));
    GetRenderer()->DrawCircle(0, 0, 3, true);
    GetRenderer()->SetColourBackground(HMI_CYAN);
    GetRenderer()->DrawTriangle(0, 0, -8, -16, 6, -16, true);
    GetRenderer()->SetColourBackground(HMI_DARK_BLUE);
    GetRenderer()->SetColourForeground(HMI_DARK_BLUE);
    GetRenderer()->DrawTriangle(0, 0, -3, -15, 1, -15, true);
    GetRenderer()->Restore();
  }
  GetRenderer()->Restore();
}

void WidgetPlanPositionIndicator::DrawSight(double_t radius, uint32_t render_sight_azimuth, double_t angle) {
  int32_t x2 = 0;
  int32_t y2 = 0;

  // Sight
  GetRenderer()->SetColourBackground(HMI_WHITE);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);

  x2 = PlotCircleX(0, radius - 10, render_sight_azimuth);
  y2 = PlotCircleY(0, radius - 10, render_sight_azimuth);
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->DrawPen(x2, y2, true);
  GetRenderer()->SetLineThickness(1, LineType::kLineDashed);
  x2 = PlotCircleX(0, radius - 10, (render_sight_azimuth - (angle / 2)));
  y2 = PlotCircleY(0, radius - 10, (render_sight_azimuth - (angle / 2)));
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->DrawPen(x2, y2, true);
  GetRenderer()->SetLineThickness(1, LineType::kLineDashed);
  x2 = PlotCircleX(0, radius - 10, (render_sight_azimuth + (angle / 2)));
  y2 = PlotCircleY(0, radius - 10, (render_sight_azimuth + (angle / 2)));
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->DrawPen(x2, y2, true);
}

void WidgetPlanPositionIndicator::DrawPPI(widget::ModeEnum mode, uint32_t x, uint32_t y, uint32_t degrees,
                                          uint32_t sight_azimuth, uint32_t weapon_azimuth) {
  double_t radius = 100;
  double_t angle = 45;
  const uint32_t font_size = 14;

  // Degrees north
  uint32_t render_sight_azimuth = sight_azimuth;
  render_sight_azimuth = (render_sight_azimuth >= 360) ? render_sight_azimuth - 360 : render_sight_azimuth;

  // Set the font for all compass/s
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             gva::ConfigData::GetInstance()->GetThemeFont(), font_size);

  if (mode == widget::ModeEnum::kPpiModernTankWithSights) {
    DrawModern(x, y, degrees, sight_azimuth, 10, true);
    return;
  }
  if (mode == widget::ModeEnum::kPpiModernTankWithoutSights) {
    DrawModern(x, y, degrees, sight_azimuth, 10, false);
    return;
  }

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);
  GetRenderer()->Translate(x, y);

  GetRenderer()->DrawColor(HMI_WHITE);

  // Compass
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, (uint32_t)radius, true);  // Compass

  switch (mode) {
    case widget::ModeEnum::kPpiClassicArrowWithSight:
    case widget::ModeEnum::kPpiClassicArrowWithoutSight:
      // Vehicle outline
      GetRenderer()->Save();
      GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->SetColourBackground(HMI_WHITE);
      GetRenderer()->SetLineThickness(8, LineType::kLineSolid, LineCapEnd::kLineCapButt);
      GetRenderer()->MovePen(-22, +30);
      GetRenderer()->DrawPen(0, 10, false);
      GetRenderer()->DrawPen(22, 30, false);
      GetRenderer()->DrawPen(0, -50, true);
      GetRenderer()->ClosePath(false);
      GetRenderer()->Restore();
      break;
    default:
      // Vehicle outline
      GetRenderer()->DrawCircle(0, 0, 16, true);  // Inner circle
      GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
      GetRenderer()->Save();
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->SetColourBackground(HMI_WHITE);
      GetRenderer()->SetLineThickness(3, LineType::kLineSolid);
      GetRenderer()->MovePen(-30, +40);
      GetRenderer()->DrawPen(+30, +40, false);
      GetRenderer()->DrawPen(+30, -40, false);
      GetRenderer()->DrawPen(+10, -40, false);
      GetRenderer()->DrawPen(+10, -30, false);
      GetRenderer()->DrawPen(-10, -30, false);
      GetRenderer()->DrawPen(-10, -40, false);
      GetRenderer()->DrawPen(-30, -40, false);
      GetRenderer()->DrawPen(-30, +40, true);
      GetRenderer()->ClosePath(false);
      GetRenderer()->Restore();
      break;
  }

  // Draw Text markers
  int64_t pos = 9;
  int32_t adjust_x = -5;
  int32_t adjust_y = +4;
  double_t step_radians = (M_PI * 2) / 4;
  int64_t c = 0;
  std::array<std::string, 4> compass_points = {"S", "W", "N", "E"};

  for (uint32_t d = 0; d < 360; d += RadiansToDegrees(step_radians)) {
    auto render_degrees = d + degrees;

    GetRenderer()->DrawText((uint32_t)(adjust_x - (radius - (double_t)pos) * sin(DegreesToRadians(render_degrees))),
                            (uint32_t)(adjust_y + (radius - (double_t)pos) * cos(DegreesToRadians(render_degrees))),
                            compass_points[c]);
    c++;
  }

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  uint16_t step = 360 / 32;
  c = 0;
  uint16_t p = 0;

  for (uint16_t d = 0; d < 360; d += step) {
    double_t r = DegreesToRadians((uint16_t)(d + degrees));
    p = c % 4 ? 28 : 20;
    c++;
    GetRenderer()->MovePen((int32_t)((radius - 35) * cos(r)), (int32_t)(-(radius - 35) * sin(r)));
    GetRenderer()->DrawPen((int32_t)((radius - p) * cos(r)), (int32_t)(-(radius - p) * sin(r)), true);
  }

  // Heading (Goes under sight)
  GetRenderer()->Save();
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->Rotate(DegreesToRadians((uint16_t)weapon_azimuth));

  GetRenderer()->SetColourBackground(HMI_CYAN);
  if ((mode == widget::ModeEnum::kPpiClassicArrowWithSight) ||
      (mode == widget::ModeEnum::kPpiClassicArrowWithoutSight)) {
    GetRenderer()->SetColourForeground(HMI_BLACK);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRectangle(-4, -73, 8, 73, true);
  } else {
    GetRenderer()->SetColourForeground(HMI_CYAN);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRectangle(-1, -73, 3, 57, true);
  }
  GetRenderer()->Restore();

  // Mode zero has sight
  if ((mode == widget::ModeEnum::kPpiClassicTankWithSight) || (mode == widget::ModeEnum::kPpiClassicArrowWithSight)) {
    DrawSight(radius, render_sight_azimuth, angle);
  }

  GetRenderer()->Restore();
};

}  // namespace gva