#include <iostream>
using namespace std;

int main() {

    int v1[3] = { 1, 2, 3 };
    int v2[3]; // not initialized!
    int v3[] = { 1, 2, 3, 4, 5, 6, 7 }; // array of size 7

    int* c = v1;
    int* d = v3;
    int* e = v2;

    for(int i = 0; i < 5; ++i) {
        cout << "i: " << i << ", d = " << d << ", *d: " << *d;
        ++d;
        cout << ", e = " << e << ", *e: " << *e;
        ++e;
        cout << ", c = " << c << ", *c: " << *c << endl;
        ++c;
    }

   return 0;
}
