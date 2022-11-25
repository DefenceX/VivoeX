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
/// \brief Template for all widgets
///
/// \file widget.cc
///

#include "src/widgets/widget.h"

namespace gva {

WidgetX::WidgetX(const RendererGva& renderer, WidgetEnum widget_type)
    : renderer_(renderer), widget_type_(widget_type) {}

void WidgetX::SetVisible(bool visible) { visible_ = visible; }

bool WidgetX::GetVisible() const { return visible_; }

void WidgetX::SetX(int x) { x_ = x; }

int WidgetX::GetX() const { return x_; }

void WidgetX::SetY(int y) { y_ = y; }

int WidgetX::GetY() const { return y_; }

WidgetEnum WidgetX::GetType() const { return widget_type_; }

RendererGva* WidgetX::GetRenderer() const { return const_cast<gva::RendererGva*>(&renderer_); }

}  // namespace gva
