package obliczenia;

public class Rowne extends Operator2Arg {

    public Rowne(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {
        return left.oblicz() == right.oblicz() ? 1 : 0;
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " == " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Rowne && this.left.equals(((Rowne) obj).left) && this.right.equals(((Rowne) obj).right);
    }
}
