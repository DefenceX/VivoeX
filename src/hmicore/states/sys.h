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
/// \file sys.h
///
#ifndef HMICORE_STATES_SYS_H_
#define HMICORE_STATES_SYS_H_

#include <iostream>
#include <glog/logging.h>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {

struct StateSYS : Hmi {
  void entry() override;
  void react(EventKeyPowerOn const &) override;
  void react(EventKeySA const &) override;
  void react(EventKeyWPN const &) override;
  void react(EventKeyDEF const &) override;
  void react(EventKeySYS const &) override;
  void react(EventKeyDRV const &) override;
  void react(EventKeySTR const &) override;
  void react(EventKeyCOM const &) override;
  void react(EventKeyBMS const &) override;
  void react(EventKeyAlarms const &) override;
  void react(EventKeyFunction const &e) override;
};

}  // namespace gva

#endif  // HMICORE_STATES_SYS_H_
