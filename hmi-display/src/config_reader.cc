//
// MIT License
//
// Copyright (c) 2023 DefenceX (enquiries@defencex.ai)
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
/// \file config_reader.cc
///

#include "config_reader.h"

#include <glog/logging.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "gva.h"
#include "src/renderer_cairo.h"

namespace gva {

ConfigData* ConfigData::config_ = nullptr;

ConfigDataBase::ConfigDataBase() {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  LOG(ERROR) << "Created new config reader" << std::filesystem::current_path().string() << "/" << config_file_;
  current_config_ = std::make_unique<config::Gva>();

  // Read the existing configuration file.
  if (std::fstream input(config_file_, std::fstream::in | std::fstream::binary); !input) {
    LOG(ERROR) << "File not found. Creating a new file " << std::filesystem::current_path().string() << "/"
               << config_file_;
    current_config_->set_name("Test HMI configuration.");
    // Doesn't write defaults unless they have been set once
    current_config_->set_height(current_config_->height());
    current_config_->set_width(current_config_->width());
  } else if (!current_config_->ParseFromIstream(&input)) {
    LOG(ERROR) << " Failed to parse config file.";
    return;
  }

  // Add arrays here if any.
  current_config_->bindings().empty();

  std::array<config::Key, 33> keys = {
      config::kKeyBLK,       config::kKeySA,         config::kKeyWPN,      config::kKeyDEF, config::kKeySYS,
      config::kKeyDRV,       config::kKeySTR,        config::kKeyCOM,      config::kKeyBMS, config::kKeyF1,
      config::kKeyF2,        config::kKeyF3,         config::kKeyF4,       config::kKeyF5,  config::kKeyF6,
      config::kKeyF7,        config::kKeyF8,         config::kKeyF9,       config::kKeyF10, config::kKeyF11,
      config::kKeyF12,       config::kKeyF13,        config::kKeyF14,      config::kKeyF15, config::kKeyF16,
      config::kKeyF17,       config::kKeyF18,        config::kKeyF19,      config::kKeyF20, config::kKeyUpArrow,
      config::kKeyDownArrow, config::kKeyRightArrow, config::kKeyLeftArrow};

  // These are the default display bindings
  // std::array<uint32_t, 29> default_bind = {
  // 'b',    '1',    '2',    '3',    '4',    '5',    '6',    '7', '8', 0xffbe, 0xffbf, 0xffc0, 0xffc1, 0xffc2,
  // 0xffc3, 0xffc4, 0xffc5, 0xffc6, 0xffc7, 0xffc8, 0xffc9, 'a', 's', 'd',    'f',    'g',    'h',    'j', 0xff52,
  // 0xff54};

  // These are the APC display bindings
  std::array<uint32_t, 33> apc_bind = {'q',    'w',    'e',    'r',    't',    'y',    'u',    'i',    'o',
                                       0xffbe, 0xffbf, 0xffc0, 0xffc1, 0xffc2, 0xffc3, 0xffc4, 0xffc5, 0xffc6,
                                       0xffc7, 0xffc8, 0xffc9, 'a',    's',    'd',    'f',    'g',    'h',
                                       'j',    0xff0d, 0xff54, 0xff52, 0xff53, 0xff51};

  for (std::size_t c = 0; c < keys.size(); c++) {
    auto bindings = current_config_->add_bindings();
    bindings->set_bind(apc_bind[c]);
    bindings->set_key(keys[c]);
  }

  // Write the new config back to disk.
  if (std::fstream output(config_file_, std::fstream::out | std::fstream::trunc | std::fstream::binary);
      !current_config_->SerializeToOstream(&output)) {
    LOG(ERROR) << "Failed to write config file.";
    return;
  }
}

ConfigDataBase::~ConfigDataBase() {
  LOG(INFO) << "Closing config reader.";
  WriteData();
}

ConfigData* ConfigData::GetInstance() {
  //  This is a safer way to create an instance. instance = new Singleton is
  //  dangerous in case GvaKeyEnum::two instance threads wants to access at the same time
  if (config_ == nullptr) {
    config_ = new ConfigData();  // NOLINT, this is needed for singleton creation
  }
  return config_;
}

void ConfigDataBase::WriteData() const {
  // Write the config back to disk.
  if (std::fstream output(config_file_, std::fstream::out | std::fstream::trunc | std::fstream::binary);
      !current_config_->SerializeToOstream(&output)) {
    LOG(INFO) << "Failed to update config file.";
    return;
  }
  // Log
  LOG(INFO) << "Updated configuration file ";
  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();
}

int ConfigData::GetZoom() const { return current_config_->zoom(); }

void ConfigData::SetZoom(int zoom) const { current_config_->set_zoom(zoom); }

double ConfigData::GetTestLon() const { return current_config_->osm().test_lon(); }

void ConfigData::SetTestLon(double lon) const { current_config_->mutable_osm()->set_test_lon(lon); }

double ConfigData::GetTestLat() const { return current_config_->osm().test_lat(); }

void ConfigData::SetTestLat(double lat) const { current_config_->mutable_osm()->set_test_lat(lat); }

bool ConfigData::GetFullscreen() const { return current_config_->fullscreen(); }

void ConfigData::SetFullscreen(bool fullscreen) const { current_config_->set_fullscreen(fullscreen); }

bool ConfigData::GetMapEnabled() const { return current_config_->osm().enabled(); }

void ConfigData::SetMapEnabled(bool enabled) const { current_config_->mutable_osm()->set_enabled(enabled); }

std::string ConfigData::GetMapPath() const { return current_config_->osm().map_path(); }

std::string ConfigData::GetStylesheetPath() const { return current_config_->osm().map_stylesheet_path(); }

uint32_t ConfigDataTheme::GetThemeBackground() const { return (uint32_t)current_config_->theme().theme_background(); }

uint32_t ConfigDataTheme::GetTableBackground() const { return (uint32_t)current_config_->theme().table_background(); }

uint16_t ConfigDataTheme::GetThemeLabelStyle() const { return (uint16_t)current_config_->theme().theme_label_style(); }

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

LineType ConfigDataTheme::GetThemeLabelLineEnabledSelectedChanging() const {
  switch (current_config_->theme().theme_label_line_enabled_selected_changing()) {
    case 1:
      return LineType::kLineDotted;
    case 2:
      return LineType::kLineDashed;
    default:
      return LineType::kLineSolid;
  }
}

LineType ConfigDataTheme::GetThemeLabelLineEnabledSelected() const {
  switch (current_config_->theme().theme_label_line_enabled_selected()) {
    case 1:
      return LineType::kLineDotted;
    case 2:
      return LineType::kLineDashed;
    default:
      return LineType::kLineSolid;
  }
}

LineType ConfigDataTheme::GetThemeLabelLineEnabled() const {
  switch (current_config_->theme().theme_label_line_enabled()) {
    case 1:
      return LineType::kLineDotted;
    case 2:
      return LineType::kLineDashed;
    default:
      return LineType::kLineSolid;
  }
}

LineType ConfigDataTheme::GetThemeLabelLineDisabled() const {
  switch (current_config_->theme().theme_label_line_disabled()) {
    case 1:
      return LineType::kLineDashedLarge;
    case 2:
      return LineType::kLineDotted;
    default:
      return LineType::kLineSolid;
  }
}

widget::ModeEnum ConfigDataTheme::GetPpiMode() const {
  switch (current_config_->theme().widget_ppi_style()) {
    case config::PpiStyle::kPpiClassicTankWithoutSight:
      return widget::ModeEnum::kPpiClassicTankWithoutSight;
    case config::PpiStyle::kPpiClassicArrowWithSight:
      return widget::ModeEnum::kPpiClassicArrowWithSight;
    case config::PpiStyle::kPpiClassicArrowWithoutSight:
      return widget::ModeEnum::kPpiClassicArrowWithoutSight;
    case config::PpiStyle::kPpiModernTankWithSights:
      return widget::ModeEnum::kPpiModernTankWithSights;
    case config::PpiStyle::kPpiModernTankWithoutSights:
      return widget::ModeEnum::kPpiModernTankWithoutSights;
    default:
      return widget::ModeEnum::kPpiClassicTankWithSight;
  }
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

std::string ConfigData::GetImagePath() const {
#if __MINGW64__ || __MINGW32__
  return "./images/";
#else
  return current_config_->file().images_path();
#endif
}

std::string ConfigData::GetGpsDevice() const { return current_config_->gps_device(); }
std::string ConfigData::GetOdbDevice() const { return current_config_->odb_device(); }

uint32_t ConfigData::GetKeyBinding(GvaKeyEnum key) const {
  switch (key) {
    case GvaKeyEnum::kKeyF1:
      return LookupKey(config::Key::kKeyF1);
    case GvaKeyEnum::kKeyF2:
      return LookupKey(config::Key::kKeyF2);
    case GvaKeyEnum::kKeyF3:
      return LookupKey(config::Key::kKeyF3);
    case GvaKeyEnum::kKeyF4:
      return LookupKey(config::Key::kKeyF4);
    case GvaKeyEnum::kKeyF5:
      return LookupKey(config::Key::kKeyF5);
    case GvaKeyEnum::kKeyF6:
      return LookupKey(config::Key::kKeyF6);
    case GvaKeyEnum::kKeyF7:
      return LookupKey(config::Key::kKeyF7);
    case GvaKeyEnum::kKeyF8:
      return LookupKey(config::Key::kKeyF8);
    case GvaKeyEnum::kKeyF9:
      return LookupKey(config::Key::kKeyF9);
    case GvaKeyEnum::kKeyF10:
      return LookupKey(config::Key::kKeyF10);
    case GvaKeyEnum::kKeyF11:
      return LookupKey(config::Key::kKeyF11);
    case GvaKeyEnum::kKeyF12:
      return LookupKey(config::Key::kKeyF12);
    case GvaKeyEnum::kKeyF13:
      return LookupKey(config::Key::kKeyF13);
    case GvaKeyEnum::kKeyF14:
      return LookupKey(config::Key::kKeyF14);
    case GvaKeyEnum::kKeyF15:
      return LookupKey(config::Key::kKeyF15);
    case GvaKeyEnum::kKeyF16:
      return LookupKey(config::Key::kKeyF16);
    case GvaKeyEnum::kKeyF17:
      return LookupKey(config::Key::kKeyF17);
    case GvaKeyEnum::kKeyF18:
      return LookupKey(config::Key::kKeyF18);
    case GvaKeyEnum::kKeyF19:
      return LookupKey(config::Key::kKeyF19);
    case GvaKeyEnum::kKeyF20:
      return LookupKey(config::Key::kKeyF20);
    default:
      break;
  }

  switch (key) {
    case GvaKeyEnum::kKeyBlackout:
      return LookupKey(config::Key::kKeyBLK);
    case GvaKeyEnum::kKeySituationalAwareness:
      return LookupKey(config::Key::kKeySA);
    case GvaKeyEnum::kKeyWeapon:
      return LookupKey(config::Key::kKeyWPN);
    case GvaKeyEnum::kKeyDefensiveSystems:
      return LookupKey(config::Key::kKeyDEF);
    case GvaKeyEnum::kKeySystems:
      return LookupKey(config::Key::kKeySYS);
    case GvaKeyEnum::kKeyDriver:
      return LookupKey(config::Key::kKeyDRV);
    case GvaKeyEnum::kKeySpecialToRole:
      return LookupKey(config::Key::kKeySTR);
    case GvaKeyEnum::kKeyCommunications:
      return LookupKey(config::Key::kKeyCOM);
    case GvaKeyEnum::kKeyBattlefieldManagementSystem:
      return LookupKey(config::Key::kKeyBMS);
    case GvaKeyEnum::kKeyUpArrow:
      return LookupKey(config::Key::kKeyUpArrow);
    case GvaKeyEnum::kKeyDownArrow:
      return LookupKey(config::Key::kKeyDownArrow);
    default:
      break;
  }
  return 0;
}

double ConfigData::GetBrightness() const { return current_config_->brightness(); }

void ConfigData::SetBrightness(double brightness) { current_config_->set_brightness(brightness); }

uint32_t ConfigData::LookupKey(config::Key key) const {
  for (int i = 0; i < current_config_->bindings_size(); i++) {
    if (current_config_->bindings(i).key() == key) return current_config_->bindings(i).bind();
  }
  LOG(INFO) << "Key binding not found " << std::to_string(key);
  return 0;
}

}  // namespace gva
