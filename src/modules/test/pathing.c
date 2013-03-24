#include "../lib/pathing.h"

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    g_print("Close window\n");
    return FALSE;
}

static void destroy_event(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char **argv) {
    GtkWidget *window;
    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy_event), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "AUV Pathing");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600);

    gtk_widget_show(window);

    gtk_main();
    return 0;
}
