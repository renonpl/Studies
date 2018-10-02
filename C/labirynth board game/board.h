#pragma once
#include<stdio.h>
#include<gtk/gtk.h>

typedef struct
{
    unsigned walls;
    unsigned real_walls;
    unsigned is_blank;
    unsigned item;
    unsigned rotation;
    GdkPixbuf* pixel;
    GtkWidget* image;
}field;

typedef struct
{
    unsigned size;
    field** tab;
}board;

typedef struct
{
    unsigned red;
    unsigned green;
    unsigned blue;
}colour;

typedef struct
{
    unsigned number;
    unsigned x;
    unsigned y;
    unsigned searching_index;
    unsigned tab[6];
    colour rgb;
}Player;

board* board_init(void);

void board_destroy(board* entry);

void board_start(board* entry);

field* board_random(void);

void draw_image(field* entry);

void put_pixel(GdkPixbuf* pixbuf, unsigned x, unsigned y, unsigned red, unsigned green, unsigned blue);

void board_draw(board* enter);

unsigned set_walls(unsigned walls, unsigned rotation);

void draw_players(Player* enter, board* tab);

void field_copy(field* entry, field what);

field field_make(unsigned is_blank,unsigned walls, unsigned item, unsigned rotation);
