//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file off.h
///
#ifndef HMICORE_STATES_OFF_H_
#define HMICORE_STATES_OFF_H_

#include <glog/logging.h>

#include <iostream>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {

struct StateOff : Hmi {
  void entry() override;
  void react(EventKeyPowerOn const &) override;
};

}  // namespace gva

#endif  // HMICORE_STATES_OFF_H_
