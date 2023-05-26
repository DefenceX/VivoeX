//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file gva.h
///

#ifndef HMICORE_GVA_H_
#define HMICORE_GVA_H_

#include <array>
#include <string>

namespace gva {

///
/// Constant global type definition
///

/// major version number
static const uint32_t kSemVerMajor = 0;
/// minor version number
static const uint32_t kSemVerMinor = 4;
/// patch version number
static const uint32_t kSemVerPatch = 495;
/// minimum height
static const uint32_t kMinimumHeight = 480;
/// minimum width
static const uint32_t kMinimumWidth = 640;

///
/// Enumerated type definition
///

/// Enum for the location type
enum class LocationEnum { kLocationFormatLongLat = 0, kLocationFormatMgrs };
/// Enum for the screen mode
enum class ScreenMode { kModeMaintenance = 0, kModeOperational, kModeBlackout };
/// Enum for the label mode
enum class LabelModeEnum { kLabelAll, kLabelStatusOnly, kLabelMinimal };
/// Enum for the label states
enum class LabelStates {
  /// Screen is hidden
  kLabelHidden,
  /// Screen is disabled
  kLabelDisabled,
  /// Screen is enabled
  kLabelEnabled,
  /// Screen is enabled and selected
  kLabelEnabledSelected,
  /// Screen is enabled and selected and changing
  kLabelEnabledSelectedChanging
};
/// Enum for the label states
enum class LineType {
  /// Line is solid
  kLineSolid,
  /// Line is dotted
  kLineDotted,
  /// Line is dashed
  kLineDashed,
  /// Line is dashed small
  kLineDashedMedium,
  /// Line is dashed large
  kLineDashedLarge,
};
/// These are physical GVA keys around the display
enum class GvaKeyEnum {
  /// Unknown key
  kKeyUnknown = 0,
  /// The situational awareness key
  kKeySituationalAwareness,
  /// The weapon key
  kKeyWeapon,
  /// The defensive systems key
  kKeyDefensiveSystems,
  /// The systems key
  kKeySystems,
  /// The driver key
  kKeyDriver,
  /// The special to role key
  kKeySpecialToRole,
  /// The communications key
  kKeyCommunications,
  /// The battlefield management system key
  kKeyBattlefieldManagementSystem,
  /// The Function key F1
  kKeyF1,
  /// The Function key F2
  kKeyF2,
  /// The Function key F3
  kKeyF3,
  /// The Function key F4
  kKeyF4,
  /// The Function key F5
  kKeyF5,
  /// The Function key F6
  kKeyF6,
  /// The Function key F7
  kKeyF7,
  /// The Function key F8
  kKeyF8,
  /// The Function key F9
  kKeyF9,
  /// The Function key F10
  kKeyF10,
  /// The Function key F11
  kKeyF11,
  /// The Function key F12
  kKeyF12,
  /// The Function key F13
  kKeyF13,
  /// The Function key F14
  kKeyF14,
  /// The Function key F15
  kKeyF15,
  /// The Function key F16
  kKeyF16,
  /// The Function key F17
  kKeyF17,
  /// The Function key F18
  kKeyF18,
  /// The Function key F19
  kKeyF19,
  /// The Function key F20
  kKeyF20,
  /// Special future use
  kKeyF21,
  /// Special future use
  kKeyF22,
  /// Blackout key, special to AUS-GVA screens
  kKeyBlackout,
  /// Power key
  kKeyPower,
  /// Brightness up key
  KKeyBrightnessUp,
  /// Brightness down key
  kKeyBrightnessDown,
  // These are fake keys that only exist in the software (emulated world)
  kKeyEscape,
  /// The key full screen
  kKeyFullscreen,
  /// The Plus key
  kKeyPlus,
  /// The Minus key
  kKeyMinus,
  /// The Up Arrow key
  kKeyUpArrow,
  /// The Down Arrow key
  kKeyDownArrow,
  /// The Left Arrow key
  kKeyLeftArrow,
  /// The Right Arrow key
  kKeyRightArrow,
  /// The Greater then key
  kKeyGreaterThan,
  /// The Less than key
  kKeyLessThen,
  /// The On Screen Keyboard key
  kKeyKeyboard,
  /// The previous label key
  kKeyPreviousLabel,
  /// The next label key
  kKeyNextLabel,
  /// Numeric key 0
  kKeyKeyboard_0,
  /// Numeric key 1
  kKeyKeyboard_1,
  /// Numeric key 2
  kKeyKeyboard_2,
  /// Numeric key 3
  kKeyKeyboard_3,
  /// Numeric key 4
  kKeyKeyboard_4,
  /// Numeric key 5
  kKeyKeyboard_5,
  /// Numeric key 6
  kKeyKeyboard_6,
  /// Numeric key 7
  kKeyKeyboard_7,
  /// Numeric key 8
  kKeyKeyboard_8,
  /// Numeric key 9
  kKeyKeyboard_9,
};
/// HMI erro types, can be extended if needed
enum class GvaStatusTypes { kGvaSuccess = 0, kGvaError, kGvaNetworkError, kGvaDdsError, kGvaXmlError, kGvaRtpError };
/// Enum for the widget types
enum class EventEnumType {
  /// No event
  kNoEvent = 0,
  /// Key event
  kKeyEventPressed,
  /// Key event released
  kKeyEventReleased,
  /// Touch event
  kTouchEvent,
  /// A DDS message
  kDdsEvent,
  /// A resize event
  kResizeEvent,
  /// A redraw event
  kRedrawEvent,
  /// A widget update event
  kWidgetUpdate
};

/// Enum for the surface types
enum class SurfaceType {
  kSurfaceNone = 0,
  kSurfaceBlackout,
  kSurfaceFile,
  kSurfaceVideo,
  kSurfaceRgb24,
  kSurfaceCairo
};

/// This is where you define all your screens, these are just the defaults
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
///  These are the alarm types
enum class GvaAlarmType { kAlarmWarnings, kAlarmCaution, kAlarmAdvisory };
/// These are the functional groups
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
/// Class definitions
///

///
/// \brief Base class implementing basic label state changes and checks.
///
///
class StateBase {
 public:
  ///
  /// \brief Check if the label is active
  ///
  /// \param state
  /// \return true
  /// \return false
  ///
  bool IsActive(const LabelStates* state) const {
    return ((*state != LabelStates::kLabelDisabled) && (*state != LabelStates::kLabelHidden));
  }

