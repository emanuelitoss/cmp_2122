#include <string>
#include <iostream>
using namespace std;

#include "Function.h"
#include "Gauss.h"

int main() {

  Function* g1 = new Gauss("g1",0.,1.);
  g1->print();
  double x = g1->integrate(0., 3.);

  return 0;
}
