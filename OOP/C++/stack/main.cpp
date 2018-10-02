#include"stos.hpp"
#include<vector>

int main()
{

    stos* p = new stos({"haha", "pgae", "top"});
    cout <<(string) p->sciagnij() << endl;

    stos* z = new stos(*p);
    cout <<(string) z->sciagnij() << endl;
    cout << (int)p->rozmiar() << endl;
    stos x = *z;
    cout << (string) z->sprawdz() << endl;
    cout << (int)z->rozmiar() << endl;
    vector<stos> w;
    w.push_back(stos({"hoho","42"}));
    cout <<(int) w[0].rozmiar() << endl;
    cout <<(string) w[0].sciagnij() << endl;


    delete p;
    delete z;
    stos* s = new stos(10);

    try
    {
        while(true)
        {
            char d = 0;
            cout << "1.Dodaj stringa  2.Sciagnij stringa 3.Sprawdz stringa" << endl << "4.Sprawdz rozmiar 5.Wypisz caly stos" << endl;
                while(d < '1' || d > '5') cin >> d;
                switch(d)
                {
                    case '1':
                    {
                        cout << "podaj stringa" << endl;
                        string temp;
                        cin >> temp;
                        s->wloz((string)temp);

                        break;
                    }
                    case '2':
                        cout  << (string)s->sciagnij() << endl;
                        break;
                    case '3':
                        cout << (string)s->sprawdz() << endl;
                        break;
                    case '4':
                        cout << (int)s->rozmiar() << endl;
                        break;
                    case '5':
                        while(s->rozmiar() != 0) cout << (string)s->sciagnij() << endl;
                        break;
                }
            char c = 0;
            cout << "Kontynuowac? 1.Tak 2.Nie" << endl;
            while(c < '1' || c > '2') cin >> c;
            if(c == '2') break;
        }
    }
    catch(invalid_argument &a)
    {
        cout << a.what() << endl;
    }
    delete s;
    return 0;
}
