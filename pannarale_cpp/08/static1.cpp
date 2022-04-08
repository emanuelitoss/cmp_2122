#include <iostream>
#include <string>
using namespace std;
#include "Unit.h"


int main() {
  Unit giorgio("Giorgio Parisi");
  cout << giorgio << endl;

  cout << "&giorgio.counter_: " << &giorgio.counter_ << endl;

  Unit* gan = new Unit("Gandalf");
  Unit neo("Neo");
  cout << "&neo.counter_: " << &neo.counter_ << endl;

  cout << "&(gandalf->counter_): " << &(gan->counter_) << endl;
  cout << neo << endl;

  delete gan;

  cout << neo << endl;

  return 0;
}
