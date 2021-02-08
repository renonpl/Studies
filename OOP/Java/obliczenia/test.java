package obliczenia;

import struktury.Para;
import struktury.ZbiorNaTablicy;

public class test {
    public static void main(String[] args) {
        Wyrazenie w = new Dodawanie(new Liczba(3), new Liczba(5));
        System.out.println(w.oblicz());
        System.out.println(w.toString());

        Wyrazenie w2 = new Dodawanie(
                new Liczba(7),
                new Mnozenie(
                        new Zmienna("x"),
                        new Liczba(5)
                )
        );

        Zmienna.set.ustaw(new Para("x",2));
        System.out.println(w2.oblicz());
        System.out.println(w2.toString());

        Wyrazenie w3 = new Dzielenie(
                    new Odejmowanie(
                            new Mnozenie(
                                    new Liczba(3),
                                    new Liczba(11)
                            ),
                            new Liczba(1)
                    ),
                    new Dodawanie(
                            new Liczba(7),
                            new Liczba(5)
                    )
                );
        System.out.println(w3.oblicz());
        System.out.println(w3.toString());

        Wyrazenie w4 = new Minimum(
                new Mnozenie(
                        new Dodawanie(
                                new Zmienna("x"),
                                new Liczba(13)
                        ),
                        new Zmienna("x")
                ),
                new Modulo(
                        new Odejmowanie(
                                new Liczba(1),
                                new Zmienna("x")
                        ),
                        new Liczba(2)
                )
        );
        System.out.println(w4.oblicz());
        System.out.println(w4.toString());

        Zmienna.set.ustaw(new Para("y",1));
        Wyrazenie w5 = new Mniejsze(
                new Dodawanie(
                        new Potega(
                                new Liczba(2),
                                new Liczba(5)
                        ),
                        new Mnozenie(
                                new Zmienna("x"),
                                new Log(
                                        new Liczba(2),
                                        new Zmienna("y")
                                )
                        )
                ),
                new Liczba(20)
        );
        System.out.println(w5.oblicz());
        System.out.println(w5.toString());

    }
}
