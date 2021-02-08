package obliczenia;

public class While extends Instrukcja {
    Instrukcja i;
    Wyrazenie w;

    public While(Instrukcja p, Wyrazenie war) throws  Exception
    {
        if(p == null || war == null) throw new Exception("Nulle");
        i = p;
        w = war;
    }

    @Override
    public void wykonaj() {
        while(w.oblicz() != 0)
            i.wykonaj();
    }
}
