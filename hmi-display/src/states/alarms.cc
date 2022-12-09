///
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
//
///
/// \brief Alarms state definition
///
/// \file alarms.cc
///

#include "alarms.h"

namespace gva {

GvaKeyEnum Hmi::KeyAlarms(GvaKeyEnum keypress) {
  WidgetTable *table = (WidgetTable *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable);

  switch (keypress) {
    case GvaKeyEnum::kKeyF17:  // Down Arrow
      table->SetPreviousRow();
      return keypress;
      break;
    case GvaKeyEnum::kKeyF18:  // Up Arrow
      table->SetNextRow();
      return keypress;
      break;
    default:  // Do nothing with other keys
      return GvaKeyEnum::kKeyUnknown;
      break;
  }
  return GvaKeyEnum::kKeyUnknown;
};

void StateAlarms::entry() {
  // Check to see if alarms was requested from hidden state, if so go back to last menu.
  if (screen_.control->labels_[1].state_ != LabelStates::kLabelHidden) {
    auto *table = (WidgetTable *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable);

    if (alarmson_) {
      alarmson_ = false;
      switch (lastState_) {
        case GvaFunctionEnum::kSituationalAwareness:
          transit<StateSA>();
          return;
        case GvaFunctionEnum::kWeapon:
          transit<StateWPN>();
          return;
        case GvaFunctionEnum::kDefensiveSystems:
          transit<StateDEF>();
          return;
        case GvaFunctionEnum::kSystems:
          transit<StateSYS>();
          return;
        case GvaFunctionEnum::kDriver:
          transit<StateDRV>();
          return;
        case GvaFunctionEnum::KSpecialToRole:
          transit<StateSTR>();
          return;
        case GvaFunctionEnum::kCommunications:
          transit<StateCOM>();
          return;
        case GvaFunctionEnum::kBattlefieldManagementSystem:
          transit<StateBMS>();
          return;
        default:
          return;  // Nothing more to do
      }
    }
    Reset();
    alarmson_ = true;
    manager_->SetScreen(&screen_, GvaFunctionEnum::kAlarmsX);
    HmiHelper::TableAlarms(table);
    table->SetVisible(true);

    // Update the controls
    screen_.control->ForceEnabledSelected(4);  // Up Arrow
    screen_.control->ForceEnabledSelected(5);  // Down Arrow
    screen_.control->ForceEnabledSelected(7);  // Enter
    screen_.control->ForceEnabledSelected(1);
  }
};

void StateAlarms::exit() {}

void StateAlarms::react(EventKeySA const &) { transit<StateSA>(); };

void StateAlarms::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateAlarms::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateAlarms::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateAlarms::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateAlarms::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateAlarms::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateAlarms::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateAlarms::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateAlarms::react(EventKeyFunction const &e) {
  Key(e.key);
  KeyAlarms(e.key);
};

}  // namespace gva
