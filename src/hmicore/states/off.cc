//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file off.cc
///
#include "off.h"

#include <glog/logging.h>

namespace gva {

void StateOff::entry() { DLOG(INFO) << "Entering the Off State"; };

void StateOff::react(EventKeyPowerOn const &) { transit<StateOn>(); };

}  // namespace gva
