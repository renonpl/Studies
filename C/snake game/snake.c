#include <ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include <curses.h>
#include <time.h>
#include"snake.h"


snake* make_new_snake(unsigned x_pos, unsigned y_pos, unsigned size)
{
    snake_body* exit = (snake_body*)malloc(sizeof(snake_body));
    snake* ex = (snake*)malloc(sizeof(snake));
    ex->size = size;
    exit->x = x_pos;
    exit->y = y_pos;
    exit->parent = NULL;
    size--;
    x_pos--;
    snake_body* next = exit;
    while(size)
    {
        snake_body* temp = (snake_body*)malloc(sizeof(snake_body));
       // exit.parent = *temp;
        temp->x = x_pos;
        temp->y = y_pos;
        temp->parent = next;
        next = temp;
        x_pos--;
        size--;
    }
    ex->head = exit;
    ex->tail = next;
    ex->egg_list = NULL;
   return ex;
}

void delete_snake(snake* enter)
{
    snake_body* temp;
    if(enter->egg_list != NULL)
    {
        temp = enter->egg_list->tail;
        while(temp->parent != NULL)
        {
            snake_body* t = temp->parent;
            free(temp);
            temp = t;
        }
        free(temp);
        free(enter->egg_list);
    }
    temp = enter->tail;
    while(temp->parent != NULL)
    {
        snake_body* t = temp->parent;
        free(temp);
        temp = t;
    }
    free(temp);
    free(enter);
}

snake* add_snake_body(snake* enter)
{
    snake_body* new_body = (snake_body*)malloc(sizeof(snake_body));
    new_body->x = enter->tail->x-1;
    new_body->y = enter->tail->y;
    new_body->parent = enter->tail;
    enter->tail = new_body;
    enter->size++;
    return enter;
}


int move_snake(snake* enter, int dest, int lastdest)
{
    if((dest + lastdest == KEY_UP + KEY_DOWN) || (dest + lastdest == KEY_LEFT + KEY_RIGHT)) return move_snake(enter,lastdest,lastdest);
    if(dest != KEY_UP && dest != KEY_DOWN && dest != KEY_LEFT && dest != KEY_RIGHT) return move_snake(enter, lastdest, lastdest);
    snake_body* new_head = enter->tail;
    mvaddch(enter->tail->y,enter->tail->x,' ');
    new_head->x = enter->head->x;
    new_head->y = enter->head->y;
    switch(lastdest)
    {
        case KEY_UP:
            new_head->y--;
            break;
        case KEY_DOWN:
            new_head->y++;
            break;
        case KEY_LEFT:
            new_head->x--;
            break;
        case KEY_RIGHT:
            new_head->x++;
            break;
    }

    enter->tail = new_head->parent;
    new_head->parent = NULL;
    enter->head->parent = new_head;
    enter->head=new_head;
    return dest;
}

void display_snake(snake* enter)
{
    snake_body* tp = enter->tail;
    while(tp->parent != NULL)
    {
        mvaddch(tp->y,tp->x,'x');
        tp = tp->parent;
    }
    mvaddch(tp->y,tp->x,'o');
    if(enter->egg_list != NULL)
    {
        tp = enter->egg_list->tail;
        while(tp->parent != NULL)
        {
            mvaddch(tp->y,tp->x,'E');
            tp = tp->parent;
        }
        mvaddch(tp->y,tp->x,'E');
    }
    refresh();
}

unsigned collision_check(snake* enter, WINDOW* local_win)
{
    unsigned compare;
    compare = getmaxx(local_win);
    if(enter->head->x == compare || enter->head->x == compare - 80) return 0;
    compare = getmaxy(local_win);
    if(enter->head->y == compare+1 || enter->head->y == compare - 18) return 0;

    snake_body* check = enter->tail;
    while(check->parent != NULL)
    {
        if(check->x == enter->head->x && check->y == enter->head->y) return 0;
        check = check->parent;
    }
    if(enter->egg_list != NULL)
    {
        check = enter->egg_list->tail;
        while(check->parent != NULL)
        {
            if(check->x == enter->head->x && check->y == enter->head->y) return 0;
            check = check->parent;
        }
        if(check->x == enter->head->x && check->y == enter->head->y) return 0;
    }
    return 1;
}


