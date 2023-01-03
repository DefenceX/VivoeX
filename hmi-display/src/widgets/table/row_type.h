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
/// \file row_type.h
///

#ifndef HMI_DISPLAY_SRC_WIDGETS_TABLE_ROW_TYPE_H_
#define HMI_DISPLAY_SRC_WIDGETS_TABLE_ROW_TYPE_H_

#include <string>
#include <vector>

#include "src/widgets/table/cell_type.h"
#include "src/widgets/widget_types.h"

namespace gva {

///
/// \brief This is the class describing a TableWidget row
///
///
class RowType {
 public:
  RowType() = default;
  ~RowType() = default;
  RowType(const uint32_t background_colour, const uint32_t foreground_colour, const uint32_t outline_colour,
          const uint32_t highlight_colour, const widget::WeightType font_weight, const bool highlighted,
          const widget::CellAlignType alignment);
  RowType(const RowType &a);
  RowType &operator=(const RowType &a);

  ///
  /// \brief Sorting is based on priority then time
  ///
  ///
  bool operator<(RowType &a) const;

  bool operator>(RowType &a) const;

  ///
  /// \brief Get the Foreground Colour
  ///
  /// \return uint32_t
  ///
  uint32_t GetForegroundColour() const;

  ///
  ///  \brief Get the Background Colour
  ///
  ///  \return uint32_t
  ///
  uint32_t GetBackgroundColour() const;

  ///
  /// \brief Get the Outline Colour
  ///
  /// \return uint32_t
  ///
  uint32_t GetOutlineColour() const;

  ///
  /// \brief Get the Highlight Colour
  ///
  /// \return uint32_t
  ///
  uint32_t GetHighlightColour() const;

  ///
  /// \brief Get the Font Weight object
  ///
  /// \return widget::WeightType
  ///
  widget::WeightType GetFontWeight() const;

  ///
  /// \brief Get the Highlighted object
  ///
  /// \return true
  /// \return false
  ///
  bool GetHighlighted() const;

  ///
  /// \brief Set the Highlighted flag
  ///
  /// \param value
  ///
  void SetHighlighted(bool value);

  ///
  /// \brief Get the Cell Alignment object
  ///
  /// \return CellAlignType
  ///
  widget::CellAlignType GetCellAlignment() const;

  ///
  /// \brief Get a reference to the Cells vector for this row
  ///
  /// \return std::vector<CellType>&
  ///
  std::vector<CellType> *GetCells() { return &cells_; }

 private:
  std::vector<CellType> cells_;
  uint32_t background_colour_ = 0;
  uint32_t foreground_colour_ = 0;
  uint32_t outline_colour_ = 0;
  uint32_t highlight_colour_ = 0;
  widget::WeightType font_weight_ = widget::WeightType::kWeightNormal;
  bool highlighted_;
  widget::CellAlignType alignment_ = widget::CellAlignType::kAlignLeft;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_TABLE_ROW_TYPE_H_
