{
#include <stdio.h>
  bool bipo = 1;
  const char* pass="";
  ifstream file("NuFactGoodRuns.txt");
  FILE *fmiss = fopen("MissingRuns.txt","w");
  if(fmiss == NULL)cout<<"Error opening file\n";
  gSystem->cd(gSystem->Getenv("BIPO_OUTDIR"));
  gSystem->cd("Analyzed_NuFact_v1");
  char dir[255],ser[255], name[255];
  int notfound = 0, found = 0;
  while(file.good()&&!file.eof()){
    file.getline(dir, 255, '/');
    file.getline(ser, 255, '/');
    file.getline(name, 255);
    file.peek();
    TString st = Form("%s/%s/%s/AD1_Wet_Phys%s.root",dir,ser,name,pass);
    if(bipo) st =  Form("%s/%s/%s/AD1_Extra_Phys.root",dir,ser,name);
    ifstream f(st.Data());
    if(!f.is_open()){
      cout<<st.Data()<<" NOT found"<<endl;
      fprintf(fmiss, "%s/%s/%s\n",dir,ser,name);
      ++notfound;
    }else ++found;
  }
  cout<<found<<" runs found\n";
  cout<<notfound<<" runs not found\n";
  fclose(fmiss);

}
