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
/// \file canvas.h
///

#ifndef HMICORE_CANVAS_H_
#define HMICORE_CANVAS_H_

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/widget.h"

namespace gva {

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
  ~WidgetCanvas() final = default;

  ///
  /// \brief Get the Widget Name attribute
  ///
  /// \return std::string
  ///
  std::string GetWidgetName() const final { return "WidgetCanvas"; };

  ///
  /// \brief Draw the current widget
  ///
  ///
  void Draw() final;

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
  bool blackout_ = true;
  std::string filename_ = "";
  std::string message_ = "";
  cairo_surface_t* surface_ = nullptr;
  unsigned char* buffer_ = nullptr;
};

}  // namespace gva

#endif  // HMICORE_CANVAS_H_