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
/// \file screen_gva.cc
///

#include "hmicore/screen_gva.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "hmicore/status_updater.h"
#if defined(_WIN32)
struct termios {
  uint32_t dummy_struct = 0;
};
#else
#include <termios.h>
#endif
#include <glog/logging.h>
#include <time.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "common/debug.h"
#include "hmicore/gva.h"
#include "hmicore/gva_functions_common.h"
#include "hmicore/hmi_gva_helpers.h"
#include "widgets/canvas.h"
#include "widgets/widgets.h"

namespace gva {

ClockArgs ScreenGva::args_ = {};

ScreenGva::ScreenGva(Screen *screen, uint32_t width, uint32_t height) : RendererGva(width, height), screen_(screen) {
  struct termios settings;

  config_ = gva::ConfigData::GetInstance();

  LOG(INFO) << "GVA screen initialised (" << std::to_string(width_) << "x" << std::to_string(height_);

  // Initialise the parser for NEMA
  nmea_zero_INFO(&info_);
  nmea_parser_init(&parser_);

#if (__MINGW64__ || __MINGW32__)
#pragma message "No serial support on MSYS2 yet, GPS disabled"
#else
  // Open File Descriptor
  gps_ = open(screen->info.gpsDevice.c_str(), O_RDWR | O_NONBLOCK | O_NDELAY);

  if (gps_ > 0) {
    LOG(INFO) << "GPS Opened " + screen->info.gpsDevice;
  } else {
    LOG(ERROR) << "GPS Error Opening device " << screen->info.gpsDevice;
  }
  tcgetattr(gps_, &settings);

  //
  // Set Baud Rate
  //
  cfsetospeed(&settings, B4800);        // baud rate
  tcsetattr(gps_, TCSANOW, &settings);  // apply the settings
#endif

  //
  // Setup the required widgets
  //
  RendererGva *renderer = this;
  TouchGva *touch = GetTouch();

  // Here we need to add all the possible screen widgets to the widget list, at this point they are uninitialised
  widget_list_[widget::WidgetEnum::KWidgetTypeCanvas] = std::make_shared<WidgetCanvas>(*renderer);
  widget_list_[widget::WidgetEnum::KWidgetTypeCompass] = std::make_shared<WidgetPlanPositionIndicator>(*renderer);
  widget_list_[widget::WidgetEnum::KWidgetTypeKeyboard] = std::make_shared<WidgetKeyboard>(*renderer);
  widget_list_[widget::WidgetEnum::kWidgetTypeDialSpeedometer] = std::make_shared<WidgetDriverSpeedometer>(*renderer);
  widget_list_[widget::WidgetEnum::KWidgetTypeDialRpmFuel] = std::make_shared<WidgetDriverRpmFuel>(*renderer);
  widget_list_[widget::WidgetEnum::KWidgetTypeAlarmIndicator] =
      std::make_shared<WidgetAlarmIndicator>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeTopLabels] = std::make_shared<WidgetTopLabels>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeBottomLabels] = std::make_shared<WidgetBottomLabels>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeLeftLabels] = std::make_shared<WidgetSideLabels>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeRightLabels] = std::make_shared<WidgetSideLabels>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeRightLabels] = std::make_shared<WidgetSideLabels>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeTable] =
      std::make_shared<WidgetTable>(*renderer, touch, ConfigData::GetInstance()->GetThemeBackground());
  widget_list_[widget::WidgetEnum::KWidgetTypeTableDynamic] =
      std::make_shared<WidgetTableDynamic>(*renderer, touch, ConfigData::GetInstance()->GetThemeBackground());
  widget_list_[widget::WidgetEnum::KWidgetObjectLocalisation] =
      std::make_shared<WidgetObjectLocalisation>(*renderer, touch);
  widget_list_[widget::WidgetEnum::KWidgetTypeStatusBar] = std::make_shared<WidgetStatusBar>(*renderer, touch);

  for (auto const &[key, val] : widget_list_) {
    LOG(INFO) << "Created WidgetX item :" << val->GetWidgetName() << "(" << val->GetVisible() << ")";
  }

  //
  // Start the Real Time Clock
  //
  StartClock(widget_list_[widget::WidgetEnum::KWidgetTypeStatusBar]);

  //
  // Load some dummy alarms (real alarms come from LDM)
  //
  auto *table = (WidgetTableDynamic *)GetWidget(widget::WidgetEnum::KWidgetTypeTableDynamic);
  HmiHelper::TableAlarms(table);

  //
  // Initialise right labels
  //
  auto right_labels = (WidgetSideLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeRightLabels);
  right_labels->SetLabels(&screen_->function_right.labels);
  right_labels->SetX(kMinimumWidth - 100 - 1);

  //
  // Initialise left labels
  //
  auto left_labels = (WidgetSideLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeLeftLabels);
  left_labels->SetLabels(&screen_->function_left.labels);

  //
  // Initialise top labels
  //
  auto top_labels = (WidgetTopLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeTopLabels);
  top_labels->SetY(2);
  top_labels->SetLabels(&screen_->function_top->labels);

  //
  // Initialise bottom labels
  //
  auto bottom_labels = (WidgetBottomLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels);
  bottom_labels->SetLabels(&screen_->control->labels_);

  updater_.RegisterWidgets(widget_list_);
}

