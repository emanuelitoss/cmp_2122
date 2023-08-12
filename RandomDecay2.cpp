// Standard cpp library header files
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
using std::cout;
using std::endl;

// ROOT header files: random numbers, plotting, file storage, special relativity,...
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "TTree.h"
#include "TString.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TLegendEntry.h"

// Two particles decay parameters
// If you want to perform other experiments, change these quantities
#define m_B 5.279 // Meson mass (GeV)
#define m_pi 0.140 // Pion mass (GeV)
#define m_K 0.500 // Pion mass (GeV)
#define Nevents 10000 // Numebr of random events generated
#define sigma_resolution 0.03 // Gaussian resolution of detector. This number is the value of std deviation
// three other gaussian resolutions for detector models
#define resolution1 0.01
#define resolution2 0.05
#define resolution3 0.10

int main(){

// FILE OPENING

    // Open TFile for output
    TString rootfname("./output.root");
    // Overwite output file if it already exists
    TFile rfile(rootfname, "RECREATE");
    // Open the ROOT file and make sure the file was opened successfully.
    if( !rfile.IsOpen() ) {
        cout << "problems creating root file. existing... " << endl;
        exit(-1);
    }
    cout << "storing output in root file " << rootfname << endl;

// HISTOGRAMS SETTINGS

    // The three histograms instances (name, title, number of bins, range)
    int nbins = 100;
    TH1F invariant_m("Invariant Mass", "Distribution of invariant mass of #pi + K after the decay", nbins, 2, 8);
    TH1F opening_angle("Opening Angle","Distribution of opening angle between #pi and K in LAB", nbins, 3, 3.2);
    TH1F measured_m("Measured Invariant mass","Distribution of measured invariant mass of #pi + K after the decay", nbins, 2, 8 );
    // Other three histograms for three different resolutions 
    TH1F measured_m_1("Measured Invariant mass (1%)","Distribution of measured invariant mass of #pi + K after the decay", nbins, 2, 8 );
    TH1F measured_m_2("Measured Invariant mass (5%)","Distribution of measured invariant mass of #pi + K after the decay", nbins, 2, 8 );
    TH1F measured_m_3("Measured Invariant mass (10%)","Distribution of measured invariant mass of #pi + K after the decay", nbins, 2, 8 );

// DEFINITION OF PHYSICAL QUANTITIES

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

// TTREE SETTINGS

    TTree* myTree = new TTree("datatree", "tree containing our data");
    myTree->Branch("p_B", &p_B, "momentum of B");
    int nDau = 2;
    double nmass1, nmass2, theta1, theta2, phi1, phi2;
    std::vector<double> p1, p2;
    myTree->Branch("nDau", &nDau, "number of daughters particles");
    myTree->Branch("nmass1", &nmass1, "invariant mass of pion");
    myTree->Branch("nmass2", &nmass2, "invariant mass of kaon");
    myTree->Branch("p1", &p1, "momentum of pion");
    myTree->Branch("p2", &p2, "momentum of kaon");
    myTree->Branch("theta1", &theta1, "theta of pion");
    myTree->Branch("theta2", &theta2, "theta of kaon");
    myTree->Branch("phi1", &phi1, "phi of pion");
    myTree->Branch("phi2", &phi2, "phi of kaon");

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

// RANDOM GENERATOR

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

    // sigma_resolution

        // Including detector resolution
        // It changes only the value of module of momenta, not direction
        p_pi_meas = gen->Gaus(p4_pi_0.P(), p4_pi_0.P()*sigma_resolution);
        p_K_meas = gen->Gaus(p4_K_0.P(), p4_K_0.P()*sigma_resolution);

        // Definitions of measured momenta inf the LAB reference frame
        p4_pi_meas.SetPtEtaPhiE(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), sqrt(m_pi*m_pi + p_pi_meas*p_pi_meas));
        p4_K_meas.SetPtEtaPhiE(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), sqrt(m_K*m_K + p_K_meas*p_K_meas));

        // Measured invariant masses of the two particles in LAB, involving smearing effect
        p4_tot = p4_pi_meas + p4_K_meas;
        // Filling the 3rd hist with measured invariant masses
        measured_m.Fill(p4_tot.M());

        nmass1 = p4_pi_0.M();
        nmass2 = p4_K_0.M();
        //p1 = p_pi_meas;
        //p2 = p_K_meas;
        theta1 = p4_pi_0.Eta();
        theta2 = p4_K_0.Eta();
        phi1 = p4_pi_0.Phi();
        phi2 = p4_K_0.Phi();

    // resolution 1

        // Including detector resolution
        // It changes only the value of module of momenta, not direction
        p_pi_meas = gen->Gaus(p4_pi_0.P(), p4_pi_0.P()*resolution1);
        p_K_meas = gen->Gaus(p4_K_0.P(), p4_K_0.P()*resolution1);

        // Definitions of measured momenta inf the LAB reference frame
        p4_pi_meas.SetPtEtaPhiE(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), sqrt(m_pi*m_pi + p_pi_meas*p_pi_meas));
        p4_K_meas.SetPtEtaPhiE(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), sqrt(m_K*m_K + p_K_meas*p_K_meas));

        // Measured invariant masses of the two particles in LAB, involving smearing effect
        p4_tot = p4_pi_meas + p4_K_meas;
        // Filling hist with measured invariant masses
        measured_m_1.Fill(p4_tot.M());

        p1.push_back(p_pi_meas);
        p2.push_back(p_K_meas);

    //resolution 2

        // Including detector resolution
        // It changes only the value of module of momenta, not direction
        p_pi_meas = gen->Gaus(p4_pi_0.P(), p4_pi_0.P()*resolution2);
        p_K_meas = gen->Gaus(p4_K_0.P(), p4_K_0.P()*resolution2);

        // Definitions of measured momenta inf the LAB reference frame
        p4_pi_meas.SetPtEtaPhiE(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), sqrt(m_pi*m_pi + p_pi_meas*p_pi_meas));
        p4_K_meas.SetPtEtaPhiE(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), sqrt(m_K*m_K + p_K_meas*p_K_meas));

        // Measured invariant masses of the two particles in LAB, involving smearing effect
        p4_tot = p4_pi_meas + p4_K_meas;
        // Filling hist with measured invariant masses
        measured_m_2.Fill(p4_tot.M());

        p1.push_back(p_pi_meas);
        p2.push_back(p_K_meas);
        
    //resolution 3

        // Including detector resolution
        // It changes only the value of module of momenta, not direction
        p_pi_meas = gen->Gaus(p4_pi_0.P(), p4_pi_0.P()*resolution3);
        p_K_meas = gen->Gaus(p4_K_0.P(), p4_K_0.P()*resolution3);

        // Definitions of measured momenta inf the LAB reference frame
        p4_pi_meas.SetPtEtaPhiE(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), sqrt(m_pi*m_pi + p_pi_meas*p_pi_meas));
        p4_K_meas.SetPtEtaPhiE(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), sqrt(m_K*m_K + p_K_meas*p_K_meas));

        // Measured invariant masses of the two particles in LAB, involving smearing effect
        p4_tot = p4_pi_meas + p4_K_meas;
        // Filling hist with measured invariant masses
        measured_m_3.Fill(p4_tot.M());

        p1.push_back(p_pi_meas);
        p2.push_back(p_K_meas);

        myTree -> Fill();

        p1.clear();
        p2.clear();

    }

