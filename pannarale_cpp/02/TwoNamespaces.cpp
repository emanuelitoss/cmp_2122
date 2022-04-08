#include <iostream>

namespace physics {
  double mean(double a, double b) {
    return (a+b)/2.;
  }
}

namespace foobar {
  double mean(double a, double b) {
    return (a*a+b*b)/2.;
  }
}

int main() {

   double x = 3, y = 4;

   double z1 = physics::mean(x,y);
   std::cout << "physics::mean(" << x << "," << y << ") = " << z1 
             << std::endl;

   double z2 = foobar::mean(x,y);
   std::cout << "foobar::mean(" << x << "," << y << ") = " << z2 
             << std::endl;

   return 0;
}
