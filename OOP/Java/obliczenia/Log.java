package obliczenia;

public class Log extends Operator2Arg {

    public Log(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {

        return (int)(Math.log(right.oblicz()) / Math.log(left.oblicz()));
    }

    @Override
    public String toString() {
        return "log( " +left.toString() + "," + right.toString() + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Log && this.left.equals(((Log) obj).left) && this.right.equals(((Log) obj).right);
    }
}
