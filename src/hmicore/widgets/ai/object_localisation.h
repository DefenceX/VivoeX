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
