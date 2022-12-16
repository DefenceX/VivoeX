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
///
/// \file bottom_labels.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_BOTTOM_LABELS_H_
#define HMI_DISPLAY_SRC_WIDGETS_BOTTOM_LABELS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "src/events_gva.h"
#include "src/renderer_cairo_types.h"
#include "src/widgets/widget.h"

namespace gva {

class WidgetBottomLabels : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object, this widget is interactive and requires the touch events
  ///
  /// \param renderer
  ///
  explicit WidgetBottomLabels(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetBottomLabels() final = default;

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///, TouchType& touch
  void Draw() final;

  ///
  /// \brief Set the Labels object
  ///
  /// \param labels
  ///
  void SetLabels(std::array<CommonTaskKeys::Labels, 8>* labels);

 private:
  void DrawControlLabels();
  ConfigData* config_ = nullptr;
  std::array<CommonTaskKeys::Labels, 8>* labels_;
  TouchGva* touch_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_BOTTOM_LABELS_H_
