package obliczenia;

public class Mnozenie  extends Operator2Arg{

    public Mnozenie(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {
        return left.oblicz() * right.oblicz();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " * " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Mnozenie && this.left.equals(((Mnozenie) obj).left) && this.right.equals(((Mnozenie) obj).right);
    }
}
