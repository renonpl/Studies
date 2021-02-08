package Mikolaj;

import java.util.Random;

import static java.lang.Math.random;

public final class Board {
    static int size = 30;
    static int score = 0;
    static volatile int kids = 12;
    static volatile int end = 0;
    static volatile int[][] tab = new int[size][size];


    public static void initialize_board(){
        for(int i = 0; i < size; i++)
            for(int j = 0; j < size; j++)
                tab[i][j] = 0;
        tab[size/2][size/2] = 1;
    }

    public synchronized static void MoveChild(Child t, int a, int b, boolean present) {
        if (tab[a][b] == 4)
            return;
        tab[t.x][t.y] &= (~4);
        t.x = a;
        t.y = b;
        if (t.x == Santa.x && t.y == Santa.y)
            end = 1;
        if(present){
            Board.tab[a][b] = 8;
        }
        else
            Board.tab[a][b] |= 4;
    }

    public synchronized static void MoveSanta(int x, int y)
    {
        if(tab[x][y] > 2)
            return;
        tab[Santa.x][Santa.y] &= (~1);
        Santa.x = x;
        Santa.y = y;
        tab[Santa.x][Santa.y] |= 1;
    }

    public static synchronized void putPresent(){
        tab[Santa.x][Santa.y] = 3;
        score++;
    }

    public static synchronized void decreaseKids(){
        kids--;
    }
}
