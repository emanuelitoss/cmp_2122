// Counter.cpp
#include "Counter.h" 

using namespace std;

int main() {
  Counter counter;
  cout << "counter: " << counter.value() << endl;

  // no argument
  counter.increment();
  cout << "counter: " << counter.value() << endl;

  // provide argument, same function
  counter.increment(14);
  cout << "counter: " << counter.value() << endl;

  return 0;
}
