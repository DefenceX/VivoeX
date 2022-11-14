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
/// \brief HMI Manager
///
/// \file hmi_gva.h
///

#ifndef HMI_DISPLAY_SRC_HMI_GVA_H_
#define HMI_DISPLAY_SRC_HMI_GVA_H_
#include <iostream>

#include "src/config_reader.h"
#include "src/hmi_gva_helpers.h"
#include "src/renderer_map.h"
#include "src/screen_gva.h"
#include "src/tinyfsm.h"
#include "src/view_gva.h"

#define LABEL_NULL "Unused!"

//
// These labels should not change
//

//                              Visible    Active    Hidden
#define COMMON_KEYS \
  { true, 0b0010000, 0b10110000, "Up", "Alarms", "Threats", "Ack", "↑", "↓", "Labels", "Enter" }
#define COMMON_FUNCTION_KEYS_TOP \
  { true, 0b01000000, 0b0000100 }
#define COMMON_STATUS_BAR                                                                                    \
  {                                                                                                          \
    true, DEFAULT_HEIGHT - 11, 0, {gva::LOCATION_FORMAT_MGRS, 51.500655, -0.124240}, "12:30:00, 03/06/2019", \
        "LON/LAT", "Lat:51.500655 Lon:-0.124240    [1,3]", "W:0", "A:5", "C:1", "O:2"                        \
  }
#define COMPASS \
  { true, 165, 370, 0, 55 }
//                              Visible    Active    Hidden
#define TEST_FUNCTION_KEYS_LEFT                                      \
  {                                                                  \
    true, 0b000001, 0b011100, { "F1", "F2", "F3", "F4", "F5", "F6" } \
  }
#define TEST_FUNCTION_KEYS_RIGHT                                        \
  {                                                                     \
    true, 0b100000, 0b001111, { "F7", "F8", "F9", "F10", "F11", "F12" } \
  }

//                              Visible    Active    Hidden    Toggle  ToggleOn
#define SA_FUNCTION_KEYS_LEFT                                               \
  {                                                                         \
    true, 0b100000, 0b110111, 0b000000, 0b000000, {                         \
      "Wpn Sight", "Quad", LABEL_NULL, "Front right", "Front", "Front left" \
    }                                                                       \
  }
#define SA_FUNCTION_KEYS_RIGHT                                                                                    \
  {                                                                                                               \
    true, 0b000000, 0b000111, 0b000000, 0b000000, { LABEL_NULL, LABEL_NULL, LABEL_NULL, "Right", "Rear", "Left" } \
  }

