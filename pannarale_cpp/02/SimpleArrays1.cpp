#include <iostream>
using namespace std;

int main() {

    float v1[3] = {0.4, 1.34, 56.156};
    float v2[3]; // use default value 0 for each element
    // array of size 7
    float v3[] = { 0.9, -0.1, -0.65, 1.012, 2.23, -0.67, 2.22 };

    for(int i = 0; i < 5; ++i) {
        cout << "i: " << i << "\t"
             << "v1[" << i << "]: " << v1[i] << "\t\t"
             << "v2[" << i << "]: " << v2[i] << "\t"
             << "v3[" << i << "]: " << v3[i]
             << endl;
   }

   return 0;
}
