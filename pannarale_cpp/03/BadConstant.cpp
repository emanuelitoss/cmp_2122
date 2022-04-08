int main() {

   float a = 1, c = 3;

   // From right to left: constant pointer to constant float
   const float * const b = &a;

   // Change value of what b points to: NOT OK!
   *b = 5;

   // Assign new value (address) to b: NOT OK!
   b = &c;

   return 0;
}
