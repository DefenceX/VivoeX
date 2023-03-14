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
/// \file updater.h
///

#ifndef HMI_DISPLAY_UPDATER_EXAMPLE_UPDATER_H_
#define HMI_DISPLAY_UPDATER_EXAMPLE_UPDATER_H_

#include <string>

#include "include/updater_base.h"

namespace gva {

class Updater : public UpdaterBase {
 public:
  ///
  /// \brief Construct a new Updater object
  ///
  /// \param id The HMI identity, will only get updates for this ID.
  ///
  Updater(uint64_t id);

  ~Updater();

  ///
  /// \brief Register the widgets to be updated
  ///
  ///
  void RegisterWidgets(std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>>& widget_list);

  ///
  /// \brief Update the HMI state
  ///
  /// \param state The new state
  ///
  void UpdateState(std::string state) final;

  ///
  /// \brief Process at HMI event
  ///
  /// \param event
  ///
  void Event(std::string event) final;

  ///
  /// \brief The updater thread
  ///
  /// \param ptr The widgets list pointer
  /// \return void*
  ///
  static void* WidgetUpdaterThread(void* ptr);

 private:
  std::map<widget::WidgetEnum, std::shared_ptr<WidgetX>>* widget_list_ = nullptr;
  int thread_id_ = 0;
  pthread_t thread_ = 0;

  ///
  /// \brief Generate a sine wave
  ///
  /// \param sample The sample being requested
  /// \param sampleRate i.e. 44100.0
  /// \param frequency i.e. 440.0;
  /// \return int The sample value. amplitude is 0-100
  ///
  static int GenerateSineWave(int sample, double sampleRate = 44100, double frequency = 440.0);
};

}  // namespace gva

#endif  //  HMI_DISPLAY_UPDATER_EXAMPLE_UPDATER_H_
