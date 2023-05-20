//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
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
/// Event for SA key press
struct EventKeySA : tinyfsm::Event {};
/// Event for WPN key press
struct EventKeyWPN : tinyfsm::Event {};
/// Event for DEF key press
struct EventKeyDEF : tinyfsm::Event {};
/// Event for SYS key press
struct EventKeySYS : tinyfsm::Event {};
/// Event for DRV key press
struct EventKeyDRV : tinyfsm::Event {};
/// Event for STR key press
struct EventKeySTR : tinyfsm::Event {};
/// Event for COM key press
struct EventKeyCOM : tinyfsm::Event {};
/// Event for BMS key press
struct EventKeyBMS : tinyfsm::Event {};
/// Event for Alarms key press
struct EventKeyAlarms : tinyfsm::Event {};
/// Event for Function key press
struct EventKeyFunction : tinyfsm::Event {
  /// The key pressed
  GvaKeyEnum key;
};

//
// State Machine Base Class Declaration
//
struct Hmi : tinyfsm::Fsm<Hmi> {
  virtual ~Hmi() = default;
  /// Nothing to do in base class
  virtual void react(EventKeyPowerOn const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeySA const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyWPN const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyDEF const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeySYS const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyDRV const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeySTR const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyCOM const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyBMS const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyAlarms const &) { return; }
  /// Nothing to do in base class
  virtual void react(EventKeyFunction const &) { return; }
  /// entry actions in some States
  virtual void entry(void) { return; }
  /// no exit actions
  virtual void exit(void) { return; }

 protected:
  /// The HMI manager
  static std::shared_ptr<ViewGvaManager> manager_;
  /// The resolution type
  static ResolutionType view_;
  /// The function select widget
  static FunctionSelect top_;
  /// The common task keys at the bottom of the screen
  static CommonTaskKeys bottom_;
  /// The screen canvas
  static Canvas canvas_;
  /// The screen
  static Screen screen_;
  /// The updater to use
  static std::shared_ptr<Updater> updater_;
  /// The screen render object
  static std::shared_ptr<ScreenGva> screen_render_;
  /// A map object
  static std::shared_ptr<rendererMap> map_;
  /// The last state
  static GvaFunctionEnum lastState_;
  /// True is alarms being displayed
  static bool alarmson_;

 public:
  /// Process side label key presses
  static void KeySide(GvaKeyEnum key);
  /// Process key presses
  static GvaKeyEnum Key(GvaKeyEnum key);
  /// Process SA key press
  static GvaKeyEnum KeySA(GvaKeyEnum key, GvaKeyEnum *current);
  /// Process WPN key press
  static GvaKeyEnum KeyWPN(GvaKeyEnum key);
  /// Process DEF key press
  static GvaKeyEnum KeyDEF(GvaKeyEnum key);
  /// Process SYS key press
  static GvaKeyEnum KeySYS(GvaKeyEnum key);
  /// Process DRV key press
  static GvaKeyEnum KeyDRV(GvaKeyEnum key);
  /// Process STR key press
  static GvaKeyEnum KeySTR(GvaKeyEnum key);
  /// Process COM key press
  static GvaKeyEnum KeyCOM(GvaKeyEnum key);
  /// Process BMS key press
  static GvaKeyEnum KeyBMS(GvaKeyEnum key);
  /// Process Alarms key press
  static GvaKeyEnum KeyAlarms(GvaKeyEnum key);  // Nothing to do in base class
  /// Reset the HMI widgets
  static void Reset();
  /// Set a screen PNG file as background
  static void SetCanvasPng(const std::string &file);
  /// Get the screen render object
  static ScreenGva *GetRendrer() { return screen_render_.get(); }
  /// Get the screen object
  static Screen *GetScreen() { return &screen_; }
  /// Toggle onscreen label states
  static void Labels(LabelModeEnum labels);
  /// Clear the alarms
  static void ClearAlarms(std::shared_ptr<ScreenGva> screen_render);
};

}  // namespace gva

#endif  // HMICORE_STATES_BASE_HMI_H_
