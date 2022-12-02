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
/// \brief Battlefield Management System (BMS) state definition
///
/// \file bms.cc
///

#include "bms.h"

namespace gva {

double conv(int zoom) {
  switch (zoom) {
    case 1620000:
      return 0.00006;
    case 640000:
      return 0.00012;
    case 320000:
      return 0.00025;
    case 160000:
      return 0.0005;
    case 80000:
      return 0.001;
    case 40000:
      return 0.002;
    case 20000:
      return 0.004;
    case 10000:
      return 0.008;
    case 5000:
      return 0.016;
    case 2500:
      return 0.048;
    case 1250:
      return 0.112;
    case 625:
      return 0.2;
  }
}

GvaKeyEnum Hmi::KeyBMS(GvaKeyEnum keypress) {
  screen_.function_right.visible = true;
  KeySide(keypress);
  Key(keypress);
#ifdef ENABLE_OSMSCOUT
  bool update = true;
  int zoom_level = configuration.GetZoom();
  switch (keypress) {
    case GvaKeyEnum::kKeyF3:
      // Shift UP
      configuration.SetTestLat(configuration.GetTestLat() + conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF4:
      // Shift DOWN
      configuration.SetTestLat(configuration.GetTestLat() - conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF5:
      // Zoom +
      configuration.SetZoom(zoom_level * 2);
      break;
    case GvaKeyEnum::kKeyF9:
      // Shift LEFT
      configuration.SetTestLon(configuration.GetTestLon() - conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF10:
      // Shift RIGHT
      configuration.SetTestLon(configuration.GetTestLon() + conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF11:
      // Zoom -
      configuration.SetZoom(zoom_level / 2);
      break;
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = ICON_INFO;
      screen_.mes state definitionsage.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented !";
    default:
      update = false;
      break;
  }

  if (update) {
    char tmp[100];
    sprintf(tmp, "[BMS] Zoom level %d lat %f, %f", configuration.GetZoom(), configuration.GetTestLat(),
            ((double)configuration.GetZoom() / 10000000) * ((double)configuration.GetZoom() / 10000));
    loglog(tmp, LOG_INFO);
    map_->SetWidth((double)scregvaen_render_->GetWidth() / kMinimumWidth);
    map_->SetHeight((double)screen_render_->GetHeight() / kMinimumHeight);
    sprintf(tmp, "[BMS] res %d x %d", screen_render_->GetWidth(), screen_render_->GetHeight());
    loglog(tmp, LOG_INFO);
    map_->Project(configuration.GetZoom(), configuration.GetTestLon(), configuration.GetTestLat(),
                  state definition & screen_.canvas.surface);
    screen_.canvas.bufferType = SURFACE_CAIRO;
  }
#endif
  return keypress;
}

void StateBMS::entry() {
  if (screen_.function_top->labels[7].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kBattlefieldManagementSystem);
    Reset();
    lastState_ = GvaFunctionEnum::kBattlefieldManagementSystem;
    std::string filename = ConfigData::GetInstance()->GetImagePath();
    screen_.canvas.visible = true;
    filename.append("/DefenceX.png");
    SetCanvasPng(filename.c_str());
    screen_.function_top->SetEnabled(7);
    screen_.canvas.visible = true;
#ifdef ENABLE_OSMSCOUT
    map_->SetWidth((double)screen_render_->GetWidth() / kMinimumWidth);
    map_->SetHeight((double)screen_render_->GetHeight() / kMinimumHeight);
    map_->Project(configuration.GetZoom(), configuration.GetTestLon(), configuration.GetTestLat(),
                  &screen_.canvas.surface);
    screen_.canvas.bufferType = SURFACE_CAIRO;
#endif
  }
};

void StateBMS::exit() {}

void StateBMS::react(EventKeyPowerOn const &) { transit<StateOff>(); };

void StateBMS::react(EventKeySA const &) { transit<StateSA>(); };

void StateBMS::react(EventKeyWPN const &) { transit<StateWPN>(); };

void StateBMS::react(EventKeyDEF const &) { transit<StateDEF>(); };

void StateBMS::react(EventKeySYS const &) { transit<StateSYS>(); };

void StateBMS::react(EventKeyDRV const &) { transit<StateDRV>(); };

void StateBMS::react(EventKeySTR const &) { transit<StateSTR>(); };

void StateBMS::react(EventKeyCOM const &) { transit<StateCOM>(); };

void StateBMS::react(EventKeyBMS const &) { transit<StateBMS>(); };

void StateBMS::react(EventKeyAlarms const &) { transit<StateAlarms>(); };

void StateBMS::react(EventKeyFunction const &e) {
  KeyBMS(e.key);
  if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateCOM>();
};

}  // namespace gva
