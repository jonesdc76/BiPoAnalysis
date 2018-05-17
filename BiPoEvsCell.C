#include <vector>
#include "BP.C"
#include <iostream>
#include "TH1D.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TPaveText.h"
#include "TPaveStats.h"

using namespace std;

const double kTimeOn = 83.65*3600, kTimeOff = 75*3600, kRelWindowSize = 119.0/10000.0;
const double tauBiPo = 0.1643/log(2); 
const double f2n = 12;//ratio of lengths of far to near windows
const double tmin = 0.002;//start coincidence window tmin ms away from electron
const int kNcell = 154;

bool isET(int seg){
  return (seg%14 == 13 || seg%14 == 0 || seg >= 140);
}

int BiPoEvsCell(bool fiducialize = 0){
  gStyle->SetOptFit(1111);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadLeftMargin(0.14);
  BP *bp = new BP();
  double hAE = 0.96, lAE = 0.77, hApsd = 0.31, lApsd = 0.2;
  double hppsd = 0.26, lppsd = 0;
 
  //Initialize histograms
  //-------------------------------------------
  TH1D *hcorr[kNcell], *hacc[kNcell], *hA[kNcell];
  TH1D *hcorrOff[kNcell], *haccOff[kNcell], *hAOff[kNcell];

  for(int i=0;i<kNcell;++i){
    hcorr[i] = new TH1D(Form("hcorr[%i]",i), Form("hcorr[%i]",i),25, lAE, hAE);
    hacc[i] = new TH1D(Form("hacc[%i]",i), Form("hacc[%i]",i),25, lAE, hAE);
    hcorrOff[i] = new TH1D(Form("hcorrOff[%i]",i), Form("hcorrOff[%i]",i),25, lAE, hAE);
    haccOff[i] = new TH1D(Form("haccOff[%i]",i), Form("haccOff[%i]",i),25, lAE, hAE);
  }


  //Loop over tree
  //-------------------------------------------
  for(int i=0;i<bp->fChain->GetEntries();++i){
    bp->GetEntry(i);
    //cout<<bp->pz->at(0)<<endl;
    //Apply alpha cuts
    //-------------------------------------------
    if(!(abs(bp->az)<1000))continue;//alpha position
    if(bp->aE<lAE || bp->aE > hAE)continue;//alpha energy
    if(bp->aPSD<lApsd || bp->aPSD > hApsd)continue;//alpha PSD
    if(fiducialize && (bp->aseg<14 || bp->aseg>139 || bp->aseg%14 == 0 || bp->aseg%14 == 13))continue;//alpha fiducial

    //Fill alpha energy histos for near window
    //-------------------------------------------
    for(int j=0;j<bp->mult_prompt;++j){
      if( bp->pPSD->at(j) > lppsd && bp->pPSD->at(j) < hppsd && abs(bp->pz->at(j)) < 1000 && bp->at - bp->pt->at(j) > 0.002){
	// if(TString(bp->fChain->GetDirectory()->GetFile()->GetName()).Contains("Wet")){
	//   hcorr[bp->aseg]->Fill(bp->aE);
	// }else{
	//   hcorrOff[bp->aseg]->Fill(bp->aE);
	// }
	hcorr[bp->aseg]->Fill(bp->aE);

      }
    }
    //Fill alpha energy histos for far window
    //-------------------------------------------
    for(int j=0;j<bp->mult_far;++j){
      if( bp->fPSD->at(j) > lppsd && bp->fPSD->at(j) < hppsd && abs(bp->fz->at(j)) < 1000 )
    	hacc[bp->aseg]->Fill(bp->aE);
    }
  }
  TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",lAE,hAE);
  TGraphErrors *gE = new TGraphErrors();
  TGraphErrors *gEW = new TGraphErrors();
  TGraphErrors *gE_ET = new TGraphErrors();
  TGraphErrors *gEW_ET = new TGraphErrors();
  TH1D* hE = new TH1D("hE","hE",20, 0.84, 0.9);
  TH1D* hW = new TH1D("hW","hW",30, 0.01, 0.05);
  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
  int n = 0, nET = 0;
  for(int i=0;i<kNcell;++i){
    if(hcorr[i]->GetEntries()==0)continue;
    hA[i] = (TH1D*)hcorr[i]->Clone(Form("hA[%i]",i));
    hA[i]->Sumw2();
    hacc[i]->Sumw2();
    hacc[i]->Scale(1/f2n);
    hA[i]->Add(hacc[i],-1);
    f->SetParameters(hA[i]->GetMaximum(),0.865,0.042);
    hA[i]->Draw();
    gPad->Update();
    hA[i]->Fit(f,"r");
    gE->SetPoint(n, i, f->GetParameter(1));
    gE->SetPointError(n, 0, f->GetParError(1));
    gEW->SetPoint(n, i, f->GetParameter(2));
    gEW->SetPointError(n, 0, f->GetParError(2));
    hE->Fill(f->GetParameter(1));
    hW->Fill(f->GetParameter(2));
    ++n;
    if(isET(i)){
      gE_ET->SetPoint(nET, i, f->GetParameter(1));
      gE_ET->SetPointError(nET, 0, f->GetParError(1));
      gEW_ET->SetPoint(nET, i, f->GetParameter(2));
      gEW_ET->SetPointError(nET, 0, f->GetParError(2));
      ++nET;
    }
    c1->ForceUpdate();
    gE->Fit("pol0");
  }
  TCanvas *cE = new TCanvas("cE","cE",0,0,1400,800);
  cE->Divide(2,1);
  TPaveText *pt = new TPaveText(0.8,0.8,0.995,0.89,"NDC");
  pt->SetShadowColor(0);
  pt->SetFillColor(0);
  pt->SetTextColor(kBlue);
  pt->AddText("Hamamatsu");  
  TText *t = (TText*)pt->AddText("ET");
  t->SetTextColor(kRed);
  
  TCanvas *cW = new TCanvas("cW","cW",0,0,1400,800);
  cW->Divide(2,1);
  cE->cd(1);
  gE->SetTitle("^{214}Bi Alpha Energy Mean vs Cell");
  gE->SetMarkerColor(kBlue);
  gE->SetLineColor(kBlue);
  gE->SetMarkerStyle(8);
  gE->SetMarkerSize(0.6);
  gE->Draw("ap");
  gPad->Update();
  TPaveStats *ps = (TPaveStats*)gE->FindObject("stats");
  ps->SetX1NDC(0.141);
  ps->SetX2NDC(0.49);
  ps->SetY1NDC(0.899);
  ps->SetY2NDC(0.78);
  gE->GetXaxis()->SetTitle("Segment Number");
  gE->GetYaxis()->SetTitle("Alpha Energy (MeV)");
  gE_ET->SetMarkerColor(kRed);
  gE_ET->SetLineColor(kRed);
  gE_ET->SetMarkerStyle(8);
  gE_ET->SetMarkerSize(0.6);
  gE_ET->Draw("samep");
  pt->Draw();
  gPad->Update();
  cE->cd(2);
  hE->Draw();
  hE->SetTitle("^{214}Bi Alpha Energy By Cell");
  hE->GetXaxis()->SetTitle("Alpha Energy (MeV)");
  gPad->Update();
  cW->cd(1);
  gEW->SetTitle("^{214}Bi Alpha Energy Width vs Cell");
  gEW->SetMarkerColor(kBlue);
  gEW->SetLineColor(kBlue);
  gEW->SetMarkerStyle(8);
  gEW->SetMarkerSize(0.6);
  gEW->Draw("ap");
  gEW->Fit("pol0");
  gPad->Update();
  TPaveStats *ps1 = (TPaveStats*)gEW->FindObject("stats");
  ps1->SetX1NDC(0.141);
  ps1->SetX2NDC(0.49);
  ps1->SetY1NDC(0.899);
  ps1->SetY2NDC(0.78);
  
  gEW->GetXaxis()->SetTitle("Segment Number");
  gEW->GetYaxis()->SetTitle("Alpha Energy Width (MeV)");
  gEW_ET->SetMarkerColor(kRed);
  gEW_ET->SetLineColor(kRed);
  gEW_ET->SetMarkerStyle(8);
  gEW_ET->SetMarkerSize(0.6);
  gEW_ET->Draw("samep");
  pt->Draw();
  gPad->Update();
  cW->cd(2);
  hW->Draw();
  hW->SetTitle("^{214}Bi Alpha Energy Width By Cell");
  hW->GetXaxis()->SetTitle("Alpha Energy Width (MeV)");
  gPad->Update();
  cE->SaveAs("/Users/jonesdc76/prospect/plots/BiPoEvsCell.png");
  cW->SaveAs("/Users/jonesdc76/prospect/plots/BiPoEWidthvsCell.png");
  return 0;
}
