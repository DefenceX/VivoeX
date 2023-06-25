//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file widget_types.h
///

#ifndef HMICORE_WIDGETS_WIDGET_TYPES_H_
#define HMICORE_WIDGETS_WIDGET_TYPES_H_
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
  KWidgetTypeCanvas,
  KWidgetTypeVideo,
  KWidgetTypeStatusBar,
  KWidgetTypeObjectLocalisation,
  KWidgetTypeCompass,
  KWidgetTypeKeyboard,
  KWidgetTypeAlarmIndicator,
  KWidgetTypeTopLabels,
  KWidgetTypeBottomLabels,
  KWidgetTypeLeftLabels,
  KWidgetTypeRightLabels,
  KWidgetTypeMode,
  KWidgetTypeTable,
  KWidgetTypeMessageBox,
  KWidgetTypeTableDynamic,
  kWidgetTypeDialSpeedometer,
  KWidgetTypeDialRpmFuel,
  KWidgetTypeBezelButtons,
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

#endif  // HMICORE_WIDGETS_WIDGET_TYPES_H_
