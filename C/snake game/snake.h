#pragma once
#include <ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

typedef struct snake_b
{
    unsigned x;
    unsigned y;
    struct snake_b* parent;
 //   unsigned head;
}snake_body;

typedef struct sn
{
    struct snake_b* head;
    struct snake_b* tail;
    unsigned size;
    struct sn* egg_list;
}snake;

typedef struct fd
{
    unsigned score;
    unsigned x;
    unsigned y;
    unsigned timer;
}food;


WINDOW *create_newwin();

snake* make_new_snake(unsigned x_pos, unsigned y_pos, unsigned size);

void delete_snake(snake* enter);

snake* add_snake_body(snake* enter);


int move_snake(snake* enter, int dest, int lastdest);

void display_snake(snake* enter);

unsigned collision_check(snake* enter, WINDOW* local_win);


snake* new_egg(snake* enter);

void add_egg(snake* enter);

food* start_food(unsigned size, WINDOW* local_win);

void delete_food(food* tab);

void generate_food(food* tab, unsigned index, WINDOW* local_win);

void display_food(food* tab, unsigned size);

unsigned food_eat(food* tab, unsigned size, snake* enter, unsigned score, unsigned diff,  WINDOW* local_win);

void food_decay(food* tab, unsigned size,  WINDOW* local_win);

unsigned game_start();
