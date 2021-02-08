package struktury;

public class ZbiorNaTablicy extends Zbior {
      private int size;
      private int last;
      private Para[] tab;
      public ZbiorNaTablicy(int n){
            if(n < 2) throw new IllegalArgumentException("Tablica musi byc rozmiaru conajmniej 2");
            size = n;
            last = 0;
            tab = new Para[n];
        }
        public ZbiorNaTablicy(){
            this(10);
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
                 throw new Exception("Tablica za mala");
             tab[last++] = p;
         }

         public void usun (String k){
             for(int i = 0; i < last; i++)
                 if(tab[i].klucz.equals(k))
                 {
                     tab[i] = tab[--last];
                     return;
                 }
         }

        public double czytaj (String k) throws Exception
        {
            Para p = znajdz(k);
            if(p == null)
                 throw new Exception("Nie ma takiej pary");
            return p.getValue();
        }

         public void ustaw (Para p) throws Exception
         {
             Para k = znajdz(p.klucz);
             if(k != null) {
                k.setValue(p.getValue());
                return;
             }
             if(last == size)
                 throw new Exception("Tablica za mala");
             tab[last++] = p;
         }

         public void czysc ()
         {
             last = 0;
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
