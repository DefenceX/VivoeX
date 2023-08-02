//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file on.cc
///

#include "on.h"

#include <glog/logging.h>

#include <filesystem>

#include "common/utils.h"

namespace gva {

void StateOn::entry() {
  DLOG(INFO) << "Entering the On State";

  hmiScreenSize& hmiScreenSize = hmiScreenSize::getInstance();
  std::tuple<int, int> size = hmiScreenSize.getMinimumSize(); 

  /* 4:3 aspect ratio @ lowest resolution */
  view_ = {static_cast<uint32_t>(std::get<0>(size)), static_cast<uint32_t>(std::get<1>(size)), 24};

  if (!manager_) manager_ = std::make_shared<ViewGvaManager>();

  if (!std::filesystem::is_directory(ConfigData::GetInstance()->GetMapPath())) {
    LOG(ERROR) << "Could not find map data " << ConfigData::GetInstance()->GetMapPath();
    ConfigData::GetInstance()->SetMapEnabled(false);
  } else {
    ConfigData::GetInstance()->SetMapEnabled(true);
  }

  if (ConfigData::GetInstance()->GetMapEnabled()) {
    // Render a map for BMS
    map_ = std::make_shared<rendererMap>(ConfigData::GetInstance()->GetMapPath(),
                                         ConfigData::GetInstance()->GetStylesheetPath(), std::get<0>(size), std::get<1>(size));
  }
  top_ = DefaultSettings::GetDefaultFunctionSelect();
  bottom_ = DefaultSettings::GetDefaultCommonTaskKeys();
  screen_ = DefaultSettings::GetDefaultScreen();

  // Setup the main screens
  // SituationalAwareness (SA)
  manager_->AddNewView(GvaFunctionEnum::kSituationalAwareness, &top_, &bottom_,
                       DefaultSettings::GetDefaultFunctionKeysSituationalAwarenessLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeysSituationalAwarenessRight());
  // Weapons (WPN)
  manager_->AddNewView(GvaFunctionEnum::kWeapon, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeysWeaponsLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeysWeaponsRight());
  // Defensive Systems (DEF)
  manager_->AddNewView(GvaFunctionEnum::kDefensiveSystems, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeysDefensiveSystemsLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Systems, no labels on right so defaults used
  manager_->AddNewView(GvaFunctionEnum::kSystems, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeySystemsLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeySystemsRight());
  // Driver (DRV), no labels on right so defaults used
  manager_->AddNewView(GvaFunctionEnum::kDriver, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden(),
                       gva::DefaultSettings::GetDefaultFunctionKeyDriverRight());
  // Special To Role (STR), not used so all defaults
  manager_->AddNewView(GvaFunctionEnum::KSpecialToRole, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Communications (COM), no labels on right so defaults used
  manager_->AddNewView(GvaFunctionEnum::kCommunications, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeyCommunicationsLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Battlefield Management System (BMS)
  manager_->AddNewView(GvaFunctionEnum::kBattlefieldManagementSystem, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemRight());
  // Alarms
  manager_->AddNewView(GvaFunctionEnum::kAlarmsX, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeyAlarmsLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeyAlarmsRight());

  manager_->SetScreen(&screen_, GvaFunctionEnum::kSystems);

  // Create the screen render now
  screen_render_ = std::make_shared<ScreenGva>(&screen_, view_.width, view_.height);

  // Configure the widgets
  ((WidgetPlanPositionIndicator *)screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass))
      ->SetBearingSight(0);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(190);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(330);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetVisible(false);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeAlarmIndicator)->SetY(58);
  screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels)->SetY(480 - 20);

  screen_.canvas = canvas_;
  screen_.canvas.visible = true;
  screen_.labels = LabelModeEnum::kLabelAll;
  std::string filename = ConfigData::GetInstance()->GetImagePath();
  filename.append("/FRONT_CENTRE.png");
  SetCanvasPng(filename.c_str());

  // Set brightness
  gva::SetBrightness(gva::ConfigData::GetInstance()->GetBrightness());

  transit<StateSYS>();
};

}  // namespace gva
