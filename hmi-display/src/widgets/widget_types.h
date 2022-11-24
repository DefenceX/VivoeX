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
/// \brief The datatypes used by all widgets
///
/// \file widget_types.h
///

#ifndef HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES__H_
#define HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES__H_

namespace gva {

enum class KeyboardModeType { kKeyboardLower = 0, kKeyboardUpper, kKeyboardNumbers };

enum class CellAlignType { kAlignLeft = 0, kAlignCentre, kAlignRight };

enum class WeightType { kWeightNormal = 0, kWeightBold, kWeightItalic };

//
// Widgets
//
enum WidgetEnum { KWidgetTypeCompass = 0, KWidgetTypeKeyboard = 1, KWidgetTypeAlarmIndicator = 2 };

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

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_
