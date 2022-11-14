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
  screen_.control->active = 0x0;
  screen_.message.visible = false;
  screen_.info.mode = gva::MODE_OPERATIONAL;
  alarmson_ = false;
}

void Hmi::Labels(gva::LabelModeEnum labels) {
  switch (labels) {
    case gva::LABEL_ALL:
      if ((screen_.currentFunction == gva::SA) || (screen_.currentFunction == gva::WPN) ||
          (screen_.currentFunction == gva::DRV))
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
    case gva::LABEL_STATUS_ONLY:
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
    case gva::LABEL_MINIMAL:
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
  screen_.message.visible = false;
  switch (key) {
    case gva::KEY_F1:
      screen_.function_left.active = 1 << 5;
      break;
    case gva::KEY_F2:
      screen_.function_left.active = 1 << 4;
      break;
    case gva::KEY_F3:
      screen_.function_left.active = 1 << 3;
      break;
    case gva::KEY_F4:
      screen_.function_left.active = 1 << 2;
      break;
    case gva::KEY_F5:
      screen_.function_left.active = 1 << 1;
      break;
    case gva::KEY_F6:
      screen_.function_left.active = 1;
      break;
    case gva::KEY_F7:
      screen_.function_right.active = 1 << 5;
      break;
    case gva::KEY_F8:
      screen_.function_right.active = 1 << 4;
      break;
    case gva::KEY_F9:
      screen_.function_right.active = 1 << 3;
      break;
    case gva::KEY_F10:
      screen_.function_right.active = 1 << 2;
      break;
    case gva::KEY_F11:
      screen_.function_right.active = 1 << 1;
      break;
    case gva::KEY_F12:
      screen_.function_right.active = 1;
      break;
  }
}

gva::GvaKeyEnum Hmi::Key(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;
  screen_.control->active = 0;
  KeySide(keypress);
  switch (keypress) {
    case gva::KEY_F13:
      screen_.control->active = 1 << 7;
      break;
    case gva::KEY_F14:
      if (screen_.currentFunction == gva::ALARMSX) screen_.control->active = 1 << 6;
      break;
    case gva::KEY_F15:
      screen_.control->active = 1 << 5;
      break;
    case gva::KEY_F16:
      screen_.control->active = 1 << 4;
      break;
    case gva::KEY_F17:
      screen_.control->active = 1 << 3;
      break;
    case gva::KEY_F18:
      screen_.control->active = 1 << 2;
      break;
    case gva::KEY_F19:
      screen_.control->active = 1 << 1;
      switch (screen_.labels) {
        case gva::LABEL_ALL:
          screen_.labels = gva::LABEL_STATUS_ONLY;
          break;
        case gva::LABEL_STATUS_ONLY:
          screen_.labels = gva::LABEL_MINIMAL;
          break;
        case gva::LABEL_MINIMAL:
          screen_.labels = gva::LABEL_ALL;
          break;
      }
      Labels(screen_.labels);
      break;
    case gva::KEY_F20:
      screen_.control->active = 1;
      screen_.message.visible = false;
      break;
    default:
      screen_.control->active = 0;
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeySA(gva::GvaKeyEnum keypress) {
  const char *path = gva::ConfigData::GetInstance()->GetImagePath();
  char filename[1000];

  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  gva::Compass *compass = static_cast<gva::Compass *>(screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS));

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F2:
      snprintf(filename, sizeof(filename), "%s/%s", path, "Quad.png");
      SET_CANVAS_PNG(filename);
      break;
    case gva::KEY_F4:
      snprintf(filename, sizeof(filename), "%s/%s", path, "FrontRight.png");
      SET_CANVAS_PNG(filename);
      compass->SetBearing(45);
      break;
    case gva::KEY_F5:
      snprintf(filename, sizeof(filename), "%s/%s", path, "FrontCenter.png");
      SET_CANVAS_PNG(filename);
      compass->SetBearing(0);
      break;
    case gva::KEY_F6:
      snprintf(filename, sizeof(filename), "%s/%s", path, "FrontLeft.png");
      SET_CANVAS_PNG(filename);
      compass->SetBearing(315);
      break;
    case gva::KEY_F10:
      snprintf(filename, sizeof(filename), "%s/%s", path, "Right.png");
      SET_CANVAS_PNG(filename);
      compass->SetBearing(90);
      break;
    case gva::KEY_F11:
      snprintf(filename, sizeof(filename), "%s/%s", path, "Rear.png");
      SET_CANVAS_PNG(filename);
      compass->SetBearing(180);
      break;
    case gva::KEY_F12:
      snprintf(filename, sizeof(filename), "%s/%s", path, "Left.png");
      SET_CANVAS_PNG(filename);
      compass->SetBearing(270);
      break;
    case gva::KEY_F1:
    case gva::KEY_F3:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyWPN(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F1:
    case gva::KEY_F2:
    case gva::KEY_F3:
    case gva::KEY_F4:
    case gva::KEY_F5:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
    case gva::KEY_F10:
    case gva::KEY_F11:
    case gva::KEY_F12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyDEF(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F1:
    case gva::KEY_F2:
    case gva::KEY_F3:
    case gva::KEY_F4:
    case gva::KEY_F5:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
    case gva::KEY_F10:
    case gva::KEY_F11:
    case gva::KEY_F12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_ERROR;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeySYS(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F1:
      gva::HmiHelper::TableSystem(&screen_.table);
      break;
    case gva::KEY_F5:
      gva::HmiHelper::TableLicences(&screen_.table);
      break;
    case gva::KEY_F2:
    case gva::KEY_F3:
    case gva::KEY_F4:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
    case gva::KEY_F10:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
    case gva::KEY_F11:
      // Blackout
      screen_.info.mode = (screen_.info.mode == gva::MODE_BLACKOUT) ? gva::MODE_OPERATIONAL : gva::MODE_BLACKOUT;
      screen_.canvas.visible = true;
      if (screen_.info.mode == gva::MODE_BLACKOUT)
        screen_.canvas.bufferType = gva::SURFACE_BLACKOUT;
      else
        screen_.canvas.bufferType = gva::SURFACE_FILE;
      break;
    case gva::KEY_F12:
      // Exit
      if (gva::RendererCairo::render_.surface) cairo_surface_destroy(gva::RendererCairo::render_.surface);
      g_application_quit(G_APPLICATION(gva::RendererCairo::render_.win.app));
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyDRV(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F1:
    case gva::KEY_F2:
    case gva::KEY_F3:
    case gva::KEY_F4:
    case gva::KEY_F5:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
    case gva::KEY_F10:
    case gva::KEY_F11:
    case gva::KEY_F12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeySTR(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F1:
    case gva::KEY_F2:
    case gva::KEY_F3:
    case gva::KEY_F4:
    case gva::KEY_F5:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
    case gva::KEY_F10:
    case gva::KEY_F11:
    case gva::KEY_F12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
      break;
  }
  return keypress;
}

gva::GvaKeyEnum Hmi::KeyCOM(gva::GvaKeyEnum keypress) {
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;
  screen_.message.visible = false;

  KeySide(keypress);
  Key(keypress);

  switch (keypress) {
    case gva::KEY_F1:
    case gva::KEY_F2:
    case gva::KEY_F3:
    case gva::KEY_F4:
    case gva::KEY_F5:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F9:
    case gva::KEY_F10:
    case gva::KEY_F11:
    case gva::KEY_F12:
      screen_.message.visible = true;
      screen_.message.icon = gva::ICON_INFO;
      strcpy(screen_.message.brief.text, "Function key");
      strcpy(screen_.message.detail.text, "Operation not implemented!");
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
  screen_.function_left.active = 0;
  screen_.function_right.active = 0;

  KeySide(keypress);
  Key(keypress);
#ifdef ENABLE_OSMSCOUT
  bool update = true;
  int zoom_level = configuration.GetZoom();
  switch (keypress) {
    case gva::KEY_F3:
      // Shift UP
      configuration.SetTestLat(configuration.GetTestLat() + conv(zoom_level));
      break;
    case gva::KEY_F4:
      // Shift DOWN
      configuration.SetTestLat(configuration.GetTestLat() - conv(zoom_level));
      break;
    case gva::KEY_F5:
      // Zoom +
      configuration.SetZoom(zoom_level * 2);
      break;
    case gva::KEY_F9:
      // Shift LEFT
      configuration.SetTestLon(configuration.GetTestLon() - conv(zoom_level));
      break;
    case gva::KEY_F10:
      // Shift RIGHT
      configuration.SetTestLon(configuration.GetTestLon() + conv(zoom_level));
      break;
    case gva::KEY_F11:
      // Zoom -
      configuration.SetZoom(zoom_level / 2);
      break;
    case gva::KEY_F1:
    case gva::KEY_F2:
    case gva::KEY_F6:
    case gva::KEY_F7:
    case gva::KEY_F8:
    case gva::KEY_F12:
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
    map_->SetWidth((double)screen_render_->GetWidth() / DEFAULT_WIDTH);
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
    if (!BIT(7, screen_.function_top->hidden)) {
      screen_ = manager_->GetScreen(gva::SA);
      lastState_ = gva::SA;
      Reset();
      screen_.function_top->visible = true;

      if (screen_.labels != gva::LABEL_MINIMAL) screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      if (!screen_.canvas.surface) {
        char filename[1000];
        snprintf(filename, sizeof(filename), "%s/%s", gva::ConfigData::GetInstance()->GetImagePath(),
                 "FrontCenter.png");
        SET_CANVAS_PNG(filename);
      }
      screen_.function_top->active = 0x1 << 7;
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
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateWPN>();
  };
};

struct StateWPN : Hmi {
  void entry() override {
    if (!BIT(6, screen_.function_top->hidden)) {
      char filename[1000];
      screen_ = manager_->GetScreen(gva::WPN);
      lastState_ = gva::WPN;
      Reset();

      if (screen_.labels != gva::LABEL_MINIMAL) screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_.canvas.visible = true;
      snprintf(filename, sizeof(filename), "%s/%s", gva::ConfigData::GetInstance()->GetImagePath(), "FrontCenter.png");
      SET_CANVAS_PNG(filename);
      screen_.function_top->active = 0x1 << 6;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateSA>();
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateDEF>();
  };
};

struct StateDEF : Hmi {
  void entry() override {
    if (!BIT(5, screen_.function_top->hidden)) {
      screen_ = manager_->GetScreen(gva::DEF);
      lastState_ = gva::DEF;
      Reset();

      screen_.status_bar->visible = true;
      screen_.function_top->active = 0x1 << 5;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateWPN>();
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateSYS>();
  };
};

struct StateSYS : Hmi {
  void entry() override {
    if (!BIT(4, screen_.function_top->hidden)) {
      char filename[1000];
      screen_ = manager_->GetScreen(gva::SYS);
      lastState_ = gva::SYS;
      Reset();

      screen_.status_bar->visible = true;
      screen_.function_top->visible = true;
      screen_.canvas.visible = true;
      snprintf(filename, sizeof(filename), "%s/%s", gva::ConfigData::GetInstance()->GetImagePath(), "FrontCenter.png");
      SET_CANVAS_PNG(filename);

      gva::HmiHelper::TableSystem(&screen_.table);

      screen_.function_top->active = 0x1 << 4;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateDEF>();
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateDRV>();
  };
};

struct StateDRV : Hmi {
  void entry() override {
    if (!BIT(3, screen_.function_top->hidden)) {
      screen_ = manager_->GetScreen(gva::DRV);
      lastState_ = gva::DRV;
      Reset();

      if (screen_.labels != gva::LABEL_MINIMAL) screen_render_->GetWidget(gva::WIDGET_TYPE_COMPASS)->SetVisible(true);
      screen_.status_bar->visible = true;
      screen_.function_top->active = 0x1 << 3;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateSYS>();
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateSTR>();
  };
};

struct StateSTR : Hmi {
  void entry() override {
    if (!BIT(2, screen_.function_top->hidden)) {
      screen_ = manager_->GetScreen(gva::STR);
      lastState_ = gva::STR;
      Reset();

      screen_.function_top->active = 0x1 << 2;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateDRV>();
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateCOM>();
  };
};

struct StateCOM : Hmi {
  void entry() override {
    if (!BIT(1, screen_.function_top->hidden)) {
      screen_ = manager_->GetScreen(gva::COM);
      lastState_ = gva::COM;
      Reset();

      screen_.function_top->active = 0x1 << 1;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateSTR>();
    if (e.key == gva::KEY_NEXT_LABEL) transit<StateBMS>();
  };
};

struct StateBMS : Hmi {
  void entry() override {
    if (!BIT(0, screen_.function_top->hidden)) {
      screen_ = manager_->GetScreen(gva::BMS);
      lastState_ = gva::BMS;
      Reset();

      screen_.canvas.visible = true;
#ifdef ENABLE_OSMSCOUT
      map_->SetWidth((double)screen_render_->GetWidth() / DEFAULT_WIDTH);
      map_->SetHeight((double)screen_render_->GetHeight() / DEFAULT_HEIGHT);
      map_->Project(configuration.GetZoom(), configuration.GetTestLon(), configuration.GetTestLat(),
                    &screen_.canvas.surface);
      screen_.canvas.bufferType = SURFACE_CAIRO;
#endif
      screen_.function_top->active = 0x1 << 0;
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
    if (e.key == gva::KEY_PREV_LABEL) transit<StateCOM>();
  };
};

struct StateAlarms : Hmi {
  void entry() override {
    if (!BIT(1, screen_.control->hidden)) {
      if (alarmson_) {
        alarmson_ = false;
        switch (lastState_) {
          case gva::SA:
            transit<StateSA>();
            return;
          case gva::WPN:
            transit<StateWPN>();
            return;
          case gva::DEF:
            transit<StateDEF>();
            return;
          case gva::SYS:
            transit<StateSYS>();
            return;
          case gva::DRV:
            transit<StateDRV>();
            return;
          case gva::STR:
            transit<StateSTR>();
            return;
          case gva::COM:
            transit<StateCOM>();
            return;
          case gva::BMS:
            transit<StateBMS>();
            return;
        }
      }
      Reset();
      alarmson_ = true;
      screen_ = manager_->GetScreen(gva::ALARMSX);
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

    init(top_, gva::FunctionSelectType, COMMON_FUNCTION_KEYS_TOP);
    init(bottom_, gva::CommonTaskKeysType, COMMON_KEYS);
    init(status_, gva::StatusBarType, COMMON_STATUS_BAR);
    init(canvas_, gva::CanvasType, CANVAS);

    // Setup the main screens
    manager_->GetNewView(gva::SA, &top_, &bottom_, (gva::FunctionKeys)SA_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)SA_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::WPN, &top_, &bottom_, (gva::FunctionKeys)WPN_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)WPN_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::DEF, &top_, &bottom_, (gva::FunctionKeys)DEF_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)DEF_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::SYS, &top_, &bottom_, (gva::FunctionKeys)SYS_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)SYS_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::DRV, &top_, &bottom_, (gva::FunctionKeys)DRV_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)DRV_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::STR, &top_, &bottom_, (gva::FunctionKeys)STR_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)STR_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::COM, &top_, &bottom_, (gva::FunctionKeys)COM_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)COM_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::BMS, &top_, &bottom_, (gva::FunctionKeys)BMS_FUNCTION_KEYS_LEFT,
                         (gva::FunctionKeys)BMS_FUNCTION_KEYS_RIGHT);
    manager_->GetNewView(gva::ALARMSX, &top_, &bottom_, (gva::FunctionKeys)ALARM_KEYS_LEFT,
                         (gva::FunctionKeys)ALARM_KEYS_RIGHT);

    screen_ = manager_->GetScreen(gva::SYS);

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
    strcpy(ai->text_, "Engine over tempreture");

    screen_.canvas = canvas_;
    screen_.canvas.visible = true;
    screen_.table = alarms_;
    screen_.table.visible_ = false;
    screen_.labels = gva::LABEL_ALL;
    SET_CANVAS_PNG("FRONT_CENTRE.png");

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
gva::FunctionSelectType Hmi::top_;
gva::CommonTaskKeysType Hmi::bottom_;
gva::CanvasType Hmi::canvas_;
gva::TableWidget Hmi::alarms_;
gva::ScreenType Hmi::screen_;
gva::ScreenGva *Hmi::screen_render_;
gva::rendererMap *Hmi::map_;
int Hmi::lastState_;
bool Hmi::alarmson_ = false;

// ----------------------------------------------------------------------------
// Initial state definition
//
FSM_INITIAL_STATE(Hmi, StateOff)