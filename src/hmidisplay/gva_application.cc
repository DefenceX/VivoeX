//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file gva_application.cc
///

#include "gva_application.h"

#include <glog/logging.h>
#include <gtk/gtk.h>

#include <memory>

#include "common/utils.h"
#include "hmicore/gva.h"
#include "hmicore/gva_functions_common.h"
#include "hmicore/widgets/keyboard.h"
#include "hmicore/widgets/widget.h"

GvaApplication::Options GvaApplication::options_ = {};
bool GvaApplication::first_execution_ = true;
std::shared_ptr<gva::EventsGva> GvaApplication::io_;

gtkType GvaApplication::gtk_;

void GvaApplication::CloseWindow(void) { gva::hmi::GetRendrer()->DestroySurface(); }

//
// ReDraw the screen from the surface. Note that the ::Draw
// signal receives a ready-to-be-used cairo_t that is already
// clipped to only Draw the exposed areas of the Widget
//
gboolean GvaApplication::DrawCb(GtkWidget *Widget, cairo_t *cr, gpointer dat [[maybe_unused]]) {
  gva::hmi::GetRendrer()->DrawSurface(cr);
  gtk_widget_queue_draw(Widget);
  return FALSE;
}

// Create a new surface of the appropriate size to store our HMI
gboolean GvaApplication::ConfigureEventCb(GtkWidget *Widget, GdkEventConfigure *event, gpointer data [[maybe_unused]]) {
  LOG(INFO) << "GTK configure event";
  gva::hmi::GetRendrer()->SetSurface(gdk_window_create_similar_surface(
      gtk_widget_get_window(Widget), CAIRO_CONTENT_COLOR, gtk_widget_get_allocated_width(Widget),
      gtk_widget_get_allocated_height(Widget)));

  int width = gtk_widget_get_allocated_width(Widget);
  int height = gtk_widget_get_allocated_height(Widget);
  gva::hmi::GetRendrer()->Configure(height, width);

  gtk_widget_set_size_request(gtk_.draw, width, height);
  gtk_widget_queue_draw(Widget);

  // We've handled the configure event, no need for further processing.
  return TRUE;
}

void GvaApplication::Activate(GtkApplication *app, gpointer user_data [[maybe_unused]]) {
  gtk_.win = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(gtk_.win), "HMI vivoe-lite");

  // Parse screensize gflag option : Default: 640x480
  std::string screenSizeStr = options_.screenSizeStr_;
  size_t delimiterPos = screenSizeStr.find('x');
    if (delimiterPos != std::string::npos) {
        std::string widthString = screenSizeStr.substr(0, delimiterPos);
        std::string heightString = screenSizeStr.substr(delimiterPos + 1);

        uint32_t width = std::atoi(widthString.c_str());
        uint32_t height = std::atoi(heightString.c_str());

        gva::kMinimumWidth = width;
        gva::kMinimumHeight = height;

        std::cout << "Width: " << width << std::endl;
        std::cout << "Height: " << height << std::endl;
    } else {
        LOG(ERROR) << "Invalid input format.";
        std::cout << "Invalid input format." << std::endl;
    }


  gtk_.draw = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(gtk_.win), gtk_.draw);
  // set a minimum size
  gtk_widget_set_size_request(gtk_.draw, gva::kMinimumWidth, gva::kMinimumHeight);
  gtk_window_set_default_size(GTK_WINDOW(gtk_.win), gva::kMinimumWidth, gva::kMinimumHeight);

  //
  // Event signals
  //
  g_signal_connect(gtk_.win, "destroy", G_CALLBACK(CloseWindow), NULL);
  g_signal_connect(gtk_.draw, "button-press-event", G_CALLBACK(gva::EventsGva::ButtonPressEventCb), NULL);
  g_signal_connect(gtk_.draw, "button-release-event", G_CALLBACK(gva::EventsGva::ButtonReleaseEventCb), NULL);
  g_signal_connect(gtk_.win, "key-press-event", G_CALLBACK(gva::EventsGva::KeyPressEventCb), NULL);
  g_signal_connect(gtk_.win, "key-release-event", G_CALLBACK(gva::EventsGva::KeyReleaseEventCb), NULL);

  // Ask to receive events the Drawing area doesn't normally
  // subscribe to. In particular, we need to ask for the
  // button press and motion notify events that want to handle.
  //
  gtk_widget_set_events(gtk_.draw, gtk_widget_get_events(gtk_.draw) | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK |
                                       GDK_POINTER_MOTION_MASK);

  //
  // Signals used to handle the backing surface
  //
  g_signal_connect(gtk_.draw, "draw", G_CALLBACK(DrawCb), NULL);
  g_signal_connect(gtk_.draw, "configure-event", G_CALLBACK(ConfigureEventCb), NULL);
  if (gva::ConfigData::GetInstance()->GetFullscreen()) gtk_window_fullscreen(GTK_WINDOW(gtk_.win));

  gtk_widget_show_all(gtk_.win);
}

