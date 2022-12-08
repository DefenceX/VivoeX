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
/// \file rpm_fuel.cc
///

#include "src/widgets/driver/rpm_fuel.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "src/gva_functions_common.h"
#include "src/renderer_gva.h"

namespace gva {

WidgetDriverRpmFuel::WidgetDriverRpmFuel(const RendererGva& renderer)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeDialRpmFuel) {
  SetVisible(false);
}

void WidgetDriverRpmFuel::Draw() {
  double_t radius = 100;
  double_t d = 0;
  const uint32_t font_size = 14;

  // Check to see if we need to be rendered
  if (!GetVisible()) {
    return;
  }

  // Degrees north
  double degrees = 0;

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

  d = DegreesToRadians(degrees);
  int64_t p = 28;
  uint32_t adjust_x = -8;
  uint32_t adjust_y = +4;
  double step = (M_PI * 2) / 12;
  int64_t c = 0;
  for (d = DegreesToRadians(degrees) + (M_PI * 1.25); d >= DegreesToRadians(-45); d -= step) {
    if (c * 10 > 99) adjust_x = 0 - 15;
    GetRenderer()->DrawText((uint32_t)(adjust_x + (radius - p) * cos(d)), (uint32_t)(adjust_y - (radius - p) * sin(d)),
                            std::to_string(c));
    c++;
  }

  // Gears
  GetRenderer()->DrawText(-16, 60, "RPM");
  GetRenderer()->DrawText(-20, 40, "Drive");

  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  c = 0;
  d = degrees;
  step = (M_PI * 2) / 120;
  for (d = DegreesToRadians(degrees) + (M_PI * 1.25); d >= DegreesToRadians(-45); d -= step) {
    p = c % 10 ? 8 : 14;
    if ((c > 69) && (p != 14)) {
      GetRenderer()->SetColourForeground(HMI_RED);
      GetRenderer()->DrawColor(HMI_RED);
    } else {
      GetRenderer()->SetColourForeground(HMI_WHITE);
      GetRenderer()->DrawColor(HMI_WHITE);
    }
    c++;
    GetRenderer()->MovePen((uint32_t)(+(radius - p) * cos(d)), (uint32_t)(-(radius - p) * sin(d)));
    GetRenderer()->DrawPen((uint32_t)(+(radius)*cos(d)), (uint32_t)(-(radius)*sin(d)), true);
  }
  GetRenderer()->SetColourForeground(HMI_WHITE);

  // Dial
  GetRenderer()->MovePen(0, 0);
  GetRenderer()->Rotate(DegreesToRadians(45 + (value_ * 0.03)));

  GetRenderer()->SetColourBackground(HMI_CYAN);
  GetRenderer()->SetColourForeground(HMI_BLACK);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  GetRenderer()->DrawRectangle(-4, +12, 4, 76, true);

  GetRenderer()->Restore();
};

}  // namespace gva