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
/// \file base_hmi.h
///

#ifndef HMICORE_STATES_BASE_HMI_H_
#define HMICORE_STATES_BASE_HMI_H_

#include <glog/logging.h>

#include <memory>
#include <string>

#include "hmicore/gva.h"
#include "hmicore/renderer_map.h"
#include "hmicore/screen_gva.h"
#include "hmicore/states/base_hmi.h"
#include "hmicore/tinyfsm.h"
#include "hmicore/view_gva.h"

namespace gva {

//
// Event Declarations
//
struct EventKeyPowerOn : tinyfsm::Event {};
struct EventKeySA : tinyfsm::Event {};
struct EventKeyWPN : tinyfsm::Event {};
struct EventKeyDEF : tinyfsm::Event {};
struct EventKeySYS : tinyfsm::Event {};
struct EventKeyDRV : tinyfsm::Event {};
struct EventKeySTR : tinyfsm::Event {};
struct EventKeyCOM : tinyfsm::Event {};
struct EventKeyBMS : tinyfsm::Event {};
struct EventKeyAlarms : tinyfsm::Event {};
struct EventKeyFunction : tinyfsm::Event {
  GvaKeyEnum key;
};

//
// State Machine Base Class Declaration
//
struct Hmi : tinyfsm::Fsm<Hmi> {
  virtual ~Hmi() = default;
  virtual void react(EventKeyPowerOn const &) { return; }   // Nothing to do in base class
  virtual void react(EventKeySA const &) { return; }        // Nothing to do in base class
  virtual void react(EventKeyWPN const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeyDEF const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeySYS const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeyDRV const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeySTR const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeyCOM const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeyBMS const &) { return; }       // Nothing to do in base class
  virtual void react(EventKeyAlarms const &) { return; }    // Nothing to do in base class
  virtual void react(EventKeyFunction const &) { return; }  // Nothing to do in base class
  virtual void entry(void) { return; }                      // entry actions in some States
  virtual void exit(void) { return; }                       // no exit actions

 protected:
  static std::shared_ptr<ViewGvaManager> manager_;
  static ResolutionType view_;
  static FunctionSelect top_;
  static CommonTaskKeys bottom_;
  static Canvas canvas_;
  static Screen screen_;
  static std::shared_ptr<Updater> updater_;
  static std::shared_ptr<ScreenGva> screen_render_;
  static std::shared_ptr<rendererMap> map_;
  static GvaFunctionEnum lastState_;
  static bool alarmson_;

 public:
  static void KeySide(GvaKeyEnum key);
  static GvaKeyEnum Key(GvaKeyEnum key);
  static GvaKeyEnum KeySA(GvaKeyEnum key);
  static GvaKeyEnum KeyWPN(GvaKeyEnum key);
  static GvaKeyEnum KeyDEF(GvaKeyEnum key);
  static GvaKeyEnum KeySYS(GvaKeyEnum key);
  static GvaKeyEnum KeyDRV(GvaKeyEnum key);
  static GvaKeyEnum KeySTR(GvaKeyEnum key);
  static GvaKeyEnum KeyCOM(GvaKeyEnum key);
  static GvaKeyEnum KeyBMS(GvaKeyEnum key);
  static GvaKeyEnum KeyAlarms(GvaKeyEnum key);  // Nothing to do in base class
  static void Reset();
  static void SetCanvasPng(const std::string &file);
  static ScreenGva *GetRendrer() { return screen_render_.get(); }
  static Screen *GetScreen() { return &screen_; }
  static void Labels(LabelModeEnum labels);
  static void ClearAlarms(std::shared_ptr<ScreenGva> screen_render);
};

}  // namespace gva

#endif  // HMICORE_STATES_BASE_HMI_H_
