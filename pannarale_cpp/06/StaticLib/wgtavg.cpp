#include <vector> 
#include <iostream> 
 
#include "Datum.h" // basic data object 
#include "InputService.h" // class handle input of data
#include "Calculator.h" // impelments various algorithms 

using std::cout;
using std::endl;

int main() { 
 
  std::vector<Datum> data = InputService::readDataFromUser();
  
  Datum r1 = Calculator::weightedAverage(data);
  cout << "weighted average: " << r1 << endl;

  Datum r2 = Calculator::arithmeticAverage(data); 

  Datum r3 = Calculator::geometricAverage(data);

  return 0;
} 
