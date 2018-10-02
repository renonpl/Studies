#ifndef stos_hpp
#define stos_hpp

#include<iostream>
#include<list>
using namespace std;

class stos
{
    private:
        string* tab;
        int ile;
        int pojemnosc;
    public:
         ~stos();

        stos();
        stos(int);
        stos(const stos&);
        stos(initializer_list<string>);
        stos(stos&&);

        stos& operator= (const stos&);
        stos& operator= (stos&&);

        void wloz(string);
        string sciagnij();
        string sprawdz();
        int rozmiar();
};


#endif // stos_hpp
