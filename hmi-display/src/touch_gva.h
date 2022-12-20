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

#ifndef HMI_DISPLAY_SRC_TOUCH_GVA_H_
#define HMI_DISPLAY_SRC_TOUCH_GVA_H_

#include <vector>

#include "src/renderer_base.h"
#include "src/renderer_gva.h"

namespace gva {

class Hotspot : public RenderBase {
 public:
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) : RenderBase(x, y), group_id_(groupId), binding_(0) {}
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
      : RenderBase(x, y, width, height), group_id_(groupId), binding_(binding) {}
  GvaFunctionGroupEnum GetGroupId() const { return group_id_; }
  uint32_t GetBinding() const { return binding_; }

 private:
  GvaFunctionGroupEnum group_id_;  // Group hotspots together
  uint32_t binding_;               // Bind a value or a key to this Hotspot
};

class TouchGva {
 public:
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y);
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height);
  GvaStatusTypes AddAbsolute(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t xx,
                             uint32_t yy);
  void SetResolution(uint32_t x, uint32_t y);
  void Reset();
  bool Check(GvaFunctionGroupEnum groupId, uint32_t *binding, uint32_t x, uint32_t y) const;

 private:
  uint32_t x_;
  uint32_t y_;
  std::vector<Hotspot> hotspots_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_TOUCH_GVA_H_
