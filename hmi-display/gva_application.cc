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
/// \brief GVA application class
///
/// \file gva_application.cc
///

#include "gva_application.h"

#include <memory>

namespace gva {

gva::GvaApplication::GvaApplication(const Options options, std::string &ipaddr, const uint32_t port) {
  options_ = options;
  char tmp[256];

  // instantiate events
  EventKeyPowerOn on;

  // Start the state machine
  hmi::start();

  // Open window and start event loop and set inital state to 'on'
  hmi::dispatch(on);

  //
  // Initialise the display events
  //
  io_ = std::make_shared<EventsGva>(hmi::GetRendrer()->GetWindow(), hmi::GetRendrer()->GetTouch());

  //
  // Setup video sources (default size will be 640 x 480 unless specified)
  // @todo hmi_display: Fix issue with stream blocking execution on RTP input
  // @body The RTP stream blocks for a whole frame slowing down the HMI.
  if (options_.videoEnabled == true) {
    rtp_stream1_ = new GvaVideoRtpYuv(ipaddr, port);
    snprintf(tmp, strlen(tmp), "Resolution %dx%d", rtp_stream1_->GetHeight(), rtp_stream1_->GetWidth());
    logGva::log(tmp, LOG_INFO);
    rtp_buffer_ = reinterpret_cast<char *>(malloc(rtp_stream1_->GetHeight() * rtp_stream1_->GetWidth() * 4));
    snprintf(tmp, strlen(tmp), "GVA Incoming RTP stream initalized %s:%d", ipaddr, port);
    logGva::log(tmp, LOG_INFO);
  }
}

void GvaApplication::Exec() {
  //
  // Start the render and event loop
  //
  hmi::GetRendrer()->init(640, 480, gva::ConfigData::GetInstance()->GetFullscreen(), Update,
                          reinterpret_cast<void *>(io_.get()));
  // Free the config reader (writes data back to disk)
  gva::ConfigData::GetInstance()->WriteData();
}

GvaApplication::~GvaApplication() {
  //
  // Clean up code goes here
  //
  free(rtp_stream1_);
}

///
/// \brief Dispatch key events
///
/// \param key Key input to dispatch
///
void GvaApplication::Dispatch(GvaKeyEnum key) {
  EventKeyFunction input;

  input.key = key;
  hmi::dispatch(input);
}

///
/// \brief Toggle full screen mode
///
/// \param render Renderer handle
///
void GvaApplication::Fullscreen(HandleType *render) {
  render->fullscreen ? gtk_window_unfullscreen(GTK_WINDOW(render->win.win))
                     : gtk_window_fullscreen(GTK_WINDOW(render->win.win));
  render->fullscreen = render->fullscreen ? false : true;
  gva::ConfigData::GetInstance()->SetFullscreen(render->fullscreen);
  logGva::log("Toggle fullscreen", LOG_INFO);
}

GvaVideoRtpYuv *GvaApplication::rtp_stream1_ = nullptr;
GvaApplication::Options GvaApplication::options_ = {};

///
/// \brief Renderer callback to update screen
///
/// \param arg Callback arguments
/// \param user_data Renderer handle
///
void GvaApplication::Update(void *arg, gpointer user_data) {
  EventsGva *io = static_cast<EventsGva *>(arg);
  EventGvaType event;
  bool update = true;
  static int c = 0;
  static uint32_t count = 0;
  HandleType *render = static_cast<HandleType *>(user_data);

  io->NextGvaEvent(&event);

  if (options_.videoEnabled) {
    // Get the live video frame if Driver (DRV)
    if (hmi::GetScreen()->currentFunction == DRV) {
      hmi::GetScreen()->canvas.bufferType = SURFACE_CAIRO;
      hmi::GetScreen()->canvas.surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, DEFAULT_WIDTH, DEFAULT_HEIGHT);
      char *test = reinterpret_cast<char *>(cairo_image_surface_get_data(hmi::GetScreen()->canvas.surface));
      rtp_stream1_->GvaReceiveFrame(test, RGBA_COLOUR);
      cairo_surface_mark_dirty(hmi::GetScreen()->canvas.surface);

      // @todo hmi_display: Add RTP HMI streaming output to display.
      // @body The HMI window is only a preview. Add RTP output and headless
      // mode.
    }
  }

