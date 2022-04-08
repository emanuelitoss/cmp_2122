#include <iostream>
using namespace std;

int main() {
  enum FitStatus  { Successful, Failed, Converged };

  FitStatus status;

  status = Successful;
  cout << "Status: " << status << endl;

  status = Converged;
  cout << "Status: " << status << endl;

  return 0;
}
