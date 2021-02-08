package obliczenia;

public class DoWhile extends Instrukcja {
    Instrukcja i;
    Wyrazenie w;

    public DoWhile(Instrukcja p, Wyrazenie war) throws Exception {
        if(p == null || war == null) throw new Exception("Nulle");
        i = p;
        w = war;
    }

    @Override
    public void wykonaj() {
        do {
            i.wykonaj();
        } while (w.oblicz() != 0);
    }
}
