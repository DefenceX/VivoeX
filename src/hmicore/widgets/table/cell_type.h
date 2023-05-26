//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file cell_type.h
///

#ifndef HMICORE_WIDGETS_TABLE_CELL_TYPE_H_
#define HMICORE_WIDGETS_TABLE_CELL_TYPE_H_

#include <string>
#include <string_view>
#include <stdint.h>
 
#include "hmicore/widgets/widget_types.h"

namespace gva {

///
/// \brief This is the class describing a TableWidget cell
///
///
class CellType {
 public:
  ///
  /// \brief Construct a new Cell Type object
  ///
  ///
  CellType() = default;

  ///
  /// \brief Destroy the Cell Type object
  ///
  ///
  ~CellType() = default;

  ///
  /// \brief Construct a new Cell Type object
  ///
  /// \param text The text to display in the cell
  /// \param width The width of the cell
  /// \param background_colour The background colour of the cell
  /// \param foreground_colour The foreground colour of the cell
  /// \param outline_colour The outline colour of the cell
  /// \param highlight_colour The highlight colour of the cell
  /// \param alignment The alignment of the cell
  ///
  CellType(const std::string text, const uint32_t width, const uint32_t background_colour,
           const uint32_t foreground_colour, const uint32_t outline_colour, const uint32_t highlight_colour,
           const widget::CellAlignType alignment);

  ///
  /// \brief Construct a new Cell Type object
  ///
  /// \param a The cell to copy
  ///
  CellType(const CellType &a);

  ///
  /// \brief Assignment operator
  ///
  /// \param a The cell to assign
  /// \return CellType&
  ///
  CellType &operator=(const CellType &a);

  ///
  /// \brief Get the Width object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetWidth() const;

  ///
  /// \brief Get the Text object
  ///
  /// \return const std::string
  ///
  std::string GetText() const;

  ///
  /// \brief Set the Text attribute
  ///
  /// \param text
  ///
  void SetText(std::string_view text);

  ///
  /// \brief Get the Foreground Colour object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetForegroundColour() const;

  ///
  /// \brief Get the Background Colour object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetBackgroundColour() const;

  ///
  /// \brief Get the Outline Colour object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetOutlineColour() const;

  ///
  /// \brief Get the Highlight Colour object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetHighlightColour() const;

  ///
  /// \brief Get the Cell Alignment object
  ///
  /// \return const CellAlignType
  ///
  widget::CellAlignType GetCellAlignment() const;

 private:
  /// The width of the cell
  uint32_t width_ = 0;
  /// The text to display in the cell
  std::string text_ = "";
  /// The background colour of the cell
  uint32_t background_colour_ = 0;
  /// The foreground colour of the cell
  uint32_t foreground_colour_ = 0;
  /// The outline colour of the cell
  uint32_t outline_colour_ = 0;
  /// The highlight colour of the cell
  uint32_t highlight_colour_ = 0;
  /// The alignment of the cell enum
  widget::CellAlignType alignment_ = widget::CellAlignType::kAlignLeft;
};
}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_CELL_TYPE_H_
