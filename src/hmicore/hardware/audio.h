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
///
/// \file audio.h
///

#ifndef HMICORE_HARDWARE_AUDIO_H_
#define HMICORE_HARDWARE_AUDIO_H_

#include <portaudio.h>
#include <sndfile.h>

#include <string>

#include "hmicore/hardware/sample.h"

namespace gva {

class AudioFunctions {
 public:
  struct CallbackData {
    SNDFILE *file;
    SF_INFO info;
  };

  ///
  /// \brief Construct a new Audio Functions object
  ///
  ///
  AudioFunctions();

  ///
  /// \brief Destroy the Audio Functions object
  ///
  ///
  ~AudioFunctions();

  AudioFunctions &operator=(const AudioFunctions &) = delete;
  AudioFunctions(const AudioFunctions &) = delete;

  ///
  /// \brief Portaudio callback for simple audio
  ///
  /// \param input
  /// \param output
  /// \param frameCount
  /// \param timeInfo
  /// \param statusFlags
  /// \param userData
  /// \return int
  ///
  static int Callback(const void *input, void *output, unsigned long frameCount,  // NOLINT
                      const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData);

  ///
  /// \brief Play a given file
  ///
  /// \param filename
  /// \return int
  ///
  int Play(AudioSampleBase &sample);

  ///
  /// \brief Play threat tone
  ///
  ///
  void PlayThreat();

  ///
  /// \brief Play Caution tone
  ///
  ///
  void PlayCaution();

  ///
  /// \brief Play Warning
  ///
  ///
  void PlayWarning();

  const uint32_t kFramesPerBuffer = 512;

 private:
#if _WIN32
  const std::string kThreatFilename = "../sounds/threat.wav";
  const std::string kCautionFilename = "../sounds/caution.wav";
  const std::string kWarningFilename = "../sounds/warning.wav";
#else
  const std::string kThreatFilename = "/opt/gva/hmi/sounds/threat.wav";
  const std::string kCautionFilename = "/opt/gva/hmi/sounds/caution.wav";
  const std::string kWarningFilename = "/opt/gva/hmi/sounds/warning.wav";
#endif
  AudioSample threat_ = AudioSample(kThreatFilename);
  AudioSample caution_ = AudioSample(kCautionFilename);
  AudioSample warning_ = AudioSample(kWarningFilename);
  PaStream *stream_ = nullptr;

  static void *AlsaLog(const char *file, int line, const char *function, int err, const char *fmt, ...);
};

}  // namespace gva

#endif  // HMICORE_HARDWARE_AUDIO_H_
