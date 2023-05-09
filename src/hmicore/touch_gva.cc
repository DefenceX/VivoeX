//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// \brief Manage the touch screen events
///
/// \file touch_gva.h
///

#include "hmicore/touch_gva.h"

#include "hmicore/renderer.h"

namespace gva {

GvaStatusTypes TouchGva::Add(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) {
  hotspots_.emplace_back(Hotspot(groupId, x, y));
  return GvaStatusTypes::kGvaSuccess;
}

GvaStatusTypes TouchGva::Add(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width,
                             uint32_t height) {
  hotspots_.emplace_back(Hotspot(groupId, binding, x, y, width, height));
  return GvaStatusTypes::kGvaSuccess;
}

GvaStatusTypes TouchGva::AddAbsolute(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y,
                                     uint32_t xx, uint32_t yy) {
  hotspots_.emplace_back(Hotspot(groupId, binding, x, y, xx - x, yy - y));
  return GvaStatusTypes::kGvaSuccess;
}

void TouchGva::SetResolution(uint32_t x, uint32_t y) {
  x_ = x;
  y_ = y;
}

void TouchGva::Reset() { hotspots_.clear(); }

bool TouchGva::Check(GvaFunctionGroupEnum groupId, uint32_t *binding, uint32_t x, uint32_t y) const {
  // Adjust for resized windows
  x = (uint32_t)((float)x / ((float)Renderer::GetWidth() / kMinimumWidth));
  y = (uint32_t)((float)y / ((float)Renderer::GetHeight() / kMinimumHeight));

  for (auto i = hotspots_.begin(); i != hotspots_.end(); ++i) {
    if ((x > i->GetX()) && (x < (i->GetX() + i->GetWidth())) && (y > i->GetY()) && (y < (i->GetY() + i->GetHeight())) &&
        (i->GetGroupId() == groupId)) {
      *binding = i->GetBinding();
      return true;
    }
  }
  return false;
}

}  // namespace gva
