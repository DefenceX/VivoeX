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
/// \file utils.cc
///

#include <fcntl.h>
#include <unistd.h>

#include <iostream>

#include "log_gva.h"

namespace gva {

void SetBrightness(double brightness) {
  const uint32_t max = 24000;
  int fd = 0;
  auto value = (uint32_t)(brightness * max);
  fd = open("/sys/class/backlight/intel_backlight/brightness", O_WRONLY);
  if (fd == -1) {
    logGva::log("Cant open /sys/class/backlight/intel_backlight/brightness, try running with sudo",
                gva::DebugLevel::kLogError);
    close(fd);
    return;
  }

  if (std::string str_value = std::to_string(value);
      write(fd, str_value.c_str(), str_value.length()) != (int)str_value.length()) {
    logGva::log("Cant write /sys/class/backlight/intel_backlight/brightness", gva::DebugLevel::kLogError);
  }
  close(fd);
}

}  // namespace gva