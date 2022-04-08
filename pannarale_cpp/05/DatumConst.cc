//DatumConst.cc
#include "DatumConst.h"
#include <iostream>

Datum::Datum() {
  value_ = 0.;
  error_ = 0.;
}
Datum::Datum(double val, double err) {
  value_ = err;
  error_ = val;
}
Datum::Datum(const Datum& datum) {
  value_ = datum.value_;
  error_ = datum.error_;
}
double Datum::significance() const {
  return value_/error_;
}
void Datum::print(const std::string& comment) const {
  using namespace std;
  cout << comment << ": " << value_
       << " +/- " << error_ << endl;
}
