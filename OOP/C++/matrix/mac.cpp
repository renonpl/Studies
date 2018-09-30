#include"mac.hpp"

namespace obliczenia
{
    Macierz::Macierz(int a) throw(ZerowyWymiar):Macierz(a,a)
    {
        //if(a == 0)  throw ZerowyWymiar();
        for(int i = 0; i < width; i++)
        {
            tab[i][i] = 1;
        }
    }

    Macierz::Macierz(int m ,int n) throw(ZerowyWymiar)
    {
        if(m <= 0 || n <= 0)  throw ZerowyWymiar();
        this->width = n;
        this->height = m;
        tab = new double*[height];
        for(int i = 0; i < height; i++)
        {
            tab[i] = new double[width];
        }
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                tab[i][j] = 0;
            }
        }
    }
    Macierz::Macierz(const Macierz& t)
    {
        this->width = t.width;
        this->height = t.height;
        tab = new double*[height];
        for(int i = 0; i < height; i++)
        {
            tab[i] = new double[width];
        }
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                this->tab[i][j] = t.tab[i][j];
            }
        }
    }

    Macierz::Macierz(Macierz&& t)
    {
        this->tab = t.tab;
        this->width = t.width;
        this->height = t.height;
        t.tab = nullptr;
        t.height = 0;
        t.width = 0;
    }

    Macierz& Macierz:: operator = (const Macierz& t)
    {
        if(this == &t) return *this;
        this->~Macierz();
        this->width = t.width;
        this->height = t.height;
        tab = new double*[height];
        for(int i = 0; i < height; i++)
        {
            tab[i] = new double[width];
        }
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                this->tab[i][j] = t.tab[i][j];
            }
        }
        return *this;

    }
    Macierz& Macierz:: operator = (Macierz&& t)
    {
        if(this == &t) return *this;
        this->~Macierz();
        this->tab = t.tab;
        this->width = t.width;
        this->height = t.height;
        for(int i = 0; i < height; i++)
        {
            t.tab[i] = nullptr;
        }
        t.tab = nullptr;
        t.width = 0;
        t.height = 0;

        return *this;
    }

    Macierz::~Macierz()
    {
        for(int i = 0 ; i < height; i++)
        {
            delete[] tab[i];
        }
        delete[] tab;
    }

    int Macierz:: getHeight() const
    {
        return height;
    }
    int Macierz:: getWidth() const
    {
        return width;
    }

    Macierz& Macierz:: operator *= (const double skal)
    {
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                this->tab[i][j] *= skal;
            }
        }
        return *this;
    }

    Macierz operator* (const Macierz &x, const double y)
    {
        Macierz temp(x);
        return temp *= y;
    }



    Macierz& Macierz:: operator += (const Macierz& y) throw(DodOdejWymiar)
    {
        if(this->width != y.width || this->height != y.height) throw DodOdejWymiar();
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                this->tab[i][j] += y.tab[i][j];
            }
        }
        return *this;
    }

    Macierz operator+ (const Macierz &x, const Macierz &y) throw(DodOdejWymiar)
    {
        Macierz temp(x);
        return temp += y;
    }

    Macierz& Macierz:: operator -= (const Macierz& y) throw(DodOdejWymiar)
    {
        if(this->width != y.width || this->height != y.height) throw DodOdejWymiar();
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                this->tab[i][j] -= y.tab[i][j];
            }
        }
        return *this;
    }

    Macierz operator- (const Macierz &x, const Macierz &y) throw(DodOdejWymiar)
    {
        Macierz temp(x);
        return temp -= y;
    }


    Macierz& Macierz:: operator *= (const Macierz& y) throw(MnozenieW)
    {
        if(this->width != y.height) throw MnozenieW(this->width,y.height);
        Macierz ex(this->height, y.width);
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                double temp = 0;
                for(int k = 0; k < width; k++)
                {
                    temp += tab[i][k] * y.tab[k][j];
                }
                ex.tab[i][j] = temp;
            }
        }
        *this = (Macierz&) ex;
        return *this;
    }

    Macierz operator* (const Macierz &x, const Macierz &y) throw(MnozenieW)
    {
        Macierz temp(x);
        temp *= y;
        return temp;
    }


    Macierz& Macierz::Trans()
    {
        Macierz temp(width,height);
        for(int i = 0; i < temp.height; i++)
        {
            for(int j = 0; j < temp.width; j++)
            {
                temp.tab[i][j] = this->tab[j][i];
            }
        }
        *this = (Macierz&)temp;
        return *this;
    }


    void Macierz:: swap_rows(int x,int y) throw(ZlyIndex)
    {
        if(x >= this->height || y >= this->height) throw ZlyIndex(max(x,y));
        double* temp = tab[x];
        tab[x] = tab[y];
        tab[y] = temp;
        return;
    }
    void Macierz::swap_columns(int x,int y) throw(ZlyIndex)
    {
        if(x >= this->width || y >= this->width) throw ZlyIndex(max(x,y));
        for(int i = 0; i < height; i++)
        {
            double temp = tab[i][x];
            tab[i][x] = tab[i][y];
            tab[i][y] = temp;
        }
        return;
    }
    void Macierz::multiple_row(int row,double scalar) throw(ZlyIndex)
    {
        if(row >= this->height) throw ZlyIndex(row);
        for(int i = 0; i < width; i++)
        {
            tab[row][i] *= scalar;
        }
        return;
    }

    void Macierz::multiple_column(int column,double scalar) throw(ZlyIndex)
    {
            if(column >= this->width) throw ZlyIndex(column);
        for(int i = 0; i < height; i++)
        {
            tab[i][column] *= scalar;
        }
        return;
    }
    void Macierz::add_to_row(int target, int ind, double scalar) throw(ZlyIndex)
    {
        if(target >= this->height || ind >= this->height) throw ZlyIndex(max(target,ind));
        for(int i = 0; i < width; i++)
        {
            tab[target][i] += scalar* tab[ind][i];
        }
        return;
    }
    void Macierz::add_to_column(int target, int ind, double scalar) throw(ZlyIndex)
    {
        if(target >= this->width || ind >= this->width) throw ZlyIndex(max(target,ind));
        for(int i = 0; i < height; i++)
        {
            tab[i][target] += scalar* tab[i][ind];
        }
        return;
    }


    istream& operator>> (istream &we, Macierz &x)
    {
        for(int i = 0; i < x.height; i++)
        {
            for(int j = 0; j < x.width; j++)
            {
                we >> x.tab[i][j];
            }
        }
        return we;
    }
    ostream& operator<< (ostream &wy, const Macierz &x)
    {
        for(int i = 0; i < x.height; i++)
        {
            for(int j = 0; j < x.width; j++)
            {
                wy << x.tab[i][j] << " ";
            }
            wy << endl;
        }
        return wy;
    }

    Macierz& Macierz::delete_single(int row, int column)
    {
        if(row >= this->height || column >= this->width) throw ZlyIndex(max(row,column));
        Macierz ex(height-1,width-1);
        int row_check = 0;
        int col_chek = 0;
       // cout << ex.getHeight() << endl;
        for(int i = 0; i < height; i++)
        {
            if(i == row)
            {
                row_check = 1;
                continue;
            }
            for(int j = 0; j < width; j++)
            {
                if(j == column)
                {
                    col_chek = 1;
                    continue;
                }
                ex.tab[i-row_check][j-col_chek] = this->tab[i][j];
            }
            col_chek = 0;
        }
        *this = (Macierz&)ex;
        return *this;
    }

    double det(Macierz &x) throw(NieKwadrat)
    {
        if(x.height != x.width) throw NieKwadrat();
        if(x.height == 2)
        {
            return x.tab[0][0] * x.tab[1][1] - x.tab[0][1] * x.tab[1][0];
        }
        double wyzn = 0;
        for(int i = 0; i < x.width; i++)
        {
            Macierz temp(x);
            temp.delete_single(0,i);
            if(i % 2 == 0)wyzn +=  x.tab[0][i] * det(temp);
            else wyzn -= x.tab[0][i] * det(temp);
        }
        return wyzn;
    }

    Macierz odwr(Macierz &x) throw(NieKwadrat, WyznacznikZero)
    {
        if(x.height != x.width) throw NieKwadrat();
        double wyzn = det(x);
        if(0 == wyzn) throw WyznacznikZero();
        Macierz dop(x);
        for(int i = 0; i < dop.height; i++)
        {
            for(int j = 0; j < dop.width; j++)
            {
                Macierz temp(x);
                if((i + j)%2 == 0)
                {
                    temp.delete_single(i,j);
                    dop.tab[i][j] = det(temp);
                }
                else
                {
                    temp.delete_single(i,j);
                    dop.tab[i][j] = -1 * det(temp);
                }
            }
        }
        dop = dop.Trans();
        dop *= (1.0/wyzn);
  //              cout << dop << endl;
        return dop;
    }
}
