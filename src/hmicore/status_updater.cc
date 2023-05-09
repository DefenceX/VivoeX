//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file status_updater.cc
///

#include "hmicore/status_updater.h"

#include <glog/logging.h>
#include <time.h>

#include <GeographicLib/MGRS.hpp>
#include <GeographicLib/UTMUPS.hpp>
#include <iomanip>
#include <sstream>

#include "hmicore/gva_functions_common.h"
#include "hmicore/screen_gva.h"

namespace gva {

void StatusUpdater::UpdateClock(std::shared_ptr<WidgetStatusBar> statusBar) const {
  std::tm localTime;
  GetLocalTime(&localTime);

  std::stringstream stream;
  stream << std::put_time(&localTime, "%m/%d/%Y %H:%M:%S");

  statusBar->UpdateClock(stream.str());
}

void StatusUpdater::ParseGpsData(const int *gpsFd, nmeaINFO *info, nmeaPARSER *parser,
                                 const LocationType &location) const {
  if (gpsFd == nullptr || *gpsFd <= 0) {
    return;
  }

  std::array<char, kMaxNmea> buffer{};
  auto bytesRead = read(*gpsFd, buffer.data(), buffer.size());
  if (bytesRead <= 0) {
    return;
  }

  auto start = std::find(buffer.begin(), buffer.end(), '$');
  if (start == buffer.end()) {
    return;
  }

  auto end = std::find(start, buffer.end(), '\n');
  if (end == buffer.end()) {
    return;
  }

  const std::string nmea(start, end);
  LOG(INFO) << "GPS NMEA " << nmea;

  const std::string tmp = nmea + "\r\n";
  info->lon = location.lon;
  info->lat = location.lat;
  nmea_parse(parser, tmp.c_str(), (int)tmp.size(), info);
  info->lat = ToDegrees(static_cast<float>(info->lat));
  info->lon = ToDegrees(static_cast<float>(info->lon));
}

void StatusUpdater::UpdateLocation(std::shared_ptr<WidgetStatusBar> statusBar, const nmeaINFO &info,
                                   const LocationType &location) const {
  switch (location.locationFormat) {
    case LocationEnum::kLocationFormatLongLat: {
      std::stringstream stream;
      stream << std::fixed << std::setprecision(2) << "Lat:" << info.lat << " Lon:" << info.lon << " [" << info.sig
             << "]" << info.fix;
      statusBar->UpdateLocationFormat("LON/LAT");
      statusBar->UpdateLocation(stream.str());
      break;
    }
    case LocationEnum::kLocationFormatMgrs: {
      int zone;
      bool northp;
      double x;
      double y;
      GeographicLib::UTMUPS::Forward(info.lat, info.lon, zone, northp, x, y);
      std::string mgrs;
      GeographicLib::MGRS::Forward(zone, northp, x, y, info.lat, 5, mgrs);
      statusBar->UpdateLocationFormat("MGRS");
      statusBar->UpdateLocation(mgrs);
      break;
    }
    default:
      break;
  }
}

void StatusUpdater::ClockUpdate(ClockArgs *args) {
  UpdateClock(args->status_bar);

  ParseGpsData(args->gps, args->info, args->parser, args->location);

  if (args->info->lon != 0 && args->info->lat != 0) {
    UpdateLocation(args->status_bar, *args->info, args->location);
  }

  gva::EventsGva::CreateRefreshEvent();
}

void StatusUpdater::GetLocalTime(std::tm *localTime) const {
  const auto now = std::time(nullptr);
#if defined(_WIN32)
  localtime_s(localTime, &now);
#else
  localtime_r(&now, localTime);
#endif
}
}  // namespace gva
