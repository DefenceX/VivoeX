//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file canvas.cc
///

#include "hmicore/widgets/canvas/canvas.h"

#include <glog/logging.h>
namespace gva {

WidgetCanvas::WidgetCanvas(const RendererGva& renderer) : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeCanvas) {
  width_ = kMinimumWidth;
  height_ = kMinimumHeight;
}

void WidgetCanvas::Draw() {
  if (GetVisible()) {
    DrawCanvas();
  }
}

void WidgetCanvas::DrawCanvas() {
  switch (mode_) {
    case SurfaceType::kSurfaceBlackout:
      DLOG(INFO) << "Canvas Blackout\n";
      // Set background black
      GetRenderer()->SetColourForeground(HMI_BLACK);
      GetRenderer()->SetColourBackground(HMI_BLACK);
      GetRenderer()->DrawRectangle(0, 0, width_, height_, true);
      break;
    case SurfaceType::kSurfaceCairo:
      GetRenderer()->TextureRGB(0, 0, surface_);
      break;
    case SurfaceType::kSurfaceFile:
      // GetRenderer()->TextureRGB(0, 0, buffer_);
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

void WidgetCanvas::SetMode(const SurfaceType mode) { mode_ = mode; }

void WidgetCanvas::SetBlackout() { mode_ = SurfaceType::kSurfaceBlackout; }

bool WidgetCanvas::GetBlackout() const { return (mode_ == SurfaceType::kSurfaceBlackout); }

SurfaceType WidgetCanvas::GetMode() const { return mode_; }

void WidgetCanvas::SetFilename(const std::string_view filename) {
  mode_ = SurfaceType::kSurfaceFile;
  filename_ = std::string(filename);
}

void WidgetCanvas::SetSurface(cairo_surface_t* surface) {
  mode_ = SurfaceType::kSurfaceCairo;
  surface_ = surface;
}

void WidgetCanvas::SetSurfaceDefault() {
  // No surface is the default
  mode_ = SurfaceType::kSurfaceNone;
}

}  // namespace gva
