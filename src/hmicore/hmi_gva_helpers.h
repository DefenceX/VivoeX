//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file hmi_gva_helpers.h
///

#ifndef HMICORE_HMI_GVA_HELPERS_H_
#define HMICORE_HMI_GVA_HELPERS_H_
#include "hmicore/screen_gva.h"

namespace gva {

class HmiHelper {
 public:
  static void TableLicences(WidgetTable *table);
  static void TableSystem(WidgetTable *table);
  static void TableAlarms(WidgetTable *table);
};

}  // namespace gva

#endif  // HMICORE_HMI_GVA_HELPERS_H_
