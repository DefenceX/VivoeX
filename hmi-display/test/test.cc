#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

#include <ctime>

#include "src/renderer_gva.h"

static gva::RendererGva renderer(300, 250);
static gva::FunctionKeyToggle key(renderer);
static gva::PlanPositionIndicator ppi(renderer);

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
static GtkWidget *window;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  int width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  do_drawing(cr, width, height);
  sleep(1);

  if (counter >= 9999) exit(0);

  gtk_widget_queue_draw(widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, int width, int height) {
  renderer.render_.cr = cr;
  uint8_t mode = 0;

  switch (counter) {
    case 0:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      renderer.Init(width, height);
      ppi.DrawPPI(mode, 0, 0, 0, 90);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_01.png");
      break;
    case 1:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      renderer.Init(width, height);
      ppi.DrawPPI(mode, 0, 0, 350, 180);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_02.png");
      break;
    case 2:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      renderer.Init(width, height);
      ppi.DrawPPI(mode, 0, 0, 340, 270);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_03.png");
      break;
    case 3:
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      renderer.Init(width, height);
      ppi.DrawPPI(mode, 0, 0, 330, 0);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "widget_ppi_04.png");
      break;
    case 4:
      // Next PPI
      cairo_translate(cr, width / 2, height / 2);
      cairo_scale(cr, 2, 2);
      renderer.Init(width, height);
      mode = 1;
      ppi.DrawPPI(mode, 0, 0, 320, 90);
      renderer.Draw();
      cairo_surface_write_to_png(cairo_get_group_target(cr), "test5.png");
      counter = 9999;
      break;
    default:
      break;
  }
  counter++;
}

int main(int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *darea;

  std::cout << "Widget tester, created PNG files for all widgets" << std::endl;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  tran_setup(window);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 250);
  gtk_window_set_title(GTK_WINDOW(window), "Widget testing");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}