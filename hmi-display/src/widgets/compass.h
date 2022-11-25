///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief This is the Generic Vehicle Architecture (GVA) Plan Position Indicator (PPI) widget. It comes in several
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
  enum class ModeEnum { kPpiClassicTankWithSight, kPpiClassicTankWithoutSight, kPpiModernTankWithSights };

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
  /// \brief Draw the Plan Position Indicator
  ///
  /// \param mode The PPI mode, different styles
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param degrees Compass heading
  /// \param sightAzimuth Camera heading
  ///
  void DrawPPI(ModeEnum mode, uint32_t x, uint32_t y, uint32_t degrees, uint32_t sightAzimuth);

  ///
  /// \brief Set the Bearing object
  ///
  /// \param bearing
  ///
  void SetBearing(int16_t bearing) { bearing_ = bearing; }

  ///
  /// \brief Set the Bearing Sight object
  ///
  /// \param bearing
  /// : WidgetX(renderer, KWidgetTypeAlarmIndicator) {}
  void SetBearingSight(int16_t bearing_sight) { bearing_sight_ = bearing_sight; }

  ///
  /// \brief Get the Bearing object
  ///
  /// \return int16_t
  ///
  int16_t GetBearing() const { return bearing_; }

  ///
  /// \brief Get the Bearing Sight object
  ///
  /// \return int16_t
  ///
  int16_t GetBearingSight() const { return bearing_sight_; }

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(ModeEnum mode) { mode_ = mode; }

  void SetX(int x) override { x_ = x * 2; }
  void SetY(int y) override { y_ = y - (100); }

 private:
  const double scale_ = 0.5;
  int16_t bearing_ = 0;
  int16_t bearing_sight_ = 0;
  ModeEnum mode_ = ModeEnum::kPpiClassicTankWithSight;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_COMPASS_H_
