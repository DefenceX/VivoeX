//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file canvas.h
///

#ifndef HMICORE_WIDGETS_CANVAS_CANVAS_H_
#define HMICORE_WIDGETS_CANVAS_CANVAS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"
#include "hmicore/hmi_gva_helpers.h"

namespace gva {

/// Class defining the mode widget
class WidgetCanvas : public WidgetX {
 public:
  ///
  /// \brief Construct a new Widget Keyboard object
  ///
  /// \param renderer
  ///
  explicit WidgetCanvas(const RendererGva& renderer);

  ///
  /// \brief Destroy the Widget mode object
  ///
  ///
  ~WidgetCanvas() override = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetCanvas"; };

  ///
  /// \brief Draw the current widget, not final as used by video sources
  ///
  ///
  void Draw() override;

  ///
  /// \brief Draw the canvas
  ///
  ///
  void DrawCanvas();

  ///
  /// \brief Set the Mode object
  ///
  /// \param mode
  ///
  void SetMode(const SurfaceType mode);

  ///
  ///  \brief Get the Mode object
  ///
  ///  \return std::string
  ///
  SurfaceType GetMode() const;

  ///
  /// \brief Set Blackout mode
  ///
  ///
  void SetBlackout();

  ///
  /// \brief Get the Blackout attribute
  ///
  /// \return true
  /// \return false
  ///
  bool GetBlackout() const;

  ///
  /// \brief Set the Filename attribute, canvas will show the image. Image will be rescaled to fit current resolution
  ///
  /// \param filename
  ///
  void SetFilename(const std::string_view filename);

  ///
  /// \brief Set the canvas to surface
  ///
  /// \param surface
  ///
  void SetSurface(cairo_surface_t* surface);

  ///
  /// \brief Set the Surface to the default background
  ///
  ///
  void SetSurfaceDefault();

  ///
  /// \brief Set to default background
  ///
  ///
  void Reset();

 private:
  SurfaceType mode_ = SurfaceType::kSurfaceNone;
  std::string filename_ = "";
  std::string message_ = "";
  cairo_surface_t* surface_ = nullptr;
  unsigned char* buffer_ = nullptr;
};

}  // namespace gva

#endif  // HMICORE_WIDGETS_CANVAS_CANVAS_H_
