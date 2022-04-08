// DatumNamespace.cc
// implementation of the Datum class

// include the class header file
#include "DatumNamespace.h"

// include any additional header files
// needed in the class definition
#include <iostream>
using std::cout;
using std::endl;
using namespace rome::teaching;

// constructor
Datum::Datum(double val, double error) {
    value_ = val;
    error_ = error;
}

// getters
double Datum::value() { return value_; }
double Datum::error() { return error_; }

// setters
void Datum::setValue(double value) { value_ = value; }
void Datum::setError(double error) { error_ = error; }

void Datum::print() {
    cout << "datum: " << value_ << " +/- " << error_ << endl;
}
