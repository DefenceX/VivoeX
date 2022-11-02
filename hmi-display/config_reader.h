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

#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include "config.pb.h"

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
  ConfigData(ConfigData& other) = delete;

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
  /// \brief Get the Theme Label Style object
  ///
  /// \return uint16_t
  ///
  uint16_t GetThemeLabelStyle();

  ///
  /// \brief Get the Theme Label Background Active object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundActive();

  ///
  /// \brief Get the Theme Label Background Inactive object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBackgroundInactive();

  ///
  /// \brief Get the Theme Label Text Active object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextActive();

  ///
  /// \brief Get the Theme Label Text Inactive object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelTextInactive();

  ///
  /// \brief Get the Theme Label Border Selected object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderSelected();

  ///
  /// \brief Get the Theme Label Border Active object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderActive();

  ///
  /// \brief Get the Theme Label Border Inactive object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderInactive();

  ///
  /// \brief Get the Theme Label Border Thickness object
  ///
  /// \return uint32_t
  ///
  uint32_t GetThemeLabelBorderThickness();

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
  ///
  uint32_t GetThemeCritical();

  ///
  /// \brief Get the Theme Font object
  ///
  /// \return char*
  ///
  char* GetThemeFont();

 protected:
  ///
  /// \brief Construct a new Config Data object
  ///
  ///
  ConfigData();
  static ConfigData* config_;

 private:
  config::Gva* current_config_ = nullptr;
};

}  // namespace gva
#endif
