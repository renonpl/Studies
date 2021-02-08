package obliczenia;

public class Minimum extends Operator2Arg {

    public Minimum(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {
        return left.oblicz() > right.oblicz() ? right.oblicz() : left.oblicz();
    }

    @Override
    public String toString() {
        return "min( " +left.toString() + "," + right.toString() + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Minimum && this.left.equals(((Minimum) obj).left) && this.right.equals(((Minimum) obj).right);
    }
}
