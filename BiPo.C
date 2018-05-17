{
#include <vector>
  bool fiducialize = 0, new_release = 1;
  gStyle->SetOptFit(1111);
  gStyle->SetTitleW(0.9);
  //  gStyle->SetPadLeftMargin(0.12);
  //  gStyle->SetPadRightMargin(0.04);
  TFile file("Don.root", "RECREATE");
  const double kTimeOn = 83.65*3600, kTimeOff = 75*3600, kRelWindowSize = 119.0/10000.0;
  gStyle->SetOptStat(0);
  TString release("Phys_20180316");
  if(new_release) release = TString("Phys_20180409");
  TString rxon = TString("WetCommissioning");
  TString rxoff = TString("180316_Background");
  TString pass= TString("pass_BiPo4");
  int length = 1000, width=1900;


  TCanvas *c1 = new TCanvas("c1","c1",0,0,width,length);
  c1->Divide(3,2);
  TChain *ch;
  const double tauBiPo = 0.1643/log(2); 
  double f2n = 12;//ratio of lengths of far to near windows
  double tmin = 0.002;//start coincidence window tmin ms away from electron
  gSystem->cd(Form("/home/jonesdc/prospect/Outdir/%s/%s/%s",release.Data(),rxon.Data(), pass.Data()));
  cout<<Form("/home/jonesdc/prospect/Outdir/%s/%s/%s\n",release.Data(),rxon.Data(), pass.Data());
  ch= new TChain("BiPoTreePlugin/BiPo");
  cout<<ch->Add(Form("s*.root"))<<" Rx on files\n";
  gSystem->cd(Form("/home/jonesdc/prospect/Outdir/%s/%s/%s",release.Data(),rxoff.Data(), pass.Data()));
  cout<<Form("/home/jonesdc/prospect/Outdir/%s/%s/%s\n",release.Data(),rxoff.Data(), pass.Data());
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
  double hppsd = 0.26, lppsd = 0;
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
  //  TCut cutp(Form("pseg>=0&&at-pt>%f&&(pseg%14==0||pseg%14==13||pseg<14||pseg>140)", tmin));
  TCut cutp(Form("pseg>=0&&at-pt>%f", tmin));
  cutp += cutpPSD;
  cutp += cutpz;
  //  TCut cutf(Form("fseg>=0&&(ft-at-%f)/%f>%f&&(fseg%14==0||fseg%14==13||fseg<14||fseg>140)", 10*tauBiPo, f2n, tmin));
  TCut cutf(Form("fseg>=0&&(ft-at-%f)/%f>%f", 10*tauBiPo, f2n, tmin));
  cutf += cutfPSD;
  cutf += cutfz;
  ///////////////////////////////////////////

  
  c1->cd(1);
  ch->Draw("pPSD:pE>>hppsdE(100,0,4,100)","pseg>=0&&pPSD>-25&&pPSD<25","colz");
  TH2D *hppsdE = (TH2D*)gDirectory->Get("hppsdE");
  hppsdE->GetXaxis()->SetTitle("Prompt E (MeV)");
  hppsdE->GetYaxis()->SetTitle("Prompt PSD");
  hppsdE->SetTitle("Prompt PSD versus Energy");
  c1->cd(2);
  ch->Draw("pPSD:pE>>hppsdEz(100,0,4,100,-0.1,1)","pseg>=0&&pPSD>-0.1&&pPSD<1","colz");
  TH2D *hppsdEz = (TH2D*)gDirectory->Get("hppsdEz");
  hppsdEz->GetXaxis()->SetTitle("Prompt E (MeV)");
  hppsdEz->GetYaxis()->SetTitle("Prompt PSD");
  hppsdEz->SetTitle("Prompt PSD versus Energy");
  TLine *linpPSD[2];
  linpPSD[0] = new TLine(0,lppsd,4,lppsd);
  linpPSD[0]->SetLineColor(kRed);
  linpPSD[0]->Draw();
  linpPSD[1] = new TLine(0,hppsd,4,hppsd);
  linpPSD[1]->SetLineColor(kRed);
  linpPSD[1]->Draw();

  c1->cd(3);
  ch->Draw("aPSD:aE>>hE(100,0.65,1.1,100,0.15,0.45)", cutp,"colz");
  TH2D *hE = (TH2D*)gDirectory->Get("hE");
  hE->SetTitle("PSD vs Energy for Alpha Candidate");
  hE->GetYaxis()->SetTitle("#alpha PSD");
  hE->GetXaxis()->SetTitle("Energy (MeV)");
  TLine *lpsd[4], *lE[2];
  lpsd[0] = new TLine(lAE,lApsd,hAE,lApsd);
  lpsd[0]->SetLineColor(kRed);
  lpsd[0]->Draw();
  lpsd[1] = new TLine(lAE,hApsd,hAE,hApsd);
  lpsd[1]->SetLineColor(kRed);
  lpsd[1]->Draw();
  lE[0] = new TLine(lAE,lApsd,lAE,hApsd);
  lE[0]->SetLineColor(kRed);
  lE[0]->Draw();
  lE[1] = new TLine(hAE,lApsd,hAE,hApsd);
  lE[1]->SetLineColor(kRed);
  lE[1]->Draw();
  gPad->Update();


  c1->cd(4);
  ch->Draw("aPSD:az>>hp(100,-1100,1100,100,0.15,0.42)", cutp, "colz");
  TH2D *hp = (TH2D*)gDirectory->Get("hp");
  hp->SetTitle("PSD vs Position for Alpha Candidate");
  hp->GetYaxis()->SetTitle("#alpha PSD");
  hp->GetXaxis()->SetTitle("Position (mm)");
  lpsd[2] = new TLine(-1100, lApsd, 1100, lApsd);
  lpsd[2]->SetLineColor(kRed);
  lpsd[2]->Draw();
  lpsd[3] = new TLine(-1100, hApsd, 1100, hApsd);
  lpsd[3]->SetLineColor(kRed);
  lpsd[3]->Draw();
  gPad->Update();
  int col[4] = {kBlack, kBlue, kRed, kMagenta};
  TString str[4] = {"Before cuts","After Cuts","Acc-Subtracted", "Accidental"};
  TPaveText *pt[4];
  for(int i=0;i<4;++i){
    pt[i] = new TPaveText(0.72,0.83-i*0.065,0.98,0.899-i*0.065,"ndc");
    pt[i]->SetTextColor(col[i]);
    pt[i]->SetShadowColor(0);
    pt[i]->SetFillColor(0);
    pt[i]->SetBorderSize(0);
    pt[i]->AddText(str[i].Data());
    pt[i]->SetTextAlign(12);//left justified centered vertically
    pt[i]->SetTextSize(0.045);
  }
  c1->cd(5);
  ch->Draw("az>>ha(220,-1100,1100)", "pseg>=0");
  TH1D *ha = (TH1D*)gDirectory->Get("ha");
  ha->SetTitle("Position of Alpha Candidate in Cell");
  ha->GetXaxis()->SetTitle("Z-Position (mm)");
  ha->SetLineColor(kBlack);
  ch->Draw("az>>haz(220,-1100,1100)", cuta && cutp, "goff");
  TH1D *haz = (TH1D*)gDirectory->Get("haz");
  haz->SetMarkerColor(kBlue);
  haz->Draw("sames");
  ch->Draw("fz>>hfa(220,-1100,1100)", cuta && cutf, "goff");
  TH1D *hfa = (TH1D*)gDirectory->Get("hfa");
  hfa->SetLineColor(kMagenta);
  hfa->Scale(1/f2n);
  hfa->Draw("sames");
  TH1D *hazd = (TH1D*)haz->Clone("hazd");
  hazd->Add(hfa,-1);
  for(int i=0;i<hazd->GetNbinsX();++i){
    double var = pow(haz->GetBinError(i),2);
    var += pow(hfa->GetBinError(i),2);
    hazd->SetBinError(i, sqrt(var));
  }
  hazd->SetLineColor(kRed);
  hazd->Draw("sames");
  for(int i=0;i<4;++i)pt[i]->Draw();
  gPad->Update();

  c1->cd(6);
  ch->Draw("az-pz>>hdz", "pseg>=0");
  TH1D* hdz = (TH1D*)gDirectory->Get("hdz");
  hdz->SetLineColor(kBlack);
  hdz->SetTitle("Distance #DeltaZ Between #alpha && #beta BiPo Candidates");
  hdz->Draw();
  hdz->GetYaxis()->SetTitle("Counts");
  hdz->GetXaxis()->SetTitle("(#alpha_{Z}-#beta_{Z})(mm)");
  ch->Draw("az-pz>>hpdz", cuta && cutp, "goff");
  TH1D* hpdz = (TH1D*)gDirectory->Get("hpdz");
  hpdz->SetLineColor(kBlue);
  hpdz->Draw("sames");
  ch->Draw("az-fz>>hfdz", cuta && cutf, "goff");
  TH1D *hfdz = (TH1D*)gDirectory->Get("hfdz");
  hfdz->SetLineColor(kMagenta);
  hfdz->Scale(1/f2n);
  hfdz->Draw("sames");
  TH1D *hdzf = (TH1D*)hpdz->Clone("hdzf");
  hdzf->Add(hfdz,-1);
  for(int i=0;i<hdzf->GetNbinsX();++i){
    double var = pow(hpdz->GetBinError(i),2);
    var += pow(hfdz->GetBinError(i),2);
    hdzf->SetBinError(i, sqrt(var));
  }
  hdzf->SetLineColor(kRed);
  hdzf->Draw("sames");
  TF1 *fg = new TF1("fg","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",-600,600);
  fg->SetParNames("A","Mean","#sigma");
  fg->SetParameters(1000,0,15);
  hdzf->Fit(fg);
  gPad->Update();
  TPaveStats *ps = (TPaveStats*)hdzf->FindObject("stats");
  ps->SetX1NDC(0.1);
  ps->SetX2NDC(0.45);
  ps->Draw();
  for(int i=0;i<4;++i)pt[i]->Draw();
 //  if(1)goto end;
 //  TCanvas *c2 = new TCanvas("c2","c2",0,0,width, length);
 //  c2->Divide(3,2);

 //  c2->cd(1);
 //  ch->Draw("at-pt>>h(360,0,0.72)", "pseg>=0","goff");
 //  TH1D* h = (TH1D*)gDirectory->Get("h");
 //  h->SetLineColor(kBlack);
 //  h->SetBinContent(1,0);
 //  h->SetTitle("Time Between #beta and #alpha BiPo Candidates");
 //  h->Draw();
 //  h->GetYaxis()->SetTitle("Counts per ms separation");
 //  h->GetYaxis()->SetTitleSize(0.04);
 //  h->GetXaxis()->SetTitle("(t_{#alpha}-t_{#beta}) (ms)");
 //  h->GetXaxis()->SetTitleSize(0.04);
 //  ch->Draw("at-pt>>hdt(360,0,0.72)", cuta && cutp,"goff");
 //  TH1D* hdt = (TH1D*)gDirectory->Get("hdt");
 //  hdt->SetLineColor(kBlue);
 //  //hdt->SetBinContent(1,0);
 //  hdt->Draw("sames");
 //  ch->Draw(Form("(ft-at-%f)/%f>>hf(360,0,0.72)",10*tauBiPo,f2n), cuta && cutf,"goff");
 //  TH1D* hf = (TH1D*)gDirectory->Get("hf");
 //  hf->Scale(1/(f2n));
 //  hf->SetLineColor(kMagenta);
 //  //hf->SetBinContent(1,0);
 //  hf->Draw("sames");
 //  TH1D *hBiPo = (TH1D*)hdt->Clone("hBiPo");
 //  hBiPo->Add(hf,-1);
 //  hBiPo->SetLineColor(kRed);
 //  for(int i=0;i<hBiPo->GetNbinsX();++i){
 //    double var = pow(h->GetBinError(i),2);
 //    var += pow(hf->GetBinError(i),2);
 //    hBiPo->SetBinError(i, sqrt(var));
 //  }
 //  TF1 *f = new TF1("f","[0]*exp(-x/([1])*log(2))",tmin,0.71);
 //  f->SetParNames("A","t_{1/2} (ms)");
 //  hBiPo->Draw("sames");
 //  f->SetParameters(hBiPo->GetBinContent(2),0.2);
 //  hBiPo->Fit(f,"r");
 //  gPad->Update();
 //  TPaveStats *ps2 = (TPaveStats*)hBiPo->FindObject("stats");
 //  ps2->SetX1NDC(0.1);
 //  ps2->SetX2NDC(0.45);
 //  ps2->Draw();
 //  for(int i=0;i<4;++i)pt[i]->Draw();

 //  c2->cd(2);
 //  ch->Draw("aE-pE*0>>hAlphaE(36,0.7,1.06)",cuta && cutp,"goff");
 //  TH1D *hAlphaE = (TH1D*)gDirectory->Get("hAlphaE");
 //  hAlphaE->SetLineColor(kBlue);
 //  hAlphaE->SetTitle("Delayed Alpha Energy Distribution");
 //  hAlphaE->Draw();
 //  hAlphaE->GetYaxis()->SetTitle("Counts");
 //  hAlphaE->GetYaxis()->SetTitleSize(0.04);
 //  hAlphaE->GetXaxis()->SetTitle("#alpha Energy (MeV)");
 //  hAlphaE->GetXaxis()->SetTitleSize(0.04);
 //  ch->Draw("aE-fE*0>>hAlphafE(36,0.7,1.06)",cuta && cutf,"goff");
 //  TH1D *hAlphafE = (TH1D*)gDirectory->Get("hAlphafE");
 //  hAlphafE->Scale(1/f2n);
 //  hAlphafE->SetLineColor(kMagenta);
 //  hAlphafE->Draw("sames");
 //  TH1D *hFinAE = (TH1D*)hAlphaE->Clone("hFinAE");
 //  hFinAE->Add(hAlphafE,-1);
 //  for(int i=0;i<hFinAE->GetNbinsX();++i){
 //    double var = pow(hAlphafE->GetBinError(i),2);
 //    var += pow(hAlphaE->GetBinError(i),2);
 //    hFinAE->SetBinError(i, sqrt(var));
 //  }
 //  hFinAE->SetLineColor(kRed);
 //  hFinAE->Draw("sames");
 //  TF1 *fg2 = new TF1("fg2","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",lAE,hAE);
 //  fg2->SetParNames("A","#bar{E} (MeV)","#sigma");
 //  fg2->SetParameters(1000,0.88,0.03);
 //  hFinAE->Fit(fg2,"r");
 //  gPad->Update();
 //  TPaveStats *ps3 = (TPaveStats*)hFinAE->FindObject("stats");
 //  ps3->SetX1NDC(0.1);
 //  ps3->SetX2NDC(0.45);
 //  ps3->Draw();
 //  for(int i=1;i<4;++i)pt[i]->Draw();
 
 //  c2->cd(3);
 //  ch->Draw(Form("aPSD>>h1Dpsd(20,%f,%f)",lApsd,hApsd), cuta && cutp, "goff");
 //  TH1D *h1Dpsd = (TH1D*)gDirectory->Get("h1Dpsd");
 //  h1Dpsd->SetTitle("BiPo Alpha Candidate PSD");
 //  h1Dpsd->SetLineColor(kBlue);
 //  h1Dpsd->Draw();
 //  h1Dpsd->GetXaxis()->SetTitle("PSD value");
 //  gPad->Update();
 //  ch->Draw(Form("aPSD>>h1Dfpsd(20,%f,%f)",lApsd,hApsd), cuta && cutf, "goff");
 //  TH1D *h1Dfpsd = (TH1D*)gDirectory->Get("h1Dfpsd");
 //  h1Dfpsd->Scale(1/f2n);
 //  h1Dfpsd->SetLineColor(kMagenta);
 //  h1Dfpsd->Draw("same");
 //  TH1D *h1Dpsdfinal = (TH1D*)h1Dpsd->Clone("h1Dpsdfinal");
 //  h1Dpsdfinal->Add(h1Dfpsd,-1);
 //  h1Dpsdfinal->SetLineColor(kRed);
 //  for(int i=0;i<h1Dpsdfinal->GetNbinsX();++i){
 //    double var = pow(h1Dpsd->GetBinError(i),2);
 //    var += pow(h1Dfpsd->GetBinError(i),2);
 //    h1Dpsdfinal->SetBinError(i, sqrt(var));
 //  }
 //  h1Dpsdfinal->Draw("sames");
 //  fg->SetParameters(h1Dpsdfinal->GetMaximum()*1.5,0.26,0.02);
 //  h1Dpsdfinal->Fit(fg);
 //  gPad->Update();
 //  TPaveStats *ps4 = (TPaveStats*)h1Dpsdfinal->FindObject("stats");
 //  ps4->SetX1NDC(0.1);
 //  ps4->SetX2NDC(0.45);
 //  ps4->Draw();
 //  gPad->Update();
 //  for(int i=1;i<4;++i)pt[i]->Draw();

 //  c2->cd(4);
 //  ch->Draw("pE>>hbetad(20,0,4)", cuta && cutp,"goff");
 //  TH1D *hbetad = (TH1D*)gDirectory->Get("hbetad");
 //  hbetad->SetLineColor(kBlue);
 //  hbetad->Draw();
 //  hbetad->SetTitle("Bi-214 #beta Energy Spectrum");
 //  hbetad->GetXaxis()->SetTitle("E_{#beta} (MeV)");
 //  gPad->Update();
 //  ch->Draw("fE>>hfbeta(20,0,4)", cuta && cutf,"goff");
 //  TH1D *hfbeta = (TH1D*)gDirectory->Get("hfbeta");
 //  hfbeta->SetLineColor(kMagenta);
 //  hfbeta->Scale(1/f2n);
 //  hfbeta->Draw("same");
 //  TH1D *hbetaFinal = (TH1D*)hbetad->Clone("hbetaFinal");
 //  hbetaFinal->SetLineColor(kRed);
 //  hbetaFinal->Add(hfbeta,-1);
 //  for(int i=0;i<hbetaFinal->GetNbinsX();++i){
 //    double var = pow(hbetad->GetBinError(i),2);
 //    var += pow(hfbeta->GetBinError(i),2);
 //    hbetaFinal->SetBinError(i, sqrt(var));
 //  }
 //  hbetaFinal->Draw("samel");
 //  for(int i=1;i<4;++i)pt[i]->Draw();
 //  c2->cd(5);
 //  ch->Draw("aseg/14:aseg%14>>hseg(14,0,14,11,0,11)", cuta && cutp, "colzgoff");
 //  TH2D *hseg = (TH2D*)gDirectory->Get("hseg");
 //  hseg->SetTitle("BiPo Events by Segment");
 //  ch->Draw("aseg/14:aseg%14>>hfseg(14,0,14,11,0,11)", cuta && cutf, "colzgoff");
 //  TH2D *hfseg = (TH2D*)gDirectory->Get("hfseg");
 //  hfseg->Scale(1/f2n);
 //  hseg->Add(hfseg,-1);
 //  hseg->Draw("colz");
 //  hseg->GetXaxis()->SetTitle("Column");
 //  hseg->GetYaxis()->SetTitle("Row");
 //  gPad->Update();
 //  c2->cd(6);
 //  ch->Draw("aseg>>h1Dseg(154,0,154)", cuta && cutp, "goff");
 //  TH1D *h1Dseg = (TH1D*)gDirectory->Get("h1Dseg");
 //  h1Dseg->SetTitle("BiPo Events by Segment");
 //  h1Dseg->SetLineColor(kBlue);
 //  h1Dseg->Draw();
 //  h1Dseg->GetXaxis()->SetTitle("Segment");
 //  gPad->Update();
 //  ch->Draw("aseg>>h1Dfseg(154,0,154)", cuta && cutf, "goff");
 //  TH1D *h1Dfseg = (TH1D*)gDirectory->Get("h1Dfseg");
 //  h1Dfseg->Scale(1/f2n);
 //  h1Dfseg->SetLineColor(kMagenta);
 //  h1Dfseg->Draw("same");
 //  TH1D *h1Dsegfinal = (TH1D*)h1Dseg->Clone("h1Dsegfinal");
 //  h1Dsegfinal->Add(h1Dfseg,-1);
 //  h1Dsegfinal->SetLineColor(kRed);
 //  for(int i=0;i<h1Dsegfinal->GetNbinsX();++i){
 //    double var = pow(h1Dseg->GetBinError(i),2);
 //    var += pow(h1Dfseg->GetBinError(i),2);
 //    h1Dsegfinal->SetBinError(i, sqrt(var));
 //  }
 //  h1Dsegfinal->Draw("sames");
 //  for(int i=1;i<4;++i)pt[i]->Draw();

 //  TCanvas *c3 = new TCanvas("c3","c3",0,0, width, length);
 //  c3->Divide(2,2);
 //  c3->cd(1);
 //  TProfile *pr[10], *prf[10], *prd[10];
 //  TH2D* hx[10], *hxf[10];
 //  int n=0;
 //  ch->Draw(Form("aE:abs(az)>>hx%i(25,0,700,100,%f,%f)",n,lAE,hAE), cuta && cutp, "goff");
 //  hx[n] = (TH2D*)gDirectory->Get(Form("hx%i",n));
 //  hx[n]->SetTitle("Average Alpha Energy vs Position");
 //  hx[n]->GetYaxis()->SetTitle("Average Alpha Energy (MeV)");
 //  hx[n]->GetXaxis()->SetTitle("Alpha Z-Position (mm)");
 //  hx[n]->SetLineColor(kBlue);
 //  hx[n]->SetMarkerColor(kBlue);
 //  ch->Draw(Form("aE:abs(az)>>hxf%i(25,0,700,100,%f,%f)",n,lAE,hAE), cuta && cutf, "goff");
 //  hxf[n] = (TH2D*)gDirectory->Get(Form("hxf%i",n));
 //  hxf[n]->Scale(1/f2n);
 //  hx[n]->Add(hxf[n],-1);
 //  hx[n]->Draw();
 //  pr[n] = hx[n]->ProfileX(Form("pr%i",n),0,700);
 //  c3->cd(1);
 //  pr[n]->Draw();
 //  ++n;
 //  c3->cd(2);

 //  ch->Draw(Form("pE:abs(pz)>>hx%i(25,0,700,100,%f,%f)",n,0.0,4.0), cuta && cutp, "goff");
 //  hx[n] = (TH2D*)gDirectory->Get(Form("hx%i",n));
 //  hx[n]->SetTitle("Average Beta Energy vs Position");
 //  hx[n]->GetYaxis()->SetTitle("Average Beta Energy (MeV)");
 //  hx[n]->GetXaxis()->SetTitle("Beta Z-Position (mm)");
 //  hx[n]->SetLineColor(kRed);
 //  hx[n]->SetMarkerColor(kRed);
 //  ch->Draw(Form("fE:abs(fz)>>hxf%i(25,0,700,100,%f,%f)",n,0.0,4.0), cuta && cutf, "goff");
 //  hxf[n] = (TH2D*)gDirectory->Get(Form("hxf%i",n));
 //  hxf[n]->Scale(1/f2n);
 //  hx[n]->Add(hxf[n],-1);
 //  //hx[n]->Draw();
 //  pr[n] = hx[n]->ProfileX(Form("pr%i",n),0,700);
 //  c3->cd(2);
 //  pr[n]->Draw();
 //  c3->cd(3);
 //  ++n;
 //  ch->Draw("pE:aE>>htm",cuta&&cutp,"goff");
 //  TH2D *htm = (TH2D*)gDirectory->Get("htm");
 //  pr[n] = htm->ProfileX(Form("pr%i",n),0,100);
 //  pr[n]->Draw();
 //  pr[n]->SetTitle("Average Beta vs Alpha Energy");
 //  pr[n]->GetYaxis()->SetTitle("Average Beta Energy (MeV)");
 //  pr[n]->GetXaxis()->SetTitle("Alpha Energy (MeV)");
 //  pr[n]->SetLineColor(kGreen+2);
 //  pr[n]->SetMarkerColor(kGreen+2);
 //  if(fiducialize){
 //    c1->SaveAs(Form("/home/jonesdc/prospect/plots/%s_BiPoCuts_fid.png",release.Data()));
 //    c2->SaveAs(Form("/home/jonesdc/prospect/plots/%s_BiPoSpectra_fid.png",release.Data()));
 //  }else{
 //    c1->SaveAs(Form("/home/jonesdc/prospect/plots/%s_BiPoCuts.png",release.Data()));
 //    c2->SaveAs(Form("/home/jonesdc/prospect/plots/%s_BiPoSpectra.png",release.Data()));
 //  }

}
