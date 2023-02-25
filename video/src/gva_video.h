///
/// MIT License
///
/// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief The video source to receive RAW video streams over RTP as per DEF-STAN 00-082
///
/// \file gva_video.h
///

#ifndef VIDEO_SRC_GVA_VIDEO_H_
#define VIDEO_SRC_GVA_VIDEO_H_

#include <string>

namespace gva {

enum class VideoFormat { kFormatRgbaColour = 0, kFormatRgb24Colour, kFormatYuyvColour };

class GvaVideoSource {
 public:
  GvaVideoSource(uint32_t height, uint32_t width);

  virtual ~GvaVideoSource() = default;

  ///
  /// \brief Receive one frame of video
  ///
  /// \param buffer
  /// \param format
  /// \return uint32_t
  ///
  virtual uint32_t GvaReceiveFrame(char *buffer, VideoFormat format) = 0;

  ///
  /// \brief Transmit one frame of video
  ///
  /// \param buffer
  /// \param format
  /// \return uint32_t
  ///
  virtual uint32_t GvaTransmitFrame(char *buffer, VideoFormat format) = 0;

  ///
  /// \brief Get the Width object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetWidth() const { return width_; }

  ///
  /// \brief Get the Height object
  ///
  /// \return const uint32_t
  ///
  uint32_t GetHeight() const { return height_; }

 private:
  uint32_t height_;
  uint32_t width_;
};

}  // namespace gva

#endif  // VIDEO_SRC_GVA_VIDEO_H_
