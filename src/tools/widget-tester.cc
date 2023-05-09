//
// Copyright (c) 2023, DefenceX PTY LTD
//
// This file is part of the VivoeX project developed by DefenceX.
//
// Licensed under the Attribution-NonCommercial 4.0 International (CC BY-NC 4.0)
// License. See the LICENSE file in the project root for full license details.
//
/// from the command line using the following to get help:
///
/// \code
/// $ widget-tester -h
/// \endcode This program will loop
/// through all images displaying them on the screen, each image will also be written to disk as a .png file with a
/// transparent background. These images are the ones included in the doxygen user documentation.
///
/// To use this program for testing you can view a single image using its ID. IDs are listed when you run with the -h
/// help option.
///
/// \image html widget_ppi_06.png  "Example classic arrow PPI showing in tool"
/// The above PPI (Plan Position Indicator) has the ID of 0 and so can be viewed using the command line below:
/// \code
/// $ widget-tester -i 0 -o /tmp
/// \endcode
/// The resulting output image will be placed in the /tmp directory.
///
/// To generate all the images you can cycle through all IDs by running the command:
/// \code
/// $ widget-tester -t 500 -o ./images
/// \endcode
///
/// Widgets will be displayed every 500 milliseconds on the screen until all images have been displayed. By not
/// specifying an ID we get all the images, the default timeout to 1 second. All images for all widgets will be placed
/// in the ./images folder
///
/// \file widget-tester.cc
///

#include <cairo.h>
#include <ctype.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ctime>

#include "hmicore/gva.h"
#include "hmicore/hmi_gva_helpers.h"
#include "hmicore/renderer_gva.h"
#include "hmicore/widgets/ai/object_localisation.h"
#include "hmicore/widgets/alarm_indicator.h"
#include "hmicore/widgets/bottom_labels.h"
#include "hmicore/widgets/driver/rpm_fuel.h"
#include "hmicore/widgets/driver/speedometer.h"
#include "hmicore/widgets/keyboard.h"
#include "hmicore/widgets/mode.h"
#include "hmicore/widgets/plan_position_indicator.h"
#include "hmicore/widgets/side_labels.h"
#include "hmicore/widgets/table/table.h"
#include "hmicore/widgets/top_labels.h"
#include "hmicore/widgets/widget_types.h"

DEFINE_string(path, ".", "Path to save images to");
DEFINE_int32(timeout, 1000, "Timeout in milliseconds between widget renders, 1 second if not specified.");
DEFINE_int32(id, 0,
             "The ID of the single widget to render from list below (timeout does not apply here):\n"
             "       0: PPI classic tank site, north facing site\n"
             "       1: PPI classic tank site, east facing site\n"
             "       2: PPI classic tank site, south facing site\n"
             "       3: PPI classic tank site, west facing site\n"
             "       4: PPI classic tank site with no site\n"
             "       5: PPI classic tank site with threats\n"
             "       6: PPI classic arrow site, north facing site\n"
             "       7: PPI classic arrow site, east facing site\n"
             "       8: PPI classic arrow site, south facing site\n"
             "       9: PPI classic arrow site, west facing site\n"
             "       10: PPI classic arrow site with no site\n"
             "       11: PPI classic arrow site, with threats site\n"
             "       12: PPI modern site, north facing site\n"
             "       13: PPI modern site, east facing site\n"
             "       14: PPI modern site, south facing site\n"
             "       15: PPI modern site, west facing site\n"
             "       16: PPI modern site with no site\n"
             "       17: PPI modern site with threats\n"
             "       18: Keyboard, lower case\n"
             "       19: Keyboard, upper case\n"
             "       20: Keyboard, numbers\n"
             "       21: Alarms indicator, advisory\n"
             "       22: Alarms indicator, warning\n"
             "       23: Alarms indicator, caution\n"
             "       24: Labels for top of screen, functional areas\n"
             "       25: Labels for bottom of screen, control\n"
             "       26: Labels for side of screen, used for both left and right hand sides\n"
             "       27: Operator mode, visual indication of the non operational mode/s\n"
             "       28: Table example, example message box/s\n"
             "       29: Table example, sample alarms/s\n"
             "       30: Drivers speed dial/s 10Kph\n"
             "       31: Drivers speed dial/s 40Kph\n"
             "       32: Drivers speed dial/s 100Kph\n"
             "       33: RPM 0\n"
             "       34: RPM 4000\n"
             "       35: Oject localisation people");

const uint32_t kScreenHeight = 480;
const uint32_t kScreenWidth = 640;

