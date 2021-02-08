package obliczenia;

public class MniejszeRowne extends Operator2Arg{

    public MniejszeRowne(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return left.oblicz() <= right.oblicz() ? 1 : 0;
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " <= " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof MniejszeRowne && this.left.equals(((MniejszeRowne) obj).left) && this.right.equals(((MniejszeRowne) obj).right);
    }
}
