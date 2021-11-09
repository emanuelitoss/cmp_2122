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
#define sigma_resolution 0.03 //gaussian resolution of detector. This number is the value of std deviation

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

    // The three histograms instances (name, title, number of bins, range)
    int nbins = 100;
    TH1F invariant_m("Invariant Mass", "Distribution of invariant mass of #pi + K after the decay", nbins, 4.5, 6);
    TH1F opening_angle("Opening Angle","Distribution of opening angle between #pi and K in LAB", nbins, 3, 3.2);
    TH1F measured_m("Measured Invariant mass","Distribution of measured invariant mass of #pi + K after the decay", nbins, 4, 12);
// DEFINITION OF 4-VECTORS

    // Create the B meson 4-momentum in the LAB frame
    TLorentzVector p4_B;
    double p_B = 0.300; // GeV
    // Flat metric, (- - - +) signature: m^2 = E^2 - p^2
    p4_B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B*m_B));
    std::cout << "\n>>> Meson B in the lab:" << std::endl;
    p4_B.Print();

    //momentum of generated particles in the CoM system 
    double p_star = sqrt(pow(m_B,4) + pow(m_pi,4) + pow(m_K,4) - 2*pow(m_K,2)*pow(m_pi,2) - 2*pow(m_K,2)*pow(m_B,2) - 2*pow(m_pi,2)*pow(m_B,2) )/(2*m_B);
    std::cout << "\n>>> Value of p* in the ceneter of mass system is:\t" << p_star << std::endl;
    
// RANDOM MOMENTA GENERATION

    std::cout << "\n>>> Generating random sherical distribution for pion and K meson.\nFollows some random samples (in teh LAB reference frame):\n" << std::endl;
    // Start up a new random generator... (we have a new: we will need a delete!)
    TRandom3* gen = new TRandom3();
    // ...exploiting the machine clock for the seed
    gen->SetSeed(0);

    //momentum for the sphere
    double px_star, py_star, pz_star;
    //four momenta of pion and K, and the sum of the two
    TLorentzVector p4_pi_0, p4_K_0, p4_tot;
    //four momenta measured from the detector
    TLorentzVector p4_pi_meas, p4_K_meas;
    //module of the measuren momentum of pion and K
    double p_pi_meas, p_K_meas;
    
    // Loop on the measurements
    for(int i=0; i<Nevents; ++i){

        gen->Sphere(px_star, py_star, pz_star, p_star);
        //Generate values for momentum in random direction in the CoM system:
        p4_pi_0.SetPxPyPzE(px_star, py_star, pz_star, sqrt( pow(p_star,2) + pow(m_pi,2) ));
        p4_K_0.SetPxPyPzE(-px_star, -py_star, -pz_star, sqrt( pow(p_star,2) + pow(m_K,2) ));

        //Boosting these vectors from CoM to LAB frame
        p4_pi_0.Boost( -p4_B.BoostVector() );
        p4_K_0.Boost( -p4_B.BoostVector() );

        //true invariant masses of the two particles
        p4_tot = p4_pi_0 + p4_K_0;
        invariant_m.Fill( p4_tot.M() );

        //opening angle between the two particles
        opening_angle.Fill( p4_K_0.Angle(p4_pi_0.Vect()) );

        //including detector smearing effect. It changes only the 
        p_pi_meas = gen->Gaus(p4_pi_0.P(), p4_pi_0.P()*sigma_resolution);
        p_K_meas = gen->Gaus(p4_K_0.P(), p4_K_0.P()*sigma_resolution);

        //definition of p4_pi_meas and p4_K_meas
        p4_pi_meas.SetPtEtaPhiM(p_pi_meas, p4_pi_0.Eta(), p4_pi_0.Phi(), m_pi);
        p4_K_meas.SetPtEtaPhiM(p_K_meas, p4_K_0.Eta(), p4_K_0.Phi(), m_K);

        //measured invariant masses of the two particles
        p4_tot = p4_pi_meas + p4_K_meas;
        measured_m.Fill(p4_tot.M());

    }

    //aesthetic space
    std::cout << "\n" << std::endl;

//PLOTTING AND SAVING RESULTS

    //set canvas
    TCanvas canv1("canv", "canvas for plotting", 1280, 1280);
    //set axis titles
    invariant_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    invariant_m.GetYaxis()->SetTitle("Number of events");
    //draw and save
    invariant_m.Draw();
    canv1.SaveAs("./true-mass.pdf");
    invariant_m.Write();


    //set canvas
    TCanvas canv2("canv", "canvas for plotting", 1280, 1280);
    //set axis titles
    opening_angle.GetXaxis()->SetTitle("Opening angle [rad]");
    invariant_m.GetYaxis()->SetTitle("Number of events");
    //draw and save
    opening_angle.Draw();
    canv2.SaveAs("./opening-angle.pdf");
    opening_angle.Write();

    //set canvas
    TCanvas canv3("canv", "canvas for plotting", 1280, 1280);
    //set axis titles
    measured_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    measured_m.GetYaxis()->SetTitle("Number of events");
    //draw and save
    measured_m.Draw("pe");
    canv3.SaveAs("./measured-mass.pdf");
    measured_m.Write();

/******************************* NEED TO UNDERSTAND HOW TO SUPERPOSITION TWO PLOT *******************************/
    //set canvas
    TCanvas canv4("canv", "canvas for plotting", 1280, 1280);
    canv4.Divide(1,2);
    //set axis titles
    measured_m.GetXaxis()->SetTitle("Invariant mass for #pi + K [GeV]");
    measured_m.GetYaxis()->SetTitle("Number of events");
    //draw and save
    canv4.cd(1);
    invariant_m.Draw();
    canv4.cd(2);
    measured_m.Draw("pe");
    canv4.SaveAs("./invariant-mass.pdf");

//CLOSING THINGS AND DELETING OBJECTS

    delete gen;

    //closing the file
    rfile.Close();

    //exit
    return 0;
}