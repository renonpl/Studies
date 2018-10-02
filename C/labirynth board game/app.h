#pragma once
#include<stdio.h>
#include"board.h"

typedef struct
{
    unsigned x;
    unsigned y;
}cordinates;

typedef struct
{
    GtkWidget* grid;
    GtkWidget* accept;
    GtkWidget* player_turn;
    GtkWidget* action_name;
}PlayerController;

typedef struct
{
    GtkWidget* window;
    GtkWidget* table;
    board* board;
    GtkWidget *hbox;
    GtkWidget* vbox;
    Player* player_list;
    PlayerController* player_controll;
    cordinates* free_field;
    unsigned active_player;
    unsigned move_board;
}GameData;

typedef struct
{
    GtkWidget* button;
    unsigned x;
    unsigned y;
    GameData* data;
}Button_data;

typedef struct
{
    unsigned player_number;
    unsigned direction;
    GameData* data;
}PlayerMover;

void move_player(PlayerMover* enter);

void move_column(GameData* data, unsigned x, unsigned direction);

void move_row(GameData* data, unsigned y, unsigned direction);

void  board_mover(GtkWidget* widget, gpointer data);

PlayerController* set_player_contoller(GameData* data);

void accept_function(GtkWidget* widget, gpointer data);
