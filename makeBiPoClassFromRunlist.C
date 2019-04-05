#include "TChain.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>

int makeBiPoClassFromRunlist(const char *fname="2018C_GoodRuns.txt", const char* TFilename = "AD1_BiPo_wDT.root", const char* release = "Analyzed_2018C"){
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
    TString st = Form("%s/%s/%s/%s",gSystem->Getenv("BIPO_OUTDIR"), release, line.data(), TFilename);
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
