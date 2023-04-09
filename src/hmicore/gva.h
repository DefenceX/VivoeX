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
/// \file gva.h
///

#ifndef HMICORE_GVA_H_
#define HMICORE_GVA_H_

#include <array>
#include <string>

enum class SurfaceType { kSurfaceNone = 0, kSurfaceFile, kSurfaceRgb24, kSurfaceCairo, kSurfaceBlackout };

namespace gva {

static const uint32_t kSemVerMajor = 0;
static const uint32_t kSemVerMinor = 4;
static const uint32_t kSemVerPatch = 331;
static const uint32_t kMinimumHeight = 480;
static const uint32_t kMinimumWidth = 640;

enum class LocationEnum { kLocationFormatLongLat = 0, kLocationFormatMgrs };

enum class ScreenMode { kModeMaintenance = 0, kModeOperational, kModeBlackout };

enum class LabelModeEnum { kLabelAll, kLabelStatusOnly, kLabelMinimal };

enum class LabelStates {
  kLabelHidden,
  kLabelDisabled,
  kLabelEnabled,
  kLabelEnabledSelected,
  kLabelEnabledSelectedChanging
};

enum class LineType {
  kLineSolid,
  kLineDotted,
  kLineDashed,
  kLineDashedMedium,
  kLineDashedLarge,
};

///
/// \brief Base class implementing basic label state changes and checks.
///
///
class StateBase {
 public:
  bool IsActive(const LabelStates* state) const {
    return ((*state != LabelStates::kLabelDisabled) && (*state != LabelStates::kLabelHidden));
  }

  void StateEnabledSelectedChanging(LabelStates* state) const {
    if ((*state != LabelStates::kLabelDisabled) && (*state != LabelStates::kLabelHidden)) {
      *state = LabelStates::kLabelEnabledSelectedChanging;
    }
  }
  void StateEnabledSelected(LabelStates* state) const {
    if ((*state != LabelStates::kLabelDisabled) && (*state != LabelStates::kLabelHidden)) {
      *state = LabelStates::kLabelEnabledSelected;
    }
  }
  void ResetEnabled(LabelStates* state) const {
    if ((*state == LabelStates::kLabelEnabledSelected) || (*state == LabelStates::kLabelEnabledSelectedChanging)) {
      *state = LabelStates::kLabelEnabled;
    }
  }

  void ResetEnabledSelected(LabelStates* state) const {
    if (*state == LabelStates::kLabelEnabledSelected) {
      *state = LabelStates::kLabelEnabled;
    }
  }

  void ResetEnabledSelectedChanging(LabelStates* state) const {
    if (*state == LabelStates::kLabelEnabledSelectedChanging) {
      *state = LabelStates::kLabelEnabled;
    }
  }
};

class FunctionSelect : public StateBase {
 public:
  bool visible;

  struct Labels {
    LabelStates state;
  };
  std::array<Labels, 8> labels;

  ///
  /// \brief Set the label to Enabled
  ///
  ///
  void SetEnabledEnabledChanging(int index) { StateEnabledSelectedChanging(&labels[index].state); }

  ///
  /// \brief Set the label to Enabled
  ///
  ///
  void SetEnabled(int index) {
    ResetAllEnabled();
    StateEnabledSelected(&labels[index].state);
  }

  ///
  /// \brief Reset all LabelStates::kLabelEnabledSelected buttons.
  ///
  ///
  void ResetAllEnabled() {
    for (auto& label : labels) {
      ResetEnabled(&label.state);
    }
  }

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  ///
  void ResetAllEnabledSelected() {
    visible = true;
    for (auto& label : labels) {
      ResetEnabledSelected(&label.state);
    }
  }

  ///
  /// \brief Reset and label in the LabelStates::kLabelEnabledSelectedChanging state to
  /// LabelStates::kLabelEnabledSelected
  ///
  ///
  void ResetAllEnabledSelectedChanging() {
    for (auto& label : labels) {
      ResetEnabledSelectedChanging(&label.state);
    }
  }
};

///
/// \brief These are at the top of the screen
///
///
struct FunctionKeys : public StateBase {
  bool visible;
  struct Labels {
    LabelStates state;
    bool toggleActive;
    bool toggleOn;
    std::string text;
    std::string toggleText1;
    std::string toggleText2;
  };
  std::array<Labels, 6> labels;

