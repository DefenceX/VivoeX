//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer.cc
///

#include "hmicore/renderer.h"

#include "hmicore/gva.h"

namespace gva {

hmiScreenSize& hmiScreenSize = hmiScreenSize::getInstance();
std::tuple<int, int> size = hmiScreenSize.getMinimumSize();    

uint32_t Renderer::height_ = std::get<0>(size);
uint32_t Renderer::width_ = std::get<1>(size);

Renderer::Renderer(uint32_t width, uint32_t height) {
  width_ = width;
  height_ = height;
}

RgbUnpackedType Renderer::UnpackRgb(uint64_t rgb) const {
  RgbUnpackedType colour;
  colour.r = (rgb & 0x0000000000ff0000) >> 16;
  colour.g = (rgb & 0x000000000000ff00) >> 8;
  colour.b = (rgb & 0x00000000000000ff);
  return colour;
}

uint32_t Renderer::PackRgb(ColourType colour) {
  auto red = (uint32_t)colour.red;
  auto green = (uint32_t)colour.green;
  auto blue = (uint32_t)colour.blue;
  uint32_t packed = (red << 16) | (green << 8) | blue;
  return packed;
}

uint32_t Renderer::PackRgb(uint8_t r, uint8_t g, uint8_t b) {
  auto red = (uint32_t)r;
  auto green = (uint32_t)g;
  auto blue = (uint32_t)b;
  uint32_t packed = (red << 16) | (green << 8) | blue;
  return packed;
}

}  // namespace gva