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

#include "screen_gva.h"

namespace gva {

void AlarmIndicator::Draw() {
  if (GetVisible()) {
    GvaTable table(104, GetY(), 432);
    table.SetFontName(gva::ConfigData::GetInstance()->GetThemeFont());
    GvaRow alarmrow;
    GvaCellType cell = {text_, ALIGN_CENTRE, {HMI_WHITE}, {HMI_RED}, {HMI_WHITE}, WEIGHT_NORMAL};
    table.border_ = 0;
    alarmrow.addCell(cell, 100);
    table.AddRow(alarmrow);
    screen_->DrawTable(&table);
  }
}

}  // namespace gva