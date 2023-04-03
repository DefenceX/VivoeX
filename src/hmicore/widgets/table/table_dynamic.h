//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
/// \file table_dynamic.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_TABLE_TABLE_DYNAMIC_H_
#define HMI_DISPLAY_SRC_WIDGETS_TABLE_TABLE_DYNAMIC_H_

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
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
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
  uint32_t foreground_colour_ = Renderer::PackRgb(HMI_WHITE);
  uint32_t outline_colour_ = ConfigData::GetInstance()->GetThemeLabelBorderEnabled();
  uint32_t highlight_colour_ = ConfigData::GetInstance()->GetThemeLabelBorderEnabledSelected();

  std::vector<RowType> dynamic_rows_;
  std::vector<RowType> dynamic_rows_filtered_;

  bool highlight_all_ = false;
  bool hide_override_ = false;
  SortType sorted_ = SortType::kSortUnsorted;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_TABLE_TABLE_DYNAMIC_H_
