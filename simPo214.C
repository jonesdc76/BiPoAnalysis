#include "TChain.h"
#include "TH1D.h"
#include "TFile.h"
#include "BPsim.C"

int simPo214(){
  BPsim *bps = new BPsim();
  TChain *ch = bps->chain;

  ch->Draw("pEtot>>h(100,0,4)");
  TH1D *h = (TH1D*)gDirectory->Get("h");
  h->SetName("hSimBetaBi214");
  TFile f("SimPo214BetaSpectrum.root","recreate");
  h->GetXaxis()->SetTitle("AD Full Detector Po214 #beta Energy Spectrum");
  h->GetXaxis()->SetTitle("#beta Energy (MeV)");
  h->GetYaxis()->SetTitle("Counts (a.u.)");
  h->Write();
  ch->Draw("pE>>h76(100,0,4)","pseg==76");
  TH1D *h76 = (TH1D*)gDirectory->Get("h76");
  h76->GetXaxis()->SetTitle("Segment 76 Single Cell Po214 #beta Energy Spectrum");
  h76->GetXaxis()->SetTitle("#beta Energy (MeV)");
  h76->GetYaxis()->SetTitle("Counts (a.u.)");
  h76->SetName("hCell76SimBetaBi214");
  h76->Write();
  return 0;
  //f.Close();
}
