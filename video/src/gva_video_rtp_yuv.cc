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

#include "src/gva_video_rtp_yuv.h"

#include <iostream>
#include <memory>
#include <string>

#include "src/gva.h"

namespace gva {

GvaVideoRtpYuv::GvaVideoRtpYuv(std::string_view ip, uint32_t port, uint32_t height, uint32_t width)
    : GvaVideoSource(height, width), ip_(ip), port_(port), frame_counter_(0) {}

GvaVideoRtpYuv::GvaVideoRtpYuv(std::string_view ip, uint32_t port)
    : GvaVideoSource(kMinimumHeight, kMinimumWidth), ip_(ip), port_(port) {
  stream_ = std::make_unique<RtpStream>(kMinimumHeight, kMinimumWidth);
  const char* ipaddr = ip_.data();
  stream_->RtpStreamIn(ipaddr, port_);
  stream_->Open();
}

uint32_t GvaVideoRtpYuv::GvaReceiveFrame(char* buffer, VideoFormat format) {
  char* frame_buffer;
  stream_->Receive((void**)&frame_buffer, 5);
  switch (format) {
    case VideoFormat::kFormatYuyvColour:
      memcpy(buffer, frame_buffer, GetWidth() * GetHeight() * 2);
      break;
    case VideoFormat::kFormatRgbaColour:
      yuvtorgba(GetHeight(), GetWidth(), frame_buffer, buffer);
      break;
    case VideoFormat::kFormatRgb24Colour:
      yuvtorgb(GetHeight(), GetWidth(), frame_buffer, buffer);
      break;
  }
  frame_counter_++;
  return 0;
}

uint32_t GvaVideoRtpYuv::GvaTransmitFrame(char* buffer, VideoFormat format) { return -1; };

}  // namespace gva