std::string path;
static gva::RendererGva renderer(kScreenWidth, kScreenHeight);
static gva::TouchGva touch;  // Dummy to get the interactive widgets to render
static gva::WidgetFunctionKeyToggle key(renderer);
static gva::WidgetPlanPositionIndicator ppi(renderer);
static gva::WidgetKeyboard keyboard(renderer);
static gva::WidgetAlarmIndicator alarmx(renderer, &touch);
static gva::WidgetTopLabels top(renderer, &touch);
static gva::WidgetBottomLabels bottom(renderer, &touch);
static gva::WidgetSideLabels left(renderer, &touch);
static gva::WidgetSideLabels right(renderer, &touch);
static gva::WidgetMode mode(renderer);
static gva::WidgetTable table(renderer, &touch, gva::ConfigData::GetInstance()->GetThemeBackground());
static gva::WidgetDriverSpeedometer driver_speed(renderer);
static gva::WidgetDriverRpmFuel driver_rpm(renderer);
static gva::WidgetObjectLocalisation objects(renderer, &touch);

std::array<gva::WidgetPlanPositionIndicator::ThreatType, 5> threats;

static void do_drawing(cairo_t *, int width, int h);

///
/// \brief Transparent window setup, saves .png files have a transparent layer for the background
///
/// \param win
///
static void tran_setup(GtkWidget *win) {
  GdkScreen *screen;
  GdkVisual *visual;

  gtk_widget_set_app_paintable(win, TRUE);
  screen = gdk_screen_get_default();
  visual = gdk_screen_get_rgba_visual(screen);
  if (visual != NULL && gdk_screen_is_composited(screen)) {
    gtk_widget_set_visual(win, visual);
  }
}

static int counter = 0;

///
/// \brief Manage the GTK3 on draw event, callback
///
/// \param widget
/// \param cr
/// \param user_data
/// \return gboolean
///
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  int width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  do_drawing(cr, width, height);

  if (counter >= 9999) exit(0);

  return FALSE;
}

///
/// \brief A timer to enable looping through images
///
/// \param widget
/// \return gboolean
///
static gboolean time_handler(GtkWidget *widget) {
  gtk_widget_queue_draw(widget);

  return TRUE;
}

