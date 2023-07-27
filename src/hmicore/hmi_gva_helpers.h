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

/// Class definition of the HmiHelper
class HmiHelper {
 public:
  /// Construct a table of licences
  static void TableLicences(WidgetTable *table);
  /// Construct a table of system information
  static void TableSystem(WidgetTable *table);
  /// Construct a table of alarms
  static void TableAlarms(WidgetTable *table);
};

class hmiScreenSize {
public:
    // Function to get the instance of the hmiScreenSize class
    static hmiScreenSize& getInstance() {
        static hmiScreenSize instance; // The only instance of hmiScreenSize will be created once
        return instance;
    }

    // Getter function for the tuple containing hmiScreenWidth and hmiScreenHeight
    std::tuple<int, int> getMinimumSize() const {
        return minimumSize;
    }

    // Setter function for the tuple containing hmiScreenWidth and hmiScreenHeight
    void setMinimumSize(int width, int height) {
        minimumSize = std::make_tuple(width, height);
    }

private:
    // Private constructor to prevent direct instantiation
    hmiScreenSize() {
        // Initialize the default values for hmiScreenWidth and hmiScreenHeight
        minimumSize = std::make_tuple(480, 300);
    }

    // Private copy constructor and assignment operator to prevent cloning
    hmiScreenSize(const hmiScreenSize&) = delete;
    hmiScreenSize& operator=(const hmiScreenSize&) = delete;

    // hmiScreenSize variable as a tuple
    std::tuple<int, int> minimumSize;
};

}  // namespace gva

#endif  // HMICORE_HMI_GVA_HELPERS_H_
