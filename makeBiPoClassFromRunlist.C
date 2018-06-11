#include "TChain.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>

int makeBiPoClassFromRunlist(const char *fname="NeutrinoGoodRuns.txt", const char* passname = "_BiPoNeutrino_v2", const char* release = "Phys_Neutrino_v2"){
  std::ifstream file;
  file.open(fname, std::ifstream::in);
  if(!(file.is_open()&&file.good())){
    printf("Good runs file not found. Exiting\n");
    return -1;
  }
  TChain *ch = new TChain("BiPoTreePlugin/BiPo");
  while(file.good()&!file.eof()){
    string line;
    getline(file, line);
    TString st = Form("%s/%s/%s/AD1_Wet_Phys%s.root",gSystem->Getenv("BIPO_OUTDIR"), release, line.data(), passname);
    //printf("%s", st.Data());
    ch->Add(st.Data());
    file.peek();
  }
  int nadded = ch->GetListOfFiles()->GetEntries();
  ch->Lookup(1);
  int nmissing = nadded - ch->GetListOfFiles()->GetEntries();
  cout<<"Attempted to add "<<nadded<<" files from good runs list to TChain\n";
  cout<<"Removed "<<nmissing<<" missing files from TChain for total of "<<nadded-nmissing<<" files in TChain \n";
  ch->MakeClass("BP");
  gSystem->Exec("./editBiPoClass.sh");
  return 0;
}
