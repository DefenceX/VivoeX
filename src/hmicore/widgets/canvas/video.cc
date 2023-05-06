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
/// \file video.cc
///

#include "hmicore/widgets/canvas/video.h"

#include <colourspace.h>
#include <rtpvraw_depayloader.h>

namespace gva {

WidgetVideo::WidgetVideo(const RendererGva &renderer) : WidgetCanvas(renderer) {
  SetVisible(true);
  video_feed_.RtpvrawDepayloaderIn("DemoVideo1", ColourspaceType::kColourspaceYuv, 640, 480, "239.192.1.1", 5004);
}

void WidgetVideo::SetReceiveTimeout(uint32_t timeout_ms) { timeout_ms_ = timeout_ms; }

void WidgetVideo::Draw() {
  if (GetVisible()) {
    DrawVideo();
  }
}

void WidgetVideo::DrawVideo() {
  uint8_t *cpu_buffer;
  if (video_feed_.Receive(&cpu_buffer, timeout_ms_) == true) {
    video::YuvToRgba(480, 640, cpu_buffer, rgb_buffer_.data());
    GetRenderer()->TextureRGB(0, 0, rgb_buffer_.data());
  }
}

}  // namespace gva
