// standard library header files
#include <vector>
#include <iostream>
// ROOT header files
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

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

  // Create a new TTree object
  TTree* tree = new TTree("datatree", "tree containing our data");

  /* Often the number of objects to be stored varies across events.
     Example: storing the energy for all photons produced in a collision
     involves the fact that the number of photons changes with the event.
     The simplest approach is to use fixed-size C-style arrays and to
     fill them up as need be.

     Here we store nmeas values of x and dx for nexp events/esperiments,
     where nmeas is Poisson-distributed. */

  // Variables to be stored in the tree
  const int nMeasMax=200; // Maximum size of static array per event
  double x0, x[nMeasMax], dx[nMeasMax];
  int nmeas;
  // The assumption that the number of measurements will never exceed nMeasMax
  // may be overcome by using std:vector<T> 

  // Set the info for each branch of the tree to correspond to data
  tree->Branch("nmeas", &nmeas, "nmeas/I");
  tree->Branch("value", x,  "value[nmeas]/D"); // nmeas is the index of value[]
  tree->Branch("error", dx, "error[nmeas]/D"); // and error[] in the tree
  // The new branch nmeas stores the (useful) size of value and error

  // Start up a new random generator...
  TRandom3*  gen = new TRandom3();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

  // Average # of measurements
  int nMeasAvg=50;
  // Number of experiments
  int nexp = 1000;

  // Loop over experiments
  for(int iexp=0; iexp<nexp; iexp++) {

    // Use Poisson distribution to generate nmeas
    nmeas = gen->Poisson(nMeasAvg);
    if(nmeas > nMeasMax) {
      std::cout << "WARNING: nmeas > " << nMeasMax << " your TTRee will be corrupted" << std::endl;
    }

    // Loop over number of measurements and fill in arrays
    for(int i=0; i<nmeas; ++i) {
      // Genarate TRUE value
      x0 = x1 + gen->Uniform(x2-x1);
      // Generate MEASURED value based on the true value and resolution
      x[i] = gen->Gaus(x0, x0*resol);
      // Generate UNCERTAINTY value based on the resolution and the measured value
      dx[i] = x[i]*resol;
    }

    // Then for each *experiment* store data in tree IN MEMORY
    tree->Fill();

  } // End of experiments loop

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
