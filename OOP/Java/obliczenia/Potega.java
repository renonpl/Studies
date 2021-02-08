package obliczenia;

public class Potega extends Operator2Arg{

    public Potega(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }


    @Override
    public int oblicz() {
        return (int)Math.pow(left.oblicz(),right.oblicz());
    }

    @Override
    public String toString() {
        return "power( " + left.toString() + "," + right.toString() + ")";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Potega && this.left.equals(((Potega) obj).left) && this.right.equals(((Potega) obj).right);
    }
}
