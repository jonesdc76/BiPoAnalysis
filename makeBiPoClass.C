#include "TChain.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include <iostream>

int makeBiPoClass(TString pass = "BiPoNeutrino_v2", TString release = "Phys_Neutrino_v2"){
  TChain *ch = new TChain("BiPoTreePlugin/BiPo");
  cout<<ch->Add(Form("%s/%s/WetCommissioning/pass_%s/*.root",gSystem->Getenv("BIPO_OUTDIR"),release.Data(),pass.Data()))<<" files added from WetCommissioining\n";
  cout<<ch->Add(Form("%s/%s/180316_Background/pass_%s/*.root",gSystem->Getenv("BIPO_OUTDIR"),release.Data(),pass.Data()))<<" files added from 180316_Background\n";
  cout<<ch->Add(Form("%s/%s/180417_Background/pass_%s/*.root",gSystem->Getenv("BIPO_OUTDIR"),release.Data(),pass.Data()))<<" files added from 180417_Background\n";
  cout<<ch->Add(Form("%s/%s/180420_Background/pass_%s/*.root",gSystem->Getenv("BIPO_OUTDIR"),release.Data(),pass.Data()))<<" files added from 180420_Background\n";
  cout<<ch->Add(Form("%s/%s/180501_ReactorOn/pass_%s/*.root",gSystem->Getenv("BIPO_OUTDIR"),release.Data(),pass.Data()))<<" files added from 180501_ReactorOn\n";
  cout<<ch->Add(Form("%s/%s/180525_Background/pass_%s/*.root",gSystem->Getenv("BIPO_OUTDIR"),release.Data(),pass.Data()))<<" files added from 180501_ReactorOn\n";

  
  ch->MakeClass("BP");
  gSystem->Exec("./editBiPoClass.sh");
  return 0;
}