  ///
  /// \brief Set the label to EnabledSelectedChanging
  ///
  /// \param state
  ///
  void StateEnabledSelectedChanging(LabelStates* state) const {
    if ((*state != LabelStates::kLabelDisabled) && (*state != LabelStates::kLabelHidden)) {
      *state = LabelStates::kLabelEnabledSelectedChanging;
    }
  }

  ///
  /// \brief Set the label to EnabledSelected
  ///
  /// \param state
  ///
  void StateEnabledSelected(LabelStates* state) const {
    if ((*state != LabelStates::kLabelDisabled) && (*state != LabelStates::kLabelHidden)) {
      *state = LabelStates::kLabelEnabledSelected;
    }
  }

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  /// \param state
  ///
  void ResetEnabled(LabelStates* state) const {
    if ((*state == LabelStates::kLabelEnabledSelected) || (*state == LabelStates::kLabelEnabledSelectedChanging)) {
      *state = LabelStates::kLabelEnabled;
    }
  }

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  /// \param state
  ///
  void ResetEnabledSelected(LabelStates* state) const {
    if (*state == LabelStates::kLabelEnabledSelected) {
      *state = LabelStates::kLabelEnabled;
    }
  }

  ///
  /// \brief Reset the label from 'enabled selected changing' to 'enabled'
  ///
  /// \param state
  ///
  void ResetEnabledSelectedChanging(LabelStates* state) const {
    if (*state == LabelStates::kLabelEnabledSelectedChanging) {
      *state = LabelStates::kLabelEnabled;
    }
  }
};

///
/// \brief These are the labels on the left and right of the screen
///
///
class FunctionSelect : public StateBase {
 public:
  /// The label is visible
  bool visible;

