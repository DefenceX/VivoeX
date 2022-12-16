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
//
///
/// \file str.h
///
#ifndef HMI_DISPLAY_SRC_STATES_STR_H_
#define HMI_DISPLAY_SRC_STATES_STR_H_

#include <iostream>

#include "src/gva.h"
#include "src/hmi_gva.h"
#include "src/states/base_hmi.h"
#include "src/view_gva.h"
#include "src/widgets/alarm_indicator.h"
#include "src/widgets/compass.h"

namespace gva {

struct StateSTR : Hmi {
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

#endif  // HMI_DISPLAY_SRC_STATES_STR_H_
