//
// MIT License
//
// Copyright (c) 2020 Ross Newman (ross@rossnewman.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#ifndef VIDEO_SRC_GVA_VIDEO_H_
#define VIDEO_SRC_GVA_VIDEO_H_

#include <string>

#define VIDEO_DEFAULT_HEIGHT 480
#define VIDEO_DEFAULT_WIDTH 640

namespace gva {

enum VideoFormat { RGBA_COLOUR = 0, RGB24_COLOUR, YUYV_COLOUR };

class GvaVideoSource {
 public:
  GvaVideoSource(uint32_t height, uint32_t width);

  ///
  /// \brief Receive one frame of video
  ///
  /// \param buffer
  /// \param format
  /// \return uint32_t
  ///
  virtual const uint32_t GvaReceiveFrame(char *buffer, VideoFormat format) = 0;

  ///
  /// \brief Transmit one frame of video
  ///
  /// \param buffer
  /// \param format
  /// \return uint32_t
  ///
  virtual const uint32_t GvaTransmitFrame(char *buffer, VideoFormat format) = 0;

  ///
  /// \brief Get the Width object
  ///
  /// \return const uint32_t
  ///
  const uint32_t GetWidth() { return width_; }

  ///
  /// \brief Get the Height object
  ///
  /// \return const uint32_t
  ///
  const uint32_t GetHeight() { return height_; }

 private:
  uint32_t height_;
  uint32_t width_;
};

}  // namespace gva

#endif  // VIDEO_SRC_GVA_VIDEO_H_
