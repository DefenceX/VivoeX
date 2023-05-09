//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file hmi_gva_defaults.cc
///

#include "hmi_gva_defaults.h"

#include "hmicore/gva.h"

namespace gva {

Screen DefaultSettings::GetDefaultScreen() {
  Screen screen;
  screen.canvas.visible = true;
  screen.info.gpsDevice = ConfigData::GetInstance()->GetGpsDevice();
  screen.info.mode = ScreenMode::kModeOperational;
  screen.info.name = "Commanders Display";
  return screen;
}

CommonTaskKeys DefaultSettings::GetDefaultCommonTaskKeys() {
  CommonTaskKeys common_task_keys;
  common_task_keys.visible_ = true;
  common_task_keys.labels_[0].state_ = LabelStates::kLabelDisabled;
  common_task_keys.labels_[0].text_ = "Up";
  common_task_keys.labels_[1].state_ = LabelStates::kLabelEnabled;
  common_task_keys.labels_[1].text_ = "Alarms";
  common_task_keys.labels_[2].state_ = LabelStates::kLabelDisabled;
  common_task_keys.labels_[2].text_ = "Threats";
  common_task_keys.labels_[3].state_ = LabelStates::kLabelDisabled;
  common_task_keys.labels_[3].text_ = "Ack";
  common_task_keys.labels_[4].state_ = LabelStates::kLabelDisabled;
  common_task_keys.labels_[4].text_ = "";
  common_task_keys.labels_[5].state_ = LabelStates::kLabelDisabled;
  common_task_keys.labels_[5].text_ = "";
  common_task_keys.labels_[6].state_ = LabelStates::kLabelEnabled;
  common_task_keys.labels_[6].text_ = "Labels";
  common_task_keys.labels_[7].state_ = LabelStates::kLabelDisabled;
  common_task_keys.labels_[7].text_ = "Enter";
  return common_task_keys;
}

FunctionSelect DefaultSettings::GetDefaultFunctionSelect() {
  FunctionSelect function_select;
  function_select.visible = true;
  function_select.labels[0].state = LabelStates::kLabelEnabled;
  function_select.labels[1].state = LabelStates::kLabelEnabled;
  function_select.labels[2].state = LabelStates::kLabelEnabled;
  function_select.labels[3].state = LabelStates::kLabelEnabledSelected;
  function_select.labels[4].state = LabelStates::kLabelEnabled;
  function_select.labels[5].state = LabelStates::kLabelDisabled;
  function_select.labels[6].state = LabelStates::kLabelEnabled;
  function_select.labels[7].state = LabelStates::kLabelEnabled;
  return function_select;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelHidden;
  keys.labels[0].text = "Unused";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelHidden;
  keys.labels[1].text = "Unused";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeysSituationalAwarenessLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelDisabled;
  keys.labels[0].text = "Remote.Wpn Sight";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "Quad";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelEnabled;
  keys.labels[3].text = "Front right";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelEnabledSelected;
  keys.labels[4].text = "Front";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelEnabled;
  keys.labels[5].text = "Front left";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeysSituationalAwarenessRight() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelHidden;
  keys.labels[0].text = "Unused";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelHidden;
  keys.labels[1].text = "Unused";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelEnabled;
  keys.labels[3].text = "Right";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelEnabled;
  keys.labels[4].text = "Rear";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelEnabled;
  keys.labels[5].text = "Left";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeysWeaponsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabledSelected;
  keys.labels[0].text = "Wpn Sight";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "IR Sight";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeysWeaponsRight() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabled;
  keys.labels[0].text = "icon:waterfall";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "icon:cross";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeysDefensiveSystemsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelDisabled;
  keys.labels[0].text = "ECM";
  keys.labels[0].toggleActive = true;
  keys.labels[0].toggleText1 = "On";
  keys.labels[0].toggleText2 = "Off";
  keys.labels[1].state = LabelStates::kLabelDisabled;
  keys.labels[1].text = "Spike";
  keys.labels[1].toggleActive = true;
  keys.labels[1].toggleText1 = "On";
  keys.labels[1].toggleText2 = "Off";
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeySystemsRight() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].text = "Commander.Health";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelDisabled;
  keys.labels[1].text = "Gunner.Health";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelDisabled;
  keys.labels[2].text = "Driver.Health";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelDisabled;
  keys.labels[3].text = "Roll.Allocation";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelEnabled;
  keys.labels[4].text = "Blackout";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelEnabled;
  keys.labels[5].text = "icon:exit";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeySystemsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabledSelected;
  keys.labels[0].text = "Overview";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelDisabled;
  keys.labels[1].text = "Automotive";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelDisabled;
  keys.labels[2].text = "HUMS";
  keys.labels[2].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelDisabled;
  keys.labels[3].text = "System";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelEnabled;
  keys.labels[4].text = "Licences";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelDisabled;
  keys.labels[5].text = "BIT";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyDriverRight() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabledSelected;
  keys.labels[0].text = "Assist";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "PPI Mode";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyCommunicationsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelDisabled;
  keys.labels[0].text = "Comms";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelDisabled;
  keys.labels[1].text = "RF State";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelHidden;
  keys.labels[2].text = "Unused";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemLeft() {
  FunctionKeys keys;
  LabelStates state;
  keys.visible = true;
  if (ConfigData::GetInstance()->GetMapEnabled())
    state = LabelStates::kLabelEnabled;
  else
    state = LabelStates::kLabelDisabled;
  keys.labels[0].state = state;
  keys.labels[0].text = "Mission";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelHidden;
  keys.labels[1].text = "Unused";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = state;
  keys.labels[2].text = "icon:uparrow";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = state;
  keys.labels[3].text = "icon:downarrow";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = state;
  keys.labels[4].text = "icon:plus";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = state;
  keys.labels[5].text = "icon:rotateleft";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemRight() {
  FunctionKeys keys;
  LabelStates state;
  keys.visible = true;
  if (ConfigData::GetInstance()->GetMapEnabled())
    state = LabelStates::kLabelEnabled;
  else
    state = LabelStates::kLabelDisabled;
  keys.labels[0].state = LabelStates::kLabelHidden;
  keys.labels[0].text = "Unused";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelHidden;
  keys.labels[1].text = "Unused";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = state;
  keys.labels[2].text = "icon:leftarrow";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = state;
  keys.labels[3].text = "icon:rightarrow";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = state;
  keys.labels[4].text = "icon:minus";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = state;
  keys.labels[5].text = "icon:rotateright";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyAlarmsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabled;
  keys.labels[0].text = "Sort.Ascending";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "Reset";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelEnabled;
  keys.labels[2].text = "Hide.Overridden";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelEnabled;
  keys.labels[3].text = "Select.All";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelHidden;
  keys.labels[4].text = "Unused";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelHidden;
  keys.labels[5].text = "Unused";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyAlarmsRight() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabled;
  keys.labels[0].text = "Override";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "Clear";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelEnabled;
  keys.labels[2].text = "Add Note";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelHidden;
  keys.labels[3].text = "Unused";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelEnabled;
  keys.labels[4].text = "Page.Up";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelEnabled;
  keys.labels[5].text = "Page.Down";
  keys.labels[5].toggleActive = false;
  return keys;
}

}  // namespace gva
