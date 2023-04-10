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
/// \file sample.h
///

#include "hmicore/hardware/sample.h"

#include <glog/logging.h>

#include <array>
#include <string>

namespace gva {

AudioSample::AudioSample(const std::string_view filename) {
  int num_bytes = 0;
  std::array<float, 4096> tmp_buffer;

  // Load the audio file into memory
  fileinfo_.file = sf_open(std::string(filename).c_str(), SFM_READ, &fileinfo_.info);
  if (sf_error(fileinfo_.file) != SF_ERR_NO_ERROR) {
    LOG(ERROR) << "File " << filename << sf_strerror(fileinfo_.file);
    return;
  }

  num_bytes = sf_read_float(fileinfo_.file, &tmp_buffer[0], 4096);
  data_.insert(data_.end(), &tmp_buffer[0], &tmp_buffer[4096]);
  total_ += num_bytes;
  while (num_bytes) {
    num_bytes = sf_read_float(fileinfo_.file, &tmp_buffer[0], 4096);
    data_.insert(data_.end(), &tmp_buffer[0], &tmp_buffer[4096]);
    total_ += num_bytes;
  }

  sf_close(fileinfo_.file);

  LOG(INFO) << "Loaded " << total_ << " bytes from " << filename;
}

int32_t AudioSample::ReadBytes(void* buffer, const uint32_t bytes) {
  uint32_t bytes_to_copy = 0;
  // Clear the buffer
  memset(buffer, 0, sizeof(float) * bytes);

  if ((total_ - seek_) < bytes) {
    bytes_to_copy = total_ - seek_;
  } else {
    bytes_to_copy = bytes;
  }
  // Copy the buffer bytes
  memcpy(buffer, &data_[seek_], bytes * sizeof(float));
  seek_ += bytes_to_copy;
  return bytes_to_copy;
}

int32_t AudioSample::GetChannels() const { return fileinfo_.info.channels; }

int32_t AudioSample::GetSamplingRate() const { return fileinfo_.info.samplerate; }

void AudioSample::Seek(uint32_t bytes) { seek_ = bytes; }

}  // namespace gva