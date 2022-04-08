#include <iostream>
using namespace std;

int main() { // main begins here

   int nIterations = 0; // Initialized

   cout << "How many iterations? "; 

   cin >> nIterations;

   // fails if input data does not match expected data type
   if(cin.fail()) cout << "cin failed!" << endl;

   // print message to STDOUT
   cout << "Number of requested iterations: " << nIterations << endl;

   return 0;

} // end of main
