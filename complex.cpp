#include <iostream>
#include "complex.h"
using namespace std;

int main(){

    complex c1;
    complex c2;

    double var = 0.;

    std::cout << "This app works with complex numbers. Have fun!" << std::endl;
    
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
    
    complex c3, c4, c5, c6;
    c3 = c1 + c2;
    c4 = c1 - c2;
    c5 = c1 * c2;
    c6 = c1 / c2;

    std::cout << "Mostro le operazioni di somma, sottrazione, prodotto e divisione:" << std::endl;
    c3.print();
    c4.print();
    c5.print();
    c6.print();

    return 0;
}