snake* new_egg(snake* enter)
{
    snake_body* exit = (snake_body*)malloc(sizeof(snake_body));
    snake* ex = (snake*)malloc(sizeof(snake));
    ex->size = 1;
    exit->x = enter->tail->x;
    exit->y = enter->tail->y;
    exit->parent = NULL;
    ex->head = exit;
    ex->tail = exit;
    ex->egg_list = NULL;
    return ex;
}

void add_egg(snake* enter)
{
    snake_body* new_body = (snake_body*)malloc(sizeof(snake_body));
    new_body->x = enter->tail->x;
    new_body->y = enter->tail->y;
    new_body->parent = enter->egg_list->tail;
    enter->egg_list->tail = new_body;
    enter->egg_list->size++;
    return;
}

food* start_food(unsigned size, WINDOW* local_win)
{
    food* exit = malloc(size*sizeof(food));
    for(unsigned i = 0; i < size; i++)
    {
        food temp;
        temp.score = rand()%10+1;
        temp.x = rand()%78+1;
        temp.y = rand()%18+1+(getmaxy(local_win)-18);
        temp.timer = rand()%100+1;
        exit[i] = temp;
    }
    return exit;
}

void delete_food(food* tab)
{
    free(tab);
    return;
}


void generate_food(food* tab, unsigned index, WINDOW* local_win)
{
        food temp;
        temp.score = rand()%10+1;
        temp.x = rand()%78+1;
        temp.y = rand()%18+1+(getmaxy(local_win)-18);
        temp.timer = rand()%100+1;
        tab[index] = temp;
        return;
}

void display_food(food* tab, unsigned size)
{
    for(unsigned i = 0; i < size; i++)
    {
        food temp = tab[i];
        mvaddch(temp.y,temp.x,'F');
    }
    refresh();
}

unsigned food_eat(food* tab, unsigned size, snake* enter, unsigned score, unsigned diff, WINDOW* local_win)
{
    score+=diff;
    for(unsigned i = 0; i < size; i++)
    {
        if(tab[i].x == enter->head->x && tab[i].y == enter->head->y)
        {
            score += tab[i].score +1;
            enter = add_snake_body(enter);
            generate_food(tab,i, local_win);
            if(enter->size%5 == 0)
            {
                if(enter->size == 20)
                {
                    enter->egg_list = new_egg(enter);
                }
                else
                {
                    add_egg(enter);
                }
                score += diff*5;
                    switch(diff)
                    {
                        case 1:
                            timeout(300-(enter->size-20)/5);
                            break;
                        case 2:
                            timeout(200-(enter->size-20)/5);
                            break;
                        case 3:
                            timeout(100-(enter->size-20)/5);
                            break;
                        break;
                    }
            }

        }
    }
    return score;
}

void food_decay(food* tab, unsigned size,  WINDOW* local_win)
{
    for(unsigned i = 0; i < size; i++)
    {
        tab[i].timer--;
        if(tab[i].timer == 0)
        {
            mvaddch(tab[i].y,tab[i].x, ' ');
            generate_food(tab,i, local_win);
        }
    }
    return;
}


unsigned game_start()
{
    printw("Witamy w grze Snake \n Wybierz swoj poziom trudnosci \n 1 - Latwy 2 - Sredni 3 - Trudny");
    char c = getch();
    while(c < '1' || c > '3') c = getch();
    clear();
    unsigned exit = c -'0';
    switch(exit)
    {
        case 1:
            timeout(300);
            break;
        case 2:
            timeout(200);
            break;
        case 3:
            timeout(100);
            break;
        break;
    }
    return exit;
}

WINDOW *create_newwin()
{	WINDOW *local_win;

	local_win = newwin(20, 80, (LINES - 20)/2, (COLS - 80)/2);
	box(local_win, 0 , 0);

	wrefresh(local_win);

	return local_win;
}
