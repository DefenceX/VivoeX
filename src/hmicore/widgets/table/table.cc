//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file table.cc
///

#include "table.h"

#include <glog/logging.h>

namespace gva {

WidgetTable::WidgetTable(const RendererGva& renderer, TouchGva* touch, uint32_t background_colour)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeTable), touch_(touch), background_colour_(background_colour) {}

void WidgetTable::Draw() { DrawTable(); }

void WidgetTable::DrawTable() {
  uint32_t height = 19;

  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeTableBorderThickness(), LineType::kLineSolid);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightBold,
                             ConfigData::GetInstance()->GetThemeFont(), 12);
  GetRenderer()->SetColourBackground(gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
  GetRenderer()->DrawColor(kHmiWhite);

  uint16_t row_count = 0;
  for (auto row : rows_) {
    uint32_t offset = GetX();

    for (auto column : *row.GetCells()) {
      uint32_t pos = 0;
      uint32_t cell_width = (float)(GetWidth() / (float)100) * column.GetWidth();  // As a percentage of thetable width

      GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, row.GetFontWeight(),
                                 ConfigData::GetInstance()->GetThemeFont(), 12);

      GetRenderer()->Save();
      GetRenderer()->SetColourForeground(outline_colour_);

      if (column.GetBackgroundColour()) {
        GetRenderer()->SetColourBackground(column.GetBackgroundColour());
      } else {
        GetRenderer()->SetColourBackground(row.GetBackgroundColour());
      }

      GetRenderer()->DrawRectangle(offset, (GetY() + (row_count * height)), cell_width, height, true);
      GetRenderer()->Restore();

      uint32_t w = GetRenderer()->GetTextWidth(column.GetText(), 12);

      switch (column.GetCellAlignment()) {
        case widget::CellAlignType::kAlignCentre:
          pos = offset + (cell_width / 2 - w / 2);
          break;
        case widget::CellAlignType::kAlignRight:
          pos = offset + (cell_width - w - 4);
          break;
        case widget::CellAlignType::kAlignLeft:
        default:
          pos = offset + 4;
          break;
      }
      GetRenderer()->DrawText(pos, (GetY() + ((row_count + 1) * height)) - 5, column.GetText());
      offset += cell_width;
    }
    row_count++;
  }
  // Highlight the selected row
  if (current_row_) {
    GetRenderer()->DrawColor(highlight_colour_);
    GetRenderer()->DrawRectangle(GetX(), (GetY() + (current_row_ * height)), GetWidth() - 1, height, false);
  }

  // Can have all rows highlighted so check those also
  int count = 1;
  for (auto row : rows_) {
    if ((row.GetHighlighted()) && (row.GetCells()->size() > 3)) {
      GetRenderer()->DrawColor(row.GetHighlightColour());
      GetRenderer()->DrawRectangle(GetX(), (GetY() + (count++ * height)), GetWidth() - 1, height, false);
    }
  }
}

void WidgetTable::AddRow(uint32_t foreground_colour, uint32_t background_colour, uint32_t outline_colour,
                         uint32_t highlight_colour, widget::WeightType font_weight) {
  RowType row(background_colour, foreground_colour, outline_colour, highlight_colour, font_weight, false,
              widget::CellAlignType::kAlignLeft);
  rows_.push_back(row);
}

void WidgetTable::AddRow() {
  RowType row(ConfigData::GetInstance()->GetTableBackground(), Renderer::PackRgb(kHmiWhite),
              Renderer::PackRgb(kHmiWhite), Renderer::PackRgb(kHmiYellow), widget::WeightType::kWeightNormal, false,
              widget::CellAlignType::kAlignLeft);
  rows_.push_back(row);
}

void WidgetTable::AddRow(widget::WeightType font_weight) {
  AddRow(Renderer::PackRgb(kHmiWhite), ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled(),
         Renderer::PackRgb(kHmiWhite), Renderer::PackRgb(kHmiYellow), font_weight);
}

void WidgetTable::AddCell(const std::string text, uint32_t width) {
  AddCell(text, width, widget::CellAlignType::kAlignLeft);
}

void WidgetTable::AddCell(const std::string text, uint32_t width, widget::CellAlignType align) {
  AddCell(text, width, align, 0);
}

void WidgetTable::AddCell(const std::string text, uint32_t width, uint32_t background_colour) {
  AddCell(text, width, widget::CellAlignType::kAlignLeft, background_colour);
}

void WidgetTable::AddCell(const std::string text, uint32_t width, widget::CellAlignType align,
                          uint32_t background_colour) {
  if (rows_.size()) {
    CellType cell(text, width, background_colour, foreground_colour_, outline_colour_, highlight_colour_, align);
    rows_.back().GetCells()->push_back(cell);
  } else {
    LOG(ERROR) << "[GVA] No rows could be found when adding new cell.";
  }
}

void WidgetTable::Reset() {
  current_row_ = 0;
  rows_.clear();
}

uint32_t WidgetTable::GetBackgroundColour() const { return background_colour_; }

void WidgetTable::SetBackgroundColour(uint32_t background_colour) { background_colour_ = background_colour; }

void WidgetTable::SetCurrentRow(uint32_t row) { current_row_ = row; }

void WidgetTable::SetNextRow() {
  if (current_row_ < rows_.size() - 2) current_row_++;
}

void WidgetTable::SetPreviousRow() {
  if (current_row_ > 1) current_row_--;
}

uint32_t WidgetTable::GetCurrentRow() const { return current_row_; }

std::vector<RowType>& WidgetTable::GetRows() { return rows_; }

void WidgetTable::SetRows(const std::vector<RowType>& rows) {
  rows_.clear();
  rows_ = rows;
}

}  // namespace gva