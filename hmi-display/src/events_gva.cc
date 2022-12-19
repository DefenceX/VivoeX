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

gboolean EventsGva::CreateKeyEvent(GtkWidget* Widget, GdkEventKey* event, EventEnumType type) {
  EventGvaType gvaEvent;
  gvaEvent.type_ = type;
  gvaEvent.key_ = GvaKeyEnum::kKeyUnknown;

  std::string state = (EventEnumType::kKeyEventPressed == type) ? "(Pressed) " : "(Released) ";
  logGva::log("[GVA] Key press event " + state + std::to_string(event->keyval) + " (prev " +
                  std::to_string(previous_key_) + ")",
              DebugLevel::kLogInfo);

  // The event was handled, and the emission should stop
  if (event->keyval == 65307) {
    // exit on ESC key press
    gvaEvent.key_ = GvaKeyEnum::kKeyEscape;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyBlackout)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyBlackout;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeySituationalAwareness)) {
    gvaEvent.key_ = GvaKeyEnum::kKeySituationalAwareness;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyWeapon)) {
    // 2 maps to WPN
    gvaEvent.key_ = GvaKeyEnum::kKeyWeapon;
  }
  // 1 maps to SA
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
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF13)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF13;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF14)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF14;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF15)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF15;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF16)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF16;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF17)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF17;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF18)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF18;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF19)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF19;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyF20)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF20;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyUpArrow)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF18;
  }
  if (event->keyval == ConfigData::GetInstance()->GetKeyBinding(GvaKeyEnum::kKeyDownArrow)) {
    gvaEvent.key_ = GvaKeyEnum::kKeyF17;
  }
  if ((event->keyval == 'm') || (event->keyval == 'M')) {
    // m toggle fullscreen
    gvaEvent.key_ = GvaKeyEnum::kKeyFullscreen;
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
  if ((event->keyval == 'p') || (event->keyval == 'P')) {
    //[p|P] Move to previous label
    gvaEvent.key_ = GvaKeyEnum::kKeyPreviousLabel;
  }
  if ((event->keyval == 'n') || (event->keyval == 'N')) {
    //[n|N] Move to next label
    gvaEvent.key_ = GvaKeyEnum::kKeyNextLabel;
  }
  if (event->keyval != 0) {
    if (gvaEvent.type_ != EventEnumType::kNoEvent) eventqueue_.push_back(gvaEvent);
  }

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
