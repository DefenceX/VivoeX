//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file wpn.cc
///

#include "wpn.h"

#include "hmicore/gva.h"

namespace gva {

GvaKeyEnum Hmi::KeyWPN(GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF8:  // Enable Waterfall sight
    case GvaKeyEnum::kKeyF7:  // Enable Cross hair sight
      // This is the only active screen at this time
      screen_.message.visible = false;
      break;
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = widget::IconType::kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

void StateWPN::entry() {
  DLOG(INFO) << "Entering the WPN State";

  if (screen_.function_top->labels[1].state != LabelStates::kLabelHidden) {
    std::string filename;
    manager_->SetScreen(&screen_, GvaFunctionEnum::kWeapon);
    Reset();
    lastState_ = GvaFunctionEnum::kWeapon;
    screen_.function_top->SetEnabled(1);

    if (screen_.labels != LabelModeEnum::kLabelMinimal)
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);
    screen_.canvas.visible = true;
    filename = ConfigData::GetInstance()->GetImagePath();
    filename.append("/FrontCenter.png");
    SetCanvasPng(filename.c_str());
  }
};

void StateWPN::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateWPN::react(EventKeySA const &) { transit<StateSA>(); };

void StateWPN::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateWPN::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateWPN::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateWPN::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateWPN::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateWPN::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateWPN::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateWPN::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateWPN::react(EventKeyFunction const &e) {
  DLOG(INFO) << "Leaving the WPN State";

  KeyWPN(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSA>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateDEF>();
};

}  // namespace gva