gboolean GvaApplication::Callback(gpointer data) {
  Update(data);
  return TRUE;
}

GvaApplication::GvaApplication(const Options &options, const std::string &ipaddr, const uint32_t port) {
  options_ = options;

  // instantiate events
  gva::EventKeyPowerOn on;

  // Start the state machine
  gva::hmi::start();

  // Open window and start event loop and set inital state to 'on'
  gva::hmi::dispatch(on);

  //
  // Initialise the display events
  //
  io_ = std::make_shared<gva::EventsGva>(&gtk_, gva::hmi::GetRendrer()->GetTouch());
}

///
/// \brief Execute the main GTK application loop (blocking till windows destroyed)
///
///
void GvaApplication::Exec() const {
  gva::HandleType *renderer;

  // Draw the first screen, then the callback (Update) will refresh as required
  renderer = gva::hmi::GetRendrer()->Init(640, 480, gva::ConfigData::GetInstance()->GetFullscreen());

#if __MINGW64__ || __MINGW32__
  gtk_.app = gtk_application_new("org.gtk.vivoe-lite-hmi", G_APPLICATION_DEFAULT_FLAGS);
#else
  gtk_.app = gtk_application_new("org.gtk.vivoe-lite-hmi", G_APPLICATION_FLAGS_NONE);
#endif
  g_signal_connect(gtk_.app, "activate", G_CALLBACK(Activate), NULL);

  // This timer drives the display at 25 Htz (Wake every 40ms)
  g_timeout_add(40, Callback, renderer);

  //
  // Start the render and event loop
  //
  g_application_run(G_APPLICATION(gtk_.app), 0, nullptr);
  g_object_unref(gtk_.app);

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
  GdkRectangle workarea;

  if (render->fullscreen) {
    LOG(INFO) << "Un-fullscreen";
    gtk_window_unfullscreen(GTK_WINDOW(gtk_.win));
    gva::hmi::GetRendrer()->GetTouch()->SetResolution(gva::kMinimumWidth, gva::kMinimumHeight);
    gtk_window_resize(GTK_WINDOW(gtk_.win), gva::kMinimumWidth, gva::kMinimumHeight);
  } else {
    LOG(INFO) << "Switch to fullscreen";
    gtk_window_fullscreen(GTK_WINDOW(gtk_.win));
    if (GdkMonitor *monitor = gdk_display_get_primary_monitor(gdk_display_get_default()); monitor) {
      gdk_monitor_get_workarea(monitor, &workarea);
      LOG(INFO) << "Switching resolution to " + std::to_string(workarea.width) + "x" + std::to_string(workarea.height);

      gva::hmi::GetRendrer()->GetTouch()->SetResolution(workarea.width, workarea.height);
    } else {
      LOG(ERROR) << "gdk_monitor_get_workarea failed when switching to fullscreen.";
    }
  }

  render->fullscreen = render->fullscreen ? false : true;
  gva::ConfigData::GetInstance()->SetFullscreen(render->fullscreen);

  gva::EventsGva::CreateRefreshEvent();
}

bool GvaApplication::SetKeyPressed(gva::GvaKeyEnum key) {
  switch (key) {
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
    // No an active touch zone so just reset everything
    default:
      return false;
  }
  return true;
}

void GvaApplication::BrightnessUp() {
  BrightnessAdjust(0.05);  // 5% down
}

void GvaApplication::BrightnessDown() {
  BrightnessAdjust(-0.05);  // 5% down
}

