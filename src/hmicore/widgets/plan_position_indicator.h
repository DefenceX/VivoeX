//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// different styles.
///
/// \file plan_position_indicator.h
///
#ifndef HMICORE_WIDGETS_PLAN_POSITION_INDICATOR_H_
#define HMICORE_WIDGETS_PLAN_POSITION_INDICATOR_H_

#include <math.h>

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

/// Class defining the Plan Position Indicator
class WidgetPlanPositionIndicator : public WidgetX {
 public:
  /// Threat structured data
  struct ThreatType {
    /// The threat bearing
    uint16_t bearing = 0;
    /// The azimuth of the threat
    uint16_t size = 0;
    // The colour of the threat
    uint32_t rgb_value = 0x00FF0000;  // green
    /// The label of the threat
    std::string label = "";
    /// Flash if true
    bool flashing = false;
    /// Dotted if true
    bool dotted = false;
  };

  ///
  /// \brief Construct a new Widget Plan Position Indicator object
  ///
  /// \param renderer
  ///
  explicit WidgetPlanPositionIndicator(const RendererGva& renderer);

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetPlanPositionIndicator"; };

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///
  void Draw() final;

  ///
  /// \brief Draw the Plan Position Indicator
  ///
  /// \param mode The PPI mode, different styles
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param degrees Compass heading
  /// \param sight_azimuth Camera heading
  /// \param weapon_azimuth Weapon heading
  ///
  void DrawPPI(widget::ModeEnum mode, int32_t x, int32_t y, int16_t degrees, int16_t sight_azimuth,
               int16_t weapon_azimuth) const;

  ///
  /// \brief Set the Bearing object
  ///
  /// \param bearing
  ///
  void SetBearing(int16_t bearing) { bearing_ = bearing; }

  ///
  /// \brief Add a threat onto the PPI
  ///
  /// \param id Unique ID of the threat
  /// \param threat The threat object
  ///
  void AddThreat(int16_t id, ThreatType threat);

  ///
  /// \brief Delete a threat by ID
  ///
  /// \param id The ID of the threat to be deletes
  ///
  void DeleteThreat(int16_t id);

  ///
  /// \brief Delete all threats
  ///
  ///
  void DeleteAllThreats();

  ///
  /// \brief Set the Bearing Sight object
  ///
  /// \param bearing_sight The bearing sight
  ///
  void SetBearingSight(int16_t bearing_sight) { bearing_sight_ = bearing_sight; }

  ///
  /// \brief Set the Weapon Azimuth attribute
  ///
  /// \param weapon_azimuth
  ///
  void SetWeaponAzimuth(int16_t weapon_azimuth) { weapon_azimuth_ = weapon_azimuth; }

  ///
  /// \brief Get the Bearing object
  ///
  /// \return uint16_t
  ///
  int16_t GetBearing() const { return bearing_; }

  ///
  /// \brief Get the Bearing Sight object
  ///
  /// \return uint16_t
  ///
  int16_t GetBearingSight() const { return bearing_sight_; }

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(widget::ModeEnum mode) { mode_ = mode; }

 private:
  ///
  /// \brief Draw a modern looking PPI
  ///
  ///
  void DrawModern(int32_t x, int32_t y, int16_t degrees, int16_t sightAzimuth, int16_t weaponAzimuth, bool sight) const;

  ///
  /// \brief Draw a GVA compliant PPI, two options to choose from
  ///
  /// \param x
  /// \param y
  /// \param degrees
  /// \param sight_azimuth
  /// \param weapon_azimuth
  ///
  void DrawClassic(widget::ModeEnum mode, int32_t x, int32_t y, int16_t degrees, int16_t sight_azimuth,
                   int16_t weapon_azimuth) const;

  ///
  /// \brief Draw a classic sight on PPI
  ///
  /// \param radius
  /// \param render_sight_azimuth
  /// \param angle
  ///
  void DrawSight(double_t radius, int16_t render_sight_azimuth, double_t angle) const;

  ///
  /// \brief Draw any threats over the PPI
  ///
  ///
  void DrawThreats() const;

  const double scale_ = 0.5;
  int16_t radius_ = 100;
  int16_t bearing_ = 0;
  int16_t bearing_sight_ = 0;
  int16_t weapon_azimuth_ = 10;
  widget::ModeEnum mode_ = widget::ModeEnum::kPpiClassicTankWithSight;
  std::unordered_map<int16_t, std::shared_ptr<ThreatType>> threats_;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_PLAN_POSITION_INDICATOR_H_
