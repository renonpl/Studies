package obliczenia;

public class Maksimum extends Operator2Arg {

    public Maksimum(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return left.oblicz() > right.oblicz() ? left.oblicz() : right.oblicz();
    }

    @Override
    public String toString() {
        return "max( " +left.toString() + "," + right.toString() + ")";
    }

    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Maksimum && this.left.equals(((Maksimum) obj).left) && this.right.equals(((Maksimum) obj).right);
    }
}
