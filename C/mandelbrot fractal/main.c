#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include"board.h"
#include"app.h"


static void set_game(GameData* data)
{
    data->hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
    gtk_container_add((GtkContainer*)data->window,data->hbox);
    data->table = gtk_grid_new();
    gtk_box_pack_start((GtkBox*)data->hbox,data->table,TRUE,TRUE,0);
    data->active_player = 0;
    data->move_board = 1;
    for(unsigned i = 0; i < 9; i++)
    {
        for(unsigned j = 0; j < 9; j++)
        {
            GtkWidget* img = data->board->tab[i][j].image;
            gtk_grid_attach((GtkGrid*)data->table, img, j+1,i+1,1,1);
        }
    }
    for(unsigned i = 3; i < 9; i+=2)
    {
        GtkWidget* button;
        GtkWidget* buttonik;
        buttonik = gtk_button_new_with_label("Klik");
        button = gtk_button_new_with_label("Klik");
        gtk_grid_attach((GtkGrid*)data->table,button,i,0,1,1);
        gtk_grid_attach((GtkGrid*)data->table,buttonik,i,10,1,1);
        Button_data* temp = (Button_data*)malloc(sizeof(Button_data)); //wyciek
        temp->data = data;
        temp->y = 0;
        temp->x = i;
        temp->button = button;
        g_signal_connect(button,"clicked",G_CALLBACK(board_mover),temp);
        Button_data* temp2 = (Button_data*)malloc(sizeof(Button_data)); //i ten
        temp2->data = data;
        temp2->y = 8;
        temp2->x = i;
        temp2->button = button;
        g_signal_connect(buttonik,"clicked",G_CALLBACK(board_mover),temp2);
    }
    for(unsigned i = 3; i < 9; i+=2)
    {
        GtkWidget* button;
        GtkWidget* buttonik;
        buttonik = gtk_button_new_with_label("Klik");
        button = gtk_button_new_with_label("Klik");
        gtk_grid_attach((GtkGrid*)data->table,button,0,i,1,1);
        gtk_grid_attach((GtkGrid*)data->table,buttonik,10,i,1,1);
        Button_data* temp = (Button_data*)malloc(sizeof(Button_data)); //te reczy
        temp->data = data;
        temp->y = i;
        temp->x = 0;
        temp->button = button;
        g_signal_connect(button,"clicked",G_CALLBACK(board_mover),temp);
        Button_data* temp2 = (Button_data*)malloc(sizeof(Button_data)); // i te
        temp2->data = data;
        temp2->y = i;
        temp2->x = 8;
        temp2->button = button;
        g_signal_connect(buttonik,"clicked",G_CALLBACK(board_mover),temp2);
    }
    data->player_list = (Player*)malloc(4*sizeof(Player)); // o i to
    unsigned tab[24] = {0};
    for(unsigned i = 0; i < 4; i++)
    {
        Player temp;
        for(unsigned j = 0; j < 6;j++)
        {
            unsigned item = rand()%24;
            while(tab[item] != 0) item = rand()%24;
            temp.tab[j] = item+1;
            tab[item] = 1;
        }
        temp.searching_index = 0;
        if(i == 0)
        {
            temp.x = 1;
            temp.y = 1;
            temp.rgb.red = 255;
            temp.rgb.green = 0;
            temp.rgb.blue = 0;
        }
        if(i == 1)
        {
            temp.x = 7;
            temp.y = 1;
            temp.rgb.red = 255;
            temp.rgb.green = 255;
            temp.rgb.blue = 0;
        }
        if(i == 2)
        {
            temp.x = 1;
            temp.y = 7;
            temp.rgb.red = 0;
            temp.rgb.green = 255;
            temp.rgb.blue = 0;
        }
        if(i == 3)
        {
            temp.x = 7;
            temp.y = 7;
            temp.rgb.red = 0;
            temp.rgb.green = 0;
            temp.rgb.blue = 255;
        }
        temp.number = i;
        data->player_list[i] = temp;
    }
    draw_players(data->player_list,data->board);
    data->player_controll = set_player_contoller(data);
    data->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,1);
    gtk_box_pack_start((GtkBox*)data->hbox,data->vbox,TRUE,TRUE,0);
    PlayerController* plc = data->player_controll;
    gtk_box_pack_start((GtkBox*)data->vbox,plc->grid,TRUE,TRUE,0);
    cordinates* empty_field = (cordinates*)malloc(sizeof(cordinates));
    empty_field->x = 0;
    empty_field->y = 0;
    data->free_field = empty_field;
    return;
}


static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget* window;
    window = gtk_application_window_new(app);
    gtk_window_set_title((GtkWindow*)window, "LABIRYNT GRA");
    gtk_window_set_default_size((GtkWindow*)window, 1200, 800);

    GameData* data;
    data = (GameData*)malloc(sizeof(GameData));  // to mi wycieka
    data->window = window;

    board* plansza = board_init(); // to mi wycieka
    board_start(plansza);
    data->board = plansza;

    set_game(data);
    gtk_widget_show_all(window);
}


int main(int argc, char** argv)
{

    GtkApplication *app;
    int status;

    app = gtk_application_new("labirynth.gtk", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app),argc,argv);
    g_object_unref(app);

    return status;
}
