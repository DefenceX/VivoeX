//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
/// \file table.cc
///

#include "table.h"

#include "src/screen_gva.h"

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
  GetRenderer()->DrawColor(HMI_WHITE);

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
      GetRenderer()->SetColourBackground(row.GetBackgroundColour());
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
    GetRenderer()->DrawRectangle(GetX(), (GetY() + (current_row_ * height)), GetWidth(), height, false);
  }
}

void WidgetTable::AddRow(uint32_t foreground_colour, uint32_t background_colour, uint32_t outline_colour,
                         uint32_t highlight_colour, widget::WeightType font_weight) {
  RowType row(background_colour, foreground_colour, outline_colour, highlight_colour, font_weight, false,
              widget::CellAlignType::kAlignLeft);
  rows_.push_back(row);
}

void WidgetTable::AddRow() {
  RowType row(ConfigData::GetInstance()->GetTableBackground(), Renderer::PackRgb(HMI_WHITE),
              Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_YELLOW), widget::WeightType::kWeightNormal, false,
              widget::CellAlignType::kAlignLeft);
  rows_.push_back(row);
}

void WidgetTable::AddRow(widget::WeightType font_weight) {
  AddRow(Renderer::PackRgb(HMI_WHITE), ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled(),
         Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_YELLOW), font_weight);
}

void WidgetTable::AddCell(std::string text, uint32_t width) { AddCell(text, width, widget::CellAlignType::kAlignLeft); }

void WidgetTable::AddCell(std::string text, uint32_t width, widget::CellAlignType align) {
  AddCell(text, width, align, ConfigData::GetInstance()->GetTableBackground());
}

void WidgetTable::AddCell(std::string text, uint32_t width, uint32_t background_colour) {
  AddCell(text, width, widget::CellAlignType::kAlignLeft, background_colour);
}

void WidgetTable::AddCell(std::string text, uint32_t width, widget::CellAlignType align, uint32_t background_colour) {
  if (rows_.size()) {
    CellType cell(text, width, background_colour, foreground_colour_, outline_colour_, highlight_colour_, align);
    rows_.back().GetCells()->push_back(cell);
  } else {
    logGva::log("[GVA] No rows could be found when adding new cell.", DebugLevel::kLogError);
  }
}

void WidgetTable::Reset() {
  current_row_ = 0;
  SetVisible(false);
  rows_.clear();
}

}  // namespace gva