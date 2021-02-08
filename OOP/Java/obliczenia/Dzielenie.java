package obliczenia;

public class Dzielenie extends Operator2Arg {

    public Dzielenie(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {
        return left.oblicz() / right.oblicz();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " / " + right.toString() + ")";
    }

    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Dzielenie && this.left.equals(((Dzielenie) obj).left) && this.right.equals(((Dzielenie) obj).right);
    }
}
