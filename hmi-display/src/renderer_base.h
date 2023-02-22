//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
///
/// \brief The base of and renderer class
///
/// \file renderer_base.h
///

#ifndef HMI_DISPLAY_SRC_RENDERER_BASE_H_
#define HMI_DISPLAY_SRC_RENDERER_BASE_H_

#include <stdint.h>

namespace gva {

class RenderBase {
 public:
  ///
  /// \brief Construct a new Render Base object
  ///
  ///
  RenderBase() = default;

  ///
  /// \brief Construct a new Render Base object
  ///
  /// \param x X pixel position
  /// \param y Y pixel position
  ///
  RenderBase(uint32_t x, uint32_t y) : m_x(x), m_y(y) {}

  ///
  /// \brief Construct a new Render Base object
  ///
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param width the width in pixels
  ///
  RenderBase(uint32_t x, uint32_t y, uint32_t width) : m_x(x), m_y(y), m_width(width) {}

  ///
  /// \brief Construct a new Render Base object
  ///
  /// \param x X pixel position
  /// \param y Y pixel position
  /// \param width the width in pixels
  /// \param height the height in pixels
  ///
  RenderBase(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
      : m_x(x), m_y(y), m_width(width), m_height(height) {}

  ///
  /// \brief Get the X attribute
  ///
  /// \return uint32_t The X pixel position
  ///
  uint32_t GetX() const { return m_x; }

  ///
  /// \brief Get the Y attribute
  ///
  /// \return uint32_t The Y pixel position
  ///
  uint32_t GetY() const { return m_y; }

  ///
  /// \brief Get the Width attribute
  ///
  /// \return uint32_t The width in pixels
  ///
  uint32_t GetWidth() const { return m_width; }

  ///
  /// \brief Get the Height attribute
  ///
  /// \return uint32_t The height in pixels
  ///
  uint32_t GetHeight() const { return m_height; }

 private:
  uint32_t m_x = 0;
  uint32_t m_y = 0;
  uint32_t m_width = 0;
  uint32_t m_height = 0;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_RENDERER_BASE_H_
