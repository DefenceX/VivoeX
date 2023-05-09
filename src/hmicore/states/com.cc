//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file com.cc
///

#include "com.h"

namespace gva {

GvaKeyEnum Hmi::KeyCOM(GvaKeyEnum keypress) {
  screen_.function_right.visible = true;
  screen_.message.visible = true;

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

void StateCOM::entry() {
  DLOG(INFO) << "Entering the COM State";

  if (screen_.function_top->labels[6].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kCommunications);
    lastState_ = GvaFunctionEnum::kCommunications;
    Reset();
    screen_.function_top->SetEnabled(6);
  }
};

void StateCOM::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateCOM::react(EventKeySA const &) { transit<StateSA>(); };

void StateCOM::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateCOM::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateCOM::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateCOM::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateCOM::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateCOM::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateCOM::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateCOM::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateCOM::react(EventKeyFunction const &e) {
  KeyCOM(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSTR>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateBMS>();
};

};  // namespace gva
