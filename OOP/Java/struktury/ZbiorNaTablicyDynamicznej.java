package struktury;

public class ZbiorNaTablicyDynamicznej extends Zbior {
    private int size;
    private int last;
    private Para[] tab;
    public ZbiorNaTablicyDynamicznej(){
        size = 2;
        last = 0;
        tab = new Para[size];
    }

    private void doubleUp(){
        size *= 2;
        Para[] temp = new Para[size];
        System.arraycopy(tab,0,temp,0,last);
        tab = temp;
    }

    private void doubleDown(){
        if(size > 2) {
            size /= 2;
            if(last > size)
                last = size;
            Para[] temp = new Para[size];
            System.arraycopy(tab, 0, temp, 0, size/2);
            tab = temp;
        }
    }

    private Para znajdz(String k)
    {
        for(int i = 0; i < last; i++)
            if(tab[i].klucz.equals(k))
                return tab[i];
        return null;

    }

    public Para szukaj (String k) throws Exception
    {
        Para p = znajdz(k);
        if (p == null)
            throw new Exception("Nie ma takiej pary");
        return p;
    }

    public void wstaw (Para p) throws Exception
    {
        Para k = znajdz(p.klucz);
        if (k != null)
            throw new Exception("Juz jest taki klucz");
        if(last == size)
            doubleUp();
        tab[last++] = p;
    }

    public void usun (String k){
        for(int i = 0; i < last; i++)
            if(tab[i].klucz.equals(k))
            {
                tab[i] = tab[--last];
                break;
            }
        if(last < size/4)
            doubleDown();
    }

    public double czytaj (String k) throws Exception
    {
        Para p = znajdz(k);
        if(p == null)
            throw new Exception("Nie ma takiej pary");
        return p.getValue();
    }

    public void ustaw (Para p)
    {
        Para k = znajdz(p.klucz);
        if(k != null) {
            k.setValue(p.getValue());
            return;
        }
        if(last == size)
            doubleUp();
        tab[last++] = p;
    }

    public void czysc()
    {
        size = 2;
        last = 0;
        tab = new Para[size];
    }

    public int ile()
    {
        return last;
    }

    public void print(){
        System.out.println("Size/Last/Tab");
        System.out.println(size);
        System.out.println(last);
        for(int i = 0; i < last; i++)
            System.out.println(tab[i].toString());
    }
}
