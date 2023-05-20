//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file speedometer.cc
///

#include "hmicore/widgets/driver/speedometer.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "hmicore/gva_functions_common.h"
#include "hmicore/renderer_gva.h"

namespace gva {

WidgetDriverSpeedometer::WidgetDriverSpeedometer(const RendererGva& renderer)
    : WidgetX(renderer, widget::WidgetEnum::kWidgetTypeDialSpeedometer) {
  SetVisible(false);
}

void WidgetDriverSpeedometer::Draw() {
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

  GetRenderer()->DrawColor(kHmiWhite);

  // Compass
  GetRenderer()->SetColourBackground(kHmiBlack);
  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, radius, true);  // Compass

  int16_t p = 28;
  uint32_t adjust_x = -8;
  uint32_t adjust_y = +4;
  uint16_t step = 360 / 16;
  int64_t c = 0;
  for (uint16_t d = 0; d <= 270; d += step) {
    double_t r = DegreesToRadians(d + 225);
    if (c * 10 > 99) adjust_x = 0 - 15;
    GetRenderer()->DrawText((uint32_t)(adjust_x + ((radius - p) * sin(r))),
                            (uint32_t)(adjust_y + (-(radius - p) * cos(r))), std::to_string(c * 10));
    c++;
  }
  // Digital speed
  if (mode_ == widget::DialType::kDialSpeedKph) {
    GetRenderer()->DrawText(-30, 40, std::to_string(value_) + " Km/h");
  }

  if (mode_ == widget::DialType::kDialSpeedMph) {
    GetRenderer()->DrawText(-30, 40, std::to_string(value_) + " Mph");
  }

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  c = 0;
  step = 360 / 64;
  for (uint16_t d = 0; d <= 270; d += step) {
    double_t radians = DegreesToRadians(d + 225);
    p = c % 4 ? 10 : 15;
    c++;
    GetRenderer()->MovePen((uint32_t)(+(radius - p) * sin(radians)), (uint32_t)(-(radius - p) * cos(radians)));
    GetRenderer()->DrawPen((uint32_t)(+radius * sin(radians)), (uint32_t)(-radius * cos(radians)), true);
  }

  // Heading (Goes under sight)
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->Rotate(DegreesToRadians((uint16_t)(45 + (value_ * 2.23))));

  GetRenderer()->SetColourBackground(kHmiCyan);
  GetRenderer()->SetColourForeground(kHmiBlack);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->DrawRectangle(-4, +12, 4, 76, true);

  GetRenderer()->Restore();
};

}  // namespace gva
