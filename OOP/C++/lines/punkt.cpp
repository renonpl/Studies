#include"punkt.hpp"
#include<iostream>
using namespace std;

punkt::punkt(double a, double b) : x(a), y(b)
{
}


punkt::punkt(const punkt &a) : x(a.x), y(a.y)
{
}

punkt::punkt(const punkt &p, const wektor &w) : x(p.x + w.dx), y(p.y + w.dy)
{
}

void punkt::print_punkt()
{
    cout << "x = " << x << " y = " << y << endl;
}
