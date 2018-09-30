#include"tab.hpp"

tab_bit::ref::~ref()
{
    adres = nullptr;
    ile = 0;
}

tab_bit::~tab_bit()
{
    dl = 0;
    delete[] tab;
}

tab_bit::tab_bit(int rozm): dl(rozm)
{
    tab = new slowo[dl/rozmiarS+1];
    for(unsigned i = 0; i < dl/rozmiarS+1; i++)
    {
        tab[i] = 0;
    }
}

tab_bit::tab_bit(slowo tb)
{
    dl = rozmiarS;
    tab = new slowo[1];
    tab[0] = tb;
}

tab_bit::tab_bit(initializer_list<bool> l)
{
    dl = l.size();
    tab = new slowo[dl/rozmiarS+2];
    int i = 0;
    for(auto w : l)
    {
        ref z(i,tab);
        z = w;
        i++;
    }
}

tab_bit::tab_bit(const tab_bit &tb)
{
    dl = tb.dl;
    tab = new slowo[dl/rozmiarS+1];
    for(unsigned i = 0; i < dl/rozmiarS+1;i++)
    {
        tab[i] = tb.tab[i];
    }
}

tab_bit:: tab_bit (tab_bit &&tb)
{
    dl = tb.dl;
    tab = tb.tab;
    tb.tab = nullptr;
}

tab_bit& tab_bit :: operator = (const tab_bit &tb)
{
    if(this != &tb)
    {
        delete[] tab;
        dl = tb.dl;
        tab = new slowo[dl/rozmiarS+1];
        for(unsigned i = 0; i < dl/rozmiarS+1;i++)
        {
            tab[i] = tb.tab[i];
        }
    }
    return *this;
}

tab_bit& tab_bit :: operator = (tab_bit &&tb)
{
    if(this != &tb)
    {
        delete[] tab;
        dl = tb.dl;
        tab = tb.tab;
        tb.tab = nullptr;
    }
    return *this;
}

tab_bit& tab_bit :: operator|= (const tab_bit &tb)
{
    if(this->dl != tb.dl) throw string("ZLE WYMIARY");
    for(int i = 0; i < dl/rozmiarS+1;i++)
    {
        this->tab[i] = this->tab[i] | tb.tab[i];
    }
    return *this;
}

tab_bit& tab_bit :: operator^= (const tab_bit &tb)
{
    if(this->dl != tb.dl) throw string("ZLE WYMIARY");
    for(int i = 0; i < dl/rozmiarS+1;i++)
    {
        this->tab[i] = this->tab[i] ^ tb.tab[i];
    }
    return *this;
}
tab_bit& tab_bit :: operator&= (const tab_bit &tb)
{
    if(this->dl != tb.dl) throw string("ZLE WYMIARY");
    for(int i = 0; i < dl/rozmiarS+1;i++)
    {
        this->tab[i] = this->tab[i] & tb.tab[i];
    }
    return *this;
}

tab_bit tab_bit :: operator| (const tab_bit &tb)
{
    tab_bit temp(*this);
    temp |= tb;
    return temp;
}

tab_bit tab_bit :: operator^ (const tab_bit &tb)
{
    tab_bit temp(*this);
    temp ^= tb;
    return temp;
}
tab_bit tab_bit :: operator& (const tab_bit &tb)
{
    tab_bit temp(*this);
    temp &= tb;
    return temp;
}

tab_bit& tab_bit::operator!()
{
    for(int i = 0; i < dl/rozmiarS+1;i++)
    {
        this->tab[i] = ~(this->tab[i]);
    }
    return *this;
}


inline int tab_bit :: rozmiar() const
{
    return dl;
}


bool tab_bit :: operator[](int i) const
{
    return tab_bit::ref(i,tab);
}

/*
bool tab_bit :: czytaj(int i) const
{
    ref help(i,tab);
    return help;
}

bool tab_bit :: pisz(int i, bool b)
{
    ref help(i,tab);
    help = b;
    return help;
}*/

tab_bit :: ref ::ref(int ind, slowo* tab)
{
    ile = ind%rozmiarS;
    adres = tab+(ind/rozmiarS);
}


tab_bit::ref tab_bit :: operator[](int i)
{
    return ref(i,tab);
}

tab_bit::ref& tab_bit::ref::operator=(const bool b)
{
    if(b) *adres |= (slowo)1<<ile;
    else *adres &= ~((slowo)1 << ile);
    return *this;
}

tab_bit::ref& tab_bit::ref::operator=(const ref& r)
{

    bool temp = r;
    *this = temp;
    return *this;
}

tab_bit::ref::operator bool()const
{
    return (*adres>>ile)&1;
}
