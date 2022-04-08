#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  // file name
  const char filename[30] = "input.txt";

  // create object for input file
  ifstream infile(filename); //input file object

  // string to hold each line
  string line;

  // make sure input file is open otherwise exit
  if(!infile.is_open()) {
    cerr << "cannot open input file" << endl;
    return -1;
  }

  // variables to read in from file at each line
  char name[30];
  double val, errpos;
  float errneg;

  // loop over file until end-of-file
  while(!infile.eof()) {
     // get current line
     getline(infile,line);
     if( line == "\n" || line == "" ) continue;

     // parse line with the provided format and put data in variables
     // NB: USING POINTERS TO VARIABLES
     // format:  %s string    %f  float   %lf  double 
     sscanf(line.c_str(),"%s %lf %lf %f", name, &val, &errpos, &errneg);

     // print out for debug purposes
     cout << "name: " << name
          << "\t\tvalue: " << val << "\tpos err: " << errpos
          << "\tneg err: " << errneg << endl;
  } // !eof

  infile.close(); // close input file before exiting

  return 0;
}
