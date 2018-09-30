#ifndef tab_hpp
#define tab_hpp

#include<iostream>
#include<list>

using namespace std;

class tab_bit
{
        typedef uint64_t slowo; // komorka w tablicy
        static const int rozmiarS = (sizeof(slowo)*8); // rozmiar slowa w bitach
        friend istream & operator >> (istream &we, tab_bit &tb);
        friend ostream & operator << (ostream &wy, const tab_bit &tb);
        friend class ref;
        class ref
        {
            private:
                int ile;
                slowo* adres;
            public:
                ref(int ind, slowo* tab);
                operator bool() const;
                ref& operator= (const bool b);
                ref& operator= (const ref& r);
                ~ref();
        }; // klasa pomocnicza do adresowania bitów
    protected:
        int dl; // liczba bitów
        slowo *tab; // tablica bitów
    public:
        explicit tab_bit (int rozm); // wyzerowana tablica bitow [0...rozm]
        explicit tab_bit (slowo tb); // tablica bitów [0...rozmiarSlowa]
        tab_bit(initializer_list<bool>);// zainicjalizowana wzorcem
        tab_bit (const tab_bit &tb); // konstruktor kopiujący
        tab_bit (tab_bit &&tb); // konstruktor przenoszący
        tab_bit & operator = (const tab_bit &tb); // przypisanie kopiujące
        tab_bit & operator = (tab_bit &&tb); // przypisanie przenoszące
        ~tab_bit (); // destruktor
    private:
       bool czytaj (int i) const; // metoda pomocnicza do odczytu bitu
        bool pisz (int i, bool b); // metoda pomocnicza do zapisu bitu
    public:
        bool operator[] (int i) const; // indeksowanie dla stałych tablic bitowych
        ref operator[] (int i); // indeksowanie dla zwykłych tablic bitowych
        inline int rozmiar () const; // rozmiar tablicy w bitach
    public:
        tab_bit  operator|(const tab_bit &tb);
        tab_bit & operator|=(const tab_bit &tb);
        tab_bit  operator&(const tab_bit &tb);
        tab_bit & operator&=(const tab_bit &tb);
        tab_bit  operator^(const tab_bit &tb);
        tab_bit & operator^=(const tab_bit &tb);
        tab_bit & operator!();
    // operatory bitowe: | i |=, & i &=, ^ i ^= oraz !
    public:
        friend istream & operator >> (istream &we, tab_bit &tb)
        {
            for(unsigned i = 0; i < tb.dl/rozmiarS+1; i++)
            {
                for(unsigned j = 0; j < rozmiarS; j++)
                {
                    int w;
                    we >> w;
                    tb[i*rozmiarS+j] = w;
                }
            }
            return we;
        }
        friend ostream & operator << (ostream &wy, const tab_bit &tb)
        {
            for(int i = 0; i < tb.dl/rozmiarS+1; i++)
            {
                for(int j = 0; j < rozmiarS && j < tb.dl; j++)
                    wy << tb[i*rozmiarS + j];
                //wy << endl;
            }
            return wy;
        }
    // zaprzyjaźnione operatory strumieniowe: << i >>
};



#endif // tab_hpp
