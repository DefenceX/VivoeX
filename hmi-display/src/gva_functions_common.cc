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
/// \file gva_functions_common.cc
///
#include <math.h>
#include <stdint.h>

namespace gva {

int32_t PlotCircleX(uint16_t x, double_t radius, double_t degree) {
  return (int32_t)(x + radius * sin(((M_PI * 2) / 360) * degree));
}

int32_t PlotCircleY(uint16_t y, double_t radius, double_t degree) {
  return (int32_t)(y - radius * cos(((M_PI * 2) / 360) * degree));
}

double_t DegreesToRadians(uint16_t angle_degrees) { return (angle_degrees * M_PI / 180.0); }

uint16_t RadiansToDegrees(double_t angle_radians) { return (uint16_t)(angle_radians * 180.0 / M_PI); }

float ToDegrees(float lon_lat) {
  float d = lon_lat / 100;
  float m = lon_lat - d * 100;
  return d + m / (float)60;
}

uint16_t DegreesSubtract(uint16_t degrees, uint16_t minus) {
  int16_t new_value = degrees - minus;
  if (new_value < 0) new_value += 360;
  return new_value;
}

uint16_t DegreesAdd(uint16_t degrees, uint16_t add) {
  int16_t new_value = degrees + add;
  if (new_value > 360) new_value -= 360;
  return new_value;
}

}  // namespace gva
