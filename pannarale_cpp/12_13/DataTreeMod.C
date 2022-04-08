#define DataTree_cxx
#include "DataTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>

void DataTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L DataTree.C
//      root> DataTree t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // Create a new TFile to store output:
   // this is different from the file storing the input data
   TString rootoutfname("./analysis.root");
   TFile outfile(rootoutfname, "RECREATE");

   // Book histograms
   TH1F  hx("hx","distribution of all x", 50, 0.4, 1.8);
   TH1F  hxmean("hxmean","distribution of average x per experiment", 50, 0.9, 1.1);
   TH1F  hdx("hdx","distribution of all \\deltax", 50, 0., 0.1);
   TH1F  hdxstdev("hdxstdev","distribution of Std. Dev of \\deltax per experiment", 50, 0., 0.01);
   TH1F  hxSmalldx("hxSmalldx","distribution of all x with small errors", 100, 0.5, 2.5);
   TH2F  hdxvsxall("hdxvsxall", "\\deltax vs x",50, 0.4, 1.8, 50, 0., 0.1 );

   // Loop over events in the tree
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries; jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // ---- Add your code here to do analysis with data in the Tree
      if(jentry%5==0) std::cout << "processing event: " << jentry << std::endl;

      // Reset histograms to compute mean and std Dev
      //hx->Clear();
      hx.Clear();
      hdx.Clear();

      // Loop over measurements in this event
      for(int im=0; im < nmeas; im++) {
        // Fill histos to compute mean and stdev for each experiment/event
        //hx->Fill(value[im]);
        hx.Fill(value[im]);
        hdx.Fill(error[im]);
        hdxvsxall.Fill(value[im], error[im]);

        // Only plot value for small errors
        if(error[im]<0.05) hxSmalldx.Fill(value[im]);
      }

      // Fill histo with info for each event/experiment
      hxmean.Fill(hx.GetMean());
      hdxstdev.Fill(hdx.GetStdDev());

      // --- End of analysis code
   } // End of event Loop

   // Make newplots
   TCanvas* c1 = new TCanvas("c1","canvas", 1280,1024);
   c1->Divide(2,2);
   gStyle->SetOptStat(111111);

   c1->cd(1);
   hxmean.Draw();
   
   c1->cd(2);
   hdxstdev.Draw();

   c1->cd(3);
   hxSmalldx.Draw();

   c1->cd(4);
   hdxvsxall.Draw("colz3");

   c1->SaveAs("./analysisPlots.pdf");

  // Write objects to output file
  hxmean.Write();
  hdxstdev.Write();
  hxSmalldx.Write();
  hdxvsxall.Write();
  c1->Write();

  // Close outout file
  outfile.Close();
  std::cout << "Done writing to " << rootoutfname << std::endl;

}
