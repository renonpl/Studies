package obliczenia;

public abstract class Operator2Arg extends Operator1Arg {
    Wyrazenie right;

    public Operator2Arg(Wyrazenie l, Wyrazenie r)
    {
        left = l;
        right = r;
    }

    public Operator2Arg() {
        left = new Stala(0);
        right = new Stala(0);
    }



}
