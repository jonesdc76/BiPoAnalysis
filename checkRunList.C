{
#include <stdio.h>
  ifstream file("NeutrinoGoodRuns.txt");
  FILE *fmiss = fopen("MissingRuns.txt","w");
  if(fmiss == NULL)cout<<"Error opening file\n";
  gSystem->cd(gSystem->Getenv("BIPO_OUTDIR"));
  gSystem->cd("Phys_Neutrino_v2");
  char dir[255],ser[255], name[255];
  int n = 0;
  while(file.good()&&!file.eof()){
    file.getline(dir, 255, '/');
    file.getline(ser, 255, '/');
    file.getline(name, 255);
    file.peek();
    ifstream f(Form("%s/pass_BiPoNeutrino_v2/%s.root",dir,name));
    if(!f.is_open()){
      cout<<Form("%s/pass_BiPoNeutrino_v2/%s.root",dir,name)<<" NOT found"<<endl;
      fprintf(fmiss, "%s/%s/%s\n",dir,ser,name);
      ++n;
    }
  }
  cout<<n<<" runs not found\n";
  fclose(fmiss);

}
