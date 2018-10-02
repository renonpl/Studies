#include <ncurses.h>
#include "snake.h"


int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    srand(time(0));

    unsigned level = game_start();
    unsigned food_size = 10;
    snake* player = make_new_snake(20, 20, 16);
    unsigned score = 0;

    WINDOW* my_win = create_newwin();

    food* food_tab = start_food(food_size, my_win);

    int lastdest = KEY_RIGHT;
    int input = KEY_RIGHT;

    refresh();

    while(true)
    {
        lastdest = move_snake(player,input,lastdest);
        if(collision_check(player, my_win) == 0) break;
        score = food_eat(food_tab,food_size,player,score,level,my_win);
        food_decay(food_tab,food_size,  my_win);
        box(my_win, 0 , 0);
        wrefresh(my_win);
        display_food(food_tab, food_size);
        display_snake(player);


        input = getch();
    }

    clear();
    printw("Twoj wynik to:  %d \n Gratulacje!", score);
    timeout(10000);
    getch();
	endwin();
    delete_snake(player);
    delwin(my_win);
    delete_food(food_tab);
	return 0;
}
