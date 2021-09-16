//
// MIT License
//
// Copyright (c) 2022 Ross Newman (ross@rossnewman.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
// Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#include "config_reader.h"

#include <fstream>
#include <iostream>
#include <string>

#include "log_gva.h"

using namespace std;

#define CONFIG_FILE "./config.pb"

namespace gva {
static config::Gva* configuration_;

ConfigData::ConfigData() {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  current_config_ = new config::Gva();
  {
    // Read the existing address book.
    fstream input(CONFIG_FILE, std::fstream::in | std::fstream::binary);
    if (!input) {
      char tmp[100];
      sprintf(tmp, "%s : File not found. Creating a new file.", CONFIG_FILE);
      logGva::log(tmp, LOG_INFO);
      current_config_->set_name("Test HMI configuration.");
      // Doesnt write defaults unless they have been set once
      current_config_->set_height(current_config_->height());
      current_config_->set_width(current_config_->width());
    } else if (!current_config_->ParseFromIstream(&input)) {
      logGva::log("Failed to parse config file.", LOG_INFO);
      return;
    }
  }
  {
    // Write the new config back to disk.
    fstream output(CONFIG_FILE, std::fstream::out | std::fstream::trunc | std::fstream::binary);
    if (!current_config_->SerializeToOstream(&output)) {
      logGva::log("Failed to write config file.", LOG_INFO);
      return;
    }
  }
}

ConfigData::~ConfigData() {
  // Write the config back to disk.
  fstream output(CONFIG_FILE, std::fstream::out | std::fstream::trunc | std::fstream::binary);
  if (!current_config_->SerializeToOstream(&output)) {
    logGva::log("Failed to update config file.", LOG_INFO);
    return;
  }
  // Log
  logGva::log("Updated configuration file", LOG_INFO);
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();
  free(configuration_);
}

int ConfigData::GetZoom() { return current_config_->zoom(); };

void ConfigData::SetZoom(int zoom) { current_config_->set_zoom(zoom); }

double ConfigData::GetTestLon() { return current_config_->test_lon(); };

void ConfigData::SetTestLon(double lon) { current_config_->set_test_lon(lon); }

double ConfigData::GetTestLat() { return current_config_->test_lat(); };

void ConfigData::SetTestLat(double lat) { current_config_->set_test_lat(lat); }

bool ConfigData::GetFullscreen() { return current_config_->fullscreen(); }

void ConfigData::SetFullscreen(bool fullscreen) { current_config_->set_fullscreen(fullscreen); }

uint32_t ConfigData::GetThemeBackground() { return (uint32_t)current_config_->theme().theme_background(); }

uint16_t ConfigData::GetThemeLabelStyle() { return (uint32_t)current_config_->theme().theme_label_style(); }

uint32_t ConfigData::GetThemeLabelBackgroundActive() {
  return (uint32_t)current_config_->theme().theme_label_background_active();
}

uint32_t ConfigData::GetThemeLabelBackgroundInactive() {
  return (uint32_t)current_config_->theme().theme_label_background_inactive();
}

uint32_t ConfigData::GetThemeLabelTextActive() { return (uint32_t)current_config_->theme().theme_label_text_active(); }

uint32_t ConfigData::GetThemeLabelTextInactive() {
  return (uint32_t)current_config_->theme().theme_label_text_inactive();
}

uint32_t ConfigData::GetThemeLabelBorderSelected() {
  return (uint32_t)current_config_->theme().theme_label_border_selected();
}

uint32_t ConfigData::GetThemeLabelBorderActive() {
  return (uint32_t)current_config_->theme().theme_label_border_active();
}

uint32_t ConfigData::GetThemeLabelBorderInactive() {
  return (uint32_t)current_config_->theme().theme_label_border_inactive();
}

uint32_t ConfigData::GetThemeLabelBorderThickness() {
  return (uint32_t)current_config_->theme().theme_label_border_thickness();
}

uint32_t ConfigData::GetThemeStatusBackground() { return (uint32_t)current_config_->theme().theme_status_background(); }

uint32_t ConfigData::GetThemeStatusBorder() { return (uint32_t)current_config_->theme().theme_status_border(); }

uint32_t ConfigData::GetThemeStatusText() { return (uint32_t)current_config_->theme().theme_status_text(); }

uint32_t ConfigData::GetThemeAlert() { return (uint32_t)current_config_->theme().theme_alert(); }

uint32_t ConfigData::GetThemeCritical() { return (uint32_t)current_config_->theme().theme_critical(); }

char* ConfigData::GetThemeFont() {
  return (char*)current_config_->theme().theme_font().c_str();
  ;
}
}  // namespace gva
