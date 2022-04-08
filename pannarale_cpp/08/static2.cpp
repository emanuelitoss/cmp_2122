#include <iostream>
#include <string>
using namespace std;
#include "Unit2.h"


int main() {
  Unit piero("Piero");
  Unit* fra = new Unit("Francesca");
  cout << "piero.getCount(): " << piero.getCount() << endl;
  cout << "fra->getCount(): " << fra->getCount() << endl;

  delete fra;

  return 0;
}
