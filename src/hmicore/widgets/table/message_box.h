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
/// \file messaage_box.h
///

#ifndef HMICORE_WIDGETS_TABLE_MESSAGE_BOX_H_
#define HMICORE_WIDGETS_TABLE_MESSAGE_BOX_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/table/table.h"
#include "hmicore/widgets/widget.h"

namespace gva {

class WidgetMessageBox : public WidgetTable {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
  ///
  explicit WidgetMessageBox(const RendererGva &renderer, TouchGva *touch);

  ///
  /// \brief Destroy the Widget mode object
  ///
  ///
  ~WidgetMessageBox() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetMessageBox"; };

  ///
  /// \brief Draw the current widget
  ///
  ///
  void Draw() final;

  ///
  /// \brief Set the Message text and icon
  ///
  /// \param message_text the supplementary information used in the massage box
  /// \param icon the icon to display with the message
  ///
  void SetMessage(const std::string_view message_text, widget::IconType icon);

 private:
  std::string_view message_text_;
  widget::IconType icon_ = widget::IconType::kIconNone;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_TABLE_MESSAGE_BOX_H_
