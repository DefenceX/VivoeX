//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file plan_position_indicator.cc
///

#include "hmicore/widgets/plan_position_indicator.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include <map>

#include "hmicore/gva_functions_common.h"
#include "hmicore/renderer_gva.h"

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
void WidgetPlanPositionIndicator::DrawModern(int32_t x, int32_t y, int16_t degrees, int16_t sightAzimuth,
                                             int16_t weaponAzimuth [[maybe_unused]], bool sight) const {
  double_t radius = 100;
  const uint32_t font_size = 14;

  // Set the font for all compass/s
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             gva::ConfigData::GetInstance()->GetThemeFont(), font_size);

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);
  GetRenderer()->Translate(x, y);
  GetRenderer()->DrawColor(kHmiWhite);

  // Compass
  GetRenderer()->SetColourBackground(kHmiGrey);
  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, (uint32_t)radius, true);  // Compass outline
  GetRenderer()->SetColourBackground(kHmiBlack);
  GetRenderer()->DrawCircle(0, 0, 80, true);  // Inner circle

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  uint32_t step = 360 / 12;

  for (uint32_t d = 0; d <= 360; d += step) {
    double_t r = DegreesToRadians((int16_t)(d + 15 + degrees % 30));
    GetRenderer()->MovePen((int32_t)((radius - 20) * sin(r)), (int32_t)(-(radius - 20) * cos(r)));
    GetRenderer()->DrawPen((int32_t)(radius * sin(r)), (int32_t)(-radius * cos(r)), true);
  }

  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont(), font_size);

  // Draw Text markers
  int32_t adjust_x = -8;
  int32_t adjust_y = 4;
  int64_t c = 0;
  std::array<std::string, 4> compass_points = {"N", "E", "S", "W"};
  step = 360 / 4;
  for (uint16_t d = 0; d < 360; d += step) {
    double_t r = DegreesToRadians((uint16_t)(d + degrees));

    GetRenderer()->DrawText((int32_t)(adjust_x + ((radius - 9) * sin(r))),
                            (int32_t)(adjust_y + (-(radius - 9) * cos(r))), compass_points[c]);
    c++;
  }

  // Vehicle outline
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
  GetRenderer()->Save();
  GetRenderer()->DrawColor(kHmiWhite);
  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetColourBackground(kHmiGrey);
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
  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetColourBackground(kHmiGrey);
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
    GetRenderer()->SetColourBackground(kHmiCyan);
    GetRenderer()->DrawTriangle(0, 0, -8, -16, 6, -16, true);
    GetRenderer()->SetColourBackground(kHmiDarkBlue);
    GetRenderer()->SetColourForeground(kHmiDarkBlue);
    GetRenderer()->DrawTriangle(0, 0, -3, -15, 1, -15, true);
    GetRenderer()->Restore();
  }
  GetRenderer()->Restore();
}

