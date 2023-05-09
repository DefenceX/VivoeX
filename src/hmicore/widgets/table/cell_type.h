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

#include "hmicore/widgets/widget_types.h"

namespace gva {

///
/// \brief This is the class describing a TableWidget cell
///
///
class CellType {
 public:
  CellType() = default;
  ~CellType() = default;
  CellType(const std::string text, const uint32_t width, const uint32_t background_colour,
           const uint32_t foreground_colour, const uint32_t outline_colour, const uint32_t highlight_colour,
           const widget::CellAlignType alignment);

  CellType(const CellType &a);
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
  uint32_t width_ = 0;
  std::string text_ = "";
  uint32_t background_colour_ = 0;
  uint32_t foreground_colour_ = 0;
  uint32_t outline_colour_ = 0;
  uint32_t highlight_colour_ = 0;
  widget::CellAlignType alignment_ = widget::CellAlignType::kAlignLeft;
};
}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_CELL_TYPE_H_
