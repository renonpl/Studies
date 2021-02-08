package Mikolaj;

import java.awt.*;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;


public class Window extends JPanel {

    static int rect_size = 20;
    static int sleep_time = 10;
    static List<Child> childList = new ArrayList<Child>(Board.kids);

    public Window() {
        KeyListener listener = new MyKeyListener();
        addKeyListener(listener);
        setFocusable(true);
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(Color.BLACK);
        for(int i = 0; i < Board.size; i++)
            for(int j = 0; j < Board.size; j++) {
                if((Board.tab[i][j] & 1 ) > 0){
                    g2d.setColor(Color.RED);
                    g2d.fillRect(Santa.x * rect_size, Santa.y * rect_size, rect_size, rect_size);
                    g2d.setColor(Color.BLACK);
                }
                if((Board.tab[i][j] & 4) > 0){
                    g2d.setColor(Color.BLUE);
                    g2d.fillRect(i * rect_size, j * rect_size, rect_size, rect_size);
                    g2d.setColor(Color.BLACK);
                }
                if((Board.tab[i][j] & 2) > 0) {
                    g2d.setColor(Color.GREEN);
                    g2d.fillOval(i * rect_size + rect_size/4, j * rect_size + rect_size/4, rect_size/2, rect_size/2);
                    g2d.setColor(Color.BLACK);
                }
                if(Board.tab[i][j] == 8) {
                    g2d.setColor(Color.YELLOW);
                    g2d.fillRect(i * rect_size, j * rect_size, rect_size, rect_size);
                    g2d.setColor(Color.BLACK);
                    continue;
                }
                g2d.drawRect(i * rect_size, j * rect_size, rect_size, rect_size);
            }
    }

    public static void main(String[] args) throws InterruptedException {
        Board.initialize_board();
        for(int i = 0; i < Board.kids; i++)
            childList.add(new Child());



        JFrame frame = new JFrame("Mikolaj");
        Window game = new Window();
        JLabel endscore = new JLabel("");
        game.add(endscore);
        frame.add(game);
        frame.setSize((Board.size+2)*rect_size, (Board.size+2)*rect_size);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        for(int i = 0; i < childList.size(); i++){
            new Thread(childList.get(i)).start();
        }

        javax.swing.Timer t = new javax.swing.Timer(20, new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                game.repaint();
            }
        });

        t.start();

        while (Board.end == 0 && Board.kids > 0)
        {
            Thread.sleep(10);
        }

        for(int i = 0; i < childList.size(); i++){
            new Thread(childList.get(i)).join();
        }
        t.stop();
        game.repaint();

        endscore.setFont(new Font("Calibri", Font.BOLD, 32));
        endscore.setText("<html> Koniec Gry! Dzieci bez prezentu: " +  Board.kids + "<br/> Liczba użytych prezentów: " + Board.score + "</html> ");


        System.out.println("KONIEC");
        return;
    }


    public class MyKeyListener implements KeyListener {
        @Override
        public void keyTyped(KeyEvent e) {
        }

        @Override
        public void keyPressed(KeyEvent e) {
            switch (e.getKeyChar()){
                case 'w':
                    Board.MoveSanta(Santa.x,Math.floorMod((Santa.y-1), Board.size));
                    break;
                case 's':
                    Board.MoveSanta(Santa.x,(Santa.y+1)%Board.size);
                    break;
                case 'a':
                    Board.MoveSanta(Math.floorMod((Santa.x-1), Board.size), Santa.y);
                    break;
                case 'd':
                    Board.MoveSanta((Santa.x+1)%Board.size,Santa.y);
                    break;
                case 'e':
                    Board.putPresent();
                    return;
            }
            System.out.println("keyPressed="+KeyEvent.getKeyText(e.getKeyCode()));
        }

        @Override
        public void keyReleased(KeyEvent e) {
            System.out.println("keyReleased="+KeyEvent.getKeyText(e.getKeyCode()));
        }
    }
}