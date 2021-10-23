#include <iostream>
#include "complex.h"
using namespace std;

int main(){

    //two complex numbers initialized at z = 0 +i0
    complex c1;
    complex c2;

    //Checking initialization
    c1.print();
    c2.print();

    double var = 0.;

    //welcome message
    std::cout << "This app works with complex numbers. Have fun!" << std::endl;
    
    //inserting two complex numbers
    std::cout << "Insert real part of first complex number:" << std::endl;
    std::cin >> var;
    c1.setX(var);
    
    std::cout << "Insert immaginary part of first complex number:" << std::endl;
    std::cin >> var;
    c1.setY(var);

    c1.print();

    std::cout << "Insert real part of second complex number:" << std::endl;
    std::cin >> var;
    c2.setX(var);
    
    std::cout << "Insert immaginary part of second complex number:" << std::endl;
    std::cin >> var;
    c2.setY(var);
    
    c2.print();
    
    //four complex number needed to check overloaded operators
    complex c3, c4, c5, c6;
    c3 = c1 + c2;
    c4 = c1 - c2;
    c5 = c1 * c2;
    c6 = c1 / c2;

    std::cout << "Mostro le operazioni +, -, *, /" << std::endl;
    c3.print();
    c4.print();
    c5.print();
    c6.print();

    //overloaded operators *=, +=, -=, /=
    c3 -= c2; //is it equal to c1?
    c4 += c2; //is it equal to c1?
    c5 /= c2; //is it equal to c1? NO
    c6 *= c2; //is it equal to c1? NO

    std::cout << "Mostro le operazioni -=, +=, /=, *=" << std::endl;
    c3.print();
    c4.print();
    c5.print();
    c6.print();

    return 0;
}