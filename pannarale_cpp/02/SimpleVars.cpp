#include <iostream>
using namespace std;

int main() {
    int samples; // declaration only
    int events = 1; // declaration and assignment

    cout << "samples default value: " << samples << endl;

    samples = 123; // assignment separate from declaration
    cout << "samples initialization value: " << samples << endl;

    cout << "How many samples? " ;
    cin >> samples; // assigment via I/O

    cout << "samples: " << samples
         << "\t"  // insert a tab in the printout
         <<  "events: " << events
         << endl;

    return 0;
} // end of main
