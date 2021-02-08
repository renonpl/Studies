package Mikolaj;

import java.util.Random;
import java.util.RandomAccess;

import static java.lang.Math.random;

public class Child implements   Runnable {
    int x, y;
    static int wtime = 1000;


    public Child(){
        Random rand = new Random();
        x = rand.nextInt(Board.size);
        y = rand.nextInt(Board.size);
        while(Math.abs(Board.size/2-x) < 5 && Math.abs(Board.size/2-y) < 5 || Board.tab[x][y] == 4) {
            x = rand.nextInt(Board.size);
            y = rand.nextInt(Board.size);
        }
        Board.tab[x][y] = 4;

    }

    public boolean CheckforSanta(){
        if(Math.abs(x-Santa.x) == 1 && y == Santa.y || x == Santa.x && Math.abs(y-Santa.y) == 1 ||
            Math.abs(x-Santa.x) == Board.size-1 && y == Santa.y || x == Santa.x && Math.abs(y-Santa.y) == Board.size -1)
            return true;
        return false;
    }

    public boolean SearchforSanta(){
        for(int i = -3; i < 4; i++)
            for(int j = -3; j < 4; j++)
            {
                if((Board.tab[Math.floorMod(x+i,Board.size)][Math.floorMod(y+j, Board.size)] & 1) > 0)
                {
                    RuntoSanta();
                    return true;
                }
            }
        return false;
    }

    public void RuntoSanta()
    {
        for(int i = 0; i < 8; )
        {
            if(Board.end > 0)
                return;
            try {
                Thread.sleep((int) wtime);
            }
            catch(InterruptedException ex) {
                return;
            }
                if (x != Santa.x) {
                    if (Math.abs(Santa.x - x) > Board.size / 2) {
                        if (x > Board.size / 2) {
                            Board.MoveChild(this, (x + 1) % Board.size, y, false);
                            i++;
                            continue;
                        } else {
                            Board.MoveChild(this, Math.floorMod(x - 1, Board.size), y, false);
                            i++;
                            continue;
                        }

                    } else {
                        if (x > Santa.x) {
                            Board.MoveChild(this, x - 1, y, false);
                            i++;
                            continue;
                        } else {
                            Board.MoveChild(this, x + 1, y, false);
                            i++;
                            continue;
                        }
                    }
                }
                if (x != Santa.y) {
                    if (Math.abs(Santa.y - y) > Board.size / 2) {
                        if (y > Board.size / 2) {
                            Board.MoveChild(this, x, (y + 1) % Board.size, false);
                            i++;
                        } else {
                            Board.MoveChild(this, x, Math.floorMod(y - 1, Board.size), false);
                            i++;
                        }

                    } else {
                        if (y > Santa.y) {
                            Board.MoveChild(this, x, y - 1, false);
                            i++;
                        } else {
                            Board.MoveChild(this, x, y + 1, false);
                            i++;
                        }
                    }
                }
        }
    }

    public boolean CheckforPresent(){
        if(Board.tab[Math.floorMod((x-1),Board.size)][y] == 2)
        {
            Board.MoveChild(this,Math.floorMod((x-1),Board.size),y, true);
            return true;
        }
        if(Board.tab[x][Math.floorMod((y-1),Board.size)] == 2)
        {
            Board.MoveChild(this,x,Math.floorMod((y-1),Board.size), true);
            return true;
        }
        if(Board.tab[(x+1)%Board.size][y] == 2)
        {
            Board.MoveChild(this,(x+1)%Board.size, y, true);
            return true;
        }
        if(Board.tab[x][(y+1)%Board.size] == 2)
        {
            Board.MoveChild(this,x,(y+1)%Board.size, true);
            return true;
        }
        return false;
    }

    public void  RandomMove(){
        int temp = (int)(4 * random());
        switch (temp){
            case 0:
                Board.MoveChild(this,(x+1)%Board.size,y, false);
                break;
            case 1:
                Board.MoveChild(this, x,(y+1)%Board.size, false);
                break;
            case 2:
                Board.MoveChild(this, x,Math.floorMod((y-1),Board.size), false);
                break;
            case 3:
                Board.MoveChild(this, Math.floorMod((x-1),Board.size), y, false);
                break;
        }

    }

    public void run(){
            try {
                while(true) {
                    if(Board.end > 0)
                    {
                        return;
                    }
                    if(CheckforSanta())
                    {
                        Board.end = 1;
                        return;
                    }
                    if (CheckforPresent()) {
                        Board.decreaseKids();
                        return;
                    }
                    if(!SearchforSanta())
                        RandomMove();
                    Thread.sleep((int) (wtime * random() + 2*wtime));
                }
            }
            catch(InterruptedException ex) {
                return;
            }
    }
}
