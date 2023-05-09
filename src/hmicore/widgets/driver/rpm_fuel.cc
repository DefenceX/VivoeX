//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file rpm_fuel.cc
///

#include "hmicore/widgets/driver/rpm_fuel.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "hmicore/gva_functions_common.h"
#include "hmicore/renderer_gva.h"

namespace gva {

WidgetDriverRpmFuel::WidgetDriverRpmFuel(const RendererGva& renderer)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeDialRpmFuel) {
  SetVisible(false);
}

void WidgetDriverRpmFuel::Draw() {
  uint16_t radius = 100;
  const uint32_t font_size = 14;

  // Check to see if we need to be rendered
  if (!GetVisible()) {
    return;
  }

  // Set the font for all compass/s
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             gva::ConfigData::GetInstance()->GetThemeFont(), font_size);

  GetRenderer()->Save();
  GetRenderer()->Scale(0.5, 0.5);
  GetRenderer()->Translate(GetX(), GetY());

  GetRenderer()->DrawColor(HMI_WHITE);

  // Compass
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, radius, true);  // Compass

  int64_t p = 28;
  uint32_t adjust_x = -8;
  uint32_t adjust_y = +4;
  uint16_t step = 360 / 12;
  int64_t c = 0;
  for (uint16_t d = 0; d <= 270; d += step) {
    double_t radians = DegreesToRadians(d + 225);

    if (c * 10 > 99) adjust_x = 0 - 15;
    GetRenderer()->DrawText((uint32_t)(adjust_x + (double_t)(radius - p) * sin(radians)),
                            (uint32_t)(adjust_y - (double_t)(radius - p) * cos(radians)), std::to_string(c));
    c++;
  }

  // Gears
  GetRenderer()->DrawText(-16, 60, "RPM");
  GetRenderer()->DrawText(-20, 40, "Drive");

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  c = 0;
  step = 360 / 120;
  for (uint16_t d = 0; d <= 270; d += step) {
    double_t radians = DegreesToRadians(d + 225);
    p = c % 10 ? 8 : 14;
    if ((c > 69) && (p != 14)) {
      GetRenderer()->SetColourForeground(HMI_RED);
      GetRenderer()->DrawColor(HMI_RED);
    } else {
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->DrawColor(HMI_WHITE);
    }
    c++;
    GetRenderer()->MovePen((uint32_t)(+(double_t)(radius - p) * sin(radians)),
                           (uint32_t)(-(double_t)(radius - p) * cos(radians)));
    GetRenderer()->DrawPen((uint32_t)(+(double_t)(radius)*sin(radians)), (uint32_t)(-(double_t)(radius)*cos(radians)),
                           true);
  }

  GetRenderer()->SetColourForeground(HMI_WHITE);

  // Dial
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->Rotate(DegreesToRadians((uint16_t)(45 + (value_ * 0.03))));

  GetRenderer()->SetColourBackground(HMI_CYAN);
  GetRenderer()->SetColourForeground(HMI_BLACK);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->DrawRectangle(-4, +12, 4, 76, true);

  GetRenderer()->Restore();
};

}  // namespace gva