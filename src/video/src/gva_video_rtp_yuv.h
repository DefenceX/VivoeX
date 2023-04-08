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
/// \brief Video colour space conversion functions wo handle YUV / RGB
///
/// \file gva_video_rtp_yuv.h
///

#ifndef VIDEO_SRC_GVA_VIDEO_RTP_YUV_H_
#define VIDEO_SRC_GVA_VIDEO_RTP_YUV_H_

#include <memory>
#include <string>
#include <string_view>

#include "gva_video.h"   // NOLINT
#include "rtp_stream.h"  // NOLINT

namespace gva {

//
// Buffers are assumed to be YUV
//
class GvaVideoRtpYuv : public GvaVideoSource {
 public:
  GvaVideoRtpYuv(std::string_view ip, uint32_t port, uint32_t height, uint32_t width);
  GvaVideoRtpYuv(std::string_view ip, uint32_t port);
  ~GvaVideoRtpYuv() final = default;

  // Implementation of pure virtual base class functions
  uint32_t GvaReceiveFrame(char *buffer, VideoFormat format) final;
  uint32_t GvaTransmitFrame(char *buffer, VideoFormat format) final;

 private:
  std::string_view ip_;
  uint32_t port_;
  uint32_t frame_counter_ = 0;
  std::unique_ptr<RtpStream> stream_;
};

}  // namespace gva

#endif  // VIDEO_SRC_GVA_VIDEO_RTP_YUV_H_