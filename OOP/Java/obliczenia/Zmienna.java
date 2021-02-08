package obliczenia;

import struktury.ZbiorNaTablicyDynamicznej;

public class Zmienna extends Wyrazenie {
    public static final ZbiorNaTablicyDynamicznej set = new ZbiorNaTablicyDynamicznej();
    String variable;

    public Zmienna(String v)
    {
        variable = v;
    }
    public int oblicz(){
        try {
            return (int) set.czytaj(variable);
        }
        catch (Exception e){
            System.out.println(e.getMessage());
            return 0;
        }
    }

    public String toString()
    {
        return variable;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Zmienna && this.variable == ((Zmienna) obj).variable;
    }
}
