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
/// \brief The alarms indicator
///
/// \file alarms_indicator.cc
///

#include "alarm_indicator.h"

#include "src/screen_gva.h"

namespace gva {

void AlarmIndicator::Draw() {
  if (GetVisible()) {
    screen_->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightNormal,
                         gva::ConfigData::GetInstance()->GetThemeFont());
    screen_->SetColourBackground(HMI_RED);
    screen_->SetColourForeground(HMI_WHITE);
    screen_->DrawRoundedRectangle(110, 32, 420, 20, 6, true);
    screen_->DrawColor(HMI_WHITE);
    uint16_t width = screen_->GetTextWidth(text_, 14);
    screen_->DrawText(110 + (420 / 2) - (width / 2), 38, text_, 14);
    screen_->SetColourBackground(HMI_RED);
    screen_->SetColourForeground(HMI_WHITE);
    screen_->DrawColor(HMI_WHITE);
    screen_->DrawRoundedRectangle(110 + (420 / 2) + (width / 2) + 4, 34, 19, 16, 4, true);
    //      screen_->DrawIcon(ICON_ERROR, 110 + (420 / 2) + (width / 2) + 16, 42, 12, 12);
  }
}

}  // namespace gva