#include"time.hpp"

bool por_wyd(Wydarzenie &a, Wydarzenie &b)
{
    return a.czas < b.czas;
}


int main()
{
    try
    {
        Data t1(1516, 5, 6);
        cout << t1 << endl;
        t1 -= 4;
        cout << t1 << endl;
        t1-= 7;
        cout << t1 << endl;
        t1-=365;
        cout << t1 << endl;
        t1+=5;
        cout << t1 << endl;
        t1 += (366 + 365);
        cout << t1;
        Data t2(1410, 7, 15);
        cout << t1-t2 << endl;
        t2 += (t1-t2);
        cout << t2 << endl;
        t2++;
        cout << t2 << endl;
        t2--;
        t2--;
        cout << t2 << endl;


        DataGodz d1(2000, 4, 5, 12, 42, 58);
        cout << d1 << endl;
        d1++;
        d1++;
        d1 += 1440*60;
        cout << d1 << endl;
        d1 -= 1440*60;
        cout << d1 << endl;
        DataGodz d2(2001, 4, 5, 12, 42, 13);
        cout << (d2 - d1)/365 << endl;
        cout << (d2 == d1) << endl;
        cout << (d2 < d1) << endl;
        cout << (d1 < d2) << endl;

        vector<Wydarzenie> tab;
        Wydarzenie grunwald;
        grunwald.czas = DataGodz(1410, 7, 15, 12, 00, 02);
        grunwald.nazwa = "Bitwa pod Grunwaldem";
        tab.push_back(grunwald);
        Wydarzenie rzym;
        rzym.czas = DataGodz(476, 12, 31, 23, 59, 59);
        rzym.nazwa = "Upadek Cesarstawa Zachodniego";
        tab.push_back(rzym);
        Wydarzenie chwila_obecna;
        chwila_obecna.czas = DataGodz();
        chwila_obecna.nazwa = "Dzisiejsza data";
        tab.push_back(chwila_obecna);
        Wydarzenie potop;
        potop.czas = DataGodz(1655,7,1,3,32,1);
        potop.nazwa = "Potop szwedzki";
        tab.push_back(potop);
        sort(tab.begin(),tab.end(), por_wyd);
        for(Wydarzenie w : tab)
        {
            cout << w.czas << endl << w.nazwa << endl;
        }
        Data t5(-3, 17, 54);
    }
    catch(string &a)
    {
        cout << a <<endl;
    }
    return 0;
}
