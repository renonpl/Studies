import obliczenia.*;

public class testob {
    public static void main(String[] args) {
        try {
            Zmienna.set.czysc();
            Blok b = new Blok(new NowaZmienna("n"), new Czytaj("n"),new IfElse(
                    new Wypisz(new Stala(0)),
                    new Blok(new NowaZmienna("p"), new Przypisz("p", new Liczba(2)), new NowaZmienna("wyn"), new While(
                            new Blok(new If(
                                        new Blok(new Przypisz("wyn", new Zmienna("p")),
                                                new Przypisz("p", new Zmienna("n"))),
                                        new Rowne(new Modulo(new Zmienna("n"),new Zmienna("p")), new Stala(0))),
                                    new Przypisz("p", new Dodawanie(new Zmienna("p"),new Liczba(1)))),
                            new MniejszeRowne(new Mnozenie(new Zmienna("p"), new Zmienna("p")),new Zmienna("n"))),
                            new IfElse(new Wypisz(new Stala(0)),
                                    new Wypisz(new Stala(1)),
                                    new Wieksze(new Zmienna("wyn"),new Stala(0)))),
                    new Mniejsze(new Zmienna("n"),new Liczba(2))));

            b.wykonaj();
        }
        catch (Exception e){
            System.out.println(e.getMessage());
        }
    }
}
