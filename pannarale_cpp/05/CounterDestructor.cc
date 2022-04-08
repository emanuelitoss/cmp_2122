// CounterDestructor.cc
#include "CounterDestructor.h"

#include <iostream>
using std::cout;
using std::endl;

Counter::Counter(const std::string& name) {
  count_ = 0;
  name_ = name;
  cout << "Counter::Counter() called for Counter "
       << name_ << endl;
};

Counter::~Counter() {
  cout << "Counter::~Counter() called for Counter "
       << name_ << endl;
};

int Counter::value() {
  return count_;
}

void Counter::reset() { 
 count_ = 0;
}

void Counter::increment(int step) { 
  count_ = count_+step;
}

void Counter::print() {
  cout << "Counter::print(): name: " << name_ 
       << "  value: " << count_ << endl;
}
