package obliczenia;

import java.util.ArrayList;
import java.util.List;

public class Blok extends Instrukcja{
    Instrukcja[] tab;

    public Blok(Instrukcja... list) throws  Exception{
        if(list == null) throw new Exception("nulle");
        tab = list;
    }

    @Override
    public void wykonaj() {
        List<String> varList =new ArrayList<String>();

        for (Instrukcja i:
             tab) {
            i.wykonaj();
            if (i instanceof NowaZmienna) {
                varList.add(((NowaZmienna) i).v);
            }
        }
         for(String s: varList)
                Zmienna.set.usun(s);

        }
    }

