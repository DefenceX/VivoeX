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
/// \brief Driver (DRV) state definition
///
/// \file drv.cc
///

#include "drv.h"

#include "src/widgets/driver/rpm_fuel.h"
#include "src/widgets/driver/speedometer.h"

namespace gva {

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
    WidgetDriverSpeedometer *dial =
        (WidgetDriverSpeedometer *)screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer);
    dial->SetValue(10);

    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetVisible(true);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetX(950);
    screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetY(750);
    WidgetDriverRpmFuel *rpm =
        (WidgetDriverRpmFuel *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel);
    rpm->SetValue(1200);
    screen_.status_bar->visible = true;
    screen_.function_top->SetEnabled(4);
  }
};

void StateDRV::exit() {
  // Switch the dials off now not needed in other states
  screen_render_->GetWidget(widget::WidgetEnum::kWidgetTypeDialSpeedometer)->SetVisible(false);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeDialRpmFuel)->SetVisible(false);
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
