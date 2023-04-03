//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
#include <memory>

#include "hmicore/gva.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/plan_position_indicator.h"
#include "hmicore/widgets/table/table.h"

namespace gva {

void Hmi::SetCanvasPng(const std::string &file) {
  Hmi::GetScreen()->canvas.filename = file.c_str();
  Hmi::GetScreen()->canvas.bufferType = SurfaceType::kSurfaceFile;
  Hmi::GetScreen()->canvas.buffer = nullptr;
}

void Hmi::Reset() {
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
  screen_.labels = LabelModeEnum::kLabelAll;
  Labels(screen_.labels);
  screen_.function_top->ResetAllEnabled();
  screen_.canvas.visible = false;
  screen_.canvas.bufferType = SurfaceType::kSurfaceNone;
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetVisible(false);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(false);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeKeyboard)->SetVisible(false);
  if (screen_.currentFunction == GvaFunctionEnum::kDriver) {
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(190);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(120);
  } else {
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(190);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(330);
  }
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTopLabels)->SetVisible(true);
  screen_.control->SetDisabled(4);  // Up Arrow
  screen_.control->SetDisabled(5);  // Down Arrow
  screen_.control->SetDisabled(7);  // Enter
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
        screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeRightLabels)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeLeftLabels)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTopLabels)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetY(15);
      if (screen_.currentFunction == GvaFunctionEnum::kDriver) {
        screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(190);
        screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(120);

      } else {
        screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(190);
        screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(330);
      }
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetWidth(420);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetX(110);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetWidth(420);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetX(110);
      break;
    case LabelModeEnum::kLabelStatusOnly:
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeRightLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeLeftLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTopLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels)->SetVisible(false);
      screen_.function_top->visible = false;
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetY(2);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(160);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(120);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetWidth(kMinimumWidth - 40);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetX(20);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetWidth(kMinimumWidth - 40);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetX(20);
      break;
    case LabelModeEnum::kLabelMinimal:
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeRightLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeLeftLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTopLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(false);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetWidth(kMinimumWidth - 40);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable)->SetX(20);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetWidth(kMinimumWidth - 40);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetX(20);
      break;
  }
};

void Hmi::KeySide(GvaKeyEnum key) {
  // Clear any on screen messages
  screen_.message.visible = false;

  // Manage the changing of functional areas
  switch (key) {
    case GvaKeyEnum::kKeyF1:
      screen_.function_right.ResetAllEnabled();
      screen_.function_left.SetEnabled(0);
      break;
    case GvaKeyEnum::kKeyF2:
      screen_.function_right.ResetAllEnabled();
      screen_.function_left.SetEnabled(1);
      break;
    case GvaKeyEnum::kKeyF3:
      screen_.function_right.ResetAllEnabled();
      screen_.function_left.SetEnabled(2);
      break;
    case GvaKeyEnum::kKeyF4:
      screen_.function_right.ResetAllEnabled();
      screen_.function_left.SetEnabled(3);
      break;
    case GvaKeyEnum::kKeyF5:
      screen_.function_right.ResetAllEnabled();
      screen_.function_left.SetEnabled(4);
      break;
    case GvaKeyEnum::kKeyF6:
      screen_.function_right.ResetAllEnabled();
      screen_.function_left.SetEnabled(5);
      break;
    case GvaKeyEnum::kKeyF7:
      screen_.function_right.SetEnabled(0);
      screen_.function_left.ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF8:
      screen_.function_right.SetEnabled(1);
      screen_.function_left.ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF9:
      screen_.function_right.SetEnabled(2);
      screen_.function_left.ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF10:
      screen_.function_right.SetEnabled(3);
      screen_.function_left.ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF11:
      screen_.function_right.SetEnabled(4);
      screen_.function_left.ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF12:
      screen_.function_right.SetEnabled(5);
      screen_.function_left.ResetAllEnabled();
      break;
    default:
      break;
  }
}

GvaKeyEnum Hmi::Key(GvaKeyEnum keypress) {
  KeySide(keypress);
  switch (keypress) {
    case GvaKeyEnum::kKeyBlackout:
      screen_.canvas.blackout = screen_.canvas.blackout ? false : true;
      break;
    case GvaKeyEnum::kKeyF13:
      screen_.control->SetEnabledSelected(0);
      screen_.control->ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF14:
      screen_.control->SetEnabledSelected(1);
      screen_.control->ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF15:
      screen_.control->SetEnabledSelected(2);
      screen_.control->ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF16:  // Ack
      screen_.control->SetEnabledSelected(3);
      screen_.control->ResetAllEnabled();
      Hmi::ClearAlarms(screen_render_);
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeAlarmIndicator)->SetVisible(false);
      break;
    case GvaKeyEnum::kKeyF17:  // Up Arrow
      screen_.control->SetEnabledSelected(4);
      screen_.control->ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF18:  // Down Arrow
      screen_.control->SetEnabledSelected(5);
      screen_.control->ResetAllEnabled();
      break;
    case GvaKeyEnum::kKeyF19:
      screen_.control->SetEnabledSelected(6);
      screen_.control->ResetAllEnabled();
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
      screen_.control->SetEnabledSelected(7);
      screen_.control->ResetAllEnabled();
      screen_.message.visible = false;
      break;
    default:
      break;
  }
  return keypress;
}

void Hmi::ClearAlarms(std::shared_ptr<ScreenGva> screen_render) {
  // Clear alarms here till LDM
  auto bottom = (gva::WidgetBottomLabels *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels));
  bottom->DisableLabel(GvaKeyEnum::kKeyF16);
}

std::shared_ptr<ViewGvaManager> Hmi::manager_;
ResolutionType Hmi::view_;
FunctionSelect Hmi::top_;
CommonTaskKeys Hmi::bottom_;
Canvas Hmi::canvas_;
Screen Hmi::screen_;
std::shared_ptr<ScreenGva> Hmi::screen_render_;
std::shared_ptr<rendererMap> Hmi::map_;
GvaFunctionEnum Hmi::lastState_;
bool Hmi::alarmson_ = false;

//
// Initial state definition
//
FSM_INITIAL_STATE(Hmi, StateOff)

}  // namespace gva
