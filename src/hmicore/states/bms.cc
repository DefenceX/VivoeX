//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file bms.cc
///

#include "bms.h"

#include <glog/logging.h>

#include "hmicore/widgets/canvas/canvas.h"
#include "hmicore/widgets/widget_types.h"

namespace gva {

///
/// \brief Convert zoom level to a double
///
/// \param zoom The zoom level
/// \return double
///
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
    default:  // Dont modify value
      break;
  }
  return 0;
}

GvaKeyEnum Hmi::KeyBMS(GvaKeyEnum keypress) {
  screen_.function_right.visible = true;
  KeySide(keypress);
  Key(keypress);
  if (ConfigData::GetInstance()->GetMapEnabled()) {
    bool update = true;
    int zoom_level = ConfigData::GetInstance()->GetZoom();
    switch (keypress) {
      case GvaKeyEnum::kKeyF3:
        // Shift UP
        ConfigData::GetInstance()->SetTestLat(ConfigData::GetInstance()->GetTestLat() + conv(zoom_level));
        break;
      case GvaKeyEnum::kKeyF4:
        // Shift DOWN
        ConfigData::GetInstance()->SetTestLat(ConfigData::GetInstance()->GetTestLat() - conv(zoom_level));
        break;
      case GvaKeyEnum::kKeyF5:
        // Zoom +
        ConfigData::GetInstance()->SetZoom(zoom_level * 2);
        break;
      case GvaKeyEnum::kKeyF9:
        // Shift LEFT
        ConfigData::GetInstance()->SetTestLon(ConfigData::GetInstance()->GetTestLon() - conv(zoom_level));
        break;
      case GvaKeyEnum::kKeyF10:
        // Shift RIGHT
        ConfigData::GetInstance()->SetTestLon(ConfigData::GetInstance()->GetTestLon() + conv(zoom_level));
        break;
      case GvaKeyEnum::kKeyF11:
        // Zoom -
        ConfigData::GetInstance()->SetZoom(zoom_level / 2);
        break;
      case GvaKeyEnum::kKeyF1:
      case GvaKeyEnum::kKeyF2:
      case GvaKeyEnum::kKeyF6:
      case GvaKeyEnum::kKeyF7:  ///
      case GvaKeyEnum::kKeyF8:
      case GvaKeyEnum::kKeyF12:
        screen_.message.visible = true;
        screen_.message.icon = widget::IconType::kIconInfo;
        screen_.message.brief.text = "Function key";
        screen_.message.detail.text = "Operation not implemented !";
      default:
        update = false;
        break;
    }

    if (update) {
      LOG(INFO) << "[BMS] Zoom level " + std::to_string(ConfigData::GetInstance()->GetZoom()) << " "
                << std::to_string(ConfigData::GetInstance()->GetTestLat()) << " "
                << std::to_string(((double)ConfigData::GetInstance()->GetZoom() / 10000000) +
                                  ((double)ConfigData::GetInstance()->GetZoom() / 10000))
                << " ";
      map_->SetWidth(1920);
      map_->SetHeight(1080);
      LOG(INFO) << "[BMS] res " + std::to_string(screen_render_->GetWidth()) << "x"
                << std::to_string(screen_render_->GetHeight());

      map_->Project(ConfigData::GetInstance()->GetZoom(), ConfigData::GetInstance()->GetTestLon(),
                    ConfigData::GetInstance()->GetTestLat(), &screen_.canvas.surface);
      auto canvas = (gva::WidgetCanvas *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCanvas));
      canvas->SetSurface(screen_.canvas.surface);
    }
  }
  return keypress;
}

void StateBMS::entry() {
  DLOG(INFO) << "Entering the BMS State";

  if (screen_.function_top->labels[7].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kBattlefieldManagementSystem);
    Reset();
    lastState_ = GvaFunctionEnum::kBattlefieldManagementSystem;
    screen_.function_top->SetEnabled(7);
    screen_.canvas.visible = true;
    if (ConfigData::GetInstance()->GetMapEnabled()) {
      map_->SetWidth(kMinimumWidth);
      map_->SetHeight(kMinimumHeight);
      map_->Project(ConfigData::GetInstance()->GetZoom(), ConfigData::GetInstance()->GetTestLon(),
                    ConfigData::GetInstance()->GetTestLat(), &screen_.canvas.surface);
      auto canvas = (gva::WidgetCanvas *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCanvas));
      canvas->SetSurface(screen_.canvas.surface);
    } else {
      // Display the DefenceX logo
      std::string filename = ConfigData::GetInstance()->GetImagePath();
      filename.append("/DefenceX.png");
      SetCanvasPng(filename.c_str());
    }
  }
};

void StateBMS::exit() { return; }  // Nothing to do on exit

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
