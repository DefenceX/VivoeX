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
///
/// \file def.cc
///

#include "def.h"

#include <glog/logging.h>

namespace gva {

GvaKeyEnum Hmi::KeyDEF(GvaKeyEnum keypress) {
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
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

void StateDEF::entry() {
  DLOG(INFO) << "Entering the DEF State";
  if (screen_.function_top->labels[2].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kDefensiveSystems);
    Reset();

    screen_.function_top->SetEnabled(2);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
    screen_.function_top->visible = true;
    screen_.function_top->labels[2].state = LabelStates::kLabelEnabledSelected;
  }
};

void StateDEF::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateDEF::react(EventKeySA const &) { transit<StateSA>(); };

void StateDEF::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateDEF::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateDEF::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateDEF::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateDEF::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateDEF::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateDEF::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateDEF::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateDEF::react(EventKeyFunction const &e) {
  KeyDEF(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateWPN>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateSYS>();
};

}  // namespace gva
