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
/// \brief Manage the touch screen events
///
/// \file trace.h
///

#ifndef HMI_DISPLAY_UPDATER_UPDATER_H_
#define HMI_DISPLAY_UPDATER_UPDATER_H_

#include <string>

#include "src/widgets/widget.h"

namespace gva {

class UpdaterBase {
 public:
  ///
  /// \brief Construct a new Updater object
  ///
  /// \param id The HMI identity, will only get updates for this ID.
  ///
  UpdaterBase(uint64_t id) : id_(id){};

  virtual ~UpdaterBase() = default;

  ///
  /// \brief Update the HMI state
  ///
  /// \param state The new state
  ///
  virtual void UpdateState(std::string state) = 0;

  ///
  /// \brief Process at HMI event
  ///
  /// \param event
  ///
  virtual void Event(std::string event) = 0;

 private:
  uint64_t id_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_UPDATER_UPDATER_H_