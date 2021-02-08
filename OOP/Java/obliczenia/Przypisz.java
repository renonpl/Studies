package obliczenia;
import struktury.Para;

public class Przypisz extends Instrukcja{
    String v;
    Wyrazenie w;

    public Przypisz(String s, Wyrazenie w) throws Exception {
        if(s == null || w == null) throw new Exception("Nulle");
        v = s;
        this.w = w;
    }

    @Override
    public void wykonaj() {
        Zmienna.set.ustaw(new Para(v,w.oblicz()));
    }
}
