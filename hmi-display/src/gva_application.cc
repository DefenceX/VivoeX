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

#include "src/widgets/keyboard.h"
#include "src/widgets/widget.h"

GvaApplication::GvaApplication(const Options options, const std::string &ipaddr, const uint32_t port) {
  options_ = options;
  char tmp[256];

  // instantiate events
  gva::EventKeyPowerOn on;

  // Start the state machine
  gva::hmi::start();

  // Open window and start event loop and set inital state to 'on'
  gva::hmi::dispatch(on);

  //
  // Initialise the display events
  //
  io_ = std::make_shared<gva::EventsGva>(gva::hmi::GetRendrer()->GetWindow(), gva::hmi::GetRendrer()->GetTouch());

  //
  // Setup video sources (default size will be 640 x 480 unless specified)
  // @todo hmi_display: Fix issue with stream blocking execution on RTP input
  // @body The RTP stream blocks for a whole frame slowing down the HMI.
  if (options_.videoEnabled == true) {
    rtp_stream1_ = new gva::GvaVideoRtpYuv(ipaddr, port);
    snprintf(tmp, strlen(tmp), "Resolution %dx%d", rtp_stream1_->GetHeight(), rtp_stream1_->GetWidth());
    gva::logGva::log(tmp, gva::LOG_INFO);
    rtp_buffer_ = reinterpret_cast<char *>(malloc(rtp_stream1_->GetHeight() * rtp_stream1_->GetWidth() * 4));
    snprintf(tmp, strlen(tmp), "GVA Incoming RTP stream initalized %s:%d", ipaddr, port);
    gva::logGva::log(tmp, gva::LOG_INFO);
  }
}

