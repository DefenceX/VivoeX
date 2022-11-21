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

namespace gva {

TableWidget::CellType::CellType(const uint32_t width, const std::string &text, const uint32_t background_colour,
                                const uint32_t foreground_colour, const uint32_t outline_colour,
                                const uint32_t highlight_colour, const CellAlignType alignment)
    : width_(width),
      background_colour_(background_colour),
      foreground_colour_(foreground_colour),
      outline_colour_(outline_colour),
      highlight_colour_(highlight_colour),
      alignment_(alignment) {}

TableWidget::RowType::RowType(const uint32_t background_colour, const uint32_t foreground_colour,
                              const uint32_t outline_colour, const uint32_t highlight_colour,
                              const WeightType font_weight, const bool highlighted, const CellAlignType alignment)
    : background_colour_(background_colour),
      foreground_colour_(foreground_colour),
      outline_colour_(outline_colour),
      highlight_colour_(highlight_colour),
      font_weight_(font_weight),
      highlighted_(highlighted),
      alignment_(alignment) {}

void TableWidget::AddRow(uint32_t forground_colour, uint32_t background_colour, uint32_t outline_colour,
                         uint32_t highlight_colour, WeightType font_weight) {
  RowType row(background_colour, forground_colour, outline_colour, highlight_colour, font_weight, false,
              CellAlignType::kAlignLeft);
  rows_.push_back(row);
}

void TableWidget::AddRow() {
  RowType row(ConfigData::GetInstance()->GetTableBackground(), Renderer::PackRgb(HMI_WHITE),
              Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_YELLOW), WeightType::kWeightNormal, false,
              CellAlignType::kAlignLeft);
  rows_.push_back(row);
}

void TableWidget::AddRow(WeightType font_weight) {
  AddRow(ConfigData::GetInstance()->GetTableBackground(), Renderer::PackRgb(HMI_WHITE), Renderer::PackRgb(HMI_WHITE),
         Renderer::PackRgb(HMI_YELLOW), font_weight);
}

void TableWidget::CurrentRowHighlight() { rows_[row_count_ - 1].highlighted_ = true; }

void TableWidget::AddCell(std::string text, uint32_t width) { AddCell(text, width, CellAlignType::kAlignLeft); }

void TableWidget::AddCell(std::string text, uint32_t width, CellAlignType align) {
  AddCell(text, width, align, ConfigData::GetInstance()->GetTableBackground());
}

void TableWidget::AddCell(std::string text, uint32_t width, uint32_t background_colour) {
  AddCell(text, width, CellAlignType::kAlignLeft, background_colour);
}

void TableWidget::AddCell(std::string text, uint32_t width, CellAlignType align, uint32_t background_colour) {
  auto row = rows_.end();
  CellType cell(width, text, row->background_colour_, row->foreground_colour_, row->outline_colour_,
                row->highlight_colour_, align);
  row->cells_.push_back(cell);
}

void TableWidget::Reset() {
  visible_ = false;
  rows_.clear();
}

}  // namespace gva