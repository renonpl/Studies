#include"app.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void move_player(PlayerMover* enter)
{
    Player* player = &enter->data->player_list[enter->player_number];
    board* board = enter->data->board;
    if(enter->direction == 1)
    {
        if(player->x == 7) return;
        if(board->tab[player->y][player->x].real_walls & 1 || board->tab[player->y][player->x+1].real_walls & 4) return;
        (player->x)++;
        board_draw(board);
        draw_players(enter->data->player_list,board);
        return;
    }
    if(enter->direction == 2)
    {
        if(player->y == 7) return;
        if(board->tab[player->y][player->x].real_walls & 2 || board->tab[player->y+1][player->x].real_walls & 8) return;
        (player->y)++;
        board_draw(board);
        draw_players(enter->data->player_list,board);
        return;
    }
    if(enter->direction == 4)
    {
        if(player->x == 1) return;
        if(board->tab[player->y][player->x].real_walls & 4 || board->tab[player->y][player->x-1].real_walls & 1) return;
        (player->x)--;
        board_draw(board);
        draw_players(enter->data->player_list,board);
        return;
    }
    if(enter->direction == 8)
    {
        if(player->y == 1) return;
        if(board->tab[player->y][player->x].real_walls & 8 || board->tab[player->y-1][player->x].real_walls & 2) return;

            (player->y)--;
                board_draw(board);
                draw_players(enter->data->player_list,board);

        return;
    }
}

static void player_mover(GtkWidget* widget, gpointer data)
{
    PlayerMover* temp = (PlayerMover*)data;
    if(temp->data->move_board == 1) return;
    temp->player_number = temp->data->active_player;
    move_player(temp);
}


void move_column(GameData* data, unsigned x, unsigned direction)
{
    board* place = data->board;
    Player* player_list = data->player_list;
    unsigned free_y = data->free_field->y;
    unsigned free_x = data->free_field->x;
    field free_field = place->tab[free_y][free_x];
    field blank = place->tab[0][1];
    field_copy(&place->tab[free_y][free_x], blank);
    draw_image(&place->tab[free_y][free_x]);

    if(direction)
    {
        field temp = place->tab[0][x];
        for(unsigned i = 1; i < 9; i++)
        {
            field save = place->tab[i][x];
            field_copy(&place->tab[i][x], temp);
            temp = save;
        }
        field_copy(&place->tab[0][x], temp);
        field_copy(&place->tab[1][x], free_field);

    }
    else
    {
        field temp = place->tab[8][x];
        for(int i = 7; i >= 0; i--)
        {
            field save = place->tab[i][x];
            field_copy(&place->tab[i][x], temp);
            temp = save;
        }
        field_copy(&place->tab[8][x], temp);
        field_copy(&place->tab[7][x], free_field);

    }
    for(unsigned i = 0; i < 4; i++)
    {
        if(player_list[i].x == x)
        {
            player_list[i].y--;
            if(player_list[i].y == direction*8) player_list[i].y = 7-6*direction;
        }
    }
    data->free_field->y = 8*direction;
    data->free_field->x = x;
    for(unsigned i = 0; i < 9; i++) draw_image(&place->tab[i][x]);
    draw_players(player_list,place);
    return;
}


void move_row(GameData* data, unsigned y, unsigned direction)
{
    board* place = data->board;
    Player* player_list = data->player_list;
    unsigned free_y = data->free_field->y;
    unsigned free_x = data->free_field->x;
    field free_field = place->tab[free_y][free_x];
    field blank = place->tab[0][1];
    field_copy(&place->tab[free_y][free_x], blank);
    draw_image(&place->tab[free_y][free_x]);

    if(direction)
    {
        field temp = place->tab[y][0];
        for(unsigned i = 1; i < 9; i++)
        {
            field save = place->tab[y][i];
            field_copy(&place->tab[y][i], temp);
            temp = save;
        }
        field_copy(&place->tab[y][0], temp);
        field_copy(&place->tab[y][1], free_field);

    }
    else
    {
        field temp = place->tab[y][8];
        for(int i = 7; i >= 0; i--)
        {
            field save = place->tab[y][i];
            field_copy(&place->tab[y][i], temp);
            temp = save;
        }
        field_copy(&place->tab[y][8], temp);
        field_copy(&place->tab[y][7], free_field);

    }
    for(unsigned i = 0; i < 4; i++)
    {
        if(player_list[i].y == y)
        {
            player_list[i].x--;
            if(player_list[i].x == direction*8) player_list[i].x = 7-direction*6;
        }
    }
    data->free_field->y = y;
    data->free_field->x = 8*direction;
    for(unsigned i = 0; i < 9; i++) draw_image(&place->tab[y][i]);
    draw_players(player_list,place);
    return;
}


