//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
#include "src/trace.h"
#include "src/widgets/alarm_indicator.h"
#include "src/widgets/compass.h"
#include "src/widgets/keyboard.h"
#include "video/src/gva_video_rtp_yuv.h"

///
/// \brief Parse the command line options
///
/// \param argc Argument count
/// \param argv Argument array
/// \param opt HMI application options
///
int32_t GetOpt(int argc, char *argv[], GvaApplication::Options *opt) {
  int c = 0;

  const gva::ConfigData *configuration = gva::ConfigData::GetInstance();

  while ((c = getopt(argc, argv, "hvwclf::")) != -1) {
    switch (c) {
      case 'v':
        std::cout << "Version " << gva::kSemVerMajor << "." << gva::kSemVerMinor << "." << gva::kSemVerPatch
                  << std::endl;
        return 0;
      case 'w':
        opt->windowEnabled_ = true;
        return -1;
      case 'c':
        opt->config = optarg;
        return -1;
      case 'l':
        printf("-l selected");
        opt->videoEnabled_ = true;
        break;
      case 'f':
        configuration->SetFullscreen(true);
        break;
      case 'h':
        std::cout << "  -c : XML config file" << std::endl;
        std::cout << "  -h : help" << std::endl;
        std::cout << "  -w : Show HMI window, for debug when no GVA display present" << std::endl;
        std::cout << "  -v : Version" << std::endl;
        std::cout << "  -l : Live video" << std::endl;
        std::cout << "  -f : Fullscreen" << std::endl;
        return 0;
      case '?':
        if (optopt == 'c')
          std::cerr << "Option -" << optopt << " requires an argument.\n" << std::endl;

        else
          std::cerr << std::hex << "Unknown option character, -h for help'" << optopt << "'." << std::endl;
        return 1;
      default:
        abort();
    }
  }
  return -1;
};

int main(int argc, char *argv[]) {
  if (!google::IsGoogleLoggingInitialized()) {
    google::SetVersionString(std::to_string(gva::kSemVerMajor) + "." + std::to_string(gva::kSemVerMinor) + "." +
                             std::to_string(gva::kSemVerPatch));
    google::SetUsageMessage("HMI Display application renderer.");
    google::ParseCommandLineFlags(&argc, &argv, false);
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    LOG(ERROR) << "Initialised Google logging";
  }

  std::string ipaddr = "127.0.0.1";
  uint32_t port = 5004;

  std::cout << "hmi_display (By defencex.com.au)..." << std::endl;
  SYSLOG(INFO) << "HMI Display application started";

  tracepoint(vivoe_lite, main, 0, (char *)"Hello");

  GvaApplication::Options options = {false, false, ""};

  if (int32_t ret = GetOpt(argc, argv, &options); ret >= 0) return ret;

  auto app = GvaApplication(options, ipaddr, port);

  // Blocking call to the application constructor
  app.Exec();
  tracepoint(vivoe_lite, main, 0, (char *)"World");

  SYSLOG(INFO) << "Exiting hmi_display...\n";
  google::ShutdownGoogleLogging();
}
