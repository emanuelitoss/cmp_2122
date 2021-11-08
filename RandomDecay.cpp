// standard library header files
#include <iostream>
#include <cmath>

// ROOT header files: random numbers, plotting, file storage, special relativity,...
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"

//Some variables
#define m_B 5.279 //Meson mass (GeV)
#define m_pi 0.140 //Pion mass (GeV)
#define m_K 0.500 //Pion mass (GeV)
#define eps 0.0001 //very little value that could be useful
#define Nevents 10000 //numebr of random events generated

int main(){

//FILE OPENING AND HISTOGRAM SETTINGS

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

    // The two histograms instances (name, title, number of bins, range)
    int nbins = 100;
    TH1F invariant_m_pi("invariant_m_pi", "distribution of invariant mass of pion", nbins, 0, 5.279);
    TH1F invariant_m_K("invariant_m_K", "distribution of invariant mass of K", nbins, 0, 5.279);

// RANDOM MOMENTA GENERATION

    // Create the B meson 4-momentum in the LAB frame
    TLorentzVector p4_B;
    double p_B = 0.300; // GeV
    // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
    p4_B.SetPxPyPzE(sqrt(p_B*p_B+m_B*m_B), 0, 0, p_B);
    std::cout << ">>> Meson B in the lab:" << std::endl;
    p4_B.Print();

    //momentum of generated particles in the CoM system 
    double p_star = sqrt((pow(m_B,4) + pow(m_pi,4) + pow(m_K,4) - 2*pow(m_K,2)*pow(m_pi,2) - 2*pow(m_K,2)*pow(m_B,2) - 2*pow(m_pi,2)*pow(m_B,2) ))/(2*m_B);
    std::cout << ">>> Value of p* in the ceneter of mass system is:\t\t" << p_star << std::endl;
    
// RANDOM MOMENTA GENERATION

    std::cout << ">>> Generating random sherical distribution for pion and K meson:" << std::endl;
    
    // Start up a new random generator... (we have a new: we will need a delete!)
    TRandom3* gen = new TRandom3();
    // ...exploiting the machine clock for the seed
    gen->SetSeed(0);

    //local variables
    double px_star, py_star, pz_star;
    TLorentzVector p4_pi;
    TLorentzVector p4_K;

    // Loop on the measurements
    for(int i=0; i<Nevents; ++i){

        gen->Sphere(px_star, py_star, pz_star, p_star);
        if (i%1000 == 0 )std::cout << px_star << "\t" << py_star << "\t" << pz_star << std::endl;
        //Generate values for momentum in random direction in the CoM system:
        p4_pi.SetPxPyPzE(px_star, py_star, pz_star, sqrt(p_star*p_star+m_pi*m_pi));
        p4_K.SetPxPyPzE(-px_star, -py_star, -pz_star, sqrt(p_star*p_star+m_K*m_K));
        //Boosting these vectors from CoM to LAB frame
        p4_pi.Boost(p4_B.BoostVector());
        p4_K.Boost(p4_B.BoostVector());
        //invariant masses of the two particles
        invariant_m_pi.Fill(p4_pi.M());
        invariant_m_K.Fill(p4_K.M());

    }

//PLOTTING RESULTS

    TCanvas canv("canv", "canvas for plotting", 1280, 1024);

    invariant_m_pi.GetXaxis()->SetTitle("Invariant mass for #pi [GeV]");
    invariant_m_K.GetXaxis()->SetTitle("Invariant mass for K [GeV]");

    invariant_m_pi.Draw();
    invariant_m_K.Draw();

    canv.SaveAs("./true-mass.pdf");

//CLOSING THINGS AND DELETING OBJECTS

    delete gen;

    //Writing files
    invariant_m_pi.Write();
    invariant_m_K.Write();

    //closing the file
    rfile.Close();

    //exit
    return 0;
}