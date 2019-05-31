#include <time.h>
#include <vector>
#include <map>
#include <iostream>
#include "TSystem.h"
#include "TCut.h"
#include "TH1D.h"
#include "TDatime.h"
#include "TVectorD.h"
#include "TChain.h"
#include "TPaveText.h"
#include "TChainElement.h"
#include "TCollection.h"
#include "TStyle.h"
#include "TLine.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
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
const int N = 3, ncol = 14, nrow = 11, nBINS = 40;
const double kCellSize = 146.0;//cell cross sectional size in mm
const double kMaxDisplacement = 550.0;//maximum displacement between alpha and beta (max pulse in prompt cluster)
const double tauBiPo = 0.1643 / log(2);
const double F2N = 100.0;//ratio of lengths of far to near windows
const double MAX_DZ = 250;//maximum z-displacement between prompt and delay
const int kNcell = ncol * nrow;
//***********************************************************
//***********************************************************
//Author: Don Jones                                        **
//Date:  May 2019
//
//**This program explores the variation in half-life from  **
//**the fit to the Po-212 dt distribution that arises from **
//**varying the bin size and the end point of the distrib- **
//**bution
//***********************************************************
//***********************************************************

//Return live time in hours
//--------------------------------
double GetLiveTime(TChain *ch, bool run_time = 0){
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  TString st;
  double tlive = 0, tl = 0;
  bool first = 1;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    tl = ((TVectorD*)file->Get("runtime"))->Norm1();
    double deadt = ((TVectorD*)ch->GetFile()->Get("BiPoTreePlugin/pileup_veto_dt"))->Norm1();
    if(run_time)
      tlive += tl;
    else
      tlive += tl - 2*deadt;
    st = TString(element->GetTitle());
    if(first){
      first = 0;
      time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi());
      printf("Date of first file: %s", asctime(localtime(&ts)));
    }
  }
  time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi() + tl);
  printf("Date of last file: %s", asctime(localtime(&ts)));
  return tlive;
}


