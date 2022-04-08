#include <iostream>
#include <vector>
#include "Datum.h"

int main() {

  // create vectors with values and errors
  std::vector<double> vals, errs;
  vals.push_back(1.3);
  vals.push_back(-2.1);
  errs.push_back(0.2);
  errs.push_back(0.3);

  // or interface vector and Datum!
  std::vector<Datum> data;
  data.push_back( Datum(1.3, 0.2) );
  data.push_back( Datum(-2.1, 0.3) );

  std::cout << "# dati:: " << data.size() << std::endl;

  // print data using traditional loop on an array
  int i=0;
  std::cout << "Using [] operator on vector" << std::endl;
  for(i=0; i<data.size(); i++) {
    std::cout << "i: " << i+1
	      << "\t data: " << data[i].value() << " +/- " << data[i].error()
	      << std::endl;
  }

  // print data using vector iterator  
  i=0;
  std::cout << "std::vector<T>::iterator " << std::endl;
  for(std::vector<Datum>::iterator d = data.begin(); d != data.end(); d++) {
    i++;
    std::cout << "i: " << i
	      << "\t data: " << d->value() << " +/- " << d->error()
	      << std::endl;
  } 

  // print data using vector iterator  
  i=0;
  std::cout << "C++11 extension feature " << std::endl;
  for(Datum data_itr : data) {
    i++;
    std::cout << "i: " << i
	      << "\t data: " << data_itr.value() << " +/- " << data_itr.error()
	      << std::endl;
  }

  return 0;

}