  bool Active(int index) { return IsActive(&labels[index].state); }

  ///
  /// \brief Set the label to Enabled
  ///
  ///
  void SetEnabledEnabledChanging(int index) { StateEnabledSelectedChanging(&labels[index].state); }

  ///
  /// \brief Set the label to Enabled
  ///
  ///
  void SetEnabled(int index) {
    ResetAllEnabled();
    StateEnabledSelected(&labels[index].state);
  }

  ///
  /// \brief Reset all LabelStates::kLabelEnabledSelected buttons.
  ///
  ///
  void ResetAllEnabled() {
    for (auto& label : labels) {
      ResetEnabled(&label.state);
    }
  }

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  ///
  void ResetAllEnabledSelected() {
    visible = true;
    for (auto& label : labels) {
      ResetEnabledSelected(&label.state);
    }
  }

  ///
  /// \brief Reset and label in the LabelStates::kLabelEnabledSelectedChanging state to
  /// LabelStates::kLabelEnabledSelected
  ///
  ///
  void ResetAllEnabledSelectedChanging() {
    for (auto& label : labels) {
      ResetEnabledSelectedChanging(&label.state);
    }
  }
};

///
/// \brief These are at the bottom of the screen
///
///

class CommonTaskKeys : public StateBase {
 public:
  bool visible_;
  struct Labels {
    LabelStates state_;
    std::string text_;
  };
  std::array<CommonTaskKeys::Labels, 8> labels_;

  ///
  /// \brief Set the label to Enabled
  ///
  ///
  void SetEnabledEnabledChanging(int index) {
    ResetAllEnabledSelected();
    StateEnabledSelectedChanging(&labels_[index].state_);
  }

  ///
  /// \brief Set the label to Enabled
  ///
  ///
  void SetDisabled(int index) { labels_[index].state_ = LabelStates::kLabelDisabled; }

  ///
  /// \brief Set state to EnabledSelected regardless of current state (no checking for valid state transition).
  ///
  /// \param index
  ///
  void ForceEnabledSelected(int index) { labels_[index].state_ = LabelStates::kLabelEnabled; }

  ///
  /// \brief Set the label to EnabledSelected
  ///
  ///
  void SetEnabledSelected(int index) {
    ResetAllEnabled();
    StateEnabledSelected(&labels_[index].state_);
  }

  ///
  /// \brief Reset all LabelStates::kLabelEnabledSelected buttons.
  ///
  ///
  void ResetAllEnabled() {
    for (auto& label : labels_) {
      ResetEnabled(&label.state_);
    }
  }

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  ///
  void ResetAllEnabledSelected() {
    for (auto& label : labels_) {
      ResetEnabledSelected(&label.state_);
    }
  }

