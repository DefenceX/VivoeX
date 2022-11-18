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
#ifndef HMI_DISPLAY_SRC_HMI_GVA_DEFAULT_H_
#define HMI_DISPLAY_SRC_HMI_GVA_DEFAULT_H_

#include "src/gva.h"
#include "src/screen_gva.h"

namespace gva {

class DefaultSettings {
 public:
  DefaultSettings() = default;

  static CommonTaskKeys GetDefaultCommonTaskKeys() {
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

  static FunctionSelect GetDefaultFunctionSelect() {
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
  }

  static StatusBar GetDefaultStatusBar() {
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
  }

  static Canvas GetDefaultCanvas() {
    Canvas canvas;
    canvas.visible = true;
    canvas.bufferType = SurfaceType::kSurfaceNone;
    canvas.filename = "";
    canvas.buffer = nullptr;
    canvas.surface = nullptr;
  }

  static FunctionKeys GetDefaultFunctionKeysSituationalAwarenessLeft() {
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
  }

  static FunctionKeys GetDefaultFunctionKeysSituationalAwarenessRight() {
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
  }

  static FunctionKeys GetDefaultFunctionKeysWeaponsLeft() {
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
  }

  static FunctionKeys GetDefaultFunctionKeysWeaponsRight() {
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
  }

 private:
};
}  // namespace gva

#endif  // HMI_DISPLAY_SRC_HMI_GVA_DEFAULT_H_