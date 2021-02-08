package obliczenia;

public class ZmianaZnaku extends Operator1Arg {


    public ZmianaZnaku(Wyrazenie l)
    {
        super(l);
    }



    public int oblicz(){
        return -1* left.oblicz();
    }
    public String toString(){
        return "-(" + super.toString() + ")";
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == null)
            return false;
        return obj instanceof ZmianaZnaku && this.left.equals(((ZmianaZnaku) obj).left);
    }
}
