#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h>
#include<time.h>
#include<assert.h>
#include<gtk/gtk.h>
#include"board.h"

#define FIELD_SIZE 80

board* board_init(void)
{
    unsigned size = 9;
    board* exit;
    field** tab = (field**)malloc(size*sizeof(field*));
    for(unsigned i = 0; i < size; i++)
    {
        tab[i] = (field*)malloc(size*sizeof(field));
    }
    exit = (board*)malloc(sizeof(board));
    exit->tab = tab;
    exit->size = size;
    return exit;
}

void field_copy(field* entry, field what)
{
        entry->walls = what.walls;
        entry->pixel = what.pixel;
        entry->real_walls = what.walls;
        entry->item = what.item;
        entry->rotation = what.rotation;
        entry->is_blank = what.is_blank;
        return;
}

field field_make(unsigned is_blank, unsigned walls, unsigned item, unsigned rotation)
{
    field exit;
    exit.pixel = gdk_pixbuf_new(GDK_COLORSPACE_RGB,TRUE,8,FIELD_SIZE,FIELD_SIZE);
    gdk_pixbuf_fill(exit.pixel,0xffff);
    exit.image = gtk_image_new_from_pixbuf(exit.pixel);
    exit.is_blank = is_blank;
    exit.walls = walls;
    exit.item = item;
    exit.rotation = rotation;
    exit.real_walls = set_walls(walls, rotation);
    draw_image(&exit);
    return exit;
}

void board_destroy(board* entry)
{
    unsigned size = entry->size;
    for(unsigned i = 0; i < size; i++)
    {
        free(entry->tab[i]);
    }
    free(entry->tab);
    free(entry);
    return;
}

void board_start(board* entry)
{
    field tempik;
    field* random_tab = board_random();
    tempik.is_blank = 2;
    for(unsigned i = 0; i < entry->size; i++)  for(unsigned j = 0; j < entry->size;j++) entry->tab[i][j] = tempik;
    FILE* descr;
    descr = fopen("field_descr.txt", "r");
    for(unsigned i = 0; i < 16; i++)
    {
        field temp;
        unsigned a, b, c, d, err;
        err = fscanf(descr,"%d%d%d%d", &a, &b, &c, &d);
        assert(err > 0);
        temp = field_make(0,a,d,0);
        entry->tab[b][c] = temp;
    }
    fclose(descr);
    unsigned index = 0;
    for(unsigned i = 0; i < entry->size; i++)
    {
        for(unsigned j = 0; j < entry->size; j++)
        {
            if(i == 0 || j == 0 || i == entry->size -1 || j == entry->size -1)
            {
                field temp;
                temp = field_make(1,0,0,0);
                entry->tab[i][j] = temp;
                continue;
            }
            if(entry->tab[i][j].is_blank == 2)
            {
                entry->tab[i][j] = random_tab[index];
                index++;
            }
        }
    }
    field first_free;
    first_free = field_make(3,5,0,0);
    entry->tab[0][0] = first_free;
    free(random_tab);
    board_draw(entry);
    return;
}

field* board_random(void)
{
    field* exit = (field*)malloc(33*sizeof(field));
    FILE* descr;
    descr = fopen("list.txt", "r");
    for(unsigned i = 0; i < 33; i++)
    {
        field temp;
        temp.is_blank = 1;
        exit[i] = temp;
    }
    srand(time(0));
    for(unsigned i = 0; i < 33; i++)
    {
        field temp;
        unsigned a, b, err;
        err = fscanf(descr,"%d%d", &a, &b);
        assert(err > 0);
        temp = field_make(0,a,b,rand()%4);
        unsigned position = rand() % 33;
        while(exit[position].is_blank == 0) position = rand() % 33;
        exit[position] = temp;
    }
    fclose(descr);
    return exit;
}

