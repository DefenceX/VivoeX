//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file renderer_cairo_types.h
///

#ifndef HMICORE_RENDERER_CAIRO_TYPES_H_
#define HMICORE_RENDERER_CAIRO_TYPES_H_

#include <gtk/gtk.h>

#include "hmicore/renderer.h"

namespace gva {

/// Class definition of the HandleType
class HandleType {
 public:
  /// Construct a new Handle Type object
  uint32_t handle;
  /// true if in user
  bool inUse;
  /// True if fullscreen
  bool fullscreen;
  /// The screen dimensions
  ResolutionType size;
  /// Cairo screen surface
  cairo_surface_t *surface;
  /// Cairo context
  cairo_t *cr;
};

/// Class definition of the DrawType
enum class DrawType {
  kCommandUndefined = 0,
  kCommandCircle,
  kCommandArc,
  kCommandColourBackground,
  kCommandColourForeground,
  kCommandImageTexture,
  kCommandImageTexturePersist,
  kCommandLineJoin,
  kCommandPenColour,
  kCommandPenCurve,
  kCommandPenCurveTo,
  kCommandPenLine,
  kCommandPenDraw,
  kCommandPenMove,
  kCommandPenRectangle,
  kCommandPenRoundedRectangle,
  kCommandPenThickness,
  kCommandPenTriangle,
  kCommandSave,
  kCommandRestore,
  kCommandScale,
  kCommandTranslate,
  kCommandRotate,
  kCommandClosePath,
  kCommandTextFont,
  kCommandPush,
  kCommandPop,
  kCommandText
};

}  // namespace gva

#endif  // HMICORE_RENDERER_CAIRO_TYPES_H_
