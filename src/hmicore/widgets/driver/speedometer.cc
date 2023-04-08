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

  GetRenderer()->DrawColor(HMI_WHITE);

  // Compass
  GetRenderer()->SetColourBackground(HMI_BLACK);
  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetLineThickness(2, LineType::kLineSolid);
  GetRenderer()->DrawCircle(0, 0, radius, true);  // Compass

  int16_t p = 28;
  uint32_t adjust_x = -8;
  uint32_t adjust_y = -4;
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

  GetRenderer()->SetColourBackground(HMI_CYAN);
  GetRenderer()->SetColourForeground(HMI_BLACK);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->DrawRectangle(-4, +12, 4, 76, true);

  GetRenderer()->Restore();
};

}  // namespace gva