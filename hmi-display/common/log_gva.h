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
//
// \file log_gva.h
//

#ifndef HMI_DISPLAY_COMMON_LOG_GVA_H_
#define HMI_DISPLAY_COMMON_LOG_GVA_H_

#include <syslog.h>

#include <iostream>
#include <string>

namespace gva {

enum class DebugLevel { kLogDebug = 0, kLogInfo, kLogWarning, kLogError };

//
///
///
class logGva {
 public:
  ///
  /// \brief Destroy the log Gva object
  ///
  ///
  ~logGva();

  ///
  /// \brief Log a message with its severity
  ///
  /// \param message Message description
  /// \param type Severity
  ///
  static void log(const std::string& message, const DebugLevel type);

  ///
  /// \brief Finalise the log
  ///
  ///
  static void finish();

 private:
  static FILE* m_errorfd_;
  static bool logfile_notfound_;
  static std::string logfile_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_COMMON_LOG_GVA_H_
