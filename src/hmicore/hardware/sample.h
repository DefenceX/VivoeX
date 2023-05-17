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

///
/// \brief The Audio Sample Base class
///
///
class AudioSampleBase {
 public:
  ///
  /// \brief Destroy the Audio Sample Base object
  ///
  ///
  virtual ~AudioSampleBase() = default;

  ///
  /// \brief Destroy the Audio Sample Base object
  ///
  /// \param buffer The buffer to read into
  /// \param bytes The number of bytes to read
  /// \return int32_t
  ///
  virtual int32_t ReadBytes(uint8_t* buffer, const uint32_t bytes) = 0;

  ///
  /// \brief Get the Channels attribute
  ///
  /// \return int32_t number of channels
  ///
  virtual int32_t GetChannels() const = 0;

  ///
  /// \brief Get the Sampling Rate attribute
  ///
  /// \return int32_t seek location
  ///
  virtual void Seek(uint32_t bytes) = 0;

  ///
  /// \brief Get the Sampling Rate attribute
  ///
  /// \return int32_t sampling rate
  ///
  virtual int32_t GetSamplingRate() const = 0;
};

///
/// \brief The Audio Sample class
///
///
class AudioSample : public AudioSampleBase {
 public:
  ///
  /// \brief Construct a new Audio Sample object
  ///
  ///
  struct CallbackData {
    /// The audio sample file
    SNDFILE* file;
    /// The audio sample info
    SF_INFO info;
  };

  ///
  /// \brief Construct a new Audio Sample object
  ///
  /// \param filename The filename of the audio sample
  ///
  explicit AudioSample(const std::string_view filename);

  ///
  /// \brief Destroy the Audio Sample object
  ///
  /// \param buffer The buffer to read into
  /// \param bytes The number of bytes to read
  /// \return int32_t bytes read
  ///
  int32_t ReadBytes(uint8_t* buffer, const uint32_t bytes) final;

  ///
  /// \brief Get the Channels attribute
  ///
  /// \return int32_t number of channels
  ///
  int32_t GetChannels() const final;

  ///
  /// \brief Get the Sampling Rate attribute
  ///
  /// \return int32_t sampling rate
  ///
  int32_t GetSamplingRate() const final;

  ///
  /// \brief Get the Total Samples attribute
  ///
  /// \param bytes The number of bytes to read
  ///
  void Seek(uint32_t bytes) final;

 private:
  uint32_t total_ = 0;
  uint32_t seek_ = 0;
  CallbackData fileinfo_;
  std::vector<float> data_;
};

}  // namespace gva

#endif  // HMICORE_HARDWARE_SAMPLE_H_
