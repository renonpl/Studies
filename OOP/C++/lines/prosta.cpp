#include"prosta.hpp"


void prosta::norm()
{
    double temp = (this->a * this->a) + (this->b * this->b);
    temp = sqrt(temp);
    this->a = a/temp;
    this->b = b/temp;
    this->c = c/temp;
}

prosta::prosta() = default;


prosta::prosta(double a, double b, double c): a(a), b(b), c(c)
{
    if(a == 0 && b == 0) throw invalid_argument("PROSTA NIE MOZE BYC POSTACI 0X 0Y \n");
    norm();
}

prosta::prosta(const punkt & p,const punkt & d)
{
    if(p.x == d.x && p.y == d.y) throw invalid_argument("NIE DA SIE STWORZYC JEDNOZNACZNIE TAKIEJ PROSTEJ \n");
    a = d.y - p.y;
    b = p.x - d.x;
    c = d.x * p.y - p.x * d.y;
    norm();
}

prosta::prosta(const wektor &w)
{
    if(w.dx == 0 && w.dy == 0) throw invalid_argument("WEKTOR 0 0 NIE JEST PROSTOPADLY DO ZADNEJ PROSTEJ \n");
    a = w.dx;
    b = w.dy;
    c = - (a*a)-(b*b);
    norm();
}

prosta::prosta(prosta &p, const wektor &w)
{
    a = p.getA();
    b = p.getB();
    c = p.getC() - p.getA()*w.dx - p.getB()*w.dy;
    norm();
}

double prosta::getA()
{
    return a;
}

double prosta::getB()
{
    return b;
}

double prosta::getC()
{
    return c;
}


bool prosta::is_on(const punkt & p)
{
    if(abs(a*p.x + b*p.y + c) < eps) return true;
    return false;
}

bool prosta::is_perp(const wektor & w)
{
    if(abs((w.dx * b) - (a * w.dy))  < eps) return true;
    return false;
}

bool prosta::is_par(const wektor & w)
{
    if(abs((b * w.dy) + a * w.dx) < eps) return true;
    return false;
}

bool is_perp(prosta& a, prosta& b)
{
    if(abs(a.getA() * a.getB() + b.getB() * b.getA())  < eps) return true;
    return false;
}
bool is_par(prosta& a, prosta& b)
{
    if(abs(a.getA() * a.getB() - (b.getB() * b.getA())) < eps) return true;
    return false;
}

punkt crossing(prosta &a, prosta& b)
{
    if(is_par(a,b) == true) throw invalid_argument("TO SA PROSTE ROWNOLEGLE \n");
    double d = a.getA()/a.getB() + b.getB()/b.getA();
    double x = (a.getB()*b.getC() - b.getB() * a.getC())/d;
    double y = (a.getA()*b.getC() - b.getA() * a.getC())/d;
    punkt result(x,y);
    return result;
}
