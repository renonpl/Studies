package obliczenia;

public class IfElse extends Instrukcja {
    Instrukcja tr;
    Instrukcja fl;
    Wyrazenie w;
    public IfElse(Instrukcja a, Instrukcja b, Wyrazenie w) throws Exception{
        if(a == null || b == null || w == null) throw new Exception("Nulle");
        this.tr = a;
        this.fl = b;
        this.w = w;
    }
    public void wykonaj(){
        if(w.oblicz() != 0) tr.wykonaj();
        else fl.wykonaj();
    }
}
