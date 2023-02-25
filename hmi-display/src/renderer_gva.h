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
/// \file renderer_gva.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_GVA_H_
#define HMI_DISPLAY_SRC_RENDERER_GVA_H_

#include <memory>
#include <string>
#include <vector>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/renderer_cairo.h"
#include "src/touch_gva.h"
#include "src/widgets/widget_types.h"

namespace gva {

class GvaCell {
 public:
  std::string text;
  widget::CellAlignType align;
  widget::GvaColourType foreground;
  widget::GvaColourType background;
  widget::GvaColourType textcolour;
  widget::WeightType weight;
};

class RendererGva : public RendererCairo {
 public:
  ///
  /// \brief Construct a new Renderer Gva object
  ///
  /// \param width
  /// \param height
  ///
  RendererGva(uint32_t width, uint32_t height);

  ///
  /// \brief Destroy the Renderer Gva object
  ///
  ///
  ~RendererGva() override = default;

  ///
  /// \brief Draw all the labels on the screen
  ///
  /// \param text The text to go in the label
  /// \param fontSize The font size
  /// \param x X Position on the screen
  /// \param y Y Position on the screen
  ///
  void DrawLabels(char *text, uint32_t fontSize, uint32_t x, uint32_t y);

  ///
  /// \param x position of the labels, useful for labels on left and right sides of the screen
  /// \param state State of the label
  /// \param toggle Toggle
  /// \param toggleOn Toggle on
  /// \param labels Array of labels to be rendered
  ///
  void DrawFunctionLabels(uint32_t x, const std::array<FunctionKeys::Labels, 6> &labels);

  /// Init
  ///  \brief Draw the labels on the top of the screen
  ///
  ///  \param y The y pixel position
  ///  \param state State of the label
  ///
  void DrawTopLabels(uint32_t y, const std::array<FunctionSelect::Labels, 8> &labels);

  ///
  /// \brief Draw the control labels on the bottom of the screen
  ///
  /// \param y The y pixel position
  /// \param state State of the label
  ///
  void DrawControlLabels(const uint32_t y, const std::array<CommonTaskKeys::Labels, 8> &labels);

  ///
  /// \brief Draw an icon
  ///
  /// \param icon The type of icon to be rendered
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param width Width of the icon
  /// \param height Height of the icon
  ///
  void DrawIcon(widget::IconType icon, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

  ///
  /// \brief Draw keyboard buttons
  ///
  /// \param keytext The button text
  /// \param fontSize The font size to be used
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param size Size in pixels
  ///
  void DrawButton(const std::string keytext, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t size);

  ///
  /// \brief Draw keyboard buttons
  ///
  /// \param keytext The button text
  /// \param fontSize The font size to be used
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param size Size in pixels
  /// \param height Height of button in pixels
  /// \param width Width of button in pixels
  /// \param align Alignment
  ///
  void DrawButton(const std::string keytext, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t height, uint32_t width,
                  widget::CellAlignType align);

  ///
  /// \brief Get the Touch object
  ///
  /// \return TouchGva*
  ///
  TouchGva *GetTouch() { return &touch_; }

 private:
  TouchGva touch_;

  ///
  /// \brief Set the State Label attribute
  ///
  /// \param state
  /// \param config
  ///
  void SetStateLabel(LabelStates state, ConfigData *config);

  ///
  /// \brief Set the State Text attribute
  ///
  /// \param state
  /// \param config
  ///
  void SetStateText(LabelStates state, ConfigData *config);
  ConfigData *config_ = nullptr;
};

class WidgetBase {
 public:
  ///
  /// \brief Construct a new Widget Base object
  ///
  /// \param renderer
  ///
  explicit WidgetBase(RendererGva &renderer) : renderer_(renderer) {}

  ///
  /// \brief
  ///
  /// \param x
  /// \param y
  /// \param width
  /// \param height
  /// \param text
  /// \param text_colour
  ///
  void Draw(uint32_t x, uint32_t y, uint32_t width, uint32_t height, std::string text, uint32_t text_colour);

  ///
  /// \brief Get the X pixel attribute
  ///
  /// \return uint32_t
  ///
  uint32_t GetX() const { return x_; }

  ///
  /// \brief Get the Y pixel attribute
  ///
  /// \return uint32_t
  ///
  uint32_t GetY() const { return y_; }
  RendererGva &renderer_;
  uint32_t x_;
  uint32_t y_;
};

class WidgetFunctionKeyToggle : public WidgetBase {
  using WidgetBase::WidgetBase;

 public:
  ///
  /// \brief Set the toggle states
  ///
  /// \param label1 The first toggle state text
  /// \param label2 The second toggle state text
  ///
  void Toggle(const std::string &label1, const std::string &label2);
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_GVA_H_
