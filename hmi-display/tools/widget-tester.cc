#include <cairo.h>
#include <ctype.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ctime>

#include "src/gva.h"
#include "src/renderer_gva.h"
#include "src/widgets/alarm_indicator.h"
#include "src/widgets/bottom_labels.h"
#include "src/widgets/compass.h"
#include "src/widgets/keyboard.h"
#include "src/widgets/mode.h"
#include "src/widgets/side_labels.h"
#include "src/widgets/table.h"
#include "src/widgets/top_labels.h"
#include "src/widgets/widget_types.h"

#define HEIGHT 480
#define WIDTH 640

struct {
  gushort count;
} glob;

static gva::RendererGva renderer(WIDTH, HEIGHT);
static gva::TouchGva touch;  // Dummy to get the interactive widgets to render
static gva::WidgetFunctionKeyToggle key(renderer);
static gva::WidgetPlanPositionIndicator ppi(renderer);
static gva::WidgetKeyboard keyboard(renderer);
static gva::WidgetAlarmIndicator alarmx(renderer);
static gva::WidgetTopLabels top(renderer, &touch);
static gva::WidgetBottomLabels bottom(renderer, &touch);
static gva::WidgetSideLabels left(renderer, &touch);
static gva::WidgetSideLabels right(renderer, &touch);
static gva::WidgetMode mode(renderer);
static gva::WidgetTable table(renderer, &touch);

static void do_drawing(cairo_t *, int width, int h);

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

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  int width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  do_drawing(cr, width, height);

  if (counter >= 9999) exit(0);

  return FALSE;
}

static gboolean time_handler(GtkWidget *widget) {
  glob.count += 1;
  gtk_widget_queue_draw(widget);

  return TRUE;
}

static void do_drawing(cairo_t *cr, int width, int height) {
  renderer.render_.cr = cr;
  cairo_save(cr);

  renderer.Init(width, height);

  switch (counter) {
    case 0:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 0, 90, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_01.png");
      break;
    case 1:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 350, 180, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_02.png");
      break;
    case 2:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 340, 270, 30);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_03.png");
      break;
    case 3:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithSight, 0, 0, 330, 0, 40);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_04.png");
      break;
    case 4:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicTankWithoutSight, 0, 0, 320, 90, 0);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_05.png");
      break;
    case 5:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 0, 90, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_06.png");
      break;
    case 6:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 350, 180, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_07.png");
      break;
    case 7:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 340, 270, 30);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_08.png");
      break;
    case 8:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithSight, 0, 0, 330, 0, 40);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_09.png");
      break;
    case 9:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiClassicArrowWithoutSight, 0, 0, 320, 90, 0);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_10.png");
      break;
    case 10:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 0, 90, 10);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_11.png");
      break;
    case 11:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 350, 180, 20);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_12.png");
      break;
    case 12:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 340, 270, 30);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_13.png");
      break;
    case 13:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithSights, 0, 0, 330, 0, 40);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_14.png");
      break;
    case 14:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      ppi.DrawPPI(gva::widget::ModeEnum::kPpiModernTankWithoutSights, 0, 0, 320, 90, 0);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_15.png");
      break;
    case 15:
      // Keyboard, Lower case
      cairo_translate(cr, 0, height / 2);
      keyboard.DrawKeyboard(gva::widget::KeyboardModeType::kKeyboardLower);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_keyboard_01.png");
      break;
    case 16:
      // Keyboard, Upper case
      cairo_translate(cr, 0, height / 2);
      keyboard.DrawKeyboard(gva::widget::KeyboardModeType::kKeyboardUpper);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_keyboard_02.png");
      break;
    case 17:
      // Keyboard, numbers
      cairo_translate(cr, 0, height / 2);
      keyboard.DrawKeyboard(gva::widget::KeyboardModeType::kKeyboardNumbers);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_keyboard_03.png");
      break;
    case 18:
      // Alarms Indicator
      cairo_translate(cr, 0, height / 2);
      alarmx.SetText("Software tester status advisory example message");
      alarmx.SetType(gva::GvaAlarmType::kAlarmAdvisory);
      alarmx.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "alarm_02.png");
      break;
    case 19:
      // Alarms Indicator
      cairo_translate(cr, 0, height / 2);
      alarmx.SetText("Software tester status warning example message");
      alarmx.SetType(gva::GvaAlarmType::kAlarmWarnings);
      alarmx.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "alarm_03.png");
      break;
    case 20:
      // Alarms Indicator
      cairo_translate(cr, 0, height / 2);
      alarmx.SetText("Software tester status caution example message");
      alarmx.SetType(gva::GvaAlarmType::kAlarmCaution);
      alarmx.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "alarm_01.png");
      break;
    case 21:
      // Top
      cairo_translate(cr, 0, height / 2);
      {
        std::array<gva::FunctionSelect::Labels, 8> labels = {
            gva::LabelStates::kLabelEnabledSelected, gva::LabelStates::kLabelEnabled, gva::LabelStates::kLabelEnabled,
            gva::LabelStates::kLabelEnabled,         gva::LabelStates::kLabelEnabled, gva::LabelStates::kLabelDisabled,
            gva::LabelStates::kLabelEnabled,         gva::LabelStates::kLabelEnabled};
        top.SetLabels(&labels);
        top.Draw();
        renderer.Draw();
        cairo_surface_write_to_png(cairo_get_group_target(cr), "top_labels_01.png");
      }
      break;
    case 22:
      // Botton
      cairo_translate(cr, 0, height / 2);
      {
        std::array<gva::CommonTaskKeys::Labels, 8> labels = {
            gva::LabelStates::kLabelEnabledSelected, "Up",      gva::LabelStates::kLabelEnabled,  "Alarms",
            gva::LabelStates::kLabelDisabled,        "Threats", gva::LabelStates::kLabelDisabled, "Ack.",
            gva::LabelStates::kLabelEnabled,         "",        gva::LabelStates::kLabelEnabled,  "",
            gva::LabelStates::kLabelEnabled,         "Labels",  gva::LabelStates::kLabelEnabled,  "Enter"};
        bottom.SetLabels(&labels);
        bottom.Draw();
        renderer.Draw();
        cairo_surface_write_to_png(cairo_get_group_target(cr), "bottom_labels_01.png");
      }
      break;
    case 23:
      // Left
      cairo_translate(cr, 0, height / 2);
      {
        std::array<gva::FunctionKeys::Labels, 6> labels = {gva::LabelStates::kLabelEnabledSelected,
                                                           true,
                                                           false,
                                                           "ECM",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelEnabledSelectedChanging,
                                                           true,
                                                           true,
                                                           "Spike",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelDisabled,
                                                           false,
                                                           false,
                                                           "HUMS",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelEnabled,
                                                           false,
                                                           false,
                                                           "Status",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelHidden,
                                                           false,
                                                           false,
                                                           "Maint",
                                                           "",
                                                           "",
                                                           gva::LabelStates::kLabelEnabled,
                                                           false,
                                                           false,
                                                           "Status",
                                                           "",
                                                           ""

        };
        left.SetLabels(&labels);
        left.Draw();
        renderer.Draw();
        cairo_surface_write_to_png(cairo_get_group_target(cr), "side_labels_01.png");
      }
      break;
    case 24:
      // Mode Indicator
      cairo_translate(cr, 0, height / 2);
      mode.SetMode("Software Testing Mode");
      mode.Draw();
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "mode_01.png");
      break;
    default:
      counter = 9999;  // Cause loop to end and terminate
      break;
  }

  cairo_restore(cr);
  counter++;
}

