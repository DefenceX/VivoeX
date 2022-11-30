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
///
/// \brief HMI Manager is the state machine that drives all the screens as defines within the system, below is a diagram
/// of a simple example of a system with one screen per functional area.
///
/// \file hmi_gva.cc
///
/// \startuml
/// skinparam monochrome true
///
/// [*] --> PowerOn
/// PowerOn : This is the inital state when the system starts
/// PowerOn --> Systems
///
/// SituationalAwareness --> Weapons
/// SituationalAwareness --> Systems
/// SituationalAwareness --> DefensiveSystems
/// SituationalAwareness --> Driver
/// SituationalAwareness --> SpecialToRole
/// SituationalAwareness --> Communications
/// SituationalAwareness --> BattlefieldManagementSystem
/// SituationalAwareness --> Alarms
/// SituationalAwareness --> PowerOff
///
/// Systems --> SituationalAwareness
/// Systems --> Weapons
/// Systems --> DefensiveSystems
/// Systems --> Driver
/// Systems --> SpecialToRole
/// Systems --> Communications
/// Systems --> BattlefieldManagementSystem
/// Systems --> Alarms
/// Systems --> PowerOff
///
/// Weapons --> SituationalAwareness
/// Weapons --> Systems
/// Weapons --> DefensiveSystems
/// Weapons --> Driver
/// Weapons --> SpecialToRole
/// Weapons --> Communications
/// Weapons --> BattlefieldManagementSystem
/// Weapons --> Alarms
/// Weapons --> PowerOff
///
/// DefensiveSystems --> SituationalAwareness
/// DefensiveSystems --> Systems
/// DefensiveSystems --> Weapons
/// DefensiveSystems --> Driver
/// DefensiveSystems --> SpecialToRole
/// DefensiveSystems --> Communications
/// DefensiveSystems --> BattlefieldManagementSystem
/// DefensiveSystems --> Alarms
/// DefensiveSystems --> PowerOff
///
/// Driver --> SituationalAwareness
/// Driver --> Systems
/// Driver --> Weapons
/// Driver --> DefensiveSystems
/// Driver --> SpecialToRole
/// Driver --> Communications
/// Driver --> BattlefieldManagementSystem
/// Driver --> Alarms
/// Driver --> PowerOff
///
/// SpecialToRole --> SituationalAwareness
/// SpecialToRole --> Systems
/// SpecialToRole --> Weapons
/// SpecialToRole --> DefensiveSystems
/// SpecialToRole --> Driver
/// SpecialToRole --> Communications
/// SpecialToRole --> BattlefieldManagementSystem
/// SpecialToRole --> Alarms
/// SpecialToRole --> PowerOff
///
/// Communications --> SituationalAwareness
/// Communications --> Systems
/// Communications --> Weapons
/// Communications --> DefensiveSystems
/// Communications --> Driver
/// Communications --> SpecialToRole
/// Communications --> BattlefieldManagementSystem
/// Communications --> Alarms
/// Communications --> PowerOff
///
/// BattlefieldManagementSystem --> SituationalAwareness
/// BattlefieldManagementSystem --> Systems
/// BattlefieldManagementSystem --> Weapons
/// BattlefieldManagementSystem --> DefensiveSystems
/// BattlefieldManagementSystem --> Driver
/// BattlefieldManagementSystem --> Communications
/// BattlefieldManagementSystem --> BattlefieldManagementSystem
/// BattlefieldManagementSystem --> Communications
/// BattlefieldManagementSystem --> Alarms
/// BattlefieldManagementSystem --> PowerOff
/// BattlefieldManagementSystem : This is the BMS systems interface
///
/// Alarms -> SituationalAwareness
/// Alarms --> Weapons
/// Alarms --> DefensiveSystems
/// Alarms --> Driver
/// Alarms --> Communications
/// Alarms --> BattlefieldManagementSystem
/// Alarms --> Communications
/// Alarms --> BattlefieldManagementSystem
/// Alarms : You can jump to alarms from any screen to action caution, warnings and alerts
///
/// PowerOff --> [*]
///
/// \enduml

#include "hmi_gva.h"

#include <iostream>

#include "src/gva.h"
#include "src/view_gva.h"
#include "widgets/alarm_indicator.h"
#include "widgets/compass.h"

