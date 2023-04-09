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

#include <alsa/asoundlib.h>
#include <glog/logging.h>

namespace gva {

void *AudioFunctions::AlsaLog(const char *file, int line, const char *function, int err, const char *fmt, ...) {
  LOG(INFO) << "PortAudio info: " << file << ":" << line << " " << function << " " << err << " " << fmt << "\n";
  return nullptr;
}

AudioFunctions::AudioFunctions() {
  PaError error;

  snd_lib_error_set_handler((snd_lib_error_handler_t)AudioFunctions::AlsaLog);
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
  auto *p_data = (CallbackData *)userData;
  sf_count_t num_read;

  out = (float *)output;
  p_data = (CallbackData *)userData;

  // clear output buffer */
  memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);

  // read directly into output buffer
  num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);

  //  If we couldn't read a full frameCount of samples we've reached EOF
  if (num_read < (int)frameCount) {
    return paComplete;
  }

  return paContinue;
}

#if __MINGW64__ || __MINGW32__
void AudioFunctions::PlayThreat() const { Play("../sounds/threat.wav"); }
void AudioFunctions::PlayCaution() const { Play("../sounds/caution.wav"); }
void AudioFunctions::PlayWarning() const { Play("../sounds/warning.wav"); }
#else
void AudioFunctions::PlayThreat() const { Play("/opt/gva/hmi/sounds/threat.wav"); }
void AudioFunctions::PlayCaution() const { Play("/opt/gva/hmi/sounds/caution.wav"); }
void AudioFunctions::PlayWarning() const { Play("/opt/gva/hmi/sounds/warning.wav"); }
#endif

int AudioFunctions::Play(std::string_view filename) const {
  PaStream *stream;
  CallbackData data;
  PaError error;

  // Open the sound file
  data.file = sf_open(std::string(filename).c_str(), SFM_READ, &data.info);
  if (sf_error(data.file) != SF_ERR_NO_ERROR) {
    LOG(ERROR) << "File " << filename << sf_strerror(data.file);
    return 1;
  }

  // Open PaStream with values read from the file
  error = Pa_OpenDefaultStream(&stream, 0,                                                // no input
                               data.info.channels,                                        // stereo out
                               paFloat32,                                                 // floating point
                               data.info.samplerate, kFramesPerBuffer, Callback, &data);  // our sndfile data struct
  if (error != paNoError) {
    LOG(ERROR) << "Problem opening Default Stream";
    return 1;
  }

  // Start the stream
  error = Pa_StartStream(stream);
  if (error != paNoError) {
    LOG(ERROR) << "Problem opening starting Stream";
    return 1;
  }

  // Run until EOF is reached
  while (Pa_IsStreamActive(stream)) {
    Pa_Sleep(100);
  }

  // Close the soundfile
  sf_close(data.file);

  //  Shut down portaudio
  error = Pa_CloseStream(stream);
  if (error != paNoError) {
    LOG(ERROR) << "Problem closing stream";
    return 1;
  }

  return 0;
}

}  // namespace gva