void GvaApplication::Exec() {
  //
  // Start the render and event loop
  //
  gva::hmi::GetRendrer()->Init(640, 480, gva::ConfigData::GetInstance()->GetFullscreen(), Update,
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
void GvaApplication::Dispatch(gva::GvaKeyEnum key) {
  gva::EventKeyFunction input;

  input.key = key;
  gva::hmi::dispatch(input);
}

///
/// \brief Toggle full screen mode
///
/// \param render Renderer handle
///
void GvaApplication::Fullscreen(gva::HandleType *render) {
  render->fullscreen ? gtk_window_unfullscreen(GTK_WINDOW(render->win.win))
                     : gtk_window_fullscreen(GTK_WINDOW(render->win.win));
  render->fullscreen = render->fullscreen ? false : true;
  gva::ConfigData::GetInstance()->SetFullscreen(render->fullscreen);
  gva::logGva::log("Toggle fullscreen", gva::LOG_INFO);
}

gva::GvaVideoRtpYuv *GvaApplication::rtp_stream1_ = nullptr;
GvaApplication::Options GvaApplication::options_ = {};

///
/// \brief Renderer callback to update screen
///
/// \param arg Callback arguments
/// \param user_data Renderer handle
///
void GvaApplication::Update(void *arg, gpointer user_data) {
  gva::EventsGva *io = static_cast<gva::EventsGva *>(arg);
  gva::EventGvaType event;
  bool update = true;
  static int c = 0;
  static uint32_t count = 0;
  gva::HandleType *render = static_cast<gva::HandleType *>(user_data);

  if (options_.videoEnabled) {
    // Get the live video frame if Driver (DRV)
    if (gva::hmi::GetScreen()->currentFunction == gva::GvaFunctionEnum::kDriver) {
      gva::hmi::GetScreen()->canvas.bufferType = gva::SurfaceType::kSurfaceCairo;
      gva::hmi::GetScreen()->canvas.surface =
          cairo_image_surface_create(CAIRO_FORMAT_RGB24, DEFAULT_WIDTH, DEFAULT_HEIGHT);
      char *test = reinterpret_cast<char *>(cairo_image_surface_get_data(gva::hmi::GetScreen()->canvas.surface));
      rtp_stream1_->GvaReceiveFrame(test, gva::RGBA_COLOUR);
      cairo_surface_mark_dirty(gva::hmi::GetScreen()->canvas.surface);

      // @todo hmi_display: Add RTP HMI streaming output to display.
      // @body The HMI window is only a preview. Add RTP output and headless
      // mode.
    }
  }

  gva::hmi::GetRendrer()->Update();

  io->NextGvaEvent(&event);
  switch (event.type_) {
    case gva::kKeyEventReleased: {
      gva::WidgetPlanPositionIndicator *compass =
          static_cast<gva::WidgetPlanPositionIndicator *>(gva::hmi::GetRendrer()->GetWidget(gva::KWidgetTypeCompass));

      auto keyboard = (gva::WidgetKeyboard *)gva::hmi::GetRendrer()->GetWidget(gva::KWidgetTypeKeyboard);

      gva::logGva::log("[GVA} Key event being processed value=" + std::to_string(int(event.key_)), gva::LOG_INFO);

      switch (event.key_) {
        case gva::GvaKeyEnum::kKeyEscape:
          // exit on ESC key press
          if (render->surface) cairo_surface_destroy(render->surface);
          g_application_quit(G_APPLICATION(render->win.app));
          break;
        case gva::GvaKeyEnum::KKeySituationalAwareness:
          // 1 maps to F1
          {
            gva::EventKeySA sa;

            gva::hmi::dispatch(sa);
          }
          break;
        case gva::GvaKeyEnum::kKeyWeapon:
          // 2 maps to F2
          {
            gva::EventKeyWPN wpn;

            gva::hmi::dispatch(wpn);
          }
          break;
        case gva::GvaKeyEnum::kKeyDefensiveSystems:
          // 3 maps to F3
          {
            gva::EventKeyDEF def;

            gva::hmi::dispatch(def);
          }
          break;
        case gva::GvaKeyEnum::kKeySystems:
          // 4 maps to F4
          {
            gva::EventKeySYS sys;

            gva::hmi::dispatch(sys);
          }
          break;
        case gva::GvaKeyEnum::kKeyDriver:
          // 5 maps to F5
          {
            gva::EventKeyDRV drv;

            gva::hmi::dispatch(drv);
          }
          break;
        case gva::GvaKeyEnum::kKeySpecialToRole:
          // 6 maps to F6
          {
            gva::EventKeySTR str;

            gva::hmi::dispatch(str);
          }
          break;
        case gva::GvaKeyEnum::kKeyCommunications:
          // 7 maps to F7
          {
            gva::EventKeyCOM com;

            gva::hmi::dispatch(gva::EventKeyCOM());
          }
          break;
        case gva::GvaKeyEnum::kKeyBattlefieldManagementSystem:
          // 8 maps to F8
          {
            gva::EventKeyBMS bms;

            gva::hmi::dispatch(bms);
          }
          break;
        case gva::GvaKeyEnum::kKeyF1:
        case gva::GvaKeyEnum::kKeyF2:
        case gva::GvaKeyEnum::kKeyF3:
        case gva::GvaKeyEnum::kKeyF4:
        case gva::GvaKeyEnum::kKeyF5:
        case gva::GvaKeyEnum::kKeyF6:
        case gva::GvaKeyEnum::kKeyF7:
        case gva::GvaKeyEnum::kKeyF8:
        case gva::GvaKeyEnum::kKeyF9:
        case gva::GvaKeyEnum::kKeyF10:
        case gva::GvaKeyEnum::kKeyF11:
        case gva::GvaKeyEnum::kKeyF12:
        case gva::GvaKeyEnum::kKeyF13:  // All drop through to here, just dispatch
          Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF14:
          // Control Alarms
          {
            gva::EventKeyAlarms alarms;

            gva::hmi::dispatch(alarms);
            Dispatch(event.key_);
          }
          break;
        case gva::GvaKeyEnum::kKeyF15:
          // F15
          Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF16:
          // F16
          Dispatch(gva::GvaKeyEnum::kKeyF16);
          break;
        case gva::GvaKeyEnum::kKeyF17:
          // F17 Control Arrow Up
          {
            keyboard->SetMode((keyboard->GetMode() == gva::KeyboardModeType::kKeyboardUpper)
                                  ? gva::KeyboardModeType::kKeyboardLower
                                  : gva::KeyboardModeType::kKeyboardUpper);
            Dispatch(gva::GvaKeyEnum::kKeyF17);
          }
          break;
        case gva::GvaKeyEnum::kKeyF18:
          // F18 Control Arrow Down
          {
            keyboard->SetMode((keyboard->GetMode() == gva::KeyboardModeType::kKeyboardNumbers)
                                  ? gva::KeyboardModeType::kKeyboardUpper
                                  : gva::KeyboardModeType::kKeyboardNumbers);
            Dispatch(event.key_);
          }
          break;
        case gva::GvaKeyEnum::kKeyF19:
          // F19 Control labels
          Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF20:
          // F20
          Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyFullscreen:
          // f toggle fullscreen
          Fullscreen(render);
          gva::hmi::GetRendrer()->GetTouch()->SetResolution(gdk_screen_width(), gdk_screen_height());
          break;
        case gva::GvaKeyEnum::kKeyKeyboard:
          // k toggle keyboard
          { keyboard->SetVisible(keyboard->GetVisible() ? false : true); }
          break;
        case gva::GvaKeyEnum::kKeyPlus:
          compass->SetBearing(compass->GetBearing() + 2);
          break;
        case gva::GvaKeyEnum::kKeyRightArrow:
          compass->SetBearingSight(compass->GetBearingSight() + 2);
          break;
        case gva::GvaKeyEnum::kKeyMinus:
          compass->SetBearing(compass->GetBearing() - 2);
          break;
        case gva::GvaKeyEnum::kKeyLeftArrow:
          compass->SetBearingSight(compass->GetBearingSight() - 2);
          break;
        case gva::GvaKeyEnum::kKeyNextLabel: {
          Dispatch(event.key_);
        } break;
        case gva::GvaKeyEnum::kKeyPreviousLabel: {
          Dispatch(event.key_);
        } break;
        default:
          printf("[GVA] KeyPress not defined 0x%x\n", event.key_);
          update = false;
          break;
      }
      if (update) gva::hmi::GetRendrer()->Update();
    } break;
    case gva::kResizeEvent: {
      printf("[GVA] WindowResize: %d x %d\n", event.resize_.width, event.resize_.height);
      if (event.resize_.width != gva::hmi::GetRendrer()->GetWidth() ||
          event.resize_.height != gva::hmi::GetRendrer()->GetHeight()) {
        printf("[GVA] WindowResize: %d x %d\n", event.resize_.width, event.resize_.height);
        gva::hmi::GetRendrer()->SetWidth(event.resize_.width);
        gva::hmi::GetRendrer()->SetHeight(event.resize_.height);
        gva::hmi::GetRendrer()->Update();
        gva::hmi::GetRendrer()->GetTouch()->SetResolution(event.resize_.width, event.resize_.height);
      }
    } break;
    case gva::kRedrawEvent: {
      gva::hmi::GetRendrer()->Update();
    } break;
  }
}
