#include <vector>
#include <map>
#include "IBDon.C"
#include "IBDoff.C"
#include "PROSPECT_Style.cc"
#include <iostream>
#include "TCut.h"
#include "TH1D.h"
#include "TVectorD.h"
#include "TChain.h"
#include "TPaletteAxis.h"
#include "TChainElement.h"
#include "TCollection.h"
#include "TStyle.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TPaveText.h"
#include "TPaveStats.h"

using namespace std;
const int N = 3, ncol = 14, nrow = 11;
const double tauBiPo = 0.1643/log(2); 
const double tlow = 1e3, thigh = 120e3, tlowacc = 2e6, thighacc = 12e6;
const double n2f = 0.0119;//ratio of lengths of near to far windows
const double f2n = 1.0e4/119.0;//ratio of lengths of far to near windows
const double tmin = 0.001;//start coincidence window tmin ms away from electron
const int kNcell = ncol * nrow;
const int ExcludeCellArr[31] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 18, 21, 23, 24, 27, 32, 34, 40, 44, 52, 68, 79, 86, 102, 115, 122, 127, 130, 139};

double GetLiveTime(TChain *ch){
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  double tlive = 0;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    tlive += ((TVectorD*)file->Get("runtime"))->Norm1();
    if(((TVectorD*)file->Get("runtime"))->Norm1()<1)
      cout<<((TVectorD*)file->Get("runtime"))->Norm1()<<endl;
  }
  return tlive/3600.0;
}

