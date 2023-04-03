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
/// \file view_gva.cc
///

#include "view_gva.h"

#include "screen_gva.h"

namespace gva {

ViewGvaManager::ViewGvaManager() {}

void ViewGvaManager::AddNewView(GvaFunctionEnum function, FunctionSelect *top, CommonTaskKeys *bottom,
                                FunctionKeys left, FunctionKeys right) {
  views_.emplace_back(ViewGva(function, top, bottom, left, right));
  return;
}

void ViewGvaManager::SetScreen(Screen *screen, GvaFunctionEnum function) const {
  for (auto view : views_) {
    if (view.GetFunction() == function) {
      screen->function_top = view.GetTop();
      screen->control = view.GetBottom();
      screen->function_left = *view.GetLeft();
      screen->function_right = *view.GetRight();
      screen->currentFunction = function;
    }
  }
}

ViewGva *ViewGvaManager::GetView(GvaFunctionEnum function) {
  Screen screen = {0};
  for (auto &view : views_) {
    if (view.GetFunction() == function) {
      return &view;
    }
  }
  return nullptr;
}
}  // namespace gva
