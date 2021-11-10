// Standard library header files
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;

// ROOT header files: random numbers, plotting, file storage, special relativity,...
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TStyle.h"
#include "TGaxis.h"

// Two particles decay parameters
// If you want to perform an other experiment, change these quantities
#define m_B 5.279 // Meson mass (GeV)
#define m_pi 0.140 // Pion mass (GeV)
#define m_K 0.500 // Pion mass (GeV)
#define Nevents 10000 // Numebr of random events generated
#define sigma_resolution 0.03 // Gaussian resolution of detector. This number is the value of std deviation

int main(){

//FILE OPENING AND HISTOGRAMS SETTINGS

    // Open TFile for output
    TString rootfname("./output.root");
    // Overwite output file if it already exists
    TFile rfile(rootfname, "RECREATE");
    // Open the ROOT file and make sure the file was opened successfully.
    // Typical cause for failure are: 1) wrong path, 2) no write privilege
    if( !rfile.IsOpen() ) {
        cout << "problems creating root file. existing... " << endl;
        exit(-1);
    }
    cout << "storing output in root file " << rootfname << endl;

    // The three histograms instances (name, title, number of bins, range)
    int nbins = 100;
    TH1F invariant_m("Invariant Mass", "Distribution of invariant mass of #pi + K after the decay", nbins, 4.5, 6);
    TH1F opening_angle("Opening Angle","Distribution of opening angle between #pi and K in LAB", nbins, 3, 3.2);
    TH1F measured_m("Measured Invariant mass","Distribution of measured invariant mass of #pi + K after the decay", nbins, 4, 12);

// DEFINITION OF FOUR MOMENTA

    // Create the B meson 4-momentum in the LAB frame
    TLorentzVector p4_B;
    double p_B = 0.300; // GeV
    // Vector momentum along x axis
    p4_B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B*m_B));
    cout << "\n>>> Meson B in the lab:" << endl;
    p4_B.Print();

    // Momentum of generated particles in the CoM system 
    double p_star = sqrt(pow(m_B,4) + pow(m_pi,4) + pow(m_K,4) - 2*pow(m_K,2)*pow(m_pi,2) - 2*pow(m_K,2)*pow(m_B,2) - 2*pow(m_pi,2)*pow(m_B,2) )/(2*m_B);
    cout << ">>> Value of momentum of produced particles in the ceneter of mass system is\t p* = " << p_star << "\n" << endl;
    
// RANDOM MOMENTA GENERATION

    cout << ">>> Generating random spherical distribution for pion and K meson momenta.\n" << endl;
    // New random generator pointer
    TRandom3* gen = new TRandom3();
    // Exploiting the machine clock for the seed
    gen->SetSeed(0);

    // Momentum coordinates in CoM reference frame.
    // I need them for the function gen->sphere()
    double px_star, py_star, pz_star;
    // True four momenta of pion and K, and the sum of the two
    TLorentzVector p4_pi_0, p4_K_0, p4_tot;
    // Measured four momenta measured from the detector
    TLorentzVector p4_pi_meas, p4_K_meas;
    // Module of the measured momentum of pion and K
    double p_pi_meas, p_K_meas;
    
    // Loop over the events
    for(int i=0; i<Nevents; ++i){

        // Generating random direction of three-momenta in the CoM system
        gen->Sphere(px_star, py_star, pz_star, p_star);
        // Assign momenta to pion and kaon
        p4_pi_0.SetPxPyPzE(px_star, py_star, pz_star, sqrt( pow(p_star,2) + pow(m_pi,2) ));
        p4_K_0.SetPxPyPzE(-px_star, -py_star, -pz_star, sqrt( pow(p_star,2) + pow(m_K,2) ));

        // Boosting these four-vectors from CoM to LAB frame
        p4_pi_0.Boost( -p4_B.BoostVector() );
        p4_K_0.Boost( -p4_B.BoostVector() );

        // Total four-momentum in LAB reference frame
        p4_tot = p4_pi_0 + p4_K_0;
        // Fill the histogram with true invariant mass of the system
        invariant_m.Fill( p4_tot.M() );

        // Fill the 2nd hist with opening angle between the two particles
        opening_angle.Fill( p4_K_0.Angle(p4_pi_0.Vect()) );

        // Including detector resolution
        // It changes only the value of module of momenta, not direction
        p_pi_meas = gen->Gaus(p4_pi_0.P(), p4_pi_0.P()*sigma_resolution);
        p_K_meas = gen->Gaus(p4_K_0.P(), p4_K_0.P()*sigma_resolution);

        // Definitions of measured momenta inf the LAB reference frame
        p4_pi_meas.SetPtEtaPhiM(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), m_pi);
        p4_K_meas.SetPtEtaPhiM(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), m_K);

        // Measured invariant masses of the two particles in LAB, involving smearing effect
        p4_tot = p4_pi_meas + p4_K_meas;
        // Filling the 3rd hist with measured invariant masses
        measured_m.Fill(p4_tot.M());

        /*if (i%1000 == 0){
            # Print something to check the correct behaviour of the program
        }*/

    }

