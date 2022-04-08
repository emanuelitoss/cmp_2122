#include <iostream>

namespace physics {
  double mean(double a, double b) {
    return (a+b)/2.;
  }
}

void printMean(double a, double b) {
  double z1 = physics::mean(a,b);

  using namespace std; // using std namespace within this method!
  cout << "physics::mean(" << a << "," << b << ") = " << z1 << endl;
}

int main() {

  double x = 3;
  double y = 4;

  printMean(x,y);
  cout << "no namespace available in the main!" << endl;

  return 0;
}
