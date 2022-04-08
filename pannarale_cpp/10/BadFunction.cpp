#include <string>
#include <iostream>
#include <cmath>
using namespace std;

class BadFunction {
  public:
    BadFunction(const std::string& name){
      name_ = name;
    }
    virtual double value(double x) const { return 0; }
    virtual double integrate(double x1, double x2) const { return 0; }

  private:
    std::string name_;
};

class Gauss : public BadFunction {
  public:
    Gauss(const std::string& name, double mean, double width) : BadFunction(name) {
      mean_ = mean;
      width_ = width;
    }
    virtual double value(double x) const {
      double pull = (x-mean_)/width_;
      double y = (1/sqrt(2.*3.14*width_)) * exp(-pull*pull/2.);
      return y;
    }

  private:
    double mean_;
    double width_;
};


int main() {

  Gauss g1("g1",0.,1.);
  cout << "g1.value(2.): " << g1.value(2.) << endl;
  cout << "g1.integrate(0.,1000.): " 
       << g1.integrate(0.,1000.) << endl;

  return 0;
}
