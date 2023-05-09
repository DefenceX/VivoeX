//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file row_type.cc
///

#include "hmicore/widgets/table/row_type.h"

#include <algorithm>

#include "hmicore/widgets/widget_types.h"

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

bool RowType::operator<(const RowType &a) const {
  if ((a.cells_.size() >= 3) && (this->cells_.size() >= 3)) {
    if ((a.cells_[2].GetText() == "A") && ((this->cells_[2].GetText() == "W") || (this->cells_[2].GetText() == "C")))
      return true;
    if ((a.cells_[2].GetText() == "B") && (this->cells_[2].GetText() == "C")) return true;
  }
  return false;
}

bool RowType::operator>(const RowType &a) const {
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