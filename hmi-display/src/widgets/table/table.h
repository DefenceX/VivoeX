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
/// \brief The Keyboard widget
///
/// \file table.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_TABLE_TABLE_H_
#define HMI_DISPLAY_SRC_WIDGETS_TABLE_TABLE_H_

#include <memory>
#include <string>
#include <vector>

#include "src/renderer_gva.h"
#include "src/widgets/table/cell_type.h"
#include "src/widgets/table/row_type.h"
#include "src/widgets/widget.h"
#include "src/widgets/widget_types.h"

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
  explicit WidgetTable(const RendererGva &renderer, TouchGva *touch, uint32_t background_colour);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetTable() final = default;

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
  void AddRow(uint32_t foreground_colour, uint32_t background_colour, uint32_t outline_colour,
              uint32_t highlight_colour, widget::WeightType font_weight);

  ///
  /// \brief Add a row to the table
  ///
  ///
  void AddRow();

  ///
  /// \brief Add a row to the table
  ///
  /// \param font_weight The font weight
  ///
  void AddRow(widget::WeightType font_weight);

  ///
  /// widgets \brief Add a basic cell
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  ///
  void AddCell(std::string text, uint32_t width);

  ///
  /// \brief Add a new cell with background colour
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param background_colour Cell background colour
  ///
  void AddCell(std::string text, uint32_t width, uint32_t background_colour);

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the ctable_
  void AddCell(std::string text, uint32_t width, widget::CellAlignType align);

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param align Alignment CellAlignType::
  /// \param background_colour Cell background colour
  ///
  void AddCell(std::string text, uint32_t width, widget::CellAlignType align, uint32_t background_colour);

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
  uint32_t GetBackgroundColour() { return background_colour_; }

  ///
  /// \brief Set the Background Colour attribute
  ///
  /// \param background_colour
  ///
  void SetBackgroundColour(uint32_t background_colour) { background_colour_ = background_colour; }

  ///
  /// \brief Set the Current selected row, will be highlighted in the theme colours
  ///
  /// \param row
  ///
  void SetCurrentRow(uint32_t row) { current_row_ = row; }

  void SetNextRow() {
    if (current_row_ < rows_.size() - 2) current_row_++;
  }

  void SetPreviousRow() {
    if (current_row_ > 1) current_row_--;
  }

  ///
  /// \brief Get the Current selected highlighted row
  ///
  /// \param row
  /// \return uint32_t
  ///
  uint32_t GetCurrentRow() const { return current_row_; }

  ///
  /// \brief Get the Rows vector
  ///
  /// \return std::vector<RowType>&
  ///
  std::vector<RowType> &GetRows() { return rows_; }

 private:
  std::vector<RowType> rows_;
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

#endif  // HMI_DISPLAY_SRC_WIDGETS_TABLE_TABLE_H_