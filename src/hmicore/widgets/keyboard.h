//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file keyboard.h
///
#ifndef HMICORE_WIDGETS_KEYBOARD_H_
#define HMICORE_WIDGETS_KEYBOARD_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"
#include "hmicore/widgets/widget_types.h"

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

#endif  // HMICORE_WIDGETS_KEYBOARD_H_
