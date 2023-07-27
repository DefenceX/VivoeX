//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file message_box.cc
///

#include "hmicore/widgets/table/message_box.h"

namespace gva {

WidgetMessageBox::WidgetMessageBox(const RendererGva &renderer, TouchGva *touch) : WidgetTable(renderer, touch) {
  WidgetTable::Reset();
  SetCurrentRow(1);
}

void WidgetMessageBox::Draw() {
  std::tuple<int, int> currentScreenSize = minimumSizeInstance.getMinimumSize();
  width_ = std::get<0>(currentScreenSize);

  SetX((width_ / 2) - 150);
  SetY(220);
  SetWidth(300);
  SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

  uint32_t background = gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled();

  AddRow();
  AddCell("System Information", 100, widget::CellAlignType::kAlignCentre, background);

  AddRow();
  AddCell(std::string(message_text_), 100, widget::CellAlignType::kAlignCentre, background);

  GetRenderer()->DrawIcon(icon_, 320 - 150 + 300 - 17, 229, 11, 11);
}

void WidgetMessageBox::SetMessage(const std::string_view message_text, widget::IconType icon) {
  message_text_ = message_text;
  icon_ = icon;
}

}  // namespace gva
