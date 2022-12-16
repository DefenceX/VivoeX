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
/// \brief Manage the touch screen events
///
/// \file touch_gva.h
///

#include "src/touch_gva.h"

namespace gva {

GvaStatusTypes TouchGva::Add(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) {
  hotspots_.push_back(Hotspot(groupId, x, y));
  return GvaStatusTypes::kGvaSuccess;
}

GvaStatusTypes TouchGva::Add(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width,
                             uint32_t height) {
  hotspots_.push_back(Hotspot(groupId, binding, x, y, width, height));
  return GvaStatusTypes::kGvaSuccess;
}

GvaStatusTypes TouchGva::AddAbsolute(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y,
                                     uint32_t xx, uint32_t yy) {
  hotspots_.push_back(Hotspot(groupId, binding, x, y, xx - x, yy - y));
  return GvaStatusTypes::kGvaSuccess;
}

void TouchGva::SetResolution(uint32_t x, uint32_t y) {
  x_ = x;
  y_ = y;
}

void TouchGva::Reset() { hotspots_.clear(); }

bool TouchGva::Check(GvaFunctionGroupEnum groupId, uint32_t *binding, uint32_t x, uint32_t y) const {
  // Adjust for resized windows
  x = x / static_cast<float>(Renderer::GetWidth() / static_cast<float>(kMinimumWidth));
  y = y / static_cast<float>(Renderer::GetHeight() / static_cast<float>(kMinimumHeight));

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