//PLOTTING AND SAVING RESULTS

    // True inavriant mass of the system in the LAB
    // Set canvas
    TCanvas canv1("canv", "canvas for plotting", 1280, 1280);
    // Set axis labels
    invariant_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    invariant_m.GetYaxis()->SetTitle("Number of events");
    // Draw and save
    invariant_m.SetFillColor(kGray+2);
    invariant_m.SetLineColor(kGray+2);
    invariant_m.Draw();
    canv1.SaveAs("./true-mass.pdf");
    invariant_m.Write();

    // Opening angle between pion and kaon in the LAB
    // Set canvas
    TCanvas canv2("canv", "canvas for plotting", 1280, 1280);
    // Set axis labels
    opening_angle.GetXaxis()->SetTitle("Opening angle [rad]");
    opening_angle.GetYaxis()->SetTitle("Number of events");
    // Draw and save
    opening_angle.SetLineColor(kOrange+9);
    opening_angle.SetFillColor(kOrange+6);
    opening_angle.Draw();
    canv2.SaveAs("./opening-angle.pdf");
    opening_angle.Write();

    // Measured invariant mass of the system in the LAB
    // Set canvas
    TCanvas canv3("canv", "canvas for plotting", 1280, 1280);
    // Set axis labels
    measured_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    measured_m.GetYaxis()->SetTitle("Number of events");
    // Draw and save
    measured_m.SetLineColor(kGreen+3);
    measured_m.Draw("pe");
    canv3.SaveAs("./measured-mass.pdf");
    measured_m.Write();

/******************************* NEED TO UNDERSTAND HOW TO SUPERPOSE TWO PLOTS *******************************/
/*
    // True and measured invariant mass of the system in LAB in one graph
    // Set canvas
    TCanvas canv4("canv", "canvas for plotting", 1280, 1280);
    // Split the pdf into two parts
    canv4.Divide(1,2);
    // Set axis labels
    measured_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    measured_m.GetYaxis()->SetTitle("Number of events");
    // Draw first plot
    canv4.cd(1);
    invariant_m.Draw();
    // Draw second plot
    canv4.cd(2);
    measured_m.Draw("pe");
    // Save
    canv4.SaveAs("./invariant-mass.pdf");
*/

    TCanvas *canv4 = new TCanvas("canv4","canvas for two hists", 1280, 1280);
    gStyle->SetOptStat(kFALSE);
    invariant_m.Draw();
    canv4->Update();
    canv4->SaveAs("./invariant-mass.pdf");

//CLOSING THINGS AND DELETING OBJECTS

    delete gen;

    //closing the file
    rfile.Close();

    //exit
    return 0;
}