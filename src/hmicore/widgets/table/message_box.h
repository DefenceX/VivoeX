//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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
