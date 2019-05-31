#include <time.h>
#include <vector>
#include <map>
#include <iostream>
#include "TSystem.h"
#include "TH1D.h"
#include "TDatime.h"
#include "TVectorD.h"
#include "TChain.h"
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
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TH2D.h"
#include "TPaveText.h"
#include "TPaveStats.h"
#include "BP.C"
#include "PROSPECT_Style.cc"
using namespace std;

using namespace std;
const int N = 3, ncol = 14, nrow = 11, nBINS = 40, nBINST = 30;
const double kCellSize = 146.0;//cell cross sectional size in mm
const double kMaxDisplacement = 550.0;//maximum displacement between alpha and beta (max pulse in prompt cluster)
const double tauBiPo = 0.1643 / log(2);//lifetime of Po214 in ms
const double F2N = 100.0;//ratio of lengths of far to near windows
const int kNcell = ncol * nrow;
const int ExcludeCellArr[63] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 17, 18, 21, 23, 24, 27, 28, 29, 31, 32, 34, 36, 40, 41, 42, 43, 44, 46, 47, 48, 50, 52, 55, 56, 60, 63, 68, 69, 70, 73, 79, 83, 86, 87, 94, 97, 102, 107, 115, 121, 122, 126, 127, 128, 130, 133, 136, 139, 141};
//start and end runs of reactor on times
const int nRxOn = 5;
const int RxOn[nRxOn][2] = {{1520293010, 1521195058}, {1525164995, 1527240253},
			    {1528800853, 1530883525}, {1532430622, 1534551207},
			    {1536060033, 1538184537}};

bool RxStat(int runnum){
  //return 0 if reactor is off 1 if on
  for(int i=0; i<nRxOn; ++i){
    if(runnum >= RxOn[i][0] && runnum <= RxOn[i][1]) return true;
  }
  return false;
}

bool isET(int seg){
  return (seg%14 == 13 || seg%14 == 0 || seg >= 140);
}

//Return live time in hours
//--------------------------------
double GetLiveTime(TChain *ch){
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  TString st;
  int n = 0;
  double tlive = 0, tl = 0;
  bool first = 1;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    tl = ((TVectorD*)file->Get("runtime"))->Norm1();
    tlive += tl;
    st = TString(element->GetTitle());
    if(first){
      first = 0;
      time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi());
      printf("Date of first file: %s", asctime(localtime(&ts)));
    }
    ++n;
  }
  time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi() + tl);
  cout<<n<<" files\n";
  printf("Date of last file: %s", asctime(localtime(&ts)));
  return tlive/3600.0;
}

void AddShade(TGraphErrors *gr){
  gr->Draw("ap");
  gPad->Update();
  TGraphErrors *g[nRxOn];
  for(int i=0;i<nRxOn;++i){
    g[i] = new TGraphErrors(4);
    g[i]->SetPoint(0,RxOn[i][0], gr->GetYaxis()->GetXmin());
    g[i]->SetPoint(1,RxOn[i][0], gr->GetYaxis()->GetXmax());
    g[i]->SetPoint(2,RxOn[i][1], gr->GetYaxis()->GetXmax());
    g[i]->SetPoint(3,RxOn[i][1], gr->GetYaxis()->GetXmin());
    g[i]->SetFillStyle(3013);
    g[i]->SetFillColor(16);
    g[i]->Draw("samef");
  }
  gr->Draw("samep");
  return;
}

