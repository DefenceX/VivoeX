//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file bottom_labels.cc
///

#include "hmicore/widgets/bottom_labels.h"

#include <array>

#include "hmicore/gva.h"

namespace gva {

WidgetBottomLabels::WidgetBottomLabels(const RendererGva& renderer, TouchGva* touch)
    : WidgetX(renderer, widget::WidgetEnum::KWidgetTypeCompass), touch_(touch) {
  config_ = ConfigData::GetInstance();
}

void WidgetBottomLabels::Draw() {
  if (GetVisible()) {
    DrawControlLabels();
  }
}

void WidgetBottomLabels::DrawControlLabels() {
  uint32_t i = 0;
  uint32_t offset = 20;
  uint32_t w = 75;

  std::array<std::string, 8> labels = {"Up", "Alarms", "Threats", "Ack", "", "", "Labels", "Enter"};

  GetRenderer()->SetColourForeground(config_->GetThemeLabelBorderEnabled());
  GetRenderer()->SetColourBackground(config_->GetThemeLabelBackgroundEnabled());
  GetRenderer()->SetLineType(CAIRO_LINE_JOIN_ROUND);
  GetRenderer()->SetLineThickness(config_->GetThemeLabelBorderThickness(), LineType::kLineSolid);
  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, widget::WeightType::kWeightNormal,
                             config_->GetThemeFont(), 12);

  for (auto label : labels_) {
    if (label.state_ != LabelStates::kLabelHidden) {
      SetStateLabel(label.state_);

      if (gva::ConfigData::GetInstance()->GetThemeLabelStyle() == config::kLabelRounded) {
        GetRenderer()->DrawRoundedRectangle((i * w) + offset, GetY(), w - 5, 20, 4, true);
      } else {
        GetRenderer()->DrawRectangle((i * w) + offset, GetY(), w - 5, 20, true);
      }
      SetStateText(label.state_);

      if (label.state_ != LabelStates::kLabelDisabled) {
        touch_->AddAbsolute(GvaFunctionGroupEnum::kBottom, int(GvaKeyEnum::kKeyF13) + i, (i * w) + offset, GetY(),
                            (i * w) + w - 5 + offset, GetY() + 20);
      }

      switch (i) {
        default: {
          uint32_t width = GetRenderer()->GetTextWidth(label.text_, 12);
          GetRenderer()->DrawString((i * w) + offset + ((70 - width) / 2), GetY() + 14, label.text_.c_str());
        } break;
        case 4:
          GetRenderer()->DrawIcon(widget::IconType::kIconUpArrow, (i * w) + offset + 34, GetY() + 11, 15, 8);
          break;
        case 5:
          GetRenderer()->DrawIcon(widget::IconType::kIconDownArrow, (i * w) + offset + 34, GetY() + 10, 15, 8);
          break;
      }
      i++;
    }
  }
}

void WidgetBottomLabels::SetLabels(std::array<CommonTaskKeys::Labels, 8>* labels) { labels_ = *labels; };

void WidgetBottomLabels::EnableLabel(GvaKeyEnum key) {
  switch (key) {
    case GvaKeyEnum::kKeyF13:  // Up
      labels_[0].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF14:  // Alarms
      labels_[1].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF15:  // Threats
      labels_[2].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF16:  // Ack
      labels_[3].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF17:  // Up
      labels_[4].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF18:  // Down
      labels_[5].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF19:  // Labels
      labels_[6].state_ = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF20:  // Enter
      labels_[7].state_ = LabelStates::kLabelEnabled;
      break;
    default:  // Enter
      break;
  }
}

void WidgetBottomLabels::DisableLabel(GvaKeyEnum key) {
  switch (key) {
    case GvaKeyEnum::kKeyF13:  // Up
      labels_[0].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF14:  // Alarms
      labels_[1].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF15:  // Threats
      labels_[2].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF16:  // Ack
      labels_[3].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF17:  // Up
      labels_[4].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF18:  // Down
      labels_[5].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF19:  // Labels
      labels_[6].state_ = LabelStates::kLabelDisabled;
      break;
    case GvaKeyEnum::kKeyF20:  // Enter
      labels_[7].state_ = LabelStates::kLabelDisabled;
      break;
    default:  // Enter
      break;
  }
}

}  // namespace gva
