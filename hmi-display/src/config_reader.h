//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross.newman@defencex.com.au)
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
/// \file config_reader.h
///

#ifndef HMI_DISPLAY_SRC_CONFIG_READER_H_
#define HMI_DISPLAY_SRC_CONFIG_READER_H_

#include <memory>
#include <string>

#include "config.pb.h"  // NOLINT
#include "src/gva.h"
#include "src/widgets/widget_types.h"

namespace gva {

///
/// \brief All the configuration data read in at startup, this is the abstraction layer and file format / type can be
/// anything
///
///
class ConfigDataBase {
 public:
  ///
  /// \brief Construct a new Config Data Base object
  ///
  ///
  ConfigDataBase();

  ///
  /// \brief Destroy the Config Data object
  ///
  ~ConfigDataBase();

  ///
  /// \brief Write contents of protobuf
  ///
  void WriteData() const;

  std::unique_ptr<config::Gva> current_config_;

  std::string config_file_ = "config.pb";
};

class ConfigDataTheme : public ConfigDataBase {
 public:
  ///
  /// \brief Get the Theme Background object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeBackground() const;

  ///
  /// \brief Get the Table Background object
  ///
  /// \return uint32_t
  ///
  uint32_t GetTableBackground() const;

  ///
  /// \brief Get the Theme Label Style object
  ///
  /// \return uint16_t
  ///
  uint16_t GetThemeLabelStyle() const;

  ///
  /// \brief Get the Theme Label Background Enabled Selected Changing object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundEnabledSelectedChanging() const;

  ///
  /// \brief Get the Theme Label Background Enabled Selected object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundEnabledSelected() const;

  ///
  /// \brief Get the Theme Label Background Active object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundEnabled() const;

  ///
  /// \brief Get the Theme Label Background Disabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundDisabled() const;

  ///
  /// \brief Get the Theme Label Text Enabled Selected Changing object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextEnabledSelectedChanging() const;

  ///
  /// \brief Get the Theme Label Text Enabled Selected object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextEnabledSelected() const;

  ///
  /// \brief Get the Theme Label Text Enabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextEnabled() const;

  ///
  /// \brief Get the Theme Label Text Disabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextDisabled() const;

  ///
  /// \brief Get the Theme Label Border Enabled Selected Changing object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderEnabledSelectedChanging() const;

  ///
  /// \brief Get the Theme Label Border Enabled Selected  object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderEnabledSelected() const;

  ///
  /// \brief Get the Theme Label Border Enabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderEnabled() const;

  ///
  /// \brief Get the Theme Label Border Disabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderDisabled() const;

  ///
  /// \brief Get the Theme Label Line Enabled Selected Changing object
  ///
  /// \return LineType
  ///
  LineType GetThemeLabelLineEnabledSelectedChanging() const;

  ///
  /// \brief Get the Theme Label Line Enabled Selected object
  ///
  /// \return LineType
  ///
  LineType GetThemeLabelLineEnabledSelected() const;

  ///
  /// \brief Get the Theme Label Line Enabled object
  ///
  /// \return LineType
  ///
  LineType GetThemeLabelLineEnabled() const;

  ///
  /// \brief Get the Theme Label Line Disabled object
  ///
  /// \return LineType
  ///
  LineType GetThemeLabelLineDisabled() const;

  ///
  /// \brief Get the Ppi Mode object
  ///
  /// \return ModeEnum
  ///
  widget::ModeEnum GetPpiMode() const;

  ///
  /// \brief Get the Theme Label Border Thickness object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderThickness() const;

  ///
  /// \brief Get the Table Label Border Thickness object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeTableBorderThickness() const;

  ///
  /// \brief Get the Theme Status Background object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeStatusBackground() const;

  ///
  /// \brief Get the Theme Status Border object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeStatusBorder() const;

  ///
  /// \brief Get the Theme Status Text object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeStatusText() const;

  ///
  /// \brief Get the Theme Alert object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeAlert() const;

  ///
  /// \brief Get the Theme Critical object
  ///
  /// \return uint32_t
  /// HMI_GVA_H
  uint32_t GetThemeCritical() const;

  ///
  /// \brief Get the Theme Font object
  ///
  /// \return std::string
  ///
  std::string GetThemeFont() const;
};

class ConfigData : public ConfigDataTheme {
 public:
  ///
  /// \brief Singletons should not be cloneable.
  ///
  explicit ConfigData(const ConfigData& other) = delete;

  ///
  /// \brief Singletons should not be assignable.
  ///
  void operator=(ConfigData&) = delete;

  // Static methods should be defined outside the class.

  ///
  /// \brief Get the Instance object
  ///
  /// On the first run, it creates a singleton object and places it
  /// into the static field. On subsequent runs, it returns the client existing
  /// object stored in the static field.
  ///
  /// \return ConfigData*
  ///
  static ConfigData* GetInstance();

  ///
  /// \brief Get the Config Filename object
  ///
  ///
  std::string GetConfigFilename() const;

  ///
  /// \brief Get the Zoom object
  ///
  /// \return int
  ///
  int GetZoom() const;

  ///
  /// \brief Set the Zoom object
  ///
  /// \param zoom
  ///
  void SetZoom(int zoom) const;

  ///
  /// \brief Get the Test Lon object
  ///
  /// \return double
  ///
  double GetTestLon() const;

  ///
  /// \brief Set the Test Lon object
  ///
  /// \param lon
  ///
  void SetTestLon(double lon) const;

  ///
  /// \brief Get the Test Lat object
  ///
  /// \return double
  ///
  double GetTestLat() const;

  ///
  /// \brief Set the Test Lat object
  ///
  /// \param lat
  ///
  void SetTestLat(double lat) const;

  ///
  /// \brief Get the Fullscreen object
  ///
  /// \return true
  /// \return false
  ///
  bool GetFullscreen() const;

  ///
  /// \brief Set the Fullscreen object
  ///
  /// \param fullscreen
  ///
  void SetFullscreen(bool fullscreen) const;

  ///
  /// \brief Get the Map Enabled object
  ///
  /// \return true
  /// \return false
  ///
  bool GetMapEnabled() const;

  ///
  /// \brief Set the Map Enabled object
  ///
  ///
  void SetMapEnabled(bool enabled) const;

  ///
  /// \brief Get the Map Path for the installed OSMScout maps
  ///
  /// \return std::string
  ///
  std::string GetMapPath() const;

  ///
  /// \brief Get the Stylesheet Path for the OSMScout stylesheets
  ///
  /// \return std::string
  ///
  std::string GetStylesheetPath() const;

  ///
  /// \brief Get the Log Path object
  ///
  /// \return std::string
  ///
  std::string GetLogPath() const;

  ///
  /// \brief Get the Log Filename object
  ///
  /// \return std::string
  ///
  std::string GetLogFilename() const;

  ///
  /// \brief Get the Image Path object
  ///
  /// \return std::string
  ///
  std::string GetImagePath() const;

  ///
  /// \brief Get the Gps Device object
  ///
  /// \return std::string
  ///
  std::string GetGpsDevice() const;

 protected:
  ///
  /// \brief Construct a new Config Data object
  ///
  ///
  ConfigData() = default;

  static ConfigData* config_;
};

}  // namespace gva

#endif  // HMI_DISPLAY_SRC_CONFIG_READER_H_
