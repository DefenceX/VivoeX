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
/// \brief The default settings for on screen widgets
///
/// \file hmi_gva_defaults.cc
///

#include "hmi_gva_defaults.h"

#include "src/gva.h"

namespace gva {

Screen DefaultSettings::GetDefaultScreen() {
  Screen screen;
  screen.canvas.visible = true;
  // screen.info.gpsDevice = ConfigData::GetInstance()->;
  screen.info.mode = ScreenMode::kModeOperational;
  screen.info.name = "Generic Vehicle HMI";
  return screen;
}

CommonTaskKeys DefaultSettings::GetDefaultCommonTaskKeys() {
  CommonTaskKeys common_task_keys;
  common_task_keys.visible = true;
  common_task_keys.labels[0].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[0].text = "Up";
  common_task_keys.labels[1].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[1].text = "Alarms";
  common_task_keys.labels[2].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[2].text = "Threats";
  common_task_keys.labels[3].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[3].text = "Ack";
  common_task_keys.labels[4].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[4].text = "↑";
  common_task_keys.labels[5].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[5].text = "↓";
  common_task_keys.labels[6].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[6].text = "Labels";
  common_task_keys.labels[7].state = LabelStates::kLabelEnabledSelected;
  common_task_keys.labels[7].text = "Enter";
  return common_task_keys;
}

FunctionSelect DefaultSettings::GetDefaultFunctionSelect() {
  FunctionSelect function_select;
  function_select.visible = true;
  function_select.labels[0].state = LabelStates::kLabelEnabledSelected;
  function_select.labels[1].state = LabelStates::kLabelEnabled;
  function_select.labels[2].state = LabelStates::kLabelEnabled;
  function_select.labels[3].state = LabelStates::kLabelEnabled;
  function_select.labels[4].state = LabelStates::kLabelEnabled;
  function_select.labels[5].state = LabelStates::kLabelEnabled;
  function_select.labels[6].state = LabelStates::kLabelDisabled;
  function_select.labels[7].state = LabelStates::kLabelEnabled;
  return function_select;
}

StatusBar DefaultSettings::GetDefaultStatusBar() {
  StatusBar status_bar;
  status_bar.visible = true;
  status_bar.x = DEFAULT_HEIGHT - 11;
  status_bar.y = 0;
  status_bar.location.locationFormat = LocationEnum::kLocationFormatMgrs;
  status_bar.location.lon = gva::ConfigData::GetInstance()->GetTestLon();
  status_bar.location.lat = gva::ConfigData::GetInstance()->GetTestLat();
  status_bar.labels[0].text = "00:00:00, 01/01/1973";
  status_bar.labels[1].text = "LON/LAT";
  status_bar.labels[2].text = "Lat:0.000000 Lon:-0.000000    [1,3]";
  status_bar.labels[3].text = "W:0";
  status_bar.labels[4].text = "A:5";
  status_bar.labels[5].text = "C:1";
  status_bar.labels[6].text = "O:2";
  return status_bar;
}

Canvas DefaultSettings::GetDefaultCanvas() {
  Canvas canvas;
  canvas.visible = true;
  canvas.bufferType = SurfaceType::kSurfaceNone;
  canvas.filename = "";
  canvas.buffer = nullptr;
  canvas.surface = nullptr;
  return canvas;
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
  keys.labels[0].state = LabelStates::kLabelEnabledSelected;
  keys.labels[0].text = "Wpn Sight";
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
  keys.labels[4].state = LabelStates::kLabelEnabled;
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

FunctionKeys DefaultSettings::GetDefaultFunctionKeysDefensiveSystemsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelDisabled;
  keys.labels[0].text = "ECM";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelDisabled;
  keys.labels[1].text = "Spike";
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

FunctionKeys DefaultSettings::GetDefaultFunctionKeySystemsRight() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].state = LabelStates::kLabelEnabledSelected;
  keys.labels[0].text = "Overview";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "Automotive";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelEnabled;
  keys.labels[2].text = "HUMS";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelEnabled;
  keys.labels[3].text = "System";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = LabelStates::kLabelEnabled;
  keys.labels[4].text = "Licences";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = LabelStates::kLabelEnabled;
  keys.labels[5].text = "BIT";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeySystemsLeft() {
  FunctionKeys keys;
  keys.visible = true;
  keys.labels[0].text = "Commander.Health";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "Gunner.Health";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelEnabled;
  keys.labels[2].text = "Driver.Health";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = LabelStates::kLabelEnabled;
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

FunctionKeys DefaultSettings::GetDefaultFunctionKeyDriverLeft() {
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
  keys.visible = true;
#if (ENABLE_OSMSCOUT)
  LabelStates state = LabelStates::kLabelEnabled;
#else
  LabelStates state = LabelStates::kLabelDisabled;
#endif
  keys.labels[0].state = state;
  keys.labels[0].text = "Mission";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelHidden;
  keys.labels[1].text = "Unused";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = state;
  keys.labels[2].text = "Shift.up";
  keys.labels[2].toggleActive = false;
  keys.labels[3].state = state;
  keys.labels[3].text = "Shift.down";
  keys.labels[3].toggleActive = false;
  keys.labels[4].state = state;
  keys.labels[4].text = "Zoom +";
  keys.labels[4].toggleActive = false;
  keys.labels[5].state = state;
  keys.labels[5].text = "Rotate.>>";
  keys.labels[5].toggleActive = false;
  return keys;
}

FunctionKeys DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemRight() {
  FunctionKeys keys;
  keys.visible = true;
#if (ENABLE_OSMSCOUT)
  LabelStates state = LabelStates::kLabelEnabled;
#else
  LabelStates state = LabelStates::kLabelDisabled;
#endif
  keys.labels[0].state = state;
  keys.labels[0].text = "Unused";
  keys.labels[0].toggleActive = LabelStates::kLabelHidden;
  keys.labels[1].state = state;
  keys.labels[1].text = "Unused";
  keys.labels[1].toggleActive = LabelStates::kLabelHidden;
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
  keys.labels[0].text = "Sort";
  keys.labels[0].toggleActive = false;
  keys.labels[1].state = LabelStates::kLabelEnabled;
  keys.labels[1].text = "Order";
  keys.labels[1].toggleActive = false;
  keys.labels[2].state = LabelStates::kLabelEnabled;
  keys.labels[2].text = "Show.Overridden";
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
