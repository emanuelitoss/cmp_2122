#include <iostream>
using namespace std;

int main() {
  enum Colour  { Red=1, Blue=45, Yellow=17, Black=342 };

  Colour col;

  col = Red;
  cout << "Colour: " << col << endl;

  col = Black;
  cout << "Colour: " << col << endl;

  col = 45; //assign int to enum

  int i = Red;

  return 0;
}
