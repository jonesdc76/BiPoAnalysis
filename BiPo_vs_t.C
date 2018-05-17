{
#include <vector>
  bool fiducialize = 0, newest_release = 1;
  gStyle->SetOptFit(1111);
  gStyle->SetTitleW(0.9);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.04);
  TFile file("Don.root", "RECREATE");
  const double kTimeOn = 83.65*3600, kTimeOff = 75*3600, kRelWindowSize = 119.0/10000.0;
  gStyle->SetOptStat(0);
  TString release("Phys_20180316");
  release = TString("Phys_20180409");
  if(newest_release) release = TString("Phys_20180510");
  TString rxon = TString("WetCommissioning");
  TString rxoff = TString("180316_Background");
  TString pass= TString("pass_BiPo5");
  int length = 1000, width=1900;


  TChain *ch;
  const double tauBiPo = 0.1643/log(2); 
  double f2n = 12;//ratio of lengths of far to near windows
  double tmin = 0.002;//start coincidence window tmin ms away from electron
  gSystem->cd(Form("/home/jonesdc/prospect/Outdir/%s/%s/%s",release.Data(),rxon.Data(), pass.Data()));
  //cout<<Form("../Outdir/%s/%s/%s\n",release.Data(),rxon.Data(), pass.Data());
  ch= new TChain("BiPoTreePlugin/BiPo");
  cout<<ch->Add(Form("s*.root"))<<" Rx on files\n";
  gSystem->cd(Form("/home/jonesdc/prospect/Outdir/%s/%s/%s",release.Data(),rxoff.Data(), pass.Data()));
  cout<<ch->Add(Form("s*.root"))<<" Rx off files\n";
  ch->SetAlias(Form("(ft-%f)/%f",10*tauBiPo,f2n),"tacc");

  // std::vector<double> *pz;
  // std::vector<int> *pseg;
  // int mult_prompt, n=0;
  // ch->SetBranchAddress("pseg", &pseg);
  // ch->SetBranchAddress("mult_prompt",&mult_prompt);
  // ch->SetBranchAddress("pz", &pz);
  // TH1D *h = new TH1D("h","h",220,-1100,1100);
  // for(int i=0;i<ch->GetEntries();++i){
  //   ch->GetEntry(i);
  //   if(mult_prompt==0)continue;
  //   for(UInt_t j=0;j<pseg->size();++j){
  //     h->Fill(pz->at(j));
  //     //      cout<<i<<" "<<mult_prompt<<" "<<pseg->size()<<endl;
  //   }
  // }
  // cout<<n<<endl;
  // h->SetLineColor(kRed);
  // h->Draw();
  // ch->Draw("pz","mult_prompt>0","sames");

  double hAE = 0.99, lAE = 0.8, hApsd = 0.31, lApsd = 0.2;
  if(release.Contains("0409")){
    hAE -= 0.03;
    lAE -= 0.03;
    lApsd = 0.22;
  }


  ///////////////////////////////////////////
  //Define cuts
  double lpE = 0.8, hppsd = 0.26, lppsd = 0;
  TCut cutaz("abs(az)<1000");//("abs(az)<460");
  TCut cutafid("aseg>13 && aseg<140 && aseg%14 != 0&&aseg%14 != 13");
  TCut cutpPSD(Form("pPSD>%f&&pPSD<%f", lppsd, hppsd));
  TCut cutpz("abs(pz)<1000");
  TCut cutfPSD(Form("fPSD>%f&&fPSD<%f", lppsd, hppsd));
  TCut cutfz("abs(fz)<1000");
  TCut cuta(Form("aPSD>%f&&aPSD<%f&&aE>%f&&aE<%f", lApsd, hApsd, lAE, hAE));
  cuta += cutaz;
  if(fiducialize)
    cuta+=cutafid;
  TCut cutp(Form("pseg>=0&&at-pt>%f", tmin));
  cutp += cutpPSD;
  cutp += cutpz;
  TCut cutf(Form("fseg>=0&&(ft-at-%f)/%f>%f", 10*tauBiPo, f2n, tmin));
  cutf += cutfPSD;
  cutf += cutfz;
  ///////////////////////////////////////////


  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  TChain *cht[100];
  double t[100], terr[100], t0 = 0, tlive[100];
  for(int i=0;i<100;++i){
    t[i] = 0;
    tlive[i] = 0;
    terr[i] = 0;
    cht[i] = new TChain("BiPoTreePlugin/BiPo");
  }
  int nTr=0;
  bool isFirst = true;
  const double nhr = 24;
  double tot_live = 0;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    //cout<<file->GetName()<<endl;
    TString st(file->GetName());
    //cout<<st(st.First(".")-10, 10)<<endl;
    double ts = TString(st(st.First(".")-10,10)).Atof();
    ts /= 3600.0;
    double rt = ((TVectorD*)file->Get("runtime"))->Norm1();
    rt /= 3600.0;
    cout<<"rt "<<rt<<endl;
    if(rt>1e6)continue;
    if(isFirst){
      t0 = ts;
      isFirst = false;
    }
    if(!file->IsZombie()){
      cht[nTr]->Add(file->GetName());
      t[nTr] += (ts-t0+rt/2.0)*rt;
      tlive[nTr] += rt;
      tot_live += rt;
    }
    if(tlive[nTr]>nhr&&tlive[nTr]>0){
      cout<<"Time: "<<t[nTr]/tlive[nTr]<<" Live: "<<tlive[nTr]<<endl;
      ++nTr;
    }
  }
  cout<<"Time: "<<t[nTr]/tlive[nTr]<<" Live: "<<tlive[nTr]<<endl;
  ++nTr;
  cout<<nTr<<endl;
  cout<<"Total live time "<<tot_live<<endl;
  vector<double>RvT, EvT, WvT, PSDvT, PSDWvT, RvTerr, EvTerr, WvTerr, PSDvTerr, PSDWvTerr;
  for(int i=0;i<nTr;++i){
    t[i] /= tlive[i];
    ///////////////////////////////////////
    //Alpha Energy, Width and Rate
    cht[i]->Draw(Form("aE-pE*0>>hAlphaE%i(36,0.7,1.06)",i),cuta && cutp,"goff");
    TH1D *hAlphaE = (TH1D*)gDirectory->Get(Form("hAlphaE%i",i));
    cht[i]->Draw(Form("aE-fE*0>>hAlphafE%i(36,0.7,1.06)",i),cuta && cutf,"goff");
    TH1D *hAlphafE = (TH1D*)gDirectory->Get(Form("hAlphafE%i",i));
    hAlphafE->Scale(1/f2n);
    TH1D *hFinAE = (TH1D*)hAlphaE->Clone("hFinAE");
    hFinAE->Add(hAlphafE,-1);
    for(int i=0;i<hFinAE->GetNbinsX();++i){
      double var = pow(hAlphafE->GetBinError(i),2);
      var += pow(hAlphaE->GetBinError(i),2);
      hFinAE->SetBinError(i, sqrt(var));
    }
    hFinAE->Draw();
    gPad->Update();

    TF1 fg("fg","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",lAE,hAE);
    fg.SetParNames("A","#bar{E} (MeV)","#sigma");
    fg.SetParameters(hFinAE->GetEntries()/100.0,0.87,0.044);
    hFinAE->Fit("fg","r");
    gPad->Update();
    double A = fg.GetParameter(0);
    double E = fg.GetParameter(1);
    double sig = fg.GetParameter(2);
    double Aerr = fg.GetParError(0);
    double Eerr = fg.GetParError(1);
    double sigerr = fg.GetParError(2);
    RvT.push_back(hFinAE->GetEntries()/tlive[i]);
    RvTerr.push_back(RvT.back()/sqrt(hFinAE->GetEntries()));
    EvT.push_back(E);
    EvTerr.push_back(Eerr);
    WvT.push_back(sig);
    WvTerr.push_back(sigerr);

    ///////////////////////////////////////
    //Alpha PSD
    cht[i]->Draw(Form("aPSD>>hpsd%i(20,%f,%f)",i,lApsd,hApsd),cuta && cutp,"goff");
    TH1D *hpsd = (TH1D*)gDirectory->Get(Form("hpsd%i",i));
    cht[i]->Draw(Form("aPSD>>hpsdf%i(20,%f,%f)",i,lApsd,hApsd),cuta && cutf,"goff");
    TH1D *hpsdf = (TH1D*)gDirectory->Get(Form("hpsdf%i",i));
    hpsdf->Scale(1/f2n);
    TH1D *hFinPSD = (TH1D*)hpsd->Clone("hFinPSD");
    hFinPSD->Add(hpsdf,-1);
    for(int i=0;i<hFinPSD->GetNbinsX();++i){
      double var = pow(hpsd->GetBinError(i),2);
      var += pow(hpsdf->GetBinError(i),2);
      hFinPSD->SetBinError(i, sqrt(var));
    }
    hFinPSD->Draw();
    gPad->Update();

    TF1 fg1("fg1","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))", lApsd, hApsd);
    fg1.SetParNames("A","Mean PSD","#sigma");
    fg1.SetParameters(hFinPSD->GetEntries()/100.0, 0.27, 0.0175);
    hFinPSD->Fit("fg1", "r");
    gPad->Update();
    A = fg1.GetParameter(0);
    double M = fg1.GetParameter(1);
    sig = fg1.GetParameter(2);
    Aerr = fg1.GetParError(0);
    double Merr = fg1.GetParError(1);
    sigerr = fg1.GetParError(2);
    PSDvT.push_back(M);
    PSDvTerr.push_back(Merr);
    PSDWvT.push_back(sig);
    PSDWvTerr.push_back(sigerr);
  }
  TGraphErrors *grRvT, *grEvT, *grWvT, *grPSDvT, *grPSDWvT;
  TCanvas *c1 = new TCanvas("c1","c1",0,0,900,700);

  grRvT = new TGraphErrors(nTr, t, &RvT[0], terr, &RvTerr[0]);
  grRvT->SetMarkerStyle(8);
  grRvT->SetMarkerColor(kBlue);
  grRvT->SetLineColor(kBlue);
  grRvT->SetTitle("BiPo Rate in AD versus Time");
  grRvT->Draw("ap");
  grRvT->GetXaxis()->SetTitle("Hours Since Mar. 5, 2018 8:36");
  grRvT->GetYaxis()->SetTitle("BiPo Rate (Counts per hour)");
  gPad->Update();
  TCanvas *c2 = new TCanvas("c2","c2",0,0,1200,650);
  c2->Divide(2,1);

  c2->cd(1);
  grEvT = new TGraphErrors(nTr, t, &EvT[0], terr, &EvTerr[0]);
  grEvT->SetMarkerStyle(8);
  grEvT->SetMarkerColor(kBlue);
  grEvT->SetLineColor(kBlue);
  grEvT->SetTitle("BiPo Alpha Energy Distribution Mean versus Time");
  grEvT->Draw("ap");
  grEvT->GetXaxis()->SetTitle("Hours Since Mar. 5, 2018 8:36");
  grEvT->GetYaxis()->SetTitle("E_{#alpha} (MeV)");
  grEvT->Fit("pol0");
  c2->cd(2);
  grWvT = new TGraphErrors(nTr, t, &WvT[0], terr, &WvTerr[0]);
  grWvT->SetMarkerStyle(8);
  grWvT->SetMarkerColor(kBlue);
  grWvT->SetLineColor(kBlue);
  grWvT->SetTitle("BiPo Alpha Energy Distribution Width versus Time");
  grWvT->Draw("ap");
  grWvT->GetXaxis()->SetTitle("Hours Since Mar. 5, 2018 8:36");
  grWvT->GetYaxis()->SetTitle("Peak Width (MeV)");
  grWvT->Fit("pol0");
  gPad->Update();
  TCanvas *c3 = new TCanvas("c3","c3",0,0,1200,650);
  c3->Divide(2,1);  
  c3->cd(1);
  grPSDvT = new TGraphErrors(nTr, t, &PSDvT[0], terr, &PSDvTerr[0]);
  grPSDvT->SetMarkerStyle(8);
  grPSDvT->SetMarkerColor(kBlue);
  grPSDvT->SetLineColor(kBlue);
  grPSDvT->SetTitle("BiPo Alpha PSD Distribution Mean versus Time");
  grPSDvT->Draw("ap");
  grPSDvT->GetXaxis()->SetTitle("Hours Since Mar. 5, 2018 8:36");
  grPSDvT->GetYaxis()->SetTitle("PSD Mean");
  grPSDvT->Fit("pol1");
  
  c3->cd(2);
  grPSDWvT = new TGraphErrors(nTr, t, &PSDWvT[0], terr, &PSDWvTerr[0]);
  grPSDWvT->SetMarkerStyle(8);
  grPSDWvT->SetMarkerColor(kBlue);
  grPSDWvT->SetLineColor(kBlue);
  grPSDWvT->SetTitle("BiPo Alpha PSD Distribution Width versus Time");
  grPSDWvT->Draw("ap");
  grPSDWvT->GetXaxis()->SetTitle("Hours Since Mar. 5, 2018 8:36");
  grPSDWvT->GetYaxis()->SetTitle("PSD Width");
  grPSDWvT->Fit("pol1");
  gPad->Update();
  if(fiducialize){
    c1->SaveAs(Form("/Users/jonesdc76/prospect/plots/%s_BiPoRatevsT_fid.png",release.Data()));
    c2->SaveAs(Form("/Users/jonesdc76/prospect/plots/%s_BiPoEvsT_fid.png",release.Data()));
    c3->SaveAs(Form("/Users/jonesdc76/prospect/plots/%s_BiPoPSDvsT_fid.png",release.Data()));
  }else{
    c1->SaveAs(Form("/Users/jonesdc76/prospect/plots/%s_BiPoRatevsT.png",release.Data()));
    c2->SaveAs(Form("/Users/jonesdc76/prospect/plots/%s_BiPoEvsT.png",release.Data()));
    c3->SaveAs(Form("/Users/jonesdc76/prospect/plots/%s_BiPoPSDvsT.png",release.Data()));
  }


}
