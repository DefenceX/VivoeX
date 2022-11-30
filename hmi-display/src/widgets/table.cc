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
/// \brief This is a table widget object
///
/// \file table.cc
///

#include "table.h"

#include "src/screen_gva.h"

namespace gva {

WidgetTable::WidgetTable(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::KWidgetTypeTable), touch_(touch) {}

void WidgetTable::Draw() { DrawTable(table_); }

void WidgetTable::SetTable(GvaTable* table) { table_ = table; }

void WidgetTable::DrawTable(GvaTable* table) {
  uint32_t height = 19;
  uint32_t row = 0;
  uint32_t column = 0;

  GetRenderer()->SetLineThickness(ConfigData::GetInstance()->GetThemeTableBorderThickness(), LineType::kLineSolid);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightBold, table->fontname_, 12);
  GetRenderer()->SetColourBackground(gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

  for (row = 0; row < table->rows_; row++) {
    uint32_t offset = table->GetX();

    for (column = 0; column < table->row_[row].cells_; column++) {
      uint32_t pos = 0;
      uint32_t tmp = table->row_[row].widths_[column] * ((double)table->GetWidth() / 100);

      GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, table->row_[row].cell_[column].weight,
                                 table->fontname_, 12);

      GetRenderer()->SetColourForeground(table->row_[row].cell_[column].foreground.red,
                                         table->row_[row].cell_[column].foreground.green,
                                         table->row_[row].cell_[column].foreground.blue);
      GetRenderer()->SetColourBackground(table->row_[row].cell_[column].background.red,
                                         table->row_[row].cell_[column].background.green,
                                         table->row_[row].cell_[column].background.blue);
      GetRenderer()->DrawRectangle(offset, table->GetY() - (height * row), tmp, height, true);

      GetRenderer()->DrawColor(table->row_[row].cell_[column].textcolour.red,
                               table->row_[row].cell_[column].textcolour.green,
                               table->row_[row].cell_[column].textcolour.blue);

      uint32_t w = GetRenderer()->GetTextWidth(table->row_[row].cell_[column].text, 12);

      switch (table->row_[row].cell_[column].align) {
        case widget::CellAlignType::kAlignCentre:
          pos = offset + (tmp / 2 - w / 2);
          break;
        case widget::CellAlignType::kAlignRight:
          pos = offset + (tmp - w - 4);
          break;
        case widget::CellAlignType::kAlignLeft:
        default:
          pos = offset + 4;
          break;
      }
      GetRenderer()->SetTextFontSize(12);
      GetRenderer()->DrawText(pos, table->GetY() - (height * row) + 5, table->row_[row].cell_[column].text);
      offset += tmp;
    }
  }
}

// Class CellType

WidgetTable::CellType::CellType(const std::string text, const uint32_t width, const uint32_t background_colour,
                                const uint32_t foreground_colour, const uint32_t outline_colour,
                                const uint32_t highlight_colour, const widget::CellAlignType alignment)
    : width_(width),
      text_(text),
      background_colour_(background_colour),
      foreground_colour_(foreground_colour),
      outline_colour_(outline_colour),
      highlight_colour_(highlight_colour),
      alignment_(alignment) {
  return;
}

uint32_t WidgetTable::CellType::GetWidth() const { return width_; }

std::string WidgetTable::CellType::GetText() const { return text_; }

uint32_t WidgetTable::CellType::GetForegroundColour() const { return foreground_colour_; }

uint32_t WidgetTable::CellType::GetBackgroundColour() const { return foreground_colour_; }

uint32_t WidgetTable::CellType::GetOutlineColour() const { return foreground_colour_; }

uint32_t WidgetTable::CellType::GetHighlightColour() const { return foreground_colour_; }

widget::CellAlignType WidgetTable::CellType::GetCellAlignment() const { return alignment_; }

// Class RowType

WidgetTable::RowType::RowType(const uint32_t background_colour, const uint32_t foreground_colour,
                              const uint32_t outline_colour, const uint32_t highlight_colour,
                              const widget::WeightType font_weight, const bool highlighted,
                              const widget::CellAlignType alignment)
    : background_colour_(background_colour),
      foreground_colour_(foreground_colour),
      outline_colour_(outline_colour),
      highlight_colour_(highlight_colour),
      font_weight_(font_weight),
      highlighted_(highlighted),
      alignment_(alignment) {}

uint32_t WidgetTable::RowType::GetForegroundColour() const { return foreground_colour_; }

uint32_t WidgetTable::RowType::GetBackgroundColour() const { return foreground_colour_; }

uint32_t WidgetTable::RowType::GetOutlineColour() const { return foreground_colour_; }

uint32_t WidgetTable::RowType::GetHighlightColour() const { return foreground_colour_; }

widget::WeightType WidgetTable::RowType::GetFontWeight() const { return font_weight_; }

bool WidgetTable::RowType::GetHighlighted() const { return highlighted_; }

void WidgetTable::RowType::SetHighlighted(bool value) { highlighted_ = value; }

widget::CellAlignType WidgetTable::RowType::GetCellAlignment() const { return alignment_; }

// Class TableWidget

void WidgetTable::AddRow(uint32_t forground_colour, uint32_t background_colour, uint32_t outline_colour,
                         uint32_t highlight_colour, widget::WeightType font_weight) {
  RowType row(background_colour, forground_colour, outline_colour, highlight_colour, font_weight, false,
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
  AddRow(ConfigData::GetInstance()->GetTableBackground(), Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_WHITE),
         Renderer::PackRgb(HMI_YELLOW), font_weight);
}

void WidgetTable::CurrentRowHighlight() { rows_[current_row_ - 1].SetHighlighted(true); }

void WidgetTable::AddCell(std::string text, uint32_t width) { AddCell(text, width, widget::CellAlignType::kAlignLeft); }

void WidgetTable::AddCell(std::string text, uint32_t width, widget::CellAlignType align) {
  AddCell(text, width, align, ConfigData::GetInstance()->GetTableBackground());
}

void WidgetTable::AddCell(std::string text, uint32_t width, uint32_t background_colour) {
  AddCell(text, width, widget::CellAlignType::kAlignLeft, background_colour);
}

void WidgetTable::AddCell(std::string text, uint32_t width, widget::CellAlignType align, uint32_t background_colour) {
  auto row = rows_.back();
  if (rows_.size()) {
    CellType cell(text, width, row.GetBackgroundColour(), row.GetForegroundColour(), row.GetOutlineColour(),
                  row.GetHighlightColour(), align);
    row.cells_.push_back(cell);
  } else {
    logGva::log("[GVA] No rows could be found when adding new cell.", LOG_ERROR);
  }
}

void WidgetTable::Reset() {
  visible_ = false;
  rows_.clear();
}

}  // namespace gva