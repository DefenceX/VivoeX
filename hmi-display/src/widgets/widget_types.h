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

#ifndef HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_
#define HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_

namespace gva::widget {

enum class KeyboardModeType { kKeyboardLower = 0, kKeyboardUpper, kKeyboardNumbers };

enum class CellAlignType { kAlignLeft = 0, kAlignCentre, kAlignRight };

enum class WeightType { kWeightNormal = 0, kWeightBold, kWeightItalic };

//
// Widgets
//
enum WidgetEnum {
  KWidgetTypeCompass,
  KWidgetTypeKeyboard,
  KWidgetTypeAlarmIndicator,
  KWidgetTypeTopLabels,
  KWidgetTypeBottomLabels,
  KWidgetTypeLeftLabels,
  KWidgetTypeRightLabels,
  KWidgetTypeMode,
  KWidgetTypeTable
};
enum class ModeEnum {
  kPpiClassicTankWithSight,
  kPpiClassicTankWithoutSight,
  kPpiClassicArrowWithSight,
  kPpiClassicArrowWithoutSight,
  kPpiModernTankWithSights,
  kPpiModernTankWithoutSights
};

enum class IconType {
  kIconNone = 0,
  kIconUpArrow,
  kIconDownArrow,
  kIconRightArrow,
  kIconLeftArrow,
  kIconUpArrowOutline,
  kIconDownArrowOutline,
  kIconLeftArrowOutline,
  kIconRightArrowOutline,
  kIconPlus,
  kIconMinus,
  kIconEnter,
  kIconRotateLeft,
  kIconRotateRight,
  kIconPowerOff,
  kIconLocation,
  kIconWarning,
  kIconError,
  kIconInfo,
  kIconCentre
};

struct GvaColourType {
  int red;
  int green;
  int blue;
};

}  // namespace gva::widget

#endif  // HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_
