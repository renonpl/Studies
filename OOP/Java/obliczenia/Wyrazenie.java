package obliczenia;

abstract class Wyrazenie implements Obliczalny {

    /** metoda sumująca wyrażenia */
    public static int suma (Wyrazenie... wyr) {
        int result = 0;
        for (Wyrazenie w:
             wyr) {
            result += w.oblicz();
        }
        return result;
    };
    /** metoda mnożąca wyrażenia */
    public static int iloczyn (Wyrazenie... wyr) {
        int result = 1;
        for (Wyrazenie w:
                wyr) {
            result *= w.oblicz();
        }
        return result;
    }
}
