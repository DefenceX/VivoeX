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
#include "src/gva_functions_common.h"
#include "widgets/alarm_indicator.h"
#include "widgets/bottom_labels.h"
#include "widgets/compass.h"
#include "widgets/keyboard.h"
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
  logGva::log(tmp, LOG_INFO);

  // Initalise the pasert for NMEA
  nmea_zero_INFO(&info_);
  nmea_parser_init(&parser_);

  // Open File Descriptor
  gps_ = open(screen->info.gpsDevice.c_str(), O_RDWR | O_NONBLOCK | O_NDELAY);

  if (gps_ > 0) {
    logGva::log("GPS Opened " + screen->info.gpsDevice, LOG_INFO);
  } else {
    logGva::log("GPS Error Opening device " + screen->info.gpsDevice, LOG_ERROR);
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
  StartClock(screen_->status_bar);

  // WidgetTo
  //  Setup the required widgets
  //
  RendererGva *renderer = this;
  TouchGva *touch = GetTouch();

  // Here we need to add all the possible screen widgets to the widget list, at this point they are uninitialised
  widget_list_[KWidgetTypeCompass] = std::make_shared<WidgetPlanPositionIndicator>(*renderer);
  widget_list_[KWidgetTypeKeyboard] = std::make_shared<WidgetKeyboard>(*renderer);
  widget_list_[KWidgetTypeAlarmIndicator] = std::make_shared<WidgetAlarmIndicator>(*renderer);
  widget_list_[KWidgetTypeTopLabels] = std::make_shared<WidgetTopLabels>(*renderer, touch);
  widget_list_[KWidgetTypeBottomLabels] = std::make_shared<WidgetBottomLabels>(*renderer, touch);
  widget_list_[KWidgetTypeLeftLabels] = std::make_shared<WidgetSideLabels>(*renderer, touch);
  widget_list_[KWidgetTypeRightLabels] = std::make_shared<WidgetSideLabels>(*renderer, touch);
}

ScreenGva::~ScreenGva() {
  args_.active = false;
  pthread_join(clock_thread_, 0);
  nmea_parser_destroy(&parser_);
  close(gps_);
  if (gps_) logGva::log("GPS closed", LOG_INFO);
  logGva::log("GVA screen finalized.", LOG_INFO);
  logGva::finish();
}

void *ClockUpdate(void *arg) {
  args *a = (args *)arg;
  time_t t;
  struct tm *tm;
  char c;
  char buffer[MAX_NMEA] = {0};
  char tmp[MAX_NMEA] = {0};

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
          //             pruint32_tf("0x%02x ", c);
        }
        if (i == MAX_NMEA) break;
      }
      buffer[i - 1] = 0;
      sprintf(tmp, "GPS NMEA %s", buffer);
      logGva::log(tmp, LOG_INFO);

      sprintf(tmp, "%s\r\n", buffer);
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
          double x, y;
          GeographicLib::UTMUPS::Forward(a->info->lat, a->info->lon, zone, northp, x, y);
          std::string mgrs;
          GeographicLib::MGRS::Forward(zone, northp, x, y, a->info->lat, 5, mgrs);
          a->locationFormat, "MGRS";
          a->locationString = mgrs;
        } break;
      }
    }
    usleep(1000000);
  }
}

void ScreenGva::StartClock(StatusBar *barData) {
  pthread_t clock_thread_;
  args_.active = true;
  args_.clockString = barData->labels[0].text;
  args_.locationFormat = barData->labels[1].text;
  args_.locationString = barData->labels[2].text;
  args_.parser = &parser_;
  args_.info = &info_;
  args_.gps = &gps_;
  args_.screen = this;
  args_.location = &barData->location;
  args_.info->lon = DUMMY_LON;
  args_.info->lat = DUMMY_LAT;

  /* Launch clock thread */
  if (pthread_create(&clock_thread_, NULL, ClockUpdate, (void *)&args_)) {
    logGva::log("Error creating thread", LOG_ERROR);
    return;
  }
  logGva::log("uint32_ternal clock thread started", LOG_INFO);
}

