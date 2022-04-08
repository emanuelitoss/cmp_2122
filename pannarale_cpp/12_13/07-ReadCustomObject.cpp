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
#include "TStyle.h"

// My header files
#include "Datum.h"

// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // Use parameters of the random generator in 04-WriteObjects.cpp
  // to properly center the histogram plots that will be created here:
  // * the range [x1,x2] of the uniform distribution of TRUE values
  double x1 = 0.5, x2 = 1.5;
  // Create new histograms to look at values and error distributions
  int nbins = 50;
  double binwidth = (x2-x1) / nbins;
  TH1F hx1("hx1", "distribution of x values", nbins, x1, x2);
  // Use TString::Form() function to add correct y axis label with bin width
  hx1.GetYaxis()->SetTitle(Form("entries/%.3f", binwidth));
  TH1F hdx1("hdx1", "distribution of x uncertainty", nbins, 0, 0.1);
  binwidth = 0.1/nbins;
  hdx1.GetYaxis()->SetTitle(Form("entries/%.3f", binwidth));

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

  // Pointer to a Datum object to be read from Branch
  Datum* d=0;

  // Set the info for each branch of the tree to correspond to data
  // Note: setting the address of a pointer to a Datum object in the branch
  tree->SetBranchAddress("datum", &d);
  

  // Print tree information
  tree->Print();

  // Vector of Datum for data being read
  std::vector<Datum> data;

  // Loop over all the entries in the tree
  int nentries = tree->GetEntries();
  for (int i=0; i<nentries; ++i) {
    // Access (i.e., read from file) Datum object which the leaf of the tree
    tree->GetEntry(i);
    // Fill in histos with value and error data
    hx1.Fill(d->value());
    hdx1.Fill(d->error());
    // Fill Datum vector for later use (no actual use in this example)
    data.push_back(*d);
  }

  // ==== Make plots

  // Useful plot setting: show over and underflow
  gStyle->SetOptStat(111111);

  // Histogram titles
  hx1.GetXaxis()->SetTitle("Distribution of x");
  hdx1.GetXaxis()->SetTitle("Distribution of uncertainty \\deltax");

  // Create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);

  // One pdf with two panels
  canv.Divide(1,2);
  canv.cd(1);
  hx1.SetFillColor(kRed);
  hx1.Draw();
  canv.cd(2);
  hdx1.SetMarkerStyle(31);
  hdx1.Draw("pe");
  canv.SaveAs("./newplots.pdf");

  // Critical to close the file!
  infile->Close();

  // Exit
  return 0;
}
