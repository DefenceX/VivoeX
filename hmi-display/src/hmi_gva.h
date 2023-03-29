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
/// \file hmi_gva.h
///

#ifndef HMI_DISPLAY_SRC_HMI_GVA_H_
#define HMI_DISPLAY_SRC_HMI_GVA_H_
#include <iostream>
#include <string>

#include "src/config_reader.h"
#include "src/gva.h"
#include "src/hmi_gva_defaults.h"
#include "src/hmi_gva_helpers.h"
#include "src/renderer_map.h"
#include "src/screen_gva.h"
#include "src/view_gva.h"

namespace gva {

class HmiState {
 public:
  HmiState() {}
  HmiState(HmiState const &) = delete;
  void operator=(HmiState const &) = delete;

  static HmiState &GetInstance() {
    static HmiState instance;  // Guaranteed to be destroyed.
                               // Instantiated on first use.
    return instance;
  }

  void SetCanvasPng(const std::string &file);
  void ResetHmi();
  void Labels(LabelModeEnum labels);
  void KeySide(GvaKeyEnum key);
  GvaKeyEnum Key(GvaKeyEnum keypress);

  void ClearAlarms(std::shared_ptr<ScreenGva> screen_render);
  std::shared_ptr<ViewGvaManager> manager_;
  ResolutionType view_;
  FunctionSelect top_;
  CommonTaskKeys bottom_;
  Canvas canvas_;
  Screen screen_;
  std::shared_ptr<ScreenGva> screen_render_;
  std::shared_ptr<rendererMap> map_;
  GvaFunctionEnum lastState_;
  bool alarmson_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_HMI_GVA_H_
