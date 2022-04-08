// standard library header files
#include <iostream>
#include <fstream>
#include <iomanip>

// ROOT header files
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TStyle.h"

// My header files
#include "DataTree.h" // Implmentation needs to be the modified one!


// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // ==== Read data from input file
  // In order to access the data in a tree one needs
  // 1) name of the ROOT file where the tree is stored ("./data.root")
  // 2) name of the tree object ("datatree")
  // 3) name of the branches ("value" and "error"): DataTree.C takes care of this!
  TString rootfname("./data.root"); // [1]
  TFile* infile = TFile::Open(rootfname);
  if( !infile->IsOpen() ) {
    std::cout << "problems opening root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "Reading data from root file " << rootfname << std::endl;

  // Get pointer to tree object stored in the file
  TTree* tree = (TTree*) infile->Get("datatree"); // [2]
  if(!tree) {
    std::cout << "null pointer for TTree! exiting..." << std::endl;
    exit(-1);
  }

  // Instantiate object for data analysis
  // and pass the tree pointer to the constructor
  DataTree analyser(tree);

  // Perform the analysis
  analyser.Loop();

  // Critical to close the file!
  infile->Close();

  // Exit
  return 0;
}