void  board_mover(GtkWidget* widget, gpointer data)
{
    Button_data* enter = (Button_data*)data;
    if(enter->data->move_board == 0) return;
    if(enter->y == 0)
    {
        if(enter->data->free_field->x == enter->x-1 && enter->data->free_field->y == 0) return;
        move_column(enter->data,(enter->x)-1,1);
    }
    if(enter->y == 8)
    {

        if(enter->data->free_field->x == enter->x-1 && enter->data->free_field->y == 8) return;
        move_column(enter->data,(enter->x)-1,0);
    }
    if(enter->x == 0)
    {

        if(enter->data->free_field->y == enter->y-1 && enter->data->free_field->x == 0) return;
        move_row(enter->data,(enter->y)-1,1);

    }
    if(enter->x == 8)
     {
        if(enter->data->free_field->y == enter->y-1 && enter->data->free_field->x == 8) return;
        move_row(enter->data,(enter->y)-1,0);
    }
    enter->data->move_board = 0;
    gtk_label_set_text((GtkLabel*)enter->data->player_controll->action_name,"Przesun pionek");
    return;
}


PlayerController* set_player_contoller(GameData* data)
{
    PlayerController* exit = (PlayerController*)malloc(sizeof(PlayerController));
    exit->grid = gtk_grid_new();
    exit->action_name = gtk_label_new("Przesun kolumne/wiersz");
    gtk_grid_attach((GtkGrid*)exit->grid,exit->action_name,0,1,3,1);
    exit->player_turn = gtk_label_new("Tura gracza czerwonego");
    gtk_grid_attach((GtkGrid*)exit->grid,exit->player_turn,0,0,3,1);
    exit->accept = gtk_button_new_with_label("Accept");


    gtk_grid_attach((GtkGrid*)exit->grid,exit->accept,1,4,1,1);
    g_signal_connect(exit->accept,"clicked",G_CALLBACK(accept_function),data);

    GtkWidget* button;
    button = gtk_button_new_with_label("Up");
    gtk_grid_attach((GtkGrid*)exit->grid,button,1,3,1,1);

    PlayerMover* temp = (PlayerMover*)malloc(sizeof(PlayerMover)); //to wycieka
    temp->data = data;
    temp->direction = 8;
    g_signal_connect(button,"clicked",G_CALLBACK(player_mover),temp);


    GtkWidget* button2;
    button2 = gtk_button_new_with_label("Down");
    gtk_grid_attach((GtkGrid*)exit->grid,button2,1,5,1,1);

    PlayerMover* temp2 = (PlayerMover*)malloc(sizeof(PlayerMover)); //to
    temp2->data = data;
    temp2->direction = 2;
    g_signal_connect(button2,"clicked",G_CALLBACK(player_mover),temp2);


    GtkWidget* button3;
    button3 = gtk_button_new_with_label("Left");
    gtk_grid_attach((GtkGrid*)exit->grid,button3,0,4,1,1);

    PlayerMover* temp3 = (PlayerMover*)malloc(sizeof(PlayerMover)); //to
    temp3->data = data;
    temp3->direction = 4;
    g_signal_connect(button3,"clicked",G_CALLBACK(player_mover),temp3);


    GtkWidget* button4;
    button4 = gtk_button_new_with_label("Right");
    gtk_grid_attach((GtkGrid*)exit->grid,button4,2,4,1,1);

    PlayerMover* temp4 = (PlayerMover*)malloc(sizeof(PlayerMover)); //to
    temp4->data = data;
    temp4->direction = 1;
    g_signal_connect(button4,"clicked",G_CALLBACK(player_mover),temp4);

    return exit;
}

void accept_function(GtkWidget* widget, gpointer data)
{
    GameData* enter = (GameData*)data;
    if(enter->move_board == 1) return;

    Player* temp = &enter->player_list[enter->active_player];
    if(temp->tab[temp->searching_index] == enter->board->tab[temp->y][temp->x].item)
    {
        temp->searching_index++;
        if(temp->searching_index == 6)
        {
            printf("ZWYCIESTO GRACZA NUMER %d", temp->number+1);
            assert(temp->searching_index < 6);
            temp->searching_index = 0;
            temp->tab[0] = 100;
        }
        enter->board->tab[temp->y][temp->x].item = 0;
        board_draw(enter->board);
        draw_players(enter->player_list,enter->board);
    }
    enter->active_player++;
    if(enter->active_player == 4) enter->active_player = 0;
    switch(enter->active_player)
    {
        case 0:
            gtk_label_set_text((GtkLabel*)enter->player_controll->player_turn, "Tura gracza czerwonego");
            break;
        case 1:
            gtk_label_set_text((GtkLabel*)enter->player_controll->player_turn, "Tura gracza zoltego");
            break;
        case 2:
            gtk_label_set_text((GtkLabel*)enter->player_controll->player_turn, "Tura gracza zielonego");
            break;
        case 3:
            gtk_label_set_text((GtkLabel*)enter->player_controll->player_turn, "Tura gracza niebieskiego");
            break;
    }
    gtk_label_set_text((GtkLabel*)enter->player_controll->action_name,"Przesun kolumne/wiersz");

    enter->move_board = 1;
    return;
}
