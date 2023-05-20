//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
//
/// \file events_gva.h
///

#ifndef HMICORE_EVENTS_GVA_H_
#define HMICORE_EVENTS_GVA_H_

#include <gtk/gtk.h>

#include <vector>

#include "hmicore/gva.h"
#include "hmicore/renderer_gva.h"
#include "hmidisplay/gva_application_types.h"

namespace gva {

/// Class defining the events
class EventsGva {
 public:
  //
  ///
  /// \param window The GTK3 window
  /// \param touch Touch event register
  ///
  EventsGva(gtkType *window, TouchGva *touch);

  ///
  /// \brief Get the next event from the queue
  ///
  /// \param event
  /// \return GvaStatusTypes
  ///
  GvaStatusTypes NextGvaEvent(EventGvaType *event);  // Use for GTK/DDS/Touch events

  ///
  /// \brief Process a GTK button press event
  ///
  /// \param widget
  /// \param event
  /// \param data
  /// \return gboolean
  ///
  static gboolean ButtonPressEventCb(GtkWidget *widget, GdkEventButton *event, gpointer data);

  ///
  /// \brief  A button press event or touch label event, key released
  ///
  /// \param widget
  /// \param event
  /// \param data
  /// \return gboolean
  ///
  static gboolean ButtonReleaseEventCb(GtkWidget *widget, GdkEventButton *event, gpointer data);

  ///
  /// \brief Handle button press events by either Drawing a rectangle or clearing the surface, depending on which
  /// button was pressed. The button-press signal handler receives a GdkEventButton struct which contains this
  /// information.
  ///
  /// \param widget
  /// \param event
  /// \return gboolean
  ///
  static gboolean KeyPressEventCb(GtkWidget *widget, GdkEventKey *event);

  ///
  /// \brief Handle button press events by either Drawing a rectangle or clearing the surface, depending on which
  /// button was pressed. The button-press signal handler receives a GdkEventButton struct which contains this
  /// information.
  ///
  /// \param widget
  /// \param event
  /// \return gboolean
  ///
  static gboolean KeyReleaseEventCb(GtkWidget *widget, GdkEventKey *event);

  ///
  /// \brief Get the Window object
  ///
  /// \return gtkType*
  ///
  gtkType *GetWindow() { return window_; }

  /// The event queue
  static std::vector<EventGvaType> eventqueue_;

  ///
  /// \brief Create a refresh event because a widget was updated and queue it
  ///
  ///
  static void CreateRefreshEvent();

 private:
  ///
  /// \brief Process the key event and return the enum value
  ///
  /// \param key the raw key value
  /// \return GvaKeyEnum representing the key
  ///
  static GvaKeyEnum ProcessFunctionEvents(unsigned int key);

  ///
  /// \brief Process the key event and return the enum value
  ///
  /// \param key the raw key value
  /// \return GvaKeyEnum representing the key
  ///
  static GvaKeyEnum ProcessFunctionKeyEvents(unsigned int key);

  ///
  /// \brief Create a Key Event and queue it
  ///
  /// \param Widget
  /// \param event
  /// \param type
  /// \return gboolean
  ///
  static gboolean CreateKeyEvent(GtkWidget *Widget, GdkEventKey *event, EventEnumType type);
  gtkType *window_;
  static uint32_t previous_key_;
  static TouchGva *touch_;
};

};  // namespace gva

#endif  // HMICORE_EVENTS_GVA_H_
