#include"wym.hpp"
#include<vector>
#include<cmath>

namespace obliczenia
{
    wymierna::wymierna() : wymierna(1,1)
    {
    }
    wymierna::wymierna(int a) : wymierna(a,1)
    {
    }
    wymierna::wymierna(int a, int b) throw(blad_konstr)
    {
        if(b == 0 || b == INT_MIN) throw blad_konstr();
        licz = a;
        mian = b;
        if(mian < 0)
        {
            mian *= -1;
            licz *= -1;
        }
        this->skroc();
    }

    void wymierna::skroc()
    {
        int c;
        if(licz < 0) c = eukli(-1*licz, mian);
        else c = eukli(licz,mian);
        licz /= c;
        mian /= c;
        return;
    }

    int wymierna::eukli(int a, int b) const
    {
        if(b == 0) return a;
        return eukli(b, a%b);
    }

    int wymierna::getLicz() const
    {
        return licz;
    }

    int wymierna::getMian() const
    {
        return mian;
    }

    wymierna operator * (const wymierna& a, const wymierna& b) throw(blad_zakresu)
    {
        if(abs(INT_MAX/a.licz) < abs(b.licz) || INT_MAX/b.mian < a.mian) throw blad_zakresu();
        wymierna temp((a.licz * b.licz), (b.mian * a.mian));
        return temp;
    }

    wymierna operator / (const wymierna& a, const wymierna& b) throw(blad_zakresu, blad_przez_zero)
    {
        if(b.licz == 0) throw blad_przez_zero();
        return a * !b;
    }

    wymierna operator + (const wymierna& a, const wymierna& b) throw(blad_zakresu)
    {
        int licznik;
        int mianownik;
        int e = a.eukli(a.mian, b.mian);
        if(INT_MAX/a.mian*e < b.mian || INT_MAX/b.mian*e < abs(a.licz) || INT_MAX/a.mian*e < abs(b.licz)) throw blad_zakresu();
        mianownik = a.mian/e * b.mian;
        licznik = (b.mian/e*a.licz) + (a.mian/e*b.licz);
        wymierna temp(licznik,mianownik);
        return temp;
    }

    wymierna  operator - (const wymierna& a, const wymierna & b) throw(blad_zakresu)
    {
        return a + (- b);
    }

    wymierna operator ! (const wymierna& a) throw(blad_przez_zero, blad_zakresu)
    {
        if(a.licz == 0) throw blad_przez_zero();
        if(INT_MIN == a.licz) throw blad_zakresu();
        wymierna temp(a.mian, a.licz);
        return temp;
    }

    wymierna operator - (const wymierna& a) throw(blad_zakresu)
    {
        if(INT_MIN == a.licz) throw blad_zakresu();
        wymierna temp(-1*a.licz, a.mian);
        return temp;
    }


    ostream& operator<< (ostream &wyj, const wymierna &w)
    {
        vector<int>reszty;
        vector<int>wyniki;
        long long temp = w.licz;
        int a = temp/w.mian;
        temp -= a*w.mian;
        if(a == 0)
        {
            if(temp < 0)
            {
                wyj << "-0,";
            }
            else
            {
                wyj << "0,";
            }
        }
        else
        {
            if(temp == 0)
            {
                wyj << a;
                return wyj;
            }
            wyj << a << ",";
        }
        if(temp < 0) temp *= -1;
        reszty.push_back(temp);

        temp *= 10;
        while(temp != 0)
        {
            a = temp/w.mian;
            temp -= a *w.mian;
          //  cout << "Temp = " << temp << endl;
            for(unsigned i = 0; i < reszty.size();i++)
            {
                if(reszty[i] == temp)
                {
                    wyniki.push_back(a);
                    for(unsigned j = 0; j < wyniki.size(); j++)
                    {
                        if(j == i)
                        {
                            wyj << "[";
                        }
                        wyj << wyniki[j];
                    }
                    wyj << "]";
                    return wyj;
                }
            }
            wyniki.push_back(a);
            reszty.push_back(temp);
            temp *= 10;
        }
        for(unsigned i = 0; i < wyniki.size();i++)
        {
            wyj << wyniki[i];
        }
        return wyj;
    }

    istream& operator>> (istream &we, wymierna &w)
    {
        we >> w.licz >> w.mian;
        w.skroc();
        return we;
    }

    wymierna::operator double() const
    {
        return 1.0*licz/mian;
    }

    wymierna::operator int() const
    {
        return licz/mian;
    }
}