namespace gva {

void Hmi::SetCanvasPng(const std::string file) {
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
  screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetVisible(false);
  screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetY(360 + 28);
  screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetX(161);
  screen_.control->visible_ = true;
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
        screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetVisible(true);
      screen_.function_left.visible = true;
      screen_.function_right.visible = true;
      screen_.control->visible_ = true;
      screen_.function_top->visible = true;
      screen_.status_bar->visible = true;
      screen_.status_bar->y = 446;
      screen_render_->GetWidget(widget::KWidgetTypeAlarmIndicator)->SetVisible(true);
      screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetY(360 + 28);
      screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetX(161);
      screen_render_->GetWidget(widget::KWidgetTypeAlarmIndicator)->SetY(423);
      break;
    case LabelModeEnum::kLabelStatusOnly:
      screen_.function_left.visible = false;
      screen_.function_right.visible = false;
      screen_.control->visible_ = false;
      screen_.function_top->visible = false;
      screen_.status_bar->visible = true;
      screen_.status_bar->y = 459;
      screen_render_->GetWidget(widget::KWidgetTypeAlarmIndicator)->SetVisible(true);
      screen_render_->GetWidget(widget::KWidgetTypeAlarmIndicator)->SetY(423);
      screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetY(360 + 42);
      screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetX(161 - 106);
      break;
    case LabelModeEnum::kLabelMinimal:
      screen_.function_left.visible = false;
      screen_.function_right.visible = false;
      screen_.control->visible_ = false;
      screen_.function_top->visible = false;
      screen_.status_bar->visible = false;
      screen_render_->GetWidget(widget::KWidgetTypeAlarmIndicator)->SetVisible(false);
      screen_render_->GetWidget(widget::KWidgetTypeCompass)->SetVisible(false);
      break;
  }
};

void Hmi::KeySide(GvaKeyEnum key) {
  // Clear any onscreen messages
  screen_.message.visible = false;

  // Reset the active label/s
  screen_.function_left.visible = true;
  for (auto &label : screen_.function_left.labels) {
    if (label.state == LabelStates::kLabelEnabledSelected) label.state = LabelStates::kLabelEnabled;
  }
  screen_.function_right.visible = true;
  for (auto &label : screen_.function_right.labels) {
    if (label.state == LabelStates::kLabelEnabledSelected) label.state = LabelStates::kLabelEnabled;
  }

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
    default:
      printf("File %s:%d, %s()\n", __FILE__, __LINE__, __FUNCTION__);

      for (auto &label : screen_.function_right.labels) {
        if ((label.state == LabelStates::kLabelEnabledSelectedChanging) ||
            (label.state == LabelStates::kLabelEnabledSelected)) {
          label.state == LabelStates::kLabelEnabledSelected;
        }
      }
  }
}

GvaKeyEnum Hmi::Key(GvaKeyEnum keypress) {
  KeySide(keypress);
  switch (keypress) {
    case GvaKeyEnum::kKeyF13:
      screen_.control->labels_[0].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF14:
      if (screen_.currentFunction == GvaFunctionEnum::kAlarmsX)
        screen_.control->labels_[1].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF15:
      screen_.control->labels_[2].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF16:
      screen_.control->labels_[3].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF17:
      screen_.control->labels_[4].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF18:
      screen_.control->labels_[5].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF19:
      screen_.control->labels_[6].state_ = LabelStates::kLabelEnabled;
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
      screen_.control->labels_[7].state_ = LabelStates::kLabelEnabled;
      screen_.message.visible = false;
      break;
    default:
      break;
  }
  return keypress;
}

void Hmi::ResetState(LabelStates *state) {
  switch (screen_.function_top->labels[7].state) {
    case LabelStates::kLabelEnabledSelectedChanging:
    case LabelStates::kLabelEnabledSelected:
      *state = LabelStates::kLabelEnabled;
      break;
  }
}

ViewGvaManager *Hmi::manager_;
ResolutionType Hmi::view_;
StatusBar Hmi::status_;
FunctionSelect Hmi::top_;
CommonTaskKeys Hmi::bottom_;
Canvas Hmi::canvas_;
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
