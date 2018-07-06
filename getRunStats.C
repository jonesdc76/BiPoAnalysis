#include <iostream>
#include <time.h>
#include "BP.C"
#include "TChainElement.h"
#include "TString.h"
#include "TFile.h"
#include "TVectorD.h"

int getRunStats(){  
  BP *bp = new BP();
  TChain *ch = bp->chain;
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  TString st, prev_st = "";
  double tlive = 0, tl = 0, prev_rt = 0, prev_tlive = 0;
  bool first = 1, first_of_dataset = 1;
  const int N=6;
  int n = 0;
  time_t ts1, ts2, prev_ts = 0;
  TString month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
  TString week[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  TString data[N] = {"WetCommissioning", "180316_Background",  "180417_Background","180420_Background","180501_ReactorOn","180520_Background"};
  while((element = (TChainElement*)next())){
    st = TString(element->GetTitle());
    if(st.Contains(data[n]) && first_of_dataset){
      first_of_dataset = 0;
      ts1 = time_t(TString(st(st.Last('/')-10,10)).Atoi());
    }
    if((!st.Contains(data[n])) && n < N-1){
      //ut<<st.Data()<<"\n"<<prev_st.Data()<<endl<<endl;
      ts2 = prev_ts + tl;
      cout<<"\\item{"<<data[n].ReplaceAll("_","\\_")<<": "<<Form("%0.3f", (tlive-prev_tlive)/3600.0)<<" hours of data between ";
      auto t = localtime(&ts1);
      printf("%s %s %i, %i %02i:%02i", week[t->tm_wday].Data(), month[t->tm_mon].Data(), t->tm_mday, t->tm_year+1900, t->tm_hour, t->tm_min);
      t = localtime(&ts2);
      printf(" and %s %s %i, %i %02i:%02i}\n", week[t->tm_wday].Data(), month[t->tm_mon].Data(), t->tm_mday, t->tm_year+1900, t->tm_hour, t->tm_min);
      ts1 = time_t(TString(st(st.Last('/')-10,10)).Atoi());
      prev_tlive = tlive;
      ++n;
    }
    TFile *file = TFile::Open(st);
    tl = ((TVectorD*)file->Get("runtime"))->Norm1();
    tlive += tl;
    if(first){
      first = 0;
      time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi());
      printf("Start time of first file: %s", asctime(localtime(&ts)));
    }
    prev_st = st;
    prev_ts = time_t(TString(st(st.Last('/')-10,10)).Atoi());
  }
  time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi() + tl);
  cout<<"\\item{"<<data[n].ReplaceAll("_","\\_")<<": "<<Form("%0.3f",(tlive-prev_tlive)/3600.0)<<" hours of data between ";
  auto t = localtime(&ts1);
  printf("%s %s %i, %i %02i:%02i", week[t->tm_wday].Data(), month[t->tm_mon].Data(), t->tm_mday, t->tm_year+1900, t->tm_hour, t->tm_min);
  t = localtime(&ts);
  printf(" and %s %s %i, %i %02i:%02i}\n", week[t->tm_wday].Data(), month[t->tm_mon].Data(), t->tm_mday, t->tm_year+1900, t->tm_hour, t->tm_min);
  printf("End time of last file: %s", asctime(localtime(&ts)));
  cout<<"Total hours of data: "<<tlive/3600.0<<"\n";
  
  return 0;
}