#define WPN_FUNCTION_KEYS_LEFT                                                \
  {                                                                           \
    true, 0b100000, 0b110000, 0b000000, 0b000000, {                           \
      "Wpn Sight", "IR Sight", LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                         \
  }
#define WPN_FUNCTION_KEYS_RIGHT                                              \
  {                                                                          \
    true, 0b000000, 0b000000, 0b000000, 0b000000, {                          \
      LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                        \
  }

#define DEF_FUNCTION_KEYS_LEFT                                                                                       \
  {                                                                                                                  \
    true, 0b100000, 0b110000, 0b110000, 0b000000, { "ECM", "Spike", LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL } \
  }
#define DEF_FUNCTION_KEYS_RIGHT                                              \
  {                                                                          \
    true, 0b000000, 0b000000, 0b000000, 0b000000, {                          \
      LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                        \
  }

#define SYS_FUNCTION_KEYS_LEFT                                                                                      \
  {                                                                                                                 \
    true, 0b100000, 0b111111, 0b000000, 0b000000, { "Overview", "Automotive", "HUMS", "System", "Licences", "BIT" } \
  }
#define SYS_FUNCTION_KEYS_RIGHT                                                                        \
  {                                                                                                    \
    true, 0b000000, 0b111111, 0b000000, 0b000000, {                                                    \
      "Commander.Health", "Gunner.Health", "Driver.Health", "Roll.Allocation", "Blackout", "icon:exit" \
    }                                                                                                  \
  }

#define DRV_FUNCTION_KEYS_LEFT                                             \
  {                                                                        \
    true, 0b110000, 0b100000, 0b000000, 0b000000, {                        \
      "Assist", "PPI Mode", LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                      \
  }
#define DRV_FUNCTION_KEYS_RIGHT                                              \
  {                                                                          \
    true, 0b000000, 0b000000, 0b000000, 0b000000, {                          \
      LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                        \
  }

#define STR_FUNCTION_KEYS_LEFT                                               \
  {                                                                          \
    true, 0b000000, 0b000000, 0b000000, 0b000000, {                          \
      LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                        \
  }
#define STR_FUNCTION_KEYS_RIGHT                                              \
  {                                                                          \
    true, 0b000000, 0b000000, 0b000000, 0b000000, {                          \
      LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                        \
  }

#define COM_FUNCTION_KEYS_LEFT                                            \
  {                                                                       \
    true, 0b100000, 0b110000, 0b000000, 0b000000, {                       \
      "Comms", "RF State", LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                     \
  }
#define COM_FUNCTION_KEYS_RIGHT                                              \
  {                                                                          \
    true, 0b000000, 0b000000, 0b000000, 0b000000, {                          \
      LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL, LABEL_NULL \
    }                                                                        \
  }

// #define BMS_FUNCTION_KEYS_LEFT   { true, 0b100000, 0b101111, 0b000000,
// 0b000000, { "Mission", LABEL_NULL, "Shift.up", "Shift.down", "Zoom +",
// "Rotate.>>" } }
#define BMS_FUNCTION_KEYS_LEFT                                                                \
  {                                                                                           \
    true, 0b100000, 0b101111, 0b000000, 0b000000, {                                           \
      "Mission", LABEL_NULL, "icon:uparrow", "icon:downarrow", "icon:plus", "icon:rotateleft" \
    }                                                                                         \
  }
#define BMS_FUNCTION_KEYS_RIGHT                                                                     \
  {                                                                                                 \
    true, 0b000000, 0b001111, 0b000000, 0b000000, {                                                 \
      LABEL_NULL, LABEL_NULL, "icon:leftarrow", "icon:rightarrow", "icon:minus", "icon:rotateright" \
    }                                                                                               \
  }

#define ALARM_KEYS_LEFT                                                        \
  {                                                                            \
    true, 0b000000, 0b111100, 0b000000, 0b000000, {                            \
      "Sort", "Order", "Show.Overridden", "Select.All", LABEL_NULL, LABEL_NULL \
    }                                                                          \
  }
#define ALARM_KEYS_RIGHT                                                  \
  {                                                                       \
    true, 0b000000, 0b111011, 0b000000, 0b000000, {                       \
      "Override", "Clear", "Add Note", LABEL_NULL, "Page.Up", "Page.Down" \
    }                                                                     \
  }

//
// forward declarations
//
struct StateOff;
struct StateSA;
struct StateWPN;
struct StateDEF;
struct StateDRV;
struct StateSYS;
struct StateSTR;
struct StateCOM;
struct StateBMS;
struct StateAlarms;

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
  gva::GvaKeyEnum key;
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
  static gva::ViewGvaManager *manager_;
  static gva::ResolutionType view_;
  static gva::StatusBarType status_;
  static gva::FunctionSelectType top_;
  static gva::CommonTaskKeysType bottom_;
  static gva::CanvasType canvas_;
  static gva::TableWidget alarms_;
  static gva::ScreenType screen_;
  static gva::ScreenGva *screen_render_;
  static gva::rendererMap *map_;
  static int lastState_;
  static bool alarmson_;

 public:
  static void KeySide(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum Key(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeySA(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeyWPN(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeyDEF(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeySYS(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeyDRV(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeySTR(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeyCOM(gva::GvaKeyEnum key);
  static gva::GvaKeyEnum KeyBMS(gva::GvaKeyEnum key);
  static void Reset();
  static gva::ScreenGva *GetRendrer() { return screen_render_; }
  static gva::ScreenType *GetScreen() { return &screen_; }
  static void Labels(gva::LabelModeEnum labels);
};

using hmi = Hmi;
#endif  // HMI_DISPLAY_SRC_HMI_GVA_H_