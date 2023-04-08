//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
/// \file gva_functions_common.h
///

#ifndef HMI_DISPLAY_SRC_GVA_FUNCTIONS_COMMON_H_
#define HMI_DISPLAY_SRC_GVA_FUNCTIONS_COMMON_H_

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

#endif  // HMI_DISPLAY_SRC_GVA_FUNCTIONS_COMMON_H_