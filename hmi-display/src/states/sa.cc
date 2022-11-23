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

struct StateSA : Hmi {
  void entry() override {
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
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeySA(e.key);
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateWPN>();
  };
};
