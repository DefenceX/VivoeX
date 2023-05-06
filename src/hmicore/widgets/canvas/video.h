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
/// \file video.h
///

#ifndef HMICORE_CANVAS_VIDEO_H_
#define HMICORE_CANVAS_VIDEO_H_

#include <rtpvraw_depayloader.h>

#include <cstdint>
#include <string>
#include <vector>

#include "hmicore/renderer_cairo_types.h"
#include "hmicore/widgets/canvas/canvas.h"
#include "hmicore/widgets/widget.h"

namespace gva {

class WidgetVideo : public WidgetCanvas {
 public:
  ///
  /// \brief Construct a new Widget video object
  ///
  /// \param renderer
  ///
  explicit WidgetVideo(const RendererGva& renderer);

  ///
  /// \brief Destroy the Widget video object
  ///
  ///
  ~WidgetVideo();

  ///
  /// \brief Set the Receive timeout attribute for frame data, default 80ms
  ///
  ///
  void SetReceiveTimeout(uint32_t timeout_ms);

  ///
  /// \brief This will update the video frame if one available
  ///
  ///
  void Draw() final;

  ///
  /// \brief Draw the canvas with video rendered on it
  ///
  ///
  void DrawVideo();

  ///
  /// \brief Start the video stream
  ///
  ///
  void Start();

  ///
  /// \brief Stop the video stream
  ///
  ///
  void Stop();

 private:
  std::array<uint8_t, 640 * 480 * 3> rgb_buffer_;
  RtpvrawDepayloader video_feed_;
  uint32_t timeout_ms_ = 80;
  const bool kSapEnabled = true;
};

}  // namespace gva

#endif  // HMICORE_CANVAS_VIDEO_H_