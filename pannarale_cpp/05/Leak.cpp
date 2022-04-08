#include <iostream>
using namespace std;

int main() {

  int i=1;
  while(i>0){

    double* ptr = new double[1000000000];
    ptr[0] = 1.1;

    cout << "i: " << i
         << ", ptr: " << ptr
         << ", ptr[0]: " << ptr[0]
         << endl;

    //delete[] ptr; // ops! memory leak!
    i++;
  }

  return 0;
}
