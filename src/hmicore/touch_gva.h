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

#ifndef HMICORE_TOUCH_GVA_H_
#define HMICORE_TOUCH_GVA_H_

#include <vector>

#include "hmicore/gva.h"
#include "hmicore/renderer_base.h"

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

#endif  // HMICORE_TOUCH_GVA_H_
