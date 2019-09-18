#include "TString.h"
#include "TChain.h"
#include "TSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int makeBiPoSimClassFromRunlist(const char *fname="2019B_GoodRuns.txt", const char* TFilename = "AD1_BiPo.root", const char* release = "2019B"){
  std::ifstream file;
  file.open(fname, std::ifstream::in);
  if(!(file.is_open()&&file.good())){
    printf("Good runs file not found. Exiting\n");
    return -1;
  }
  TChain *ch = new TChain("BiPoTreePlugin/BiPo");
  while(file.good()&!file.eof()){
    string line, fname;
    getline(file, line);
    stringstream ss(line);
    TString st;
    while(getline(ss, fname,'/'))
      st = Form("%s/simulation/%s/AD_Bi214_%s/%s",gSystem->Getenv("BIPO_OUTDIR"), release, fname.data(), TFilename);
    //printf("%s\n", st.Data());
    ch->Add(st.Data());
    file.peek();
  }
  int nadded = ch->GetListOfFiles()->GetEntries();
  ch->Lookup(1);
  int nmissing = nadded - ch->GetListOfFiles()->GetEntries();
  cout<<"Attempted to add "<<nadded<<" files from good runs list to TChain\n";
  cout<<"Removed "<<nmissing<<" missing files from TChain for total of "<<nadded-nmissing<<" files in TChain \n";
  ch->MakeClass("BPsim");
  gSystem->Exec("./editBiPoSimClass.sh");
  return 0;
}
