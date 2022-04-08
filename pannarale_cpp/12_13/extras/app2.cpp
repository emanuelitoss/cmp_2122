// standard library header files
#include <iostream>

// ROOT header files
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"


// For the time being we will not use command line variables
int main(int argc, char* argv[]) {

  // With a random generator, we want to
  // 1) generate the TRUE VALUE of the observable in a given range and then
  // 2) take into account the detector resolution to generate the
  //    VALUE MEASURED by the detector
  // The range [x1,x2] for step 1
  double x1=0.9, x2=1.1;
  // For step 2 we condider a gaussian resolution of 5%
  double resol = 0.05;

  // Create new histograms to look at TRUE and MEASURED distributions
  int nbins = 50;
  // The two histograms instances (name, title, number of bins, range)
  // The horizontal axis ranges are set as a function of interval and resolution
  TH1F hx1("hx1", "distribution of true x",
           nbins, x1*(1-5*resol), x2*(1+5*resol));
  TH1F hdx1("hdx1", "distribution of measured x",
           nbins, x1*(1-5*resol), x2*(1+5*resol));
  double binwidth = (x2*(1+5*resol)-x1*(1-5*resol)) / nbins;
  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;

  // Start up a new random generator...
  TRandom3*  gen = new TRandom3();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

  // # measurements
  int nmeas = 1000;

  // Loop on the measurements
  for(int i=0; i<nmeas; ++i) {

    // Genarate TRUE values: these have a flat distribution in [x1, x2]
    double x = x1 + gen->Uniform(x2-x1);

    // Generate MEASURED value based on the true value and resolution
    double dx = gen->Gaus(x, x*resol);

    // Fill histograms
    hx1.Fill(x);
    hdx1.Fill(dx);
  }

  // After generating the data, we take care of plotting the results
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);

  // Make histogram hx1 nicer
  hx1.GetXaxis()->SetTitle("Distribution of x [cm]");
  hx1.Draw();
  // Make pdf file
  canv.SaveAs("./x.pdf");

  // Make histogram hdx1 nicer
  hdx1.GetXaxis()->SetTitle("Distribution of uncertainty dx [cm]");
  hdx1.Draw("pe");
  // Make pdf file
  canv.SaveAs("./dx.pdf");

  // Clean up
  delete gen;

  // Exit
  return 0;
}
