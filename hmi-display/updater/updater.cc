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
/// \file updater.cc
///

#include "updater/updater.h"

#include <glog/logging.h>

#include <cmath>
#include <iostream>

#include "src/hardware/audio.h"
#include "src/widgets/ai/object_localisation.h"
#include "src/widgets/alarm_indicator.h"
#include "src/widgets/bottom_labels.h"
#include "src/widgets/driver/rpm_fuel.h"
#include "src/widgets/driver/speedometer.h"
#include "src/widgets/plan_position_indicator.h"

namespace gva {

Updater::Updater(uint64_t id) : UpdaterBase(id){};

Updater::~Updater() { pthread_cancel(thread_); };

void Updater::RegisterWidgets(std::unordered_map<widget::WidgetEnum, std::shared_ptr<WidgetX>> &widget_list) {
  std::shared_ptr<gva::WidgetPlanPositionIndicator> compass =
      std::static_pointer_cast<gva::WidgetPlanPositionIndicator>(widget_list[widget::WidgetEnum::KWidgetTypeCompass]);
  compass->SetBearing(200);

  auto it = widget_list[widget::WidgetEnum::KWidgetTypeCompass];

  widget_list_ = &widget_list;

  thread_id_ = pthread_create(&thread_, nullptr, Updater::WidgetUpdaterThread, (void *)widget_list_);
}

void Updater::UpdateState(std::string state) {}

void Updater::Event(std::string event) {}

void *Updater::WidgetUpdaterThread(void *ptr) {
  uint64_t count = 0;
  std::array<gva::WidgetObjectLocalisation::BoxType, 8> box;

  gva::AudioFunctions audio;
  LOG(INFO) << "Starting widget updater thread";

  box[0] = {310, 170, 240, 104, 0xff0000, "Person, threat", false, false};
  box[1] = {20, 185, 100, 40, 0x00ff00, "Person", false, false};
  box[2] = {76, 200, 105, 50, 0xffa500, "Person, Gun", false, true};
  box[3] = {180, 200, 180, 80, 0xff0000, "Person, Threat", false, false};
  box[4] = {400, 190, 90, 36, 0xffa500, "", false, false};
  box[5] = {500, 195, 50, 20, 0xfff00, "Person", false, true};
  box[6] = {550, 169, 100, 42, 0xfff00, "Person", false, false};

  const std::unordered_map<widget::WidgetEnum, std::shared_ptr<WidgetX>> *widget_list =
      (std::unordered_map<widget::WidgetEnum, std::shared_ptr<WidgetX>> *)ptr;

  std::shared_ptr<gva::WidgetDriverSpeedometer> speed = std::static_pointer_cast<gva::WidgetDriverSpeedometer>(
      widget_list->at(widget::WidgetEnum::kWidgetTypeDialSpeedometer));

  std::shared_ptr<gva::WidgetDriverRpmFuel> rpm =
      std::static_pointer_cast<gva::WidgetDriverRpmFuel>(widget_list->at(widget::WidgetEnum::KWidgetTypeDialRpmFuel));

  std::shared_ptr<gva::WidgetPlanPositionIndicator> compass =
      std::static_pointer_cast<gva::WidgetPlanPositionIndicator>(
          widget_list->at(widget::WidgetEnum::KWidgetTypeCompass));

  std::shared_ptr<gva::WidgetObjectLocalisation> objects = std::static_pointer_cast<gva::WidgetObjectLocalisation>(
      widget_list->at(widget::WidgetEnum::KWidgetObjectLocalisation));

  std::shared_ptr<gva::WidgetAlarmIndicator> alarm_indicator = std::static_pointer_cast<gva::WidgetAlarmIndicator>(
      widget_list->at(widget::WidgetEnum::KWidgetTypeAlarmIndicator));

  std::shared_ptr<gva::WidgetBottomLabels> bottom =
      std::static_pointer_cast<gva::WidgetBottomLabels>(widget_list->at(widget::WidgetEnum::KWidgetTypeBottomLabels));

  alarm_indicator->SetType(GvaAlarmType::kAlarmCaution);
  alarm_indicator->SetText("Engine over temperature");

  // Loop through box and set unique ids
  for (int16_t c = 0; c < 7; c++) {
    objects->AddBoundingBox(c + 1, box[c]);
  }

  gva::WidgetPlanPositionIndicator::ThreatType threat = {110, 30, 0xff0000, "Person", false, false};
  compass->AddThreat(1, threat);
  threat.rgb_value = 0xffa500;
  threat.bearing = 20;
  compass->AddThreat(2, threat);
  // This is the threat event loop
  while (true) {
    compass->SetBearing((uint16_t)GenerateSineWave((int)count));
    compass->SetBearingSight((uint16_t)(count % 360));
    compass->SetWeaponAzimuth((uint16_t)(360 - (count % 360)));

    speed->SetValue(GenerateSineWave(count));
    rpm->SetValue(GenerateSineWave(count) * 90);
    nanosleep((const struct timespec[]){{0, 100000000L}}, NULL);

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
  return nullptr;
}

// Generate a sine wave with values ranging from 0 to 100
int Updater::GenerateSineWave(int sample, double sampleRate, double frequency) {
  const double PI = 3.14159265358979323846;
  double time = (double)sample / sampleRate;
  double value = sin(2 * PI * frequency * time);
  return (int)(50.0 * value + 50.0);
}
}  // namespace gva