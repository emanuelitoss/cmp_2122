#include <iostream>
using namespace std;

int main() {

   int a;
   cout << "Insert value of a: ";
   cin >> a; // store value provided by user

   int* b; // b is  a pointer to varible of type int
   b  = &a; // value of b is the adress of memory location assigned to a

   int& x = a;

   cout << "value of a: " << a
        << ", address of a, &a: " << &a
        << endl;

   cout << "value of b: " << b
        << ", address of b, &b: " << &b
        << ", value of *b: " << *b
        << endl;

   cout << "value of x: " << x
        << ", address of x, &x: " << &x
        << endl;

   return 0;
}