  ///
  /// \brief Reset and label in the LabelStates::kLabelEnabledSelectedChanging state to
  /// LabelStates::kLabelEnabledSelected
  ///
  ///
  void ResetAllEnabledSelectedChanging() {
    for (auto& label : labels_) {
      ResetEnabledSelectedChanging(&label.state_);
    }
  }
};

struct LocationType {
  LocationEnum locationFormat;
  float lat;
  float lon;
};

enum class SurfaceType { kSurfaceNone = 0, kSurfaceFile, kSurfaceBufferRgb24, kSurfaceCairo };

///
/// \brief This is where you define all your screens, these are just the defaults
///
///
enum class GvaFunctionEnum {
  kSituationalAwareness = 0,
  kWeapon,
  kDefensiveSystems,
  kSystems,
  kDriver,
  KSpecialToRole,
  kCommunications,
  kBattlefieldManagementSystem,
  kAlarmsX
};

///
/// \brief These are the alarm types
///
///
enum class GvaAlarmType { kAlarmWarnings, kAlarmCaution, kAlarmAdvisory };

///
/// \brief These are the functional groups
///
///
enum class GvaFunctionGroupEnum {
  kTop,
  kBottom,
  kLeft,
  kRight,
  kAlarmTable,
  kKeyboard,
  kAlarmsIndicator,
  kObjectBoxes
};

///
/// \brief These are physical GVA keys around the display
///
///
enum class GvaKeyEnum {
  kKeyUnknown = 0,
  kKeySituationalAwareness,
  kKeyWeapon,
  kKeyDefensiveSystems,
  kKeySystems,
  kKeyDriver,
  kKeySpecialToRole,
  kKeyCommunications,
  kKeyBattlefieldManagementSystem,
  kKeyF1,
  kKeyF2,
  kKeyF3,
  kKeyF4,
  kKeyF5,
  kKeyF6,
  kKeyF7,
  kKeyF8,
  kKeyF9,
  kKeyF10,
  kKeyF11,
  kKeyF12,
  kKeyF13,
  kKeyF14,
  kKeyF15,
  kKeyF16,
  kKeyF17,
  kKeyF18,
  kKeyF19,
  kKeyF20,
  kKeyF21,  // Special future use
  kKeyF22,  // Special future use
  kKeyBlackout,
  kKeyPower,
  KKeyBrightnessUp,
  kKeyBrightnessDown,
  // These are fake keys that only exist in the software (emulated world)
  kKeyEscape,
  kKeyFullscreen,
  kKeyPlus,
  kKeyMinus,
  kKeyUpArrow,
  kKeyDownArrow,
  kKeyLeftArrow,
  kKeyRightArrow,
  kKeyGreaterThan,
  kKeyLessThen,
  kKeyKeyboard,
  kKeyPreviousLabel,
  kKeyNextLabel,
  kKeyKeyboard_0,
  kKeyKeyboard_1,
  kKeyKeyboard_2,
  kKeyKeyboard_3,
  kKeyKeyboard_4,
  kKeyKeyboard_5,
  kKeyKeyboard_6,
  kKeyKeyboard_7,
  kKeyKeyboard_8,
  kKeyKeyboard_9,
};

///
/// \brief HMI erro types, can be extended if needed
///
///
enum class GvaStatusTypes { kGvaSuccess = 0, kGvaError, kGvaNetworkError, kGvaDdsError, kGvaXmlError, kGvaRtpError };

struct ColourType {
  uint32_t red = 0;
  uint32_t green = 0;
  uint32_t blue = 0;
};

struct PointType {
  int32_t x = 0;
  int32_t y = 0;
};

struct ResolutionType {
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t depth = 0;
};

struct RgbUnpackedType {
  uint32_t r = 0;
  uint32_t g = 0;
  uint32_t b = 0;
};

enum class EventEnumType {
  kNoEvent = 0,
  kKeyEventPressed,
  kKeyEventReleased,
  kTouchEvent,
  kDdsEvent,
  kResizeEvent,
  kRedrawEvent,
  kWidgetUpdate
};

struct TouchType {
  int x = 0;
  int y = 0;
};

///
/// \brief This holds additional information on keys
///
///
struct KeyType {
  GvaKeyEnum key = GvaKeyEnum::kKeyUnknown;
  LabelStates label_state = LabelStates::kLabelHidden;  // Only applicable to labels on screen F1-F20
};

class EventGvaType {
 public:
  EventGvaType() = default;
  EventGvaType(int x, int y) {
    touch_.x = x;
    touch_.y = y;
    type_ = EventEnumType::kTouchEvent;
  }
  explicit EventGvaType(GvaKeyEnum key) : key_(key) { type_ = EventEnumType::kNoEvent; }
  EventEnumType type_;
  GvaKeyEnum key_ = GvaKeyEnum::kKeyUnknown;  // Key pressed
  TouchType touch_;                           // Touch event
  ResolutionType resize_;
};

}  // namespace gva

#endif  // HMICORE_GVA_H_
