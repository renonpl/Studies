#include"wektor.hpp"

wektor::wektor(double a, double b) : dx(a), dy(b)
{
}



wektor::wektor(const wektor &a) : dx(a.dx), dy(a.dy)
{
}


wektor zloz(const wektor& a, const wektor& b)
{
    wektor result((a.dx+b.dx),(a.dy+b.dy));
    return result;
}

void wektor::print_wektor()
{
    cout << "x = " << dx << " y = " << dy << endl;
}
