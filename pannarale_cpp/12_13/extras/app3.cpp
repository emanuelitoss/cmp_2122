// standard library header files
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

// ROOT header files
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"

// My header files
#include "Datum.h"

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

  // Create new histograms to look at TRUE and MEASURED distributions
  int nbins = 100;
  // The horizontal axis ranges are set as a function of interval and resolution
  double xlo = x1*(1-5*resol);
  double xhi = x2*(1+5*resol);
  double binwidth = (xhi-xlo) / nbins;
  std::cout << "# bins: " << nbins << "\t bin width: " << binwidth << std::endl;
  // The two histograms instances (name, title, number of bins, range)
  TH1F hx1("hx1", "distribution of true x", nbins, xlo, xhi );
  TH1F hdx1("hdx1", "distribution of  x uncertainty", nbins, -5*resol , 5*resol );

  // Start up a new random generator...
  TRandom3*  gen = new TRandom3();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);

  // # measurements
  int nmeas = 1000;
  std::vector<Datum> data;

  // Loop on the measurements
  for(int i=0; i<nmeas; ++i) {

    // Genarate TRUE values: these have a flat distribution in [x1, x2]
    double x0 = x1 + gen->Uniform(x2-x1);

    // Generate MEASURED value based on the true value and resolution
    double x = gen->Gaus(x0, x0*resol);

    // Generate UNCERTAINTY based on the resolution
    double dx = x*resol;

    // Store Datum in vector
    data.push_back( Datum( x, dx) );

    // Fill histograms
    hx1.Fill(x);
    hdx1.Fill(dx);
  }

  // After generating the data, we take care of plotting the results
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);

  // Make histogram hx1 nicer
  hx1.GetXaxis()->SetTitle("Distribution of \\deltax [GeV]");
  hx1.Draw();
  // Make pdf file
  canv.SaveAs("./x.pdf");

  // Make histogram hdx1 nicer
  hdx1.GetXaxis()->SetTitle("Distribution of uncertainty \\deltax [cm]");
  hdx1.Draw("pe");
  // Make pdf file
  canv.SaveAs("./dx.pdf");

  // One pdf with two panels
  canv.Clear();
  canv.Divide(1,2);
  canv.cd(1);
  hx1.Draw();
  canv.cd(2);
  hdx1.Draw("pe");
  canv.SaveAs("./plots.pdf");

  // Store data to file
  std::ofstream ofile;
  std::string ofname("./data.txt");
  std:: cout << "storing data in " << ofname << std::endl;
  ofile.open( ofname );

  for(std::vector<Datum>::const_iterator it = data.begin(); it != data.end(); ++it) {
    ofile << std::setprecision(3) << std::fixed ;
    ofile << it->value() << "\t" << it->error() << std::endl;
  }
  ofile.close();
  std::cout << ofname << " output file successfully created" << std::endl;

  // Clean up
  delete gen;

  // Exit
  return 0;
}
