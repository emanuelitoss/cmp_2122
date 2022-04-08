#include <iostream>
#include <map>
using std::cout;
using std::endl;

int main(){
  enum Colour { Red=1, Blue=45, Yellow=17, Black=342 };

  Colour col;

  // new map with key: integer     value: string
  std::map<int, std::string> colname;
  
  colname[Red] = std::string("Red");
  colname[Black] = std::string("Black");

  col = Red;
  cout << "Colour int: " << col << endl;
  cout << "Colour name: " << colname[col] << endl;

  return 0;
}
