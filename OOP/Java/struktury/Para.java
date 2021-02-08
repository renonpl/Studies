package struktury;

public class Para {
    public final String klucz;
    private double wartosc;

    public Para(String s, double v){
        if(s == null)
            throw new IllegalArgumentException("Klucz pusty");
        if(!s.matches("^[a-z]+$"))
            throw new IllegalArgumentException("Klucz ma byc w malymi literami");

        klucz = s;
        wartosc = v;
    }

    public double getValue(){
        return wartosc;
    }
    public void setValue(double x){
        wartosc = x;
    }

    public String toString(){
        return "Para: " + klucz + " : " + wartosc;
    }

    public boolean equals(Object o){
        return o instanceof Para && this.klucz.equals(((Para) o).klucz);
    }
}
