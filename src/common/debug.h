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

#define TRACE_POINT cout << "Function : " << __FUNCTION__ << ", Line : " << __LINE__ << "\n"

namespace gva {

#include <stdio.h>
void DumpHex(const void* data, size_t size);

}  // namespace gva

#endif  // COMMON_DEBUG_H_
