/*
    Copyright (c) November 2010 by Paweł Rzechonek
    Aplikacja okienkowa AWT - prezentuje możliwości klasy Canvas
    w przechwytywaniu zdarzeń od myszy i od klawiatury.
    Aby przechwytywać zdarzenia od klawiatury trzeba najpierw wywołać metodę
    setFocusable(true) na obiekcie Canvas.
*/

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.util.Random;
import java.util.Stack;
import java.util.Vector;

class Chamber{
    public int x,y;
    public int mask;
    public boolean visited;

    public Chamber(int a, int b, int m){
        x = a;
        y = b;
        mask = m;
    }

    public void setXY(int a, int b){
        x = a;
        y = b;
    }
    public void setMask(int m){
        mask = m | mask;
    }
}


class Board{
    static public int size = 10;
    static public Chamber[][] tab = new Chamber[size][size];
    static public int playerX;
    static public int playerY;
    //bitmask 1 up 2 right, 4 down, 8 left
    Random rand = new Random();

    public Board(){
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                tab[i][j] = new Chamber(i,j,0);
            }
        }

        Stack<Chamber> st = new Stack<>();
        tab[0][0].setMask(1);
        st.push(tab[0][0]);
        tab[0][0].visited = true;
        while(!st.empty()){
            Chamber z = st.pop();
            Vector<Chamber> v = new Vector<>();
            if(z.x != size-1)
                if(!tab[z.x+1][z.y].visited)
                  v.add(tab[z.x+1][z.y]);
            if(z.x != 0)
                if(!tab[z.x-1][z.y].visited)
                    v.add(tab[z.x-1][z.y]);
            if(z.y != size-1)
                if(!tab[z.x][z.y+1].visited)
                    v.add(tab[z.x][z.y+1]);
            if(z.y != 0)
                if(!tab[z.x][z.y-1].visited)
                    v.add(tab[z.x][z.y-1]);

            if(!v.isEmpty()){
                int n = rand.nextInt(v.size());
                Chamber p = v.elementAt(n);
                if(p.x == z.x)
                    if(p.y > z.y){
                        p.setMask(1);
                        z.setMask(4);
                    }else{
                        p.setMask(4);
                        z.setMask(1);
                    }
                else{
                    if(p.x > z.x) {
                        p.setMask(8);
                        z.setMask(2);
                    }else{
                        p.setMask(2);
                        z.setMask(8);
                    }
                }
                st.push(z);
                p.visited = true;
                st.push(p);
            }
        }
        playerX = 4 + rand.nextInt(5);
        playerY = 4 + rand.nextInt(5);
    }
}

class Paint extends Frame{

    private Canvas plotno = new Canvas() {
        @Override
        public void paint(Graphics gr) {
            super.paint(gr);
            drawBoard();
            drawPlayer();
        }
    };
    private TextField pole = new TextField("Poprowadz postac do wyjscia!");

    String filename = "indiana.jpg";
    int rect_size = 60;
    Image badacz = null;

    private WindowListener frameList = new WindowAdapter()
    {
        @Override
        public void windowClosing (WindowEvent ev)
        {
            Paint.this.dispose();
        }
    };

    private KeyListener keyList = new KeyAdapter()
    {
        @Override
        public void keyPressed (KeyEvent ev)
        {
            Chamber c = Board.tab[Board.playerX][Board.playerY];
            switch (ev.getKeyCode())
            {
                case KeyEvent.VK_UP:
                    if((c.mask & 1) != 0) {
                        removePlayer();
                        Board.playerY--;
                    }
                    break;
                case KeyEvent.VK_DOWN:
                    if((c.mask & 4) != 0) {
                        removePlayer();
                        Board.playerY++;
                    }
                    break;
                case KeyEvent.VK_LEFT:
                    if((c.mask & 8) != 0) {
                        removePlayer();
                        Board.playerX--;
                    }
                    break;
                case KeyEvent.VK_RIGHT:
                    if((c.mask & 2) != 0) {
                        removePlayer();
                        Board.playerX++;
                    }
                    break;
            }
            drawPlayer();
            if((Board.playerY | Board.playerX) == 0){
                pole.setText("KONIEC GRY! GRATULACJE!");
                plotno.removeKeyListener(keyList);
            }
        }
    };

    public Paint()
    {
        super("Labirynt");
        setSize(800, 800);
        setLocation(100, 100);
        try{
            badacz = ImageIO.read(new File(filename));
        }catch (Exception e){
            System.out.println(e.toString());
        }
        add(plotno, BorderLayout.CENTER);
        add(pole, BorderLayout.SOUTH);
        plotno.addKeyListener(keyList);
        plotno.setFocusable(true);
        plotno.requestFocus();
        addWindowListener(frameList);
        setVisible(true);
    }

    public void drawBoard(){
        Graphics gr = plotno.getGraphics();
        gr.setColor(Color.BLACK);
        for(int i = 0; i < Board.size; i++){
            for(int j = 0; j < Board.size; j++){
                Chamber c = Board.tab[i][j];
                if((c.mask & 1) == 0)
                    gr.fillRect(i*rect_size,j*rect_size, rect_size,5);
                if((c.mask & 2) == 0)
                    gr.fillRect(i*rect_size+rect_size-5,j*rect_size, 5,rect_size);
                if((c.mask & 4) == 0)
                    gr.fillRect(i*rect_size,j*rect_size+rect_size-5, rect_size,5);
                if((c.mask & 8) == 0)
                    gr.fillRect(i*rect_size,j*rect_size, 5,rect_size);
                gr.fillRect(i*rect_size,j*rect_size, 5,5);
                gr.fillRect(i*rect_size+rect_size-5,j*rect_size, 5,5);
                gr.fillRect(i*rect_size,j*rect_size+rect_size-5, 5,5);
                gr.fillRect(i*rect_size+rect_size-5,j*rect_size+rect_size-5, 5,5);
            }
        }
    }

    public void drawPlayer(){
        Graphics gr = plotno.getGraphics();
        gr.drawImage(badacz,Board.playerX*rect_size+5,Board.playerY*rect_size+5,rect_size-10,rect_size-10, null);
    }
    public void removePlayer(){
        Graphics gr = plotno.getGraphics();
        gr.setColor(Color.WHITE);
        gr.fillRect(Board.playerX*rect_size+5,Board.playerY*rect_size+5,rect_size-10,rect_size-10);
    }
}

public class Labirynt {
    public static void main(String[] args) {
            new Board();
            new Paint();
    }
}
