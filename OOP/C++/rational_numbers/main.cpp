#include"wym.hpp"

using namespace obliczenia;

int main()
{
    try
    {
        wymierna test(3,4);
        cout << test << endl;
        wymierna test2(31*17*1024,31*17*2048);
        cout << test2 << endl;
        wymierna test3(5);
        cout << "Dodawanie" << endl;
        cout << test2+test << endl;
        cout << "Odejmowanie" << endl;
        cout << test2 - test << endl;
        cout << "Dzielenie" << endl;
        cout << test2/test << endl;
        cout << "Mnozenie" << endl;
        test3 = test2 * test;
        cout << test3 << endl;
        cout << "Operator - i !" << endl;
        cout << -test3 << endl << !test3 << endl;
        cout << "Rzutowanie" << endl;
        double x = (double)test;
        cout << x << endl;
        cout << (int)test << endl;
        wymierna test5(7,9);
        cout << test5 << endl;
        wymierna test6(17,42);
        cout << test6 << endl;
        wymierna test8(51,-15);
        wymierna test9(42,-17);
        wymierna test10(54151,412);
        cout << test8 << endl;
        cout << test9 << endl;
        cout << test10 << endl;
        wymierna test11(42,1);
        cout << test11 << endl;
        wymierna test7(INT_MAX,4);
        cout << test7 << endl;
        cout << test7 * test7 << endl;
        wymierna as(3,0);
    }
    catch(wyjatek_wymierny &a)
    {
        cout << a.what() << endl;
    }
    return 0;
}
