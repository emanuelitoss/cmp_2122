// Counter.cc
#include "Counter.h"

#include <iostream>

Counter::Counter() {
  count_ = 0;
}

int Counter::value() {
  return count_;
}

void Counter::reset() { 
 count_ = 0;
}

void Counter::increment() {
  count_++;
}

void Counter::increment(int step) { 
  count_ = count_+step;
}