int IBDBiPoOverlap(bool prompt = 0, bool P2style = 1){
  char *particle = (char *)(prompt==0 ? "Delayed":"prompt");
  if(P2style){
    setup_PROSPECT_style();
  }else{
    gStyle->SetOptStat(0);
    //gStyle->SetOptFit(1111);
    gStyle->SetPadLeftMargin(0.12);
    gStyle->SetPadRightMargin(0.04);
  }
  const double EBW = 0.2;//energy bin width in MeV
  bool deadtime_corr = 0;
  double lowE = prompt ? 0 : 0.4, highE = prompt ? 8 : 0.9, lowEncapt = 0.46, highEncapt = 0.6;
  int nBins = prompt ? int((highE-lowE)/EBW) : int((highE-lowE)/0.01), colOn = kRed, colOff = kBlue, colAcc = kBlack, colCorr = kGreen+2;
  IBDon *on = new IBDon();
  TChain *chon = on->chain;
  chon->SetAlias("energy", prompt ? "E" : "Encapt");
  IBDoff *off = new IBDoff();
  TChain *choff = off->chain;
  choff->SetAlias("energy", prompt ? "E" : "Encapt");
  double Ton = GetLiveTime(chon);
  double Toff = GetLiveTime(choff);
  double on2offscale = Ton/Toff;
  if(deadtime_corr){
    on2offscale = 30.09/25.88;
    cout<<"\n*\nNOTE! Correcting for deadtime\n*\n";
  }
  cout<<"Reactor on live time: "<<Form("%0.4f hours = %0.4f days\n",Ton, Ton/24.0);
  cout<<"Reactor off live time: "<<Form("%0.4f hours = %0.4f days\n",Toff, Toff/24.0);
  TCut cutdt = Form("ncapt_dt>%f&&ncapt_dt<%f", tlow, thigh);
  TCut cutdtacc = Form("fabs(ncapt_dt)>%f&&fabs(ncapt_dt)<%f",tlowacc,thighacc);
  if(prompt){
    cutdt = Form("ncapt_dt>%f&&ncapt_dt<%f&&Encapt>%f&&Encapt<%f",
		 tlow, thigh, lowEncapt, highEncapt);
    cutdtacc =Form("fabs(ncapt_dt)>%f&&fabs(ncapt_dt)<%f&&Encapt>%f&&Encapt<%f",
		   tlowacc,thighacc, lowEncapt, highEncapt);
  }

  TCanvas *cOn = new TCanvas("cOn", "cOn",0,0,800,600);
  chon->Draw(Form("energy>>hOn(%i,%f,%f)",nBins, lowE, highE), cutdt, "goff");
  TH1D *hOn = (TH1D*)gDirectory->Get("hOn");
  hOn->Sumw2();
  gPad->Update();
  hOn->SetTitle(Form("Reactor ON IBD Candidate %s Energy", particle));
  hOn->GetXaxis()->SetTitle("Energy (MeV)");
  hOn->GetYaxis()->SetTitle("Counts");
  hOn->GetYaxis()->SetRangeUser(0,hOn->GetMaximum()*1.1);
  hOn->SetMarkerStyle(8);
  hOn->SetMarkerColor(colOn);
  hOn->SetLineColor(colOn);
  
  chon->Draw(Form("energy>>hOnAcc(%i,%f,%f)",nBins, lowE, highE), cutdtacc, "goff");
  TH1D *hOnAcc = (TH1D*)gDirectory->Get("hOnAcc");
  hOnAcc->Sumw2();
  hOnAcc->Scale(n2f);
  hOnAcc->SetTitle(Form("Reactor ON Accidental IBD Candidate %s Energy", particle));
  hOnAcc->GetXaxis()->SetTitle("Energy (MeV)");
  hOnAcc->GetYaxis()->SetTitle("Counts");
  hOnAcc->SetMarkerColor(colAcc);
  hOnAcc->SetLineColor(colAcc);
  TH1D *hOnCorr = (TH1D*)hOn->Clone("hOnCorr");
  hOnCorr->SetMarkerColor(colCorr);
  hOnCorr->SetMarkerStyle(8);
  hOnCorr->SetLineColor(colCorr);
  hOnCorr->Add(hOnAcc,-1);
  hOn->Draw();
  hOnAcc->Draw("sames");
  hOnCorr->Draw("sames");
  TF1 *f = new TF1("f","[0]*exp(-pow(x-0.862,2)/(2*pow(0.04272,2)))",0.7,highE);
  if(!prompt)hOnCorr->Fit(f,"r");
  TPaveText *pton = new TPaveText(0.77,0.74,0.99,0.93,"ndc");
  pton->SetFillColor(0);
  pton->SetShadowColor(0);
  pton->SetTextColor(colOn);
  pton->AddText("ON total");
  TText *tt = pton->AddText("ON Accidental");
  tt->SetTextColor(colAcc);
  tt = pton->AddText("ON Acc-Subtracted");
  tt->SetTextColor(colCorr);
  pton->Draw();


  TCanvas *cOff = new TCanvas("cOff", "cOff",850,0,800,600);
  choff->Draw(Form("energy>>hOff(%i,%f,%f)",nBins, lowE, highE), cutdt, "goff");
  TH1D *hOff = (TH1D*)gDirectory->Get("hOff");
  hOff->Sumw2();
  gPad->Update();
  hOff->SetTitle(Form("Reactor OFF IBD Candidate %s Energy", particle));
  hOff->GetXaxis()->SetTitle("Energy (MeV)");
  hOff->GetYaxis()->SetTitle("Counts");
  hOff->GetYaxis()->SetRangeUser(0,hOn->GetMaximum()*1.1);
  hOff->SetMarkerColor(colOff);
  hOff->SetMarkerStyle(8);
  hOff->SetLineColor(colOff);
  choff->Draw(Form("energy>>hOffAcc(%i,%f,%f)",nBins, lowE, highE),cutdtacc, "goff");
  TH1D *hOffAcc = (TH1D*)gDirectory->Get("hOffAcc");
  hOffAcc->Sumw2();
  hOffAcc->Scale(n2f);
  hOffAcc->SetTitle(Form("Reactor OFF Accidental IBD Candidate %s Energy", particle));
  hOffAcc->GetXaxis()->SetTitle("Energy (MeV)");
  hOffAcc->GetYaxis()->SetTitle("Counts");
  hOffAcc->SetMarkerColor(colAcc);
  hOffAcc->SetLineColor(colAcc);
  TH1D *hOffCorr = (TH1D*)hOff->Clone("hOffCorr");
  hOffCorr->Add(hOffAcc,-1);
  hOffCorr->SetMarkerStyle(8);
  hOffCorr->SetMarkerColor(colCorr);
  hOffCorr->SetLineColor(colCorr);
  hOff->Draw();
  hOffAcc->Draw("sames");
  hOffCorr->Draw("sames");
  if(!prompt)hOffCorr->Fit(f,"r");
  TPaveText *ptoff = new TPaveText(0.77,0.74,0.99,0.93,"ndc");
  ptoff->SetFillColor(0);
  ptoff->SetShadowColor(0);
  ptoff->SetTextColor(colOff);
  ptoff->AddText("OFF total");
  tt = ptoff->AddText("OFF Accidental");
  tt->SetTextColor(colAcc);
  tt = ptoff->AddText("OFF Acc-Subtracted");
  tt->SetTextColor(colCorr);
  ptoff->Draw();

  TCanvas *cPrE = new TCanvas("cPrE", "cPrE",0,600,800,600);
  TH1D *hOnCorr2 = (TH1D*)hOnCorr->Clone("hOnCorr2");
  hOnCorr2->Add(hOffCorr,-on2offscale);
  hOnCorr2->SetTitle(Form("Background Subtracted IBD %s Energy Distribution", particle));
  hOnCorr2->Draw();
  TF1 *f1 = new TF1("f1","gaus",lowE,0.8);
  if(!prompt)hOnCorr2->Fit(f1,"r");
  TPaveText *pt = new TPaveText(0.56,0.64,0.82,0.83,"ndc");
  pt->SetFillColor(0);
  pt->SetShadowColor(0);
  pt->AddText(Form("#chi^{2}/NDF:  %0.2f",f1->GetChisquare()/double(f1->GetNDF())));
  pt->AddText(Form("Mean:  %0.4f #pm %0.4f",f1->GetParameter(1),f1->GetParError(1)));
  pt->AddText(Form("#sigma:    %0.3f #pm %0.3f",f1->GetParameter(2),f1->GetParError(2)));
  pt->Draw();
  return 0; 
}


