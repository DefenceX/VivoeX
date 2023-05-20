//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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

///
/// \brief The Audio Functions class
///
///
class AudioFunctions {
 public:
  /// The callback data
  struct CallbackData {
    /// The audio sample file
    SNDFILE *file;
    /// The audio sample info
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

  ///
  /// \brief Construct a new Audio Functions object
  ///
  ///
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
  /// \param sample The audio sample
  /// \return int
  ///
  int Play(AudioSampleBase *sample);

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

  /// Number of frames per buffer
  const uint32_t kFramesPerBuffer = 512;

 private:
#if _WIN32
  /// The threat audio sample filename
  const std::string kThreatFilename = "../sounds/threat.wav";
  /// The caution audio sample filename
  const std::string kCautionFilename = "../sounds/caution.wav";
  /// The warning audio sample filename
  const std::string kWarningFilename = "../sounds/warning.wav";
#else
  /// The threat audio sample filename
  const std::string kThreatFilename = "/opt/gva/hmi/sounds/threat.wav";
  /// The caution audio sample filename
  const std::string kCautionFilename = "/opt/gva/hmi/sounds/caution.wav";
  /// The warning audio sample filename
  const std::string kWarningFilename = "/opt/gva/hmi/sounds/warning.wav";
#endif
  /// The threat audio sample
  AudioSample threat_ = AudioSample(kThreatFilename);
  /// The caution audio sample
  AudioSample caution_ = AudioSample(kCautionFilename);
  /// The warning audio sample
  AudioSample warning_ = AudioSample(kWarningFilename);
  /// The portaudio stream
  PaStream *stream_ = nullptr;

  ///
  /// \brief Log the ALSA error
  ///
  /// \param file The file name
  /// \param line The line number
  /// \param function The callback
  /// \param err The error code
  /// \param fmt The format string
  /// \param ...
  /// \return void*
  ///
  static void *AlsaLog(const char *file, int line, const char *function, int err, const char *fmt, ...);
};

}  // namespace gva

#endif  // HMICORE_HARDWARE_AUDIO_H_
