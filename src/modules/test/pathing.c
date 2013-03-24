#include "../lib/pathing.h"

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    g_print("Close window\n");
    return FALSE;
}

static void destroy_event(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

static gboolean redraw(GtkWidget *widget, cairo_t *ct, gpointer data) {
    guint width;
    guint height;
    GdkColor color;

    gtk_widget_add_events(widget, GDK_BUTTON_PRESS_MASK);
    gdk_draw_arc (widget->window, widget->style->fg_gc[gtk_widget_get_state (widget)], TRUE, 0, 0, widget->allocation.width, widget->allocation.height,0, 64 * 360);
    return TRUE;
}

static gboolean da_click(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gdouble x;
    gdouble y;

    gdk_event_get_coords(event, &x, &y);
    printf("X: %f, Y: %f\n", x, y);
    return TRUE;
}

int main(int argc, char **argv) {
    GtkWidget *window;
    GtkWidget *drawing_area;

    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    drawing_area = gtk_drawing_area_new();

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy_event), NULL);

    gtk_widget_set_size_request (drawing_area, 100, 100);
    g_signal_connect(G_OBJECT(drawing_area), "expose-event", G_CALLBACK(redraw), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "button-press-event", G_CALLBACK(da_click), NULL);

    gtk_window_set_title(GTK_WINDOW(window), "AUV Pathing");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show(drawing_area);
    gtk_widget_show(window);

    gtk_main();
    return 0;
}
