///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief Process events (touch and IO)
///
/// \file events_gva.h
///

#ifndef HMI_DISPLAY_SRC_EVENTS_GVA_H_
#define HMI_DISPLAY_SRC_EVENTS_GVA_H_
#include <gtk/gtk.h>

#include <vector>

#include "src/gva.h"
#include "src/renderer_gva.h"

namespace gva {

enum EventEnumType { NO_EVENT = 0, KEY_EVENT, TOUCH_EVENT, DDS_EVENT, RESIZE_EVENT, REDRAW_EVENT };

struct TouchType {
  int x;
  int y;
};

class EventGvaType {
 public:
  EventGvaType() { type = NO_EVENT; }
  EventGvaType(int x, int y) {
    touch_.x = x;
    touch_.y = y;
    type = TOUCH_EVENT;
  }
  explicit EventGvaType(GvaKeyEnum key) : key_(key) { type = KEY_EVENT; }
  EventEnumType type;
  GvaKeyEnum key_;
  TouchType touch_;
  ResolutionType resize_;
};

static std::vector<EventGvaType> eventqueue_;
static TouchGva *touch_;

class EventsGva {
 public:
  EventsGva(gtkType *window, TouchGva *touch);
  uint32_t NextGvaEvent(EventGvaType *event);  // Use for GTK/DDS/Touch events
  static gboolean ButtonPressEventCb(GtkWidget *Widget, GdkEventButton *event, gpointer data);
  static gboolean KeyPressEventCb(GtkWidget *Widget, GdkEventKey *event);
  gtkType *GetWindow() { return window_; }

 private:
  gtkType *window_;
};

};  // namespace gva

#endif  // HMI_DISPLAY_SRC_EVENTS_GVA_H_