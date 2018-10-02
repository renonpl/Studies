#ifndef prosta_hpp
#define prosta_hpp
#include"punkt.hpp"
#define eps 0.0001


class prosta
{
    private:
        double a, b,c;
        void norm();

    public:
        prosta();
        prosta(double a, double b, double c);
        prosta(const punkt &,const punkt &);
        prosta(const wektor &);
        prosta(prosta &, const wektor &);
        bool is_perp(const wektor &);
        bool is_par(const wektor &);
        bool is_on(const punkt &);
        double getA();
        double getB();
        double getC();
        prosta (const prosta&) = delete;
        prosta& operator = (const prosta&) = delete;
};

bool is_perp(prosta &, prosta &);
bool is_par(prosta &, prosta &);
punkt crossing(prosta &, prosta &);


#endif

