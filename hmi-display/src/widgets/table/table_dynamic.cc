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
/// \file table_dynamic.cc
///

#include "src/widgets/table/table_dynamic.h"

#include "src/screen_gva.h"

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
  SetRows(dynamic_rows_);
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
    logGva::log("[GVA] No rows could be found when adding new cell.", DebugLevel::kLogError);
  }
}

void WidgetTableDynamic::SetHideOverride(bool hide) { hide_override_ = hide; }

}  // namespace gva