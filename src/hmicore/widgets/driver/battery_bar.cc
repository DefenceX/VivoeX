//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file battery_bar.cc
///

#include "hmicore/widgets/driver/battery_bar.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

#include "hmicore/gva_functions_common.h"
#include "hmicore/renderer_gva.h"

namespace gva {

WidgetDriverBatteryBar::WidgetDriverBatteryBar(const RendererGva& renderer)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeBatteryBar) {
  SetVisible(false);
}

void WidgetDriverBatteryBar::Draw() {
  uint16_t width = 40;
  uint16_t height = 100;
  const uint32_t font_size = 18;

  // Check to see if we need to be rendered
  if (!GetVisible()) {
    return;
  }

  // Set the font for all compass/s
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             gva::ConfigData::GetInstance()->GetThemeFont(), font_size);

  GetRenderer()->Save();
  GetRenderer()->Scale(0.5, 0.5);
  GetRenderer()->Translate(GetX(), GetY());

  GetRenderer()->DrawColor(kHmiWhite);

  // Battery frame
  uint16_t frameThickness = 4;
  GetRenderer()->SetColourBackground(kHmiBlack);
  GetRenderer()->SetColourForeground(kHmiWhite);
  GetRenderer()->SetLineThickness(frameThickness, LineType::kLineSolid);
  GetRenderer()->DrawRectangle(0, 0, width, height, true);

  // Hard code value level as a percentage
  float value_ = 0.8;
  uint16_t batteryPercentage = static_cast<uint16_t>(value_ * 100);

  // Battery level boxes
  uint16_t maxBoxes = 10;
  uint16_t numBoxes = static_cast<uint16_t>(std::floor(value_ * maxBoxes));
  uint16_t spacing = 5;
  GetRenderer()->SetColourBackground(kHmiGreen);
  GetRenderer()->SetColourForeground(kHmiBlack);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);
  for (uint16_t i = 0; i < numBoxes; ++i) {
    // Determine the color based on battery percentage range
    uint16_t batteryPercentage = i * 10;
    switch (batteryPercentage) {
      case 0 ... 20:
        GetRenderer()->SetColourBackground(kHmiRed);
        break;
      case 21 ... 40:
        GetRenderer()->SetColourBackground(kHmiYellow);
        break;
      default:
        GetRenderer()->SetColourBackground(kHmiGreen);
        break;
    }
    uint16_t boxY = (height - frameThickness*2) - (i * (height / maxBoxes)) - spacing;
    GetRenderer()->DrawRectangle(spacing, boxY, width - 2 * spacing, height / maxBoxes - spacing, true);
  }

  // Battery text
  std::string labelText = "Battery " + std::to_string(batteryPercentage) + "%";
  uint16_t textWidth = (labelText.size() * font_size)/2 ;
  int16_t textX = (width - textWidth) + (width/2);  // Calculate the x-coordinate for centering the text
  GetRenderer()->DrawString(textX, height + 20, labelText);

  GetRenderer()->Restore();
}



}  // namespace gva