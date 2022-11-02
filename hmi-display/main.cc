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
/// \brief
///
/// \file main.cc
///

#include <unistd.h>

#include <iostream>
#include <string>

#include "alarm_indicator.h"
#include "compass.h"
#include "events_gva.h"
#include "gva.h"
#include "gva_application.h"
#include "gva_video_rtp_yuv.h"
#include "hmi_gva.h"
#include "keyboard.h"
#include "log_gva.h"
#include "renderer_map.h"
#include "rtp_stream.h"

GvaApplication::Options options = {false, false, ""};

///
/// \brief Parse the command line options
///
/// \param argc Argument count
/// \param argv Argument array
/// \param opt HMI application options
///
int32_t GetOpt(int argc, char *argv[], GvaApplication::Options *opt) {
  uint32_t c = 0;

  ConfigData *configuration = gva::ConfigData::GetInstance();

  while ((c = getopt(argc, argv, "hvwclf::")) != -1) switch (c) {
      case 'v':
        cout << "Version " << MAJOR << "." << MINOR << "." << PATCH << endl;
        return 0;
      case 'w':
        opt->windowEnabled = true;
        return -1;
      case 'c':
        strcpy(opt->config, optarg);
        return -1;
      case 'l':
        printf("-l selected");
        opt->videoEnabled = true;
        break;
      case 'f':
        configuration->SetFullscreen(true);
        break;
      case 'h':
        cout << "  -c : XML config file" << endl;
        cout << "  -h : help" << endl;
        cout << "  -w : Show HMI window, for debug when no GVA display present" << endl;
        cout << "  -v : Version" << endl;
        cout << "  -l : Live video" << endl;
        cout << "  -f : Fullscreen" << endl;
        return 0;
      case '?':
        if (optopt == 'c') cerr << "Option -" << optopt << " requires an argument.\n" << endl;
        //        else if (isprint(optopt))
        //          cerr << "Unknown option `-" << c << "'" << endl;
        else
          cerr << std::hex << "Unknown option character, -h for help'" << optopt << "'." << endl;
        return 1;
      default:
        abort();
    }
  return -1;
};

// printf("File %s:%d, %s()\n", __FILE__, __LINE__, __FUNCTION__);
int main(int argc, char *argv[]) {
  uint32_t done = 0;
  uint32_t hndl;
  bool update;
  char ipaddr[] = "127.0.0.1";
  uint32_t port = 5004;

  cout << "hmi_display (By defencex.com.au)..." << endl;

  int32_t ret = GetOpt(argc, argv, &options);

  if (ret >= 0) return ret;

  GvaApplication app = GvaApplication(options, ipaddr, port);

  // Blocking call to the application constructor
  app.Exec();

  logGva::log("Exiting hmi_display...\n", LOG_INFO);
}