void WidgetPlanPositionIndicator::DrawSight(double_t radius, int16_t render_sight_azimuth, double_t angle) const {
  int32_t x2 = 0;
  int32_t y2 = 0;

  // Sight
  GetRenderer()->SetColourBackground(kHmiWhite);
  GetRenderer()->SetColourForeground(kHmiWhite);
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

void WidgetPlanPositionIndicator::DrawPPI(widget::ModeEnum mode, int32_t x, int32_t y, int16_t degrees,
                                          int16_t sight_azimuth, int16_t weapon_azimuth [[maybe_unused]]) const {
  switch (mode) {
    case widget::ModeEnum::kPpiModernTankWithSights:
      DrawModern(x, y, degrees, sight_azimuth, 10, true);
      break;
    case widget::ModeEnum::kPpiModernTankWithoutSights:
      DrawModern(x, y, degrees, sight_azimuth, 10, false);
      break;
    default:
      DrawClassic(mode, x, y, degrees, sight_azimuth, 10);
      break;
  }
  DrawThreats();
}

void WidgetPlanPositionIndicator::DrawClassic(widget::ModeEnum mode, int32_t x, int32_t y, int16_t degrees,
                                              int16_t sight_azimuth, int16_t weapon_azimuth) const {
  double_t radius = 100;
  double_t angle = 45;
  const uint32_t font_size = 14;

  // Degrees north
  int16_t render_sight_azimuth = sight_azimuth;
  render_sight_azimuth = (render_sight_azimuth >= 360) ? render_sight_azimuth - 360 : render_sight_azimuth;

  // Set the font for all compass/s
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             gva::ConfigData::GetInstance()->GetThemeFont(), font_size);

  GetRenderer()->Save();
  GetRenderer()->Scale(scale_, scale_);
  GetRenderer()->Translate(x, y);

  GetRenderer()->DrawColor(kHmiWhite);

  // Compass
  GetRenderer()->SetColourBackground(kHmiBlack);
  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, (uint32_t)radius, true);  // Compass

  switch (mode) {
    case widget::ModeEnum::kPpiClassicArrowWithSight:
    case widget::ModeEnum::kPpiClassicArrowWithoutSight:
      // Vehicle outline
      GetRenderer()->Save();
      GetRenderer()->SetLineType(CAIRO_LINE_JOIN_MITER);
      GetRenderer()->SetColourForeground(kHmiWhite);
      GetRenderer()->SetColourBackground(kHmiWhite);
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
      GetRenderer()->SetColourForeground(kHmiWhite);
      GetRenderer()->SetColourBackground(kHmiWhite);
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
  int32_t adjust_x = -5;
  int32_t adjust_y = 4;
  int64_t c = 0;
  std::array<std::string, 4> compass_points = {"N", "E", "S", "W"};

  uint16_t step = 360 / 4;
  for (uint16_t d = 0; d < 360; d += step) {
    double_t r = DegreesToRadians((uint16_t)(d + degrees));

    GetRenderer()->DrawText((int32_t)(adjust_x + ((radius - 12) * sin(r))),
                            (int32_t)(adjust_y + (-(radius - 12) * cos(r))), compass_points[c]);
    c++;
  }

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  step = 360 / 40;
  c = 0;
  int16_t p = 0;

  for (uint16_t d = 0; d < 360; d += step) {
    double_t r = DegreesToRadians((uint16_t)(d + degrees));
    p = c % 5 ? 28 : 20;
    c++;
    GetRenderer()->MovePen((int32_t)((radius - 35) * sin(r)), (int32_t)(-(radius - 35) * cos(r)));
    GetRenderer()->DrawPen((int32_t)((radius - p) * sin(r)), (int32_t)(-(radius - p) * cos(r)), true);
  }

  // Heading (Goes under sight)
  GetRenderer()->Save();
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->Rotate(DegreesToRadians(weapon_azimuth_));

  GetRenderer()->SetColourBackground(kHmiCyan);
  if ((mode == widget::ModeEnum::kPpiClassicArrowWithSight) ||
      (mode == widget::ModeEnum::kPpiClassicArrowWithoutSight)) {
    GetRenderer()->SetColourForeground(kHmiBlack);
    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
    GetRenderer()->DrawRectangle(-4, -73, 8, 73, true);
  } else {
    GetRenderer()->SetColourForeground(kHmiCyan);
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

void WidgetPlanPositionIndicator::AddThreat(int16_t id, ThreatType threat) {
  threats_[id] = std::make_shared<ThreatType>(threat);
};

void WidgetPlanPositionIndicator::DeleteThreat(int16_t id) { threats_.erase(id); };

void WidgetPlanPositionIndicator::DeleteAllThreats() { threats_.clear(); };

void WidgetPlanPositionIndicator::DrawThreats() const {
  for (auto& [id, threat_info] : threats_) {
    uint32_t angle1 = threat_info->bearing - (threat_info->size / 2);
    uint32_t angle2 = threat_info->bearing + (threat_info->size / 2);
    GetRenderer()->DrawColor(threat_info->rgb_value);
    GetRenderer()->SetLineThickness(4, LineType::kLineSolid);
    GetRenderer()->DrawArcRaw(GetX() / 2, GetY() / 2, (radius_ / 2) + 1, angle1, angle2);
  }
};

}  // namespace gva
