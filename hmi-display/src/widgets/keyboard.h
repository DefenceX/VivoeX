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
/// \file keyboard.h
///
#ifndef HMI_DISPLAY_SRC_WIDGETS_KEYBOARD_H_
#define HMI_DISPLAY_SRC_WIDGETS_KEYBOARD_H_

#include <cstdint>
#include <vector>

#include "src/renderer_cairo_types.h"
#include "src/widgets/widget.h"
#include "src/widgets/widget_types.h"

namespace gva {

class WidgetKeyboard : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
  ///
  explicit WidgetKeyboard(const RendererGva& renderer);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetKeyboard() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetKeyboard"; };

  ///
  /// \brief Draw the current widget
  ///
  ///
  void Draw() final;

  ///
  /// \brief Draw the on screen keyboard
  ///
  /// \param mode
  ///
  void DrawKeyboard(const widget::KeyboardModeType mode);

  ///
  /// \brief Set the Mode object
  ///
  /// void SetMode(KeyboardModeType mode) { mode_ = mode; }

  void SetMode(const widget::KeyboardModeType mode);

  ///
  /// \brief Get the Mode object
  ///
  /// \return KeyboardModeType
  ///
  widget::KeyboardModeType GetMode() const;

 private:
  widget::KeyboardModeType mode_ = widget::KeyboardModeType::kKeyboardUpper;
  const std::vector<std::vector<char>> upperKeys_ = {{'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
                                                     {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '-'},
                                                     {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', '-', '-'}};
  const std::vector<std::vector<char>> lowerKeys_ = {{'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
                                                     {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '-'},
                                                     {'z', 'x', 'c', 'v', 'b', 'n', 'm', ' ', '-', '-'}};
  const std::vector<std::vector<char>> numKeys_ = {{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
                                                   {'-', '_', '.', ',', ';', ':', '"', '-', '-', '-'},
                                                   {'!', '@', '#', '$', '%', '^', '&', ' ', '-', '-'}};
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_KEYBOARD_H_
