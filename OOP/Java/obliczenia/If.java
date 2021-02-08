package obliczenia;

public class If extends Instrukcja {
    Instrukcja i;
    Wyrazenie w;
    public If(Instrukcja i, Wyrazenie w) throws Exception{
        if(i == null || w == null) throw new Exception("Nulle");
        this.i = i;
        this.w = w;
    }
    public void wykonaj(){
        if(w.oblicz() != 0) i.wykonaj();
    }
}
