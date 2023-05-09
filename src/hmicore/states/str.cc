//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file str.cc
///

#include "str.h"

namespace gva {

GvaKeyEnum Hmi::KeySTR(GvaKeyEnum keypress) {
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
      screen_.message.detail.text = "Operation not implemented !";
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

void StateSTR::entry() {
  DLOG(INFO) << "Entering the STR State";

  if (screen_.function_top->labels[5].state != LabelStates::kLabelHidden) {
    Reset();
    manager_->SetScreen(&screen_, GvaFunctionEnum::KSpecialToRole);
    lastState_ = GvaFunctionEnum::KSpecialToRole;
    screen_.function_top->SetEnabled(5);
  }
};

void StateSTR::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateSTR::react(EventKeySA const &) { transit<StateSA>(); };

void StateSTR::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateSTR::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateSTR::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateSTR::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateSTR::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateSTR::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateSTR::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateSTR::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateSTR::react(EventKeyFunction const &e) {
  DLOG(INFO) << "Leaving the STR State";

  KeySTR(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateDRV>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateCOM>();
};

}  // namespace gva
