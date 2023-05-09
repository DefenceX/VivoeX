//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file sa.cc
///

#include "sa.h"

#include <glog/logging.h>
namespace gva {

GvaKeyEnum Hmi::KeySA(GvaKeyEnum keypress, GvaKeyEnum *current) {
  gva::WidgetVideo *video = (gva::WidgetVideo *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeVideo));
  screen_.function_right.visible = true;
  const std::string path = ConfigData::GetInstance()->GetImagePath();
  std::string filename;

  auto *compass =
      static_cast<WidgetPlanPositionIndicator *>(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass));
  auto *objects = static_cast<WidgetObjectLocalisation *>(
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeObjectLocalisation));
  objects->SetVisible(false);
  KeySide(keypress);
  Key(keypress);

  compass->SetMode(ConfigData::GetInstance()->GetPpiMode());

  switch (keypress) {
    case GvaKeyEnum::kKeyF2:
      filename = path;
      filename.append("/Quad.png");
      SetCanvasPng(filename);
      video->SetVisible(false);
      if (ConfigData::GetInstance()->GetPpiMode() == widget::ModeEnum::kPpiClassicArrowWithSight)
        compass->SetMode(widget::ModeEnum::kPpiClassicArrowWithoutSight);
      if (ConfigData::GetInstance()->GetPpiMode() == widget::ModeEnum::kPpiClassicTankWithSight)
        compass->SetMode(widget::ModeEnum::kPpiClassicTankWithoutSight);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF4:
      // filename = path;
      // filename.append("/FrontRight.png");
      // SetCanvasPng(filename.c_str());
      video->SetSessionName("day1");
      video->SetIpAddress("239.192.1.1");
      video->SetVisible(true);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF5:
      objects->SetVisible(true);
      filename = path;
      // filename.append("/FrontCenter.png");
      filename.append("/Soldiers01.png");
      SetCanvasPng(filename.c_str());
      video->SetVisible(false);
      // video->SetIpAddress("239.192.2.1");
      // video->SetVisible(true);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF6:
      // filename = path;
      // filename.append("/FrontLeft.png");
      // SetCanvasPng(filename.c_str());
      video->SetSessionName("day3");
      video->SetIpAddress("239.192.3.1");
      video->SetVisible(true);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF10:
      // filename = path;
      // filename.append("/Right.png");
      // SetCanvasPng(filename.c_str());
      video->SetSessionName("day4");
      video->SetIpAddress("239.192.4.1");
      video->SetVisible(true);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF11:
      // filename = path;
      // filename.append("/Rear.png");
      // SetCanvasPng(filename.c_str());
      video->SetSessionName("day5");
      video->SetIpAddress("239.192.5.1");
      video->SetVisible(true);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF12:
      // filename = path;
      // filename.append("/Left.png");
      // SetCanvasPng(filename.c_str());
      video->SetSessionName("day6");
      video->SetIpAddress("239.192.6.1");
      video->SetVisible(true);
      *current = keypress;
      break;
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
      screen_.message.visible = true;
      screen_.message.icon = widget::IconType::kIconError;
      screen_.message.brief.text = "Function key";
      screen_.message.detail.text = "Operation not implemented!";
      break;
    case GvaKeyEnum::kKeyF19:  // labels
      if (*current == GvaKeyEnum::kKeyF5) {
        screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeObjectLocalisation)->SetVisible(true);
      }
      break;
    default:
      break;
  }
  return keypress;
}

void StateSA::entry() {
  LOG(INFO) << "Entering the SA State";
  if (screen_.function_top->labels[0].state != LabelStates::kLabelHidden) {
    manager_->SetScreen(&screen_, GvaFunctionEnum::kSituationalAwareness);
    lastState_ = GvaFunctionEnum::kSituationalAwareness;
    Reset();
    screen_.function_top->SetEnabled(0);

    if (screen_.labels != LabelModeEnum::kLabelMinimal)
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);
    if (!screen_.canvas.surface) {
      std::string filename;
      filename = ConfigData::GetInstance()->GetImagePath();
      screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeObjectLocalisation)->SetVisible(true);
      // filename.append("/FrontCenter.png");
      std::cout << "Setting soldier image\n";
      filename.append("/Soldiers01.png");
      SetCanvasPng(filename.c_str());
      // video_ = (gva::WidgetVideo *)(screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeVideo));
    }
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
  KeySA(e.key, &current_selection_);
  if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateWPN>();
};

void StateSA::exit() {
  DLOG(INFO) << "Leaving the SA State";
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeObjectLocalisation)->SetVisible(false);
}

}  // namespace gva
