//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
/// \file drv.cc
///

#include "drv.h"

#include <colourspace.h>

#include "hmicore/widgets/driver/rpm_fuel.h"
#include "hmicore/widgets/driver/speedometer.h"

namespace gva {

StateDRV::StateDRV() {
  canvas_ = (gva::WidgetCanvas *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCanvas));
  RtpvrawDepayloader::RtpvrawDepayloaderIn("DemoVideo1", ColourspaceType::kColourspaceYuv, 640, 480, "239.192.1.1",
                                           5004);
}

void StateDRV::UpdateVideo() {
  uint8_t *cpu_buffer;
  if (drivers_feed_.Receive(&cpu_buffer, 80) == true) {
    if (gva::hmi::GetScreen()->currentFunction == gva::GvaFunctionEnum::kDriver) {
      gva::hmi::GetScreen()->canvas.surface =
          cairo_image_surface_create(CAIRO_FORMAT_ARGB32, gva::kMinimumWidth, gva::kMinimumHeight);
      auto test = (uint8_t *)(cairo_image_surface_get_data(gva::hmi::GetScreen()->canvas.surface));
      video::YuvToRgba(480, 640, cpu_buffer, test);
      cairo_surface_mark_dirty(gva::hmi::GetScreen()->canvas.surface);
      canvas_->SetSurface(gva::hmi::GetScreen()->canvas.surface);
    }
  }
}

GvaKeyEnum Hmi::KeyDRV(GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = widget::IconType::kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
    default:  // LotsThe state machine for of keys we dont care about
      break;
  }
  return keypress;
}

void StateDRV::entry() {
  if (screen_.function_top->labels[4].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kDriver);
    Reset();
    lastState_ = GvaFunctionEnum::kDriver;
    if (screen_.labels != LabelModeEnum::kLabelMinimal)
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);

    screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetVisible(true);
    screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetX(320);
    screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetY(750);

    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetVisible(true);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetX(950);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetY(750);

    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeStatusBar)->SetVisible(true);
    screen_.function_top->SetEnabled(4);

    // Start the video stream receiver
    drivers_feed_.Start();
  }
};

void StateDRV::exit() {
  // Switch the dials off now not needed in other states
  screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetVisible(false);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetVisible(false);
  // Stop the video stream receiver, easy to restart. Stream still running
  drivers_feed_.Stop();
}

void StateDRV::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateDRV::react(EventKeySA const &) { transit<StateSA>(); };

void StateDRV::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateDRV::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateDRV::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateDRV::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateDRV::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateDRV::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateDRV::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateDRV::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateDRV::react(EventKeyFunction const &e) {
  KeyDRV(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSYS>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateSTR>();
};

}  // namespace gva
