//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file hmi_gva.h
///

#ifndef HMICORE_HMI_GVA_H_
#define HMICORE_HMI_GVA_H_
#include <iostream>
#include <string>

#include "hmicore/config_reader.h"
#include "hmicore/gva.h"
#include "hmicore/hmi_gva_defaults.h"
#include "hmicore/hmi_gva_helpers.h"
#include "hmicore/renderer_map.h"
#include "hmicore/screen_gva.h"
#include "hmicore/states/alarms.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/states/bms.h"
#include "hmicore/states/com.h"
#include "hmicore/states/def.h"
#include "hmicore/states/drv.h"
#include "hmicore/states/off.h"
#include "hmicore/states/on.h"
#include "hmicore/states/sa.h"
#include "hmicore/states/str.h"
#include "hmicore/states/sys.h"
#include "hmicore/states/wpn.h"
#include "hmicore/view_gva.h"

namespace gva {

/// Alias for HMI
using hmi = Hmi;

}  // namespace gva

#endif  // HMICORE_HMI_GVA_H_
