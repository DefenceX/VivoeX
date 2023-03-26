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
/// \file view_gva.h
///

#ifndef HMI_DISPLAY_SRC_VIEW_GVA_H_
#define HMI_DISPLAY_SRC_VIEW_GVA_H_
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/screen_gva.h"
#include "src/touch_gva.h"

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
  explicit ViewGvaManager();
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

#endif  // HMI_DISPLAY_SRC_VIEW_GVA_H_