  hmi::GetRendrer()->Update();
  switch (event.type) {
    case KEY_EVENT: {
      Compass *compass = static_cast<Compass *>(hmi::GetRendrer()->GetWidget(WIDGET_TYPE_COMPASS));
      Keyboard *keyboard = static_cast<Keyboard *>(hmi::GetRendrer()->GetWidget(WIDGET_TYPE_KEYBOARD));
      switch (event.key_) {
        case KEY_ESC:
          // exit on ESC key press
          if (render->surface) cairo_surface_destroy(render->surface);
          g_application_quit(G_APPLICATION(render->win.app));
          break;
        case KEY_SA:
          // 1 maps to F1
          {
            EventKeySA sa;

            hmi::dispatch(sa);
          }
          break;
        case KEY_WPN:
          // 2 maps to F2
          {
            EventKeyWPN wpn;

            hmi::dispatch(wpn);
          }
          break;
        case KEY_DEF:
          // 3 maps to F3
          {
            EventKeyDEF def;

            hmi::dispatch(def);
          }
          break;
        case KEY_SYS:
          // 4 maps to F4
          {
            EventKeySYS sys;

            hmi::dispatch(sys);
          }
          break;
        case KEY_DRV:
          // 5 maps to F5
          {
            EventKeyDRV drv;

            hmi::dispatch(drv);
          }
          break;
        case KEY_STR:
          // 6 maps to F6
          {
            EventKeySTR str;

            hmi::dispatch(str);
          }
          break;
        case KEY_COM:
          // 7 maps to F7
          {
            EventKeyCOM com;

            hmi::dispatch(com);
          }
          break;
        case KEY_BMS:
          // 8 maps to F8
          {
            EventKeyBMS bms;

            hmi::dispatch(bms);
          }
          break;
        case KEY_F1:
          Dispatch(KEY_F1);
          break;
        case KEY_F2:
          Dispatch(KEY_F2);
          break;
        case KEY_F3:
          Dispatch(KEY_F3);
          break;
        case KEY_F4:
          Dispatch(KEY_F4);
          break;
        case KEY_F5:
          Dispatch(KEY_F5);
          break;
        case KEY_F6:
          Dispatch(KEY_F6);
          break;
        case KEY_F7:
          Dispatch(KEY_F7);
          break;
        case KEY_F8:
          Dispatch(KEY_F8);
          break;
        case KEY_F9:
          Dispatch(KEY_F9);
          break;
        case KEY_F10:
          Dispatch(KEY_F10);
          break;
        case KEY_F11:
          Dispatch(KEY_F11);
          break;
        case KEY_F12:
          Dispatch(KEY_F12);
          break;
        case KEY_F13:
          // Control UP
          { Dispatch(KEY_F13); }
          break;
        case KEY_F14:
          // Control Alarms
          {
            EventKeyAlarms alarms;

            hmi::dispatch(alarms);
            Dispatch(KEY_F14);
          }
          break;
        case KEY_F15:
          // F15
          { Dispatch(KEY_F15); }
          break;
        case KEY_F16:
          // F16
          { Dispatch(KEY_F16); }
          break;
        case KEY_F17:
          // F17 Control Arrow Up
          {
            keyboard->mode_ = (keyboard->mode_ == KEYBOARD_UPPER) ? KEYBOARD_LOWER : KEYBOARD_UPPER;
            Dispatch(KEY_F17);
          }
          break;
        case KEY_F18:
          // F18 Control Arrow Down
          {
            keyboard->mode_ = (keyboard->mode_ == KEYBOARD_NUMBERS) ? KEYBOARD_UPPER : KEYBOARD_NUMBERS;
            Dispatch(KEY_F18);
          }
          break;
        case KEY_F19:
          // F19 Control labels
          { Dispatch(KEY_F19); }
          break;
        case KEY_F20:
          // F20
          { Dispatch(KEY_F20); }
          break;
        case KEY_FULLSCREEN:
          // f toggle fullscreen
          Fullscreen(render);
          hmi::GetRendrer()->GetTouch()->SetResolution(gdk_screen_width(), gdk_screen_height());
          break;
        case KEY_KEYBOARD:
          // k toggle keyboard
          { keyboard->SetVisible(keyboard->GetVisible() ? false : true); }
          break;
        case KEY_PLUS:
          compass->bearing_ += 2;
          break;
        case KEY_GREATER:
          compass->bearingSight_ += 2;
          break;
        case KEY_MINUS:
          compass->bearing_ -= 2;
          break;
        case KEY_LESS:
          compass->bearingSight_ -= 2;
          break;
        case KEY_NEXT_LABEL: {
          Dispatch(KEY_NEXT_LABEL);
        } break;
        case KEY_PREV_LABEL: {
          Dispatch(KEY_PREV_LABEL);
        } break;
        default:
          printf("[GVA] KeyPress not defined 0x%x\n", event.key_);
          update = false;
          break;
      }
      if (update) hmi::GetRendrer()->Update();
    } break;
    case RESIZE_EVENT: {
      printf("[GVA] WindowResize: %d x %d\n", event.resize_.width, event.resize_.height);
      if (event.resize_.width != hmi::GetRendrer()->GetWidth() ||
          event.resize_.height != hmi::GetRendrer()->GetHeight()) {
        printf("[GVA] WindowResize: %d x %d\n", event.resize_.width, event.resize_.height);
        hmi::GetRendrer()->SetWidth(event.resize_.width);
        hmi::GetRendrer()->SetHeight(event.resize_.height);
        hmi::GetRendrer()->Update();
        hmi::GetRendrer()->GetTouch()->SetResolution(event.resize_.width, event.resize_.height);
      }
    } break;
    case REDRAW_EVENT: {
      hmi::GetRendrer()->Update();
    } break;
  }
}

}  // namespace gva
