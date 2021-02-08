package obliczenia;

public class Liczba extends Wyrazenie {
    int value;

    public Liczba(int n)
    {
        value = n;
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
        return obj instanceof Liczba && this.value == ((Liczba) obj).value;
    }
}
