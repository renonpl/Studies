#include<gtk/gtk.h>
#include<stdio.h>
#include<complex.h>
#include<math.h>
#include<stdlib.h>

typedef struct Dt
{
	GdkPixbuf* pixel;
	GtkWidget* img;
	GtkWidget* grid;
	GtkWidget* window;
	GtkWidget* hbox;
	GtkWidget* vbox;
}Data;

typedef struct rec
{
	float leftx;
	float lefty;
	float rightx;
	float righty;
}rectangle;

void put_pixel (GdkPixbuf *pixbuf, int x, int y, int colour);

float mand(complex float a);

rectangle position(GtkGrid* data);

void draw(GtkWidget *widget, gpointer data);

void destroy(GtkWidget *widget, gpointer data);

void save_file(GtkWidget *widget, gpointer data);
