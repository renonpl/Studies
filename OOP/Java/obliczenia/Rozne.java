package obliczenia;

public class Rozne extends Operator2Arg {

    public Rozne(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return left.oblicz() != right.oblicz() ? 1 : 0;
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " != " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Rozne && this.left.equals(((Rozne) obj).left) && this.right.equals(((Rozne) obj).right);
    }
}
