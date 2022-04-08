// standard library header files
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

// ROOT header files
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"

// My header files
#include "Datum.h"

// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // Use parameters of the random generator in 02-WriteTree.cpp
  // to properly center the histogram plots that will be created here:
  // * the range [x1,x2] of the uniform distribution of TRUE values
  double x1=0.9, x2=1.1;
  // * the detector resolution for the (Gaussian) distribution of MEASURED values
  double resol = 0.10;

  // Create new histograms to look at values and error distributions
  int nbins = 100;
  // The histogram limits are set as a function of interval and resolution
  double xlo = x1*(1-5*resol);
  double xhi = x2*(1+5*resol);
  double binwidth = (xhi-xlo) / nbins;
  TH1F hx1("hx1", "distribution of value", nbins, xlo, xhi);
  TH1F hdx1("hdx1", "distribution of error", nbins, -1.1, 0.4 );

  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;

  // ==== Read data from file
  // In order to access the data in a tree one needs
  // 1) name of the ROOT file where the tree is stored ("./data.root")
  // 2) name of the tree object ("datatree")
  // 3) name of the branches ("value" and "error")
  TString rootfname("./data.root"); // [1]
  TFile* infile = new TFile(rootfname);
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

  // Variables to be read from the tree
  double y, dy;

  // Set the info for each branch of the tree to correspond to our data
  tree->SetBranchAddress("value", &y);  // [3]
  tree->SetBranchAddress("error", &dy); // [3]

  // Vector of Datum for data being read
  std::vector<Datum> data;

  int nentries = tree->GetEntries();
  for (int i=0; i<nentries; ++i) {
    tree->GetEntry(i); // read data from file to memory

    // Populate Datum object
    data.push_back(Datum(y, dy));

    hx1.Fill(y);
    hdx1.Fill(dy);
  }

  // ==== Make plots
  hx1.GetXaxis()->SetTitle("Distribution of x [GeV]");
  hdx1.GetXaxis()->SetTitle("Distribution of \\deltax [GeV]");

  // One pdf with two panels
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  canv.Divide(1,2);
  canv.cd(1);
  hx1.Fit("gaus");
  hx1.Draw();
  canv.cd(2);
  hdx1.Fit("gaus");
  hdx1.Draw("pe");
  canv.SaveAs("./newplots.pdf");

  // Critical to close the file!
  infile->Close();

  // Exit
  return 0;
}
