#include"stos.hpp"

stos::~stos()
{
    pojemnosc = 0;
    ile = 0;
    delete[] tab;
}

stos::stos():stos(1)
{
}

stos::stos(int rozmiar)
{
    ile = 0;
    pojemnosc = rozmiar;
    tab = new string[rozmiar];
}



stos::stos(const stos& kopia)
{
    pojemnosc = kopia.pojemnosc;
    ile = kopia.ile;
    tab = new string[pojemnosc];
    for(int i = 0; i < ile; i++)
    {
        tab[i] = kopia.tab[i];
    }
}

stos::stos(initializer_list<string> lista)
{
    pojemnosc = lista.size();
    ile = 0;
    tab = new string[pojemnosc];
    for(string w : lista)
    {
        wloz(w);
    }
}

stos::stos(stos&& przepisz)
{
    pojemnosc = przepisz.pojemnosc;
    ile = przepisz.ile;
    tab = przepisz.tab;
    przepisz.pojemnosc = 0;
    przepisz.tab = nullptr;
}

stos& stos::operator= (const stos &kopia)
{
    if(this != &kopia)
    {
        delete[] tab;
        ile = kopia.ile;
        pojemnosc = kopia.pojemnosc;
        tab = new string[pojemnosc];
        for(int i = 0; i < ile; i++)
        {
            tab[i] = kopia.tab[i];
        }
    }
    return *this;
}


stos& stos::operator= (stos &&przepisz)
{
    if(this != &przepisz)
    {
        delete[] tab;
        ile = przepisz.ile;
        pojemnosc = przepisz.pojemnosc;
        tab = przepisz.tab;
        przepisz.pojemnosc = 0;
        przepisz.tab = nullptr;
    }
    return *this;
}



int stos::rozmiar()
{
    return ile;
}

void stos::wloz(string t)
{
    if(pojemnosc == ile) throw invalid_argument("STOS PRZEPELNIONY");
    tab[ile] = t;
    ile++;
    return;
}

string stos::sciagnij()
{
    if(ile == 0) throw invalid_argument("STOS PUSTY");
    string temp = tab[ile-1];
    ile--;
    return temp;
}

string stos::sprawdz()
{
    if(ile == 0)throw invalid_argument("STOS PUSTY");
    string temp = tab[ile-1];
    return temp;
}
