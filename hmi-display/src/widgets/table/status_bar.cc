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
/// \file status_bar.cc
///

#include "src/widgets/table/status_bar.h"

#include <glog/logging.h>

#include "src/events_gva.h"

namespace gva {

WidgetStatusBar::WidgetStatusBar(const RendererGva &renderer, TouchGva *touch) : WidgetTable(renderer, touch) {
  WidgetTable::Reset();
  SetCurrentRow(1);
  labels_[0].text = "00:00:00 01/01/1973";
  labels_[1].text = "Norm.";
  labels_[2].text = "Lat:0.000000 Lon:-0.000000";
  labels_[3].text = "W:" + std::to_string(warnings_);
  labels_[4].text = "A:" + std::to_string(advisories_);
  labels_[5].text = "C:" + std::to_string(cautions_);
  labels_[6].text = "O:" + std::to_string(overrides_);
}

void WidgetStatusBar::Draw() {
  // Setup and Draw the status bar, one row table
  if (GetVisible()) {
    SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

    // Setup and Draw the status bar, one row table
    std::array<uint32_t, 7> widths = {23, 8, 37, 8, 8, 8, 8};
    SetX(1);
    SetWidth(640);
    SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

    // Update the rows and cells
    Reset();
    AddRow();

    for (uint32_t i = 0; i < 7; i++) {
      AddCell(labels_[i].text, widths[i], widget::CellAlignType::kAlignLeft);
    }
    WidgetTable::Draw();
  }
}

void WidgetStatusBar::UpdateClock(std::string_view clock_string) { labels_[0].text = clock_string; }

void WidgetStatusBar::UpdateLocation(std::string_view location) { labels_[2].text = location; }

void WidgetStatusBar::UpdateLocationFormat(std::string_view location_format) { labels_[1].text = location_format; }

}  // namespace gva