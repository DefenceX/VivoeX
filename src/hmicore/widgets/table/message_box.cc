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
/// \file message_box.cc
///

#include "hmicore/widgets/table/message_box.h"

namespace gva {

WidgetMessageBox::WidgetMessageBox(const RendererGva &renderer, TouchGva *touch) : WidgetTable(renderer, touch) {
  WidgetTable::Reset();
  SetCurrentRow(1);
}

void WidgetMessageBox::Draw() {
  SetX((gva::kMinimumWidth / 2) - 150);
  SetY(220);
  SetWidth(300);
  SetBackgroundColour(ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

  uint32_t background = gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled();

  AddRow();
  AddCell("System Information", 100, widget::CellAlignType::kAlignCentre, background);

  AddRow();
  AddCell(std::string(message_text_), 100, widget::CellAlignType::kAlignCentre, background);

  Draw();

  GetRenderer()->DrawIcon(icon_, 320 - 150 + 300 - 17, 229, 11, 11);
}

void WidgetMessageBox::SetMessage(const std::string_view message_text, widget::IconType icon) {
  message_text_ = message_text;
  icon_ = icon;
}

}  // namespace gva
