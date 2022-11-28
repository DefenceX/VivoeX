///
/// MIT License
///
/// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
///
/// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
/// associated documentation files (the 'Software'), to deal in the Software without restriction,
/// including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
/// subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included in all copies or substantial
/// portions of the Software.
/// THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
/// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
/// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
/// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
/// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
///
/// \brief The operational mode widget
///
/// \file mode.cc
///

#include "src/widgets/mode.h"

#include "src/screen_gva.h"

namespace gva {

WidgetMode::WidgetMode(const RendererGva& renderer) : WidgetX(renderer, KWidgetTypeMode) { SetVisible(false); }

void WidgetMode::Draw() {
  uint32_t offset = DEFAULT_WIDTH * 0.4;
  uint32_t y = DEFAULT_HEIGHT * 0.12;

  GetRenderer()->SetColourForeground(HMI_WHITE);
  GetRenderer()->SetColourBackground(HMI_DARK_BLUE);
  GetRenderer()->SetLineThickness(1, LineType::kLineSolid);

  GetRenderer()->SetTextFont((uint32_t)CAIRO_FONT_SLANT_NORMAL, WeightType::kWeightNormal,
                             ConfigData::GetInstance()->GetThemeFont());

  uint32_t w = GetRenderer()->GetTextWidth(mode_, 12);
  uint32_t h = GetRenderer()->GetTextHeight(mode_, 12);

  GetRenderer()->DrawRoundedRectangle(DEFAULT_WIDTH / 2 - (w / 2) - 5, y, w + 10, (h) + 15, 6, true);
  GetRenderer()->SetTextFontSize(12);
  GetRenderer()->DrawText(DEFAULT_WIDTH / 2 - (w / 2), y + 8, mode_);
}

void WidgetMode::SetMode(const std::string mode) { mode_ = mode; }

std::string WidgetMode::GetMode() const { return mode_; }

}  // namespace gva