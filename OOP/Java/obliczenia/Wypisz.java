package obliczenia;

public class Wypisz extends Instrukcja {
    Wyrazenie out;

    public Wypisz(Wyrazenie w) throws Exception{
        if(w == null) throw new Exception("Nulle");
        out = w;
    }

    @Override
    public void wykonaj() {
        System.out.println(out.oblicz());
    }
}
