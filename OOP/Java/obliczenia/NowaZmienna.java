package obliczenia;
import struktury.Para;

public class NowaZmienna extends  Instrukcja{
    public String v;

    public NowaZmienna(String s) throws Exception{
        if(s == null) throw new Exception("Nulle");
        v = s;
    }

    @Override
    public void wykonaj(){
        try {
            Zmienna.set.wstaw(new Para(v, 0));
        }
        catch (Exception e){
            System.out.println(e);
        }
    }
}
