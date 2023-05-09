//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file video.cc
///

#include "hmicore/widgets/canvas/video.h"

#include <colourspace.h>
#include <rtpvraw_depayloader.h>

namespace gva {

WidgetVideo::WidgetVideo(const RendererGva &renderer) : WidgetCanvas(renderer) {
  std::string session_name = "TestVideo1";
  std::string ip_address = "239.192.1.1";
  RtpvrawDepayloader test;
  if (kSapEnabled == true) {
    // Listed for SAP/SDP
    video_feed_.SetStreamInfo(session_name);
  } else {
    // No SAP/SDP so define it now in code
    video_feed_.SetStreamInfo(session_name, ColourspaceType::kColourspaceYuv, 640, 480, ip_address);
    video_feed_.Open();
  }
  Start();
}

WidgetVideo::~WidgetVideo() { video_feed_.Close(); }

void WidgetVideo::SetReceiveTimeout(uint32_t timeout_ms) { timeout_ms_ = timeout_ms; }

void WidgetVideo::Draw() {
  if (GetVisible()) {
    DrawVideo();
  }
}

void WidgetVideo::DrawVideo() {
  // uint8_t *cpu_buffer;
  // if (video_feed_.Receive(&cpu_buffer, timeout_ms_) == true) {
  //   // video::YuvToRgba(480, 640, cpu_buffer, rgb_buffer_.data());
  //   // GetRenderer()->TextureRGB(0, 0, rgb_buffer_.data());
  //   GetRenderer()->SetColourForeground(HMI_BLACK);
  //   GetRenderer()->SetColourBackground(HMI_BLACK);
  //   GetRenderer()->DrawRectangle(0, 0, width_, height_, true);
  // } else
  {
    std::cout << "Running\n";
    const std::string path = ConfigData::GetInstance()->GetImagePath();
    SetFilename(path + "/VideoBackground.png");

    WidgetCanvas::Draw();
    GetRenderer()->SetColourForeground(HMI_WHITE);

    GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                               ConfigData::GetInstance()->GetThemeFont(), 12);
    std::string stream = video_feed_.GetIpAddress() + ":" + std::to_string(video_feed_.GetPort()) + " offline";
    uint32_t w = GetRenderer()->GetTextWidth(stream, 12);

    GetRenderer()->DrawText(kMinimumWidth / 2 - (w / 2), 400 + 16, stream);
  }
}

void WidgetVideo::Stop() { video_feed_.Stop(); }

void WidgetVideo::Start() { video_feed_.Start(); }

}  // namespace gva
