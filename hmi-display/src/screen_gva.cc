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

#include "src/screen_gva.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#if __MINGW64__ || __MINGW32__
struct termios {
  uint32_t dummy_struct = 0;
};
#else
#include <termios.h>
#endif
#include <time.h>
#include <unistd.h>

// #include <GeographicLib/LambertConformalConic.hpp>
#include <glog/logging.h>

#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "common/debug.h"
#include "src/gva.h"
#include "src/gva_functions_common.h"
#include "src/hmi_gva_helpers.h"
#include "widgets/widgets.h"

const int kMaxNmea = 1000;

namespace gva {
ScreenGva::ScreenGva(std::shared_ptr<Updater> updater, Screen *screen, uint32_t width, uint32_t height)
    : RendererGva(width, height), screen_(screen), updater_(updater) {
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
  // Start the Real Time Clock
  //
  StartClock(screen_->status_bar);

  //
  // Setup the required widgets
  //
  RendererGva *renderer = this;
  TouchGva *touch = GetTouch();

  // Here we need to add all the possible screen widgets to the widget list, at this point they are uninitialised
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
}

ScreenGva::~ScreenGva() {
  args_.active = false;
  pthread_join(clock_thread_, nullptr);
  nmea_parser_destroy(&parser_);
  close(gps_);
  if (gps_) LOG(INFO) << "GPS closed";
  LOG(INFO) << "GVA screen finalized.";
}

void ClockUpdate(ClockArgs *a) {
  // Get the system time and be thread safe
  auto unix_epoch_time = (time_t) nullptr;
  struct tm local_time;
  unix_epoch_time = time(&unix_epoch_time);
  localtime_r(&unix_epoch_time, &local_time);  // Compliant

  char clock[1000];
  snprintf(clock, sizeof(clock), "%02d/%02d/%02d %02d:%02d:%02d", local_time.tm_mday, local_time.tm_mon + 1,
           local_time.tm_year + 1900, local_time.tm_hour, local_time.tm_min, local_time.tm_sec);
  a->clockString = clock;

#if (__MINGW64__ || __MINGW32__)
#else
  char c;
  char tmp[kMaxNmea + 2] = {0};
  uint32_t i = 0;
  uint32_t ii = 0;
  char buffer[kMaxNmea] = {0};

  if (*a->gps > 0) {
    i = 0;
    tcflush(*a->gps, TCIOFLUSH);

    if (auto size = read(*a->gps, &buffer[0], 1); size != 0) {
      memset(buffer, 0, kMaxNmea);
      while (buffer[0] != '$') {
        auto size_read = read(*a->gps, &buffer[0], 1);
        if (size_read == 0) break;
      }
      while (buffer[i++] != '\n') {
        ii = (uint32_t)read(*a->gps, &c, 1);
        if (ii == 1) {
          buffer[i] = c;
        }
        if (i == kMaxNmea) break;
      }
      buffer[i - 1] = 0;
      std::string tmp_buffer = buffer;
      LOG(INFO) << "GPS NMEA " << tmp_buffer;
    }

    snprintf(tmp, sizeof(tmp), "%s\r\n", buffer);
    a->info->lon = a->location->lon;
    a->info->lat = a->location->lat;
    nmea_parse(a->parser, tmp, sizeof(tmp), a->info);
    a->info->lat = ToDegrees((float)a->info->lat);
    a->info->lon = ToDegrees((float)a->info->lon);
  }
#endif

  if ((a->info->lon != 0) && (a->info->lat != 0)) {
    switch (a->location->locationFormat) {
      case LocationEnum::kLocationFormatLongLat:
        a->locationFormat = "LONLAT";
        {
          std::stringstream stream;
          stream << std::fixed << std::setprecision(2) << "Lat:" << a->info->lat << " Lon:" << a->info->lon << " ["
                 << a->info->sig << "]" << a->info->fix;
          a->locationString = stream.str();
        }
        break;
      case LocationEnum::kLocationFormatMgrs: {
        int zone;
        bool northp;
        double x;
        double y;
        GeographicLib::UTMUPS::Forward(a->info->lat, a->info->lon, zone, northp, x, y);
        std::string mgrs;
        GeographicLib::MGRS::Forward(zone, northp, x, y, a->info->lat, 5, mgrs);
        a->locationFormat = "MGRS";
        a->locationString = mgrs;
      } break;
    }
  }
  gva::EventsGva::CreateRefreshEvent();
}

void *ClockUpdateThread(void *arg) {
  auto a = (ClockArgs *)arg;

  while (a->active) {
    ClockUpdate(a);
    struct timespec reqDelay = {1, 0};
    nanosleep(&reqDelay, (struct timespec *)nullptr);
  }  // End thread loop

  return nullptr;
}

void ScreenGva::StartClock(StatusBar *barData) {
  args_.active = true;
  args_.parser = &parser_;
  args_.info = &info_;
  args_.gps = &gps_;
  args_.screen = this;
  args_.location = &barData->location;
  args_.info->lon = ConfigData::GetInstance()->GetTestLon();
  args_.info->lat = ConfigData::GetInstance()->GetTestLat();

  /* Launch clock thread */
  if (pthread_create(&clock_thread_, nullptr, ClockUpdateThread, (void *)&args_)) {
    LOG(ERROR) << "Error creating thread";
    return;
  }
  LOG(INFO) << "Clock thread started";
}

GvaStatusTypes ScreenGva::Update() {
  unsigned char *texture = nullptr;

  // Reset the Drawing context, must be Reset before reDrawing the screen
  Reset();
  GetTouch()->Reset();

  // Draw the background canvas first
  if (screen_->canvas.blackout) {
    // Set background black
    SetColourForeground(HMI_BLACK);
    SetColourBackground(HMI_BLACK);
    DrawRectangle(0, 0, width_, height_, true);
  } else {
    switch (screen_->canvas.bufferType) {
      case SurfaceType::kSurfaceCairo:
        TextureRGB(0, 0, screen_->canvas.surface);
        break;
      case SurfaceType::kSurfaceFile:
        TextureRGB(0, 0, screen_->canvas.buffer);
        TextureRGB(0, 0, texture, screen_->canvas.filename);
        break;
      default:
        // Set background green
        SetColourForeground(config_->GetThemeBackground());
        SetColourBackground(config_->GetThemeBackground());
        DrawRectangle(0, 0, width_, height_, true);
        break;
    }
  }

  // If BLACKOUT then nothing to render
  if (screen_->canvas.blackout) {
    //
    // Refresh display
    //
    Draw();
    LOG(INFO) << "Blackout Requested";
    last_screen_ = *screen_;
    return GvaStatusTypes::kGvaSuccess;
  }

  // Setup and Draw the status bar, one row table
  if (screen_->status_bar->visible) {
    WidgetTable status_bar_table(*(RendererGva *)this, GetTouch(),
                                 ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

    // Setup and Draw the status bar, one row table
    std::array<uint32_t, 7> widths = {23, 8, 37, 8, 8, 8, 8};
    status_bar_table.SetVisible(true);
    status_bar_table.SetX(1);
    status_bar_table.SetY(screen_->status_bar->y);
    status_bar_table.SetWidth(640);
    status_bar_table.SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
    status_bar_table.AddRow();

    // Update the status bar cells
    screen_->status_bar->labels[0].text = args_.clockString;
    screen_->status_bar->labels[1].text = args_.locationFormat;
    screen_->status_bar->labels[2].text = args_.locationString;
    for (uint32_t i = 0; i < 7; i++) {
      status_bar_table.AddCell(screen_->status_bar->labels[i].text, widths[i], widget::CellAlignType::kAlignLeft);
    }
    status_bar_table.Draw();
  }

  // Generic message box
  if (screen_->message.visible) {
    WidgetTable message_box_table(*(RendererGva *)this, GetTouch(),
                                  ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
    message_box_table.SetX((gva::kMinimumWidth / 2) - 150);
    message_box_table.SetY(220);
    message_box_table.SetWidth(300);
    message_box_table.SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

    uint32_t background = gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled();

    message_box_table.AddRow();
    message_box_table.AddCell("System Information", 100, widget::CellAlignType::kAlignCentre, background);

    message_box_table.AddRow();
    message_box_table.AddCell(screen_->message.detail.text, 100, widget::CellAlignType::kAlignCentre, background);

    message_box_table.Draw();

    DrawIcon(screen_->message.icon, 320 - 150 + 300 - 17, 229, 11, 11);
  }

  /// Iterate over all widgets and draw the visible ones
  for (auto const &[key, val] : widget_list_) {
    if (val->GetVisible()) val->Draw();
  }

  //
  // Refresh display
  //
  Draw();
  last_screen_ = *screen_;

  return GvaStatusTypes::kGvaSuccess;
}

WidgetX *ScreenGva::GetWidget(widget::WidgetEnum widget) { return widget_list_[widget].get(); }

}  // namespace gva