bool GvaApplication::ProcessTopKeys(gva::HandleType *render, gva::GvaKeyEnum key) {
  // Bezel Top Keys
  switch (key) {
    case gva::GvaKeyEnum::kKeyEscape:
      // exit on ESC key press
      if (render->surface) cairo_surface_destroy(render->surface);
      g_application_quit(G_APPLICATION(gtk_.app));
      return true;
    case gva::GvaKeyEnum::kKeyBlackout:
      Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeySituationalAwareness:
      // 1 maps to F1
      gva::hmi::dispatch(gva::EventKeySA());
      return true;
    case gva::GvaKeyEnum::kKeyWeapon:
      // 2 maps to F2
      gva::hmi::dispatch(gva::EventKeyWPN());
      return true;
    case gva::GvaKeyEnum::kKeyDefensiveSystems:
      // 3 maps to F3
      gva::hmi::dispatch(gva::EventKeyDEF());
      return true;
    case gva::GvaKeyEnum::kKeySystems:
      // 4 maps to F4
      gva::hmi::dispatch(gva::EventKeySYS());
      return true;
    case gva::GvaKeyEnum::kKeyDriver:
      // 5 maps to F5
      gva::hmi::dispatch(gva::EventKeyDRV());
      return true;
    case gva::GvaKeyEnum::kKeySpecialToRole:
      // 6 maps to F6
      gva::hmi::dispatch(gva::EventKeySTR());
      return true;
    case gva::GvaKeyEnum::kKeyCommunications:
      // 7 maps to F7
      gva::hmi::dispatch(gva::EventKeyCOM());
      return true;
    case gva::GvaKeyEnum::kKeyBattlefieldManagementSystem:
      // 8 maps to F8
      gva::hmi::dispatch(gva::EventKeyBMS());
      return true;
    default:
      break;
  }
  return false;
}

