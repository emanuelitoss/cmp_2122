// standard library header files
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

// ROOT header files
#include "TRandom1.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

// My header files
#include "Datum.h"

// Additional lines to handle the Datum dictionary
#ifdef __MAKECINT__
#pragma link C++ class Datum+;
#endif

// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // With a random generator, we want to
  // 1) generate the TRUE VALUE of the observable in a given range and then
  // 2) take into account the detector resolution to generate the
  //    VALUE MEASURED by the detector
  // The range [x1,x2] for step 1
  double x1=0.9, x2=1.1;
  // For step 2 we condider a gaussian resolution of 10%
  double resol = 0.10;

  // ==== Store data in a TTree
  // Open a root file
  TString rootfname("./data.root");
  TFile* orootfile = new TFile( rootfname, "RECREATE");
  if( !orootfile->IsOpen() ) {
    std::cout << "problems creating root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

  // Create a new TTree object with branch suited for Datum objects
  TTree* tree = new TTree("datatree", "tree containing our data");

  // Variables to be stored in the tree
  Datum  datapoint;

  // Set the info for each branch (one) of the tree to correspond to data
  tree->Branch("datum", &datapoint);

  int nmeas = 100;

  // Start up a new random generator...
  TRandom1*  gen = new TRandom1();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

  // Loop over number of measurements and generate data 
  for(int i=0; i<nmeas; ++i) {
    // Genarate TRUE value
    double x0 = x1 + gen->Uniform(x2-x1);
    // Generate MEASURED value based on the true value and resolution
    double x = gen->Gaus(x0 , x0*resol);
    // Construct datapoint, including a Gaussian error on the value
    double err = (x2-x1)/sqrt(12);
    datapoint = Datum(x, gen->Gaus(err , err*0.10));

    // Add leaf to the tree
    tree->Fill();
  }

  // Finally, actually store tree in file on disk
  tree->Write();

  // Print some info about the tree
  tree->Print();
   
  // Critical to close the file!
  orootfile->Close();

  // ==== Done storing data in a TTree

  delete orootfile;
  delete gen;

  // Exit
  return 0;
}
