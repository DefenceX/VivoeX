//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file row_type.h
///

#ifndef HMICORE_WIDGETS_TABLE_ROW_TYPE_H_
#define HMICORE_WIDGETS_TABLE_ROW_TYPE_H_

#include <string>
#include <vector>

#include "hmicore/widgets/table/cell_type.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

///
/// \brief This is the class describing a TableWidget row
///
///
class RowType {
 public:
  ///
  /// \brief Construct a new Row Type object
  ///
  ///
  RowType() = default;

  ///
  /// \brief Destroy the Row Type object
  ///
  ///
  ~RowType() = default;

  ///
  /// \brief Construct a new Row Type object
  ///
  /// \param background_colour The background colour of the row
  /// \param foreground_colour The foreground colour of the row
  /// \param outline_colour The outline colour of the row
  /// \param highlight_colour The highlight colour of the row
  /// \param font_weight The font weight of the row
  /// \param highlighted The highlighted flag
  /// \param alignment The alignment of the row
  ///
  RowType(const uint32_t background_colour, const uint32_t foreground_colour, const uint32_t outline_colour,
          const uint32_t highlight_colour, const widget::WeightType font_weight, const bool highlighted,
          const widget::CellAlignType alignment);

  ///
  /// \brief Construct a new Row Type object
  ///
  /// \param a The row to copy
  ///
  RowType(const RowType &a);

  ///
  /// \brief Assignment operator
  ///
  /// \param a The row to copy
  /// \return RowType&
  ///
  RowType &operator=(const RowType &a);

  ///
  /// \brief Sorting is based on priority then time
  ///
  ///
  bool operator<(const RowType &a) const;

  ///
  /// \brief Sorting is based on priority then time
  ///
  /// \param a The row to compare
  /// \return true
  /// \return false
  ///
  bool operator>(const RowType &a) const;

  ///
  /// \brief Get the Foreground Colour
  ///
  /// \return uint32_t The foreground colour
  ///
  uint32_t GetForegroundColour() const;

  ///
  ///  \brief Get the Background Colour
  ///
  ///  \return uint32_t The background colour
  ///
  uint32_t GetBackgroundColour() const;

  ///
  /// \brief Get the Outline Colour
  ///
  /// \return uint32_t The outline colour
  ///
  uint32_t GetOutlineColour() const;

  ///
  /// \brief Get the Highlight Colour
  ///
  /// \return uint32_t The highlight colour
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
  /// \param value The value to set
  ///
  void SetHighlighted(bool value);

  ///
  /// \brief Get the Cell Alignment object
  ///
  /// \return CellAlignType The cell alignment
  ///
  widget::CellAlignType GetCellAlignment() const;

  ///
  /// \brief Get a reference to the Cells vector for this row
  ///
  /// \return std::vector<CellType>&
  ///
  std::vector<CellType> *GetCells() { return &cells_; }

 private:
  /// The cells in this row
  std::vector<CellType> cells_;
  /// The background colour
  uint32_t background_colour_ = 0;
  /// The foreground colour
  uint32_t foreground_colour_ = 0;
  /// The outline colour
  uint32_t outline_colour_ = 0;
  /// The highlight colour
  uint32_t highlight_colour_ = 0;
  /// The font weight
  widget::WeightType font_weight_ = widget::WeightType::kWeightNormal;
  /// The highlighted flag
  bool highlighted_;
  /// The cell alignment
  widget::CellAlignType alignment_ = widget::CellAlignType::kAlignLeft;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_ROW_TYPE_H_
