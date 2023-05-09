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

struct gtkType {
  GtkApplication* app;
  GtkWidget* win;
  GtkWidget* draw;
  uint32_t height;
  uint32_t width;
};

#endif  // HMIDISPLAY_GVA_APPLICATION_TYPES_H_
