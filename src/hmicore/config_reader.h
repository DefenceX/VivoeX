//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
///
/// \file config_reader.h
///

#ifndef HMICORE_CONFIG_READER_H_
#define HMICORE_CONFIG_READER_H_

#include <memory>
#include <string>

#include "config.pb.h"  // NOLINT
#include "hmicore/gva.h"
#include "hmicore/widgets/widget_types.h"

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

  /// CThe current config data
  std::unique_ptr<config::Gva> current_config_;

  /// The default config data
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

  ~ConfigData() = delete;

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
  /// \brief Get the Gps Device path to virtual port
  ///
  /// \return std::string
  ///
  std::string GetGpsDevice() const;

  ///
  /// \brief Get the Odb Device path to virtual port
  ///
  /// \return std::string
  ///
  std::string GetOdbDevice() const;

  ///
  /// \brief Get the Key Binding attribute
  ///
  /// \return uint32_t
  ///
  uint32_t GetKeyBinding(GvaKeyEnum key) const;

  ///
  /// \brief Get the Brightness attribute
  ///
  /// \return long
  ///
  double GetBrightness() const;

  ///
  /// \brief Set the Brightness attribute
  ///
  /// \param brightness
  ///
  void SetBrightness(double brightness);

 protected:
  ///
  /// \brief Construct a new Config Data object
  ///
  ///
  ConfigData() = default;

  ///
  /// \brief Lookup the actual key binding value from the config data
  ///
  /// \param key
  /// \return uint32_t
  ///
  uint32_t LookupKey(config::Key key) const;

  static ConfigData* config_;
};

}  // namespace gva

#endif  // HMICORE_CONFIG_READER_H_
