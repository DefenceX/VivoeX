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

#ifndef HMI_DISPLAY_SRC_WIDGETS_WIDGET_H_
#define HMI_DISPLAY_SRC_WIDGETS_WIDGET_H_

namespace gva {

enum class KeyboardModeType { KEYBOARD_LOWER = 0, KEYBOARD_UPPER, KEYBOARD_NUMBERS };

enum class CellAlignType { ALIGN_LEFT = 0, ALIGN_CENTRE, ALIGN_RIGHT };

enum class WeightType { WEIGHT_NORMAL = 0, WEIGHT_BOLD, WEIGHT_ITALIC };

typedef enum {
  ICON_NONE = 0,
  ICON_UP_ARROW,
  ICON_DOWN_ARROW,
  ICON_LEFT_ARROW,
  ICON_RIGHT_ARROW,
  ICON_UP_ARROW_OUTLINE,
  ICON_DOWN_ARROW_OUTLINE,
  ICON_LEFT_ARROW_OUTLINE,
  ICON_RIGHT_ARROW_OUTLINE,
  ICON_PLUS,
  ICON_MINUS,
  ICON_ENTER,
  ICON_ROTATE_LEFT,
  ICON_ROTATE_RIGHT,
  ICON_POWER_OFF,
  ICON_LOCATION,
  ICON_WARNING,
  ICON_ERROR,
  ICON_INFO,
  ICON_CENTRE
} IconType;

struct GvaColourType {
  int red;
  int green;
  int blue;
};

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

#endif  // HMI_DISPLAY_SRC_WIDGETS_WIDGET_H_
