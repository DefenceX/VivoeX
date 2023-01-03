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
// \file gva_application.cc
//

#include "gva_application.h"

#include <memory>

#include "common/log_gva.h"
#include "common/utils.h"
#include "src/gva_functions_common.h"
#include "src/trace.h"
#include "src/widgets/keyboard.h"
#include "src/widgets/widget.h"

GvaApplication::Options GvaApplication::options_ = {};
std::unique_ptr<gva::GvaVideoRtpYuv> GvaApplication::rtp_stream1_ = nullptr;
uint32_t GvaApplication::update_counter_ = 0;
bool GvaApplication::first_execution_ = true;

GvaApplication::GvaApplication(const Options &options, const std::string &ipaddr, const uint32_t port) {
  options_ = options;

  rtp_stream1_ = std::make_unique<gva::GvaVideoRtpYuv>(ipaddr, port);

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
  if (options_.videoEnabled_ == true) {
    gva::logGva::log(
        "Resolution " + std::to_string(rtp_stream1_->GetHeight()) + "x" + std::to_string(rtp_stream1_->GetWidth()),
        gva::DebugLevel::kLogInfo);

    gva::logGva::log("GVA Incoming RTP stream initalized " + ipaddr + ":" + std::to_string(port),
                     gva::DebugLevel::kLogInfo);
  }
}

//
///
///
void GvaApplication::Exec() const {
  //
  // Start the render and event loop
  //

  // Draw the first screen, then the callback (Update) will refresh as required
  gva::hmi::GetRendrer()->Init(640, 480, gva::ConfigData::GetInstance()->GetFullscreen(), Update,
                               reinterpret_cast<void *>(io_.get()));
  // Free the config reader (writes data back to disk)
  gva::ConfigData::GetInstance()->WriteData();
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
  gva::logGva::log("Toggle fullscreen", gva::DebugLevel::kLogInfo);
}

