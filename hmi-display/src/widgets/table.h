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
#ifndef HMI_DISPLAY_SRC_WIDGETS_TABLE_H_
#define HMI_DISPLAY_SRC_WIDGETS_TABLE_H_

#include <memory>
#include <string>
#include <vector>

#include "src/renderer_gva.h"
#include "src/widgets/widget.h"

namespace gva {

///
/// \brief A widget respresenting a table of elements
///
///
class TableWidget {
 public:
  class CellType {
   public:
    CellType(const uint32_t width, const std::string &text, const uint32_t background_colour,
             const uint32_t foreground_colour, const uint32_t outline_colour, const uint32_t highlight_colour,
             const CellAlignType alignment);
    CellType &operator=(const CellType &a) {
      width_ = a.width_;
      text_ = a.text_;
      background_colour_ = a.background_colour_;
      foreground_colour_ = a.foreground_colour_;
      outline_colour_ = a.outline_colour_;
      highlight_colour_ = a.highlight_colour_;
      alignment_ = a.alignment_;
      return *this;
    }
    uint32_t width_;
    std::string text_;
    uint32_t background_colour_;
    uint32_t foreground_colour_;
    uint32_t outline_colour_;
    uint32_t highlight_colour_;
    CellAlignType alignment_;
  };

  class RowType {
   public:
    RowType(const uint32_t background_colour, const uint32_t foreground_colour, const uint32_t outline_colour,
            const uint32_t highlight_colour, const WeightType font_weight, const bool highlighted,
            const CellAlignType alignment);
    RowType &operator=(const RowType &a) {
      background_colour_ = a.background_colour_;
      foreground_colour_ = a.foreground_colour_;
      outline_colour_ = a.outline_colour_;
      highlight_colour_ = a.highlight_colour_;
      font_weight_ = a.font_weight_;
      highlighted_ = a.highlighted_;
      alignment_ = a.alignment_;
      return *this;
    }
    uint32_t cell_count_;
    std::vector<CellType> cells_;
    uint32_t background_colour_;
    uint32_t foreground_colour_;
    uint32_t outline_colour_;
    uint32_t highlight_colour_;
    WeightType font_weight_;
    bool highlighted_;
    CellAlignType alignment_;
  };

  TableWidget() { configuration_ = gva::ConfigData::GetInstance(); }

  ///
  /// \brief Add a row to the table
  ///
  /// \param forground_colour Foreground colour
  /// \param background_colour Background colour
  /// \param outline_colour Outline colour
  /// \param highlight_colour Highlight colour
  /// \param font_weight The font weight
  ///
  void AddRow(uint32_t forground_colour, uint32_t background_colour, uint32_t outline_colour, uint32_t highlight_colour,
              WeightType font_weight);

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
  void AddRow(WeightType font_weight);

  ///
  /// \brief Set the highlighted row
  ///
  ///
  void CurrentRowHighlight();

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
  /// \param width The width of the cell in pixels
  /// \param align Alignment CellAlignType::
  ///
  void AddCell(std::string text, uint32_t width, CellAlignType align);

  ///
  /// \brief Add a new cell specifying alignment
  ///
  /// \param text The text to be contained in the cell
  /// \param width The width of the cell in pixels
  /// \param align Alignment CellAlignType::
  /// \param background_colour Cell background colour
  ///
  void AddCell(std::string text, uint32_t width, CellAlignType align, uint32_t background_colour);

  ///
  /// \brief Reset the table
  ///
  ///
  void Reset();

  bool visible_;
  uint32_t height_;
  uint32_t width_;
  uint32_t x_;
  uint32_t y_;
  uint32_t row_count_;
  uint32_t background_colour_;
  std::vector<RowType> rows_;

 private:
  ConfigData *configuration_ = nullptr;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_TABLE_H_
