// CounterDestructor.h
#ifndef Counter_h_
#define Counter_h_

#include <string>
#include <iostream>

using namespace std;

class Counter {
  public:
    Counter(const std::string& name);
    ~Counter();
    int value();
    void reset();
    void increment(int step = 1);
    void print();

  private:
    int count_;
    std::string name_;
};
#endif
