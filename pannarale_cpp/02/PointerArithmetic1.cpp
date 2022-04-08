#include <iostream>

void d_info(int *d){
   using namespace std;
   cout << "d = " << d << ", *d: " << *d <<endl;
}

int main() {

   int v3[] = { 1, 2, 3, 4, 5, 6, 7 }; // array of size 7

   int* d = v3;

   d_info(d++); // post-increment of d
   d_info(d);

   d_info(d+3); // 3 after address d

   d_info(d+7); // 7 after address d

   d_info(d+10); // 10 after address d

   return 0;
}
