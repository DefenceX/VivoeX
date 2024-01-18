//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file drv.cc
///

#include "drv.h"

#include "hmicore/widgets/driver/rpm_fuel.h"
#include "hmicore/widgets/driver/speedometer.h"

namespace gva {

StateDRV::StateDRV() = default;

GvaKeyEnum Hmi::KeyDRV(GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = widget::IconType::kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
    default:  // LotsThe state machine for of keys we dont care about
      break;
  }
  return keypress;
}

void StateDRV::entry() {
  if (screen_.function_top->labels[4].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kDriver);
    Reset();
    lastState_ = GvaFunctionEnum::kDriver;
    if (screen_.labels != LabelModeEnum::kLabelMinimal)
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);

    screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetVisible(true);
    screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetX(320);
    screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetY(750);

    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetVisible(true);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetX(950);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetY(750);

    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
    screen_.function_top->SetEnabled(4);

    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCanvas)->SetVisible(false);
    video_ = (gva::WidgetVideo *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeVideo));
    video_->SetSessionName("driver");
    video_->SetIpAddress("239.192.20.1");
    video_->SetVisible(true);
  }
};

void StateDRV::exit() {
  // Switch the dials off now not needed in other states
  screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetVisible(false);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetVisible(false);
}

void StateDRV::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateDRV::react(EventKeySA const &) { transit<StateSA>(); };

void StateDRV::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateDRV::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateDRV::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateDRV::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateDRV::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateDRV::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateDRV::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateDRV::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateDRV::react(EventKeyFunction const &e) {
  KeyDRV(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSYS>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateSTR>();
};

}  // namespace gva
