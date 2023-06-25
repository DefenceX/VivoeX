//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file updater.cc
///

#include "updater/updater.h"

#include <glog/logging.h>

#include <cmath>
#include <iostream>

#include "hmicore/gva.h"
#include "hmicore/hardware/audio.h"
#include "hmicore/widgets/ai/object_localisation.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/bottom_labels.h"
#include "hmicore/widgets/driver/rpm_fuel.h"
#include "hmicore/widgets/driver/speedometer.h"
#include "hmicore/widgets/driver/battery_bar.h"
#include "hmicore/widgets/plan_position_indicator.h"

namespace gva {
bool Updater::running_ = false;

Updater::Updater(uint64_t id) : UpdaterBase(id){};

void Updater::RegisterWidgets(std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>> &widget_list) {
  widget_list_ = &widget_list;
  std::shared_ptr<gva::WidgetPlanPositionIndicator> compass =
      std::static_pointer_cast<gva::WidgetPlanPositionIndicator>(widget_list[widget::WidgetEnum::KWidgetTypeCompass]);
  compass->SetBearing(200);

  auto it = widget_list[widget::WidgetEnum::KWidgetTypeCompass];

  thread_ = std::thread(Updater::WidgetUpdaterThread, widget_list_);
}

Updater::~Updater() {
  LOG(INFO) << "Finalising updater";
  running_ = false;
  if (thread_.joinable()) {
    thread_.join();
  }
}

void Updater::UpdateState(std::string state) {}

void Updater::Event(std::string event) {}

void Updater::WidgetUpdaterThread(std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>> *widget_list) {
  uint16_t count = 0;
  std::array<gva::WidgetObjectLocalisation::BoxType, 6> box;

  gva::AudioFunctions audio;
  LOG(INFO) << "Starting widget updater thread";

  // box[0] = {310, 170, 240, 104, 0xff0000, "Person, threat", false, false};
  // box[1] = {20, 185, 100, 40, 0x00ff00, "Person", false, false};
  // box[2] = {76, 200, 105, 50, 0xffa500, "Person, Gun", false, true};
  // box[3] = {180, 200, 180, 80, 0xff0000, "Person, Threat", false, false};
  // box[4] = {400, 190, 90, 36, 0xffa500, "", false, false};
  // box[5] = {500, 195, 50, 20, 0xfff00, "Person", false, true};
  // box[6] = {550, 169, 100, 42, 0xfff00, "Person", false, false};

  box[0] = {8, 174, 234, 88, 0x00ff00, "Person", false, false};
  box[1] = {80, 83, 366, 148, 0x00ff00, "Person", false, false};
  box[2] = {285, 144, 274, 120, 0x00ff00, "Person", false, false};
  box[3] = {395, 187, 213, 71, 0x00ff00, "Person", false, false};
  box[4] = {436, 88, 369, 162, 0xffa500, "Person", false, false};
  box[5] = {475, 189, 43, 90, 0xff0000, "Weapon", false, false};
  // box[1] = {20, 185, 100, 40, 0x00ff00, "Person", false, false};
  // box[2] = {76, 200, 105, 50, 0xffa500, "Person, Gun", false, true};
  // box[3] = {180, 200, 180, 80, 0xff0000, "Person, Threat", false, false};
  // box[4] = {400, 190, 90, 36, 0xffa500, "", false, false};
  // box[5] = {500, 195, 50, 20, 0xfff00, "Person", false, true};
  // box[6] = {550, 169, 100, 42, 0xfff00, "Person", false, false};

  std::shared_ptr<gva::WidgetDriverSpeedometer> speed = std::static_pointer_cast<gva::WidgetDriverSpeedometer>(
      widget_list->at(widget::WidgetEnum::kWidgetTypeDialSpeedometer));

  std::shared_ptr<gva::WidgetDriverRpmFuel> rpm =
      std::static_pointer_cast<gva::WidgetDriverRpmFuel>(widget_list->at(widget::WidgetEnum::KWidgetTypeDialRpmFuel));
  
  std::shared_ptr<gva::WidgetDriverBatteryBar> gauge_bar =
      std::static_pointer_cast<gva::WidgetDriverBatteryBar>(widget_list->at(widget::WidgetEnum::KWidgetTypeBatteryBar));

  std::shared_ptr<gva::WidgetPlanPositionIndicator> compass =
      std::static_pointer_cast<gva::WidgetPlanPositionIndicator>(
          widget_list->at(widget::WidgetEnum::KWidgetTypeCompass));

  std::shared_ptr<gva::WidgetObjectLocalisation> objects = std::static_pointer_cast<gva::WidgetObjectLocalisation>(
      widget_list->at(widget::WidgetEnum::KWidgetTypeObjectLocalisation));

  std::shared_ptr<gva::WidgetAlarmIndicator> alarm_indicator = std::static_pointer_cast<gva::WidgetAlarmIndicator>(
      widget_list->at(widget::WidgetEnum::KWidgetTypeAlarmIndicator));

  std::shared_ptr<gva::WidgetBottomLabels> bottom =
      std::static_pointer_cast<gva::WidgetBottomLabels>(widget_list->at(widget::WidgetEnum::KWidgetTypeBottomLabels));

  alarm_indicator->SetType(GvaAlarmType::kAlarmCaution);
  alarm_indicator->SetText("Engine over temperature");

  // Loop through box and set unique ids
  uint16_t id = 0;
  for (const auto &object : box) {
    objects->AddBoundingBox(id++, object);
  }

  gva::WidgetPlanPositionIndicator::ThreatType threat = {110, 30, 0xff0000, "Person", false, false};
  compass->AddThreat(1, threat);
  threat.rgb_value = 0xffa500;
  threat.bearing = 20;
  compass->AddThreat(2, threat);

  running_ = true;
  // This is the threat event loop
  while (running_) {
    compass->SetBearing((uint16_t)GenerateSineWave((int)count));
    compass->SetBearingSight((uint16_t)(count % 360));
    compass->SetWeaponAzimuth((uint16_t)(360 - (count % 360)));

    speed->SetValue(GenerateSineWave(count));
    rpm->SetValue(GenerateSineWave(count) * 90);
    nanosleep((const struct timespec[]){{0, 100000000L}}, nullptr);

    if (count == 50) {
      alarm_indicator->SetType(GvaAlarmType::kAlarmAdvisory);
      alarm_indicator->SetVisible(true);
      // As there is an alarm set the Ack control to enabled
      bottom->EnableLabel(GvaKeyEnum::kKeyF16);
    }

    if (count == 150) {
      alarm_indicator->SetVisible(true);
      alarm_indicator->SetType(GvaAlarmType::kAlarmWarnings);
      // As there is an alarm set the Ack control to enabled
      bottom->EnableLabel(GvaKeyEnum::kKeyF16);
      audio.PlayWarning();
    }

    if (count == 200) {
      alarm_indicator->SetVisible(true);
      alarm_indicator->SetType(GvaAlarmType::kAlarmCaution);
      // As there is an alarm set the Ack control to enabled
      bottom->EnableLabel(GvaKeyEnum::kKeyF16);
      audio.PlayCaution();
    }

    count++;
  }
  LOG(INFO) << "Quitting widget updater thread";
}

// Generate a sine wave with values ranging from 0 to 100
uint16_t Updater::GenerateSineWave(int sample, double sampleRate, double frequency) {
  const double PI = 3.14159265358979323846;
  double time = (double)sample / sampleRate;
  double value = sin(2 * PI * frequency * time);
  return (uint16_t)(50.0 * value + 50.0);
}
}  // namespace gva