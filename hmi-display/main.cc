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
/// \file main.cc
///

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <unistd.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>

#include "rtp_stream.h"  // NOLINT
#include "src/events_gva.h"
#include "src/gva.h"
#include "src/gva_application.h"
#include "src/hmi_gva.h"
#include "src/renderer_map.h"
#include "src/widgets/alarm_indicator.h"
#include "src/widgets/compass.h"
#include "src/widgets/keyboard.h"
#include "video/src/gva_video_rtp_yuv.h"

DEFINE_bool(fullscreen, false, "Start the application fullscreen");
DEFINE_bool(live, false, "Show live video streams");

int main(int argc, char *argv[]) {
  google::SetVersionString(std::to_string(gva::kSemVerMajor) + "." + std::to_string(gva::kSemVerMinor) + "." +
                           std::to_string(gva::kSemVerPatch));
  google::SetUsageMessage(
      "Human Machine Interface (HMI) display application renderer for using in\n"
      "vehicles build on the Generic Vehicle Architecture (GVA), this is the open source\n"
      "edition and does not include any elements of the Land Data Model (LDM). Commercial\n"
      "support needed for country specific LDM");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (!google::IsGoogleLoggingInitialized()) {
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    LOG(INFO) << "Initialised Google logging";
  }

  std::string ipaddr = "127.0.0.1";
  uint32_t port = 5004;

  std::cout << "hmi_display (By defencex.com.au)..." << std::endl;
  SYSLOG(INFO) << "HMI Display application started";

  GvaApplication::Options options = {FLAGS_live, FLAGS_fullscreen, ""};

  auto app = GvaApplication(options, ipaddr, port);

  // Blocking call to the application constructor
  app.Exec();

  SYSLOG(INFO) << "Exiting hmi_display...\n";
  google::ShutdownGoogleLogging();
}
