//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file debug.h
///

#ifndef COMMON_DEBUG_H_
#define COMMON_DEBUG_H_

#include <stdint.h>
#include <stdio.h>

namespace gva {

///
/// \brief Dump hexidecimal values to stdout
///
/// \param data The data to dump
/// \param size The size of the data
///
void DumpHex(const uint8_t* data, size_t size);

}  // namespace gva

#endif  // COMMON_DEBUG_H_
