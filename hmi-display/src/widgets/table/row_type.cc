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
/// \file row_type.cc
///

#include "src/widgets/table/row_type.h"

#include <algorithm>

#include "src/widgets/widget_types.h"

namespace gva {

// Class RowType

RowType::RowType(const uint32_t background_colour, const uint32_t foreground_colour, const uint32_t outline_colour,
                 const uint32_t highlight_colour, const widget::WeightType font_weight, const bool highlighted,
                 const widget::CellAlignType alignment)
    : background_colour_(background_colour),
      foreground_colour_(foreground_colour),
      outline_colour_(outline_colour),
      highlight_colour_(highlight_colour),
      font_weight_(font_weight),
      highlighted_(highlighted),
      alignment_(alignment) {}

RowType::RowType(const RowType &a)
    : cells_(a.cells_),
      background_colour_(a.background_colour_),
      foreground_colour_(a.foreground_colour_),
      outline_colour_(a.outline_colour_),
      highlight_colour_(a.highlight_colour_),
      font_weight_(a.font_weight_),
      highlighted_(a.highlighted_),
      alignment_(a.alignment_) {}

RowType &RowType::operator=(const RowType &a) {
  background_colour_ = a.background_colour_;
  foreground_colour_ = a.foreground_colour_;
  outline_colour_ = a.outline_colour_;
  highlight_colour_ = a.highlight_colour_;
  font_weight_ = a.font_weight_;
  highlighted_ = a.highlighted_;
  alignment_ = a.alignment_;
  cells_.clear();
  for (auto cell : a.cells_) {
    cells_.push_back(cell);
  };
  return *this;
}

bool RowType::operator<(RowType &a) const {
  if ((a.cells_.size() >= 3) && (this->cells_.size() >= 3)) {
    if ((a.cells_[2].GetText() == "A") && ((this->cells_[2].GetText() == "W") || (this->cells_[2].GetText() == "C")))
      return true;
    if ((a.cells_[2].GetText() == "B") && (this->cells_[2].GetText() == "C")) return true;
  }
  return false;
}

bool RowType::operator>(RowType &a) const {
  if ((a.cells_.size() >= 3) && (this->cells_.size() >= 3)) {
    if ((a.cells_[2].GetText() == "W") && ((this->cells_[2].GetText() == "C") || (this->cells_[2].GetText() == "A")))
      return true;
    if ((a.cells_[2].GetText() == "C") && (this->cells_[2].GetText() == "A")) return true;
  }
  return false;
}

uint32_t RowType::GetForegroundColour() const { return foreground_colour_; }

uint32_t RowType::GetBackgroundColour() const { return background_colour_; }

uint32_t RowType::GetOutlineColour() const { return outline_colour_; }

uint32_t RowType::GetHighlightColour() const { return highlight_colour_; }

widget::WeightType RowType::GetFontWeight() const { return font_weight_; }

bool RowType::GetHighlighted() const { return highlighted_; }

void RowType::SetHighlighted(bool highlighted) { highlighted_ = highlighted; }

widget::CellAlignType RowType::GetCellAlignment() const { return alignment_; }

}  // namespace gva