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
/// \file widget.h
///

#ifndef HMI_DISPLAY_SRC_WIDGETS_WIDGET_H_
#define HMI_DISPLAY_SRC_WIDGETS_WIDGET_H_

#include "src/renderer_gva.h"
#include "src/widgets/widget_types.h"

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

  uint32_t x_ = 0;
  uint32_t y_ = 0;
  uint32_t width_ = 0;
  uint32_t height_ = 0;

 private:
  const RendererGva& renderer_;
  widget::WidgetEnum widget_type_;
  bool visible_ = true;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_WIDGETS_WIDGET_H_
