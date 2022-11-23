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

void StateSA::entry() {
  if (screen_.function_top->labels[0].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kSituationalAwareness);
    lastState_ = GvaFunctionEnum::kSituationalAwareness;
    Reset();
    screen_.function_top->labels[0].state = LabelStates::kLabelEnabledSelected;

    if (screen_.labels != LabelModeEnum::kLabelMinimal)
      screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetVisible(true);
    screen_render_->GetWidget(WIDGET_TYPE_COMPASS)->SetVisible(true);
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
