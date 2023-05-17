//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file gva_application_types.h
///

#ifndef HMIDISPLAY_GVA_APPLICATION_TYPES_H_
#define HMIDISPLAY_GVA_APPLICATION_TYPES_H_

#include <gtk/gtk.h>

/// \brief The GVA application type and associated data
struct gtkType {
  /// The GTK application
  GtkApplication* app;
  /// The GTK window
  GtkWidget* win;
  /// The GTK drawing area
  GtkWidget* draw;
  /// The draw area height
  uint32_t height;
  /// The draw area width
  uint32_t width;
};

#endif  // HMIDISPLAY_GVA_APPLICATION_TYPES_H_