ScreenGva::~ScreenGva() {
  args_.active = false;
  clock_thread_.join();
  nmea_parser_destroy(&parser_);
  close(gps_);
  if (gps_) LOG(INFO) << "GPS closed";
  LOG(INFO) << "GVA screen finalized.";
}

void ScreenGva::ClockUpdateThread(ClockArgs *arg) {
  StatusUpdater updater;
  while (arg->active) {
    updater.ClockUpdate(arg);
    struct timespec reqDelay = {1, 0};
    nanosleep(&reqDelay, (struct timespec *)nullptr);
  }  // End thread loop

  LOG(INFO) << "Clock thread terminated";
}

void ScreenGva::StartClock(std::shared_ptr<WidgetX> status_bar_widget) {
  std::shared_ptr<WidgetStatusBar> status_bar = std::dynamic_pointer_cast<WidgetStatusBar>(status_bar_widget);
  args_.active = true;
  args_.parser = &parser_;
  args_.info = &info_;
  args_.gps = &gps_;
  args_.screen = this;
  args_.status_bar = status_bar;
  args_.location.locationFormat = LocationEnum::kLocationFormatMgrs;
  args_.info->lon = ConfigData::GetInstance()->GetTestLon();
  args_.info->lat = ConfigData::GetInstance()->GetTestLat();

  // Launch clock thread
  clock_thread_ = std::thread(ClockUpdateThread, &args_);
  LOG(INFO) << "Created clock thread";
}

GvaStatusTypes ScreenGva::Update() {
  // Reset the Drawing context, must be Reset before reDrawing the screen
  Reset();
  GetTouch()->Reset();

  /// Iterate over all widgets and draw the visible ones
  for (auto const &[key, val] : widget_list_) {
    if (val->GetVisible()) val->Draw();

    // Now lets check check we are not blacked out
    if (val->GetWidgetType() == widget::WidgetEnum::KWidgetTypeCanvas) {
      const gva::WidgetCanvas *canvas_ = (gva::WidgetCanvas *)val.get();
      if (canvas_->GetBlackout()) {
        // Break out the loop as we are blacked out, nothing more to render
        break;
      }
    }
  }

  //
  // Refresh display
  //
  Draw();
  last_screen_ = *screen_;

  return GvaStatusTypes::kGvaSuccess;
}

WidgetX *ScreenGva::GetWidget(widget::WidgetEnum widget) {
  if (widget_list_.empty()) {
    LOG(FATAL) << "Widget list is empty";
  }

  // find the widget in widget_list_ and return it
  if (widget_list_.find(widget) == widget_list_.end()) {
    LOG(FATAL) << "Widget(" << (int)widget << ") not found";
  }
  return widget_list_.find(widget)->second.get();
}

}  // namespace gva
