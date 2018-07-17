#include "TChain.h"
#include "TSystem.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

int makeIBDClassFromRunlist(const char *fname="NeutrinoGoodRuns_RxStat.txt", const char* passname = "", const char* release = "Analyzed_NuFact_v1"){
  std::ifstream file;
  file.open(fname, std::ifstream::in);
  if(!(file.is_open()&&file.good())){
    printf("Good runs file not found. Exiting\n");
    return -1;
  }
  TChain *chOn = new TChain("P2kIBDPlugin/Tibd");
  TChain *chOff = new TChain("P2kIBDPlugin/Tibd");
  while(file.good()&!file.eof()){
    string line, dir, status;
    getline(file, line);
    stringstream ss(line);
    getline(ss, dir, ' ');
    getline(ss, status, ' ');
    //cout<<status<<endl;
    TString rel(release);
    TString str = Form("%s/%s/%s/AD1_Wet_Phys%s.root",gSystem->Getenv("BIPO_OUTDIR"), rel.Data(), dir.data(), passname);
    if(stoi(status) == 0) chOff->Add(str.Data());
    else if(stoi(status) == 1) chOn->Add(str.Data());
    else cout<<"Problem. Rx status not 0 or 1\n";
    file.peek();
  }
  int nadded = chOn->GetListOfFiles()->GetEntries();
  chOn->Lookup(1);
  int nmissing = nadded - chOn->GetListOfFiles()->GetEntries();
  cout<<"Attempted to add "<<nadded<<" files from good runs list to Reactor On TChain\n";
  cout<<"Removed "<<nmissing<<" missing files from Reactor On TChain for total of "<<nadded-nmissing<<" files in Reactor On TChain \n";
  nadded = chOff->GetListOfFiles()->GetEntries();
  chOff->Lookup(1);
  nmissing = nadded - chOff->GetListOfFiles()->GetEntries();
  cout<<"Attempted to add "<<nadded<<" files from good runs list to Reactor Off TChain\n";
  cout<<"Removed "<<nmissing<<" missing files from Reactor Off TChain for total of "<<nadded-nmissing<<" files in Reactor Off TChain \n";
  chOn->MakeClass("IBDon");
  chOff->MakeClass("IBDoff");
  gSystem->Exec("./editIBDClass.sh");
  return 0;
}
