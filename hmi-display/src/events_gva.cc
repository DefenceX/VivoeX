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
///
/// \file events_gva.cpp
///

#include "events_gva.h"

#include "common/log_gva.h"
#include "src/gva.h"
#include "src/renderer_gva.h"

namespace gva {

static uint32_t previous_key_;
static TouchGva* touch_;

std::vector<EventGvaType> EventsGva::eventqueue_;

EventsGva::EventsGva(gtkType* window, TouchGva* touch) : window_(window) {
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
    gvaEvent.type_ = EventEnumType::kKeyEventPressed;
    gvaEvent.key_ = (GvaKeyEnum)binding;
    eventqueue_.push_back(gvaEvent);

    logGva::log("[GVA] Button press event " + std::to_string(event->button), DebugLevel::kLogInfo);
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
    logGva::log("[GVA] Button release event " + std::to_string(event->button), DebugLevel::kLogInfo);
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

GvaKeyEnum ProcessTopKeys(uint32_t keyval) {
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeySituationalAwareness))
    return GvaKeyEnum::kKeySituationalAwareness;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyWeapon))
    return GvaKeyEnum::kKeySituationalAwareness;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF15)) return GvaKeyEnum::kKeyWeapon;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF16)) return GvaKeyEnum::kKeyDefensiveSystems;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF17)) return GvaKeyEnum::kKeySystems;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF18)) return GvaKeyEnum::kKeyDriver;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF19)) return GvaKeyEnum::kKeySpecialToRole;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF20)) return GvaKeyEnum::kKeyCommunications;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF20))
    return GvaKeyEnum::kKeyBattlefieldManagementSystem;
  return GvaKeyEnum::kKeyUnknown;
}

GvaKeyEnum ProcessBottonKeys(uint32_t keyval) {
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF13)) return GvaKeyEnum::kKeyF13;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF14)) return GvaKeyEnum::kKeyF14;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF15)) return GvaKeyEnum::kKeyF15;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF16)) return GvaKeyEnum::kKeyF16;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF17)) return GvaKeyEnum::kKeyF17;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF18)) return GvaKeyEnum::kKeyF18;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF19)) return GvaKeyEnum::kKeyF19;
  if (keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF20)) return GvaKeyEnum::kKeyF20;
  return GvaKeyEnum::kKeyUnknown;
}

gboolean EventsGva::CreateKeyEvent(GtkWidget* Widget, GdkEventKey* event, EventEnumType type) {
  EventGvaType gvaEvent;
  gvaEvent.type_ = type;

  std::string state = (EventEnumType::kKeyEventPressed == type) ? "(Pressed) " : "(Released) ";
  logGva::log("[GVA] Key press event " + state + std::to_string(event->keyval) + " (prev " +
                  std::to_string(previous_key_) + ")",
              DebugLevel::kLogInfo);
  switch (previous_key_) {
    case 0xffe3:  // Top keys
      gvaEvent.key_ = ProcessTopKeys(event->keyval);
      printf("[GVA] Top event 0x%x\n", event->keyval);
      previous_key_ = event->keyval;
      if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
      return TRUE;
    case 0xffe9:  // Bottom keys
      gvaEvent.key_ = ProcessBottonKeys(event->keyval);
      printf("[GVA] Bottom event 0x%x\n", event->keyval);
      previous_key_ = event->keyval;
      if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
      return TRUE;
  }

  // The event was handled, and the emission should stop
  if (event->keyval == 65307) {
    // exit on ESC key press
    gvaEvent.key_ = GvaKeyEnum::kKeyEscape;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeySituationalAwareness)) {
    // 1 maps to SA
    gvaEvent.key_ = GvaKeyEnum::kKeySituationalAwareness;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyWeapon)) {
    // 2 maps to WPN
    gvaEvent.key_ = GvaKeyEnum::kKeyWeapon;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyDefensiveSystems)) {
    // 3 maps to DEF
    gvaEvent.key_ = GvaKeyEnum::kKeyDefensiveSystems;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeySystems)) {
    // 4 maps to SYS
    gvaEvent.key_ = GvaKeyEnum::kKeySystems;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyDriver)) {
    // 5 maps to DRV
    gvaEvent.key_ = GvaKeyEnum::kKeyDriver;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeySpecialToRole)) {
    // 6 maps to STR
    gvaEvent.key_ = GvaKeyEnum::kKeySpecialToRole;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyCommunications)) {
    // 7 maps to COM
    gvaEvent.key_ = GvaKeyEnum::kKeyCommunications;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyBattlefieldManagementSystem)) {
    // 8 maps to BMS
    gvaEvent.key_ = GvaKeyEnum::kKeyBattlefieldManagementSystem;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF1)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF1;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF2)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF2;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF3)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF3;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF4)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF4;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF5)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF5;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF6)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF6;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF7)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF7;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF8)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF8;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF9)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF9;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF10)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF10;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF11)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF11;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF12)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF12;
  }
  if ((event->keyval == 70) || (event->keyval == 102)) {
    // f toggle fullscreen TODO: Does not work
    gvaEvent.key_ = GvaKeyEnum::kKeyFullscreen;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyBlackout)) {
    // b toggle blackout F11
    gvaEvent.key_ = GvaKeyEnum::kKeyF11;
  }
  if ((event->keyval == 75) || (event->keyval == 107)) {
    // k toggle keyboard
    gvaEvent.key_ = GvaKeyEnum::kKeyKeyboard;
  }
  if (event->keyval == 65509) {
    // caps_lock keyboard
    gvaEvent.key_ = GvaKeyEnum::kKeyF17;
  }
  if (event->keyval == 65407) {
    // num_lock keyboard
    gvaEvent.key_ = GvaKeyEnum::kKeyF18;
  }
  if ((event->keyval == 76) || (event->keyval == 108)) {
    // l or L show / hide labels
    gvaEvent.key_ = GvaKeyEnum::kKeyF19;
  }
  if (event->keyval == 43) {
    //+ keyboard
    gvaEvent.key_ = GvaKeyEnum::kKeyPlus;
  }
  if (event->keyval == 95) {
    //- show / hide labels
    gvaEvent.key_ = GvaKeyEnum::kKeyMinus;
  }
  if (event->keyval == 62) {
    //> keyboard
    gvaEvent.key_ = GvaKeyEnum::kKeyRightArrow;
  }
  if (event->keyval == 60) {
    //< show / hide labels
    gvaEvent.key_ = GvaKeyEnum::kKeyLeftArrow;
  }
  if ((event->keyval == 'a') || (event->keyval == 'A')) {
    //[a|A] Move to previous label
    gvaEvent.key_ = GvaKeyEnum::kKeyF14;
  }
  if ((event->keyval == 'p') || (event->keyval == 'P')) {
    //[p|P] Move to previous label
    gvaEvent.key_ = GvaKeyEnum::kKeyPreviousLabel;
  }
  if ((event->keyval == 'n') || (event->keyval == 'N')) {
    //[n|N] Move to next label
    gvaEvent.key_ = GvaKeyEnum::kKeyNextLabel;
  }

  if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
  return TRUE;
}

GvaStatusTypes EventsGva::NextGvaEvent(EventGvaType* event) {
  EventGvaType popEvent;

  popEvent.type_ = EventEnumType::kNoEvent;
  if (!eventqueue_.empty()) {
    popEvent = eventqueue_.back();
    eventqueue_.pop_back();
  }
  *event = popEvent;
  return GvaStatusTypes::kGvaSuccess;
}

}  // namespace gva
