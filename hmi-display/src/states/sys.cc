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
/// \brief System (SYS) state definition
///
/// \file sys.cc
///

#include "bms.h"

namespace gva {

GvaKeyEnum Hmi::KeySYS(GvaKeyEnum keypress) {
  screen_.function_left.visible = true;
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
      HmiHelper::TableSystem(&screen_.table);
      break;
    case GvaKeyEnum::kKeyF5:
      HmiHelper::TableLicences(&screen_.table);
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
      screen_.message.icon = kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
    case GvaKeyEnum::kKeyF11:
      // Blackout
      screen_.info.mode =
          (screen_.info.mode == ScreenMode::kModeBlackout) ? ScreenMode::kModeOperational : ScreenMode::kModeBlackout;
      screen_.canvas.visible = true;
      if (screen_.info.mode == ScreenMode::kModeBlackout)
        screen_.canvas.bufferType = SurfaceType::kSurfaceBlackout;
      else
        screen_.canvas.bufferType = SurfaceType::kSurfaceFile;
      break;
    case GvaKeyEnum::kKeyF12:
      // Exit
      if (RendererCairo::render_.surface) cairo_surface_destroy(RendererCairo::render_.surface);
      g_application_quit(G_APPLICATION(RendererCairo::render_.win.app));
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

void StateSYS::entry() {
  if (screen_.function_top->labels[3].state != LabelStates::kLabelHidden) {
    std::string filename;
    manager_->SetScreen(&screen_, GvaFunctionEnum::kSystems);
    lastState_ = GvaFunctionEnum::kSystems;
    Reset();

    screen_.status_bar->labels[3].state = LabelStates::kLabelEnabledSelected;
    screen_.function_top->labels[3].state = LabelStates::kLabelEnabledSelected;
    screen_.canvas.visible = true;
    filename = ConfigData::GetInstance()->GetImagePath();
    filename.append("/FrontCenter.png");
    SetCanvasPng(filename.c_str());

    HmiHelper::TableSystem(&screen_.table);

    screen_.function_top->labels[3].state = LabelStates::kLabelEnabledSelected;
  }
};

void StateSYS::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateSYS::react(EventKeySA const &) { transit<StateSA>(); };

void StateSYS::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateSYS::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateSYS::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateSYS::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateSYS::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateSYS::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateSYS::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateSYS::react(EventKeyFunction const &e) {
  KeySYS(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateDEF>();
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateDRV>();
};

}  // namespace gva
