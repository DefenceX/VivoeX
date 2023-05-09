//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file sys.cc
///

#include "bms.h"
#include "hmidisplay/gva_application.h"

namespace gva {

GvaKeyEnum Hmi::KeySYS(GvaKeyEnum keypress) {
  screen_.function_left.visible = true;
  screen_.function_right.visible = true;
  auto table = (WidgetTable *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable);

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
      HmiHelper::TableSystem(table);
      break;
    case GvaKeyEnum::kKeyF5:
      HmiHelper::TableLicences(table);
      break;
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
      screen_.message.visible = true;
      screen_.message.icon = widget::IconType::kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
    case GvaKeyEnum::kKeyF11:
      // Blackout
      screen_.info.mode =
          (screen_.info.mode == ScreenMode::kModeBlackout) ? ScreenMode::kModeOperational : ScreenMode::kModeBlackout;
      screen_.canvas.visible = true;
      if (screen_.info.mode == ScreenMode::kModeBlackout)
        screen_.canvas.blackout = true;
      else
        screen_.canvas.blackout = false;
      break;
    case GvaKeyEnum::kKeyF12:
      // Exit
      if (RendererCairo::render_.surface) cairo_surface_destroy(RendererCairo::render_.surface);
      g_application_quit(G_APPLICATION(GvaApplication::gtk_.app));
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

void StateSYS::entry() {
  DLOG(INFO) << "Entering the SYS State";

  if (screen_.function_top->labels[3].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kSystems);
    lastState_ = GvaFunctionEnum::kSystems;
    Reset();
    screen_.function_top->SetEnabled(3);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
    screen_.function_top->labels[3].state = LabelStates::kLabelEnabledSelected;

    auto table = (WidgetTable *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTable);
    HmiHelper::TableSystem(table);
  }
};

void StateSYS::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateSYS::react(EventKeySA const &) { transit<StateSA>(); };

void StateSYS::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateSYS::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateSYS::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateSYS::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateSYS::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateSYS::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateSYS::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateSYS::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateSYS::react(EventKeyFunction const &e) {
  DLOG(INFO) << "Entering the SYS State";

  KeySYS(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateDEF>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateDRV>();
};

}  // namespace gva
