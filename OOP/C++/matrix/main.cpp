#include"mac.hpp"
using namespace obliczenia;

int main()
{
    try{
    Macierz test(5);
    cout << test;

    Macierz test2(10, 5);
    cout << test2;
    test*= 7;
    cout << test;
    Macierz test3(test);
    test3 *= 3;
    cout << test3;
    test *= test3;
    test.swap_columns(1,3);
    test.swap_rows(1,2);
    cout << test;
    test = test.Trans();
    cout << test;
    cout << endl;
    Macierz testowe(4);
    //cin >> testowe;
    cout << testowe;
    testowe.delete_single(2,2);
    cout << testowe;

    Macierz deta(4);
    cin >> deta;
    cout << deta;
    cout << det(deta) << endl;
    Macierz x =  odwr(deta);
    cout << x;
    cout << x * deta;
    return 0;
    }
    catch(ZerowyWymiar &a)
    {
        cout << a.nazwa;
    }
    catch(MnozenieW &a)
    {
        cout << a.nazwa << " " << a.x << " " << a.y;
    }
    catch(DodOdejWymiar &a)
    {
        cout << a.nazwa;
    }
    catch(ZlyIndex &a)
    {
        cout << a.nazwa << " " << a.index;
    }
    catch(NieKwadrat &a)
    {
        cout << a.nazwa;
    }
    catch(WyznacznikZero &a)
    {
        cout << a.nazwa;
    }
}
