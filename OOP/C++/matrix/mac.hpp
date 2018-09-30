#ifndef mac_hpp
#define mac_hpp
#include<iostream>

using namespace std;

namespace obliczenia
{

    class BladMacierzy : public exception
    {
        public:
            string nazwa;
            string what()
            {
                return nazwa;
            }
    };
    class ZerowyWymiar : public BladMacierzy
    {
        public:
            ZerowyWymiar()
            {
                nazwa = "ZerowyWymiar";
            }
    };
    class BladArytm : public BladMacierzy{};
    class MnozenieW : public BladArytm
    {
        public:
            int x;
            int y;
            MnozenieW(int a, int b)
            {
                nazwa = "Blad mnozenia macierzy";
                x = a;
                y = b;
            }
    };

    class DodOdejWymiar:public BladArytm
    {
        public:
            DodOdejWymiar()
            {
                nazwa = "Wymiary nie zgadzaja sie przy +/-";
            }
    };

    class BladElem : public BladMacierzy{};
    class ZlyIndex : public BladElem
    {
        public:
            int index;
            ZlyIndex(int x)
            {
                index = x;
                nazwa = "Zly index x";
            }
    };

    class NieKwadrat : public BladMacierzy
    {
    public:
        NieKwadrat()
        {
            nazwa = "Nie jest to kwadratowa macierz";
        }
    };
    class WyznacznikZero : public BladMacierzy
    {
        public:
            WyznacznikZero()
            {
                nazwa = "Wyznacznik = 0, nie ma macierzy odwr";
            }
    };

    class Macierz
    {
        private:
            int height;
            int width;
            double** tab;

        public:
            Macierz(int) throw(ZerowyWymiar);
            Macierz(int,int) throw(ZerowyWymiar);
            Macierz(const Macierz&);
            Macierz(Macierz&&);
            Macierz& operator = (const Macierz&);
            Macierz& operator = (Macierz&&);
            ~Macierz();

            int getHeight() const;
            int getWidth() const;

        public:
            friend Macierz operator* (const Macierz &x, const double y);
            Macierz & operator *= (const double);
            friend Macierz operator+ (const Macierz &x, const Macierz &y) throw(DodOdejWymiar);
            Macierz & operator+= (const Macierz &y) throw(DodOdejWymiar);

            friend Macierz operator- (const Macierz &x, const Macierz &y) throw(DodOdejWymiar);
            Macierz & operator-= (const Macierz &y) throw(DodOdejWymiar);

            friend Macierz operator* (const Macierz &x, const Macierz &y) throw(MnozenieW);
            Macierz & operator*= (const Macierz &y) throw(MnozenieW);

            Macierz & Trans();

            void swap_rows(int,int) throw(ZlyIndex);
            void swap_columns(int,int) throw(ZlyIndex);
            void multiple_row(int row,double scalar) throw(ZlyIndex);
            void multiple_column(int row,double scalar) throw(ZlyIndex);
            void add_to_row(int target, int ind, double scalar) throw(ZlyIndex);
            void add_to_column(int target, int ind, double scalar) throw(ZlyIndex);

            Macierz& delete_single(int row, int column);

        public:
            friend istream& operator>> (istream &we, Macierz &x);
            friend ostream& operator<< (ostream &wy, const Macierz &x);

            friend double det(Macierz &x) throw(NieKwadrat);
            friend Macierz odwr(Macierz &x) throw(NieKwadrat, WyznacznikZero);

    };
}
#endif // mac_hpp


