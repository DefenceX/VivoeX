//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file onscreen_bezel_btns.h
///
#ifndef HMICORE_WIDGETS_ONSCREEN_BEZEL_BTNS_H_
#define HMICORE_WIDGETS_ONSCREEN_BEZEL_BTNS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/events_gva.h"
#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

/// Class defining the top labels
class WidgetOnscreenBezelBtns : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object, this widget is interactive and requires the touch events
  ///
  /// \param renderer The underlying renderer, should be cairo
  /// \param touch the touch object
  ///
  explicit WidgetOnscreenBezelBtns(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetOnscreenBezelBtns() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetOnscreenBezelBtns"; }

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
  void SetLabels(std::array<FunctionKeys::Labels, 8>* toplabels, std::array<FunctionKeys::Labels, 8>* bottomlabels, std::array<FunctionKeys::Labels, 8>* leftlabels, std::array<FunctionKeys::Labels, 8>* rightlabels);

  ///
  /// \brief Render the requested icon
  ///
  /// \param text the textual representation of the icon being requested
  ///
  void RenderIcon(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height) const;

 private:
  ///
  /// \brief Draw the labels along the top of the screen with the states as set using SetLabels()
  ///
  /// \param y
  /// \param labels
  ///
  void DrawLabels(uint32_t topY, uint32_t bottomY, uint32_t leftX, uint32_t rightX,
                                const std::array<FunctionKeys::Labels, 8>& topLabels,
                                const std::array<FunctionKeys::Labels, 8>& bottomLabels,
                                const std::array<FunctionKeys::Labels, 8>& leftLabels,
                                const std::array<FunctionKeys::Labels, 8>& rightLabels);
  
  void DrawLabelsRow(uint32_t y, const std::array<FunctionKeys::Labels, 8>& labels);
  void DrawLabelsColumn(uint32_t x, const std::array<FunctionKeys::Labels, 8>& labels);

  void DrawBezelButton(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const std::string& text, uint32_t text_colour,
            bool toggle_on);

  std::array<FunctionKeys::Labels, 8>* toplabels_;
  std::array<FunctionKeys::Labels, 8>* bottomlabels_;
  std::array<FunctionKeys::Labels, 8>* leftlabels_;
  std::array<FunctionKeys::Labels, 8>* rightlabels_;

  TouchGva* touch_;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_ONSCREEN_BEZEL_BTNS_H_
