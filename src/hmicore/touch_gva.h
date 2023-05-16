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
  ///
  /// \brief Construct a new Hotspot object
  ///
  /// \param groupId
  /// \param x
  /// \param y
  ///
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) : RenderBase(x, y), group_id_(groupId), binding_(0) {}

  ///
  /// \brief Construct a new Hotspot object
  ///
  /// \param groupId
  /// \param binding
  /// \param x
  /// \param y
  /// \param width
  /// \param height
  ///
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
      : RenderBase(x, y, width, height), group_id_(groupId), binding_(binding) {}

  ///
  /// \brief Get the Group Id attribute
  ///
  /// \return GvaFunctionGroupEnum
  ///
  GvaFunctionGroupEnum GetGroupId() const { return group_id_; }

  ///
  /// \brief Get the Binding attribute
  ///
  /// \return uint32_t
  ///
  uint32_t GetBinding() const { return binding_; }

 private:
  /// Group hotspots together
  GvaFunctionGroupEnum group_id_;
  /// Bind a value or a key to this Hotspot
  uint32_t binding_;
};

class TouchGva {
 public:
  ///
  /// \brief Construct a new Touch Gva object
  ///
  /// \param groupId
  /// \param x
  /// \param y
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y);

  ///
  /// \brief Construct a new Touch Gva object
  ///
  /// \param groupId
  /// \param binding
  /// \param x
  /// \param y
  /// \param width
  /// \param height
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height);

  ///
  /// \brief Add a new absolute touch hotspot
  ///
  /// \param groupId
  /// \param binding
  /// \param x
  /// \param y
  /// \param xx
  /// \param yy
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes AddAbsolute(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t xx,
                             uint32_t yy);

  ///
  /// \brief Set the Resolution attribute
  ///
  /// \param x
  /// \param y
  ///
  void SetResolution(uint32_t x, uint32_t y);

  ///
  /// \brief Reset the touch screen
  ///
  ///
  void Reset();

  ///
  /// \brief Check if a touch event is within a hotspot
  ///
  /// \param groupId
  /// \param binding
  /// \param x
  /// \param y
  /// \return true
  /// \return false
  ///
  bool Check(GvaFunctionGroupEnum groupId, uint32_t *binding, uint32_t x, uint32_t y) const;

 private:
  /// Touch screen resolution X
  uint32_t x_;
  /// Touch screen resolution Y
  uint32_t y_;
  /// List of hotspots
  std::vector<Hotspot> hotspots_;
};

}  // namespace gva

#endif  // HMICORE_TOUCH_GVA_H_
