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

#include "src/hardware/audio.h"

#include <glog/logging.h>
#define BUFFER_SIZE 8192

namespace gva {

#define FRAMES_PER_BUFFER (512)

int AudioFunctions::callback(const void *input, void *output, unsigned long frameCount,
                             const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags,
                             void *userData) {
  float *out;
  callback_data_s *p_data = (callback_data_s *)userData;
  sf_count_t num_read;

  out = (float *)output;
  p_data = (callback_data_s *)userData;

  /* clear output buffer */
  memset(out, 0, sizeof(float) * frameCount * p_data->info.channels);

  /* read directly into output buffer */
  num_read = sf_read_float(p_data->file, out, frameCount * p_data->info.channels);

  /*  If we couldn't read a full frameCount of samples we've reached EOF */
  if (num_read < (int)frameCount) {
    return paComplete;
  }

  return paContinue;
}

void AudioFunctions::PlayThreat() { Play("/opt/gva/hmi/threat.wav"); }
void AudioFunctions::PlayCaution() { Play("/opt/gva/hmi/caution.wav"); }
void AudioFunctions::PlayWarning() { Play("/opt/gva/hmi/warning.wav"); }

int AudioFunctions::Play(std::string filename) {
  PaStream *stream;
  PaError error;
  callback_data_s data;

  /* Open the soundfile */
  data.file = sf_open(filename.c_str(), SFM_READ, &data.info);
  if (sf_error(data.file) != SF_ERR_NO_ERROR) {
    fprintf(stderr, "%s\n", sf_strerror(data.file));
    return 1;
  }

  /* init portaudio */
  error = Pa_Initialize();
  if (error != paNoError) {
    fprintf(stderr, "Problem initializing\n");
    return 1;
  }

  /* Open PaStream with values read from the file */
  error = Pa_OpenDefaultStream(&stream, 0 /* no input */
                               ,
                               data.info.channels /* stereo out */
                               ,
                               paFloat32 /* floating point */
                               ,
                               data.info.samplerate, FRAMES_PER_BUFFER, callback, &data); /* our sndfile data struct */
  if (error != paNoError) {
    fprintf(stderr, "Problem opening Default Stream\n");
    return 1;
  }

  /* Start the stream */
  error = Pa_StartStream(stream);
  if (error != paNoError) {
    fprintf(stderr, "Problem opening starting Stream\n");
    return 1;
  }

  /* Run until EOF is reached */
  while (Pa_IsStreamActive(stream)) {
    Pa_Sleep(100);
  }

  /* Close the soundfile */
  sf_close(data.file);

  /*  Shut down portaudio */
  error = Pa_CloseStream(stream);
  if (error != paNoError) {
    fprintf(stderr, "Problem closing stream\n");
    return 1;
  }

  error = Pa_Terminate();
  if (error != paNoError) {
    fprintf(stderr, "Problem terminating\n");
    return 1;
  }

  return 0;
}

}  // namespace gva
