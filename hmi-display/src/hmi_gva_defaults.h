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
/// \brief The default values for the on screen widgets
///
/// \file hmi_gva_defaults.h
///
#ifndef HMI_DISPLAY_SRC_HMI_GVA_DEFAULTS_H_
#define HMI_DISPLAY_SRC_HMI_GVA_DEFAULTS_H_

#include "src/gva.h"
#include "src/screen_gva.h"

namespace gva {

class DefaultSettings {
 public:
  DefaultSettings() = default;

  ///
  /// \brief Get the Default Screen object
  ///
  /// \return Screen
  ///
  static Screen GetDefaultScreen();

  ///
  /// \brief Get the Default Common Task Keys object
  ///
  /// \return CommonTaskKeys
  ///
  static CommonTaskKeys GetDefaultCommonTaskKeys();

  ///
  /// \brief Get the Default Function Select object
  ///
  /// \return FunctionSelect
  ///
  static FunctionSelect GetDefaultFunctionSelect();

  ///
  /// \brief Get the Default Status Bar object
  ///
  /// \return StatusBar
  ///
  static StatusBar GetDefaultStatusBar();

  ///
  /// \brief Get the Default Canvas object
  ///
  /// \return Canvas
  ///
  static Canvas GetDefaultCanvas();

  ///
  /// \brief Get the Default Function Keys Default All Hidden object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeysDefaultAllHidden();

  ///
  /// \brief Get the Default Function Keys Situational Awareness Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeysSituationalAwarenessLeft();

  ///
  /// \brief Get the Default Function Keys Situational Awareness Right object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeysSituationalAwarenessRight();

  ///
  /// \brief Get the Default Function Keys Weapons Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeysWeaponsLeft();

  ///
  /// \brief Get the Default Function Keys Weapons Right object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeysWeaponsRight();

  ///
  /// \brief Get the Default Function Keys Defensive Systems Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeysDefensiveSystemsLeft();

  ///
  /// \brief Get the Default Function Key Systems Right object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeySystemsRight();

  ///
  /// \brief Get the Default Function Key Systems Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeySystemsLeft();

  ///
  /// \brief Get the Default Function Key Driver Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeyDriverLeft();

  ///
  /// \brief Get the Default Function Key Communications Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeyCommunicationsLeft();

  ///
  /// \brief Get the Default Function Key Battlefield Management System Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeyBattlefieldManagementSystemLeft();

  ///
  /// \brief Get the Default Function Key Battlefield Management System Right object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeyBattlefieldManagementSystemRight();

  ///
  /// \brief Get the Default Function Key Alarms Left object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeyAlarmsLeft();

  ///
  /// \brief Get the Default Function Key Alarms Right object
  ///
  /// \return FunctionKeys
  ///
  static FunctionKeys GetDefaultFunctionKeyAlarmsRight();

 private:
};
}  // namespace gva

#endif  // HMI_DISPLAY_SRC_HMI_GVA_DEFAULTS_H_
