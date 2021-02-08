package obliczenia;

public class Wieksze extends Operator2Arg {

    public Wieksze(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return left.oblicz() > right.oblicz() ? 1 : 0;
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " > " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Wieksze && this.left.equals(((Wieksze) obj).left) && this.right.equals(((Wieksze) obj).right);
    }
}
