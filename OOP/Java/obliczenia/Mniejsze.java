package obliczenia;

public class Mniejsze extends Operator2Arg {

    public Mniejsze(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() { return left.oblicz() < right.oblicz() ? 1 : 0;}

    @Override
    public String toString() {
        return "(" + left.toString() + " < " + right.toString() + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Mniejsze && this.left.equals(((Mniejsze) obj).left) && this.right.equals(((Mniejsze) obj).right);
    }
}
