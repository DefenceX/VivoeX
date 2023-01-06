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
/// different styles.
///
/// \file compass.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_COMPASS_H_
#define HMI_DISPLAY_SRC_WIDGETS_COMPASS_H_

#include <cstdint>

#include "src/renderer_cairo_types.h"
#include "src/widgets/widget.h"

namespace gva {

class WidgetPlanPositionIndicator : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Plan Position Indicator object
  ///
  /// \param renderer
  ///
  explicit WidgetPlanPositionIndicator(const RendererGva& renderer);

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///
  void Draw() final;

  ///
  /// \brief Draw a modern looking PPI
  ///
  ///
  void DrawModern(uint32_t x, uint32_t y, uint32_t degrees, uint32_t sightAzimuth, uint32_t weaponAzimuth,
                  bool sight) const;

  ///
  /// \brief Draw the Plan Position Indicator
  ///
  /// \param mode The PPI mode, different styles
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param degrees Compass heading
  /// \param sightAzimuth Camera heading
  ///
  void DrawPPI(widget::ModeEnum mode, uint32_t x, uint32_t y, uint32_t degrees, uint32_t sightAzimuth,
               uint32_t weaponAzimuth);

  ///
  /// \brief Set the Bearing object
  ///
  /// \param bearing
  ///
  void SetBearing(uint16_t bearing) { bearing_ = bearing; }

  ///
  /// \brief Set the Bearing Sight object
  ///
  /// \param bearing
  ///
  void SetBearingSight(uint16_t bearing_sight) { bearing_sight_ = bearing_sight; }

  ///
  /// \brief Get the Bearing object
  ///
  /// \return uint16_t
  ///
  uint16_t GetBearing() const { return bearing_; }

  ///
  /// \brief Get the Bearing Sight object
  ///
  /// \return uint16_t
  ///
  uint16_t GetBearingSight() const { return bearing_sight_; }

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(widget::ModeEnum mode) { mode_ = mode; }

 private:
   ///
  /// \brief Draw a classic sight on PPI
  ///
  /// \param radius
  /// \param render_sight_azimuth
  /// \param angle
  ///
  void DrawSight(double_t radius, uint32_t render_sight_azimuth, double_t angle);
  const double scale_ = 0.5;
  int16_t bearing_ = 0;
  int16_t bearing_sight_ = 0;
  widget::ModeEnum mode_ = widget::ModeEnum::kPpiClassicTankWithSight;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_COMPASS_H_
