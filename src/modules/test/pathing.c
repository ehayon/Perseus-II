#include "../lib/pathing.h"
#include <stdlib.h>
#include <math.h>

#define CELL_WIDTH 15

typedef struct s_graph_node {
	gdouble x;
	gdouble y;
} t_graph_node;

t_graph_node **nodes;
unsigned int node_pos;
unsigned int node_count;

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
    g_print("Close window\n");
    return FALSE;
}

static void destroy_event(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void draw_grid(GtkWidget *widget, cairo_t *cr, gint width, gint height) {
	g_print("Running draw_grid\n");
	unsigned int i;

	printf("Width = %d, Height = %d\n", width, height);
	cairo_set_line_width(cr, 0.5);
	cairo_set_source_rgb(cr, 0,0,255);
	for(i=CELL_WIDTH; i < width; i+=CELL_WIDTH) {
		cairo_move_to(cr, i, 0);
		cairo_line_to(cr, i, height); 
	}
	for(i=CELL_WIDTH; i < height; i+=CELL_WIDTH) {
		cairo_move_to(cr, 0, i);
		cairo_line_to(cr, width, i); 
	}
	cairo_stroke(cr);
}

static gboolean redraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    GdkColor color;
	GtkRequisition *size = (GtkRequisition*)malloc(sizeof(GtkRequisition));
	unsigned int i;
	size->height = 0;
	size->width = 0;
	
	gtk_widget_size_request(widget, size);
    gtk_widget_add_events(widget, GDK_BUTTON_PRESS_MASK);
	
	cr = gdk_cairo_create(gtk_widget_get_window(widget));
	
	draw_grid(widget, cr, size->width, size->height);


	cairo_set_line_width(cr, 2);
	cairo_set_source_rgb(cr, 255,0,0);
	// draw the graph nodes
	for(i=0; i<node_count; i++) {
		cairo_arc(cr, nodes[i]->x, nodes[i]->y, 3.0, 0, 2*M_PI);		
		cairo_fill(cr);
	}
    return TRUE;
}

static gboolean da_click(GtkWidget *widget, GdkEvent *event, gpointer data) {
    gdouble x;
    gdouble y;
    GtkRequisition *size = (GtkRequisition*)malloc(sizeof(GtkRequisition));
	size->width = 0;
	size->height = 0;
	gtk_widget_size_request(widget, size);
	gdk_event_get_coords(event, &x, &y);
	
	// find the closest node to snap to
	gdouble x_int, y_int;
	x_int = round(x/CELL_WIDTH);
	y_int = round(y/CELL_WIDTH);
	x_int *= CELL_WIDTH;
	y_int *= CELL_WIDTH;

	// draw a small circle at x_int, y_int
	t_graph_node *node = (t_graph_node*)malloc(sizeof(t_graph_node));
	node->x = x_int;
	node->y = y_int;
	nodes[node_pos++] = node;	
	node_count++;
	gtk_widget_queue_draw(widget);
    printf("X: %f, Y: %f\n", x_int, y_int);



    return TRUE;
}

int main(int argc, char **argv) {
    GtkWidget *window;
    GtkWidget *drawing_area;
	GtkWidget *fixed;

    gtk_init(&argc, &argv);
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    drawing_area = gtk_drawing_area_new();

	nodes = (t_graph_node**)malloc(54*sizeof(t_graph_node*));
	node_pos = 0;
	node_count = 0;

    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy_event), NULL);

    gtk_widget_set_size_request (drawing_area, 600, 600);
    g_signal_connect(G_OBJECT(drawing_area), "expose-event", G_CALLBACK(redraw), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "button-press-event", G_CALLBACK(da_click), NULL);

    gtk_window_set_title(GTK_WINDOW(window), "AUV Pathing");
    gtk_window_set_default_size(GTK_WINDOW(window), 800,600);

	fixed = gtk_fixed_new();
	gtk_fixed_put(GTK_FIXED(fixed), drawing_area, 200, 0);


	// generate path button



    gtk_container_add(GTK_CONTAINER(window), fixed);
	gtk_widget_show(fixed);
    gtk_widget_show(drawing_area);
    gtk_widget_show(window);

    gtk_main();
    return 0;
}
