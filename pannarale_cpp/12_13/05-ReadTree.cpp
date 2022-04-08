// standard library header files
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

// ROOT header files
#include "TH1F.h"
#include "TH2F.h"
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
  TH1F hdx1("hdx1", "distribution of \\deltax values", nbins, 0.1, 0.3);
  TH1F hdxRMS("hdxRMS", "distribution of \\deltax RMS in all experiments", nbins, 0.0, 0.05 );

  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;

  TH1I hnmeas("hnmeas","Number of measurements per experiment", 81, -0.5, 80.5);
  // This is 2D, so there are two sets of bins numbers and ranges
  TH2F h2RMS("h2RMS", "Distribution of dx RMS vs numb. measurements",
	     81, -0.5, 80.5,
	     nbins, 0.0, 0.05);

  // ==== Read data from file
  // In order to access the data in a tree one needs
  // 1) name of the ROOT file where the tree is stored ("./data.root")
  // 2) name of the tree object ("datatree")
  // 3) name of the branches ("value", "error" and "neams")
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

  // Variables to be read from the tree: use fixed-size C-style arrays 
  const int nMeasMax = 200;
  double y[nMeasMax], dy[nMeasMax];
  int nmeas;

  // Set the info for each branch of the tree to correspond to our data
  tree->SetBranchAddress("value", y);      // [3]
  tree->SetBranchAddress("error", dy);     // [3]
  tree->SetBranchAddress("nmeas", &nmeas); // [3]

  // Retrieve information about number of experiments
  int nentries = tree->GetEntries();

  // Loop over events/experiments in the tree
  for (int iexp=0; iexp<nentries; ++iexp) {
    tree->GetEntry(iexp); // read data from file to memory

    // Vector of Datum for data being read
    std::vector<Datum> data;
    hnmeas.Fill(nmeas);

    // For each event/experiment, iterate over measurements
    for(int i=0; i<nmeas; ++i) {
      // Fill Datum vector for later use (no actual use in this example)
      data.push_back(Datum(y[i], dy[i]));
      hdx1.Fill(dy[i]);
    } // End loop on mesurements

    // Compute RMS for measurements in each experiment and fill a histogram
    // Double call to hdx1.GetRMS() is suboptimal
    hdxRMS.Fill(hdx1.GetRMS());
    h2RMS.Fill(nmeas, hdx1.GetRMS());

  } // End loop on experiments

  // ==== Make plots

  // Useful plot setting: show over and underflow
  gStyle->SetOptStat(111111);

  // Create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);

  // Plot with 2D histogram
  h2RMS.GetXaxis()->SetTitle("Number of measurements");
  h2RMS.GetYaxis()->SetTitle("dx RMS");
  h2RMS.Draw("colz");
  canv.SaveAs("./2dRMS.pdf");

  // Plot with 3 1D histograms
  canv.Clear();
  canv.Divide(2,2);
  canv.cd(1);
  hnmeas.GetXaxis()->SetTitle("Number of measurements");
  hnmeas.Draw("");

  canv.cd(2);
  hdxRMS.GetXaxis()->SetTitle("Distribution of RMS of uncertainty dx");
  hdxRMS.Draw("pe");

  canv.cd(3);
  hdx1.Draw();

  canv.SaveAs("./expplots.pdf");

  // Critical to close the file!
  infile->Close();

  // Exit
  return 0;
}
