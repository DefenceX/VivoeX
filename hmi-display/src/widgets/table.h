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

    CellType(const CellType &a)
        : width_(a.width_),
          text_(a.text_),
          background_colour_(a.background_colour_),
          foreground_colour_(a.foreground_colour_),
          outline_colour_(a.outline_colour_),
          highlight_colour_(a.highlight_colour_),
          alignment_(a.alignment_) {}
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

  ///
  /// \brief The base class override to draw the table once setup
  ///
  ///
  void Draw() override;

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
    RowType(const RowType &a)
        : background_colour_(a.background_colour_),
          foreground_colour_(a.foreground_colour_),
          outline_colour_(a.outline_colour_),
          highlight_colour_(a.highlight_colour_),
          font_weight_(a.font_weight_),
          highlighted_(a.highlighted_),
          alignment_(a.alignment_) {}
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

    ///
    /// \brief Get the Foreground Colour
    ///
    /// \brief Get the Background Colour
    ///
    /// \return uint32_t
    ///
    uint32_t GetForegroundColour() const;

    /// table_
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

    std::vector<CellType> cells_;

   private:
    uint32_t background_colour_ = 0;
    uint32_t foreground_colour_ = 0;
    uint32_t outline_colour_ = 0;
    uint32_t highlight_colour_ = 0;
    widget::WeightType font_weight_ = widget::WeightType::kWeightNormal;
    bool highlighted_ = false;
    widget::CellAlignType alignment_ = widget::CellAlignType::kAlignLeft;
  };

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

  std::vector<RowType> rows_;

 private:
  void DrawTable();
  TouchGva *touch_;
  uint32_t current_row_ = 3;
  uint32_t background_colour_;
  uint32_t foreground_colour_ = Renderer::PackRgb(HMI_WHITE);
  uint32_t outline_colour_ = Renderer::PackRgb(HMI_WHITE);
  uint32_t highlight_colour_ = Renderer::PackRgb(HMI_WHITE);
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_TABLE_H_
