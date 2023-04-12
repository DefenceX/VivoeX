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
  float *out;
  auto *sample_data = (AudioSampleBase *)userData;
  sf_count_t num_read;

  out = (float *)output;
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

void AudioFunctions::PlayThreat() { Play(threat_); }
void AudioFunctions::PlayCaution() { Play(caution_); }
void AudioFunctions::PlayWarning() { Play(warning_); }

int AudioFunctions::Play(AudioSampleBase &sample) {
  PaError error;

  // Go to start of file, may have been played before
  sample.Seek(0);

  if (stream_ != nullptr) {
    Pa_CloseStream(stream_);
    stream_ = nullptr;
  }

  // Open PaStream with values read from the sample
  error =
      Pa_OpenDefaultStream(&stream_, 0,                                                     // no input
                           sample.GetChannels(),                                            // stereo out
                           paFloat32,                                                       // floating point
                           sample.GetSamplingRate(), kFramesPerBuffer, Callback, &sample);  // our sndfile data struct
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
