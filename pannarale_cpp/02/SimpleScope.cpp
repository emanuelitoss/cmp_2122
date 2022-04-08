#include <iostream>
using namespace std;

int main() {

    double x = 1.2;

    cout << "in main before scope, x: " << x << endl;

    for(int i=0; i<3; ++i) { // just a local scope
        cout << "--> i: " << i << endl;

        x++;
        cout << "in local scope before int, x: " << x << endl;

        int x = 4;
        cout << "in local scope after int, x: " << x << endl;
    }

    //This will not work: it is outside the scope of i
    // cout << i << endl;
    cout << "in main after local scope, x: " << x << endl;

    return 0;
}
