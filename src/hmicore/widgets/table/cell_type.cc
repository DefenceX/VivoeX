//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file cell_type.cc
///

#include "hmicore/widgets/table/cell_type.h"
#include <string>
#include <string_view>
#include <stdint.h>

// Class CellType

namespace gva {

CellType::CellType(const std::string text, const uint32_t width, const uint32_t background_colour,
                   const uint32_t foreground_colour, const uint32_t outline_colour, const uint32_t highlight_colour,
                   const widget::CellAlignType alignment)
    : width_(width),
      text_(text),
      background_colour_(background_colour),
      foreground_colour_(foreground_colour),
      outline_colour_(outline_colour),
      highlight_colour_(highlight_colour),
      alignment_(alignment) {
  return;
}

CellType::CellType(const CellType &a)
    : width_(a.width_),
      text_(a.text_),
      background_colour_(a.background_colour_),
      foreground_colour_(a.foreground_colour_),
      outline_colour_(a.outline_colour_),
      highlight_colour_(a.highlight_colour_),
      alignment_(a.alignment_) {}

CellType &CellType::operator=(const CellType &a) {
  width_ = a.width_;
  text_ = a.text_;
  background_colour_ = a.background_colour_;
  foreground_colour_ = a.foreground_colour_;
  outline_colour_ = a.outline_colour_;
  highlight_colour_ = a.highlight_colour_;
  alignment_ = a.alignment_;
  return *this;
}

uint32_t CellType::GetWidth() const { return width_; }

std::string CellType::GetText() const { return text_; }

void CellType::SetText(std::string_view text) { text_ = text; }

uint32_t CellType::GetForegroundColour() const { return foreground_colour_; }

uint32_t CellType::GetBackgroundColour() const { return background_colour_; }

uint32_t CellType::GetOutlineColour() const { return foreground_colour_; }

uint32_t CellType::GetHighlightColour() const { return highlight_colour_; }

widget::CellAlignType CellType::GetCellAlignment() const { return alignment_; }

}  // namespace gva
