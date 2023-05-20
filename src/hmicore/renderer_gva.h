//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer_gva.h
///

#ifndef HMICORE_RENDERER_GVA_H_
#define HMICORE_RENDERER_GVA_H_

#include <memory>
#include <string>
#include <vector>

#include "hmicore/config_reader.h"
#include "hmicore/gva.h"
#include "hmicore/renderer_cairo.h"
#include "hmicore/touch_gva.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

/// Class definition of the GVA renderer
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
  /// \brief Draw all the labels on the screen
  ///
  /// \param x position of the labels, useful for labels on left and right sides of the screen
  /// \param labels Array of labels to be rendered
  ///
  void DrawFunctionLabels(uint32_t x, const std::array<FunctionKeys::Labels, 6> &labels);

  ///
  ///  \brief Draw the labels on the top of the screen
  ///
  ///  \param y The y pixel position
  ///  \param labels The labels
  ///
  void DrawTopLabels(uint32_t y, const std::array<FunctionSelect::Labels, 8> &labels);

  ///
  /// \brief Draw the control labels on the bottom of the screen
  ///
  /// \param y The y pixel position
  /// \param labels The labels
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
  void DrawButton(const std::string &keytext, uint32_t fontSize, uint32_t x, uint32_t y, uint32_t size);

  ///
  /// \brief Draw keyboard buttons
  ///
  /// \param key_text The button text
  /// \param font_size The font size to be used
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param height Height of button in pixels
  /// \param width Width of button in pixels
  /// \param align The text alignment
  ///
  void DrawButton(const std::string &key_text, uint32_t font_size, uint32_t x, uint32_t y, uint32_t height,
                  uint32_t width, widget::CellAlignType align);

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

/// Class definition of the Widget Base
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

  /// The GVA renderer
  RendererGva &renderer_;
  /// The X pixel position
  uint32_t x_;
  /// The Y pixel position
  uint32_t y_;
};

/// Class definition of the Widget Function Select
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

#endif  // HMICORE_RENDERER_GVA_H_
