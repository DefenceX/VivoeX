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
/// \file table_dynamic.cc
///

#include "hmicore/widgets/table/table_dynamic.h"

#include <glog/logging.h>

#include "hmicore/events_gva.h"

namespace gva {

WidgetTableDynamic::WidgetTableDynamic(const RendererGva& renderer, TouchGva* touch, uint32_t background_colour)
    : WidgetTable(renderer, touch, background_colour) {
  WidgetTable::Reset();
  SetCurrentRow(1);
}

void WidgetTableDynamic::AddRow(uint32_t foreground_colour, uint32_t background_colour, uint32_t outline_colour,
                                uint32_t highlight_colour, widget::WeightType font_weight) {
  RowType row(background_colour, foreground_colour, outline_colour, highlight_colour, font_weight, false,
              widget::CellAlignType::kAlignLeft);
  dynamic_rows_.push_back(row);
}

void WidgetTableDynamic::Draw() {
  dynamic_rows_filtered_.clear();
  if (hide_override_) {
    for (auto row : dynamic_rows_) {
      auto cells = *row.GetCells();
      if (cells.size() >= 3) {
        if (gva::CellType cell = cells[3]; cell.GetText().find("OVR") == std::string::npos) {
          dynamic_rows_filtered_.push_back(row);
        }
      } else {                                  // short rows
        dynamic_rows_filtered_.push_back(row);  // Other rows just copy
      }
    }
  } else {
    dynamic_rows_filtered_ = dynamic_rows_;
  }

  // Do any sorting
  if (sorted_ == SortType::kSortDescending) {
    std::sort(dynamic_rows_filtered_.begin(), dynamic_rows_filtered_.end());
  }
  if (sorted_ == SortType::kSortAscending) {
    std::sort(dynamic_rows_filtered_.begin(), dynamic_rows_filtered_.end(), std::greater<>());
  }
  SetRows(dynamic_rows_filtered_);

  WidgetTable::Draw();
}

void WidgetTableDynamic::AddRow() {
  RowType row(ConfigData::GetInstance()->GetTableBackground(), Renderer::PackRgb(HMI_WHITE),
              Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal, false,
              widget::CellAlignType::kAlignLeft);
  dynamic_rows_.push_back(row);
}

void WidgetTableDynamic::AddRow(widget::WeightType font_weight) {
  AddRow(Renderer::PackRgb(HMI_WHITE), ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled(),
         Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_YELLOW), font_weight);
}

void WidgetTableDynamic::AddCell(const std::string text, uint32_t width) {
  AddCell(text, width, widget::CellAlignType::kAlignLeft);
}

void WidgetTableDynamic::AddCell(const std::string text, uint32_t width, widget::CellAlignType align) {
  AddCell(text, width, align, 0);
}

void WidgetTableDynamic::AddCell(const std::string text, uint32_t width, uint32_t background_colour) {
  AddCell(text, width, widget::CellAlignType::kAlignLeft, background_colour);
}

void WidgetTableDynamic::AddCell(const std::string text, uint32_t width, widget::CellAlignType align,
                                 uint32_t background_colour) {
  if (dynamic_rows_.size()) {
    CellType cell(text, width, background_colour, foreground_colour_, outline_colour_, highlight_colour_, align);
    dynamic_rows_.back().GetCells()->push_back(cell);
  } else {
    LOG(ERROR) << "[GVA] No rows could be found when adding new cell.";
  }
}

void WidgetTableDynamic::SetHideOverride(bool hide) {
  if (hide != hide_override_) {
    hide_override_ = hide;
    // Force repaint of the screen
    gva::EventsGva::CreateRefreshEvent();
  }
}

bool WidgetTableDynamic::GetHideOverride() const { return hide_override_; }

void WidgetTableDynamic::SetSorted(SortType sort) {
  if (sort != sorted_) {
    sorted_ = sort;
    gva::EventsGva::CreateRefreshEvent();
  }
}

WidgetTableDynamic::SortType WidgetTableDynamic::GetSorted() const { return sorted_; }

void WidgetTableDynamic::SetAllHighlighted(bool highlight_all) {
  bool first_row = true;
  highlight_all_ = highlight_all;

  // Loop through rows to set or unset highlight attribute
  for (auto& row : dynamic_rows_) {
    auto cells = *row.GetCells();
    if (first_row == false) {
      if (highlight_all_) {  // First row is the headers and not for highlighting
        row.SetHighlighted(true);
      } else {
        row.SetHighlighted(false);
      }
    }  // skip header row
    first_row = false;
  }  // end for loop on rows
  gva::EventsGva::CreateRefreshEvent();
}

bool WidgetTableDynamic::GetAllHighlighted() const { return highlight_all_; }

}  // namespace gva