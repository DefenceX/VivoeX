//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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
