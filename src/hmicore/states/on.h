//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file on.h
///
#ifndef HMICORE_STATES_ON_H_
#define HMICORE_STATES_ON_H_

#include <glog/logging.h>

#include <iostream>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/hmi_gva_helpers.h"
#include "hmicore/view_gva.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {

/// The On state
struct StateOn : Hmi {
  void entry() override;
};

}  // namespace gva

#endif  // HMICORE_STATES_ON_H_