int BiPodtFitRange(int alpha_type = 1){
  //Set boundary cut values on energy, psd, z-pos and time
  //-------------------------------------------------------
  double f2n = F2N > 12.0 ? 12.0 : F2N, n2f = 1.0/f2n;
  double hAE = 1.0, lAE = 0.72, hApsd = 0.34, lApsd = 0.17;//alpha
  double highBE = 4.0, lowBE = 0.0, hPpsd = 0.22, lPpsd = 0.05;//beta
  double t_start = 0.01, t_end = 3 * tauBiPo;//prompt window
  double ft_offset = 10 * tauBiPo;//far window time offset
  double ft_start = ft_offset;//start time of far window 
  double ft_end = ft_start + f2n * (t_end - t_start);//far window
  double  l_dZ = alpha_type==1 ? -200 : -MAX_DZ, h_dZ = fabs(l_dZ);
  double l_t = 0.005, h_t = 3*tauBiPo;
  if(alpha_type == 1){
    t_start = 7.0e-4;
    t_end = 0.0017;
    highBE = 3.0;
    hAE = 1.27;
    lAE = 0.95;
    f2n = F2N, n2f = 1.0/f2n;
    ft_end = ft_start + f2n * (t_end - t_start); 
  }else if(alpha_type == 2){
    t_start = 7.0e-4;
    hAE = 1.27;
    ft_end = ft_start + f2n * (t_end - t_start); 
  }
  //-------------------------------------------------------
  gStyle->SetOptFit(1111);
  BP *bp = new BP();
  TChain *ch = bp->chain;
  double live_t = GetLiveTime(ch);
  cout<<"Run time: "<<GetLiveTime(ch,1)<<" sec."<<endl;
  cout<<"Live time: "<<live_t<<" sec."<<endl;
  TH1D *hn[20];
  for(int i=0;i<20;++i){
    int n = i*5+5;
    hn[i] = new TH1D(Form("hn%i",i),Form("hn%i",i),n,t_start,t_end);
    hn[i]->Sumw2();
  }
  TH1D* h = new TH1D(Form("h"),Form("h"),400,t_start,t_start+0.004);
  h->Sumw2();
  TH1D* hbkg = new TH1D(Form("hbkg"),Form("hbkg"),100,l_t,h_t);
  hbkg->Sumw2();
  TH1D* hacc = new TH1D(Form("hacc"),Form("hacc"),100,ft_start,ft_end);
  hacc->Sumw2();
  int nEnt = bp->fChain->GetEntries()/10;
  for(Long64_t i=0;i<bp->fChain->GetEntries();++i){
    if(i%nEnt==0)cout<<"*"<<flush;
    
    bp->LoadTree(i);
    bp->GetEntry(i);
    //Apply alpha cuts
    //-------------------------------------------
    if(!(abs(bp->az)<1000))continue;//alpha position
    if(bp->aE<lAE || bp->aE > hAE)continue;//alpha energy
    if(bp->aPSD < lApsd || bp->aPSD > hApsd)continue;//alpha PSD
    //--------------------------------------------
    //Fill Prompt Window Plots
    //-------------------------------------------
    double scale = 0, end_t = alpha_type==1 ? t_end : 3*tauBiPo;
    for(int j=0;j<bp->mult_prompt;++j){
      if( (bp->pmult_clust->at(j) != bp->pmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->pEtot->at(j) < lowBE || bp->pEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      if(bp->pPSD->at(j) < lPpsd || bp->pPSD->at(j) > hPpsd)
	continue;
      if(!(fabs(bp->pz->at(j)) < 1000))
	continue;
      double dx = kCellSize*((bp->aseg - bp->pseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->pseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->pz->at(j);
      if(dz < l_dZ || dz > h_dZ)continue;
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;
      double dt = bp->at - bp->pt->at(j);
      if(dt > l_t && dt < h_t){
	//accidentals + correlated background from Bi214 in Bi212 data
	hbkg->Fill(dt);
      }
      if(dt > t_start && dt < t_start+0.004)
	h->Fill(dt);
      if(dt > t_start && dt < t_end){
	for(int k=0;k<20;++k)
	  hn[k]->Fill(dt);

      }
    }
    for(int j=0;j<bp->mult_far;++j){
      if( (bp->fmult_clust->at(j) != bp->fmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->fEtot->at(j) < lowBE || bp->fEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      if(bp->fPSD->at(j) < lPpsd || bp->fPSD->at(j) > hPpsd)continue;
      if(!(fabs(bp->fz->at(j)) < 1000)) continue;
      double dx = kCellSize*((bp->aseg - bp->fseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->fseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->fz->at(j);
      if(dz < l_dZ || dz > h_dZ)continue;
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;
      double dt = bp->ft->at(j) - bp->at;
      if(dt > ft_start && dt < ft_end){
	hacc->Fill(dt);
      }
    }
  }
  cout<<endl;
  TCanvas *cx = new TCanvas("cx","cx",0,0,2000,600);
  cx->Divide(3,1);
  cx->cd(1);
  cout<<"Entries: "<<h->Integral(1,100);
  h->Scale(1/h->GetBinWidth(1)/live_t);
  hbkg->Scale(1/hbkg->GetBinWidth(1)/live_t);
  hacc->Scale(1/hacc->GetBinWidth(1)/live_t);
  h->Draw();
  cx->cd(2);
  hbkg->Draw();
  gPad->Update();
  cx->cd(3);
  TF1 *fpol0 = new TF1("fpol0","pol0",0,1);
  hacc->Fit(fpol0);
  TF1 *f = new TF1("f","[0]*exp(-x/[1])+[2]*exp(-x/0.2370348)+[3]",0.0007,0.7);
  f->FixParameter(0,0);
  f->FixParameter(1,1);
  f->SetParameter(2,0);
  f->FixParameter(3, fpol0->GetParameter(0));
  hbkg->Fit(f,"B");
  hacc->Draw();
  f->ReleaseParameter(0);
  f->ReleaseParameter(1);
  f->FixParameter(2, f->GetParameter(2));
  TCanvas *cc = new TCanvas("cc","cc",0,600,1200,600);
  cc->Divide(2,1);
  cc->cd(1);
  TGraph *grc = new TGraph();
  TGraphErrors *grv = new TGraphErrors();
  TGraphErrors *grR1= new TGraphErrors(), *grR2= new TGraphErrors();
  for(int i=0;i<80;++i){
    double x = 0.0011001+0.00005*i;
    f->SetParameter(0, h->GetMaximum()*5);
    f->SetParameter(1, 0.00043);
    f->SetRange(0.0006999,x);
    if(x>0.0047)break;
    TFitResultPtr ftr = h->Fit(f,"SRB");
    TMatrixDSym cov = ftr->GetCovarianceMatrix();
    grR1->SetPoint(i, x/0.000299,f->GetParameter(1)*f->GetParameter(0)*1000);
    double er = sqrt(cov[0][0]*pow(f->GetParameter(1),2)+cov[1][1]*pow(f->GetParameter(0),2)+2*cov[0][1]*f->GetParameter(0)*f->GetParameter(1));
    grR1->SetPointError(i, 0, er*1000);
    grv->SetPoint(i,x/0.000299, f->GetParameter(1)*1000*log(2));
    grv->SetPointError(i,0,f->GetParError(1)*1000*log(2));
    grc->SetPoint(i,x/0.000299, f->GetProb());
    cout<<i<<" "<<x<<" "<<x/0.000299<<" "<<f->GetParameter(1)*1000*log(2)<<"+/-"<<f->GetParError(1)*1000*log(2)<<" "<<f->GetProb()<<" "<<f->GetNDF()<<endl;
  }
  grv->SetMarkerColor(kBlue);
  grv->SetLineColor(kBlue);
  grv->SetMarkerStyle(8);
  grc->SetMarkerColor(kBlue);
  grc->SetLineColor(kBlue);
  grc->SetMarkerStyle(8);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.05);
  grv->Draw("alp");
  gPad->Update();
  TLine *tl = new TLine(t_end/0.000299,grv->GetYaxis()->GetXmin(),t_end/0.000299,grv->GetYaxis()->GetXmax());
  tl->SetLineWidth(2);
  tl->SetLineStyle(5);
  tl->Draw();
  grv->SetTitle("Half-life of Po212 vs. Fit Range");
  grv->GetXaxis()->SetTitle("End of Fit Range (# of half-lives)");
  grv->GetYaxis()->SetTitle("Half-life (#mus)");
  cc->cd(2);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.05);
  grc->Draw("alp");
  TLine *tl2 = new TLine(t_end/0.000299,grc->GetYaxis()->GetXmin(),t_end/0.000299,grc->GetYaxis()->GetXmax());
  tl2->SetLineWidth(2);
  tl2->SetLineStyle(5);
  tl2->Draw();
  grc->SetTitle("Fit Probability vs. Fit Range");
  grc->GetXaxis()->SetTitle("End of Fit Range (# of half-lives)");
  grc->GetYaxis()->SetTitle("Probability");

  TCanvas *cc2 = new TCanvas("cc2","cc2",0,0,1200,600);
  TGraph *grc2 = new TGraph();
  TGraphErrors *grv2 = new TGraphErrors();
  grv2->SetMarkerColor(kBlue);
  grv2->SetLineColor(kBlue);
  grv2->SetMarkerStyle(8);
  grc2->SetMarkerColor(kBlue);
  grc2->SetLineColor(kBlue);
  grc2->SetMarkerStyle(8);
  cc2->Divide(2,1);
  cc2->cd(1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.04);
  f->FixParameter(2, f->GetParameter(2));
  f->FixParameter(3, fpol0->GetParameter(0));
  f->SetRange(0.000699999,t_end+0.000000001);
  for(int i=0;i<20;++i){
    hn[i]->Scale(1/hn[i]->GetBinWidth(1)/live_t);
    f->SetParameter(0, hn[i]->GetMaximum()*5);
    f->SetParameter(1, 0.00043);
    TFitResultPtr ftr = hn[i]->Fit(f,"SB");
    TMatrixDSym cov = ftr->GetCovarianceMatrix();
    grR2->SetPoint(i, hn[i]->GetNbinsX(),f->GetParameter(1)*f->GetParameter(0)*1000);
    double er = sqrt(cov[0][0]*pow(f->GetParameter(1),2)+cov[1][1]*pow(f->GetParameter(0),2)+2*cov[0][1]*f->GetParameter(0)*f->GetParameter(1));
    grR2->SetPointError(i, 0, er*1000);
    grc2->SetPoint(i,hn[i]->GetNbinsX(), f->GetProb());//->GetChisquare()/f->GetNDF());
    grv2->SetPoint(i,hn[i]->GetNbinsX(),f->GetParameter(1)*1000*log(2));
    grv2->SetPointError(i,0,f->GetParError(1)*1000*log(2));
  }
  grv2->Draw("alp");
  gPad->Update();
  grv2->SetTitle("Half-life of Po212 vs. #of Bins (0.7#mus<dt<1.7#mus)");
  grv2->GetXaxis()->SetTitle("Number of bins");
  grv2->GetYaxis()->SetTitle("Half-life (#mus)");
  grc2->SetTitle("Fit Probability vs. #of Bins (0.7#mus<dt<1.7#mus)");
  grc2->GetXaxis()->SetTitle("Number of bins");
  grc2->GetYaxis()->SetTitle("Probability");
  cc2->cd(2);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.05);
  grc2->Draw("alp");
  TCanvas *cc3 = new TCanvas("cc3","cc3",0,0,1200,600);
  cc3->Divide(2,1);
  cc3->cd(1);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.05);
  grR1->Draw("alp");
  grR1->SetMarkerStyle(8);
  grR1->SetMarkerColor(kBlue);
  grR1->SetLineColor(kBlue);
  gPad->Update();
  grR1->SetTitle("Po-212 Rate from dt Exp. Fit vs. End of Fit Range");
  grR1->GetXaxis()->SetTitle("End of Fit Range (# of half-lives)");
  grR1->GetYaxis()->SetTitle("Rate (mHz)");
  TLine *tl3 = new TLine(t_end/0.000299,grR1->GetYaxis()->GetXmin(),t_end/0.000299,grR1->GetYaxis()->GetXmax());
  tl3->SetLineWidth(2);
  tl3->SetLineStyle(5);
  tl3->Draw();
  cc3->cd(2);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.05);
  grR2->Draw("alp");
  grR2->SetMarkerStyle(8);
  grR2->SetMarkerColor(kBlue);
  grR2->SetLineColor(kBlue);
  gPad->Update();
  grR2->SetTitle("Po-212 Rate from dt Exp. Fit vs. No. of Bins in Fit Range");
  grR2->GetXaxis()->SetTitle("Number of bins");
  grR2->GetYaxis()->SetTitle("Rate (mHz)");
  cc->SaveAs(Form("%s/Po212HalfLifevsFitRange.pdf",gSystem->Getenv("TECHNOTE")));
  cc2->SaveAs(Form("%s/Po212HalfLifevsNbinsX.pdf",gSystem->Getenv("TECHNOTE")));
  cc3->SaveAs(Form("%s/Po212RatevsNbinsXandFitRange.pdf",gSystem->Getenv("TECHNOTE")));
  return 0;
}
