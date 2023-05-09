//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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
