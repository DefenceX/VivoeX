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
#include "hmicore/renderer_cairo.h"
#include "gva.h"
#include "config_reader.h"
#include "states/base_hmi.h"


namespace gva {

/// Class definition of the HmiHelper
class HmiHelper {
 public:
  /// Construct a table of licences
  static void TableLicences(WidgetTable *table);
  /// Construct a table of system information
  static void TableSystem(WidgetTable *table);
  /// Construct a table of alarms
  static void TableAlarms(WidgetTable *table);
  /// Change canvas size to accomdate bezel buttons
  static void bezelButtons(WidgetOnscreenBezelBtns *onscreenBezelBtns);
};

}  // namespace gva

#endif  // HMICORE_HMI_GVA_HELPERS_H_
