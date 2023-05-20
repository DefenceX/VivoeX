//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file str.h
///
#ifndef HMICORE_STATES_STR_H_
#define HMICORE_STATES_STR_H_

#include <glog/logging.h>

#include <iostream>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {

/// The STR state
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

#endif  // HMICORE_STATES_STR_H_
