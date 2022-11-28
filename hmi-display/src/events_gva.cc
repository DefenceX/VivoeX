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
/// \file events_gva.cpp
///

#include "events_gva.h"

#include "common/log_gva.h"
#include "src/gva.h"
#include "src/renderer_gva.h"

namespace gva {

static uint32_t previous_key_;

EventsGva::EventsGva(gtkType* window, TouchGva* touch) {
  window_ = window;
  touch_ = touch;
  previous_key_ = 0;
}

// Handle button press events by either Drawing a rectangle
// or clearing the surface, depending on which button was pressed.
// The ::button-press signal handler receives a GdkEventButton
// struct which contains this information.
gboolean EventsGva::ButtonPressEventCb(GtkWidget* Widget, GdkEventButton* event, gpointer data) {
  EventGvaType gvaEvent;
  uint32_t binding = 0;

  touch_->Check(GvaFunctionGroupEnum::kTop, &binding, event->x, event->y);
  if (!binding) touch_->Check(GvaFunctionGroupEnum::kBottom, &binding, event->x, event->y);
  if (!binding) touch_->Check(GvaFunctionGroupEnum::kRight, &binding, event->x, event->y);
  if (!binding) touch_->Check(GvaFunctionGroupEnum::kLeft, &binding, event->x, event->y);
  if (binding) {
    gvaEvent.type_ = kKeyEventPressed;
    gvaEvent.key_ = (GvaKeyEnum)binding;
    eventqueue_.push_back(gvaEvent);

    logGva::log("[GVA] Button press event " + std::to_string(event->button), LOG_INFO);
  }

  // We've handled the event, stop processing
  return TRUE;
}

gboolean EventsGva::ButtonReleaseEventCb(GtkWidget* Widget, GdkEventButton* event, gpointer data) {
  if (event->button == GDK_BUTTON_PRIMARY) {
    EventGvaType gvaEvent;
    uint32_t binding = 0;

    touch_->Check(GvaFunctionGroupEnum::kTop, &binding, event->x, event->y);
    if (!binding) touch_->Check(GvaFunctionGroupEnum::kBottom, &binding, event->x, event->y);
    if (!binding) touch_->Check(GvaFunctionGroupEnum::kRight, &binding, event->x, event->y);
    if (!binding) touch_->Check(GvaFunctionGroupEnum::kLeft, &binding, event->x, event->y);
    if (binding) {
      gvaEvent.type_ = EventEnumType::kKeyEventReleased;
      gvaEvent.key_ = (GvaKeyEnum)binding;
      eventqueue_.push_back(gvaEvent);
    } else {
      // Not an active hotspot so cant set key but event still happened.
      gvaEvent.type_ = EventEnumType::kKeyEventReleased;
      gvaEvent.key_ = GvaKeyEnum::kKeyUnknown;
      eventqueue_.push_back(gvaEvent);
    }
    logGva::log("[GVA] Button release event " + std::to_string(event->button), LOG_INFO);
  }

  // We've handled the event, stop processing
  return TRUE;
}

gboolean EventsGva::KeyPressEventCb(GtkWidget* Widget, GdkEventKey* event) {
  return CreateKeyEvent(Widget, event, EventEnumType::kKeyEventPressed);
}

gboolean EventsGva::KeyReleaseEventCb(GtkWidget* Widget, GdkEventKey* event) {
  return CreateKeyEvent(Widget, event, EventEnumType::kKeyEventReleased);
}

gboolean EventsGva::CreateKeyEvent(GtkWidget* Widget, GdkEventKey* event, EventEnumType type) {
  GdkModifierType modifiers;
  EventGvaType gvaEvent;
  gvaEvent.type_ = type;

  modifiers = gtk_accelerator_get_default_mod_mask();
  std::string state = (EventEnumType::kKeyEventPressed == type) ? "(Pressed) " : "(Released) ";
  logGva::log("[GVA] Key press event " + state + std::to_string(event->keyval) + " (prev " +
                  std::to_string(previous_key_) + ")",
              LOG_INFO);
  switch (previous_key_) {
    case 0xffe3:  // Top keys
      switch (event->keyval) {
        case 0xffbe:
          /* 1 maps to SA */
          gvaEvent.key_ = GvaKeyEnum::KKeySituationalAwareness;
          break;
        case 0xffbf:
          /* 2 maps to WPN */
          gvaEvent.key_ = GvaKeyEnum::kKeyWeapon;
          break;
        case 0xffc0:
          /* 3 maps to DEF */
          gvaEvent.key_ = GvaKeyEnum::kKeyDefensiveSystems;
          break;
        case 0xffc1:
          /* 4 maps to SYS */
          gvaEvent.key_ = GvaKeyEnum::kKeySystems;
          break;
        case 0xffc2:
          /* 5 maps to DRV */
          gvaEvent.key_ = GvaKeyEnum::kKeyDriver;
          break;
        case 0xffc3:
          /* 6 maps to STR */
          gvaEvent.key_ = GvaKeyEnum::kKeySpecialToRole;
          break;
        case 0xffc4:
          /* 7 maps to >>>COM */
          gvaEvent.key_ = GvaKeyEnum::kKeyCommunications;
          break;
        case 0xffc5:
          /* 8 maps to BMS */
          gvaEvent.key_ = GvaKeyEnum::kKeyBattlefieldManagementSystem;
          break;
        default:
          break;
      }
      printf("[GVA] Top event 0x%x\n", event->keyval);
      previous_key_ = event->keyval;
      if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
      return TRUE;
      break;
    case 0xffe9:  // Bottom keys
      switch (event->keyval) {
        case 97:
        case 0xffbe:
          /* a maps to F13 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF13;
          break;
        case 0xffbf:
          /* a maps to F14 (ALARMS) */
          gvaEvent.key_ = GvaKeyEnum::kKeyF14;
          break;
        case 0xffc0:
          /* Enter maps to F15 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF15;
          break;
        case 0xffc1:
          /* Enter maps to F16 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF16;
          break;
        case 0xffc2:
          /* Enter maps to F17 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF17;
          break;
        case 0xffc3:
          /* Enter maps to F18 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF18;
          break;
        case 0xffc4:
          /* Enter maps to F19 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF19;
          break;
        case 0xffc5:
          /* Enter maps to F20 */
          gvaEvent.key_ = GvaKeyEnum::kKeyF20;
          break;
      }
      printf("[GVA] Bottom event 0x%x\n", event->keyval);
      previous_key_ = event->keyval;
      if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
      return TRUE;
  }
  //    g_print ("send_event=%d, state=%u, keyval=%u, length=%d, string='%s',
  //    hardware_keycode=%u, group=%u\n", gvaEvent.send_event, gvaEvent.state,
  //    gvaEvent.keyval, gvaEvent.length, gvaEvent.string,
  //    gvaEvent.hardware_keycode, gvaEvent.group);
  /* The event was handled, and the emission should stop */
  switch (event->keyval) {
    case 65307:
      /* exit on ESC key press */
      gvaEvent.key_ = GvaKeyEnum::kKeyEscape;
      break;
    case 49:
      /* 1 maps to SA */
      gvaEvent.key_ = GvaKeyEnum::KKeySituationalAwareness;
      break;
    case 50:
      /* 2 maps to WPN */
      gvaEvent.key_ = GvaKeyEnum::kKeyWeapon;
      break;
    case 51:
      /* 3 maps to DEF */
      gvaEvent.key_ = GvaKeyEnum::kKeyDefensiveSystems;
      break;
    case 52:
      /* 4 maps to SYS */
      gvaEvent.key_ = GvaKeyEnum::kKeySystems;
      break;
    case 53:
      /* 5 maps to DRV */
      gvaEvent.key_ = GvaKeyEnum::kKeyDriver;
      break;
    case 54:
      /* 6 maps to STR */
      gvaEvent.key_ = GvaKeyEnum::kKeySpecialToRole;
      break;
    case 55:
      /* 7 maps to COM */
      gvaEvent.key_ = GvaKeyEnum::kKeyCommunications;
      break;
    case 56:
      /* 8 maps to BMS */
      gvaEvent.key_ = GvaKeyEnum::kKeyBattlefieldManagementSystem;
      break;
    case 0xffbe:
      /* F1 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF1;
      break;
    case 0xffbf:
      /* F2 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF2;
      break;
    case 0xffc0:
      /* F3 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF3;
      break;
    case 0xffc1:
      /* F4 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF4;
      break;
    case 0xffc2:
      /* F5 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF5;
      break;
    case 0xffc3:
      /* F6 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF6;
      break;
    case 0xffc4:
      /* F7 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF7;
      break;
    case 0xffc5:
      /* F8 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF8;
      break;
    case 0xffc6:
      /* F9 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF9;
      break;
    case 0xffc7:
      /* F10 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF10;
      break;
    case 0xffc8:
      /* F11 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF11;
      break;
    case 0xffc9:
      /* F12 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF12;
      break;
      //      case 65:
    case 70:
    case 102:
      /* f toggle fullscreen TODO: Does not work */
      gvaEvent.key_ = GvaKeyEnum::kKeyFullscreen;
      break;
    case 0x62:
      /* b toggle blackout F11 */
      gvaEvent.key_ = GvaKeyEnum::kKeyF11;
      break;
    case 75:
    case 107:
      /* k toggle keyboard */
      gvaEvent.key_ = GvaKeyEnum::kKeyKeyboard;
      break;
    case 65509:
      /* caps_lock keyboard */
      gvaEvent.key_ = GvaKeyEnum::kKeyF17;
      break;
    case 65407:
      /* num_lock keyboard */
      gvaEvent.key_ = GvaKeyEnum::kKeyF18;
      break;
    case 76:
    case 108:
      /* l or L show / hide labels */
      gvaEvent.key_ = GvaKeyEnum::kKeyF19;
      break;
    case 43:
      /* + keyboard */
      gvaEvent.key_ = GvaKeyEnum::kKeyPlus;
      break;
    case 95:
      /* - show / hide labels */
      gvaEvent.key_ = GvaKeyEnum::kKeyMinus;
      break;
    case 62:
      /* > keyboard */
      gvaEvent.key_ = GvaKeyEnum::kKeyRightArrow;
      break;
    case 60:
      /* < show / hide labels */
      gvaEvent.key_ = GvaKeyEnum::kKeyLeftArrow;
      break;
    case 0x41:
    case 0x61:
      /* [a|A] Move to previous label */
      gvaEvent.key_ = GvaKeyEnum::kKeyF14;
      break;
    case 0x50:
    case 0x70:
      /* [p|P] Move to previous label */
      gvaEvent.key_ = GvaKeyEnum::kKeyPreviousLabel;
      break;
    case 0x4e:
    case 0x6e:
      /* [n|N] Move to next label */
      gvaEvent.key_ = GvaKeyEnum::kKeyNextLabel;
      break;

    default:
      gva::logGva::log("[GVA] KeyPress not defined " + std::to_string(int(gvaEvent.key_)), gva::LOG_INFO);
      previous_key_ = event->keyval;
      return TRUE;
  }
  if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
  return TRUE;
}

GvaStatusTypes EventsGva::NextGvaEvent(EventGvaType* event) {
  EventGvaType popEvent;

  popEvent.type_ == EventEnumType::kNoEvent;
  if (!eventqueue_.empty()) {
    popEvent = eventqueue_.back();
    eventqueue_.pop_back();
  }
  *event = popEvent;
  return GvaStatusTypes::kGvaSuccess;
}

}  // namespace gva
