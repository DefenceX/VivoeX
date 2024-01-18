//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file main.cc
///

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <raw/rtpvraw_depayloader.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

#include "hmicore/events_gva.h"
#include "hmicore/gva.h"
#include "hmicore/hmi_gva.h"
#include "hmicore/renderer_map.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/keyboard.h"
#include "hmicore/widgets/plan_position_indicator.h"
#include "hmidisplay/gva_application.h"

/// Flag for fullscreen
DEFINE_bool(fullscreen, false, "Start the application fullscreen");
/// Flag for live video
DEFINE_bool(live, false, "Show live video streams");

int main(int argc, char* argv[]) {
  google::SetUsageMessage(
      "Human Machine Interface (HMI) display application renderer for using in\n"
      "vehicles build on the Generic Vehicle Architecture (GVA), this is the open source\n"
      "edition and does not include any elements of the Land Data Model (LDM). Commercial\n"
      "support needed for country specific LDM");

  // Initialize Google's logging library.
  google::InitGoogleLogging(argv[0]);
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::SetVersionString(std::to_string(gva::kSemVerMajor) + "." + std::to_string(gva::kSemVerMinor) + "." +
                           std::to_string(gva::kSemVerPatch));

  google::InstallFailureSignalHandler();
  LOG(INFO) << "Initialised Google logging";

  std::string ipaddr = "127.0.0.1";
  uint32_t port = 5004;

  std::cout << "hmi_display (By defencex.com.au)..." << std::endl;
  SYSLOG(INFO) << "HMI Display application started";

  GvaApplication::Options options = {FLAGS_live, FLAGS_fullscreen, ""};

  auto app = GvaApplication(options, ipaddr, port);

  // Blocking call to the application constructor
  app.Exec();

  gva::Updater::running_ = false;
  gva::ScreenGva::args_.active = false;

  SYSLOG(INFO) << "Exiting hmi_display...\n";

  // wait 100ms for threads to exit
  nanosleep((const struct timespec[]){{0, 100000000L}}, nullptr);

  google::ShutdownGoogleLogging();
}
