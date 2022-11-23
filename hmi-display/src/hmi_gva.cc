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
/// \brief HMI Manager
///
/// \file hmi_gva.cc
///

#include "hmi_gva.h"

#include <iostream>

#include "gva.h"
#include "view_gva.h"
#include "widgets/alarm_indicator.h"
#include "widgets/compass.h"

namespace gva {

void Hmi::SetCanvasPng(std::string file) {
  Hmi::GetScreen()->canvas.filename = file.c_str();
  Hmi::GetScreen()->canvas.bufferType = SurfaceType::kSurfaceFile;
  Hmi::GetScreen()->canvas.buffer = 0;
}

void Hmi::Reset() {
  screen_.status_bar->visible = true;
  screen_.function_top->Reset();
  screen_.function_left.Reset();
  screen_.function_right.Reset();
  Labels(screen_.labels);
  screen_.canvas.visible = false;
  screen_.canvas.bufferType = SurfaceType::kSurfaceNone;
  screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetVisible(false);
  screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetY(360 + 28);
  screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetX(161);
  screen_render_->GetWidget(WIDGET_TYPE_KEYBOARD)
      ->SetVisible((screen_render_->GetWidget(WIDGET_TYPE_KEYBOARD)->GetVisible()) ? true : false);
  screen_.table.visible_ = false;
  screen_.control->visible = true;
  screen_.message.visible = false;
  screen_.info.mode = ScreenMode::kModeOperational;
  alarmson_ = false;
}

void Hmi::Labels(LabelModeEnum labels) {
  switch (labels) {
    case LabelModeEnum::kLabelAll:
      if ((screen_.currentFunction == GvaFunctionEnum::kSituationalAwareness) ||
          (screen_.currentFunction == GvaFunctionEnum::kWeapon) ||
          (screen_.currentFunction == GvaFunctionEnum::kDriver))
        screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_.function_left.visible = true;
      screen_.function_right.visible = true;
      screen_.control->visible = true;
      screen_.function_top->visible = true;
      screen_.status_bar->visible = true;
      screen_.status_bar->y = 446;
      screen_render_->GetWidget(WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(true);
      screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetY(360 + 28);
      screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetX(161);
      screen_render_->GetWidget(WIDGET_TYPE_ALARM_INDICATOR)->SetY(423);
      break;
    case LabelModeEnum::kLabelStatusOnly:
      screen_.function_left.visible = false;
      screen_.function_right.visible = false;
      screen_.control->visible = false;
      screen_.function_top->visible = false;
      screen_.status_bar->visible = true;
      screen_.status_bar->y = 459;
      screen_render_->GetWidget(WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(true);
      screen_render_->GetWidget(WIDGET_TYPE_ALARM_INDICATOR)->SetY(423);
      screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetY(360 + 42);
      screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetX(161 - 106);
      break;
    case LabelModeEnum::kLabelMinimal:
      screen_.function_left.visible = false;
      screen_.function_right.visible = false;
      screen_.control->visible = false;
      screen_.function_top->visible = false;
      screen_.status_bar->visible = false;
      screen_render_->GetWidget(WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(false);
      screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetVisible(false);
      break;
  }
};

void Hmi::KeySide(GvaKeyEnum key) {
  switch (key) {
    case GvaKeyEnum::kKeyF1:
      screen_.function_left.labels[0].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF2:
      screen_.function_left.labels[1].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF3:
      screen_.function_left.labels[2].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF4:
      screen_.function_left.labels[3].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF5:
      screen_.function_left.labels[4].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF6:
      screen_.function_left.labels[5].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF7:
      screen_.function_right.labels[0].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF8:
      screen_.function_right.labels[1].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF9:
      screen_.function_right.labels[2].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF10:
      screen_.function_right.labels[3].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF11:
      screen_.function_right.labels[4].state = LabelStates::kLabelEnabledSelected;
      break;
    case GvaKeyEnum::kKeyF12:
      screen_.function_right.labels[5].state = LabelStates::kLabelEnabledSelected;
      break;
  }
}

GvaKeyEnum Hmi::Key(GvaKeyEnum keypress) {
  KeySide(keypress);
  switch (keypress) {
    case GvaKeyEnum::kKeyF13:
      screen_.control->labels[0].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF14:
      if (screen_.currentFunction == GvaFunctionEnum::kAlarmsX)
        screen_.control->labels[1].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF15:
      screen_.control->labels[2].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF16:
      screen_.control->labels[3].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF17:
      screen_.control->labels[4].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF18:
      screen_.control->labels[5].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF19:
      screen_.control->labels[6].state = LabelStates::kLabelEnabled;
      switch (screen_.labels) {
        case LabelModeEnum::kLabelAll:
          screen_.labels = LabelModeEnum::kLabelStatusOnly;
          break;
        case LabelModeEnum::kLabelStatusOnly:
          screen_.labels = LabelModeEnum::kLabelMinimal;
          break;
        case LabelModeEnum::kLabelMinimal:
          screen_.labels = LabelModeEnum::kLabelAll;
          break;
      }
      Labels(screen_.labels);
      break;
    case GvaKeyEnum::kKeyF20:
      screen_.control->labels[7].state = LabelStates::kLabelEnabled;
      screen_.message.visible = false;
      break;
    default:
      break;
  }
  return keypress;
}

GvaKeyEnum Hmi::KeySA(GvaKeyEnum keypress) {
  const std::string path = ConfigData::GetInstance()->GetImagePath();
  std::string filename;

  screen_.function_left.visible = true;
  screen_.function_right.visible = true;

  Compass *compass = static_cast<Compass *>(screen_render_->GetWidget(WIDGET_TYPE_COMPASS));

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF2:
      filename = path;
      filename.append("/Quad.png");
      SetCanvasPng(filename);
      break;
    case GvaKeyEnum::kKeyF4:
      filename = path;
      filename.append("/FrontRight.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(45);
      break;
    case GvaKeyEnum::kKeyF5:
      filename = path;
      filename.append("/FrontCenter.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(0);
      break;
    case GvaKeyEnum::kKeyF6:
      filename = path;
      filename.append("/FrontLeft.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(315);
      break;
    case GvaKeyEnum::kKeyF10:
      filename = path;
      filename.append("/Right.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(90);
      break;
    case GvaKeyEnum::kKeyF11:
      filename = path;
      filename.append("/Rear.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(180);
      break;
    case GvaKeyEnum::kKeyF12:
      filename = path;
      filename.append("/Left.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(270);
      break;
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
      screen_.message.visible = true;
      screen_.message.icon = ICON_INFO;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
  }
  return keypress;
}

//
// These are all of the states in this model
//
struct StateOn;
struct StateOff;
struct StateAlarms;
struct StateSA;
struct StateWPN;
struct StateDRV;
struct StateSYS;
struct StateDEF;
struct StateCOM;
struct StateBMS;

//
// Below are all the implementations of all teh states including all state transitions.
//
#include "src/states/alarms.cc"
#include "src/states/bms.cc"
#include "src/states/com.cc"
#include "src/states/def.cc"
#include "src/states/drv.cc"
#include "src/states/off.cc"
#include "src/states/on.cc"
#include "src/states/sa.cc"
#include "src/states/str.cc"
#include "src/states/sys.cc"
#include "src/states/wpn.cc"
// New states can be added here

ViewGvaManager *Hmi::manager_;
ResolutionType Hmi::view_;
StatusBar Hmi::status_;
FunctionSelect Hmi::top_;
CommonTaskKeys Hmi::bottom_;
Canvas Hmi::canvas_;
TableWidget Hmi::alarms_;
Screen Hmi::screen_;
ScreenGva *Hmi::screen_render_;
rendererMap *Hmi::map_;
GvaFunctionEnum Hmi::lastState_;
bool Hmi::alarmson_ = false;

//
// Initial state definition
//
FSM_INITIAL_STATE(Hmi, StateOff)

}  // namespace gva
