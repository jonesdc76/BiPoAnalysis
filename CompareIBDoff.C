#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TString.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TCut.h"
#include "TFile.h"
#include "TF1.h"
#include "TVectorD.h"
#include "TPaveText.h"
#include "TPaveStats.h"


int CompareIBDoff(bool Neutrino_v2 = 0)
{
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetLineWidth(2);
  gStyle->SetOptStat(0);
  const char* trname = "P2kIBDPlugin/Tibd";
  TChain *ch1 = new TChain(trname);
  TChain *ch2 = new TChain(trname);
  TString pass = (char*) (Neutrino_v2 ? "_IBDwBiPo" : "");
  ifstream file("RxOffRunList.txt");
  int n1 = 0, n2 = 0;
  double lt1 = 0, lt2 = 0;
  while(file.good()&&!file.eof()){
    string line;
    getline(file,line);
    TString rel("Analyzed_NuFact_v1");
    if(Neutrino_v2) {
      rel = "Phys_Neutrino_v2";
      if(TString(line).Contains("180605_Background")){
	rel = "Phys_20180605";
      }else if(TString(line).Contains("180525_Background")&&
	       (TString(line).Contains("series000/s000_f0011") || 
		TString(line).Contains("series000/s000_f0012"))){
	rel = "Phys_20180605";
      }
    }
    if(TString(line).Contains("180316_Background")){
      TString fname(Form("%s/%s/%s/AD1_Wet_Phys%s.root",gSystem->Getenv("BIPO_OUTDIR"),rel.Data(),line.data(), pass.Data()));
      cout<<fname.Data()<<endl;
      ch1->Add(fname.Data());
      TFile tfile(fname.Data());
      if(tfile.IsOpen()){
	lt1 += ((TVectorD*)tfile.Get("runtime"))->Norm1();
	++n1;
	tfile.Close();
      }
    }else if(TString(line).Contains("180525_Background")||
	     TString(line).Contains("180605_Background")){
      TString fname(Form("%s/%s/%s/AD1_Wet_Phys%s.root",gSystem->Getenv("BIPO_OUTDIR"),rel.Data(),line.data(), pass.Data()));
      ch2->Add(fname.Data());
      TFile tfile(fname.Data());
      if(tfile.IsOpen()){
	lt2 += ((TVectorD*)tfile.Get("runtime"))->Norm1();
	++n2;
	tfile.Close();
      }
    }
    file.peek();
  }
  cout<<n1<<" files added from 180316_Background\n";
  cout<<n2<<" files added from 180525_Background\n";
  cout<<lt1/3600.<<" total runtime hours from 180316_Background\n";
  cout<<lt2/3600.<<" total runtime hours from 180525_Background\n";
  const double tlow = 1e3, thigh = 120e3, tlowacc = 2e6, thighacc = 12e6;
  const double n2f = 0.0119;//ratio of lengths of near to far windows
  const double f2n = 1.0e4/119.0;//ratio of lengths of far to near windows
  const double tmin = 0.001;//start coincidence window tmin ms away from electron
  const double lowE = 0, highE = 8, EBW=0.2, highEncapt = 0.6, lowEncapt=0.46;
  int col[3] = {kBlack, kRed-3, kRed};
  TPaveText *ptc = new TPaveText(0.73,0.7,0.95,0.88,"ndc");
  ptc->SetFillColor(0);
  ptc->SetShadowColor(0);
  ptc->SetBorderSize(0);
  ptc->SetTextColor(col[0]);
  ptc->AddText("Total IBD-like");
  TText *tc = (TText*)ptc->AddText("Accidental");
  tc->SetTextColor(col[1]);
  tc = (TText*)ptc->AddText("Acc-Subtracted");
  tc->SetTextColor(col[2]);
  
  TCut cut = Form("ncapt_dt>%f&&ncapt_dt<%f&&E>%f&&E<%f&&Encapt>%f&&Encapt<%f", tlow, thigh, lowE, highE, lowEncapt, highEncapt);
  TCut cutacc = Form("fabs(ncapt_dt)>%f&&fabs(ncapt_dt)<%f&&E>%f&&E<%f&&Encapt>%f&&Encapt<%f",tlowacc,thighacc, lowE, highE, lowEncapt, highEncapt);
  double timeratio = lt1/lt2;
  ch1->Draw(Form("E>>h1(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cut, "goff");
  TH1D* h1 = (TH1D*)gDirectory->Get("h1");
  h1->Sumw2();
  h1->Scale(1000/(lt1*h1->GetBinWidth(1)));
  h1->SetLineWidth(2);
  h1->SetLineColor(col[0]);
  h1->SetMarkerColor(col[0]);
  h1->SetTitle("March Reactor OFF IBD-like Background");
  
  ch1->Draw(Form("E>>h1acc(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cutacc,"goff");
  TH1D* h1acc = (TH1D*)gDirectory->Get("h1acc");
  h1acc->Sumw2();
  h1acc->SetLineWidth(2);
  h1acc->SetLineColor(col[1]);
  h1acc->SetMarkerColor(col[1]);
  h1acc->Scale(1000*n2f/(lt1*h1acc->GetBinWidth(1)));
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
  h1->Draw();
  gPad->Update();
  h1->GetXaxis()->SetTitle("Energy (MeV)");
  h1->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  h1->GetYaxis()->SetLimits(0.001,100);
  h1->GetYaxis()->SetRangeUser(0.001,100);
  h1acc->Draw("same");
  gPad->Update();
  gPad->Update();
  TH1D *h1diff = (TH1D*)h1->Clone("h1diff");
  h1diff->SetMarkerColor(col[2]);
  h1diff->SetLineColor(col[2]);
  h1diff->Add(h1acc,-1);
  h1diff->Draw("same");
  ptc->Draw();
  c1->SetLogy();



  ch2->Draw(Form("E>>h2(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cut, "goff");
  TH1D* h2 = (TH1D*)gDirectory->Get("h2");
  h2->Sumw2();
  h2->Scale(1000/(lt2*h2->GetBinWidth(1)));
  h2->SetLineWidth(2);
  h2->SetLineColor(col[0]);
  h2->SetMarkerColor(col[0]);
  h2->SetTitle("May Reactor OFF IBD-like Background");
  
  ch2->Draw(Form("E>>h2acc(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cutacc,"goff");
  TH1D* h2acc = (TH1D*)gDirectory->Get("h2acc");
  h2acc->Sumw2();
  h2acc->Scale(1000*n2f/(lt2*h2acc->GetBinWidth(1)));
  h2acc->SetLineWidth(2);
  h2acc->SetLineColor(col[1]);
  h2acc->SetMarkerColor(col[1]);
  
  TCanvas *c2 = new TCanvas("c2", "c2",900,0,800,600);
  h2->Draw();
  gPad->Update();
  h2->GetYaxis()->SetLimits(0.001,100);
  h2->GetYaxis()->SetRangeUser(0.001,100);
  h2->GetXaxis()->SetTitle("Energy (MeV)");
  h2->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  h2acc->Draw("same");
  TH1D *h2diff = (TH1D*)h2->Clone("h2diff");
  h2diff->SetMarkerColor(col[2]);
  h2diff->SetLineColor(col[2]);
  h2diff->Add(h2acc,-1);
  h2diff->Draw("same");
  ptc->Draw();
  c2->SetLogy();
  gPad->Update();

  TCanvas *c3 = new TCanvas("c3", "c3",900,0,800,600);
  c3->SetGrid();
  TH1D *h1diffc = (TH1D*)h1diff->Clone("h1diffc");
  TH1D *h2diffc = (TH1D*)h2diff->Clone("h2diffc");
  h1diffc->SetTitle("Background IBD-like Accidental Subtracted Spectrum");
  h1diffc->SetLineColor(kRed);
  h1diffc->SetMarkerColor(kRed);
  h2diffc->SetLineColor(kBlue);
  h2diffc->SetMarkerColor(kBlue);
  h1diffc->Draw();
  gPad->Update();
  h1diffc->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  h1diffc->GetYaxis()->SetLimits(-1,1);
  h1diffc->GetYaxis()->SetRangeUser(-1, 7);
  h2diffc->Draw("same");
  TH1D *hdiff = (TH1D*)h1diff->Clone("hdiff");
  hdiff->SetLineColor(kGreen+2);
  hdiff->Add(h2diff,-1);
  hdiff->Draw("same");
  TPaveText *pt = new TPaveText(0.7,0.7,0.99,0.899,"ndc");
  pt->SetShadowColor(0);
  pt->SetFillColor(0);
  TText *tt = pt->AddText("March Background");
  tt->SetTextColor(kRed);
  tt = pt->AddText("May/June Background");
  tt->SetTextColor(kBlue);
  tt = pt->AddText("Difference");
  tt->SetTextColor(kGreen+2);
  pt->Draw();
  gPad->Update();

  gStyle->SetOptFit(1111);
  TCanvas *c4 = new TCanvas("c4", "c4",900,0,800,600);
  c4->SetGrid();
  TH1D *hdiffpct = new TH1D("hdiffpct","hdiffpct",int((highE-lowE)/EBW),lowE, highE);
  hdiffpct->SetLineWidth(2);
  hdiffpct->SetLineColor(kGreen+2);
  for(int i=2;i<=hdiffpct->GetNbinsX();++i){
    //if(i>7&&i<11)continue;
    hdiffpct->SetBinContent(i,100*hdiff->GetBinContent(i)/h1diff->GetBinContent(i));
    hdiffpct->SetBinError(i,100*hdiff->GetBinError(i)/h1diff->GetBinContent(i));
  }
  hdiffpct->Draw();
  hdiffpct->SetTitle("Difference Between March and May/June Background Spectra");
  hdiffpct->GetXaxis()->SetTitle("Energy (MeV)");
  hdiffpct->GetYaxis()->SetTitle("Difference (%)");
  hdiffpct->GetYaxis()->SetRangeUser(-100,100);
  TF1 *f = new TF1("f","pol0",0.2,8);
  // f->FixParameter(0,0);
  hdiffpct->Fit(f,"r");
  gPad->Update();
  TCanvas *c5 = new TCanvas("c5", "c5",900,0,800,600);
  ch1->SetLineColor(kBlack);
  ch2->SetLineColor(kRed);
  ch1->Draw("Encapt>>hnc(100,0.4,0.7)",cut,"goff");
  TH1D* hnc = (TH1D*)gDirectory->Get("hnc");
  hnc->Sumw2();
  hnc->SetLineColor(col[0]);
  hnc->SetMarkerColor(col[0]);

  ch1->Draw("Encapt>>hncacc(100,0.4,0.7)",cutacc,"goff");
  TH1D* hncacc = (TH1D*)gDirectory->Get("hncacc");
  hncacc->SetLineColor(col[1]);
  hncacc->SetMarkerColor(col[1]);
  hncacc->Sumw2();
  hncacc->Scale(n2f);
  TH1D *hncdiff = (TH1D*)hnc->Clone("hncdiff");
  hncdiff->SetLineColor(kRed);
  hncdiff->SetMarkerColor(kRed);
  hncdiff->Add(hncacc,-1);
  hncdiff->Draw();
  TF1 *f1= new TF1("f1","gaus",lowEncapt, highEncapt);
  f1->SetLineColor(kRed);
  f1->SetParName(2,"March #sigma");
  hncdiff->Fit(f1,"r");
  gPad->Update();
  TPaveStats *ps = (TPaveStats*)hncdiff->FindObject("stats");
  ps->SetTextColor(kRed);
  ps->SetLineColor(kRed);
  ps->Draw();
  gPad->Update();

  hncdiff->SetTitle("IBD nLi Capture Energy");
  hncdiff->GetXaxis()->SetTitle("Energy (MeV)");
  ch2->Draw("Encapt>>hnc2(100,0.4,0.7)",cut,"goff");
  TH1D* hnc2 = (TH1D*)gDirectory->Get("hnc2");
  hnc2->Sumw2();
  hnc2->SetLineColor(col[0]);
  hnc2->SetMarkerColor(col[0]);

  ch2->Draw("Encapt>>hncacc2(100,0.4,0.7)",cutacc,"goff");
  TH1D* hncacc2 = (TH1D*)gDirectory->Get("hncacc2");
  hncacc2->SetLineColor(col[1]);
  hncacc2->SetMarkerColor(col[1]);
  hncacc2->Sumw2();
  hncacc2->Scale(n2f);
  TH1D *hncdiff2 = (TH1D*)hnc2->Clone("hncdiff2");
  hncdiff2->SetLineColor(kBlue);
  hncdiff2->SetMarkerColor(kBlue);
  hncdiff2->Add(hncacc2,-1);
  hncdiff2->Draw("sames");
  f1->SetLineColor(kBlue);
  f1->SetParName(2,"May #sigma");
  hncdiff2->Fit(f1,"r");
  gPad->Update();
  TPaveStats *ps2 = (TPaveStats*)hncdiff2->FindObject("stats");
  ps2->SetTextColor(kBlue);
  ps2->SetLineColor(kBlue);
  ps2->SetY1NDC(0.45);
  ps2->SetY2NDC(0.69);
  ps2->Draw();
  gPad->Update();
  return 0;
}
