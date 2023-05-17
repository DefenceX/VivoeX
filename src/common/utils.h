//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file utils.h
///

#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

namespace gva {

///
/// \brief Set the Brightness attribute, requires superuser privileges
///
/// \param brightness
///
void SetBrightness(double brightness);

}  // namespace gva

#endif  // COMMON_UTILS_H_
