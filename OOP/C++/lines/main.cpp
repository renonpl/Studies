#include"prosta.hpp"

int main()
{
    try
        {
        wektor test(3,4);
        test.print_wektor();
        wektor test2(test);
        test2.print_wektor();
        wektor test3;
        test3.print_wektor();
        wektor test6(zloz(test,test2));
        test6.print_wektor();
        wektor test5(-41, 412);
//        test5 = test;
//        wektor test6(zloz(test,test2));
        cout << endl;


        punkt p;
        p.print_punkt();
        punkt p2(42, 24);
        p2.print_punkt();
        punkt p3(p2);
        p3.print_punkt();
        punkt p4(p2, test);
        p4.print_punkt();
        cout << endl;

        prosta pr;
        cout << pr.getA() << " " << pr.getB() << " " << pr.getC() << endl;
        prosta pr2(3, 3, 1);
        cout << pr2.getA() << " " << pr2.getB() << " " << pr2.getC() << endl;
        prosta pr3(p2, p4);
        cout << pr3.getA() << " " << pr3.getB() << " " << pr3.getC() << endl;
        prosta pr4(test);
        cout << pr4.getA() << " " << pr4.getB() << " " << pr4.getC() << endl;
        prosta pr5(pr4, test);
        cout << pr5.getA() << " " << pr5.getB() << " " << pr5.getC() << endl;
        cout << pr5.is_par(test5) << endl;
        cout << pr5.is_perp(test5) << endl;
        wektor temp(4, 3);
        cout << pr5.is_par(temp) << endl;
        cout << pr5.is_perp(temp)<< endl;
        cout << pr5.is_on(p2) << endl;
        punkt p5(6,8);
        cout << pr5.is_on(p5) << endl;
        wektor temp7(6,8);
        cout << pr5.is_perp(temp7) << endl;
        wektor temp8(-8, 6);
        cout << pr5.is_par(temp8) << endl;
        crossing(pr5,pr2).print_punkt();

        prosta z(2,3,5);
        prosta z1(-3,2,7);
        cout << is_perp(z, z1) << endl;

        prosta nowa(0,0,100);
//        prosta nowa2 = nowa;




    }
    catch(invalid_argument& a)
    {
        cerr << a.what() << endl;
    }


    return 0;
}
