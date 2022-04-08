#include <vector>

using std::vector;

// returns mean of values in data
// passing by constant reference to ensure
// data cannot be changed within the function
double mean(const vector<Datum>& data);

// returns a Datum containing
// value = mean(data)
// error = standard deviation of data values
// passing by constant reference to ensure
// data cannot be changed within the function
Datum mean_and_stdDev(const vector<Datum>& data);