int BPvTf(bool fiducialize = 0, int alpha_type = 0, bool useEsmear = 0, bool P2_style = 0, bool recreate = 0){
  //alpha_type = 0, strictly Bi214-->Po214-->Pb210
  //alpha_type = 1, strictly Bi212-->Po212-->Pb208
  //alpha_type = 2, include both
  double HrPerPnt = (alpha_type == 1 ? 167.6 : 47.6);//hours of data per point
  bool slow = 0, time_in_epoch_sec = 0;
  bool deadtime_correct = 1, modular_far_window = 0;
  int nnear = 0, nfar = 0, nalpha = 0;
  TString smear((useEsmear ? "smear" : ""));
  TString smeared((useEsmear ? "Smeared " : ""));
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  gStyle->SetTitleW(0.8);
  gStyle->SetTitleX(0.5);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadLeftMargin(0.15);
  if(P2_style) setup_PROSPECT_style();
  bool exclude_cells = 1;
  TString fid = TString((fiducialize ? "fid":""));
  //Get the TChain
  //----------------
  BP *bp = new BP(); 
  double live = GetLiveTime(bp->chain);
  TChain *ch = bp->chain;
  //  double RxOffT = 263.2;//Time when reactor turned off Mar 16 2018, 07:47
  cout<<"Live time: "<<live<<" hours\n";
  
  //Set boundary cut values on energy, psd, z-pos and time
  //-------------------------------------------------------
  double f2n = F2N > 12.0 ? 12.0 : F2N, n2f = 1.0/f2n;
  double hAE = 1.1, lAE = 0.62, hApsd = 0.34, lApsd = 0.18;//alpha
  double highBE = 4.0, lowBE = 0.0, hPpsd = 0.26, lPpsd = 0;//beta
  double t_start = 0.01, t_end = 3 * tauBiPo;//prompt window
  double ft_offset = 10 * tauBiPo;//far window time offset
  double ft_start = ft_offset;//start time of far window 
  double ft_end = ft_start + f2n * (t_end - t_start);//far window
  double fidZ = fiducialize ? 1000.0 : 1000.0;//444.0;
  if(alpha_type == 1){
    t_start = 7.0e-4;
    //    t_end = t_start+nBINST*(0.002-t_start)/26.0;
    t_end = 0.002;
    hAE = 1.27;
    lAE = 0.95;
    f2n = F2N, n2f = 1.0/f2n;
    ft_start = 0.0043;
    ft_end = ft_start + f2n * (t_end - t_start);
  }else if(alpha_type == 2){
    t_start = 7.0e-4;
    hAE = 1.27;
    ft_end = ft_start + f2n * (t_end - t_start); 
  }
  //-------------------------------------------------------


  //Set up plots
  //-------------------------------------------
  const int NP = 500;
  TH1D *hE[NP][3], *hdt[NP][3], *hZ[NP][3], *hpsd[NP][3];
  TH1D *hZcum[3], *hdtcum[3], *hdtres; 
  TCanvas *c[NP];
  TGraphErrors *gR = new TGraphErrors();
  gR->SetMarkerColor(kBlue);
  gR->SetMarkerStyle(8);
  TGraph *gEff = new TGraph();
  gEff->SetMarkerColor(kBlue);
  gEff->SetMarkerStyle(8);
  TGraphErrors *gR1 = new TGraphErrors();
  gR1->SetMarkerColor(kBlue);
  gR1->SetMarkerStyle(8);
  TGraphErrors *gR2 = new TGraphErrors();
  gR2->SetMarkerColor(kBlue);
  gR2->SetMarkerStyle(8);
  TGraphErrors *ghl = new TGraphErrors();
  ghl->SetMarkerColor(kBlue);
  ghl->SetMarkerStyle(8);
  TGraphErrors *gchi2 = new TGraphErrors();
  gchi2->SetMarkerColor(kBlue);
  gchi2->SetMarkerStyle(8);
  TGraphErrors *gE = new TGraphErrors();
  gE->SetMarkerColor(kBlue);
  gE->SetMarkerStyle(8);
  TGraphErrors *gEW = new TGraphErrors();
  gEW->SetMarkerColor(kBlue);
  gEW->SetMarkerStyle(8);
  TGraphErrors *gRon = new TGraphErrors();
  gRon->SetMarkerColor(kRed);
  gRon->SetMarkerStyle(8);
  TGraphErrors *gEon = new TGraphErrors();
  gEon->SetMarkerColor(kRed);
  gEon->SetMarkerStyle(8);
  TGraphErrors *gEWon = new TGraphErrors();
  gEWon->SetMarkerColor(kRed);
  gEWon->SetMarkerStyle(8);
  TGraph *gAcc = new TGraph();
  gAcc->SetMarkerColor(kRed);
  gAcc->SetMarkerStyle(8);
  bool isFirst = true;
  int file = 0, prev_file = -1, p = 0;
  double t[NP], terr[NP], t0 = 0, tlive[NP], trun[NP], eff[NP];
  for(int i=0;i<NP;++i){
    hE[i][0] = new TH1D(Form("hE%i",i),Form("hE%i",i), nBINS, lAE, hAE);
    hE[i][0]->Sumw2();
    hE[i][0]->SetLineColor(kBlue);
    hE[i][1] = new TH1D(Form("hEfar%i",i),Form("hEfar%i",i), nBINS, lAE, hAE);
    hE[i][1]->Sumw2();
    hE[i][1]->SetLineColor(kMagenta);
    
    hpsd[i][0] = new TH1D(Form("hpsd%i",i),Form("hpsd%i",i), nBINS, lApsd, hApsd);
    hpsd[i][0]->Sumw2();
    hpsd[i][0]->SetLineColor(kBlue);
    hpsd[i][1] = new TH1D(Form("hpsdfar%i",i),Form("hpsdfar%i",i), nBINS, lApsd, hApsd);
    hpsd[i][1]->Sumw2();
    hpsd[i][1]->SetLineColor(kMagenta);

    hdt[i][0] = new TH1D(Form("hdt%i",i),Form("hdt%i",i), nBINST, t_start, t_end);
    hdt[i][0]->Sumw2();
    hdt[i][0]->SetLineColor(kBlue);
    hdt[i][1] = new TH1D(Form("hdtfar%i",i),Form("hdtfar%i",i), nBINST, t_start, t_end);
    hdt[i][1]->Sumw2();
    hdt[i][1]->SetLineColor(kMagenta);
    hZ[i][0] = new TH1D(Form("hZ%i",i),Form("hZ%i",i), 100, -1000, 1000);
    hZ[i][0]->Sumw2();
    hZ[i][0]->SetLineColor(kBlue);
    hZ[i][1] = new TH1D(Form("hZfar%i",i),Form("hZfar%i",i), 100, -1000, 1000);
    hZ[i][1]->Sumw2();
    hZ[i][1]->SetLineColor(kMagenta);
    t[i] = 0; terr[i] = 0; tlive[i] = 0; trun[i] = 0;
  }
  hdtcum[0] = new TH1D("hdtcum","hdtcum", 100, t_start, t_end);
  hdtcum[0]->Sumw2();
  hdtcum[0]->SetLineColor(kBlue);
  hdtcum[1] = new TH1D("hdtcumfar","hdtcumfar", 100, t_start, t_end);
  hdtcum[1]->Sumw2();
  hdtcum[1]->SetLineColor(kMagenta);
  hdtres = new TH1D("hdtres","hdtres", 100, t_start, t_end);
  hdtres->Sumw2();
  hdtres->SetLineColor(kGreen);
  hZcum[0] = new TH1D("hZcum","hZcum", 100, -1000, 1000);
  hZcum[0]->Sumw2();
  hZcum[0]->SetLineColor(kBlue);
  hZcum[1] = new TH1D("hZcumfar","hZcumfar", 100, -1000, 1000);
  hZcum[1]->Sumw2();
  hZcum[1]->SetLineColor(kMagenta);

  TH1D *hbkg = new TH1D("hbkg","hbkg",1000,0,36*tauBiPo);
  TH1D *hdist = new TH1D("hdist","hdist",300,0,3000);
  TH1D *hdistf = new TH1D("hdistf","hdistf",300,0,3000);
  hdistf->SetLineColor(kRed);
  //-------------------------------------------
  

  //Loop over tree
  //-------------------------------------------
  double tot_rt = 0, tot_deadt = 0, ts = 0, prev_ts = 0;
  int nr = 0;
  bool prev_rxstat = 0, last_entry = 0;
  TString prev_st;
  Long64_t nEnt = Long64_t(bp->fChain->GetEntries()/10);
  double mean = (alpha_type == 1 ? 1.064 : 0.845);
  double sigma = 0.055 * sqrt(mean);
  double low = mean - 2.0*sigma , high = mean + 2.0*sigma;
  TF1 *f = new TF1("f","[0]*exp(-0.5*pow((x-[1])/[2],2))",0,1);
  TF1 *fpol0 = new TF1("fpol0","pol0", 0, 1);
  TF1 *fdecay = new TF1("fdecay", "[0]*exp(-x/[1])+[2]", t_start, t_end);
  double tau = 0.237;
  TCanvas *c1;
  int ncut[8] = {0,0,0,0,0,0,0,0};
  for(Long64_t i=0;i<bp->fChain->GetEntries();++i){
    if(i%nEnt==0){cout<<"*"<<std::flush;}
    bp->LoadTree(i);
    bp->GetEntry(i);
    file = bp->fCurrent;
  PROCESS_HISTOS:
    if((file != prev_file) || last_entry){
      if((trun[p] > HrPerPnt * 3600) || last_entry){
	t[p]/=trun[p];
	cout<<"Rx:"<<prev_rxstat<<" Time"<<p<<": "<<t[p]/3600.<<" Livetime: "
	    <<tlive[p]/3600.0<<" Runtime: "<<trun[p]/3600.0<<endl;
	//check for zero error bins
	for(int j=1;j<=hdt[p][0]->GetNbinsX();++j){
	  if(hdt[p][0]->GetBinContent(j)==0&&hdt[p][1]->GetBinContent(j)>0){
	    cout<<"\n\n!Changing hdt error from "<<hdt[p][0]->GetBinError(j)<<
	      " to "<<1<<" on bin "<<j<<endl<<endl;
	    hdt[p][0]->SetBinError(j,1.0);
	  }
	  //hdt[p][0]->SetBinError(j,sqrt(hdt[p][0]->GetBinContent(j)+1.0)+1.0);
	}
	for(int j=1;j<=hpsd[p][0]->GetNbinsX();++j){
	  if(hpsd[p][0]->GetBinContent(j)==0&&hpsd[p][1]->GetBinContent(j)>0){
	    cout<<"\n\n!Changing hpsd error from "<<hpsd[p][0]->GetBinError(j)<<
	      " to "<<1<<" on bin "<<j<<endl<<endl;
	    hpsd[p][0]->SetBinError(j,1.0);
	  }
	}
	for(int j=1;j<=hE[p][0]->GetNbinsX();++j){
	  if(hE[p][0]->GetBinContent(j)==0&&hE[p][1]->GetBinContent(j)>0){
	    cout<<"\n\n!Changing hE error from "<<hE[p][0]->GetBinError(j)<<
	      " to "<<1<<" on bin "<<j<<endl<<endl;
	    hE[p][0]->SetBinError(j,1.0);
	  }
	}
	hE[p][0]->Scale(1/tlive[p]);
	hE[p][1]->Scale(1/tlive[p]);
	hE[p][2] = (TH1D*)hE[p][0]->Clone(Form("hEsub%i",p));
	hE[p][2]->Add(hE[p][1],-1);
	hpsd[p][2] = (TH1D*)hpsd[p][0]->Clone(Form("hpsdsub%i",p));
	hpsd[p][2]->SetLineColor(kRed);
	hpsd[p][2]->Add(hpsd[p][1],-1);
	f->SetParameters(hpsd[p][2]->GetMaximum(), 0.25, 0.02);
	f->SetRange(lApsd, hApsd);
	hpsd[p][2]->Fit(f, "rq");
	double lr = f->GetParameter(1)-2.5*f->GetParameter(2);
	double hr = f->GetParameter(1)+2.5*f->GetParameter(2);
	f->SetRange(lr,hr);
	hpsd[p][2]->Fit(f, "r");
	eff[p] = f->Integral(lApsd,hApsd)/f->Integral(0,1);
	hZ[p][0]->Scale(1/hZ[p][0]->GetBinWidth(1));
	hZ[p][1]->Scale(1/hZ[p][1]->GetBinWidth(1));
	hZ[p][2] = (TH1D*)hZ[p][0]->Clone(Form("hZsub%i",p));
	hZ[p][2]->Add(hZ[p][1],-1);
	hZ[p][2]->SetLineColor(kRed);
	//hdtcum[0]->Add(hdt[p][0]);
	//hdtcum[1]->Add(hdt[p][1]);
	hdt[p][0]->Scale(1/hdt[p][0]->GetBinWidth(1)/tlive[p]);
	hdt[p][1]->Scale(1/hdt[p][1]->GetBinWidth(1)/tlive[p]);
	// if(prev_rxstat==1 || 1){
	//   hdtcum[0]->Add(hdt[p][0]);
	//   hdtcum[1]->Add(hdt[p][1]);
	// }
	hdt[p][2] = (TH1D*)hdt[p][0]->Clone(Form("hdtsub%i",p));
	hdt[p][2]->SetLineColor(kRed);
	hdt[p][2]->Add(hdt[p][1],-1);
	double A = (alpha_type == 1 ? 5.0 : 1.0)*hdt[p][2]->GetMaximum();
	double life_t = alpha_type == 1 ? 0.00043 : tau;
	hdt[p][1]->Fit(fpol0,"N");
	double bk = fpol0->GetParameter(0);
	fdecay->SetParameters(A, life_t, 0);
	fdecay->FixParameter(3, 0);
	gAcc->SetPoint(p,t[p],bk*(t_end-t_start)*1000);
	hdt[p][2]->Fit(fdecay, "QRB");
	
	//set errors using ideal bin values from fit not actual values
	for(int j=1;j<=hdt[p][0]->GetNbinsX();++j){
	  //ideal error from full spectrum before acc subtraction
	  double error = fdecay->Eval(hdt[p][0]->GetBinCenter(j))*tlive[p]*hdt[p][0]->GetBinWidth(1);
	  error = sqrt(error)/(tlive[p]*hdt[p][0]->GetBinWidth(1));
	  //add error from accidental background subtraction
	  
	  hdt[p][2]->SetBinError(j, error);
	}
	TFitResultPtr ftr = hdt[p][2]->Fit(fdecay, "SRB");
	TMatrixDSym cov = ftr->GetCovarianceMatrix();
	bool plot = 0;
	if(plot){
	  TString name;
	  c1 = new TCanvas(Form("c%i",p),Form("c%i",p),0,0,600,500);
	  if(0){
	    name = "Ealpha";
	    hE[p][0]->Draw();
	    gPad->Update();
	    hE[p][0]->GetYaxis()->SetLimits(-0.1*hE[p][0]->GetMaximum(),hE[p][0]->GetMaximum()*1.1);
	    hE[p][0]->GetYaxis()->SetRangeUser(-0.1*hE[p][0]->GetMaximum(),hE[p][0]->GetMaximum()*1.1);
	    hE[p][1]->Draw("same");
	    hE[p][2]->SetLineColor(kRed);
	    hE[p][2]->Draw("sames");
	    gPad->Update();
	  }else if(1){
	    name = "dt";
	    hdt[p][0]->Draw();
	    gPad->Update();
	    hdt[p][0]->GetYaxis()->SetLimits(-0.1*hdt[p][0]->GetMaximum(),hdt[p][0]->GetMaximum()*1.1);
	    hdt[p][0]->GetYaxis()->SetRangeUser(-0.1*hdt[p][0]->GetMaximum(),hdt[p][0]->GetMaximum()*1.1);
	    hdt[p][1]->Draw("same");
	    hdt[p][2]->Draw("sames");
	    gPad->Update();
	  }else if(0){
	    name = "Z";
	    hZ[p][0]->Draw();
	    gPad->Update();
	    hZ[p][0]->GetYaxis()->SetLimits(-0.1*hZ[p][0]->GetMaximum(),hZ[p][0]->GetMaximum()*1.1);
	    hZ[p][0]->GetYaxis()->SetRangeUser(-0.1*hZ[p][0]->GetMaximum(),hZ[p][0]->GetMaximum()*1.1);
	    hZ[p][1]->Draw("sames");
	    hZ[p][2]->Draw("sames");
	  gPad->Update();
	  }else{
	    name = "PSD";
	    hpsd[p][0]->Draw();
	    gPad->Update();
	    hpsd[p][0]->GetYaxis()->SetLimits(-0.1*hpsd[p][0]->GetMaximum(),hpsd[p][0]->GetMaximum()*1.1);
	    hpsd[p][0]->GetYaxis()->SetRangeUser(-0.1*hpsd[p][0]->GetMaximum(),hpsd[p][0]->GetMaximum()*1.1);
	    hpsd[p][1]->Draw("sames");
	    hpsd[p][2]->Draw("sames");

	  }
	  c1->SaveAs(Form("../plots/c%s%i.png",name.Data(),p));
	  delete c1;
	}
	f->SetRange(mean - 2*sigma, mean + 2*sigma);
	f->SetParameters(hE[p][2]->GetMaximum(), mean, sigma);
	hE[p][2]->Fit(f,"rq");
	mean = f->GetParameter(1);
	sigma = f->GetParameter(2);
	double lnsig = (f->GetParameter(1) - lAE)/f->GetParameter(2);
	double hnsig = (hAE - f->GetParameter(1))/f->GetParameter(2);
	eff[p] *= (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
	//eff[p] *= f->Integral(lAE,hAE)/f->Integral(0,2);
	double err;
	double r = hE[p][2]->IntegralAndError(1,hE[p][2]->GetNbinsX(), err)/eff[p];
	err /= eff[p];
	gR->SetPoint(p,t[p],r);
	gR->SetPointError(p,terr[p],err);
	gE->SetPoint(p,t[p],f->GetParameter(1));
	gE->SetPointError(p,terr[p],f->GetParError(1));
	gEff->SetPoint(p,t[p],eff[p]);
	gEW->SetPoint(p,t[p],f->GetParameter(2));
	gEW->SetPointError(p,terr[p],f->GetParError(2));
	if(prev_rxstat){
	  gRon->SetPoint(p,t[p],r);
	  gRon->SetPointError(p,terr[p],err/tlive[p]);
	  gEon->SetPoint(p,t[p],f->GetParameter(1));
	  gEon->SetPointError(p,terr[p],f->GetParError(1));
	  gEWon->SetPoint(p,t[p],f->GetParameter(2));
	  gEWon->SetPointError(p,terr[p],f->GetParError(2));
	}
	gR1->SetPoint(p,t[p],fdecay->GetParameter(0)*fdecay->GetParameter(1)/eff[p]);
	double er = sqrt(cov[0][0]*pow(fdecay->GetParameter(1),2)+cov[1][1]*pow(fdecay->GetParameter(0),2)+2*cov[0][1]*fdecay->GetParameter(0)*fdecay->GetParameter(1))/eff[p];
	gR1->SetPointError(p,terr[p],er);
	ghl->SetPoint(p,t[p],fdecay->GetParameter(1)*log(2));
	ghl->SetPointError(p,terr[p],fdecay->GetParError(1)*log(2));
	gchi2->SetPoint(p,t[p],fdecay->GetChisquare()/(double)fdecay->GetNDF());
	gchi2->SetPointError(p,terr[p],0);
	++p;
      }
      
      double rt = ((TVectorD*)bp->chain->GetFile()->Get("runtime"))->Norm1();
      double deadt = ((TVectorD*)bp->chain->GetFile()->Get("BiPoTreePlugin/pileup_veto_dt"))->Norm1();
      //cout<<"Dead time "<<deadt<<endl;
      TString st(bp->chain->GetFile()->GetName());
      ts = TString(st(st.Last('/')-10,10)).Atof();
      
      if(i==0) t0 = ts;
      t[p] += (ts + 0.5*rt)*rt;
      trun[p] += rt;
      tlive[p] += rt - 2 * deadt;//Correct for pileup veto dead time beta+alpha
      if(!last_entry){
	++nr;
	tot_rt += (rt)/3600.0;
	tot_deadt += (deadt)/3600.0;
      }
    }
    double scale = 0;

    //Apply cuts to alpha
    if(!(fabs(bp->az)<1000))goto WRAPUP;//alpha position
    if(bp->aE < lAE || bp->aE > hAE)goto WRAPUP;
    if(bp->aPSD < lApsd || bp->aPSD > hApsd)goto WRAPUP;
    if(fiducialize && (isET(bp->aseg) || fabs(bp->az)>fidZ))goto WRAPUP;
    ++nalpha;
    
    //Fill prompt window
    for(int j=0;j<bp->mult_prompt;++j){
      ++ncut[7];
      if( (bp->pmult_clust->at(j) != bp->pmult_clust_ioni->at(j)) ){++ncut[0];
       	continue;}//throw out clusters with recoils mixed in
      if(bp->pEtot->at(j) < lowBE || bp->pEtot->at(j) > highBE){++ncut[1];
	continue;}
      if(bp->pPSD->at(j) < lPpsd || bp->pPSD->at(j) > hPpsd){++ncut[2];
	continue;}
      if(!(fabs(bp->pz->at(j)) < 1000)){++ncut[3];
	continue;}
      if(fiducialize && (isET(bp->pseg->at(j)) || fabs(bp->pz->at(j))>fidZ))continue;
      
      double dx = kCellSize*((bp->aseg - bp->pseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->pseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->pz->at(j);
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement){++ncut[4];//discard largely displaced prompt and delayed
	continue;}
      double dt = bp->at - bp->pt->at(j);
      if(dt < t_start){++ncut[5]; continue;}
      if(dt > t_end){++ncut[6]; continue;}
      ++nnear;
      ++scale;
      hdist->Fill(d);
      // if(RxStat(int(ts))==0)
      hdtcum[0]->Fill(dt);
      hdt[p][0]->Fill(dt);
    }
    hE[p][0]->Fill((useEsmear ? bp->aEsmear : bp->aE), scale);
    hpsd[p][0]->Fill(bp->aPSD, scale);
    hZ[p][0]->Fill(bp->az, scale);
    hZcum[0]->Fill(bp->az, scale);

    //Fill far window
    scale = 0;
    for(int j=0;j<bp->mult_prompt;++j){
      if( (bp->pmult_clust->at(j) != bp->pmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->pEtot->at(j) < lowBE || bp->pEtot->at(j) > highBE)continue;
      if(bp->pPSD->at(j) < lPpsd || bp->pPSD->at(j) > hPpsd)continue;
      if(!(fabs(bp->pz->at(j)) < 1000)) continue;
      if(fiducialize && (isET(bp->pseg->at(j)) || fabs(bp->pz->at(j))>fidZ))continue;

      double dx = kCellSize*((bp->aseg - bp->pseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->pseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->pz->at(j);
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;

      double dt = bp->at - bp->pt->at(j);
      hbkg->Fill(dt-ft_start);     
      if(dt < ft_start) continue;
      if(dt > ft_end) continue;
      ++nfar;
      ++scale;
      dt -= ft_start;
      hdistf->Fill(d,n2f);
      if(modular_far_window)
	dt = (dt/(t_end-t_start)  - int(dt/(t_end-t_start)))*(t_end-t_start);
      else dt *= n2f;
      dt += t_start;
      //if(RxStat(int(ts))==0)
      hdtcum[1]->Fill(dt, n2f);     
      hdt[p][1]->Fill(dt, n2f);
    }
    hE[p][1]->Fill((useEsmear ? bp->aEsmear : bp->aE), n2f*scale);
    hpsd[p][1]->Fill(bp->aPSD, n2f*scale);
    hZ[p][1]->Fill(bp->az, n2f*scale);
    hZcum[1]->Fill(bp->az, n2f*scale);

    
  WRAPUP:
    if(i == bp->fChain->GetEntries()-1){
      last_entry = 1;
      ++i;
      goto PROCESS_HISTOS;
    }
    prev_file = file;
    prev_rxstat = RxStat(int(ts));
  }
  cout<<""<<endl;
  cout<<"Total run time "<<tot_rt<<" hours."<<endl;
  cout<<"Total live time "<<tot_rt-tot_deadt<<" hours."<<endl;
  cout<<"Total dead time "<<tot_deadt<<" hours."<<endl;
  TString title[3] = {"(^{214}Bi-->^{214}Po-->^{208}Pb) ","(^{212}Bi-->^{212}Po-->^{210}Pb) ","(Bi-->Po-->Pb) "};
  TCanvas *cR = new TCanvas("cR","cR",0,0,1000,500);
  gR->Draw("ap");
  gR->SetTitle(Form("%s Rate vs Time", title[alpha_type].Data()));
  gR->GetXaxis()->SetTimeDisplay(1);
  gR->GetXaxis()->SetTimeFormat("%m/%d");
  gR->GetXaxis()->SetTitle("Date in 2018");
  gR->GetYaxis()->SetTitle(Form("Rate (Hz)"));
  gR->Fit("pol0");
  gRon->Draw("samep");
  cR->SaveAs(Form("../plots/cR_lE%0.2f_f2n%0.0f_tstart%0.2f_tend%0.2f.png", lAE, f2n, t_start, t_end));
  TCanvas *cE = new TCanvas("cE","cE",0,0,1000,500);
  gE->Draw("ap");
  gE->SetTitle(Form("%s Average Alpha Energy vs Time", title[alpha_type].Data()));
  gE->GetXaxis()->SetTimeDisplay(1);
  gE->GetXaxis()->SetTimeFormat("%m/%d");
  gE->GetXaxis()->SetTitle("Date in 2018");
  gE->GetYaxis()->SetTitle(Form("Average Alpha Energy (MeV)"));
  gEon->Draw("samep");

  TCanvas *cEW = new TCanvas("cEW","cEW",0,0,1000,500);
  gEW->SetTitle(Form("%s Alpha Energy Width vs Time", title[alpha_type].Data()));
  gEW->GetXaxis()->SetTimeDisplay(1);
  gEW->GetXaxis()->SetTimeFormat("%m/%d");
  gEW->GetXaxis()->SetTitle("Date in 2018");
  gEW->GetYaxis()->SetTitle(Form("Alpha Energy Width (MeV)"));
  gEW->Draw("ap");
  gEWon->Draw("samep");

  TCanvas *cpsd = new TCanvas("cpsd","psd",0,0,1000,500);
  gEff->SetTitle(Form("%s Efficiency vs Time", title[alpha_type].Data()));
  gEff->GetXaxis()->SetTimeDisplay(1);
  gEff->GetXaxis()->SetTimeFormat("%m/%d");
  gEff->GetXaxis()->SetTitle("Date in 2018");
  gEff->GetYaxis()->SetTitle(Form("Efficiency"));
  //AddShade(gEff);
  gEff->Draw("ap");

  TCanvas *chl = new TCanvas("chl","chl",0,0,1600,1000);
  chl->Divide(2,2);
  chl->cd(1);
  gR1->SetTitle(Form("%s Rate vs Time", title[alpha_type].Data()));
  gR1->GetXaxis()->SetTimeDisplay(1);
  gR1->GetXaxis()->SetTimeFormat("%m/%d");
  gR1->GetXaxis()->SetTitle("Date in 2018");
  gR1->GetYaxis()->SetTitle(Form("Rate (Hz)"));
  gR1->Fit("fpol0");
  double rate212 = fpol0->GetParameter(0);
  double rate212err = fpol0->GetParError(0);
  double rate212prob = fpol0->GetProb();
  AddShade(gR1);
  double rate214 = 0;
  double rate214err = 0;
  double rate214prob = 0;
  chl->cd(3);
  ghl->SetTitle(Form("%s Half-life vs Time", title[alpha_type].Data()));
  ghl->GetXaxis()->SetTimeDisplay(1);
  ghl->GetXaxis()->SetTimeFormat("%m/%d");
  ghl->GetXaxis()->SetTitle("Date in 2018");
  ghl->GetYaxis()->SetTitle(Form("Half-life (ms)"));
  ghl->Fit("fpol0");
  double pol0th212 = fpol0->GetParameter(0);
  double pol0th212err = fpol0->GetParError(0);
  double pol0th212prob = fpol0->GetProb();
  AddShade(ghl);
  
  chl->cd(4);
  gchi2->SetTitle(Form("#chi^{2}/NDF vs Time"));
  gchi2->GetXaxis()->SetTimeDisplay(1);
  gchi2->GetXaxis()->SetTimeFormat("%m/%d");
  gchi2->GetXaxis()->SetTitle("Date in 2018");
  gchi2->GetYaxis()->SetTitle(Form("#chi^{2}/NDF"));
  gchi2->Fit("fpol0");
  AddShade(gchi2);
  chl->SaveAs(Form("../plots/chl_lE%0.2f_f2n%0.0f_tstart%0.4f_tend%0.4f.png", lAE, f2n, t_start, t_end));
  TCanvas *cZ = new TCanvas("cZ","cZ",0,0,800,600);
  hZcum[0]->Scale(1/hZcum[0]->GetBinWidth(1));
  hZcum[1]->Scale(1/hZcum[1]->GetBinWidth(1));
  hZcum[2] = (TH1D*)hZcum[0]->Clone("hZcumsub");
  hZcum[2]->Add(hZcum[1],-1);
  hZcum[2]->SetLineColor(kRed);
  hZcum[0]->Draw();
  gPad->Update();
  hZcum[0]->GetYaxis()->SetLimits(-0.1*hZcum[0]->GetMaximum(),hZcum[0]->GetMaximum()*1.1);
  hZcum[0]->GetYaxis()->SetRangeUser(-0.1*hZcum[0]->GetMaximum(),hZcum[0]->GetMaximum()*1.1);
  hZcum[1]->Draw("same");
  hZcum[2]->Draw("same");

  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(1111);
  TCanvas *cdtcum = new TCanvas("cdtcum","cdtcum",0,0,800,600);
  hdtcum[0]->Scale(1/hdtcum[0]->GetBinWidth(1));
  hdtcum[1]->Scale(1/hdtcum[1]->GetBinWidth(1));
  hbkg->Scale(1/hbkg->GetBinWidth(1));
  hdtcum[2] = (TH1D*)hdtcum[0]->Clone("hdtcumsub");
  hdtcum[2]->Add(hdtcum[1],-1);
  hdtcum[2]->SetLineColor(kRed);
  hdtcum[0]->Draw();
  gPad->Update();
  hdtcum[0]->GetYaxis()->SetLimits(-0.1*hdtcum[0]->GetMaximum(),hdtcum[0]->GetMaximum()*1.1);
  hdtcum[0]->GetYaxis()->SetRangeUser(-0.1*hdtcum[0]->GetMaximum(),hdtcum[0]->GetMaximum()*1.1);
  hdtcum[1]->Draw("same");
  hdtcum[2]->Draw("sames");
  hdtcum[1]->Fit(fpol0,"N");
  double bk = fpol0->GetParameter(0);
  fdecay->SetParameters(hdtcum[2]->GetMaximum(), tauBiPo, bk);
  fdecay->FixParameter(2, bk);
  hbkg->Fit(fpol0,"N");
  cout<<"\n\n\nNOTE! Two measurements of accidentals: "<<bk<<" "<<fpol0->GetParameter(0)<<endl<<endl<<endl;
  hdtcum[0]->Fit(fdecay,"RB");
  if(alpha_type==1){
    TF1 *fd = (TF1*)fdecay->Clone("fd");
    fd->SetLineColor(kRed);
    hdtcum[2]->Fit(fd,"RB");
  }
  double A212 = fdecay->GetParameter(0);
  double A212err = fdecay->GetParError(0);
  double th212 = fdecay->GetParameter(1)*log(2);
  double th212err = fdecay->GetParError(1)*log(2);
  double A214 = fdecay->GetParameter(2);
  double A214err = fdecay->GetParError(2);
  double probdt = fdecay->GetProb();
  
  cout<<"Alpha candidates: "<<nalpha<<endl;
  cout<<"Prompt beta candidates: "<<nnear<<endl;
  cout<<"Far beta candidates: "<<nfar<<endl;
  cout<<"Near cuts: "<<ncut[0]<<" "<<ncut[1]<<" "<<ncut[2]<<" "<<ncut[3]<<" "<<ncut[4]<<" "<<ncut[5]<<" "<<ncut[6]<<" "<<ncut[7]<<endl;

  for(int i=1;i<=hdtres->GetNbinsX();++i){
    hdtres->SetBinContent(i,hdtcum[0]->GetBinContent(i)-fdecay->Eval(hdtres->GetBinCenter(i)));
    hdtres->SetBinError(i, hdtcum[0]->GetBinError(i));
  }
  hdtres->Draw("same");
  cdtcum->SaveAs(Form("../plots/cdtcum_lE%0.2f_f2n%0.0f_tend%0.2f.png", lAE, f2n, t_end));
  printf("t_start   t_end    f2n      lAE    ft_start     Rate_212       Prob       Rate_214    Prob       T_half(pol0)       Prob            A_212               T_half(exp)                 A214             Prob\n");
  printf("%7.1e   %7.1e %5.1f   %6.2f  %9.2e  %0.4f+/-%0.4f   %0.3f", t_start, t_end, f2n, lAE, ft_start, rate212, rate212err, rate212prob);
  printf("   %0.3f+/-%0.3f  %0.3f  %0.3e+/-%0.3e  %0.3f", rate214, rate214err, rate214prob, pol0th212, pol0th212err, pol0th212prob);
  printf("   %0.3e+/-%0.3e    %0.3e+/-%0.3e   %0.3e+/-%0.3e   %0.3f \n", A212, A212err, th212, th212err, A214, A214err, probdt);
  TCanvas *cbkg = new TCanvas("cbkg","cbkg",600,0,700,500);
  hbkg->Draw();
  TCanvas *cdist = new TCanvas("cdist","cdist",600,0,700,500);
  hdist->Draw();
  hdistf->Draw("sames");
  TCanvas *cx = new TCanvas("cx","cx",0,0,700,500);
  gAcc->Draw("ap");
  gAcc->SetTitle(Form("Background Rate vs Time for Po%i",alpha_type==1?212:214));
  gPad->Update();
  gAcc->GetXaxis()->SetTitle("Date in 2018");
  gAcc->GetXaxis()->SetTimeDisplay(1);
  gAcc->GetXaxis()->SetTimeFormat("%m/%d");
  gAcc->GetYaxis()->SetTitle("Rate (mHz)");
  return 0;
}
