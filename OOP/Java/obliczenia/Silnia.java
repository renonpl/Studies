package obliczenia;

public class Silnia extends Operator1Arg {


    public Silnia(Wyrazenie l)
    {
        super(l);
    }


    @Override
    public int oblicz() {
        int result = 1;
        for(int i = 1; i < left.oblicz(); i++)
            result *= i;
        return result;
    }

    @Override
    public String toString() {
        return super.toString() + "!";
    }


    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof Silnia && this.left.equals(((Silnia) obj).left);
    }
}