///
/// \brief Renderer callback to update screen
///
/// \param arg Callback arguments
/// \param user_data Renderer handle
///
void GvaApplication::Update(void *arg, gpointer user_data) {
  auto *io = static_cast<gva::EventsGva *>(arg);
  gva::EventGvaType event;
  bool update = true;
  const gva::HandleType *render = static_cast<gva::HandleType *>(user_data);

  tracepoint(vivoe_lite, app_callback, update_counter_);

  if ((options_.videoEnabled_) && (gva::hmi::GetScreen()->currentFunction == gva::GvaFunctionEnum::kDriver)) {
    gva::hmi::GetScreen()->canvas.bufferType = gva::SurfaceType::kSurfaceCairo;
    gva::hmi::GetScreen()->canvas.surface =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, gva::kMinimumWidth, gva::kMinimumHeight);
    auto test = (char *)(cairo_image_surface_get_data(gva::hmi::GetScreen()->canvas.surface));
    rtp_stream1_->GvaReceiveFrame(test, gva::VideoFormat::kFormatRgbaColour);
    cairo_surface_mark_dirty(gva::hmi::GetScreen()->canvas.surface);

    // @todo hmi_display: Add RTP HMI streaming output to display.
    // @body The HMI window is only a preview. Add RTP output and headless
    // mode.
  }

  io->NextGvaEvent(&event);

  // Time to update the screen
  if ((first_execution_) || (event.type_ == gva::EventEnumType::kWidgetUpdate)) {
    gva::hmi::GetRendrer()->Update();
    first_execution_ = false;
    return;
  }

  // No events found to nothing to do here, just return
  if (event.type_ == gva::EventEnumType::kNoEvent) {
    return;
  }

  switch (event.type_) {
    default:
      break;
    case gva::EventEnumType::kKeyEventPressed:
      gva::logGva::log("[GVA] Key press event being processed value=" + std::to_string(int(event.key_)),
                       gva::DebugLevel::kLogInfo);

      switch (event.key_) {
        case gva::GvaKeyEnum::kKeySituationalAwareness:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(0);
          break;
        case gva::GvaKeyEnum::kKeyWeapon:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(1);
          break;
        case gva::GvaKeyEnum::kKeyDefensiveSystems:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(2);
          break;
        case gva::GvaKeyEnum::kKeySystems:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(3);
          break;
        case gva::GvaKeyEnum::kKeyDriver:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(4);
          break;
        case gva::GvaKeyEnum::kKeySpecialToRole:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(5);
          break;
        case gva::GvaKeyEnum::kKeyCommunications:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(6);
          break;
        case gva::GvaKeyEnum::kKeyBattlefieldManagementSystem:
          gva::hmi::GetScreen()->function_top->SetEnabledEnabledChanging(7);
          break;
        case gva::GvaKeyEnum::kKeyF1:
          gva::hmi::GetScreen()->function_left.SetEnabledEnabledChanging(0);
          break;
        case gva::GvaKeyEnum::kKeyF2:
          gva::hmi::GetScreen()->function_left.SetEnabledEnabledChanging(1);
          break;
        case gva::GvaKeyEnum::kKeyF3:
          gva::hmi::GetScreen()->function_left.SetEnabledEnabledChanging(2);
          break;
        case gva::GvaKeyEnum::kKeyF4:
          gva::hmi::GetScreen()->function_left.SetEnabledEnabledChanging(3);
          break;
        case gva::GvaKeyEnum::kKeyF5:
          gva::hmi::GetScreen()->function_left.SetEnabledEnabledChanging(4);
          break;
        case gva::GvaKeyEnum::kKeyF6:
          gva::hmi::GetScreen()->function_left.SetEnabledEnabledChanging(5);
          break;
        case gva::GvaKeyEnum::kKeyF7:
          gva::hmi::GetScreen()->function_right.SetEnabledEnabledChanging(0);
          break;
        case gva::GvaKeyEnum::kKeyF8:
          gva::hmi::GetScreen()->function_right.SetEnabledEnabledChanging(1);
          break;
        case gva::GvaKeyEnum::kKeyF9:
          gva::hmi::GetScreen()->function_right.SetEnabledEnabledChanging(2);
          break;
        case gva::GvaKeyEnum::kKeyF10:
          gva::hmi::GetScreen()->function_right.SetEnabledEnabledChanging(3);
          break;
        case gva::GvaKeyEnum::kKeyF11:
          gva::hmi::GetScreen()->function_right.SetEnabledEnabledChanging(4);
          break;
        case gva::GvaKeyEnum::kKeyF12:
          gva::hmi::GetScreen()->function_right.SetEnabledEnabledChanging(5);
          break;
        case gva::GvaKeyEnum::kKeyF13:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(0);
          break;
        case gva::GvaKeyEnum::kKeyF14:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(1);
          break;
        case gva::GvaKeyEnum::kKeyF15:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(2);
          break;
        case gva::GvaKeyEnum::kKeyF16:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(3);
          break;
        case gva::GvaKeyEnum::kKeyF17:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(4);
          break;
        case gva::GvaKeyEnum::kKeyF18:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(5);
          break;
        case gva::GvaKeyEnum::kKeyF19:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(6);
          break;
        case gva::GvaKeyEnum::kKeyF20:
          gva::hmi::GetScreen()->control->SetEnabledEnabledChanging(7);
          break;
        case gva::GvaKeyEnum::kKeyUnknown:  // No an active touch zone so just reset everything
        default:
          update = false;
          break;
      }
      break;

    case gva::EventEnumType::kKeyEventReleased: {
      auto *compass = static_cast<gva::WidgetPlanPositionIndicator *>(
          gva::hmi::GetRendrer()->GetWidget(gva::widget::WidgetEnum::KWidgetTypeCompass));

      auto keyboard =
          (gva::WidgetKeyboard *)gva::hmi::GetRendrer()->GetWidget(gva::widget::WidgetEnum::KWidgetTypeKeyboard);

      gva::logGva::log("[GVA] Key release event being processed value=" + std::to_string(int(event.key_)),
                       gva::DebugLevel::kLogInfo);

      switch (event.key_) {
        case gva::GvaKeyEnum::kKeyEscape:
          // exit on ESC key press
          if (render->surface) cairo_surface_destroy(render->surface);
          g_application_quit(G_APPLICATION(render->win.app));
          break;
        case gva::GvaKeyEnum::kKeyBlackout:
          Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeySituationalAwareness:
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

            gva::hmi::dispatch(com);
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
          if (gva::hmi::GetScreen()->function_left.Active(0)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF2:
          if (gva::hmi::GetScreen()->function_left.Active(1)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF3:
          if (gva::hmi::GetScreen()->function_left.Active(2)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF4:
          if (gva::hmi::GetScreen()->function_left.Active(3)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF5:
          if (gva::hmi::GetScreen()->function_left.Active(4)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF6:
          if (gva::hmi::GetScreen()->function_left.Active(5)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF7:
          if (gva::hmi::GetScreen()->function_right.Active(0)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF8:
          if (gva::hmi::GetScreen()->function_right.Active(1)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF9:
          if (gva::hmi::GetScreen()->function_right.Active(2)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF10:
          if (gva::hmi::GetScreen()->function_right.Active(3)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF11:
          if (gva::hmi::GetScreen()->function_right.Active(4)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF12:
          if (gva::hmi::GetScreen()->function_right.Active(5)) Dispatch(event.key_);
          break;
        case gva::GvaKeyEnum::kKeyF13:
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
            keyboard->SetMode((keyboard->GetMode() == gva::widget::KeyboardModeType::kKeyboardUpper)
                                  ? gva::widget::KeyboardModeType::kKeyboardLower
                                  : gva::widget::KeyboardModeType::kKeyboardUpper);
            Dispatch(event.key_);
          }
          break;
        case gva::GvaKeyEnum::kKeyF18:
          // F18 Control Arrow Down
          {
            keyboard->SetMode((keyboard->GetMode() == gva::widget::KeyboardModeType::kKeyboardNumbers)
                                  ? gva::widget::KeyboardModeType::kKeyboardUpper
                                  : gva::widget::KeyboardModeType::kKeyboardNumbers);
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
          // m|M toggle fullscreen
          Fullscreen(const_cast<gva::HandleType *>(render));
          {
            GdkRectangle workarea;
            GdkMonitor *monitor = gdk_display_get_primary_monitor(gdk_display_get_default());
            if (monitor) {
              gdk_monitor_get_workarea(monitor, &workarea);
              gva::logGva::log(
                  "Switching resolution to " + std::to_string(workarea.width) + "x" + std::to_string(workarea.height),
                  gva::DebugLevel::kLogInfo);

              gva::hmi::GetRendrer()->GetTouch()->SetResolution(workarea.width, workarea.height);
            } else {
              gva::logGva::log("gdk_monitor_get_workarea failed when switching to fullscreen.",
                               gva::DebugLevel::kLogError);
            }
          }
          break;
        case gva::GvaKeyEnum::kKeyKeyboard:
          // k toggle keyboard
          { keyboard->SetVisible(keyboard->GetVisible() ? false : true); }
          break;
        case gva::GvaKeyEnum::kKeyPlus:
          compass->SetBearing(gva::DegreesAdd(compass->GetBearing(), 2));
          break;
        case gva::GvaKeyEnum::kKeyGreaterThan:
          compass->SetBearingSight(gva::DegreesAdd(compass->GetBearingSight(), 2));
          break;
        case gva::GvaKeyEnum::kKeyMinus:
          compass->SetBearing(gva::DegreesSubtract(compass->GetBearing(), 2));
          break;
        case gva::GvaKeyEnum::kKeyLessThen:
          compass->SetBearingSight(gva::DegreesSubtract(compass->GetBearingSight(), 2));
          break;
        case gva::GvaKeyEnum::kKeyRightArrow: {
          double brightness = gva::ConfigData::GetInstance()->GetBrightness();
          brightness = brightness + 0.05;
          if (brightness > 1) brightness = 1;
          gva::SetBrightness(brightness);
          gva::ConfigData::GetInstance()->SetBrightness(brightness);
        } break;
        case gva::GvaKeyEnum::kKeyLeftArrow: {
          double brightness = gva::ConfigData::GetInstance()->GetBrightness();
          brightness = brightness - 0.05;
          if (brightness <= 0) brightness = 0;
          gva::SetBrightness(brightness);
          gva::ConfigData::GetInstance()->SetBrightness(brightness);
        } break;
        case gva::GvaKeyEnum::kKeyNextLabel: {
          Dispatch(event.key_);
        } break;
        case gva::GvaKeyEnum::kKeyPreviousLabel: {
          Dispatch(event.key_);
        } break;
        default:
          gva::logGva::log("[GVA] Key release not defined " + std::to_string(int(event.key_)),
                           gva::DebugLevel::kLogInfo);
          // When we have wondered off a hotspot we need to reset and changing labels.
          gva::hmi::GetScreen()->function_left.ResetAllEnabledSelectedChanging();
          gva::hmi::GetScreen()->function_right.ResetAllEnabledSelectedChanging();
          gva::hmi::GetScreen()->function_top->ResetAllEnabledSelectedChanging();
          gva::hmi::GetScreen()->control->ResetAllEnabledSelectedChanging();
          Dispatch(event.key_);  // Dispatch it anyway as this will clear any existing changing states
          update = false;
          break;
      }
      break;
    }  // Key Released

    break;
    case gva::EventEnumType::kResizeEvent: {
      printf("[GVA] WindowResize: %d x %d", event.resize_.width, event.resize_.height);
      if (event.resize_.width != gva::hmi::GetRendrer()->GetWidth() ||
          event.resize_.height != gva::hmi::GetRendrer()->GetHeight()) {
        printf("[GVA] WindowResize: %d x %d", event.resize_.width, event.resize_.height);
        gva::hmi::GetRendrer()->SetWidth(event.resize_.width);
        gva::hmi::GetRendrer()->SetHeight(event.resize_.height);
        gva::hmi::GetRendrer()->GetTouch()->SetResolution(event.resize_.width, event.resize_.height);
        update = true;
      }
    } break;
    case gva::EventEnumType::kRedrawEvent: {
      update = true;
    } break;
  }

  // Only update if a change was detected
  if (update) {
    gva::hmi::GetRendrer()->Update();
    update_counter_++;
    tracepoint(vivoe_lite, app_callback, update_counter_);
  }

}  // namespace gva