bool GvaApplication::ProcessFunctionKeys(gva::WidgetKeyboard *keyboard, gva::GvaKeyEnum key) {
  // Bezel All Other  Keys
  switch (key) {
    case gva::GvaKeyEnum::kKeyF1:
      if (gva::hmi::GetScreen()->function_left.Active(0)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF2:
      if (gva::hmi::GetScreen()->function_left.Active(1)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF3:
      if (gva::hmi::GetScreen()->function_left.Active(2)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF4:
      if (gva::hmi::GetScreen()->function_left.Active(3)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF5:
      if (gva::hmi::GetScreen()->function_left.Active(4)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF6:
      if (gva::hmi::GetScreen()->function_left.Active(5)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF7:
      if (gva::hmi::GetScreen()->function_right.Active(0)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF8:
      if (gva::hmi::GetScreen()->function_right.Active(1)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF9:
      if (gva::hmi::GetScreen()->function_right.Active(2)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF10:
      if (gva::hmi::GetScreen()->function_right.Active(3)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF11:
      if (gva::hmi::GetScreen()->function_right.Active(4)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF12:
      if (gva::hmi::GetScreen()->function_right.Active(5)) Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF13:
      return true;
    case gva::GvaKeyEnum::kKeyF14:
      // Control Alarms
      gva::hmi::dispatch(gva::EventKeyAlarms());
      Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF17:
      // F17 Control Arrow Up
      keyboard->SetMode((keyboard->GetMode() == gva::widget::KeyboardModeType::kKeyboardUpper)
                            ? gva::widget::KeyboardModeType::kKeyboardLower
                            : gva::widget::KeyboardModeType::kKeyboardUpper);
      Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF18:
      // F18 Control Arrow Down
      keyboard->SetMode((keyboard->GetMode() == gva::widget::KeyboardModeType::kKeyboardNumbers)
                            ? gva::widget::KeyboardModeType::kKeyboardUpper
                            : gva::widget::KeyboardModeType::kKeyboardNumbers);
      Dispatch(key);
      return true;
    case gva::GvaKeyEnum::kKeyF16:
    case gva::GvaKeyEnum::kKeyF15:
    case gva::GvaKeyEnum::kKeyF19:
    case gva::GvaKeyEnum::kKeyF20:
      Dispatch(key);
      return true;
    default:
      break;
  }
  return false;
}

void GvaApplication::BrightnessAdjust(double value) {
  double brightness = gva::ConfigData::GetInstance()->GetBrightness();
  brightness = brightness + value;
  if ((value > 0) && (brightness > 1)) brightness = 1;
  if ((value < 0) && (brightness < 0)) brightness = 0;
  gva::SetBrightness(brightness);
  gva::ConfigData::GetInstance()->SetBrightness(brightness);
}

void GvaApplication::ScreenSizeSet(std::string value) {
  """ Get screensize and set it in the proto """
  std::string screenSizeStr = gva::ConfigData::GetInstance()->GetBrightness();
  gva::ConfigData::GetInstance()->SetScreenSize(screenSizeStr);
}


bool GvaApplication::SetKeyReleased(gva::HandleType *render, gva::GvaKeyEnum key) {
  auto *compass = static_cast<gva::WidgetPlanPositionIndicator *>(
      gva::hmi::GetRendrer()->GetWidget(gva::widget::WidgetEnum::KWidgetTypeCompass));

  auto keyboard =
      (gva::WidgetKeyboard *)gva::hmi::GetRendrer()->GetWidget(gva::widget::WidgetEnum::KWidgetTypeKeyboard);

  LOG(INFO) << "[GVA] Key release event being processed value=" << std::to_string(int(key));

  gva::EventsGva::CreateRefreshEvent();

  // Process top bezel keys
  if (ProcessTopKeys(render, key)) return true;

  // Non Function keys
  if (ProcessFunctionKeys(keyboard, key)) return true;

  // Non Bezel keys
  switch (key) {
    case gva::GvaKeyEnum::kKeyFullscreen:
      // m|M toggle fullscreen
      Fullscreen(render);
      return true;
    case gva::GvaKeyEnum::kKeyKeyboard:
      // k toggle keyboard
      keyboard->SetVisible(keyboard->GetVisible() ? false : true);
      return true;
    case gva::GvaKeyEnum::kKeyPlus:
      compass->SetBearing(gva::DegreesAdd(compass->GetBearing(), 2));
      return true;
    case gva::GvaKeyEnum::kKeyGreaterThan:
      compass->SetBearingSight(gva::DegreesAdd(compass->GetBearingSight(), 2));
      return true;
    case gva::GvaKeyEnum::kKeyMinus:
      compass->SetBearing(gva::DegreesSubtract(compass->GetBearing(), 2));
      return true;
    case gva::GvaKeyEnum::kKeyLessThen:
      compass->SetBearingSight(gva::DegreesSubtract(compass->GetBearingSight(), 2));
      return true;
    case gva::GvaKeyEnum::kKeyRightArrow:
      BrightnessDown();
      return true;
    case gva::GvaKeyEnum::kKeyLeftArrow:
      BrightnessUp();
      return true;
    case gva::GvaKeyEnum::kKeyNextLabel:
    case gva::GvaKeyEnum::kKeyPreviousLabel:
      Dispatch(key);
      return true;
    default:
      LOG(INFO) << "[GVA] Key release not defined " + std::to_string(int(key));
      // When we have wondered off a hotspot we need to reset and changing labels.
      gva::hmi::GetScreen()->function_left.ResetAllEnabledSelectedChanging();
      gva::hmi::GetScreen()->function_right.ResetAllEnabledSelectedChanging();
      gva::hmi::GetScreen()->function_top->ResetAllEnabledSelectedChanging();
      gva::hmi::GetScreen()->control->ResetAllEnabledSelectedChanging();
      Dispatch(key);  // Dispatch it anyway as this will clear any existing changing states
      return false;
  }
  return true;
}

///
/// \brief Renderer callback to update screen
///
/// \param user_data Renderer handle
///
void GvaApplication::Update(gpointer user_data) {
  gva::EventGvaType event;
  bool update = true;
  auto *render = static_cast<gva::HandleType *>(user_data);

  io_->NextGvaEvent(&event);

  // Time to update the screen
  if (first_execution_ || (event.type_ == gva::EventEnumType::kWidgetUpdate)) {
    gva::hmi::GetRendrer()->Update();
    first_execution_ = false;
    return;
  }

  switch (event.type_) {
    default:
      break;
    case gva::EventEnumType::kKeyEventPressed:
      LOG(INFO) << "Key press event being processed value=" << std::to_string(int(event.key_));
      update = SetKeyPressed(event.key_);
      break;
    case gva::EventEnumType::kKeyEventReleased:
      update = SetKeyReleased(render, event.key_);
      break;
    case gva::EventEnumType::kResizeEvent: {
      if (event.resize_.width != gva::hmi::GetRendrer()->GetWidth() ||
          event.resize_.height != gva::hmi::GetRendrer()->GetHeight()) {
        LOG(INFO) << "WindowResize: " << event.resize_.width << "x" << event.resize_.height << "\n";
        gva::hmi::GetRendrer()->SetWidth(event.resize_.width);
        gva::hmi::GetRendrer()->SetHeight(event.resize_.height);
        gva::hmi::GetRendrer()->GetTouch()->SetResolution(event.resize_.width, event.resize_.height);
        update = true;
      }
    } break;
    case gva::EventEnumType::kRedrawEvent: {
      update = true;
    } break;
    case gva::EventEnumType::kNoEvent:
      // No events found, lets update anyway
      update = true;
      break;
  }

  // Only update if a change was detected
  if (update) {
    gva::hmi::GetRendrer()->Update();
  }

}  // namespace gva