  /// Label object
  struct Labels {
    /// The label state
    LabelStates state;
  };
  /// The labels
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

///  These are at the top of the screen
struct FunctionKeys : public StateBase {
  /// The label is visible
  bool visible;
  /// Label object
  struct Labels {
    /// The label state
    LabelStates state;
    /// True if active
    bool toggleActive;
    /// toggle on bool
    bool toggleOn;
    /// The label text
    std::string text;
    /// The label text when toggled on
    std::string toggleText1;
    /// The label text when toggled off
    std::string toggleText2;
  };
  /// The labels text
  std::array<Labels, 6> labels;

  ///
  /// \brief Check if the label is active
  ///
  /// \param index The index of the label
  /// \return true
  /// \return false
  ///
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

/// Class definition of the CommonTaskKeys
class CommonTaskKeys : public StateBase {
 public:
  /// The label is visible
  bool visible_;
  /// Label object
  struct Labels {
    /// The label state
    LabelStates state_;
    /// The label text
    std::string text_;
  };
  /// The labels
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

/// Enum for the location type
struct LocationType {
  /// The location format
  LocationEnum locationFormat;
  /// The location value
  float lat;
  /// The longitude value
  float lon;
};

/// Struct for the colour
struct ColourType {
  /// The red value
  uint32_t red = 0;
  /// The green value
  uint32_t green = 0;
  /// The blue value
  uint32_t blue = 0;
};

/// Struct for the point
struct PointType {
  /// The X position
  int32_t x = 0;
  /// The Y position
  int32_t y = 0;
};

/// Struct for the resolution
struct ResolutionType {
  /// The width of the screen
  uint32_t width = 0;
  /// The height of the screen
  uint32_t height = 0;
  /// The depth of the screen, colour depth
  uint32_t depth = 0;
};

/// Struct for RGB values
struct RgbUnpackedType {
  /// Red
  uint32_t r = 0;
  /// Green
  uint32_t g = 0;
  /// Blue
  uint32_t b = 0;
};

/// Struct for touch events
struct TouchType {
  /// The touch X position
  int x = 0;
  /// The touch Y position
  int y = 0;
};

///
/// \brief This holds additional information on keys
///
///
struct KeyType {
  /// The key pressed
  GvaKeyEnum key = GvaKeyEnum::kKeyUnknown;
  /// Only applicable to labels on screen F1-F20
  LabelStates label_state = LabelStates::kLabelHidden;
};

/// Class definition of the EventGvaType
class EventGvaType {
 public:
  ///
  /// \brief Construct a new Event Gva Type object
  ///
  ///
  EventGvaType() = default;

  ///
  /// \brief Construct a new Event Gva Type object
  ///
  /// \param x The X position
  /// \param y The Y position
  ///
  EventGvaType(int x, int y) {
    touch_.x = x;
    touch_.y = y;
    type_ = EventEnumType::kTouchEvent;
  }

  ///
  /// \brief Construct a new Event Gva Type object
  ///
  /// \param key The key pressed
  ///
  explicit EventGvaType(GvaKeyEnum key) : key_(key) { type_ = EventEnumType::kNoEvent; }

  /// The event type
  EventEnumType type_;
  /// Key pressed
  GvaKeyEnum key_ = GvaKeyEnum::kKeyUnknown;
  /// Touch event
  TouchType touch_;
  /// The resize dimensions
  ResolutionType resize_;
};

}  // namespace gva

#endif  // HMICORE_GVA_H_
