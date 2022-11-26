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
/// \brief Power on state definition
///
/// \file on.cc
///

#include "on.h"

namespace gva {

void StateOn::entry() {
  /* 4:3 aspect ratio @ lowest resolution */
  view_ = {MIN_WIDTH, MIN_HEIGHT, 24};

  if (!manager_) manager_ = new ViewGvaManager(&status_);

#ifdef ENABLE_OSMSCOUT
  // Render a map for BMS
  map_ = new rendererMap("/opt/osmscout/maps/australia-latest/", "/opt/osmscout/stylesheets/standard.oss", MIN_WIDTH,
                         MIN_HEIGHT);
#endif
  top_ = DefaultSettings::GetDefaultFunctionSelect();
  bottom_ = DefaultSettings::GetDefaultCommonTaskKeys();
  status_ = DefaultSettings::GetDefaultStatusBar();
  canvas_ = DefaultSettings::GetDefaultCanvas();
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
                       gva::DefaultSettings::GetDefaultFunctionKeyDriverLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Special To Role (STR), not used so all defaults
  manager_->AddNewView(GvaFunctionEnum::KSpecialToRole, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Communications (COM), no labels on right so defaults used
  manager_->AddNewView(GvaFunctionEnum::kCommunications, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeyCommunicationsLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());
  // Battlefield Management System (BMS)
  manager_->AddNewView(GvaFunctionEnum::kAlarmsX, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemLeft(),
                       gva::DefaultSettings::GetDefaultFunctionKeyBattlefieldManagementSystemRight());
  // Alarms
  manager_->AddNewView(GvaFunctionEnum::kBattlefieldManagementSystem, &top_, &bottom_,
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden(),
                       gva::DefaultSettings::GetDefaultFunctionKeysDefaultAllHidden());

  manager_->SetScreen(&screen_, GvaFunctionEnum::kSystems);

  // Create the screen render now
  screen_render_ = new ScreenGva(&screen_, view_.width, view_.height);

  // Configure the widgets
  ((WidgetPlanPositionIndicator *)screen_render_->GetWidget(KWidgetTypeCompass))->SetBearingSight(33);
  screen_render_->GetWidget(KWidgetTypeCompass)->SetX(161);
  screen_render_->GetWidget(KWidgetTypeCompass)->SetY(360 + 28);
  screen_render_->GetWidget(KWidgetTypeCompass)->SetVisible(true);
  screen_render_->GetWidget(KWidgetTypeAlarmIndicator)->SetVisible(true);
  screen_render_->GetWidget(KWidgetTypeAlarmIndicator)->SetY(422);

  WidgetAlarmIndicator *ai = (WidgetAlarmIndicator *)screen_render_->GetWidget(KWidgetTypeAlarmIndicator);
  ai->SetType(GvaAlarmType::kAlarmCaution);
  ai->SetText("Engine over temperature");

  screen_.canvas = canvas_;
  screen_.canvas.visible = true;
  screen_.table = alarms_;
  screen_.table.visible_ = false;
  screen_.labels = LabelModeEnum::kLabelAll;
  std::string filename = ConfigData::GetInstance()->GetImagePath();
  filename.append("/FRONT_CENTRE.png");
  SetCanvasPng(filename.c_str());

  transit<StateSYS>();
};

}  // namespace gva
