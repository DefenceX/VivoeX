#ifndef EVENTS_GVA_HPP
#define EVENTS_GVA_HPP
#include <X11/Xlib.h>
#include "gva.hpp"

namespace gva
{
  enum eventEnumType {
    NO_EVENT = 0,
    KEY_EVENT,
    TOUCH_EVENT,
    DDS_EVENT,
    RESIZE_EVENT,
    REDRAW_EVENT
  };

  struct touchType {
    int x;
    int y;
  };

  struct resolutionType {
    int width;
    int height;
  };

  class eventGvaType {
  public:
    eventEnumType type;
    gvaKeyEnum key;
    touchType toutch;
    resolutionType resize;
  };

  class eventsGva {
  public:
    eventsGva() { m_display = 0; };
    eventsGva(Display *display, Window *window); 
    int nextGvaEvent(eventGvaType *event); // Use for X11/DDS/Touch events
    void flush();
  private:
   Display *m_display = 0;
   Window *m_window = 0;
  };
};

#endif
