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
/// \brief The base class describing the state machine.
///
/// \file base_hmi.h
///

#ifndef HMI_DISPLAY_SRC_STATES_BASE_HMI_H_
#define HMI_DISPLAY_SRC_STATES_BASE_HMI_H_

#include <string>

#include "src/tinyfsm.h"
// #include "src/config_reader.h"
#include "src/gva.h"
// #include "src/hmi_gva_defaults.h"
// #include "src/hmi_gva_helpers.h"
#include "src/renderer_map.h"
#include "src/screen_gva.h"
#include "src/states/base_hmi.h"
#include "src/view_gva.h"

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
  virtual void react(EventKeyPowerOn const &) {}
  virtual void react(EventKeySA const &) {}
  virtual void react(EventKeyWPN const &) {}
  virtual void react(EventKeyDEF const &) {}
  virtual void react(EventKeySYS const &) {}
  virtual void react(EventKeyDRV const &) {}
  virtual void react(EventKeySTR const &) {}
  virtual void react(EventKeyCOM const &) {}
  virtual void react(EventKeyBMS const &) {}
  virtual void react(EventKeyAlarms const &) {}
  virtual void react(EventKeyFunction const &) {}

  // alternative: enforce handling of Toggle in all States (pure virtual)
  // virtual void react(EventToggle const &) = 0;

  virtual void entry(void) {}  // entry actions in some States
  void exit(void) {}           // no exit actions

  // alternative: enforce entry actions in all States (pure virtual)
  // virtual void entry(void) = 0;
 protected:
  static ViewGvaManager *manager_;
  static ResolutionType view_;
  static StatusBar status_;
  static FunctionSelect top_;
  static CommonTaskKeys bottom_;
  static Canvas canvas_;
  static TableWidget alarms_;
  static Screen screen_;
  static ScreenGva *screen_render_;
  static rendererMap *map_;
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
  static void Reset();
  static void SetCanvasPng(std::string file);
  static ScreenGva *GetRendrer() { return screen_render_; }
  static Screen *GetScreen() { return &screen_; }
  static void Labels(LabelModeEnum labels);
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_STATES_BASE_HMI_H_
