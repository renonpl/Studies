package obliczenia;

public class Stala extends Wyrazenie{
    int value;

    public Stala(int n)
    {
        value = -1;
        if(n > 0) value = 1;
        if(n == 0) value = 0;
    }

    public int oblicz() {
        return value;
    }

    public String toString()
    {
        return Integer.toString(value);
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Stala && this.value == ((Stala) obj).value;
    }
}
