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
#ifndef HMICORE_WIDGETS_AI_OBJECT_LOCALISATION_H_
#define HMICORE_WIDGETS_AI_OBJECT_LOCALISATION_H_

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "hmicore/events_gva.h"
#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

class WidgetObjectLocalisation : public WidgetX {
 public:
  struct BoxType {
    uint32_t xpos = 0;
    uint32_t ypos = 0;
    uint32_t height = 0;
    uint32_t width = 0;
    uint32_t rgb_value = 0x00FF0000;  // green
    std::string label = "";
    bool flashing = false;
    bool dotted = false;
  };

  ///
  /// \brief Construct a new Widget Keyboard object, this widget is interactive and requires the touch events
  ///
  /// \param renderer
  ///
  explicit WidgetObjectLocalisation(const RendererGva& renderer, TouchGva* touch);

  ///
  /// \brief Destroy the Widget Keyboard object
  ///
  ///
  ~WidgetObjectLocalisation() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetObjectLocalisation"; };

  ///
  /// \brief The base overloaded Draw fuctions to draw this widget type
  ///
  ///, TouchType& touch
  void Draw() final;

  ///
  /// \brief Add a box onto the object localisation overlay
  ///
  /// \param id Unique ID of the box
  /// \param box The box object
  ///
  void AddBoundingBox(int16_t id, const BoxType& box);

  ///
  /// \brief Delete a box by ID
  ///
  /// \param id The ID of the box to be deletes
  ///
  void DeleteBoundingBox(int16_t id);

  ///
  /// \brief Delete all box
  ///
  ///
  void DeleteAllBoundingBox();

 private:
  ///
  /// \brief Draw the actual bounding boxes
  ///
  /// \param x
  /// \param labels
  ///
  void DrawFunctionBoundingBoxes() const;

  ///
  /// \brief Convert an object Id to a specific key binding
  ///
  /// \param id
  /// \return GvaKeyEnum
  ///
  GvaKeyEnum IdToKey(uint16_t id) const;

  std::map<int16_t, std::shared_ptr<BoxType>> boxes_;
  TouchGva* touch_;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_AI_OBJECT_LOCALISATION_H_
