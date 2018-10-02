#ifndef time_hpp
#define time_hpp
#include<iostream>
#include<ctime>
#include<vector>
#include<algorithm>

using namespace std;

class Data
{
    friend ostream & operator << (ostream &wy, const Data&);
    protected:
        int r, m, d;
        static int dniwmiesiacach[2][13];
        static int dniodpoczroku[2][13];
    public:
     //   ~Data();
        Data(int rok, int miesiac, int dzien);
        Data();
        Data(const Data&) = default;
        Data& operator = (const Data&) = default;

        int rok() const;
        int dzien() const;
        int miesiac() const;

        Data& operator += (const int);
        Data& operator -= (const int);
        Data& operator ++(int);
        Data& operator --(int);
        virtual int operator -(const Data&);
    private:
        bool poprawny()  const;
        int od0(const Data&) const;
    protected:
        static bool przestepny(int rok);
};

class DataGodz final : public Data
{
    static const int dlug_dnia = 24*60*60;
    friend int operator -(const DataGodz&, const DataGodz&);
    friend ostream & operator << (ostream &wy, const DataGodz&);
    protected:
        int h, mi, s;
    public:
        int hour() const;
        int minut() const;
        int sekund() const;

        DataGodz();
        DataGodz(int rok, int miesiac, int dzien, int hour, int minute, int sek);
        DataGodz(const DataGodz&) = default;
        DataGodz& operator = (const DataGodz&) = default;

        //operator odejmowania
        DataGodz& operator += (const int);
        DataGodz& operator -= (const int);
        DataGodz& operator ++(int);
        DataGodz& operator --(int);

        bool operator < (const DataGodz&);
        bool operator == (const DataGodz&);
    private:
        uint64_t total_time(const DataGodz&) const;
};

int operator -(const DataGodz&, const DataGodz&);

class Wydarzenie
{
    public:
        DataGodz czas;
        string nazwa;
};

#endif // time_hpp

