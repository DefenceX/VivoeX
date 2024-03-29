//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file table_dynamic.h
///
#ifndef HMICORE_WIDGETS_TABLE_TABLE_DYNAMIC_H_
#define HMICORE_WIDGETS_TABLE_TABLE_DYNAMIC_H_

#include <memory>
#include <string>
#include <vector>

#include "hmicore/widgets/table/table.h"

namespace gva {

///
/// \brief A widget representing a table of elements
///
///
class WidgetTableDynamic : public WidgetTable {
 public:
  ///
  /// \brief An enum representing to type of sort
  ///
  ///
  enum class SortType { kSortUnsorted = 0, kSortAscending, kSortDescending };

  ///
  /// \brief Construct a new Widget Table Dynamic object
  ///
  /// \param renderer The Gva renderer
  /// \param touch The touch object
  /// \param background_colour The background colour
  ///
  explicit WidgetTableDynamic(const RendererGva &renderer, TouchGva *touch, uint32_t background_colour);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetTableDynamic() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetTableDynamic"; }

  ///
  /// \brief The base class override to draw the table once setup
  ///
  ///
  void Draw() final;

  ///
  /// \brief Add a row to the table
  ///
  /// \param foreground_colour Foreground colour
  /// \param background_colour Background colour
  /// \param outline_colour Outline colour
  /// \param highlight_colour Highlight colour
  /// \param font_weight The font weight
  ///
  void AddRow(uint32_t foreground_colour, uint32_t background_colour, uint32_t outline_colour,
              uint32_t highlight_colour, widget::WeightType font_weight) final;

  ///
  /// \brief Add a row to the table
  ///
  ///
  void AddRow() final;

  ///
  /// \brief Add a row to the table
  ///
  /// \param font_weight The font weight
  ///
  void AddRow(widget::WeightType font_weight) final;

  ///
  /// widgets \brief Add a basic cell
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  ///
  void AddCell(const std::string text, uint32_t width) final;

  ///
  /// \brief Add a new cell with background colour
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param background_colour Cell background colour
  ///
  void AddCell(const std::string text, uint32_t width, uint32_t background_colour) final;

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the ctable_
  /// \param align Alignment CellAlignType
  ///
  void AddCell(const std::string text, uint32_t width, widget::CellAlignType align) final;

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param align Alignment CellAlignType::
  /// \param background_colour Cell background colour
  ///
  void AddCell(const std::string text, uint32_t width, widget::CellAlignType align, uint32_t background_colour) final;

  ///
  /// \brief Set the Hide Override attribute
  ///
  /// \param hide
  ///
  void SetHideOverride(bool hide);

  ///
  /// \brief Get the Hide Override attribute
  ///
  /// \return true if overridden alarms are hidden
  /// \return false otherwise
  ///
  bool GetHideOverride() const;

  ///
  /// \brief Set the Sorted attribute
  ///
  /// \param sort
  ///
  void SetSorted(SortType sort);

  ///
  /// \brief Get the Sorted attribute
  ///
  /// \return true
  /// \return false
  ///
  SortType GetSorted() const;

  ///
  /// \brief Set the All Highlighted attribute
  ///
  /// \param highlight_all true if all to be highlighted, false to unset all bar first row
  ///
  void SetAllHighlighted(bool highlight_all);

  ///
  /// \brief Get the All Highlighted attribute
  ///
  /// \return true if all currently highlighted
  /// \return false if only some highlighted
  ///
  bool GetAllHighlighted() const;

 private:
  uint32_t background_colour_;
  uint32_t foreground_colour_ = Renderer::PackRgb(kHmiWhite);
  uint32_t outline_colour_ = ConfigData::GetInstance()->GetThemeLabelBorderEnabled();
  uint32_t highlight_colour_ = ConfigData::GetInstance()->GetThemeLabelBorderEnabledSelected();

  std::vector<RowType> dynamic_rows_;
  std::vector<RowType> dynamic_rows_filtered_;

  bool highlight_all_ = false;
  bool hide_override_ = false;
  SortType sorted_ = SortType::kSortUnsorted;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_TABLE_DYNAMIC_H_
