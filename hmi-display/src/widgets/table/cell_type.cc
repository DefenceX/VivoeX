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
/// \brief A class capturing all the cell attributes in a table
///
/// \file cell_type.cc
///

#include "src/widgets/table/cell_type.h"

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

uint32_t CellType::GetForegroundColour() const { return foreground_colour_; }

uint32_t CellType::GetBackgroundColour() const { return background_colour_; }

uint32_t CellType::GetOutlineColour() const { return foreground_colour_; }

uint32_t CellType::GetHighlightColour() const { return highlight_colour_; }

widget::CellAlignType CellType::GetCellAlignment() const { return alignment_; }

}  // namespace gva
