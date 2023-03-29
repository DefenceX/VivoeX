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
/// \file on.cc
///

#include "on.h"

#include <glog/logging.h>

#include <filesystem>

#include "common/utils.h"
#include "src/hmi_gva.h"
#include "src/states/states.h"

namespace gva {

void StateOn::entry() {
  /* 4:3 aspect ratio @ lowest resolution */
  HmiState::GetInstance().view_ = {kMinimumWidth, kMinimumHeight, 24};

  if (!HmiState::GetInstance().manager_) HmiState::GetInstance().manager_ = std::make_shared<ViewGvaManager>();

  if (!std::filesystem::is_directory(ConfigData::GetInstance()->GetMapPath())) {
    LOG(ERROR) << "Could not find map data " << ConfigData::GetInstance()->GetMapPath();
    ConfigData::GetInstance()->SetMapEnabled(false);
  } else {
    ConfigData::GetInstance()->SetMapEnabled(true);
  }

  if (ConfigData::GetInstance()->GetMapEnabled()) {
    // Render a map for BMS
    HmiState::GetInstance().map_ =
        std::make_shared<rendererMap>(ConfigData::GetInstance()->GetMapPath(),
                                      ConfigData::GetInstance()->GetStylesheetPath(), kMinimumWidth, kMinimumHeight);
  }
  HmiState::GetInstance().top_ = DefaultSettings::GetDefaultFunctionSelect();
  HmiState::GetInstance().bottom_ = DefaultSettings::GetDefaultCommonTaskKeys();
  HmiState::GetInstance().canvas_ = DefaultSettings::GetDefaultCanvas();
  HmiState::GetInstance().screen_ = DefaultSettings::GetDefaultScreen();

  // Setup the main screens
  // SituationalAwareness (SA)
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kSituationalAwareness, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               DefaultSettings::GetDefaultFunctionKeysSituationalAwarenessLeft(),
                                               gva::DefaultSettings::GetDefaultFunctionKeysSituationalAwarenessRight());
  // Weapons (WPN)
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kWeapon, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeysWeaponsLeft(),
                                               gva::DefaultSettings::GetDefaultFunctionKeysWeaponsRight());
  // Defensive Systems (DEF)
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kDefensiveSystems, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeysDefensiveSystemsLeft(),
                                               gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Systems, no labels on right so defaults used
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kSystems, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeySystemsLeft(),
                                               gva::DefaultSettings::GetDefaultFunctionKeySystemsRight());
  // Driver (DRV), no labels on right so defaults used
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kDriver, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden(),
                                               gva::DefaultSettings::GetDefaultFunctionKeyDriverRight());
  // Special To Role (STR), not used so all defaults
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::KSpecialToRole, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden(),
                                               gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Communications (COM), no labels on right so defaults used
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kCommunications, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeyCommunicationsLeft(),
                                               gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Battlefield Management System (BMS)
  HmiState::GetInstance().manager_->AddNewView(
      GvaFunctionEnum::kBattlefieldManagementSystem, &HmiState::GetInstance().top_, &HmiState::GetInstance().bottom_,
      gva::DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemLeft(),
      gva::DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemRight());
  // Alarms
  HmiState::GetInstance().manager_->AddNewView(GvaFunctionEnum::kAlarmsX, &HmiState::GetInstance().top_,
                                               &HmiState::GetInstance().bottom_,
                                               gva::DefaultSettings::GetDefaultFunctionKeyAlarmsLeft(),
                                               gva::DefaultSettings::GetDefaultFunctionKeyAlarmsRight());

  HmiState::GetInstance().manager_->SetScreen(&HmiState::GetInstance().screen_, GvaFunctionEnum::kSystems);

  // Create the screen render now
  HmiState::GetInstance().screen_render_ = std::make_shared<ScreenGva>(
      &HmiState::GetInstance().screen_, HmiState::GetInstance().view_.width, HmiState::GetInstance().view_.height);

  // Configure the widgets
  ((WidgetPlanPositionIndicator *)HmiState::GetInstance().screen_render_->GetWidget(
       widget::WidgetEnum::KWidgetTypeCompass))
      ->SetBearingSight(0);
  HmiState::GetInstance().screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetY(190);
  HmiState::GetInstance().screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetX(330);
  HmiState::GetInstance().screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeCompass)->SetVisible(true);
  HmiState::GetInstance().screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic)->SetVisible(false);
  HmiState::GetInstance().screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeAlarmIndicator)->SetY(58);
  HmiState::GetInstance().screen_render_->GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels)->SetY(480 - 20);

  HmiState::GetInstance().screen_.canvas = HmiState::GetInstance().canvas_;
  HmiState::GetInstance().screen_.canvas.visible = true;
  HmiState::GetInstance().screen_.labels = LabelModeEnum::kLabelAll;
  std::string filename = ConfigData::GetInstance()->GetImagePath();
  filename.append("/FRONT_CENTRE.png");
  HmiState::GetInstance().SetCanvasPng(filename.c_str());

  // Set brightness
  gva::SetBrightness(gva::ConfigData::GetInstance()->GetBrightness());

  transit<StateSYS>();
};

}  // namespace gva
