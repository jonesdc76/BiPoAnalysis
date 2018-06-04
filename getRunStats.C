{
#include <time.h>

  cout<<"Did you load/compile BP.C?"<<endl;
  BP *bp = new BP();
  TChain *ch = bp->chain;
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  TString st, prev_st = "";
  double tlive = 0, tl = 0;
  bool first = 1, first_of_dataset = 1;
  const int N=6;
  int n = 0;
  time_t ts1, ts2, prev_ts = 0;
  TString data[N] = {"WetCommissioning", "180316_Background",  "180417_Background","180420_Background","180501_ReactorOn","180520_Background"};
  while((element = (TChainElement*)next())){
    st = TString(element->GetTitle());
    if(st.Contains(data[n]) && first_of_dataset){
      cout<<"HIIIIII\n\n";
      first_of_dataset = 0;
      ts1 = time_t(TString(st(st.First(".")-10,10)).Atoi());
    }
    if(!st.Contains(data[n])){
      cout<<st.Data()<<"\n"<<prev_st.Data()<<endl<<endl;
      ts2 = prev_ts;
      cout<<"\\item{"<<data[n].Data()<<": "<<Form("%0.3f",difftime(ts2, ts1)/3600.0)<<" hours of data from ";
      printf("%s", asctime(localtime(&ts1)));
      printf("to %s.}\n",asctime(localtime(&ts2)));
      ts1 = time_t(TString(st(st.First(".")-10,10)).Atoi());
      ++n;
    }
    TFile *file = TFile::Open(element->GetTitle());
    tl = ((TVectorD*)file->Get("runtime"))->Norm1();
    tlive += tl;
    if(first){
      first = 0;
      time_t ts = time_t(TString(st(st.First(".")-10,10)).Atoi());
      printf("Date of first file: %s", asctime(localtime(&ts)));
      printf("Date of first file: %s", asctime(localtime(&ts)));
    }
    prev_st = st;
    prev_ts = time_t(TString(st(st.First(".")-10,10)).Atoi());
  }
  time_t ts = time_t(TString(st(st.First(".")-10,10)).Atoi() + tl);
  printf("Date of last file: %s", asctime(localtime(&ts)));
}
