#ifndef punkt_hpp
#define punkt_hpp
#include"wektor.hpp"

class punkt
{
    public:
        const double x = 0, y = 0;
        punkt (double p, double d);
        punkt() = default;
        punkt(const punkt &);
        punkt(const punkt &, const wektor &);
        void print_punkt();
        punkt& operator = (const punkt&) = delete;
};

#endif
