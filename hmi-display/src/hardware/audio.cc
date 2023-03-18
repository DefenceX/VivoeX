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

#include "src/hardware/audio_functions.h"

#define BUFFER_SIZE 8192

int cancel_playback;

namespace gva {

void AudioFunctions::OnCancelPlayback(int sig) {
  if (sig != SIGINT) {
    return;
  }

  cancel_playback = 1;
  exit(0);
}

void AudioFunctions::Clean(ao_device *device, SNDFILE *file) {
  ao_close(device);
  sf_close(file);
  ao_shutdown();
}

int AudioFunctions::Play() {
  ao_device *device;
  ao_sample_format format;
  SF_INFO sfinfo;

  int default_driver;

  short *buffer;

  //   signal(SIGINT, OnCancelPlayback);

  SNDFILE *file = sf_open("test.ogg", SFM_READ, &sfinfo);

  printf("Samples: %d\n", (int)sfinfo.frames);
  printf("Sample rate: %d\n", sfinfo.samplerate);
  printf("Channels: %d\n", sfinfo.channels);

  ao_initialize();

  default_driver = ao_default_driver_id();

  switch (sfinfo.format & SF_FORMAT_SUBMASK) {
    case SF_FORMAT_PCM_16:
      format.bits = 16;
      break;
    case SF_FORMAT_PCM_24:
      format.bits = 24;
      break;
    case SF_FORMAT_PCM_32:
      format.bits = 32;
      break;
    case SF_FORMAT_PCM_S8:
      format.bits = 8;
      break;
    case SF_FORMAT_PCM_U8:
      format.bits = 8;
      break;
    default:
      format.bits = 16;
      break;
  }

  format.channels = sfinfo.channels;
  format.rate = sfinfo.samplerate;
  format.byte_format = AO_FMT_NATIVE;
  format.matrix = 0;

  device = ao_open_live(default_driver, &format, NULL);

  if (device == NULL) {
    fprintf(stderr, "Error opening device.\n");
    return 1;
  }

  buffer = (short *)calloc(BUFFER_SIZE, sizeof(short));

  while (1) {
    int read = sf_read_short(file, buffer, BUFFER_SIZE);

    if (ao_play(device, (char *)buffer, (uint_32)(read * sizeof(short))) == 0) {
      printf("ao_play: failed.\n");
      Clean(device, file);
      break;
    }

    if (cancel_playback) {
      Clean(device, file);
      break;
    }
  }

  Clean(device, file);

  return 0;
}

}  // namespace gva
