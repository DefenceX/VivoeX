//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file audio.cc
///

#include "hmicore/hardware/audio.h"

#ifndef _WIN32
#include <alsa/asoundlib.h>
#endif
#include <glog/logging.h>

#include <string>

namespace gva {

#ifndef _WIN32
void *AudioFunctions::AlsaLog(const char *file, int line, const char *function, int err, const char *fmt, ...) {
  LOG(INFO) << "PortAudio info: " << file << ":" << line << " " << function << " " << err << " " << fmt << "\n";
  return nullptr;
}
#endif

AudioFunctions::AudioFunctions() {
  PaError error;

#ifndef _WIN32
  snd_lib_error_set_handler((snd_lib_error_handler_t)AudioFunctions::AlsaLog);
#endif

  // init portaudio
  error = Pa_Initialize();

  if (error != paNoError) {
    LOG(ERROR) << "Problem initializing";
  }
}

AudioFunctions::~AudioFunctions() {
  PaError error;
  error = Pa_Terminate();
  if (error != paNoError) {
    LOG(ERROR) << "Problem terminating";
  }
}

int AudioFunctions::Callback(const void *input [[maybe_unused]], void *output, unsigned long frameCount,
                             const PaStreamCallbackTimeInfo *timeInfo [[maybe_unused]],
                             PaStreamCallbackFlags statusFlags [[maybe_unused]], void *userData) {  // NOLINT
  uint8_t *out;
  auto *sample_data = (AudioSampleBase *)userData;
  sf_count_t num_read;

  out = (uint8_t *)output;
  sample_data = (AudioSampleBase *)userData;
  num_read = sample_data->ReadBytes(out, 512);

  //  If we couldn't read a full frameCount of samples we've reached EOF
  if (num_read < (int)frameCount) {
    sample_data->Seek(0);  // go to start of file ready for next play
    return paComplete;
  }

  return paContinue;
}

#if _WIN32
const std::string kThreatFilename = "../sounds/threat.wav";
const std::string kCautionFilename = "../sounds/caution.wav";
const std::string kWarningFilename = "../sounds/warning.wav";
#else
const std::string kThreatFilename = "/opt/gva/hmi/sounds/threat.wav";
const std::string kCautionFilename = "/opt/gva/hmi/sounds/caution.wav";
const std::string kWarningFilename = "/opt/gva/hmi/sounds/warning.wav";
#endif

void AudioFunctions::PlayThreat() { Play(&threat_); }
void AudioFunctions::PlayCaution() { Play(&caution_); }
void AudioFunctions::PlayWarning() { Play(&warning_); }

int AudioFunctions::Play(AudioSampleBase *sample) {
  PaError error;

  // Go to start of file, may have been played before
  sample->Seek(0);

  if (stream_ != nullptr) {
    Pa_CloseStream(stream_);
    stream_ = nullptr;
  }

  // Open PaStream with values read from the sample
  error =
      Pa_OpenDefaultStream(&stream_, 0,                                                     // no input
                           sample->GetChannels(),                                           // stereo out
                           paFloat32,                                                       // floating point
                           sample->GetSamplingRate(), kFramesPerBuffer, Callback, sample);  // our sndfile data struct
  if (error != paNoError) {
    LOG(ERROR) << "Problem opening Default Stream";
    return 1;
  }

  // Start the stream
  error = Pa_StartStream(stream_);
  if (error != paNoError) {
    LOG(ERROR) << "Problem opening starting Stream";
    return 1;
  }

  return 0;
}

}  // namespace gva
