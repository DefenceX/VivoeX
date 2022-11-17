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
/// \brief HMI Manager
///
/// \file hmi_gva.cc
///

#include "hmi_gva.h"

#include <iostream>

#include "gva.h"
#include "view_gva.h"
#include "widgets/alarm_indicator.h"
#include "widgets/compass.h"

#define CANVAS \
  { true, gva::SURFACE_NONE, "", 0 }
//#define SCREEN { "Situational Awareness", "/dev/ttyUSB0", SA, canvas_, &top_,
//&status_, SYS_FUNCTION_KEYS_LEFT, SYS_FUNCTION_KEYS_RIGHT, COMMON_KEYS,
// COMPASS, keyboard_, alarms_ }
#define init(var, typ, data) \
  {                          \
    typ x = data;            \
    var = x;                 \
  }
#define BIT(b, x) (x & 0x1 << b)
#define SET_CANVAS_PNG(file)                     \
  strcpy(screen_.canvas.filename, file);         \
  screen_.canvas.bufferType = gva::SURFACE_FILE; \
  screen_.canvas.buffer = 0;

namespace gva {

void Hmi::Reset() {
  screen_.status_bar->visible = true;
  Labels(screen_.labels);
  screen_.canvas.visible = false;
  screen_.canvas.bufferType = gva::SURFACE_NONE;
  screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(false);
  screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetY(360 + 28);
  screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetX(161);
  screen_render_->GetWidget(gva::WIDGET_TYPE_KEYBOARD)
      ->SetVisible((screen_render_->GetWidget(gva::WIDGET_TYPE_KEYBOARD)->GetVisible()) ? true : false);
  screen_.table.visible_ = false;
  screen_.control->visible = true;
  screen_.message.visible = false;
  screen_.info.mode = ScreenMode::kModeOperational;
  alarmson_ = false;
}

void Hmi::Labels(gva::LabelModeEnum labels) {
  switch (labels) {
    case LabelModeEnum::kLabelAll:
      if ((screen_.currentFunction == GvaFunctionEnum::kSituationalAwareness) ||
          (screen_.currentFunction == GvaFunctionEnum::kWeapon) ||
          (screen_.currentFunction == GvaFunctionEnum::kDriver))
        screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_.function_left.visible = true;
      screen_.function_right.visible = true;
      screen_.control->visible = true;
      screen_.function_top->visible = true;
      screen_.status_bar->visible = true;
      screen_.status_bar->y = 446;
      screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(true);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetY(360 + 28);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetX(161);
      screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetY(423);
      break;
    case LabelModeEnum::kLabelStatusOnly:
      screen_.function_left.visible = false;
      screen_.function_right.visible = false;
      screen_.control->visible = false;
      screen_.function_top->visible = false;
      screen_.status_bar->visible = true;
      screen_.status_bar->y = 459;
      screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(true);
      screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetY(423);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetY(360 + 42);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetX(161 - 106);
      break;
    case LabelModeEnum::kLabelMinimal:
      screen_.function_left.visible = false;
      screen_.function_right.visible = false;
      screen_.control->visible = false;
      screen_.function_top->visible = false;
      screen_.status_bar->visible = false;
      screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(false);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(false);
      break;
  }
};

void Hmi::KeySide(gva::GvaKeyEnum key) {
  switch (key) {
    case GvaKeyEnum::kKeyF1:
      screen_.function_left.labels[0].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF2:
      screen_.function_left.labels[1].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF3:
      screen_.function_left.labels[2].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF4:
      screen_.function_left.labels[3].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF5:
      screen_.function_left.labels[4].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF6:
      screen_.function_left.labels[5].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF7:
      screen_.function_right.labels[0].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF8:
      screen_.function_right.labels[1].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF9:
      screen_.function_right.labels[2].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF10:
      screen_.function_right.labels[3].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF11:
      screen_.function_right.labels[4].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF12:
      screen_.function_right.labels[5].state = LabelStates::kLabelEnabled;
      break;
  }
}

gva::GvaKeyEnum Hmi::Key(gva::GvaKeyEnum keypress) {
  KeySide(keypress);
  switch (keypress) {
    case GvaKeyEnum::kKeyF13:
      screen_.control->labels[0].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF14:
      if (screen_.currentFunction == GvaFunctionEnum::kAlarmsX)
        screen_.control->labels[1].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF15:
      screen_.control->labels[2].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF16:
      screen_.control->labels[3].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF17:
      screen_.control->labels[4].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF18:
      screen_.control->labels[5].state = LabelStates::kLabelEnabled;
      break;
    case GvaKeyEnum::kKeyF19:
      screen_.control->labels[6].state = LabelStates::kLabelEnabled;
      switch (screen_.labels) {
        case LabelModeEnum::kLabelAll:
          screen_.labels = LabelModeEnum::kLabelStatusOnly;
          break;
        case LabelModeEnum::kLabelStatusOnly:
          screen_.labels = LabelModeEnum::kLabelMinimal;
          break;
        case LabelModeEnum::kLabelMinimal:
          screen_.labels = LabelModeEnum::kLabelAll;
          break;
      }
      Labels(screen_.labels);
      break;
    case GvaKeyEnum::kKeyF20:
      screen_.control->labels[7].state = LabelStates::kLabelEnabled;
      screen_.message.visible = false;
      break;
    default:
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeySA(gva::GvaKeyEnum keypress) {
  const char *path = gva::ConfigData::GetInstance()->GetImagePath();
  std::string filename;

  screen_.function_left.visible = true;
  screen_.function_right.visible = true;

  gva::Compass *compass = static_cast<gva::Compass *>(screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS));

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF2:
      filename = path + "/Quad.png";
      SET_CANVAS_PNG(filename.c_str());
      break;
    case GvaKeyEnum::kKeyF4:
      filename = path + "/FrontRight.png";
      SET_CANVAS_PNG(filename.c_str());
      compass->SetBearing(45);
      break;
    case GvaKeyEnum::kKeyF5:
      filename = path + "/FrontCenter.png";
      SET_CANVAS_PNG(filename.c_str());
      compass->SetBearing(0);
      break;
    case GvaKeyEnum::kKeyF6:
      filename = path + "/FrontLeft.png";
      SET_CANVAS_PNG(filename.c_str());
      compass->SetBearing(315);
      break;
    case GvaKeyEnum::kKeyF10:
      filename = path + "/Right.png";
      SET_CANVAS_PNG(filename.c_str());
      compass->SetBearing(90);
      break;
    case GvaKeyEnum::kKeyF11:
      filename = path + "/Rear.png";
      SET_CANVAS_PNG(filename.c_str());
      compass->SetBearing(180);
      break;
    case GvaKeyEnum::kKeyF12:
      filename = path + "/Left.png";
      SET_CANVAS_PNG(filename.c_str());
      compass->SetBearing(270);
      break;
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyWPN(gva::GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyDEF(gva::GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_ERROR;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeySYS(gva::GvaKeyEnum keypress) {
  screen_.function_left.visible = true;
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
      gva::HmiHelper::TableSystem(&screen_.table);
      break;
    case GvaKeyEnum::kKeyF5:
      gva::HmiHelper::TableLicences(&screen_.table);
      break;
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    case GvaKeyEnum::kKeyF11:
      // Blackout
      screen_.info.mode = (screen_.info.mode == gva::kModeBlackout) ? gva::kModeOperational : gva::kModeBlackout;
      screen_.canvas.visible = true;
      if (screen_.info.mode == gva::kModeBlackout)
        screen_.canvas.bufferType = gva::SURFACE_BLACKOUT;
      else
        screen_.canvas.bufferType = gva::SURFACE_FILE;
      break;
    case GvaKeyEnum::kKeyF12:
      // Exit
      if (gva::RendererCairo::render_.surface) cairo_surface_destroy(gva::RendererCairo::render_.surface);
      g_application_quit(G_APPLICATION(gva::RendererCairo::render_.win.app));
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyDRV(gva::GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeySTR(gva::GvaKeyEnum keypress) {
  screen_.function_right.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyCOM(gva::GvaKeyEnum keypress) {
  screen_.function_right.visible = true;
  screen_.message.visible = true;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF3:
    case GvaKeyEnum::kKeyF4:
    case GvaKeyEnum::kKeyF5:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF9:
    case GvaKeyEnum::kKeyF10:
    case GvaKeyEnum::kKeyF11:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    default:  // Lots of keys we dont care about
      break;
  }
  return keypress;
}

double conv(int zoom) {
  switch (zoom) {
    case 1620000:
      return 0.00006;
    case 640000:
      return 0.00012;
    case 320000:
      return 0.00025;
    case 160000:
      return 0.0005;
    case 80000:
      return 0.001;
    case 40000:
      return 0.002;
    case 20000:
      return 0.004;
    case 10000:
      return 0.008;
    case 5000:
      return 0.016;
    case 2500:
      return 0.048;
    case 1250:
      return 0.112;
    case 625:
      return 0.2;
  }
}

gva::GvaKeyEnum Hmi::KeyBMS(gva::GvaKeyEnum keypress) {
  screen_.function_right.visible = true;
  KeySide(keypress);
  Key(keypress);
#ifdef ENABLE_OSMSCOUT
  bool update = true;
  int zoom_level = configuration.GetZoom();
  switch (keypress) {
    case GvaKeyEnum::kKeyF3:
      // Shift UP
      configuration.SetTestLat(configuration.GetTestLat() + conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF4:
      // Shift DOWN
      configuration.SetTestLat(configuration.GetTestLat() - conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF5:
      // Zoom +
      configuration.SetZoom(zoom_level * 2);
      break;
    case GvaKeyEnum::kKeyF9:
      // Shift LEFT
      configuration.SetTestLon(configuration.GetTestLon() - conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF10:
      // Shift RIGHT
      configuration.SetTestLon(configuration.GetTestLon() + conv(zoom_level));
      break;
    case GvaKeyEnum::kKeyF11:
      // Zoom -
      configuration.SetZoom(zoom_level / 2);
      break;
    case GvaKeyEnum::kKeyF1:
    case GvaKeyEnum::kKeyF2:
    case GvaKeyEnum::kKeyF6:
    case GvaKeyEnum::kKeyF7:
    case GvaKeyEnum::kKeyF8:
    case GvaKeyEnum::kKeyF12:
      screen_.message.visible = true;
      screen_.message.icon = ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
    default:
      update = false;
      break;
  }

  if (update) {
    char tmp[100];
    sprintf(tmp, "[BMS] Zoom level %d lat %f, %f", configuration.GetZoom(), configuration.GetTestLat(),
            ((double)configuration.GetZoom() / 10000000) * ((double)configuration.GetZoom() / 10000));
    logGva::log(tmp, LOG_INFO);
    map_->SetWidth((double)scregvaen_render_->GetWidth() / DEFAULT_WIDTH);
    map_->SetHeight((double)screen_render_->GetHeight() / DEFAULT_HEIGHT);
    sprintf(tmp, "[BMS] res %d x %d", screen_render_->GetWidth(), screen_render_->GetHeight());
    logGva::log(tmp, LOG_INFO);
    map_->Project(configuration.GetZoom(), configuration.GetTestLon(), configuration.GetTestLat(),
                  &screen_.canvas.surface);
    screen_.canvas.bufferType = SURFACE_CAIRO;
  }
#endif
  return keypress;
}

struct StateSA : Hmi {
  void entry() override {
    if (screen_.function_top->labels[0].state != LabelStates::kLabelHidden) {
      screen_ = manager_->GetScreen(GvaFunctionEnum::kSituationalAwareness);
      lastState_ = GvaFunctionEnum::kSituationalAwareness;
      Reset();
      screen_.function_top->labels[0].state = LabelStates::kLabelEnabledSelected;

      if (screen_.labels != LabelModeEnum::kLabelMinimal)
        screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      if (!screen_.canvas.surface) {
        std::string filename;
        filename = gva::ConfigData::GetInstance()->GetImagePath() + "/FrontCenter.png";
        SET_CANVAS_PNG(filename.c_str());
      }
      screen_.function_top->labels[1].state = LabelStates::kLabelEnabledSelected;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeySA(e.key);
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateWPN>();
  };
};

struct StateWPN : Hmi {
  void entry() override {
    if (screen_.function_top->labels[1].state != LabelStates::kLabelHidden) {
      std::string filename;
      screen_ = manager_->GetScreen(GvaFunctionEnum::kWeapon);
      lastState_ = GvaFunctionEnum::kWeapon;
      Reset();

      if (screen_.labels != LabelModeEnum::kLabelMinimal)
        screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_.canvas.visible = true;
      filename = gva::ConfigData::GetInstance()->GetImagePath() + "/FrontCenter.png";
      SET_CANVAS_PNG(filename.c_str());
      screen_.function_top->labels[2].state = LabelStates::kLabelEnabledSelected;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeyWPN(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSA>();
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateDEF>();
  };
};

struct StateDEF : Hmi {
  void entry() override {
    if (screen_.function_top->labels[3].state != LabelStates::kLabelHidden) {
      screen_ = manager_->GetScreen(GvaFunctionEnum::kDefensiveSystems);
      lastState_ = GvaFunctionEnum::kDefensiveSystems;
      Reset();

      screen_.status_bar->visible = true;
      screen_.function_top->visible = true;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeyDEF(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateWPN>();
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateSYS>();
  };
};

struct StateSYS : Hmi {
  void entry() override {
    if (screen_.function_top->labels[3].state != LabelStates::kLabelHidden) {
      char filename[1000];
      screen_ = manager_->GetScreen(GvaFunctionEnum::kSystems);
      lastState_ = GvaFunctionEnum::kSystems;
      Reset();

      screen_.status_bar->labels[3].state = LabelStates::kLabelEnabledSelected;
      screen_.function_top->labels[3].state = LabelStates::kLabelEnabledSelected;
      screen_.canvas.visible = true;
      snprintf(filename, sizeof(filename), "%s/%s", gva::ConfigData::GetInstance()->GetImagePath(), "FrontCenter.png";
      SET_CANVAS_PNG(filename);

      gva::HmiHelper::TableSystem(&screen_.table);

      screen_.function_top->labels[3].state = LabelStates::kLabelEnabledSelected;
    }
  };

  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeySYS(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateDEF>();
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateDRV>();
  };
};

struct StateDRV : Hmi {
  void entry() override {
    if (screen_.function_top->labels[4].state != LabelStates::kLabelHidden) {
      screen_ = manager_->GetScreen(GvaFunctionEnum::kDriver);
      lastState_ = GvaFunctionEnum::kDriver;
      Reset();

      if (screen_.labels != LabelModeEnum::kLabelMinimal)
        screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_.status_bar->visible = true;
      screen_.function_top->labels[4].state = LabelStates::kLabelEnabledSelected;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeyDRV(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSYS>();
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateSTR>();
  };
};

struct StateSTR : Hmi {
  void entry() override {
    if (screen_.function_top->labels[5].state != LabelStates::kLabelHidden) {
      screen_ = manager_->GetScreen(GvaFunctionEnum::KSpecialToRole);
      lastState_ = GvaFunctionEnum::KSpecialToRole;
      Reset();

      screen_.function_top->labels[5].state = LabelStates::kLabelEnabledSelected;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeySTR(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateDRV>();
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateCOM>();
  };
};

struct StateCOM : Hmi {
  void entry() override {
    if (screen_.function_top->labels[6].state != LabelStates::kLabelHidden) {
      screen_ = manager_->GetScreen(GvaFunctionEnum::kCommunications);
      lastState_ = GvaFunctionEnum::kCommunications;
      Reset();

      screen_.function_top->labels[6].state = LabelStates::kLabelEnabledSelected;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeyCOM(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateSTR>();
    if (e.key == GvaKeyEnum::kKeyNextLabel) transit<StateBMS>();
  };
};

struct StateBMS : Hmi {
  void entry() override {
    if (screen_.function_top->labels[7].state != LabelStates::kLabelHidden) {
      screen_ = manager_->GetScreen(GvaFunctionEnum::kBattlefieldManagementSystem);
      lastState_ = GvaFunctionEnum::kBattlefieldManagementSystem;
      Reset();

      screen_.canvas.visible = true;
#ifdef ENABLE_OSMSCOUT
      map_->SetWidth((double)screen_render_->GetWidth() / DEFAULT_WIDTH);
      map_->SetHeight((double)screen_render_->GetHeight() / DEFAULT_HEIGHT);
      map_->Project(configuration.GetZoom(), configuration.GetTestLon(), configuration.GetTestLat(),
                    &screen_.canvas.surface);
      screen_.canvas.bufferType = SURFACE_CAIRO;
#endif
      screen_.function_top->labels[7].state = LabelStates::kLabelEnabledSelected;
    }
  };
  void react(EventKeyPowerOn const &) override { transit<StateOff>(); };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) {
    KeyBMS(e.key);
    if (e.key == GvaKeyEnum::kKeyPreviousLabel) transit<StateCOM>();
  };
};

struct StateAlarms : Hmi {
  void entry() override {
    if (!BIT(1, screen_.control->hidden)) {
      if (alarmson_) {
        alarmson_ = false;
        switch (lastState_) {
          case GvaFunctionEnum::kSituationalAwareness:
            transit<StateSA>();
            return;
          case GvaFunctionEnum::kWeapon:
            transit<StateWPN>();
            return;
          case GvaFunctionEnum::kDefensiveSystems:
            transit<StateDEF>();
            return;
          case GvaFunctionEnum::kSystems:
            transit<StateSYS>();
            return;
          case GvaFunctionEnum::kDriver:
            transit<StateDRV>();
            return;
          case GvaFunctionEnum::KSpecialToRole:
            transit<StateSTR>();
            return;
          case GvaFunctionEnum::kCommunications:
            transit<StateCOM>();
            return;
          case GvaFunctionEnum::kBattlefieldManagementSystem:
            transit<StateBMS>();
            return;
        }
      }
      Reset();
      alarmson_ = true;
      screen_ = manager_->GetScreen(GvaFunctionEnum::kAlarmsX);
      gva::HmiHelper::TableAlarms(&screen_.table);
    }
  };
  void react(EventKeySA const &) override { transit<StateSA>(); };
  void react(EventKeyWPN const &) override { transit<StateWPN>(); };
  void react(EventKeyDEF const &) override { transit<StateDEF>(); };
  void react(EventKeySYS const &) override { transit<StateSYS>(); };
  void react(EventKeyDRV const &) override { transit<StateDRV>(); };
  void react(EventKeySTR const &) override { transit<StateSTR>(); };
  void react(EventKeyCOM const &) override { transit<StateCOM>(); };
  void react(EventKeyBMS const &) override { transit<StateBMS>(); };
  void react(EventKeyAlarms const &) override { transit<StateAlarms>(); };
  void react(EventKeyFunction const &e) { Key(e.key); };
};

struct StateOn : Hmi {
  void entry() override {
    /* 4:3 aspect ratio @ lowest resolution */
    view_ = {MIN_WIDTH, MIN_HEIGHT, 24};

    if (!manager_) manager_ = new gva::ViewGvaManager(&status_);

#ifdef ENABLE_OSMSCOUT
    // Render a map for BMS
    map_ = new rendererMap("/opt/osmscout/maps/australia-latest/", "/opt/osmscout/stylesheets/standard.oss", MIN_WIDTH,
                           MIN_HEIGHT);
#endif

    init(top_, gva::FunctionSelect, COMMON_FUNCTION_KEYS_TOP);
    init(bottom_, gva::CommonTaskKeys, COMMON_KEYS);
    init(status_, gva::StatusBarType, COMMON_STATUS_BAR);
    init(canvas_, gva::Canvas, CANVAS);

    // Setup the main screens
    manager_->GetNewView(GvaFunctionEnum::kSituationalAwareness, &top_, &bottom_,
                         (gva::FunctionKeys)SA_FUNCTION_KEYS_LEFT, (gva::FunctionKeys)SA_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kWeapon, &top_, &bottom_, (gva::FunctionKeys)WPN_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)WPN_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kDefensiveSystems, &top_, &bottom_, (gva::FunctionKeys)DEF_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)DEF_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kSystems, &top_, &bottom_, (gva::FunctionKeys)SYS_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)SYS_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kDriver, &top_, &bottom_, (gva::FunctionKeys)DRV_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)DRV_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::KSpecialToRole, &top_, &bottom_, (gva::FunctionKeys)STR_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)STR_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kCommunications, &top_, &bottom_, (gva::FunctionKeys)COM_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)COM_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kBattlefieldManagementSystem, &top_, &bottom_,
                         (gva::FunctionKeys)BMS_FUNCTION_KEYS_LEFT, (gva::FunctionKeys)BMS_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(GvaFunctionEnum::kAlarmsX, &top_, &bottom_, (gva::FunctionKeys)ALARM_KEYS_LEFT,
                         (gva::FunctionKeys)ALARM_KEYS_RIGHT);

    screen_ = manager_->GetScreen(GvaFunctionEnum::kSystems);

    // Create the screen render now
    screen_render_ = new gva::ScreenGva(&screen_, view_.width, view_.height);

    // Configure the widgets
    ((gva::Compass *)screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS))->bearingSight_ = 33;
    screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetX(161);
    screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetY(360 + 28);
    screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
    screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetVisible(true);
    screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR)->SetY(422);
    gva::AlarmIndicator *ai = (gva::AlarmIndicator *)screen_render_->GetWidget(gva::WIDGET_TYPE_ALARM_INDICATOR);
    strcpy(ai->text_, "Engine over temperature");

    screen_.canvas = canvas_;
    screen_.canvas.visible = true;
    screen_.table = alarms_;
    screen_.table.visible_ = false;
    screen_.labels = LabelModeEnum::kLabelAll;
    SET_CANVAS_PNG("FRONT_CENTRE.png";

    transit<StateSYS>();
  };
};

struct StateOff : Hmi {
  void entry() override {
    free(screen_render_);
    free(manager_);
    screen_render_ = 0;
    manager_ = 0;
  };
  void react(EventKeyPowerOn const &) override { transit<StateOn>(); };
};

gva::ViewGvaManager *Hmi::manager_;
gva::ResolutionType Hmi::view_;
gva::StatusBarType Hmi::status_;
gva::FunctionSelect Hmi::top_;
gva::CommonTaskKeys Hmi::bottom_;
gva::Canvas Hmi::canvas_;
gva::TableWidget Hmi::alarms_;
gva::Screen Hmi::screen_;
gva::ScreenGva *Hmi::screen_render_;
gva::rendererMap *Hmi::map_;
GvaFunctionEnum Hmi::lastState_;
bool Hmi::alarmson_ = false;

// ----------------------------------------------------------------------------
// Initial state definition
//
FSM_INITIAL_STATE(Hmi, StateOff)

}  // namespace gva
