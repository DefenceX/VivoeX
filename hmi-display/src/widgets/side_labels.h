//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
/// \file side_labels.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_SIDE_LABELS_H_
#define HMI_DISPLAY_SRC_WIDGETS_SIDE_LABELS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "src/events_gva.h"
#include "src/renderer_cairo_types.h"
#include "src/widgets/widget.h"

namespace gva {

class WidgetSideLabels : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object, this widget is interactive and requires the touch events
  ///
  /// \param renderer
  ///
  explicit WidgetSideLabels(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetSideLabels() final = default;

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
  void SetLabels(std::array<FunctionKeys::Labels, 6>* labels);

 private:
  ///
  /// \brief Draw the actual function labels (x6)
  ///
  /// \param x
  /// \param labels
  ///
  void DrawFunctionLabels();

  ///
  /// \brief Draw single label
  ///
  /// \param x
  /// \param y
  /// \param width
  /// \param height
  /// \param text
  /// \param text_colour
  ///
  void Draw(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const std::string& text, uint32_t text_colour,
            bool toggle_on);

  ///
  /// \brief Draw a toggle if required
  ///
  /// \param label1
  /// \param label2
  ///
  void Toggle(const std::string& label1, const std::string& label2) const;

  ///
  /// \brief Render the requested icon
  ///
  /// \param text the textual representation of the icon being requested
  ///
  void RenderIcon(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height) const;

  std::array<FunctionKeys::Labels, 6>* labels_;
  TouchGva* touch_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_SIDE_LABELS_H_
