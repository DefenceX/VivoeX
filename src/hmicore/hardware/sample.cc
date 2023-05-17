//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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

int32_t AudioSample::ReadBytes(uint8_t* buffer, const uint32_t bytes) {
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