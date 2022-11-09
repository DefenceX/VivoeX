#ifndef LOG_GVA_H
#define LOG_GVA_H
#include <stdio.h>

#include <iostream>
#include <string>

namespace gva {

enum { LOG_DEBUG = 0, LOG_INFO, LOG_WARNING, LOG_ERROR };

static FILE* m_errorfd;

class logGva {
 public:
  static void log(std::string message, int type);
  static void log(char* message, int type);
  static void finish();

 private:
};

}  // namespace gva

#endif
