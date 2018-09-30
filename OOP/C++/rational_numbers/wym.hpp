#ifndef wym_hpp
#define wym_hpp
#include<iostream>
#include<climits>
using namespace std;

namespace obliczenia
{
    class wyjatek_wymierny : public exception
    {
        public:
            string nazwa;
            wyjatek_wymierny()
            {
                nazwa = "Wyjatek ogolny";
            }
            string what()
            {
                return nazwa;
            }
    };
    class blad_konstr : public wyjatek_wymierny
    {
        public:
            blad_konstr()
            {
                nazwa = "Niewlasciwe paratmertry konstruktora";
            }
    };
    class blad_arytm : public wyjatek_wymierny
    {
        public:
            blad_arytm()
            {
                nazwa = "Blad w dzialaniu arytm";
            }
    };
    class blad_zakresu : public blad_arytm
    {
        public:
            blad_zakresu()
            {
                nazwa = "Przekroczenie zakresu";
            }
    };
    class blad_przez_zero : public blad_arytm
    {
        public:
            blad_przez_zero()
            {
                nazwa = "Wystepuje dzielenie przez zero";
            }
    };


    class wymierna
    {
        private:
            int licz, mian;
            void skroc();
            int eukli(int,int) const;
        public:
            wymierna();
            wymierna(int,int) throw(blad_konstr);
            wymierna(int);
            wymierna(const wymierna&) = default;
            wymierna& operator = (const wymierna&) = default;
            //            wymierna(wymierna&&) = default;
            //wymierna& operator = (wymierna&&) = default;
            int getLicz() const;
            int getMian() const;
            friend wymierna operator + (const wymierna&, const wymierna&) throw(blad_zakresu);
            friend wymierna operator * (const wymierna&, const wymierna&) throw(blad_zakresu);
            friend wymierna operator / (const wymierna&, const wymierna&) throw(blad_przez_zero, blad_zakresu);
            friend wymierna operator - (const wymierna&, const wymierna&) throw(blad_zakresu);
            friend wymierna operator ! (const wymierna&) throw(blad_przez_zero,blad_zakresu);
            friend wymierna operator - (const wymierna&) throw(blad_zakresu);

            friend ostream& operator<< (ostream &wyj, const wymierna &w);
            friend istream& operator>> (istream &we, wymierna &w);


            explicit  operator int() const;
            explicit operator double() const;
    };
}

#endif // wym_hpp
