#include <iostream>
#include <vector>
#include "TRandom3.h"
#include "TH1D.h"
#include "TCanvas.h"
const double Rbkg = 542;//background rate
const double Rrn = 0.4;//RnPo rate
const double tau = 2.57e-3;//lifetime of Po215
const double cut_t = 0.00015;//veto time


double deadtime(){
  vector<double>vRn, vPo;
  vector<bool>vVeto;
  int N = 1000000;
  TRandom3 r(0);
  TH1D *hbkg = new TH1D("hbkg","hbkg",1000,0,N);
  TH1D *hrnpo = new TH1D("hrnpo","hrnpo",100,0,N);
  hrnpo->SetLineColor(kBlue);
  TH1D *hrnpocut = new TH1D("hrnpocut","hrnpocut",100,0,N);
  hrnpocut->SetLineColor(kRed);
  TH1D *hdt = new TH1D("hdt","hdt",100,0,0.01);
  TH1D *hdtb = new TH1D("hdtb","hdtb",1000,0,0.0003);
  double trn = r.Exp(1/Rrn);
  double tn = r.Exp(1/Rbkg);
  double tbkg = r.Exp(1/Rbkg);
  for(Long64_t i=0;trn<N;++i){
      trn += r.Exp(1/Rrn);
      double tpo = trn + r.Exp(tau);
      if(tpo-trn < 3*tau && tpo-trn > 0.0001){
	vRn.push_back(trn);
	vPo.push_back(tpo);
	vVeto.push_back(1);
	hrnpo->Fill(tpo);
	hdt->Fill(tpo-trn);
      }
  }
  int nrn = 0, npo = 0;
  for(Long64_t i=0;tbkg<N;++i){
    if(i%10000000==0)cout<<i<<" "<<tbkg<<endl;
    hdtb->Fill(tn);
    hbkg->Fill(tbkg);
    if(vRn[nrn] - tbkg < 0)++nrn;
    if(vPo[npo] - tbkg < 0)++npo;
    tn = r.Exp(1/Rbkg);
    tbkg += tn;
    if(nrn < (int)vRn.size()){
      if(vRn[nrn] - tbkg > 0){
	if(vRn[nrn] - tbkg < cut_t ){
	  //int u=9;
	  vVeto[nrn] = 0;
	}
      }else{++nrn;}
    }
    if(npo < (int)vPo.size()){
      if(vPo[npo] - tbkg > 0){
	if(vPo[npo] - tbkg < cut_t ){
	  //int u=9;
	  vVeto[npo] = 0;
	}
      }else{++npo;}
    }
  }
  for(int i=0;i<(int)vVeto.size();++i){
    if(vVeto[i]){
      hrnpocut->Fill(vPo[i]);
    }
  }
  
  TCanvas *c = new TCanvas("c","c",0,0,1400,950);
  c->Divide(2,2);
  c->cd(1);
  hbkg->Draw();
  c->cd(2);
  hrnpo->Draw();
  hrnpocut->Draw("sames");
  c->cd(3);
  hdtb->Draw();
  c->cd(4);
  hdt->Draw();
  return hrnpocut->GetEntries()/double(hrnpo->GetEntries());
}
