package obliczenia;

public class Dodawanie extends Operator2Arg {

    public Dodawanie(Wyrazenie l, Wyrazenie r)
    {
        super(l,r);
    }

    @Override
    public int oblicz() {
        return left.oblicz() + right.oblicz();
    }

    @Override
    public String toString() {
        return "(" + left.toString() + " + " + right.toString() + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Dodawanie && this.left.equals(((Dodawanie) obj).left) && this.right.equals(((Dodawanie) obj).right);
    }
}
