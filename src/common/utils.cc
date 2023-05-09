//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file utils.cc
///

#include <fcntl.h>
#include <glog/logging.h>
#include <unistd.h>

#include <iostream>

#include "hmicore/gva.h"

namespace gva {

void SetBrightness(double brightness) {
  const uint32_t max = 24000;
  int fd = 0;
  auto value = (uint32_t)(brightness * max);
  fd = open("/sys/class/backlight/intel_backlight/brightness", O_WRONLY);
  if (fd == -1) {
    LOG(ERROR) << "Cant open /sys/class/backlight/intel_backlight/brightness, try running with sudo";
    close(fd);
    return;
  }

  if (std::string str_value = std::to_string(value);
      write(fd, str_value.c_str(), str_value.length()) != (int)str_value.length()) {
    LOG(ERROR) << "Cant write /sys/class/backlight/intel_backlight/brightness";
  }
  close(fd);
}

}  // namespace gva