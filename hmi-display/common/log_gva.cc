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
/// \brief A simple GVA logging module
///
/// \file log_gva.cc
///

#include "log_gva.h"

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>

namespace gva {

FILE* logGva::m_errorfd;

void logGva::log(const std::string message, const uint16_t type) { log(message.c_str(), type); }

void logGva::log(const char* message, const uint16_t type) {
  struct sysinfo info;
  char msgType[4] = "???";

  sysinfo(&info);
  switch (type) {
    case LOG_DEBUG:
      strcpy(msgType, "DBG");
      break;
    case LOG_INFO:
      strcpy(msgType, "INF");
      break;
    case LOG_WARNING:
      strcpy(msgType, "WAR");
      break;
    case LOG_ERROR:
      strcpy(msgType, "ERR");
      break;
  }

#if !DEBUG
  /** Discard debug message if DEBUG not enabled */
  if (type == LOG_DEBUG) return;
#endif
  if (!m_errorfd) {
    m_errorfd = fopen("/var/log/gva.log", "w");
  }
  fprintf(m_errorfd, "[%ld] *%s* %s\n", info.uptime, msgType, message);
  fflush(m_errorfd);
  if (type == LOG_ERROR) {
    std::cout << message << std::endl;
  }
}

void logGva::finish() { fclose(m_errorfd); }

}  // namespace gva
