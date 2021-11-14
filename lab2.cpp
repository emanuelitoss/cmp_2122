// standard library header files
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

//#include "Vector3D.h" //including Vector3D class
// ROOT header files: random numbers, plotting, file storage
#include  "TRandom3.h"
#include  "TH1F.h"
#include  "TCanvas.h"
#include  "TFile.h"
#include  "TLorentzVector.h"
#include  "TMath.h"

#define eps = 0.0001 //very little value that could be useful
int main(){

//FILE OPENING

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
    std::cout << "storing output in root file" << rootfname << std::endl;
    


    // Create the B meson 4-momentum in the LAB frame
    TLorentzVector p4_B;
    double p_B = 0.300; //Meson momentum (GeV)
    double m_B = 5.279; //Meson mass (GeV)
    double m_pi = 0.140; //Pion mass (GeV)
    double m_K = 0.500;//Pion mass (GeV)
    
    // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
    p4_B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B*m_B));
    //momentum of generated particles in the CoM system
    double p_star = sqrt((pow(m_B,4) + pow(m_pi,4) + pow(m_K,4) - 2*pow(m_K,2)*pow(m_pi,2) - 2*pow(m_K,2)*pow(m_B,2) - 2*pow(m_pi,2)*pow(m_B,2) ))/(2*m_B);

// BOOST PARAMETERS CHECK
/*
  // The TLorentzVector class provides the Beta() and Gamma() methods to
  // compute the boost parameters: we compare them to their definitions
  cout << "--> boost parameters of B reference frame" << endl;
  cout << "\t beta: " << p4_B.Beta() << "\t"
       << "\t p/E:" << p4_B.P()/p4_B.E() << "\n"
       << "\t gamma: " << p4_B.Gamma() << "\t"
       << "\t E/m: " << p4_B.E()/m_B << "\n"
       << "\t beta*gamma: " << p4_B.Beta()*p4_B.Gamma() << "\t"
       << "\t p/m: " << p_B/m_B
       << endl;

  // Boost parameters of the B frame in the LAB frame can be accessed
  // with the BoostVector method
  cout << "--> boost vector of the B meson" << endl;
  p4_B.BoostVector().Print();

*/
    // Create the 4-momentum in the CoM frame
    TLorentzVector p4_pi_0;
    TLorentzVector p4_K_0;
    // Create the 4-momentum in the LAB frame
    TLorentzVector p4_pi_meas;
    TLorentzVector p4_K_meas;
    
    TLorentzVector p4_tot;
    

    double px_star, py_star, pz_star;


    // Create new histograms
    int nbins = 100;
  
    // The histograms instances (name, title, number of bins, range)
    TH1F h_invM("invariant mass", "distribution of invariant mass", nbins, 4.5 , 6);
    TH1F h_measM("real mass", "distribution of real mass", nbins, 4.5, 14);
    TH1F h_angle("opening angle","distribution of the angle between pi and K", nbins, 3 , 3.2);
  

// RANDOM MOMENTA GENERATION
  
    //Random generator
    // Start up a new random generator... (we have a new: we will need a delete!)
    TRandom3*  gen = new TRandom3();
    // ...exploiting the machine clock for the seed
    gen->SetSeed(0);
    
    
    // Loop on the measurements
    
    // # measurements
    int nsig = 10000;
    
    for(int i=0; i<nsig; ++i) {
        //Generate values for momentum in random direction in the CoM system:
	gen->Sphere(px_star, py_star, pz_star, p_star);
        p4_pi_0.SetPxPyPzE(px_star, py_star, pz_star, sqrt(p_star*p_star+m_pi*m_pi));
        p4_K_0.SetPxPyPzE(-px_star, -py_star, -pz_star, sqrt(p_star*p_star+m_K*m_K));
	
	//BOOST		
        p4_pi_0.Boost(-p4_B.BoostVector());
        p4_K_0.Boost(-p4_B.BoostVector());
	
	p4_tot=p4_pi_0+p4_K_0;
	
	double M = p4_tot.M();
	// Fill in histogram
        h_invM.Fill(M);
	
	double angle = p4_pi_0.Angle(p4_K_0.Vect());
	// Fill in histogram
	h_angle.Fill(angle);
	
	//detector resolution effects
	double sigma_res= 0.03;
	double p_pi_meas = gen ->Gaus(p4_pi_0.P(), p4_pi_0.P()*sigma_res);
	double p_K_meas = gen ->Gaus(p4_K_0.P(), p4_K_0.P()*sigma_res);
	
	p4_pi_meas.SetPtEtaPhiM(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), m_pi);
	p4_K_meas.SetPtEtaPhiM(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), m_K);
	
	p4_tot=p4_pi_meas+p4_K_meas;
	double M_meas= p4_tot.M();
	// Fill in histogram
        h_measM.Fill(M_meas);	
	
        }
	

  // After generating the data, we take care of plotting the results:
  // * create canvas
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  // * customize some histogram properties
  h_invM.GetXaxis()->SetTitle("invariant mass [GeV]");
  h_invM.GetYaxis()->SetTitle("# events");
  // * plot
  h_invM.Draw();
  // * store to file in pdf format
  canv.SaveAs("./true-mass.pdf");
  
  h_angle.GetXaxis() ->SetTitle("angle between products [rad]");
  h_angle.GetYaxis()->SetTitle("# events");
  h_angle.Draw();
  canv.SaveAs("./opening-angle.pdf");
  
  h_measM.GetXaxis() ->SetTitle("measured mass [GeV]");
  h_measM.GetYaxis()->SetTitle("# events");
  h_measM.Draw("pe");
  canv.SaveAs("./measured-mass.pdf");

  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;

  // Store both histograms to file
  h_invM.Write();
  h_angle.Write();
  h_measM.Write();
   
    // closing the file
    //rfile.Close();
    //exit
    return 0;
}

