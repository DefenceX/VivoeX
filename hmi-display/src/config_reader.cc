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
/// \file config_reader.cc
///

#include "config_reader.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "log_gva.h"

namespace gva {

ConfigData* ConfigData::config_ = nullptr;

ConfigDataBase::ConfigDataBase() {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  std::string message = "Created new config reader";
  message.append(std::filesystem::current_path());
  message.append("/");
  message.append(config_file_);
  logGva::log(message, LOG_INFO);
  current_config_ = std::make_unique<config::Gva>();
  {
    // Read the existing configuration file.
    std::fstream input(config_file_, std::fstream::in | std::fstream::binary);
    if (!input) {
      message = "File not found. Creating a new file";
      message.append(std::filesystem::current_path());
      message.append("/");
      message.append(config_file_);
      logGva::log(message, LOG_INFO);
      current_config_->set_name("Test HMI configuration.");
      // Doesn't write defaults unless they have been set once
      current_config_->set_height(current_config_->height());
      current_config_->set_width(current_config_->width());
    } else if (!current_config_->ParseFromIstream(&input)) {
      logGva::log("Failed to parse config file.", LOG_INFO);
      return;
    }
  }
  {
    // Write the new config back to disk.
    std::fstream output(config_file_, std::fstream::out | std::fstream::trunc | std::fstream::binary);
    if (!current_config_->SerializeToOstream(&output)) {
      logGva::log("Failed to write config file.", LOG_INFO);
      return;
    }
  }
}

ConfigDataBase::~ConfigDataBase() {
  logGva::log("Closing config reader.", LOG_INFO);
  WriteData();
}

void ConfigDataBase::WriteData() {
  // Write the config back to disk.
  std::fstream output(config_file_, std::fstream::out | std::fstream::trunc | std::fstream::binary);
  if (!current_config_->SerializeToOstream(&output)) {
    logGva::log("Failed to update config file.", LOG_INFO);
    return;
  }
  // Log
  logGva::log("Updated configuration file", LOG_INFO);
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();
}

ConfigData* ConfigData::GetInstance() {
  //  This is a safer way to create an instance. instance = new Singleton is
  //  dangerous in case two instance threads wants to access at the same time
  if (config_ == nullptr) {
    config_ = new ConfigData();
  }
  return config_;
}

std::string ConfigData::GetConfigFilename() const { return current_config_->file().config_filename(); }

int ConfigData::GetZoom() const { return current_config_->zoom(); }

void ConfigData::SetZoom(int zoom) const { current_config_->set_zoom(zoom); }

double ConfigData::GetTestLon() const { return current_config_->test_lon(); }

void ConfigData::SetTestLon(double lon) const { current_config_->set_test_lon(lon); }

double ConfigData::GetTestLat() const { return current_config_->test_lat(); }

void ConfigData::SetTestLat(double lat) const { current_config_->set_test_lat(lat); }

bool ConfigData::GetFullscreen() const { return current_config_->fullscreen(); }

void ConfigData::SetFullscreen(bool fullscreen) const { current_config_->set_fullscreen(fullscreen); }

uint32_t ConfigDataTheme::GetThemeBackground() const { return (uint32_t)current_config_->theme().theme_background(); }

uint32_t ConfigDataTheme::GetTableBackground() const { return (uint32_t)current_config_->theme().table_background(); }

uint16_t ConfigDataTheme::GetThemeLabelStyle() const { return (uint32_t)current_config_->theme().theme_label_style(); }

uint32_t ConfigDataTheme::GetThemeLabelBackgroundEnabledSelectedChanging() const {
  return (uint32_t)current_config_->theme().theme_label_background_enabled_selected_changing();
}

uint32_t ConfigDataTheme::GetThemeLabelBackgroundEnabledSelected() const {
  return (uint32_t)current_config_->theme().theme_label_background_enabled_selected();
}

uint32_t ConfigDataTheme::GetThemeLabelBackgroundEnabled() const {
  return (uint32_t)current_config_->theme().theme_label_background_enabled();
}

uint32_t ConfigDataTheme::GetThemeLabelBackgroundDisabled() const {
  return (uint32_t)current_config_->theme().theme_label_background_disabled();
}

uint32_t ConfigDataTheme::GetThemeLabelTextEnabledSelectedChanging() const {
  return (uint32_t)current_config_->theme().theme_label_text_enabled_selected_changing();
}

uint32_t ConfigDataTheme::GetThemeLabelTextEnabledSelected() const {
  return (uint32_t)current_config_->theme().theme_label_text_enabled_selected();
}

uint32_t ConfigDataTheme::GetThemeLabelTextEnabled() const {
  return (uint32_t)current_config_->theme().theme_label_text_enabled();
}

uint32_t ConfigDataTheme::GetThemeLabelTextDisabled() const {
  return (uint32_t)current_config_->theme().theme_label_text_disabled();
}

uint32_t ConfigDataTheme::GetThemeLabelBorderEnabledSelectedChanging() const {
  return (uint32_t)current_config_->theme().theme_label_border_enabled_selected_changing();
}

uint32_t ConfigDataTheme::GetThemeLabelBorderEnabledSelected() const {
  return (uint32_t)current_config_->theme().theme_label_border_enabled_selected();
}

uint32_t ConfigDataTheme::GetThemeLabelBorderEnabled() const {
  return (uint32_t)current_config_->theme().theme_label_border_enabled();
}

uint32_t ConfigDataTheme::GetThemeLabelBorderDisabled() const {
  return (uint32_t)current_config_->theme().theme_label_border_disabled();
}

uint32_t ConfigDataTheme::GetThemeLabelBorderThickness() const {
  return (uint32_t)current_config_->theme().theme_label_border_thickness();
}

uint32_t ConfigDataTheme::GetThemeTableBorderThickness() const {
  return (uint32_t)current_config_->theme().theme_table_border_thickness();
}

uint32_t ConfigDataTheme::GetThemeStatusBackground() const {
  return (uint32_t)current_config_->theme().theme_status_background();
}

uint32_t ConfigDataTheme::GetThemeStatusBorder() const {
  return (uint32_t)current_config_->theme().theme_status_border();
}

uint32_t ConfigDataTheme::GetThemeStatusText() const { return (uint32_t)current_config_->theme().theme_status_text(); }

uint32_t ConfigDataTheme::GetThemeAlert() const { return (uint32_t)current_config_->theme().theme_alert(); }

uint32_t ConfigDataTheme::GetThemeCritical() const { return (uint32_t)current_config_->theme().theme_critical(); }

std::string ConfigDataTheme::GetThemeFont() const { return current_config_->theme().theme_font(); }

std::string ConfigData::GetLogPath() const { return current_config_->file().log_path(); }

std::string ConfigData::GetLogFilename() const { return current_config_->file().log_filename(); }

std::string ConfigData::GetImagePath() const { return current_config_->file().images_path(); }

std::string ConfigData::GetGpsDevice() const { return current_config_->gps_device(); }

}  // namespace gva
