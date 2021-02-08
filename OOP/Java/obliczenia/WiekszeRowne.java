package obliczenia;

public class WiekszeRowne extends Operator2Arg{



    public WiekszeRowne(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {
        return left.oblicz() >= right.oblicz() ? 1 : 0;
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " >= " + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof WiekszeRowne && this.left.equals(((WiekszeRowne) obj).left) && this.right.equals(((WiekszeRowne) obj).right);
    }
}
