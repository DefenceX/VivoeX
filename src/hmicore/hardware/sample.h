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
