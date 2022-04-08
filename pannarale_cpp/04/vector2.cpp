#include "Datum.h"
#include "MeanStdDev.h"

using std::vector;

int main(){

  std::vector<Datum> data;
  data.push_back( Datum(1.3, 0.2) );
  data.push_back( Datum(-2.1, 0.3) );

  Datum m_and_sd = mean_and_stdDev(data);
  m_and_sd.print();

  return 0;
}
