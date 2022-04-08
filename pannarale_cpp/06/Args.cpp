#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

  cout << "# of cmd line arguments argc: " << argc << endl;
  cout << "argv[0]: " << argv[0] << endl;
  cout << "Running " ;
  for(int i=0; i<argc; i++){
    cout << argv[i] << " ";
  }
  cout << endl;

  return 0;
}