///
/// \brief A GTK3 drawing callback to render the required image
///
/// \param cr
/// \param width
/// \param height
///
static void do_drawing(cairo_t *cr, int width, int height) {
  renderer.render_.cr = cr;

  threats[0] = {310, 20, 0xff0000, "Person", false, false};
  threats[1] = {230, 12, 0xff0000, "Person", false, false};
  threats[2] = {90, 13, 0xff0000, "Person", false, false};
  threats[3] = {180, 17, 0x00ff00, "Person", false, false};
  threats[4] = {45, 15, 0xffbf00, "Person", false, false};

  cairo_save(cr);

  renderer.Init(width, height);

  switch (counter) {
    case 0:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 0, 0, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_01.png").c_str());
      break;
    case 1:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 350, 90, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_02.png").c_str());
      break;
    case 2:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 340, 180, 30);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_03.png").c_str());
      break;
    case 3:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 330, 270, 40);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_04.png").c_str());
      break;
    case 4:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithoutSight, 0, 0, 320, 0, 50);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_05.png").c_str());
      break;
    case 5:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.AddThreat(1, threats[0]);
      ppi.AddThreat(2, threats[1]);
      ppi.AddThreat(3, threats[2]);
      ppi.AddThreat(4, threats[3]);
      ppi.AddThreat(5, threats[4]);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 0, 0, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_06.png").c_str());
      ppi.DeleteAllThreats();
      break;
    case 6:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 0, 0, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_07.png").c_str());
      break;
    case 7:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 350, 90, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_08.png").c_str());
      break;
    case 8:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 340, 180, 30);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_09.png").c_str());
      break;
    case 9:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 330, 270, 40);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_10.png").c_str());
      break;
    case 10:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithoutSight, 0, 0, 320, 0, 50);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_11.png").c_str());
      break;
    case 11:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      threats[0].size += 10;
      threats[2].size += 10;
      threats[3].size += 10;
      threats[4].size += 10;
      threats[5].size += 10;
      ppi.AddThreat(1, threats[0]);
      ppi.AddThreat(2, threats[1]);
      ppi.AddThreat(3, threats[2]);
      ppi.AddThreat(4, threats[3]);
      ppi.AddThreat(5, threats[4]);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 0, 0, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_12.png").c_str());
      ppi.DeleteAllThreats();
      break;
    case 12:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 0, 0, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_13.png").c_str());
      break;
    case 13:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 350, 90, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_14.png").c_str());
      break;
    case 14:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 340, 180, 30);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_15.png").c_str());
      break;
    case 15:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 330, 270, 40);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_16.png").c_str());
      break;
    case 16:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithoutSights, 0, 0, 320, 270, 0);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_17.png").c_str());
      break;
    case 17:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      threats[3].rgb_value = 0xff0000;
      threats[4].rgb_value = 0xff0000;
      ppi.AddThreat(1, threats[0]);
      ppi.AddThreat(2, threats[1]);
      ppi.AddThreat(3, threats[2]);
      ppi.AddThreat(4, threats[3]);
      ppi.AddThreat(5, threats[4]);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 350, 90, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_ppi_18.png").c_str());
      break;
    case 18:
      // Keyboard, Lower case
      keyboard.DrawKeyboard(gva::widget::KeyboardModeType::kKeyboardLower);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_keyboard_01.png").c_str());
      break;
    case 19:
      // Keyboard, Upper case
      keyboard.DrawKeyboard(gva::widget::KeyboardModeType::kKeyboardUpper);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_keyboard_02.png").c_str());
      break;
    case 20:
      // Keyboard, numbers
      keyboard.DrawKeyboard(gva::widget::KeyboardModeType::kKeyboardNumbers);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/widget_keyboard_03.png").c_str());
      break;
    case 21:
      // Alarms Indicator Advisory
      alarmx.SetText("Software tester status advisory example message");
      alarmx.SetType(gva::GvaAlarmType::kAlarmAdvisory);
      alarmx.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/alarm_01.png").c_str());
      break;
    case 22:
      // Alarms Indicator Warnings
      alarmx.SetText("Software tester status warning example message");
      alarmx.SetType(gva::GvaAlarmType::kAlarmWarnings);
      alarmx.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/alarm_02.png").c_str());
      break;
    case 23:
      // Alarms Indicator Caution
      alarmx.SetText("Software tester status caution example message");
      alarmx.SetType(gva::GvaAlarmType::kAlarmCaution);
      alarmx.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/alarm_03.png").c_str());
      break;
    case 24:
      // Top
      {
        std::array<gva::FunctionSelect::Labels, 8> labels = {
            gva::LabelStates::kLabelEnabledSelected, gva::LabelStates::kLabelEnabled, gva::LabelStates::kLabelEnabled,
            gva::LabelStates::kLabelEnabled,         gva::LabelStates::kLabelEnabled, gva::LabelStates::kLabelDisabled,
            gva::LabelStates::kLabelEnabled,         gva::LabelStates::kLabelEnabled};
        top.SetLabels(&labels);
        top.Draw();
        renderer.Draw();
        cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/top_labels_01.png").c_str());
      }
      break;
    case 25:
      // Bottom      cairo_translate(cr, width / 2, -height / 2);

      {
        std::array<gva::CommonTaskKeys::Labels, 8> labels = {
            gva::LabelStates::kLabelEnabledSelected, "Up",      gva::LabelStates::kLabelEnabled,  "Alarms",
            gva::LabelStates::kLabelDisabled,        "Threats", gva::LabelStates::kLabelDisabled, "Ack.",
            gva::LabelStates::kLabelEnabled,         "",        gva::LabelStates::kLabelEnabled,  "",
            gva::LabelStates::kLabelEnabled,         "Labels",  gva::LabelStates::kLabelEnabled,  "Enter"};
        bottom.SetLabels(&labels);
        bottom.Draw();
        renderer.Draw();
        cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/bottom_labels_01.png").c_str());
      }
      break;
    case 26:
      // Left
      {
        std::array<gva::FunctionKeys::Labels, 6> labels = {gva::LabelStates::kLabelEnabled,
                                                           true,
                                                           false,
                                                           "ECM",
                                                           "On",
                                                           "Off",
                                                           gva::LabelStates::kLabelEnabled,
                                                           true,
                                                           true,
                                                           "HUMS",
                                                           "On",
                                                           "Off",
                                                           gva::LabelStates::kLabelEnabledSelected,
                                                           false,
                                                           false,
                                                           "Maintenance",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelEnabled,
                                                           false,
                                                           false,
                                                           "Demo",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelEnabled,
                                                           false,
                                                           false,
                                                           "Two lines.of text",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelEnabled,
                                                           false,
                                                           false,
                                                           "icon:uparrow",
                                                           "",
                                                           ""};
        left.SetLabels(&labels);
        left.Draw();
        renderer.Draw();
        cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/side_labels_01.png").c_str());
      }
      break;
    case 27:
      // Mode Indicator
      mode.SetMode("Software Testing Mode");
      mode.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/mode_01.png").c_str());
      break;
    case 28: {
      gva::WidgetTable message_box_table(renderer, &touch,
                                         gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());
      message_box_table.SetX((gva::kMinimumWidth / 2) - 150);
      message_box_table.SetY(20);
      message_box_table.SetWidth(300);
      message_box_table.SetBackgroundColour(gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled());

      uint32_t background = gva::ConfigData::GetInstance()->GetThemeLabelBackgroundEnabled();

      message_box_table.AddRow();
      message_box_table.AddCell("System Information", 100, gva::widget::CellAlignType::kAlignCentre, background);

      message_box_table.AddRow();
      message_box_table.AddCell("This is not right", 100, gva::widget::CellAlignType::kAlignCentre, background);

      message_box_table.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/table_01.png").c_str());

    } break;
    case 29: {
      gva::HmiHelper::TableAlarms(&table);
      table.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/table_02.png").c_str());
    } break;
    case 30: {
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      driver_speed.SetMode(gva::widget::DialType::kDialSpeedKph);
      driver_speed.SetVisible(true);
      driver_speed.SetValue(10);
      driver_speed.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/driver_01.png").c_str());
    } break;
    case 31: {
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      driver_speed.SetMode(gva::widget::DialType::kDialSpeedKph);
      driver_speed.SetVisible(true);
      driver_speed.SetValue(40);
      driver_speed.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/driver_02.png").c_str());
    } break;
    case 32: {
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      driver_speed.SetMode(gva::widget::DialType::kDialSpeedMph);
      driver_speed.SetVisible(true);
      driver_speed.SetValue(100);
      driver_speed.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/driver_03.png").c_str());
    } break;
    case 33: {
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      driver_rpm.SetVisible(true);
      driver_rpm.SetValue(0);
      driver_rpm.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/rpm_01.png").c_str());
    } break;
    case 34: {
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      driver_rpm.SetVisible(true);
      driver_rpm.SetValue(4000);
      driver_rpm.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/rpm_02.png").c_str());
    } break;
    case 35: {
      LOG(INFO) << "Item  " << counter << ", Object localisation";
      std::array<gva::WidgetObjectLocalisation::BoxType, 8> box;
      box[0] = {310, 190, 240, 104, 0xff0000, "Person, threat", false, false};
      box[1] = {20, 100, 100, 40, 0x00ff00, "Person", false, false};
      box[2] = {76, 120, 105, 50, 0xffa500, "Person, Gun", false, true};
      box[3] = {180, 200, 180, 80, 0xff0000, "Person, Threat", false, false};
      box[4] = {400, 120, 90, 36, 0xffa500, "", false, false};
      box[5] = {500, 125, 50, 20, 0xfff00, "Person", false, true};
      box[6] = {550, 149, 100, 42, 0xfff00, "Person", false, false};
      box[7] = {630, 115, 100, 36, 0xfff00, "Person", false, false};
      objects.SetVisible(true);

      // Loop through box and set unique ids
      for (int16_t c = 0; c < 8; c++) {
        objects.AddBoundingBox(c + 1, box[c]);
      }

      objects.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), (path + "/objects_people_01.png").c_str());
    } break;
    default:
      counter = 9999;  // Cause loop to end and terminate
      break;
  }

  cairo_restore(cr);
  counter++;
}

