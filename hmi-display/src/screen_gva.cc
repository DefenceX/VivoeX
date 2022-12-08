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
/// \brief The screen manager to handle all the on screen elements
///
/// \file screen_gva.cc
///

#include "src/screen_gva.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include <GeographicLib/LambertConformalConic.hpp>
#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "common/debug.h"
#include "common/log_gva.h"
#include "src/gva.h"
#include "src/gva_functions_common.h"
#include "widgets/alarm_indicator.h"
#include "widgets/bottom_labels.h"
#include "widgets/compass.h"
#include "widgets/driver/rpm_fuel.h"
#include "widgets/driver/speedometer.h"
#include "widgets/keyboard.h"
#include "widgets/mode.h"
#include "widgets/side_labels.h"
#include "widgets/top_labels.h"

#define MAX_NMEA 1000

namespace gva {

ScreenGva::ScreenGva(Screen *screen, uint32_t width, uint32_t height) : RendererGva(width, height) {
  screen_ = screen;

  char tmp[100];
  struct termios settings;

  config_ = gva::ConfigData::GetInstance();

  sprintf(tmp, "GVA screen initalised (%dx%d)", width_, height_);
  logGva::log(tmp, DebugLevel::kLogInfo);

  // Initalise the pasert for NMEA
  nmea_zero_INFO(&info_);
  nmea_parser_init(&parser_);

  // Open File Descriptor
  gps_ = open(screen->info.gpsDevice.c_str(), O_RDWR | O_NONBLOCK | O_NDELAY);

  if (gps_ > 0) {
    logGva::log("GPS Opened " + screen->info.gpsDevice, DebugLevel::kLogInfo);
  } else {
    logGva::log("GPS Error Opening device " + screen->info.gpsDevice, DebugLevel::kLogError);
  }
  tcgetattr(gps_, &settings);

  //
  // Set Baud Rate
  //
  cfsetospeed(&settings, B4800);        // baud rate
  tcsetattr(gps_, TCSANOW, &settings);  // apply the settings

  //
  // Start the Real Time Clock
  //
  StartClock(*screen_->status_bar);

  // WidgetTo
  //  Setup the required widgets
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
}

ScreenGva::~ScreenGva() {
  args_.active = false;
  pthread_join(clock_thread_, 0);
  nmea_parser_destroy(&parser_);
  close(gps_);
  if (gps_) logGva::log("GPS closed", DebugLevel::kLogInfo);
  logGva::log("GVA screen finalized.", DebugLevel::kLogInfo);
  logGva::finish();
}

void *ClockUpdate(void *arg) {
  args *a = (args *)arg;
  time_t t;
  struct tm *tm;
  char c;
  char tmp[MAX_NMEA + 2] = {0};
  char buffer[MAX_NMEA] = {0};

  while (a->active) {
    uint32_t i, ii = 0;
    t = time(NULL);
    tm = localtime(&t);
    char clock[1000];
    sprintf(clock, "%02d/%02d/%02d %02d:%02d:%02d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour,
            tm->tm_min, tm->tm_sec);
    a->clockString = clock;
    if (*a->gps > 0) {
      i = 0;
      tcflush(*a->gps, TCIOFLUSH);
      read(*a->gps, &buffer[0], 1);

      memset(buffer, 0, MAX_NMEA);
      while (buffer[0] != '$') read(*a->gps, &buffer[0], 1);
      while (buffer[i++] != '\n') {
        ii = read(*a->gps, &c, 1);
        if (ii == 1) {
          buffer[i] = c;
        }
        if (i == MAX_NMEA) break;
      }
      buffer[i - 1] = 0;
      std::string tmp_buffer = buffer;
      logGva::log("GPS NMEA " + tmp_buffer, DebugLevel::kLogInfo);

      snprintf(tmp, sizeof(tmp), "%s\r\n", buffer);
      a->info->lon = a->location->lon;
      a->info->lat = a->location->lat;
      nmea_parse(a->parser, tmp, (uint32_t)strlen(tmp), a->info);
      a->info->lat = ToDegrees(a->info->lat);
      a->info->lon = ToDegrees(a->info->lon);
    }

    if (a->info->lon && a->info->lat) {
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
    nanosleep((const struct timespec[]){{0, 1000000000L}}, NULL);
  }
  return nullptr;
}

void ScreenGva::StartClock(const StatusBar &barData) {
  pthread_t clock_thread_;
  args_.active = true;
  args_.parser = &parser_;
  args_.info = &info_;
  args_.gps = &gps_;
  args_.screen = this;
  args_.location = const_cast<LocationType *>(&barData.location);
  args_.info->lon = ConfigData::GetInstance()->GetTestLon();
  args_.info->lat = ConfigData::GetInstance()->GetTestLat();

  /* Launch clock thread */
  if (pthread_create(&clock_thread_, NULL, ClockUpdate, (void *)&args_)) {
    logGva::log("Error creating thread", DebugLevel::kLogError);
    return;
  }
  logGva::log("Clock thread started", DebugLevel::kLogInfo);
}

GvaStatusTypes ScreenGva::Update() {
  unsigned char *texture = 0;

  // Reset the Drawing context, must be Reset before reDrawing the screen
  Reset();
  GetTouch()->Reset();

  // Draw the background canvas first
  switch (screen_->canvas.bufferType) {
    case SurfaceType::kSurfaceCairo:
      TextureRGB(0, 0, screen_->canvas.surface);
      break;
    case SurfaceType::kSurfaceFile:
      TextureRGB(0, 0, screen_->canvas.buffer);
      TextureRGB(0, 0, texture, screen_->canvas.filename);
      break;
    default:
    case SurfaceType::kSurfaceNone:
      // Set background green
      SetColourForeground(config_->GetThemeBackground());
      SetColourBackground(config_->GetThemeBackground());
      DrawRectangle(0, 0, width_, height_, true);
      break;
    case SurfaceType::kSurfaceBlackout:
      // Set background black
      SetColourForeground(HMI_BLACK);
      SetColourBackground(HMI_BLACK);
      DrawRectangle(0, 0, width_, height_, true);
      break;
  }

  // If BLACKOUT then nothing to render
  if (screen_->info.mode == ScreenMode::kModeBlackout) {
    //
    // Refresh display
    //
    Draw();
    logGva::log("Blackout Requested", DebugLevel::kLogInfo);
    last_screen_ = *screen_;
    return GvaStatusTypes::kGvaSuccess;
  }

  // Draw the LEFT bezel labels
  if (screen_->function_left.visible) {
    auto widget = (WidgetSideLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeLeftLabels);
    widget->SetLabels(&screen_->function_left.labels);
    widget->Draw();
  }

  // Draw the RIGHT bezel labels
  if (screen_->function_right.visible) {
    auto widget = (WidgetSideLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeRightLabels);
    widget->SetLabels(&screen_->function_right.labels);
    widget->SetX(kMinimumWidth - 100 - 1);
    widget->Draw();
  }

  // Draw the TOP bezel labels
  if (screen_->function_top->visible) {
    auto widget = (WidgetTopLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeTopLabels);
    widget->SetY(2);
    widget->SetLabels(&screen_->function_top->labels);
    widget->Draw();
  }

  // Draw the maintenance mode indicator
  if (screen_->info.mode == ScreenMode::kModeMaintinance) {
    auto widget = (WidgetMode *)GetWidget(widget::WidgetEnum::KWidgetTypeMode);
    widget->Draw();
  }

  // Draw the onscreen KEYBOARD
  widget_list_[widget::WidgetEnum::KWidgetTypeKeyboard]->Draw();

  // Drivers Aids
  widget_list_[widget::WidgetEnum::kWidgetTypeDialSpeedometer]->Draw();
  widget_list_[widget::WidgetEnum::KWidgetTypeDialRpmFuel]->Draw();

  // Setup and Draw the status bar, one row table
  if (screen_->status_bar->visible) {
    WidgetTable status_bar_table(*(RendererGva *)this, GetTouch(),
                                 ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
    uint32_t i = 0;
    // Setup and Draw the status bar, one row table
    uint32_t widths[7] = {23, 8, 37, 8, 8, 8, 8};
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
    for (i = 0; i < 7; i++) {
      status_bar_table.AddCell(screen_->status_bar->labels[i].text, widths[i], widget::CellAlignType::kAlignLeft);
    }
    status_bar_table.Draw();
  }

  // TODO : Draw the alarms if any (Mock up)
  if (widget_list_[widget::WidgetEnum::KWidgetTypeAlarmIndicator]->GetVisible()) {
    widget_list_[widget::WidgetEnum::KWidgetTypeAlarmIndicator]->Draw();
  }

  // Setup and Draw the alarms
  if (widget_list_[widget::WidgetEnum::KWidgetTypeTable]->GetVisible()) {
    auto table_widget = (WidgetTable *)GetWidget(widget::WidgetEnum::KWidgetTypeTable);

    table_widget->Draw();
  }

  // Draw PPI (Plan Position Indicator)
  widget_list_[widget::WidgetEnum::KWidgetTypeCompass]->Draw();

  // Draw the control labels at the bottom of the screen
  if (screen_->control->visible_) {
    auto widget = (WidgetBottomLabels *)GetWidget(widget::WidgetEnum::KWidgetTypeBottomLabels);
    widget->SetLabels(&screen_->control->labels_);
    widget->Draw();
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

  //
  // Refresh display
  //
  Draw();
  last_screen_ = *screen_;

  return GvaStatusTypes::kGvaSuccess;
}

WidgetX *ScreenGva::GetWidget(widget::WidgetEnum widget) { return widget_list_[widget].get(); }

}  // namespace gva
