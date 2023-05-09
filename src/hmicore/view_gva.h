//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file view_gva.h
///

#ifndef HMICORE_VIEW_GVA_H_
#define HMICORE_VIEW_GVA_H_
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "hmicore/config_reader.h"
#include "hmicore/gva.h"
#include "hmicore/screen_gva.h"
#include "hmicore/touch_gva.h"

namespace gva {

struct ToggleInfo {
  bool visible;
  bool right_active;
  std::string right_label;
  bool left_active;
  std::string left_label;
};

class LabelAction {
 public:
  void Bind(std::function<int(int parentId, GvaKeyEnum key)> fn) {
    privateCallback = std::bind(fn, std::placeholders::_1, std::placeholders::_2);
  }
  ToggleInfo toggle_;
  std::function<int(int parentId, GvaKeyEnum key)> privateCallback;  // Callback
};

class ViewGva {
 public:
  ViewGva(GvaFunctionEnum function, FunctionSelect *top, CommonTaskKeys *bottom, FunctionKeys left, FunctionKeys right)
      : function_(function), function_top_(top), common_bottom_(bottom), function_left_(left), function_right_(right) {}
  bool Valid() const { return valid_; }
  void Release() { valid_ = false; }
  FunctionSelect *GetTop() { return function_top_; }
  CommonTaskKeys *GetBottom() { return common_bottom_; }
  FunctionKeys *GetLeft() { return &function_left_; }
  FunctionKeys *GetRight() { return &function_right_; }
  GvaFunctionEnum GetFunction() const { return function_; }

 private:
  bool valid_ = true;
  GvaFunctionEnum function_;
  // Screen top
  FunctionSelect *function_top_;
  // Screen bottom
  CommonTaskKeys *common_bottom_;
  // Screen left
  FunctionKeys function_left_;
  std::array<LabelAction, 6> function_left_action_;
  // Screen right
  FunctionKeys function_right_;
  std::array<LabelAction, 6> function_right_action_;
};

class ViewGvaManager {
 public:
  ViewGvaManager();
  void AddNewView(GvaFunctionEnum function, FunctionSelect *top, CommonTaskKeys *bottom, FunctionKeys left,
                  FunctionKeys right);
  void SetScreen(Screen *screen, GvaFunctionEnum function) const;
  ViewGva *GetView(GvaFunctionEnum function);

 private:
  std::vector<ViewGva> views_;
  int idLast_ = 0;
  int id_ = 0;
};

}  // namespace gva

#endif  // HMICORE_VIEW_GVA_H_
