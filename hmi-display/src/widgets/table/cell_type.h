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
/// \file cell_type.h
///

#ifndef HMI_DISPLAY_SRC_WIDGETS_TABLE_CELL_TYPE_H_
#define HMI_DISPLAY_SRC_WIDGETS_TABLE_CELL_TYPE_H_

#include <string>

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

#endif  // HMI_DISPLAY_SRC_WIDGETS_TABLE_CELL_TYPE_H_
