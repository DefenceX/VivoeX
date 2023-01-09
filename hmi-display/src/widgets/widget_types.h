//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
/// \file widget_types.h
///

#ifndef HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_
#define HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_

namespace gva::widget {

///
/// \brief The various types of keyboard input (see WidgetKeyboard)
///
///
enum class KeyboardModeType { kKeyboardLower = 0, kKeyboardUpper, kKeyboardNumbers };

///
/// \brief Table (see WidgetTable) cell alignment
///
///
enum class CellAlignType { kAlignLeft = 0, kAlignCentre, kAlignRight };

///
/// \brief The line weight for boxes and tables
///
///
enum class WeightType { kWeightNormal = 0, kWeightBold, kWeightItalic };

///
/// \brief The different types of widget currently available for display
///
///
enum class WidgetEnum {
  KWidgetTypeCompass,
  KWidgetTypeKeyboard,
  KWidgetTypeAlarmIndicator,
  KWidgetTypeTopLabels,
  KWidgetTypeBottomLabels,
  KWidgetTypeLeftLabels,
  KWidgetTypeRightLabels,
  KWidgetTypeMode,
  KWidgetTypeTable,
  KWidgetTypeTableDynamic,
  kWidgetTypeDialSpeedometer,
  KWidgetTypeDialRpmFuel
};

///
/// \brief The Plan Position Indicator modes, different visual styles
///
///
enum class ModeEnum {
  kPpiClassicTankWithSight,
  kPpiClassicTankWithoutSight,
  kPpiClassicArrowWithSight,
  kPpiClassicArrowWithoutSight,
  kPpiModernTankWithSights,
  kPpiModernTankWithoutSights
};

///
/// \brief The different dial types
///
///
enum class DialType { kDialSpeedKph, kDialSpeedMph };

///
/// \brief All available types of icon
///
///
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
  kIconCentre,
  kIconWaterfallSight,
  kIconWCrossSight
};

///
/// \brief Generic colour structure without alpha value
///
///
struct GvaColourType {
  ///  Red intensity value
  int red;
  /// Green intensity value
  int green;
  /// Blue intensity value
  int blue;
};

}  // namespace gva::widget

#endif  // HMI_DISPLAY_SRC_WIDGETS_WIDGET_TYPES_H_
