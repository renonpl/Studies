#include"tab.hpp"

int main()

{
    try
    {
        tab_bit x(46);
        x[1] = true;
        x[4] = x[7] = x[1];
        x[1] = false;
        cout << "JA TU WYPISUJE" << endl;
        cout << x[1];
        cout << x[4] << x[7] << x[5];
        cout << x << endl;
        tab_bit t(46);         // tablica 46-bitowa (zainicjalizowana zerami)
       // tab_bit q(45UL);      // tablica 64-bitowa (sizeof(uint64_t)*8)
        tab_bit u(45UL);
        tab_bit v(t);          // tablica 46-bitowa (skopiowana z t)
        tab_bit s({1,0,0,0,1,1,1,1});
        cout << s << endl;
        tab_bit w(tab_bit({1, 0, 1, 1, 0, 0, 0, 1})); // tablica 8-bitowa (przeniesiona)
        v[0] = 1;              // ustawienie bitu 0-go bitu na 1
        t[45] = true;          // ustawienie bitu 45-go bitu na 1
        bool b = v[1];         // odczytanie bitu 1-go
        u[45] = u[46] = u[63]; // przepisanie bitu 63-go do bitow 45-go i 46-go
        cout<<t<<endl;         // wysietlenie zawartości tablicy bitów na ekranie
        cout << b << endl;
        tab_bit l(46);
        l |= x;
       // l ^= l;
        x[45] = true;
        x[13] = true;
        cout << x << endl;
        cout << l << endl;
        l ^= x;
        cout << l << endl;
        //cin >> l;
        //cout << l;
        u &= x;
    }
    catch(string &a)
    {
        cerr << a;
    }
    return 0;
}

