//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file hmi_gva_defaults.h
///
#ifndef HMICORE_HMI_GVA_DEFAULTS_H_
#define HMICORE_HMI_GVA_DEFAULTS_H_

#include "hmicore/gva.h"
#include "hmicore/screen_gva.h"

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
  static FunctionKeys GetDefaultFunctionKeyDriverRight();

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

#endif  // HMICORE_HMI_GVA_DEFAULTS_H_
