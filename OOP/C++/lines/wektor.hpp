#ifndef wektor_hpp
#define wektor_hpp
#include<cmath>
#include<cstdlib>
#include<iostream>

using namespace std;
class wektor
{
    public:
        const double dx = 0, dy = 0;
        wektor (double a, double b);
        wektor() = default;
        wektor(const wektor &);
        void print_wektor();
        wektor& operator = (const wektor&) = delete;
};

wektor zloz(const wektor& a, const wektor&b);

#endif
