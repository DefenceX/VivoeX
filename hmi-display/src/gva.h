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
/// \brief GVA Types and version info
///
/// \file gva.h
///

#ifndef HMI_DISPLAY_SRC_GVA_H_
#define HMI_DISPLAY_SRC_GVA_H_

#include <array>
#include <string>

#define MAJOR 0
#define MINOR 3
#define PATCH 2138

#define MIN_HEIGHT 480

enum class SurfaceType { SURFACE_NONE = 0, SURFACE_FILE, SURFACE_BUFFER_RGB24, SURFACE_CAIRO, SURFACE_BLACKOUT };

#define MIN_WIDTH 640

#define RENDER_HEIGHT 1024
#define RENDER_WIDTH 1920

namespace gva {

enum class LocationEnum { kLocationFormatLongLat = 0, kLocationFormatMgrs };

enum class ScreenMode { kModeMaintinance = 0, kModeOperational, kModeBlackout };

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

class FunctionSelect {
 public:
  bool visible;

  struct Labels {
    LabelStates state;
  };
  std::array<Labels, 8> labels;

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  ///
  void Reset() {
    visible = true;
    for (auto& label : labels) {
      if (label.state == LabelStates::kLabelEnabledSelected) label.state = LabelStates::kLabelEnabled;
    }
  }
};

///
/// \brief These are at the top of the screen
///
///
struct FunctionKeys {
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

  ///
  /// \brief Reset the label from 'enabled selected' to 'enabled'
  ///
  ///
  void Reset() {
    visible = true;
    for (auto& label : labels) {
      if (label.state == LabelStates::kLabelEnabledSelected) label.state = LabelStates::kLabelEnabled;
    }
  }
};

///
/// \brief These are at the bottom of the screen
///
///
struct CommonTaskKeys {
  bool visible_;
  struct Labels {
    LabelStates state_;
    std::string text_;
  };
  std::array<CommonTaskKeys::Labels, 8> labels_;
};

struct LocationType {
  LocationEnum locationFormat;
  float lat;
  float lon;
};

struct StatusBar {
  bool visible;
  uint32_t x;
  uint32_t y;
  LocationType location;
  struct Labels {
    LabelStates state;
    std::string text;
  };
  std::array<Labels, 7> labels;
};

enum class SurfaceType { kSurfaceNone = 0, kSurfaceFile, kSurfaceBufferRgb24, kSurfaceCairo, kSurfaceBlackout };

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
enum class GvaFunctionGroupEnum { kTop, kBottom, kLeft, kRight, kAlarmTable, kKeyboard };

///
/// \brief These are physical GVA keys around the display
///
///
enum class GvaKeyEnum {
  kKeyUnknown = 0,
  KKeySituationalAwareness,
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
  kKeyRightArrow,
  kKeyLeftArrow,
  kKeyKeyboard,
  kKeyPreviousLabel,
  kKeyNextLabel
};

///
/// \brief HMI erro types, can be extended if needed
///
///
enum class GvaStatusTypes { kGvaSuccess = 0, kGvaError, kGvaNetworkError, kGvaDdsError, kGvaXmlError, kGvaRtpError };

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_GVA_H_
