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
/// \brief Template for all widgets
///
/// \file widget.h
///

#ifndef WIDGET_H
#define WIDGET_H

#include "renderer_gva.h"
#include "widget.h"

namespace gva {

class ScreenGva;
//
// Widgets
//
enum WidgetEnum { WIDGET_TYPE_COMPASS = 0, WIDGET_TYPE_KEYBOARD = 1, WIDGET_TYPE_ALARM_INDICATOR = 2 };

class WidgetX {
 public:
  ///
  /// \brief Construct a new Widget X object
  ///
  /// \param screen The screen being rendered
  /// \param widget_type The type of widget
  ///
  WidgetX(ScreenGva *screen, WidgetEnum widget_type) {
    screen_ = screen;
    widget_type_ = widget_type;
  }
  ///
  /// \brief Set the Visible object
  ///
  /// \param visible
  ///

  void SetVisible(bool visible) { visible_ = visible; }
  ///
  /// \brief Get the Visible object
  ///
  /// \return true
  /// \return false
  ///
  bool GetVisible() { return visible_; }

  ///
  /// \brief Set the X dimension
  ///
  /// \param x
  ///
  void SetX(int x) { x_ = x; }

  ///
  /// \brief Get the Y dimension
  ///
  /// \return int
  ///
  int GetX() { return x_; }

  ///
  /// \brief Set the Y dimension
  ///
  /// \param y
  ///
  void SetY(int y) { y_ = y; }

  ///
  /// \brief Get the Y dimension
  ///
  /// \return int
  ///
  int GetY() { return y_; }

  ///
  /// \brief Draw the widget
  ///
  ///
  virtual void Draw() = 0;

  ///
  /// \brief Get the Type object
  ///
  /// \return WidgetEnum
  ///
  WidgetEnum GetType() { return widget_type_; }

 protected:
  ScreenGva *screen_;

 private:
  WidgetEnum widget_type_;
  bool visible_ = true;
  int x_ = 0;
  int y_ = 0;
};

}  // namespace gva
#endif