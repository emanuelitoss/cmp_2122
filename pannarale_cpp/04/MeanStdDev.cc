#include <cmath>
#include "Datum.h"
#include "MeanStdDev.h"

double mean(const vector<Datum>& data) {

  double m(0.); // same as = 0.

  // loop over data
  for(Datum data_itr : data){
    m += data_itr.value();
  }
  // compute average: finds out data size!
  m /= data.size();

  return m;
}

Datum mean_and_stdDev(const vector<Datum>& data) {

  double m = mean(data), stdDev(0.);

  // loop over data
  for(Datum data_itr : data){
    stdDev += pow(data_itr.value()-m, 2.);
  }
  // divide by n-1
  stdDev /= (data.size()-1);
  // finally compute the stdDev
  stdDev = sqrt( stdDev );

  return Datum(m, stdDev);
}
