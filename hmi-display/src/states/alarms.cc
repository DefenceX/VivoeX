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
// \brief
//
// \file alarms.cc
///

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
/// \brief Alarms state definition
///
/// \file alarms.cc
///

#include "alarms.h"

namespace gva {

void StateAlarms::entry() {
  // Check to see if alarms was requested from hidden state, if so go back to last menu.
  if (screen_.control->labels_[1].state_ != LabelStates::kLabelHidden) {
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
      }
    }
    Reset();
    alarmson_ = true;
    manager_->SetScreen(&screen_, GvaFunctionEnum::kAlarmsX);
    HmiHelper::TableAlarms(&screen_.table);
    screen_.table.visible_ = true;
  }
};

void StateAlarms::react(EventKeySA const &) { transit<StateSA>(); };

void StateAlarms::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateAlarms::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateAlarms::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateAlarms::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateAlarms::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateAlarms::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateAlarms::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateAlarms::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateAlarms::react(EventKeyFunction const &e) { Key(e.key); };

}  // namespace gva