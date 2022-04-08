#include <iostream>

using namespace std;

void print_info(int *var, string var_name){
   cout << var_name << " = " << var << ", *" << var_name << ": " << *var <<endl;
}

int main() {

   int v[] = { 10, 20, 300, 40, 50, 60, 70 }; // array of size 7
   int *d = v;
   int *c = &v[4];

   for (int i=0; i<7; i++){
       string var_name = "v[" + to_string(i) + "]";
       print_info(&v[i], var_name);
   }
   print_info(d, "d");
   print_info(c, "c");

   int f = c - d;
   print_info(&f, "c-d");

   f = d - c;
   print_info(&f, "d-c");

   int *h = &v[6] + (d-c);
   print_info(h, "int *h = &v3[6] + (d-c)");

   return 0;
}
