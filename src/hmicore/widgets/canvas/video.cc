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
#include <glog/logging.h>
#include <rtp_types.h>
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
  uint8_t *cpu_buffer;
  if (video_feed_.Receive(&cpu_buffer, 1) == true) {
    video::YuvToRgba(480, 640, cpu_buffer, rgb_buffer_.data());
    GetRenderer()->TextureRGB(0, 0, rgb_buffer_.data());
  } else {
    const std::string video_background_filename = ConfigData::GetInstance()->GetImagePath() + "/VideoBackground.png";
    GetRenderer()->TextureRGB(0, 0, nullptr, video_background_filename);

    GetRenderer()->DrawColor(HMI_WHITE);

    GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

    GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                               ConfigData::GetInstance()->GetThemeFont(), 12);
    std::string stream;
    if (kSapEnabled) {
      stream =
          "sap://" + kIpaddr + "@" + std::to_string(kPort) + ":" + std::to_string(video_feed_.GetPort()) + " offline ";

    } else {
      stream = "rtp://" + video_feed_.GetSessionName() + "@" + video_feed_.GetIpAddress() + ":" +
               std::to_string(video_feed_.GetPort()) + " offline";
    }
    uint32_t w = GetRenderer()->GetTextWidth(stream, 12);

    GetRenderer()->DrawText(kMinimumWidth / 2 - (w / 2), 300 + 16, stream);
  }
}

void WidgetVideo::Stop() { video_feed_.Stop(); }

void WidgetVideo::Start() { video_feed_.Start(); }

void WidgetVideo::SetSessionName(std::string_view session_name) const { video_feed_.SetSessionName(session_name); }

void WidgetVideo::SetIpAddress(std::string_view ip_address) const { video_feed_.SetIpAddress(ip_address); }

}  // namespace gva
