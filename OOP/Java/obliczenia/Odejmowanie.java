package obliczenia;

public class Odejmowanie extends Operator2Arg {

    public Odejmowanie(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return left.oblicz() - right.oblicz();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " - " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Odejmowanie && this.left.equals(((Odejmowanie) obj).left) && this.right.equals(((Odejmowanie) obj).right);
    }
}
