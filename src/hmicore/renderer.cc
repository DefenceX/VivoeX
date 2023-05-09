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

uint32_t Renderer::height_ = kMinimumHeight;
uint32_t Renderer::width_ = kMinimumWidth;

Renderer::Renderer(uint32_t width, uint32_t height) {
  width_ = width;
  height_ = height;
}

}  // namespace gva