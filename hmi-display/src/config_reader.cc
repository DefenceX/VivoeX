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

ConfigData::ConfigData() {
  char tmp[100];
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  snprintf(tmp, sizeof(tmp), "Created new config reader %s/%s", std::filesystem::current_path().c_str(),
           config_file_.c_str());

  logGva::log(tmp, LOG_INFO);
  current_config_ = std::make_unique<config::Gva>();
  {
    // Read the existing configuration file.
    std::fstream input(config_file_, std::fstream::in | std::fstream::binary);
    if (!input) {
      snprintf(tmp, sizeof(tmp), "File not found. Creating a new file %s/%s", std::filesystem::current_path().c_str(),
               config_file_.c_str());
      logGva::log(tmp, LOG_INFO);
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

ConfigData::~ConfigData() {
  logGva::log("Closing config reader.", LOG_INFO);
  WriteData();
}

ConfigData* ConfigData::GetInstance() {
  //  This is a safer way to create an instance. instance = new Singleton is
  //  dangerous in case two instance threads wants to access at the same time
  if (config_ == nullptr) {
    config_ = new ConfigData();
  }
  return config_;
}

std::string ConfigData::GetConfigFilename() { return current_config_->file().config_filename(); }

void ConfigData::WriteData() {
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

int ConfigData::GetZoom() { return current_config_->zoom(); }

void ConfigData::SetZoom(int zoom) { current_config_->set_zoom(zoom); }

double ConfigData::GetTestLon() { return current_config_->test_lon(); }

void ConfigData::SetTestLon(double lon) { current_config_->set_test_lon(lon); }

double ConfigData::GetTestLat() { return current_config_->test_lat(); }

void ConfigData::SetTestLat(double lat) { current_config_->set_test_lat(lat); }

bool ConfigData::GetFullscreen() { return current_config_->fullscreen(); }

void ConfigData::SetFullscreen(bool fullscreen) { current_config_->set_fullscreen(fullscreen); }

uint32_t ConfigData::GetThemeBackground() { return (uint32_t)current_config_->theme().theme_background(); }

uint32_t ConfigData::GetTableBackground() { return (uint32_t)current_config_->theme().table_background(); }

uint16_t ConfigData::GetThemeLabelStyle() { return (uint32_t)current_config_->theme().theme_label_style(); }

uint32_t ConfigData::GetThemeLabelBackgroundEnabledSelectedChanging() {
  return (uint32_t)current_config_->theme().theme_label_background_enabled_selected_changing();
}

uint32_t ConfigData::GetThemeLabelBackgroundEnabledSelected() {
  return (uint32_t)current_config_->theme().theme_label_background_enabled_selected();
}

uint32_t ConfigData::GetThemeLabelBackgroundEnabled() {
  return (uint32_t)current_config_->theme().theme_label_background_enabled();
}

uint32_t ConfigData::GetThemeLabelBackgroundDisabled() {
  return (uint32_t)current_config_->theme().theme_label_background_disabled();
}

uint32_t ConfigData::GetThemeLabelTextEnabledSelectedChanging() {
  return (uint32_t)current_config_->theme().theme_label_text_enabled_selected_changing();
}

uint32_t ConfigData::GetThemeLabelTextEnabledSelected() {
  return (uint32_t)current_config_->theme().theme_label_text_enabled_selected();
}

uint32_t ConfigData::GetThemeLabelTextEnabled() {
  return (uint32_t)current_config_->theme().theme_label_text_enabled();
}

uint32_t ConfigData::GetThemeLabelTextDisabled() {
  return (uint32_t)current_config_->theme().theme_label_text_disabled();
}

uint32_t ConfigData::GetThemeLabelBorderEnabledSelectedChanging() {
  return (uint32_t)current_config_->theme().theme_label_border_enabled_selected_changing();
}

uint32_t ConfigData::GetThemeLabelBorderEnabledSelected() {
  return (uint32_t)current_config_->theme().theme_label_border_enabled_selected();
}

uint32_t ConfigData::GetThemeLabelBorderEnabled() {
  return (uint32_t)current_config_->theme().theme_label_border_enabled();
}

uint32_t ConfigData::GetThemeLabelBorderDisabled() {
  return (uint32_t)current_config_->theme().theme_label_border_disabled();
}

uint32_t ConfigData::GetThemeLabelBorderThickness() {
  return (uint32_t)current_config_->theme().theme_label_border_thickness();
}

uint32_t ConfigData::GetThemeTableBorderThickness() {
  return (uint32_t)current_config_->theme().theme_table_border_thickness();
}

uint32_t ConfigData::GetThemeStatusBackground() { return (uint32_t)current_config_->theme().theme_status_background(); }

uint32_t ConfigData::GetThemeStatusBorder() { return (uint32_t)current_config_->theme().theme_status_border(); }

uint32_t ConfigData::GetThemeStatusText() { return (uint32_t)current_config_->theme().theme_status_text(); }

uint32_t ConfigData::GetThemeAlert() { return (uint32_t)current_config_->theme().theme_alert(); }

uint32_t ConfigData::GetThemeCritical() { return (uint32_t)current_config_->theme().theme_critical(); }

const char* ConfigData::GetThemeFont() {
  return reinterpret_cast<const char*>(current_config_->theme().theme_font().c_str());
}

const char* ConfigData::GetLogPath() {
  return reinterpret_cast<const char*>(current_config_->file().log_path().c_str());
}

const char* ConfigData::GetLogFilename() {
  return reinterpret_cast<const char*>(current_config_->file().log_filename().c_str());
}

const char* ConfigData::GetImagePath() {
  return reinterpret_cast<const char*>(current_config_->file().images_path().c_str());
}

}  // namespace gva