//PLOTTING AND SAVING RESULTS

    // Set canvas for plotting
    TCanvas canv1("canv", "canvas for plotting", 1500, 1280);
    
    // True inavriant mass of the system in the LAB
    // Set axis labels
    invariant_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    invariant_m.GetYaxis()->SetTitle("Number of events");
    // Draw and save
    invariant_m.SetFillColor(kGray+2);
    invariant_m.SetLineColor(kGray+2);
    invariant_m.Draw();
    canv1.SaveAs("./true-mass.pdf");

    // Opening angle between pion and kaon in the LAB
    // Set axis labels
    opening_angle.GetXaxis()->SetTitle("Opening angle [rad]");
    opening_angle.GetYaxis()->SetTitle("Number of events");
    // Draw and save
    opening_angle.SetLineColor(kOrange+9);
    opening_angle.SetFillColor(kOrange+6);
    opening_angle.Draw();
    canv1.SaveAs("./opening-angle.pdf");

    // Measured invariant mass of the system in the LAB
    // Set axis labels
    measured_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    measured_m.GetYaxis()->SetTitle("Number of events");
    // Draw and save
    measured_m.SetLineColor(kGreen+3);
    measured_m.Draw("pe");
    canv1.SaveAs("./measured-mass.pdf");

    //Measured and true masses in a single plot
    TCanvas *c1 = new TCanvas("c1","true and measured mass [GeV]",600,400);
    invariant_m.Draw();
    // overwriting the second plot
    c1->Update();
    measured_m.SetLineColor(kGreen+3);
    measured_m.Draw("pe""same");
    c1->SaveAs("./invariant-mass.pdf");

    // invariant masses with three different resolutions
    TCanvas *c2 = new TCanvas("c2","measured masses [GeV]",600,400);
    // removing Canva legend
    gStyle->SetOptStat(0);
    measured_m_1.SetLineColor(kGreen+3);
    measured_m_1.Draw();
    c2->Update();
    measured_m_2.SetLineColor(kRed+2);
    measured_m_2.Draw("same");
    c2->Update();
    measured_m_3.SetLineColor(kBlue+2);
    measured_m_3.Draw("same");
    // legend options
    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->SetHeader("Measured masses:","C"); // option "C" allows to center the header
    legend->AddEntry(&measured_m_1,"Resolution of 1%","f");
    legend->AddEntry(&measured_m_2,"Resolution of 5%","f");
    legend->AddEntry(&measured_m_3,"Resolution of 10%","f");
    legend->Draw();
    // saving plot
    c2->SaveAs("./measured-masses.pdf");

//CLOSING THINGS AND DELETING OBJECTS

    // end of the TTree
    myTree->Write();
    myTree->Print();

    // deleting pointers
    delete c1;
    delete c2;
    delete legend;
    delete gen;

    //closing the output root file
    rfile.Close();

    //exit
    return 0;
}
