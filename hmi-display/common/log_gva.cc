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
/// \file log_gva.cc
///

#include "log_gva.h"

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>

namespace gva {

FILE* logGva::m_errorfd_;
bool logGva::logfile_notfound_ = false;
std::string logGva::logfile_ = "/var/log/gva.log";

logGva::~logGva() { closelog(); }

void logGva::log(const std::string& message, const DebugLevel type) {
  struct sysinfo info;
  std::string msgType = "???";

  sysinfo(&info);
  switch (type) {
    case gva::DebugLevel::kLogDebug:
      msgType = "DBG";
      break;
    case gva::DebugLevel::kLogInfo:
      msgType = "INF";
      break;
    case gva::DebugLevel::kLogWarning:
      msgType = "WAR";
      break;
    case gva::DebugLevel::kLogError:
      msgType = "ERR";
      break;
    default:
      msgType = "UNKNOWN";
      break;
  }

#if !DEBUG
  // Discard debug message if DEBUG not enabled
  if (type == gva::DebugLevel::kLogDebug) return;
  setlogmask(LOG_UPTO(LOG_NOTICE));
#endif

  if (logfile_notfound_) {
    switch (type) {
      case gva::DebugLevel::kLogDebug:
      case gva::DebugLevel::kLogInfo:
        std::cout << message << std::endl;
        break;
      case gva::DebugLevel::kLogWarning:
      case gva::DebugLevel::kLogError:
      default:
        std::cerr << "[" + std::to_string(info.uptime) + "]" + "*" + msgType.c_str() + "* " + message.c_str()
                  << std::endl;
        break;
    }
    return;
  }

  if (!m_errorfd_) {
    m_errorfd_ = fopen(logfile_.c_str(), "w");
    openlog("vivoe-lite", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
  }
  if (m_errorfd_ != NULL) {
    fprintf(m_errorfd_, "[%ld] *%s* %s\n", info.uptime, msgType.c_str(), message.c_str());
    fflush(m_errorfd_);
    if (type == gva::DebugLevel::kLogError) {
      std::cout << message << std::endl;
      // Also add to syslog if error
      syslog(LOG_ERR, "%s", message.c_str());
    }
  } else {
    logfile_notfound_ = true;
    std::cerr << "Log file " + logfile_ + " was not found, redirecting all error messages to std::out" << std::endl;
  }
}

void logGva::finish() { fclose(m_errorfd_); }

}  // namespace gva
