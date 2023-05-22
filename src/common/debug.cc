//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file debug.cc
///

#include "debug.h"

#include <array>
#include <cstring>
#include <iomanip>
#include <iostream>

namespace gva {

///
/// \brief pad the hex dump
///
/// \param i
/// \param j
///
void Pad(size_t i, size_t j) {
  if ((i + 1) % 16 <= 8) {
    std::cout << ' ';
  }

  for (j = (i + 1) % 16; j < 16; ++j) {
    std::cout << "   ";
  }
}

void DumpHex(const uint8_t *data, size_t size) {
  const auto *bytes = static_cast<const unsigned char *>(data);
  std::array<uint8_t, 17> ascii;
  size_t j = 0;
  ascii[16] = '\0';

  for (size_t i = 0; i < size; ++i) {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(bytes[i]) << ' ';

    if (bytes[i] >= ' ' && bytes[i] <= '~') {
      ascii[i % 16] = bytes[i];
    } else {
      ascii[i % 16] = '.';
    }

    if ((i + 1) % 8 == 0 || i + 1 == size) {
      std::cout << ' ';

      if ((i + 1) % 16 == 0) {
        std::cout << "|  " << ascii.data() << '\n';
      } else if (i + 1 == size) {
        ascii[(i + 1) % 16] = '\0';
        Pad(i, j);
        std::cout << "|  " << ascii.data() << '\n';
      }
    }
  }
}

}  // namespace gva
