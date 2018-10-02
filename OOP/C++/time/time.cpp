#include"time.hpp"
Data::Data()
{
    time_t t = time(0);
    tm* teraz = localtime(&t);
    r = teraz->tm_year+1900;
    m = teraz->tm_mon+1;
    d = teraz->tm_mday;
}

Data::Data(int rok, int miesiac, int dzien): r(rok), m(miesiac), d(dzien)
{
    if(!poprawny()) throw string("Zle dane!");
}

bool Data:: przestepny(int rok)
{
    return (rok % 4 == 0 && rok % 100 != 0) || rok % 400 == 0;
}

bool Data:: poprawny() const
{
    int index = przestepny(r);
    return r >= 1 && m >= 1 && m <= 12 && d > 0 && d <= dniwmiesiacach[index][m];
}

int Data::od0(const Data& t) const
{
    int temp = t.dniodpoczroku[t.przestepny(t.r)][t.m];
    temp += t.d;
    temp = temp + 365 * t.r + t.r/4 - t.r/100 + t.r/400;
    return temp;
}

int Data::operator - (const Data& t)
{
    return od0(*this) - od0(t);
}


Data& Data::operator += (const int t)
{
    int dokonca = dniwmiesiacach[przestepny(this->r)][this->m];
    if(t + this->d > dokonca)
    {
        int ile = this->d;
        if(this->m == 12)
        {
            this->r++;
            this->m = 1;
        }
        else
        {
            this->m++;
        }
        this->d = 0;
        return *this += (t-(dokonca - ile));
    }
    this->d += t;
    return *this;
}

Data& Data::operator -= (const int t)
{
    if(t >= this->d)
    {
        int ile = this->d;
        if(this->m == 1)
        {
            this->r--;
            this->m = 12;
        }
        else
        {
            this->m--;
        }
        this->d = this->dniwmiesiacach[przestepny(this->r)][this->m];
        return *this -= (t-ile);
    }
    this->d -= t;
    return *this;
}
Data& Data::operator ++ (int)
{
    return *this += 1;
}
Data& Data::operator -- (int)
{
    return *this -= 1;
}

int Data::rok() const
{
    return r;
}
int Data::miesiac() const
{
    return m;
}
int Data::dzien() const
{
    return d;
}

int Data::dniwmiesiacach[2][13] =
{
    {0,31,28,31,30,31,30,31,31,30,31,30,31}, // lata zwykłe
    {0,31,29,31,30,31,30,31,31,30,31,30,31} // lata przestępne
};

int Data::dniodpoczroku[2][13] = {
{0,31,59,90,120,151,181,212,243,273,304,334,365}, // lata zwykłe
{0,31,60,91,121,152,182,213,244,274,305,335,366} // lata przestępne
};


ostream& operator << (ostream& wy, const Data& t)
{
    wy << t.r << "  " << t.m << "  " <<  t.d;
    return wy;
}


ostream& operator << (ostream& wy, const DataGodz& t)
{
    wy << t.r << "  " << t.m << "  " <<  t.d << "  " << t.h << "  " << t.mi << " " << t.s;
    return wy;
}





DataGodz::DataGodz()
{
    time_t t = time(NULL);
    tm* teraz = localtime(&t);
    r = teraz->tm_year+1900;
    m = teraz->tm_mon+1;
    d = teraz->tm_mday;
    h = teraz->tm_hour;
    mi = teraz->tm_min;
    s = teraz->tm_sec;
}

DataGodz::DataGodz(int rok, int miesiac, int dzien, int hour, int minute, int sek) : Data(rok,miesiac,dzien)
{

    h = hour;
    mi = minute;
    s = sek;
    int index = przestepny(rok);
    if(h < 0 || h > 23 || mi < 0 || mi > 59 || s < 0 || s > 59) throw string("Zle dane");
}

uint64_t DataGodz::total_time(const DataGodz& t) const
{
    uint64_t temp = t.dniodpoczroku[t.przestepny(t.r)][t.m];
    temp += t.d;
    temp = temp + 365 * t.r +t.r/4 - t.r/100 + t.r/400;
    temp *= dlug_dnia;
    temp = temp + t.h * 24 * 60 + t.mi * 60 + t.s;
    return temp;
}

DataGodz& DataGodz::operator += (const int t)
{
    (Data)*this = Data::operator+=(t/dlug_dnia);
    int rest = t % dlug_dnia;

    rest = this->s + rest;
    this->s = rest % 60;
    rest /= 60  ;

    rest = this->mi + rest;
    this->mi = rest % 60;
    rest /= 60;
    rest = this->h + rest;
    this->h = rest % 24;
    rest /= 24;
    if(rest > 0)     (Data)*this = Data::operator+=(1);
    return *this;
}

DataGodz& DataGodz::operator -= (const int t)
{
    int days = t/dlug_dnia;
    int rest = t % dlug_dnia;
    rest = dlug_dnia - rest;
    days++;
    (Data)*this = Data::operator-=(days);
    *this += rest;
    return *this;
}

DataGodz& DataGodz::operator ++ (int)
{
    return *this += 1;
}

DataGodz& DataGodz::operator -- (int)
{
    return *this -= 1;
}

bool DataGodz::operator==(const DataGodz& t)
{
    return total_time(*this) == total_time(t);
}

bool DataGodz::operator < (const DataGodz& t)
{
    return total_time(*this) < total_time(t);
}

int DataGodz::hour() const
{
    return h;
}
int DataGodz::minut() const
{
    return mi;
}
int DataGodz::sekund() const
{
    return s;
}

int operator - (const DataGodz& a, const DataGodz& b)
{
    return a.total_time(a) - b.total_time(b);
}
