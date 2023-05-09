//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \brief The base of and renderer class
///
/// \file renderer_base.h
///

#ifndef HMICORE_RENDERER_BASE_H_
#define HMICORE_RENDERER_BASE_H_

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

#endif  // HMICORE_RENDERER_BASE_H_
