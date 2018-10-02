#include<gtk/gtk.h>
#include<stdio.h>
#include<complex.h>
#include<math.h>
#include<stdlib.h>
#include "mandel.h"

void put_pixel (GdkPixbuf *pixbuf, int x, int y, int colour)
{
	int rowstride;
	int n_channels;
	guchar *pixels;
	guchar *p;

	n_channels = gdk_pixbuf_get_n_channels(pixbuf);
	rowstride = gdk_pixbuf_get_rowstride(pixbuf);
	pixels = gdk_pixbuf_get_pixels(pixbuf);

	p = pixels + y*rowstride + x*n_channels;
	p[0] = 0;
	p[1] = 0;
	p[2] = 255 - colour;
}

float mand(complex float a)
{
	complex temp = 0.0 + 0.0fi;
	for(unsigned i = 0; i < 256; i++)
	{
		temp = temp*temp + a;
		float exit = sqrt(cimag(temp)*cimag(temp)+creal(temp)*creal(temp));
		if(exit > 2.0) return i;
	}
	return 255;
}

rectangle position(GtkGrid* data)
{
	rectangle exit;
	GtkEntry* temp;

	temp = (GtkEntry*)gtk_grid_get_child_at(data,1,0);
	exit.leftx = atof(gtk_entry_get_text(temp));
	temp = (GtkEntry*)gtk_grid_get_child_at(data,1,1);
	exit.lefty = atof(gtk_entry_get_text(temp));
	temp = (GtkEntry*)gtk_grid_get_child_at(data,1,2);
	exit.rightx = atof(gtk_entry_get_text(temp));
	temp = (GtkEntry*)gtk_grid_get_child_at(data,1,3);
	exit.righty = atof(gtk_entry_get_text(temp));
	return exit;
}

void draw(GtkWidget *widget, gpointer data)
{
	Data* temp = (Data*)data;
	rectangle space = position((GtkGrid*)temp->grid);

	int height = gdk_pixbuf_get_height(temp->pixel);
	int width = gdk_pixbuf_get_width(temp->pixel);

	const float eps_x = (space.rightx - space.leftx)/width;
	const float eps_y = (space.lefty - space.righty)/height;

	complex float start = 1.0*(space.leftx) + 1.0fi*(space.lefty);

	for(int i = 0; i < width; start += 1.0*eps_x, i++)
	{
		start = creal(start) + 1.0fi*(space.lefty);
		for(int j = 0; j < height; j++, start -= 1.0fi*eps_y)
		{
			put_pixel(temp->pixel,i,j,mand(start));
		}
	}
	gtk_image_set_from_pixbuf((GtkImage*)temp->img,temp->pixel);
}

void destroy(GtkWidget *widget, gpointer data)
{

	Data*temp = (Data*)data;
	gtk_widget_destroy(temp->grid);
	gtk_widget_destroy(temp->img);
	gtk_widget_destroy(temp->vbox);
	gtk_widget_destroy(temp->hbox);
	g_object_unref(temp->window);
	gtk_widget_destroy(temp->window);
    g_slice_free(Data,temp);
}

void save_file(GtkWidget *widget, gpointer data)
{
	Data* temp = data;
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action;
	action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new("Zapisz plik",(GtkWindow*)temp->window,action,("Anuluj"),GTK_RESPONSE_CANCEL, ("Zapisz"), GTK_RESPONSE_ACCEPT,NULL);

	chooser = GTK_FILE_CHOOSER(dialog);

	gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
	res = gtk_dialog_run(GTK_DIALOG(dialog));
	if(res == GTK_RESPONSE_ACCEPT)
	{
		char* filename;
		filename = gtk_file_chooser_get_filename(chooser);
		gdk_pixbuf_save(temp->pixel,filename,"png",NULL,NULL);
		g_free(filename);
	}
	gtk_widget_destroy(dialog);
}
