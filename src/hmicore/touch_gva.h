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
#include "hmicore/hmi_gva_helpers.h"
#include "hmicore/renderer_base.h"

namespace gva {

/// Class defining the render base
class Hotspot : public RenderBase {
 public:
  ///
  /// \brief Construct a new Hotspot object
  ///
  /// \param groupId The group ID for this hotspot
  /// \param x The pixel position of the hotspot on the X axis
  /// \param y The pixel position of the hotspot on the Y axis
  ///
  Hotspot(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y) : RenderBase(x, y), group_id_(groupId), binding_(0) {}

  ///
  /// \brief Construct a new Hotspot object
  ///
  /// \param groupId The group ID for this hotspot
  /// \param binding The binding ID for this hotspot
  /// \param x The pixel position of the hotspot on the X axis
  /// \param y The pixel position of the hotspot on the Y axis
  /// \param width The width of the hotspot
  /// \param height The height of the hotspot
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
  /// The group ID for this hotspot, group hotspots together
  GvaFunctionGroupEnum group_id_;
  // Bind a value or a key to this Hotspot
  uint32_t binding_;
};

/// Class defining the touch screen events
class TouchGva {
 public:
  ///
  /// \brief Construct a new Touch Gva object
  ///
  /// \param groupId The group ID for this hotspot
  /// \param x The pixel position of the hotspot on the X axis
  /// \param y The pixel position of the hotspot on the Y axis
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t x, uint32_t y);

  ///
  /// \brief Construct a new Touch Gva object
  ///
  /// \param groupId The group ID for this hotspot
  /// \param binding The binding ID for this hotspot
  /// \param x The pixel position of the hotspot on the X axis
  /// \param y The pixel position of the hotspot on the Y axis
  /// \param width The width of the hotspot
  /// \param height The height of the hotspot
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes Add(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t width,
                     uint32_t height);

  ///
  /// \brief Construct a new Touch Gva object
  ///
  /// \param groupId The group ID for this hotspot
  /// \param binding The binding ID for this hotspot
  /// \param x The pixel position of the hotspot on the X axis, top right
  /// \param y The pixel position of the hotspot on the Y axis, top right
  /// \param xx The pixel position of the hotspot on the X axis, bottom left
  /// \param yy The pixel position of the hotspot on the Y axis, bottom left
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes AddAbsolute(GvaFunctionGroupEnum groupId, uint32_t binding, uint32_t x, uint32_t y, uint32_t xx,
                             uint32_t yy);

  ///
  /// \brief Set the Resolution attribute
  ///
  /// \param x The screen resolution on the X axis
  /// \param y The screen resolution on the Y axis
  ///
  void SetResolution(uint32_t x, uint32_t y);

  ///
  /// \brief Reset all the hotspots
  ///
  ///
  void Reset();

  ///
  /// \brief Check if a touch event is within a hotspot
  ///
  /// \param groupId The group ID for this hotspot
  /// \param binding The binding ID for this hotspot
  /// \param x The pixel position of the touch event on the x axis
  /// \param y The pixel position of the touch event on the y axis
  /// \return true
  /// \return false
  ///
  bool Check(GvaFunctionGroupEnum groupId, uint32_t *binding, uint32_t x, uint32_t y) const;

 private:
  /// The screen resolution on the X axis
  uint32_t x_;
  /// The screen resolution on the Y axis
  uint32_t y_;
  /// Th list of hotspots
  std::vector<Hotspot> hotspots_;
};

}  // namespace gva

#endif  // HMICORE_TOUCH_GVA_H_
