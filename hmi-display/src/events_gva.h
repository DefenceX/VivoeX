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
//
//
// \file events_gva.h
//

#ifndef HMI_DISPLAY_SRC_EVENTS_GVA_H_
#define HMI_DISPLAY_SRC_EVENTS_GVA_H_
#include <gtk/gtk.h>

#include <vector>

#include "src/gva.h"
#include "src/renderer_gva.h"

namespace gva {

enum class EventEnumType {
  kNoEvent = 0,
  kKeyEventPressed,
  kKeyEventReleased,
  kTouchEvent,
  kDdsEvent,
  kResizeEvent,
  kRedrawEvent
};

struct TouchType {
  int x;
  int y;
};

class EventGvaType {
 public:
  EventGvaType() { type_ = EventEnumType::kNoEvent; }
  EventGvaType(int x, int y) {
    touch_.x = x;
    touch_.y = y;
    type_ = EventEnumType::kTouchEvent;
  }
  explicit EventGvaType(GvaKeyEnum key) : key_(key) { type_ = EventEnumType::kNoEvent; }
  EventEnumType type_;
  GvaKeyEnum key_;
  TouchType touch_;
  ResolutionType resize_;
};

static std::vector<EventGvaType> eventqueue_;

class EventsGva {
 public:
  //
  ///
  /// \param window The GTK3 window
  /// \param touch Touch event register
  ///
  EventsGva(gtkType *window, TouchGva *touch);
  GvaStatusTypes NextGvaEvent(EventGvaType *event);  // Use for GTK/DDS/Touch events
  static gboolean ButtonPressEventCb(GtkWidget *Widget, GdkEventButton *event, gpointer data);

  ///
  /// \brief  A button press event or touch label event, key released
  ///
  /// \param Widget
  /// \param event
  /// \param data
  /// \return gboolean
  ///
  static gboolean ButtonReleaseEventCb(GtkWidget *Widget, GdkEventButton *event, gpointer data);

  ///
  /// \brief Handle button press events by either Drawing a rectangle or clearing the surface, depending on which button
  /// was pressed. The ::button-press signal handler receives a GdkEventButton struct which contains this information.
  ///
  /// \param Widget
  /// \param event
  /// \return gboolean
  ///
  static gboolean KeyPressEventCb(GtkWidget *Widget, GdkEventKey *event);

  ///
  /// \brief Handle button press events by either Drawing a rectangle or clearing the surface, depending on which button
  /// was pressed. The ::button-press signal handler receives a GdkEventButton struct which contains this information.
  ///
  /// \param Widget
  /// \param event
  /// \return gboolean
  ///
  static gboolean KeyReleaseEventCb(GtkWidget *Widget, GdkEventKey *event);

  ///
  /// \brief Get the Window object
  ///
  /// \return gtkType*
  ///
  gtkType *GetWindow() { return window_; }

 private:
  static gboolean CreateKeyEvent(GtkWidget *Widget, GdkEventKey *event, EventEnumType type);
  gtkType *window_;
};

};  // namespace gva

#endif  // HMI_DISPLAY_SRC_EVENTS_GVA_H_
