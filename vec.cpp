#include <iostream>
#include "Vector3D.h"
using namespace std;
using std::cout;
using std::endl;

int main(){

    Vector3D v1;
    v1.print();

    cout << "Instert x,y,z coordinates of v1:" << endl;
    double a,b,c;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    v1.setX(a);
    v1.setY(b);
    v1.setZ(c);

    cout << "Spherical coordinates (r,theta,phi): " << v1.magnitude() << ", " << v1.theta() << ", " << v1.phi() << endl;

    Vector3D v2;
    v2.print();

    cout << "Instert x,y,z coordinates of v2:" << endl;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    v2.setX(a);
    v2.setY(b);
    v2.setZ(c);

    cout << "Spherical coordinates (r,theta,phi): " << v2.magnitude() << ", " << v2.theta() << ", " << v2.phi() << endl;

    double scalar1 = v1.ScalarProduct(v2);
    double scalar2 = v2.ScalarProduct(v1);

    cout << "Prodotti scalari: " << scalar1 << ", " << scalar2 << endl;

    Vector3D v3;
    
    v3 = v1.VectorProduct(v2);

    cout << "Spherical coordinates of v3 (r,theta,phi): " << v3.magnitude() << ", " << v3.theta() << ", " << v3.phi() << 
    "\t Cartesian: " << v3.X() << ", " << v3.Y() << ", " << v3.Z() << endl;

    v3 = v1 + v2;
    v3.print();

    v3 = v1 - v2;    
    v3.print();

    cout << "Inserire costante:" << endl;
    cin >> a;

    v1 = v1*a;
    v1.print();
    v1 = v1/a;
    v1.print();

    return 0;
}