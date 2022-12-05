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