GvaStatusTypes ScreenGva::Update() {
  char *texture = 0;

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
    logGva::log("Blackout Requested", LOG_INFO);
    last_screen_ = *screen_;
    return GvaStatusTypes::kGvaSuccess;
  }

  // Draw label
  if (screen_->label.visible) {
    SetTextFontSize(screen_->label.fontSize);
    DrawLabel(screen_->label.x, screen_->label.y, screen_->label.text);
  }

  // Draw the LEFT bezel labels
  if (screen_->function_left.visible) {
    auto widget = (WidgetSideLabels *)GetWidget(KWidgetTypeLeftLabels);
    widget->SetLabels(&screen_->function_left.labels);
    widget->Draw();
  }

  // Draw the RIGHT bezel labels
  if (screen_->function_right.visible) {
    auto widget = (WidgetSideLabels *)GetWidget(KWidgetTypeRightLabels);
    widget->SetLabels(&screen_->function_right.labels);
    widget->SetX(DEFAULT_WIDTH - 100 - 1);
    widget->Draw();
  }

  // Draw the TOP bezel labels
  if (screen_->function_top->visible) {
    auto widget = (WidgetTopLabels *)GetWidget(KWidgetTypeTopLabels);
    widget->SetY(DEFAULT_HEIGHT - 11);
    widget->SetLabels(&screen_->function_top->labels);
    widget->Draw();
  }

  // Draw the maintenance mode indicator
  if (screen_->info.mode == ScreenMode::kModeMaintinance) {
    DrawMode();
  }

  // Draw the onscreen KEYBOARD
  if (widget_list_[KWidgetTypeKeyboard]->GetVisible()) {
    widget_list_[KWidgetTypeKeyboard]->Draw();
  }

  // Setup and Draw the status bar, one row table
  if (screen_->status_bar->visible) {
    uint32_t i = 0;
    // Setup and Draw the status bar, one row table
    uint32_t widths[7] = {23, 8, 37, 8, 8, 8, 8};
    GvaTable table(1, screen_->status_bar->y, 640);
    table.SetFontName(config_->GetThemeFont());
    GvaRow newrow;

    // Use theme colours
    GvaColourType border = {UnpackRed(config_->GetThemeStatusBorder()), UnpackGreen(config_->GetThemeStatusBorder()),
                            UnpackBlue(config_->GetThemeStatusBorder())};
    GvaColourType background = {UnpackRed(config_->GetThemeStatusBackground()),
                                UnpackGreen(config_->GetThemeStatusBackground()),
                                UnpackBlue(config_->GetThemeStatusBackground())};
    GvaColourType text = {UnpackRed(config_->GetThemeStatusText()), UnpackGreen(config_->GetThemeStatusText()),
                          UnpackBlue(config_->GetThemeStatusText())};

    for (i = 0; i < 7; i++) {
      CellAlignType align = CellAlignType::kAlignLeft;
      if (i == 1) align = CellAlignType::kAlignCentre;
      GvaCell cell = {screen_->status_bar->labels[i].text, align, border, background, text, WeightType::kWeightBold};
      newrow.addCell(cell, widths[i]);
    }
    table.AddRow(newrow);
    DrawTable(&table);
  }

  // TODO : Draw the alarms if any (Mock up)
  widget_list_[KWidgetTypeAlarmIndicator]->Draw();

  // Setup and Draw the alarms
  if (screen_->table.visible_) {
    GvaTable table(screen_->table.x_, screen_->table.y_ + 33, screen_->table.width_);
    table.SetFontName(config_->GetThemeFont());
    table.border_ = 1;
    for (auto row : screen_->table.rows_) {
      GvaRow newrow;
      RgbUnpackedType f, b, o;
      // for (uint32_t cell = 0; cell < screen_->table.rows_[row].cell_count_; cell++) {

      for (auto cell : row.cells_) {
        f = UnpackRgb(cell.GetForegroundColour());
        b = UnpackRgb(cell.GetBackgroundColour());

        // Choose colour for cell border
        if (row.GetHighlighted() == false) {
          o = UnpackRgb(cell.GetOutlineColour());
        } else {
          o = UnpackRgb(cell.GetHighlightColour());
        }

        newrow.addCell({cell.GetText(), cell.GetCellAlignment(), o.r, o.g, o.b,  // Outline
                        b.r, b.g, b.b,                                           // Background
                        f.r, f.g, f.b,                                           // Foreground
                        row.GetFontWeight()},
                       cell.GetWidth());
      }
      table.AddRow(newrow);
    }

    DrawTable(&table);
  }

  // Draw PPI (Plan Position Indicator)
  widget_list_[KWidgetTypeCompass]->Draw();

  if (screen_->control->visible) {
    auto widget = (WidgetBottomLabels *)GetWidget(KWidgetTypeBottomLabels);
    widget->SetLabels(&screen_->control->labels);
    widget->Draw();
  }

  // Generic message box
  if (screen_->message.visible) {
    GvaTable table(320 - 150, 260, 300);
    table.SetFontName(config_->GetThemeFont());
    GvaRow newrow;
    GvaRow newrow1;

    table.border_ = config_->GetThemeLabelBorderThickness();

    uint32_t background = gva::ConfigData::GetInstance()->GetThemeBackground();
    newrow.addCell({screen_->message.brief.text,
                    CellAlignType::kAlignCentre,
                    {HMI_WHITE},
                    {background << 16 && 0xff, background << 8 && 0xff, background && 0xff},
                    {HMI_WHITE},
                    WeightType::kWeightBold},
                   100);
    table.AddRow(newrow);

    newrow1.addCell({screen_->message.detail.text,
                     CellAlignType::kAlignCentre,
                     {HMI_WHITE},
                     {background << 16 && 0xff, background << 8 && 0xff, background && 0xff},
                     {HMI_WHITE},
                     WeightType::kWeightNormal},
                    100);
    table.AddRow(newrow1);
    DrawTable(&table);

    DrawIcon(screen_->message.icon, 320 - 150 + 300 - 17, 270, 11, 11);
  }

  //
  // Refresh display
  //
  Draw();
  last_screen_ = *screen_;
}

WidgetX *ScreenGva::GetWidget(WidgetEnum widget) { return widget_list_[widget].get(); }

}  // namespace gva
