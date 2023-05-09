//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file table.h
///
#ifndef HMICORE_WIDGETS_TABLE_TABLE_H_
#define HMICORE_WIDGETS_TABLE_TABLE_H_

#include <memory>
#include <string>
#include <vector>

#include "hmicore/renderer_gva.h"
#include "hmicore/widgets/table/cell_type.h"
#include "hmicore/widgets/table/row_type.h"
#include "hmicore/widgets/widget.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

///
/// \brief A widget representing a table of elements
///
///
class WidgetTable : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
  ///
  explicit WidgetTable(const RendererGva &renderer, TouchGva *touch, uint32_t background_colour = 0x000000);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetTable() override = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const override { return "WidgetTable"; };

  ///
  /// \brief The base class override to draw the table once setup
  ///
  ///
  void Draw() override;

  ///
  /// \brief Add a row to the table
  ///
  /// \param foreground_colour Foreground colour
  /// \param background_colour Background colour
  /// \param outline_colour Outline colour
  /// \param highlight_colour Highlight colour
  /// \param font_weight The font weight
  ///
  virtual void AddRow(uint32_t foreground_colour, uint32_t background_colour, uint32_t outline_colour,
                      uint32_t highlight_colour, widget::WeightType font_weight);

  ///
  /// \brief Add a row to the table
  ///
  ///
  virtual void AddRow();

  ///
  /// \brief Add a row to the table
  ///
  /// \param font_weight The font weight
  ///
  virtual void AddRow(widget::WeightType font_weight);

  ///
  /// widgets \brief Add a basic cell
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  ///
  virtual void AddCell(const std::string text, uint32_t width);

  ///
  /// \brief Add a new cell with background colour
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param background_colour Cell background colour
  ///
  virtual void AddCell(const std::string text, uint32_t width, uint32_t background_colour);

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the ctable_
  virtual void AddCell(const std::string text, uint32_t width, widget::CellAlignType align);

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param align Alignment CellAlignType::
  /// \param background_colour Cell background colour
  ///
  virtual void AddCell(const std::string text, uint32_t width, widget::CellAlignType align, uint32_t background_colour);

  ///
  /// \brief Reset the table
  ///
  ///
  void Reset();

  ///
  /// \brief Get the Background Colour attribute
  ///
  /// \return uint32_t
  ///
  uint32_t GetBackgroundColour() const;

  ///
  /// \brief Set the Background Colour attribute
  ///
  /// \param background_colour
  ///
  void SetBackgroundColour(uint32_t background_colour);

  ///
  /// \brief Set the Current selected row, will be highlighted in the theme colours
  ///
  /// \param row
  ///
  void SetCurrentRow(uint32_t row);

  ///
  /// \brief Set the Next Row attribute
  ///
  ///
  void SetNextRow();

  ///
  /// \brief Set the Previous Row attribute
  ///
  ///
  void SetPreviousRow();

  ///
  /// \brief Get the Current selected highlighted row
  ///
  /// \param row
  /// \return uint32_t
  ///
  uint32_t GetCurrentRow() const;

  ///
  /// \brief Get the Rows vector
  ///
  /// \return std::vector<RowType>&
  ///
  std::vector<RowType> &GetRows();

  ///
  /// \brief Get the all the Rows in supplie vector
  ///
  /// \param rows
  ///
  void SetRows(const std::vector<RowType> &rows);

 private:
  std::vector<RowType> rows_;
  std::vector<RowType> rows_filtered_;
  void DrawTable();
  TouchGva *touch_;
  uint32_t current_cell_ = 0;
  uint32_t current_row_ = 0;
  uint32_t background_colour_;
  uint32_t foreground_colour_ = Renderer::PackRgb(HMI_WHITE);
  uint32_t outline_colour_ = ConfigData::GetInstance()->GetThemeLabelBorderEnabled();
  uint32_t highlight_colour_ = ConfigData::GetInstance()->GetThemeLabelBorderEnabledSelected();
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_TABLE_H_