///
/// \brief Construct a new gtk destory callback object
///
/// \param widget
/// \param data
///
int gtk_destory_callback(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
  return 0;
}

///
/// \brief The main entry point for the widget tester application
///
/// \param argc
/// \param argv
/// \return int
///
int main(int argc, char *argv[]) {
  int index;
  int id = 0;
  int timeout = 1000;

  GtkWidget *window;
  GtkWidget *darea;

  opterr = 0;

  google::SetVersionString(std::to_string(gva::kSemVerMajor) + "." + std::to_string(gva::kSemVerMinor) + "." +
                           std::to_string(gva::kSemVerPatch));
  google::SetUsageMessage(
      "The HMI widget tester application. This application will render all widgets to a PNG file in the specified "
      "directory.");
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  if (!google::IsGoogleLoggingInitialized()) {
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    LOG(INFO) << "Initialised Google logging";
  }

  path = FLAGS_path;
  id = FLAGS_id;
  timeout = FLAGS_timeout;

  for (index = optind; index < argc; index++) printf("Non-option argument %s\n", argv[index]);

  LOG(INFO) << "Path set to " << path;
  LOG(INFO) << "Timeout set to " << timeout;
  LOG(INFO) << "Identity set to " << id;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  tran_setup(window);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);

  if (id > 0) {
    // Just do a single widget no need for timer
    counter = id;
  } else {
    g_timeout_add(timeout, (GSourceFunc)time_handler, (gpointer)window);
  }

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_destory_callback), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), kScreenWidth, kScreenHeight);
  gtk_window_set_title(GTK_WINDOW(window), "Widget testing");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}