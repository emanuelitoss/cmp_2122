// standard library header files
#include <iostream>

// ROOT header files: random numbers, plotting, file storage
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"

// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // Open TFile for output
  TString rootfname("./output.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
    std::cout << "problems creating root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

  // With a random generator, we want to
  // 1) generate the TRUE VALUE of the observable in a given range and then
  // 2) take into account the detector resolution to generate the
  //    VALUE MEASURED by the detector
  // The range [x1,x2] for step 1
  double x1=0.9, x2=1.1;
  // For step 2 we condider a gaussian resolution of 10%
  double resol = 0.10;

  // Create new histograms to look at TRUE and MEASURED distributions
  int nbins = 100;
  // The histogram limits are set as a function of interval and resolution
  double xlo = x1*(1-5*resol);
  double xhi = x2*(1+5*resol);
  double binwidth = (xhi-xlo) / nbins;
  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;
  // The two histograms instances (name, title, number of bins, range)
  TH1F hx1("hx1", "distribution of true x", nbins, xlo, xhi);
  // The 'd' is for detector
  TH1F hdx1("hdx1", "distribution of measured x", nbins, xlo , xhi);

  // Start up a new random generator... (we have a new: we will need a delete!)
  TRandom3*  gen = new TRandom3();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

  // # measurements
  int nsig = 1000;

  // Loop on the measurements
  for(int i=0; i<nsig; ++i) {

    // Genarate TRUE values: these have a flat distribution in [x1, x2]
    double x = x1 + gen->Uniform(x2-x1);

    // Generate MEASURED value based on the true value and resolution
    double dx = gen->Gaus(x, x*resol);

    // Fill in histograms
    hx1.Fill(x);
    hdx1.Fill(dx);
  }

  // After generating the data, we take care of plotting the results:
  // * create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  // * start from TRUE values and customize some histogram properties
  hx1.GetXaxis()->SetTitle("Distribution of x [GeV]");
  // * plot
  hx1.Draw();
  // * store to file in 2 formats
  canv.SaveAs("./x.pdf");
  canv.SaveAs("./x.jpg");
  // * move to the MEASURED values
  hdx1.GetXaxis()->SetTitle("Distribution of uncertainty \\Delta x [GeV]");
  // * in this case, show points with error bars
  hdx1.Draw("pe");
  canv.SaveAs("./dx.pdf");
  canv.SaveAs("./dx.jpg");

  // A simple example of fitting with predefined functions
  // https://root.cern.ch/root/htmldoc/guides/users-guide/FittingHistograms.html
  // * fit histogram of MEASURED values with Gaussian function
  hdx1.Fit("gaus");
  hdx1.Draw();
  canv.SaveAs("./dxfit.pdf");
  canv.SaveAs("./dxfit.jpg");

  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;

  // Store both histograms to file
  hx1.Write();
  hdx1.Write();

  // Critical to close the file!
  rfile.Close();

  // Exit
  return 0;
}
