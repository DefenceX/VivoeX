//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file widget.h
///

#ifndef HMICORE_WIDGETS_WIDGET_H_
#define HMICORE_WIDGETS_WIDGET_H_

#include <string>

#include "hmicore/renderer_gva.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

class ScreenGva;
class HandleType;

class WidgetX {
 public:
  virtual ~WidgetX() = default;

  ///
  /// \brief Construct a new Widget X object
  ///
  /// \param renderer The underlying renderer, should be cairo
  /// \param widget_type The type of widget
  ///
  explicit WidgetX(const RendererGva& renderer, widget::WidgetEnum widget_type);

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string the widget name
  ///
  virtual std::string GetWidgetName() const = 0;

  ///
  /// \brief Get the Widget Type attribute
  ///
  /// \return std::string
  ///
  virtual widget::WidgetEnum GetWidgetType() const;

  ///
  /// \brief Set the Visible object
  ///
  /// \param visible
  ///
  ///
  /// \param visible
  ///
  void SetVisible(bool visible);

  ///
  /// \brief Get the Visible object
  ///
  /// \return true
  /// \return false
  ///
  bool GetVisible() const;

  ///
  /// \brief Set the X dimension
  ///
  /// \param x
  ///
  virtual void SetX(uint32_t x);

  ///
  /// \brief Get the Y dimension
  ///
  /// \return uint32_t
  ///
  uint32_t GetX() const;

  ///
  /// \brief Set the Y dimension
  ///
  /// \param y
  ///
  virtual void SetY(uint32_t y);

  ///
  /// \brief Get the Y dimension
  ///
  /// \return uint32_t
  ///
  uint32_t GetY() const;

  ///
  /// \brief Set the Width
  ///
  /// \param width
  ///
  void SetWidth(uint32_t width);

  ///
  /// \brief Get the Width
  ///
  /// \return uint32_t
  ///
  uint32_t GetWidth() const;

  ///
  /// \brief Set the Height
  ///
  /// \param width
  ///
  void SetHeight(uint32_t width);

  ///
  /// \brief Get the Height
  ///
  /// \return uint32_t
  ///
  uint32_t GetHeight() const;

  ///
  /// \brief Draw the widget
  ///
  ///
  virtual void Draw() = 0;

  ///
  /// \brief Get the Type object
  ///
  /// \return WidgetEnum
  ///
  widget::WidgetEnum GetType() const;

  ///
  /// \brief Get the Renderer object
  ///
  /// \return RendererGva&
  ///
  RendererGva* GetRenderer() const;

  ///
  /// \brief Set the State Text of an on screen label
  ///
  /// \param state
  ///
  void SetStateText(LabelStates state);

  ///
  /// \brief Set the State Label object
  ///
  /// \param state
  ///
  void SetStateLabel(const LabelStates state);

  ///
  /// \brief Get the State Text Colour object
  ///
  /// \param state
  /// \return uint32_t
  ///
  uint32_t GetStateTextColour(LabelStates state) const;

  /// The widget x location in pixels
  uint32_t x_ = 0;
  /// The widget y location in pixels
  uint32_t y_ = 0;
  /// The widget width in pixels
  uint32_t width_ = 0;
  /// The widget height in pixels
  uint32_t height_ = 0;

 private:
  /// The GVA renderer
  const RendererGva& renderer_;
  /// The widget type enum
  widget::WidgetEnum widget_type_;
  /// The widget visible state
  bool visible_ = false;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_WIDGET_H_
