//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file side_labels.h
///
#ifndef HMICORE_WIDGETS_SIDE_LABELS_H_
#define HMICORE_WIDGETS_SIDE_LABELS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/events_gva.h"
#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

class WidgetSideLabels : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object, this widget is interactive and requires the touch events
  ///
  /// \param renderer The underlying renderer, should be cairo
  /// \param touch the touch object
  ///
  explicit WidgetSideLabels(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetSideLabels() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetSideLabels"; };

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

#endif  // HMICORE_WIDGETS_SIDE_LABELS_H_
