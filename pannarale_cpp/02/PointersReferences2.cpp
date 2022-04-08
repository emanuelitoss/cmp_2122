#include <iostream>
using namespace std;

void print_info(int a, string var_name){
   cout << "value of " << var_name << ": " << a
        << ", address of " << var_name << ", " 
        << "&" << var_name << ": " << &a << endl;
}
   
int main() {

   int a = 1;
   print_info(a, "a");

   int* b = &a;
   *b = 3;
   print_info(a, "a");

   int& x = a;
   x = 45;
   print_info(a, "a");

   return 0;
}
