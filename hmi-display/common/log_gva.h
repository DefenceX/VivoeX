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
/// \file log_gva.h
///

#ifndef HMI_DISPLAY_COMMON_LOG_GVA_H_
#define HMI_DISPLAY_COMMON_LOG_GVA_H_

#define LOG_GVA_H
#include <stdio.h>

#include <iostream>
#include <string>

namespace gva {

enum { LOG_DEBUG = 0, LOG_INFO, LOG_WARNING, LOG_ERROR };

static FILE* m_errorfd;

class logGva {
 public:
  ///
  /// \brief Log a message with its severity
  ///
  /// \param message Message description
  /// \param type Severity
  ///
  static void log(const std::string message, uint16_t type);

  ///
  /// \brief Log a message with its severity
  ///
  /// \param message Message description
  /// \param type Severity
  ///
  static void log(const char* message, uint16_t type);

  ///
  /// \brief Finalise the log
  ///
  ///
  static void finish();

 private:
};

}  // namespace gva

#endif  // HMI_DISPLAY_COMMON_LOG_GVA_H_
