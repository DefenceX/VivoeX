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

#ifndef HMICORE_HARDWARE_SAMPLE_H_
#define HMICORE_HARDWARE_SAMPLE_H_

#include <sndfile.h>

#include <string_view>
#include <vector>

namespace gva {

class AudioSampleBase {
 public:
  virtual int32_t ReadBytes(void* buffer, const uint32_t bytes) = 0;
  virtual int32_t GetChannels() const = 0;
  virtual int32_t GetSamplingRate() const = 0;
  virtual void Seek(uint32_t bytes) = 0;
};

class AudioSample : public AudioSampleBase {
 public:
  struct CallbackData {
    SNDFILE* file;
    SF_INFO info;
  };
  explicit AudioSample(const std::string_view filename);
  int32_t ReadBytes(void* buffer, const uint32_t bytes) final;
  int32_t GetChannels() const final;
  int32_t GetSamplingRate() const final;
  void Seek(uint32_t bytes) final;

 private:
  uint32_t total_ = 0;
  uint32_t seek_ = 0;
  CallbackData fileinfo_;
  std::vector<float> data_;
};

}  // namespace gva

#endif  // HMICORE_HARDWARE_SAMPLE_H_
