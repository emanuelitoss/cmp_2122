#include <iostream>
#include "complex.h"
using namespace std;

int main(){

    complex c1(2., 0.5);
    complex c2(10);

    //c1.print();
    //c2.print();
    /*
    cout << "parte reale: " << c1.re() << endl;
    cout << "modulo: " << c1.mag() << endl;
    cout << "fase: " << c1.phase() << endl;
    cout << "fase special: " << c2.phase() << endl;
    */
    complex c3, c4, c5, c6;
    c3 = c1 + c2;
    c4 = c1 - c2;
    c5 = c1 * c2;
    c6 = c1 / c2;

    c3.print();
    c4.print();
    c5.print();
    c6.print();
    
    return 0;
}