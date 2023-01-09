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
  kRedrawEvent,
  kWidgetUpdate
};

struct TouchType {
  int x = 0;
  int y = 0;
};

class EventGvaType {
 public:
  EventGvaType() = default;
  EventGvaType(int x, int y) {
    touch_.x = x;
    touch_.y = y;
    type_ = EventEnumType::kTouchEvent;
  }
  explicit EventGvaType(GvaKeyEnum key) : key_(key) { type_ = EventEnumType::kNoEvent; }
  EventEnumType type_ = EventEnumType::kNoEvent;
  GvaKeyEnum key_ = GvaKeyEnum::kKeyUnknown;
  TouchType touch_;
  ResolutionType resize_;
};

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

#endif  // HMI_DISPLAY_SRC_EVENTS_GVA_H_
