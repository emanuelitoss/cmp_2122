// DatumConst.h
#ifndef DatumConst_h
#define DatumConst_h

#include <iostream>
using namespace std;

class Datum {
  public:
    // constructors
    Datum();
    Datum(double val, double err);
    Datum(const Datum& datum);

    // getters
    double value() const { return value_; }
    double error() const { return error_; }

    // setters
    void setValue(double val) { value_ = val; }
    void setError(double err) { error_ = err; }

    double significance() const;

    void print(const std::string& comment) const;

  private:
    double value_;
    double error_;
};
#endif
