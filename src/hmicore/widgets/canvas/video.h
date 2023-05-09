//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file video.h
///

#ifndef HMICORE_WIDGETS_CANVAS_VIDEO_H_
#define HMICORE_WIDGETS_CANVAS_VIDEO_H_

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

#endif  // HMICORE_WIDGETS_CANVAS_VIDEO_H_
