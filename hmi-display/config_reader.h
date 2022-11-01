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
  ConfigData();
  ~ConfigData();
  int GetZoom();
  void SetZoom(int zoom);
  double GetTestLon();
  void SetTestLon(double lon);
  double GetTestLat();
  void SetTestLat(double lat);
  bool GetFullscreen();
  void SetFullscreen(bool fullscreen);
  uint32_t GetThemeBackground();
  uint16_t GetThemeLabelStyle();
  uint32_t GetThemeLabelBackgroundActive();
  uint32_t GetThemeLabelBackgroundInactive();
  uint32_t GetThemeLabelTextActive();
  uint32_t GetThemeLabelTextInactive();
  uint32_t GetThemeLabelBorderSelected();
  uint32_t GetThemeLabelBorderActive();
  uint32_t GetThemeLabelBorderInactive();
  uint32_t GetThemeLabelBorderThickness();
  uint32_t GetThemeStatusBackground();
  uint32_t GetThemeStatusBorder();
  uint32_t GetThemeStatusText();
  uint32_t GetThemeAlert();
  uint32_t GetThemeCritical();
  char* GetThemeFont();

 private:
  config::Gva* current_config_;
};

// Static configuration object
static ConfigData configuration;

}  // namespace gva
#endif
