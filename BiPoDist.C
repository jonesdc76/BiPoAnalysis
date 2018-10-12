#include <time.h>
#include <vector>
#include <map>
#include <iostream>
#include "TH1D.h"
#include "TDatime.h"
#include "TVectorD.h"
#include "TChain.h"
#include "TSystem.h"
#include "TChainElement.h"
#include "TCollection.h"
#include "TStyle.h"
#include "TLine.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TPaveText.h"
#include "TPaveStats.h"
#include "BP.C"
#include "PROSPECT_Style.cc"
using namespace std;

int BiPoDist(){
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  BP *bp = new BP();
  TChain *ch = bp->chain;
  TH1D *hp = new TH1D("hp","Distance Between Prompt and Delayed",100,0,2500);
  hp->SetLineColor(kBlue);
  hp->SetLineWidth(2);
  TH1D *hf = new TH1D("hf","Distance Between Prompt and Delayed",100,0,2500);
  hf->SetLineColor(kRed);
  hf->SetLineWidth(2);
  TH1D *hpz = new TH1D("hpz","Alpha position",200,-1000,1000);
  hpz->Sumw2();
  hpz->SetLineColor(kBlue);
  hpz->SetLineWidth(2);
  TH1D *hfz = new TH1D("hfz","Alpha position",200,-1000,1000);
  hfz->Sumw2();
  hfz->SetLineColor(kRed);
  hfz->SetLineWidth(2);
  TH1D *hpdz = new TH1D("hpdz","Alpha-Beta position difference",100,-400,400);
  hpdz->Sumw2();
  hpdz->SetLineColor(kBlue);
  hpdz->SetLineWidth(2);
  TH1D *hfdz = new TH1D("hfdz","Alpha-Beta position difference",100,-400,400);
  hfdz->Sumw2();
  hfdz->SetLineColor(kRed);
  hfdz->SetLineWidth(2);
  TH1D *hpdt = new TH1D("hpdt","dt",201,-0.004,0.8);
  hpdt->Sumw2();
  hpdt->SetLineColor(kBlue);
  hpdt->SetLineWidth(2);
  TH1D *hfdt = new TH1D("hfdt","dt",201,-0.004,0.8);
  hfdt->Sumw2();
  hfdt->SetLineColor(kRed);
  hfdt->SetLineWidth(2);
  TH2D *hap2 = new TH2D("hap2","BiPo Alpha Heat Map",14,0,14,11,0,11);
  TH2D *haf2 = new TH2D("haf2","BiPo Alpha Heat Map",14,0,14,11,0,11);
  TH2D *hp2 = new TH2D("hp2","BiPo Beta Heat Map",14,0,14,11,0,11);
  TH2D *hf2 = new TH2D("hf2","BiPo Beta Heat Map",14,0,14,11,0,11);
  //Set boundary cut values on energy, psd, z-pos and time
  //-------------------------------------------------------
  double hAE = 0.98, lAE = 0.73, hApsd = 0.32, lApsd = 0.2;//alpha
  double highBE = 4.0, lowBE = 0, hPpsd = 0.26, lPpsd = 0;//beta
  
  for(int i=0;i<ch->GetEntries();++i){
    bp->GetEntry(i);
    if(i%5000000==0)cout<<"Entry "<<i<<" of "<<ch->GetEntries()<<endl; 
    //Apply alpha cuts
    //-------------------------------------------
    if(!(abs(bp->az)<1000))continue;//alpha position
    if(bp->aE<lAE || bp->aE > hAE)continue;//alpha energy
    if(bp->aPSD<lApsd || bp->aPSD > hApsd)continue;//alpha PSD

    for(int j=0;j<bp->mult_prompt;++j){
      if( (bp->pmult_clust->at(j) != bp->pmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->pEtot->at(j) < lowBE || bp->pEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      if(bp->mult_prompt > 0){
	int ax = bp->aseg%14;
	int ay = bp->aseg/14;
	int x = bp->pseg->at(j)%14;
	int y = bp->pseg->at(j)/14;
	double dx = 146.0*((bp->aseg - bp->pseg->at(j))%14);
	double dy = int((bp->aseg - bp->pseg->at(j))/14)*146.0;
	double dz = bp->az - bp->pz->at(j);
	double d = sqrt(dx*dx+dy*dy+dz*dz);
	hp->Fill(d);
	if(d>1870 && d<1930){
	  hap2->Fill(ax,ay);
	  hp2->Fill(x,y);
	  hpdt->Fill(bp->at-bp->pt->at(j));
	  hpz->Fill(bp->pz->at(j));
	  hpdz->Fill(bp->az-bp->pz->at(j));
	}
      }
    }
    for(int j=0;j<bp->mult_far;++j){
      if( (bp->fmult_clust->at(j) != bp->fmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->fEtot->at(j) < lowBE || bp->fEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      if(bp->mult_far > 0){
	int ax = bp->aseg%14;
	int ay = bp->aseg/14;
	int x = bp->fseg->at(j)%14;
	int y = bp->fseg->at(j)/14;
	double dx = 146.0*((bp->aseg - bp->fseg->at(j))%14);
	double dy = int((bp->aseg - bp->fseg->at(j))/14)*146.0;
	double dz = bp->az - bp->fz->at(j);
	double d = sqrt(dx*dx+dy*dy+dz*dz);
	hf->Fill(d);
	if(d>1870 && d<1930){
	  haf2->Fill(ax,ay);
	  hf2->Fill(x,y);
	  double dt = (bp->ft->at(j)-bp->at)-10.0*0.1643/log(2);
	  hfdt->Fill(dt/12.0);
	  hfz->Fill(bp->fz->at(j));
	  hfdz->Fill(bp->az-bp->fz->at(j));
	}
      }
    }
  }
  hf->Scale(1/12.);
  TCanvas *c = new TCanvas("c","c",0,0,1600,1000);
  c->Divide(2,2);
  c->cd(1);
  hp->Draw();
  hf->Draw("same");
  gPad->Update();
  TCanvas *ctn = new TCanvas("ctn","ctn",0,0,1000,500);
  ctn->Divide(2,1);
  ctn->cd(1);
  hp->Draw();
  hf->Draw("same");
  gPad->Update();
  hp->GetXaxis()->SetTitle("Prompt/Delay displacement (mm)");
  hp->GetYaxis()->SetTitle("Counts");
  
  c->cd(2);
  hp->Sumw2();
  hf->Sumw2();
  TH1D *hs = (TH1D*)hp->Clone("hs");     
  hs->Add(hf,-1);
  hs->SetLineColor(kMagenta);
  hs->SetMarkerColor(kMagenta);
  hs->SetLineWidth(2);
  hs->Draw("simple");
  hs->GetXaxis()->SetTitle("Prompt/Delay displacement (mm)");
  hs->GetYaxis()->SetTitle("Counts");
  TLine *tl = new TLine(700,0.0,700,5.e5);
  tl->SetLineColor(kBlack);
  tl->SetLineWidth(2);
  tl->SetLineStyle(9);
  ctn->cd(2);  
  hs->Draw();
  tl->Draw();
  gPad->Update();
  ctn->SaveAs(Form("%s/distance_cut.pdf",gSystem->Getenv("TECHNOTE")));
  c->cd(3);
  haf2->Scale(1/12.0);
  hap2->Add(haf2,-1);
  hap2->Draw("colz");
  
  c->cd(4);
  hf2->Scale(1/12.0);
  hp2->Add(hf2,-1);
  hp2->Draw("colz");

  TCanvas *c1 = new TCanvas("c1","c1",0,0,1600,950);
  c1->Divide(2,2);
  c1->cd(1);
  hpz->Draw();
  hfz->Scale(1/12.0);
  TH1D *hsz = (TH1D*)hpz->Clone("hsz");
  hsz->Add(hfz,-1);
  hsz->SetLineColor(kMagenta);
  hsz->SetLineWidth(2);
  hfz->Draw("same");
  hsz->Draw("same");
  c1->cd(2);
  hpdz->Draw();
  hfdz->Scale(1/12.0);
  TH1D *hsdz = (TH1D*)hpdz->Clone("hsdz");
  hsdz->Add(hfdz,-1);
  hsdz->SetLineColor(kMagenta);
  hsdz->SetMarkerColor(kMagenta);
  hsdz->SetLineWidth(2);
  hfdz->Draw("same");
  hsdz->Draw("same");
  c1->cd(3);
  hpdt->Draw();
  hfdt->Scale(1/12.0);
  TH1D *hsdt = (TH1D*)hpdt->Clone("hsdt");
  hsdt->Add(hfdt,-1);
  hsdt->SetLineColor(kMagenta);
  hsdt->SetLineWidth(2);
  gPad->Update();
  hpdt->GetYaxis()->SetRangeUser(-100,7000);
  hfdt->Draw("same");
  hsdt->Draw("same");
  gStyle->SetOptFit(1111);
  TF1 *f1 = new TF1("f1","[0]*pow(0.5,x/[1])",0.01,0.7);
  f1->SetParameters(884,0.165);
  f1->SetParNames("A_{0}","t_{1/2}");
  hsdt->Fit(f1,"r");
  return 0;
}
