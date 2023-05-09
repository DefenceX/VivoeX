//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file status_bar.cc
///

#include "hmicore/widgets/table/status_bar.h"

#include <glog/logging.h>

#include "hmicore/events_gva.h"

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