void draw_image(field* entry)
{
    if(entry->is_blank == 1)
    {
        for(unsigned i = 0; i < FIELD_SIZE; i++)
        {
            for(unsigned j = 0; j < FIELD_SIZE; j++)
            {
                put_pixel(entry->pixel, j,i,200,200,200);
            }
        }
        gtk_image_set_from_pixbuf((GtkImage*)entry->image,entry->pixel);
        return;
    }
    unsigned wall = entry->real_walls;
    for(unsigned i = 0; i < FIELD_SIZE; i++)
        {
            for(unsigned j = 0; j < FIELD_SIZE; j++)
            {
                put_pixel(entry->pixel, j,i,100,100,100);
            }
        }
    for(unsigned i = 0; i < FIELD_SIZE; i++)
    {
        for(unsigned j = 0; j < FIELD_SIZE; j++)
        {
            if((i < FIELD_SIZE/5 && j < FIELD_SIZE/5) || (i < FIELD_SIZE/5 && j > 4*FIELD_SIZE/5-1) || (i > 4*FIELD_SIZE/5-1 && j < FIELD_SIZE/5) || (i > 4*FIELD_SIZE/5-1 && j > 4*FIELD_SIZE/5-1))
            {
                put_pixel(entry->pixel,j,i,0,0,0);
            }
        }
    }
    if(wall & 1)
    {
        for(unsigned i = 0; i < FIELD_SIZE; i++)
        {
            for(unsigned j = 4*FIELD_SIZE/5; j < FIELD_SIZE; j++)
            {
                put_pixel(entry->pixel,j,i,0,0,0);
            }
        }
    }
    if(wall & 2)
    {
        for(unsigned i = 4*FIELD_SIZE/5; i < FIELD_SIZE; i++)
        {
            for(unsigned j = 0; j < FIELD_SIZE; j++)
            {
                put_pixel(entry->pixel,j,i,0,0,0);
            }
        }
    }
    if(wall & 4)
    {
        for(unsigned i = 0; i < FIELD_SIZE; i++)
        {
            for(unsigned j = 0; j < FIELD_SIZE/5; j++)
            {
                put_pixel(entry->pixel,j,i,0,0,0);
            }
        }
    }
    if(wall & 8)
    {
        for(unsigned i = 0; i < FIELD_SIZE/5; i++)
        {
            for(unsigned j = 0; j < FIELD_SIZE; j++)
            {
                put_pixel(entry->pixel,j,i,0,0,0);
            }
        }
    }
    if(entry->item != 0)
    {
        for(unsigned i = FIELD_SIZE*3/10; i < 7*FIELD_SIZE/10; i++)
        {
            put_pixel(entry->pixel,i,i,15,15,15);
            put_pixel(entry->pixel,i,FIELD_SIZE-i,15,15,15);

            put_pixel(entry->pixel,i-1,i,15,15,15);
            put_pixel(entry->pixel,i-1,FIELD_SIZE-i,15,15,15);

            put_pixel(entry->pixel,i+1,i,15,15,15);
            put_pixel(entry->pixel,i+1,FIELD_SIZE-i,15,15,15);
        }
    }

    for(unsigned i = 0; i < FIELD_SIZE; i++)
        {
            for(unsigned j = 0; j < FIELD_SIZE; j++)
            {
                if(i == 0 || j == 0 || i == FIELD_SIZE-1 || j == FIELD_SIZE-1)
                {
                    put_pixel(entry->pixel,j,i,200,200,200);
                }
            }
        }

    gtk_image_set_from_pixbuf((GtkImage*)entry->image,entry->pixel);
    return;
}

void put_pixel(GdkPixbuf* pixbuf, unsigned x, unsigned y, unsigned red, unsigned green, unsigned blue)
{
    int rowstride, n_channels;
    guchar* pixels, *p;

    n_channels = gdk_pixbuf_get_n_channels(pixbuf);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    pixels = gdk_pixbuf_get_pixels(pixbuf);

    p = pixels + y*rowstride + x*n_channels;
    p[0] = red;
    p[1] = green;
    p[2] = blue;
    return;
}

void board_draw(board* enter)
{
    for(unsigned i = 0; i < 9; i++)
    {
        for(unsigned j = 0; j < 9; j++)
        {
            draw_image(((enter->tab[i])+j));
        }
    }
    return;
}

unsigned set_walls(unsigned walls, unsigned rotation)
{
    unsigned temp = walls;
    unsigned i = rotation;
    while(i > 0)
    {
        unsigned wl = temp;
        temp = (temp << 1)%16;
        if(wl&8)temp++;
        i--;
    }
    return temp;
}

void draw_players(Player* enter, board* tab)
{
    for(unsigned i = 0; i < 4; i++)
    {
        Player temp = enter[i];

        if(temp.number == 0)
        {
            for(unsigned i = 3*FIELD_SIZE/10; i < FIELD_SIZE/2; i++)
            {
                for(unsigned j = 3*FIELD_SIZE/10; j < FIELD_SIZE/2; j++)
                {
                    put_pixel(tab->tab[temp.y][temp.x].pixel,j,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
                }
            }
        }
        if(temp.number == 1)
        {
            for(unsigned i = FIELD_SIZE/2; i < 7*FIELD_SIZE/10; i++)
            {
                for(unsigned j = 3*FIELD_SIZE/10; j < FIELD_SIZE/2; j++)
                {
                    put_pixel(tab->tab[temp.y][temp.x].pixel,j,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
                }
            }
        }
        if(temp.number == 2)
        {
            for(unsigned i = 3*FIELD_SIZE/10; i < FIELD_SIZE/2; i++)
            {
                for(unsigned j = FIELD_SIZE/2; j < 7*FIELD_SIZE/10; j++)
                {
                    put_pixel(tab->tab[temp.y][temp.x].pixel,j,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
                }
            }
        }
        if(temp.number == 3)
        {
            for(unsigned i = FIELD_SIZE/2; i < 7*FIELD_SIZE/10; i++)
            {
                for(unsigned j = FIELD_SIZE/2; j < 7*FIELD_SIZE/10; j++)
                {
                    put_pixel(tab->tab[temp.y][temp.x].pixel,j,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
                }
            }
        }
        field* find = NULL;
        for(unsigned i = 0; i < 9; i++)
        {
            for(unsigned j = 0; j < 9; j++)
            {
                if(tab->tab[i][j].item == temp.tab[temp.searching_index])
                {
                    find = &tab->tab[i][j];
                    break;
                }
            }
        }
        for(unsigned i = 3*FIELD_SIZE/10; i < 7*FIELD_SIZE/10; i++)
        {
            put_pixel(find->pixel,i,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
            put_pixel(find->pixel,i,FIELD_SIZE-i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);

            put_pixel(find->pixel,i-1,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
            put_pixel(find->pixel,i-1,FIELD_SIZE-i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
            put_pixel(find->pixel,i+1,i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
            put_pixel(find->pixel,i+1,FIELD_SIZE-i,temp.rgb.red,temp.rgb.green,temp.rgb.blue);
        }
    }
    return;
}
