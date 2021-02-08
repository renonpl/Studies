package obliczenia;

public abstract class Operator1Arg extends Wyrazenie{

    Wyrazenie left;

    public Operator1Arg(Wyrazenie l)
    {
        left = l;
    }

    public Operator1Arg(){
        left = new Stala(0);
    }

    @Override
    public String toString() {
        return left.toString();
    }
}
