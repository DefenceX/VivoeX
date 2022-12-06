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
/// \brief This is the drivers dials, these are RPM and speed primarilly
///
/// \file driver.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_DRIVER_H_
#define HMI_DISPLAY_SRC_WIDGETS_DRIVER_H_

#include <cstdint>

#include "src/renderer_cairo_types.h"
#include "src/widgets/widget.h"

namespace gva {

class WidgetDriverDial : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Plan Position Indicator object
  ///
  /// \param renderer
  ///
  explicit WidgetDriverDial(const RendererGva& renderer);

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///
  void Draw() final;

  ///
  /// \brief Set the ValueS
  ///
  /// \param bearing
  ///
  void SetValue(int16_t value) { value_ = value; }

  ///
  /// \brief Get the Value
  ///
  /// \return int16_t
  ///
  int16_t GetValue() const { return value_; }

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(widget::DialType mode) { mode_ = mode; }

 private:
  const double scale_ = 0.5;
  int16_t value_ = 0;
  bool indicator_left_ = false;
  bool indicator_right_ = false;
  widget::DialType mode_ = widget::DialType::kDialSpeedKph;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_DRIVER_H_
