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
/// \brief Situational Awareness (SA) state definition
///
/// \file sa.cc
///

#include "sa.h"

namespace gva {

GvaKeyEnum Hmi::KeySA(GvaKeyEnum keypress) {
  const std::string path = ConfigData::GetInstance()->GetImagePath();
  std::string filename;

  screen_.function_left.visible = true;
  for (auto &label : screen_.function_left.labels) {
    if (label.state == LabelStates::kLabelEnabledSelected) label.state = LabelStates::kLabelEnabled;
  }
  screen_.function_right.visible = true;
  for (auto &label : screen_.function_right.labels) {
    if (label.state == LabelStates::kLabelEnabledSelected) label.state = LabelStates::kLabelEnabled;
  }

  gva::WidgetPlanPositionIndicator *compass =
      static_cast<WidgetPlanPositionIndicator *>(screen_render_->GetWidget(KWidgetTypeCompass));

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF2:
      filename = path;
      filename.append("/Quad.png");
      SetCanvasPng(filename);
      break;
    case GvaKeyEnum::kKeyF4:
      filename = path;
      filename.append("/FrontRight.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(45);
      break;
    case GvaKeyEnum::kKeyF5:
      filename = path;
      filename.append("/FrontCenter.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(0);
      break;
    case GvaKeyEnum::kKeyF6:
      filename = path;
      filename.append("/FrontLeft.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(315);
      break;
    case GvaKeyEnum::kKeyF10:
      filename = path;
      filename.append("/Right.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(90);
      break;
    case GvaKeyEnum::kKeyF11:
      filename = path;
      filename.append("/Rear.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(180);
      break;
    case GvaKeyEnum::kKeyF12:
      filename = path;
      filename.append("/Left.png");
      SetCanvasPng(filename.c_str());
      compass->SetBearing(270);
      break;
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
      screen_.message.visible = true;
      screen_.message.icon = kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
  }
  return keypress;
}

void StateSA::entry() {
  if (screen_.function_top->labels[0].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kSituationalAwareness);
    lastState_ = GvaFunctionEnum::kSituationalAwareness;
    Reset();
    screen_.function_top->labels[0].state = LabelStates::kLabelEnabledSelected;

    if (screen_.labels != LabelModeEnum::kLabelMinimal) screen_render_->GetWidget(KWidgetTypeCompass)->SetVisible(true);
    screen_render_->GetWidget(KWidgetTypeCompass)->SetVisible(true);
    if (!screen_.canvas.surface) {
      std::string filename;
      filename = ConfigData::GetInstance()->GetImagePath();
      filename.append("/FrontCenter.png");
      SetCanvasPng(filename.c_str());
    }
    screen_.function_top->labels[0].state = LabelStates::kLabelEnabledSelected;
  }
};

void StateSA::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateSA::react(EventKeySA const &) { transit<StateSA>(); };

void StateSA::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateSA::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateSA::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateSA::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateSA::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateSA::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateSA::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateSA::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateSA::react(EventKeyFunction const &e) {
  KeySA(e.key);
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateWPN>();
};

}  // namespace gva
