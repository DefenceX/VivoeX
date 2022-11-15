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
/// \brief Config file reader
///
/// \file config_reader.h
///

#ifndef HMI_DISPLAY_SRC_CONFIG_READER_H_
#define HMI_DISPLAY_SRC_CONFIG_READER_H_

#include <memory>
#include <string>

#include "config.pb.h"  // NOLINT

namespace gva {

class ConfigData {
 public:
  ///
  /// \brief Destroy the Config Data object
  ///
  ~ConfigData();

  ///
  /// \brief Singletons should not be cloneable.
  ///
  ConfigData(const ConfigData& other) = delete;

  ///
  /// \brief Singletons should not be assignable.
  ///
  void operator=(const ConfigData&) = delete;

  ///
  /// \brief Write contents of protobuf
  ///
  void WriteData();

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
  std::string GetConfigFilename();

  ///
  /// \brief Get the Zoom object
  ///
  /// \return int
  ///
  int GetZoom();

  ///
  /// \brief Set the Zoom object
  ///
  /// \param zoom
  ///
  void SetZoom(int zoom);

  ///
  /// \brief Get the Test Lon object
  ///
  /// \return double
  ///
  double GetTestLon();

  ///
  /// \brief Set the Test Lon object
  ///
  /// \param lon
  ///
  void SetTestLon(double lon);

  ///
  /// \brief Get the Test Lat object
  ///
  /// \return double
  ///
  double GetTestLat();

  ///
  /// \brief Set the Test Lat object
  ///
  /// \param lat
  ///
  void SetTestLat(double lat);

  ///
  /// \brief Get the Fullscreen object
  ///
  /// \return true
  /// \return false
  ///
  bool GetFullscreen();

  ///
  /// \brief Set the Fullscreen object
  ///
  /// \param fullscreen
  ///
  void SetFullscreen(bool fullscreen);

  ///
  /// \brief Get the Theme Background object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeBackground();

  ///
  /// \brief Get the Table Background object
  ///
  /// \return uint32_t
  ///
  uint32_t GetTableBackground();

  ///
  /// \brief Get the Theme Label Style object
  ///
  /// \return uint16_t
  ///
  uint16_t GetThemeLabelStyle();

  ///
  /// \brief Get the Theme Label Background Enabled Selected Changing object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundEnabledSelectedChanging();

  ///
  /// \brief Get the Theme Label Background Enabled Selected object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundEnabledSelected();

  ///
  /// \brief Get the Theme Label Background Active object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundEnabled();

  ///
  /// \brief Get the Theme Label Background Disabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundDisabled();

  ///
  /// \brief Get the Theme Label Text Enabled Selected Changing object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextEnabledSelectedChanging();

  ///
  /// \brief Get the Theme Label Text Enabled Selected object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextEnabledSelected();

  ///
  /// \brief Get the Theme Label Text Enabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextEnabled();

  ///
  /// \brief Get the Theme Label Text Disabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextDisabled();

  ///
  /// \brief Get the Theme Label Border Enabled Selected Changing object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderEnabledSelectedChanging();

  ///
  /// \brief Get the Theme Label Border Enabled Selected  object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderEnabledSelected();

  ///
  /// \brief Get the Theme Label Border Enabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderEnabled();

  ///
  /// \brief Get the Theme Label Border Disabled object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderDisabled();

  ///
  /// \brief Get the Theme Label Border Thickness object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderThickness();

  ///
  /// \brief Get the Table Label Border Thickness object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeTableBorderThickness();

  ///
  /// \brief Get the Theme Status Background object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeStatusBackground();

  ///
  /// \brief Get the Theme Status Border object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeStatusBorder();

  ///
  /// \brief Get the Theme Status Text object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeStatusText();

  ///
  /// \brief Get the Theme Alert object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeAlert();

  ///
  /// \brief Get the Theme Critical object
  ///
  /// \return uint32_t
  /// HMI_GVA_H
  uint32_t GetThemeCritical();

  ///
  /// \brief Get the Theme Font object
  ///
  /// \return char*
  ///
  const char* GetThemeFont();

  ///
  /// \brief Get the Log Path object
  ///
  /// \return const char*
  ///
  const char* GetLogPath();

  ///
  /// \brief Get the Log Filename object
  ///
  /// \return const char*
  ///
  const char* GetLogFilename();

  ///
  /// \brief Get the Image Path object
  ///
  /// \return const char*
  ///
  const char* GetImagePath();

 protected:
  ///
  /// \brief Construct a new Config Data object
  ///
  ///
  ConfigData();

  static ConfigData* config_;

 private:
  std::unique_ptr<config::Gva> current_config_;
  std::string config_file_ = "config.pb";
};

}  // namespace gva
#endif  // HMI_DISPLAY_SRC_CONFIG_READER_H_
