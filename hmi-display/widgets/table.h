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
#ifndef TABLE_H
#define TABLE_H

#include "renderer.h"
#include "widget.h"

namespace gva {

typedef struct {
  int width;
  char text[256];
  long background_colour;
  long foreground_colour;
  long outline_colour;
  long highlight_colour;
  cellAlignType alignment;
} CellType;

#define MAX_CELLS 20
typedef struct {
  int cell_count;
  CellType cells[MAX_CELLS];
  long background_colour;
  long foreground_colour;
  long outline_colour;
  long highlight_colour;
  WeightType font_weight;
  bool highlighted;
  cellAlignType alignment;
} RowType;

#define MAX_ROWS 100
class TableWidget {
 public:
  TableWidget() { configuration_ = gva::ConfigData::GetInstance(); }

  ///
  /// \brief Add a row to the table
  ///
  /// \param forground_colour Forground colour
  /// \param background_colour Background colour
  /// \param outline_colour Outline colour
  /// \param highlight_colour Highlight colour
  /// \param font_weight Font weight
  ///
  void AddRow(long forground_colour, long background_colour, long outline_colour, long highlight_colour,
              WeightType font_weight) {
    RowType *row = &rows_[row_count_];
    row->background_colour = background_colour;
    row->foreground_colour = forground_colour;
    row->outline_colour = outline_colour;
    row->highlight_colour = highlight_colour;
    row->font_weight = font_weight;
    row->highlighted = false;
    row_count_ += 1;
  }

  ///
  /// \brief Add a row to the table
  ///
  ///
  void AddRow() {
    RowType *row = &rows_[row_count_];
    row->background_colour = ConfigData::GetInstance()->GetTableBackground();
    row->foreground_colour = Renderer::PackRgb(HMI_WHITE);
    row->outline_colour = Renderer::PackRgb(HMI_WHITE);
    row->highlight_colour = Renderer::PackRgb(HMI_YELLOW);
    row->font_weight = WEIGHT_NORMAL;
    row->highlighted = false;
    row->alignment = ALIGN_LEFT;
    row_count_ += 1;
  }

  ///
  /// \brief Add a row to the table
  ///
  /// \param font_weight
  ///
  void AddRow(WeightType font_weight) {
    RowType *row = &rows_[row_count_];
    AddRow();
    row->font_weight = font_weight;
  }

  ///
  /// \brief Set the highlighted row
  ///
  ///
  void CurrentRowHighlight() { rows_[row_count_ - 1].highlighted = true; };

  ///
  /// \brief Add a basic cell
  ///
  /// \param text
  /// \param width
  ///
  void AddCell(char *text, int width) { AddCell(text, width, ALIGN_LEFT); }

  ///
  /// \brief Add a new cell with background colour
  ///
  /// \param text
  /// \param width
  /// \param background_colour
  ///
  void AddCell(char *text, int width, long background_colour) {
    CellType *cell = &rows_[row_count_ - 1].cells[rows_[row_count_ - 1].cell_count];
    AddCell(text, width, ALIGN_LEFT);
    cell->background_colour = background_colour;
  }

  ///
  /// \brief Add a new cell specifying alingment
  ///
  /// \param text
  /// \param width
  /// \param align
  ///
  void AddCell(char *text, int width, cellAlignType align) {
    CellType *cell = &rows_[row_count_ - 1].cells[rows_[row_count_ - 1].cell_count];
    cell->background_colour = rows_[row_count_ - 1].background_colour;
    cell->foreground_colour = rows_[row_count_ - 1].foreground_colour;
    cell->outline_colour = rows_[row_count_ - 1].outline_colour;
    cell->highlight_colour = rows_[row_count_ - 1].highlight_colour;
    strcpy(cell->text, text);
    cell->width = width;
    cell->alignment = align;
    rows_[row_count_ - 1].cell_count += 1;
  }

  ///
  /// \brief Reset the table
  ///
  ///
  void Reset() {
    visible_ = false;
    row_count_ = 0;
    memset(&rows_, 0, sizeof(rows_));
  }
  bool visible_;
  int height_;
  int width_;
  int x_;
  int y_;
  int row_count_;
  long background_colour_;
  RowType rows_[MAX_ROWS];

 private:
  gva::ConfigData *configuration_;
};

}  // namespace gva
#endif