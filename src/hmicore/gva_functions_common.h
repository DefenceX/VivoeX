//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file gva_functions_common.h
///

#ifndef HMICORE_GVA_FUNCTIONS_COMMON_H_
#define HMICORE_GVA_FUNCTIONS_COMMON_H_

#include <float.h>
#include <math.h>
#include <stdint.h>

namespace gva {

///
/// \brief
///
/// \param x
/// \param radius
/// \param degree
///
int32_t PlotCircleX(uint16_t x, double_t radius, double_t degree);

///
/// \brief
///
///
int32_t PlotCircleY(uint16_t y, double_t radius, double_t degree);

///
/// \brief Convert degrees to radians
///
/// \param angle_degrees
/// \return double_t
///
double_t DegreesToRadians(uint16_t angle_degrees);

///
/// \brief Convert radians to degrees
///
/// \param angle_radians
/// \return double_t
///
uint16_t RadiansToDegrees(double_t angle_radians);

///
/// \brief Convert longitude to degrees
///
///
float ToDegrees(float lon_lat);

///
/// \brief Add a value to degrees and wrap if needed
///
/// \param degrees The value to be added to
/// \param minus The value to subtract
/// \return uint32_t The new value
///
uint16_t DegreesSubtract(uint16_t degrees, uint16_t minus);

///
/// \brief Subtract a value from degrees and wrap if needed
///
/// \param degrees The inital value
/// \param add The value to add
/// \return uint32_t The new value
///
uint16_t DegreesAdd(uint16_t degrees, uint16_t add);

}  // namespace gva

#endif  // HMICORE_GVA_FUNCTIONS_COMMON_H_
