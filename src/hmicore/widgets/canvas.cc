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
/// \file canvas.cc
///

#include "hmicore/widgets/canvas.h"

namespace gva {

WidgetCanvas::WidgetCanvas(const RendererGva& renderer) : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeCanvas) {
  SetVisible(false);
}

void WidgetCanvas::Draw() {
  // Draw the background canvas first
  if (blackout_) {
    // Set background black
    GetRenderer()->SetColourForeground(HMI_BLACK);
    GetRenderer()->SetColourBackground(HMI_BLACK);
    GetRenderer()->DrawRectangle(0, 0, width_, height_, true);
  } else {
    switch (mode_) {
      case SurfaceType::kSurfaceCairo:
        GetRenderer()->TextureRGB(0, 0, surface_);
        break;
      case SurfaceType::kSurfaceFile:
        GetRenderer()->TextureRGB(0, 0, buffer_);
        GetRenderer()->TextureRGB(0, 0, buffer_, filename_);
        break;
      default:
        // Set background green
        GetRenderer()->SetColourForeground(gva::ConfigData::GetInstance()->GetThemeBackground());
        GetRenderer()->SetColourBackground(gva::ConfigData::GetInstance()->GetThemeBackground());
        GetRenderer()->DrawRectangle(0, 0, width_, height_, true);
        break;
    }
  }
}

void WidgetCanvas::SetMode(const SurfaceType mode) { mode_ = mode; }

void WidgetCanvas::SetBlackout() { blackout_ = true; }

bool WidgetCanvas::GetBlackout() const { return blackout_; }

SurfaceType WidgetCanvas::GetMode() const { return mode_; }

void WidgetCanvas::SetFilename(const std::string_view filename) {
  mode_ = SurfaceType::kSurfaceFile;
  filename_ = std::string(filename);
}

void WidgetCanvas::SetSurface(cairo_surface_t* surface) {
  mode_ = SurfaceType::kSurfaceCairo;
  surface_ = surface;
}

void WidgetCanvas::Reset() { mode_ = SurfaceType::kSurfaceNone; }

}  // namespace gva
