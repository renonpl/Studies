package obliczenia;

public class Modulo extends Operator2Arg{

    public Modulo(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return left.oblicz() % right.oblicz();
    }

    @Override
    public String toString() {
        return left.toString() + " % " + right.toString();
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Modulo && this.left.equals(((Modulo) obj).left) && this.right.equals(((Modulo) obj).right);
    }
}