int main(int argc, char *argv[]) {
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;
  int index;
  int c;
  int id = 0;
  int timeout = 1000;

  GtkWidget *window;
  GtkWidget *darea;

  opterr = 0;

  while ((c = getopt(argc, argv, "i:ht:")) != -1) switch (c) {
      case 'i':
        id = atoi(optarg);
        break;
      case 'h':
        std::cout << "Help for test-hmi:" << std::endl;
        std::cout
            << "    -t <milliseconds>    timeout in milliseconds between widget renders, 1 second if not specified."
            << std::endl;
        std::cout << "    -i <number>          The id of the single widget to render from list below (timeout does not "
                     "apply here):"
                  << std::endl;
        std::cout << "       0: PPI classic tank site, north facing site " << std::endl;
        std::cout << "       1: PPI classic tank site, east facing site " << std::endl;
        std::cout << "       2: PPI classic tank site, south facing site " << std::endl;
        std::cout << "       3: PPI classic tank site, west facing site " << std::endl;
        std::cout << "       4: PPI classic tank site with no site " << std::endl;
        std::cout << "       5: PPI classic arrow site, north facing site " << std::endl;
        std::cout << "       6: PPI classic arrow site, east facing site " << std::endl;
        std::cout << "       7: PPI classic arrow site, south facing site " << std::endl;
        std::cout << "       8: PPI classic arrow site, west facing site " << std::endl;
        std::cout << "       9: PPI classic arrow site with no site " << std::endl;
        std::cout << "       10: PPI modern site, north facing site " << std::endl;
        std::cout << "       11: PPI modern site, east facing site " << std::endl;
        std::cout << "       12: PPI modern site, south facing site " << std::endl;
        std::cout << "       13: PPI modern site, west facing site " << std::endl;
        std::cout << "       14: PPI modern site with no site " << std::endl;
        std::cout << "       15: Keyboard, lower case " << std::endl;
        std::cout << "       16: Keyboard, upper case " << std::endl;
        std::cout << "       17: Keyboard, numbers " << std::endl;
        std::cout << "       18: Alarms indicator, advisory " << std::endl;
        std::cout << "       19: Alarms indicator, warning " << std::endl;
        std::cout << "       20: Alarms indicator, caution " << std::endl;
        std::cout << "       21: Labels for top of screen, functional areas" << std::endl;
        std::cout << "       22: Labels for bottom of screen, control " << std::endl;
        std::cout << "       23: Labels for side of screen, used for both left and right hand sides " << std::endl;
        std::cout << "       24: Operator mode, visual indication of the non operational mode/s" << std::endl;
        return 0;
      case 't':
        timeout = atoi(optarg);
        break;
      case '?':
        if (optopt == 'c')
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
        return 1;
      default:
        abort();
    }

  printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

  for (index = optind; index < argc; index++) printf("Non-option argument %s\n", argv[index]);

  std::cout << "Widget tester, created PNG files for all widgets" << std::endl;
  std::cout << "   Timeout set to " << timeout << std::endl;
  std::cout << "   Identity set to " << id << std::endl;

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

  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WIDTH, HEIGHT);
  gtk_window_set_title(GTK_WINDOW(window), "Widget testing");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}