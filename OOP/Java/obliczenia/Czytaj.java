package obliczenia;

import struktury.Para;

import java.io.IOException;
import java.util.Scanner;

public class Czytaj  extends Instrukcja{
    String i;
    int value;

    public Czytaj(String s){
        i = s;
    }

    @Override
    public void wykonaj() {
            System.out.println("Czytam zmienna");
            Scanner sc = new Scanner(System.in);
            value = sc.nextInt();
            Zmienna.set.ustaw(new Para(i, value));

    }
}
