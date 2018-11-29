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
#include "TH2D.h"
#include "TPaveText.h"
#include "TPaveStats.h"
#include "BP.C"
#include "PROSPECT_Style.cc"
using namespace std;

using namespace std;
const int N = 3, ncol = 14, nrow = 11;
const double kCellSize = 146.0;//cell cross sectional size in mm
const double kMaxDisplacement = 700.0;//maximum displacement between alpha and beta (max pulse in prompt cluster)
const double tauBiPo = 0.1643/log(2);
const double n2f = 1.0/12.0;//ratio of lengths of near to far windows
const double f2n = 12.0;//ratio of lengths of far to near windows
const int kNcell = ncol * nrow;
const int ExcludeCellArr[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 17, 18, 21, 23, 24, 27, 28, 29, 31, 32, 34, 36, 40, 41, 42, 43, 44, 46, 47, 48, 50, 52, 55, 56, 60, 63, 68, 69, 70, 73, 79, 83, 86, 87, 94, 97, 102, 107, 115, 121, 122, 126, 127, 128, 130, 133, 136, 139, 141};
//start and end runs of reactor on times
const int nRxOn = 3;
const int RxOn[nRxOn][2] = {{1520293010, 1521195058}, {1525164995, 1527240253},
			    {1528800853, 1530883525}};

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
  }
  time_t ts = time_t(TString(st(st.Last('/')-10,10)).Atoi() + tl);
  printf("Date of last file: %s", asctime(localtime(&ts)));
  return tlive/3600.0;
}

int BiPovsTime(bool fiducialize = 0, int alpha_type = 0, bool useEsmear = 1, bool P2_style = 1, bool recreate = 0){
  //alpha_type = 0, strictly Bi214-->Po214-->Pb210
  //alpha_type = 1, strictly Bi212-->Po212-->Pb208
  //alpha_type = 2, include both
  double HrPerPnt = (alpha_type == 0 ? 23.6 : 47.6);//hours of data per point
  bool slow = 0, time_in_epoch_sec = 0;
  TString smear((useEsmear ? "smear":""));
  TString smeared((useEsmear ? "Smeared ":""));
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
  //  double RxOffT = 263.2;//Time when reactor turned off Mar 16 2018, 07:47
  cout<<"Live time: "<<live<<" hours\n";
  
  //Set boundary cut values on energy, psd, z-pos and time
  //-------------------------------------------------------
  double hAE = 0.98, lAE = 0.73, hApsd = 0.32, lApsd = 0.2;//alpha
  double highBE = 4.0, lowBE = 0.0, hPpsd = 0.26, lPpsd = 0;//beta
  double t_start = 0.01, t_end = 3 * tauBiPo;//prompt window
  double ft_offset = 10 * tauBiPo;//far window time offset
  double ft_start = ft_offset + (t_start * f2n);//start time of far window 
  double ft_end = ft_start + f2n * (t_end - t_start);//far window
  double fidZ = fiducialize ? 1000.0 : 1000.0;//444.0;
  if(alpha_type == 1){
    //    t_start = 6.6e-4;
    t_start = 2.5e-4;
    t_end = 2.5e-3;
    hAE = 1.27;
    lAE = 0.95;
    ft_end = ft_start + f2n * (t_end - t_start); 
  }else if(alpha_type == 2){
    t_start = 2.5e-4;
    hAE = 1.27;
    ft_end = ft_start + f2n * (t_end - t_start); 
  }
  //-------------------------------------------------------


  //Define histos
  //-------------------------------------------
  const int NP = 1000;
  TH1D *hE[NP][N], *hAPSD[NP][N], *hBPSD[NP][N], *hZ[NP][N], *hdZ[NP][N];
  for(int i=0;i<NP;++i){
    for(int j=0;j<N-1;++j){
      hE[i][j] = new TH1D(Form("hE%i_%i",i,j),Form("hE%i_%i",i,j), 50, lAE, hAE);
      hE[i][j]->Sumw2();
      
      hAPSD[i][j] = new TH1D(Form("hAPSD%i_%i",i,j),Form("hAPSD%i_%i",i,j), 50, lApsd, hApsd);
      hAPSD[i][j]->Sumw2();
      
      hBPSD[i][j] = new TH1D(Form("hBPSD%i_%i",i,j),Form("hBPSD%i_%i",i,j), 50, lPpsd, hPpsd);
      hBPSD[i][j]->Sumw2();
      
      hZ[i][j] = new TH1D(Form("hZ%i_%i",i,j),Form("hZ%i_%i",i,j), 200, -1000,1000);
      hZ[i][j]->Sumw2();

      hdZ[i][j] = new TH1D(Form("hdZ%i_%i",i,j),Form("hdZ%i_%i",i,j), 100, -200,200);
      hdZ[i][j]->Sumw2();
    }
  }
  //-------------------------------------------

  
  //Cut efficiencies
  //-------------------------------------------
  double effAE[NP], effAPSD[NP], effBPSD[NP], effdZ[NP], effTot[NP];
  //-------------------------------------------


  //Loop over tree
  //-------------------------------------------
  bool isFirst = true;
  int file = 0, prev_file = 0, p = 0;
  double t[NP], terr[NP], t0 = 0, tlive[NP];
  for(int i=0;i<NP;++i){
    t[i] = 0; terr[i] = 0; tlive[i] = 0;
    effAE[i] = 0; effAPSD[i] = 0; effBPSD[i] = 0; effdZ[i] = 0;
  }

  double tot_live = 0;
  Long64_t nEnt = Long64_t(bp->fChain->GetEntries()/10);
  cout<<nEnt<<endl;
  bool prev_rxstat = 0;
  for(Long64_t i=0;i<bp->fChain->GetEntries();++i){
    bp->LoadTree(i);
    bp->GetEntry(i);
    file = bp->fCurrent;
    if(file != prev_file){
      double rt = ((TVectorD*)bp->chain->GetFile()->Get("runtime"))->Norm1();
      TString st(bp->chain->GetFile()->GetName());
      double ts = TString(st(st.Last('/')-10,10)).Atof();

      if(isFirst){
	t0 = time_in_epoch_sec ? 0.0 : ts;
	t0 = 0;
	isFirst = false;
      }
      //stop when statistics accumulated and break at detector off period
      bool rxstat = RxStat(int(ts));
      double rxOnScale = (rxstat ? 3 : 1);
      if(alpha_type == 1)rxOnScale = 1.0;
      bool onoffchange = (prev_rxstat != rxstat && i!=0);
      prev_rxstat = rxstat;
      if(tlive[p]>HrPerPnt*rxOnScale*3600 || (onoffchange&&0)){
	t[p] /=  tlive[p];
	cout<<"Time"<<p<<": "<<t[p]/3600.<<" Live: "<<tlive[p]/3600.0<<endl;
	++p;
      }
      t[p] += (ts-t0+rt/2.0)*rt;
      tlive[p] += rt;
      tot_live += rt;
    }
    prev_file = file;

    if(i%nEnt==0)cout<<"*"<<flush;
    //Excluded cells cut
    //--------------------------------------------
    if(exclude_cells)
      if( find(begin(ExcludeCellArr), end(ExcludeCellArr), bp->aseg)
	  != end(ExcludeCellArr) )
	 continue;
    //--------------------------------------------

    //Apply alpha cuts
    //-------------------------------------------
    if(!(abs(bp->az)<1000))continue;//alpha position
    if(bp->aE<lAE || bp->aE > hAE)continue;//alpha energy
    if(bp->aPSD<lApsd || bp->aPSD > hApsd)continue;//alpha PSD
    if(fiducialize)
      if( bp->aseg<14 || bp->aseg>139 || //exclude top and bottom cells
    	  bp->aseg%14 == 0 || bp->aseg%14 == 13 ||//exclude end cells
    	  fabs(bp->az) > fidZ)//exclude volume at cell ends
    	continue;//alpha fiducial
    //--------------------------------------------
    
    //Fill Prompt Window Plots
    //-------------------------------------------
    for(int j=0;j<bp->mult_prompt;++j){
      if( (bp->pmult_clust->at(j) != bp->pmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->pEtot->at(j) < lowBE || bp->pEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      double dx = kCellSize*((bp->aseg - bp->pseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->pseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->pz->at(j);
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;
      double dt = bp->at - bp->pt->at(j);
      if(dt > t_start && dt < t_end){
	hE[p][0]->Fill((useEsmear ? bp->aEsmear : bp->aE));
	hAPSD[p][0]->Fill(bp->aPSD);
	hBPSD[p][0]->Fill(bp->pPSD->at(j));
	hZ[p][0]->Fill(bp->az);
	hdZ[p][0]->Fill(bp->az-bp->pz->at(j));
      }
    }
    //-------------------------------------------

    
    //Fill Far Window Plots
    //-------------------------------------------
    for(int j=0;j<bp->mult_far;++j){
      if( (bp->fmult_clust->at(j) != bp->fmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->fEtot->at(j) < lowBE || bp->fEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      
      double dx = kCellSize*((bp->aseg - bp->fseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->fseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->fz->at(j);
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;
      double dt = bp->ft->at(j) - bp->at - ft_offset;
      dt *= n2f;
      if(dt > t_start && dt < t_end){
	hE[p][1]->Fill((useEsmear ? bp->aEsmear : bp->aE), n2f);
	hAPSD[p][1]->Fill(bp->aPSD, n2f);
	hBPSD[p][1]->Fill(bp->fPSD->at(j), n2f);
	hZ[p][1]->Fill(bp->az, n2f);
	hdZ[p][1]->Fill(bp->az-bp->fz->at(j), n2f);
      }
    }
    //-------------------------------------------
  }
  t[p] /=  tlive[p];
  cout<<""<<endl;
  cout<<"Total live time "<<tot_live<<endl;
  TString title[3] = {"(^{214}Bi-->^{214}Po-->^{208}Pb) ","(^{212}Bi-->^{212}Po-->^{210}Pb) ","(Bi-->Po-->Pb) "};

  //Set time offset to beginning of data taking Mar 5, 2018 18:36
  //TDatime da(2018,04,17,23,15,46);
  // gStyle->SetTimeOffset(da.Convert());

  //BiPo rate and efficiency plots
  TGraphErrors *grR = new TGraphErrors();
  grR->SetMarkerColor(kBlue);
  grR->SetMarkerStyle(8);
  grR->SetMarkerSize(0.8);
  grR->SetLineColor(kBlue);
  grR->SetTitle(Form("%s Rate vs Time",title[alpha_type].Data()));
  int col[5] = {kBlack, kBlue, kRed, kGreen+2, kMagenta};
  TPaveText *pt = new TPaveText(0.7,0.6,0.99,0.83,"NDC");
  pt->SetShadowColor(0);
  pt->SetFillColor(0);
  pt->SetTextColor(col[0]);
  pt->AddText("Total Efficiency");
  TMultiGraph *mg = new TMultiGraph();
  mg->SetTitle(Form("%s Cut Efficiency vs Time",title[alpha_type].Data()));
  TGraph *grEff = new TGraph();
  grEff->SetMarkerColor(col[0]);
  grEff->SetMarkerStyle(8);
  grEff->SetMarkerSize(0.8);
  grEff->SetLineColor(col[0]);

  TGraph *grEffAPSD = new TGraph();
  grEffAPSD->SetMarkerColor(col[1]);
  grEffAPSD->SetMarkerStyle(8);
  grEffAPSD->SetMarkerSize(0.8);
  grEffAPSD->SetLineColor(col[1]);
  mg->Add(grEffAPSD);
  TText *tt = (TText*)pt->AddText("PSD_{#alpha} Cut Efficiency");
  tt->SetTextColor(col[1]);

  TGraph *grEffBPSD = new TGraph();
  grEffBPSD->SetMarkerColor(col[2]);
  grEffBPSD->SetMarkerStyle(8);
  grEffBPSD->SetMarkerSize(0.8);
  grEffBPSD->SetLineColor(col[2]);
  mg->Add(grEffBPSD);
  tt = (TText*)pt->AddText("PSD_{#beta} Cut Efficiency");
  tt->SetTextColor(col[2]);

  TGraph *grEffdZ = new TGraph();
  grEffdZ->SetMarkerColor(col[3]);
  grEffdZ->SetMarkerStyle(8);
  grEffdZ->SetMarkerSize(0.8);
  grEffdZ->SetLineColor(col[3]);
  mg->Add(grEffdZ);
  tt = (TText*)pt->AddText("dZ Cut Efficiency");
  tt->SetTextColor(col[3]);

  TGraph *grEffE = new TGraph();
  grEffE->SetMarkerColor(col[4]);
  grEffE->SetMarkerStyle(8);
  grEffE->SetMarkerSize(0.8);
  grEffE->SetLineColor(col[4]);
  mg->Add(grEffE);
  tt = (TText*)pt->AddText("E_{#alpha} Cut Efficiency");
  tt->SetTextColor(col[4]);

  //Alpha energy and rate plots
  gStyle->SetOptFit(0);
  TGraphErrors *grE = new TGraphErrors();
  grE->SetMarkerColor(kBlue);
  grE->SetMarkerStyle(8);
  grE->SetMarkerSize(0.8);
  grE->SetLineColor(kBlue);
  grE->SetTitle(Form("%s #alpha Mean %sEnergy vs Time",title[alpha_type].Data(), smeared.Data()));
  TGraphErrors *grEW = new TGraphErrors();
  grEW->SetMarkerColor(kBlue);
  grEW->SetMarkerStyle(8);
  grEW->SetMarkerSize(0.8);
  grEW->SetLineColor(kBlue);
  grEW->SetTitle(Form("%s #alpha %sEnergy 1#sigma Width vs Time",title[alpha_type].Data(), smeared.Data()));
  TCanvas *ctemp = new TCanvas("ctemp","ctemp",0,0,700,500);
  double guess = alpha_type == 1 ? 1.06 : 0.84;
  double guessErr = 0.05*sqrt(guess);
  TF1 f("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))", 0, 1);
  for(int i=0;i<=p; i++){
    hE[i][2] = (TH1D*)hE[i][0]->Clone(Form("hE%i_2",i));
    hE[i][2]->Add(hE[i][1], -1);
    for(int j=0;j<hE[i][2]->GetNbinsX();++j){//low stat bins with ~0 error bias fit
      if(hE[i][2]->GetBinError(j)<1)hE[i][2]->SetBinError(j,1.0);
    }
    f.SetParameters(hE[i][2]->GetMaximum(), guess, guessErr);
    f.SetRange(guess-2*guessErr, guess+2*guessErr);
    hE[i][2]->Fit("f", "r");
    if(1){//use for printing all energy fits for debugging
      hE[i][0]->Draw();
      hE[i][1]->SetLineColor(kMagenta);
      hE[i][1]->Draw("same");
      hE[i][2]->SetLineColor(kRed);
      hE[i][2]->Draw();
      TPaveText pt(0.75,0.75,1,1,"ndc");
      pt.SetFillColor(0);
      pt.SetShadowColor(0);
      pt.AddText(Form("#chi^{2}/NDF:  %0.3f",f.GetChisquare()/double(f.GetNDF())));
      pt.AddText(Form("Mean E:  %0.3f#pm%0.3f",f.GetParameter(1),f.GetParError(1)));
      pt.AddText(Form("Width E:  %0.3f#pm%0.3f",f.GetParameter(2),f.GetParError(2)));
      pt.Draw();
      gPad->Update();
      TDatime td(t[i]);
      ctemp->SaveAs(Form("../plots/E%s%02i_%02i_%02i_%i.png", smear.Data(), td.GetMonth(), td.GetDay(), td.GetHour(),(alpha_type == 1?212:214)));
    }
    double lnsig = (f.GetParameter(1) - lAE)/f.GetParameter(2);
    double hnsig = (hAE - f.GetParameter(1))/f.GetParameter(2);
    effAE[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
    //effAE[i] = f.Integral(lAE, hAE)/f.Integral(0,5);
    grEffE->SetPoint(i,t[i],effAE[i]);
    if(slow) sleep(1);
    double err;
    double rate = double(hE[i][2]->IntegralAndError(0,hE[i][2]->GetNbinsX(), err))/tlive[i]*1000.0;
    err /= tlive[i]/1000.0;
    grR->SetPoint(i, t[i], rate);
    grR->SetPointError(i, 0, err);
    grE->SetPoint(i, t[i], f.GetParameter(1));
    grE->SetPointError(i, 0, f.GetParError(1));
    grEW->SetPoint(i, t[i], f.GetParameter(2));
    grEW->SetPointError(i, 0, f.GetParError(2));
  }
  TCanvas *cE = new TCanvas("cE","cE",0,0,1200,600);
  cE->Divide(2,1);
  cE->cd(1);
  grE->Draw("ap");
  gPad->Update();
  grE->GetYaxis()->SetTitle("E_{#alpha} (MeV)");
  grE->GetXaxis()->SetTimeDisplay(1);
  grE->GetXaxis()->SetTimeFormat("%m/%d");
  grE->GetXaxis()->SetTitle("Date in 2018");
  grE->Fit("pol0");
  gPad->Update();
  cE->cd(2);
  grEW->Draw("ap");
  gPad->Update();
  grEW->GetYaxis()->SetTitle("E_{#alpha} Width (MeV)");
  grEW->GetXaxis()->SetTimeDisplay(1);
  grEW->GetXaxis()->SetTimeFormat("%m/%d");
  grEW->GetXaxis()->SetTitle("Date in 2018");
  
  grEW->Fit("pol0");
  gPad->Update();
  cE->SaveAs(Form("../plots/BiPoAlpha%iEvsT%s.png", alpha_type, fid.Data()));

  //Alpha PSD plots
  TCanvas *cAPSD = new TCanvas("cAPSD","cAPSD",0,0,1200,600);
  cAPSD->Divide(2,1);
  cAPSD->cd(1);
  TGraphErrors *grAPSD = new TGraphErrors();
  grAPSD->SetMarkerColor(kBlue);
  grAPSD->SetMarkerStyle(8);
  grAPSD->SetMarkerSize(0.8);
  grAPSD->SetLineColor(kBlue);
  grAPSD->SetTitle(Form("%s #alpha Mean PSD vs Time",title[alpha_type].Data()));
  TGraphErrors *grAPSDW = new TGraphErrors();
  grAPSDW->SetMarkerColor(kBlue);
  grAPSDW->SetMarkerStyle(8);
  grAPSDW->SetMarkerSize(0.8);
  grAPSDW->SetLineColor(kBlue);
  grAPSDW->SetTitle(Form("%s #alpha PSD 1#sigma Width vs Time",title[alpha_type].Data()));
  for(int i=0;i<=p; i++){
    TF1 f("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1); 
    hAPSD[i][2] = (TH1D*)hAPSD[i][0]->Clone(Form("hAPSD%i_2",i));
    hAPSD[i][2]->Add(hAPSD[i][1], -1);
    f.SetParameters(hAPSD[i][2]->GetMaximum(), 0.25, 0.017);
    f.SetRange(lApsd, hApsd);
    hAPSD[i][2]->Draw();
    hAPSD[i][2]->Fit("f", "rq");
    gPad->Update();
    if(slow) sleep(1);;
    double lnsig = (f.GetParameter(1) - lApsd)/f.GetParameter(2);
    double hnsig = (hApsd - f.GetParameter(1))/f.GetParameter(2);
    effAPSD[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
    grEffAPSD->SetPoint(i,t[i],effAPSD[i]);
    grAPSD->SetPoint(i, t[i], f.GetParameter(1));
    grAPSD->SetPointError(i, 0, f.GetParError(1));
    grAPSDW->SetPoint(i, t[i], f.GetParameter(2));
    grAPSDW->SetPointError(i, 0, f.GetParError(2));
  }
  grAPSD->Draw("ap");
  gPad->Update();
  grAPSD->GetYaxis()->SetTitle("#alpha PSD");
  grAPSD->GetYaxis()->SetTitle("#alpha PSD Width (MeV)");
  grAPSD->GetXaxis()->SetTimeDisplay(1);
  grAPSD->GetXaxis()->SetTimeFormat("%m/%d");
  grAPSD->GetXaxis()->SetTitle("Date in 2018");
  grAPSD->Fit("pol1");
  gPad->Update();
  cAPSD->cd(2);
  grAPSDW->Draw("ap");
  gPad->Update();
  grAPSDW->GetYaxis()->SetTitle("#alpha PSD Width (MeV)");
  grAPSDW->GetXaxis()->SetTimeDisplay(1);
  grAPSDW->GetXaxis()->SetTimeFormat("%m/%d");
  grAPSDW->GetXaxis()->SetTitle("Date in 2018");

  //  grAPSDW->GetYaxis()->SetTitleOffset(0.9);
  grAPSDW->Fit("pol0");
  gPad->Update();
  cAPSD->SaveAs(Form("../plots/BiPoAlpha%iPSDvsT%s.png", alpha_type, fid.Data()));

  //Beta PSD plots
  TCanvas *cBPSD = new TCanvas("cBPSD","cBPSD",0,0,1200,600);
  cBPSD->Divide(2,1);
  cBPSD->cd(1);
  TGraphErrors *grBPSD = new TGraphErrors();
  grBPSD->SetMarkerColor(kBlue);
  grBPSD->SetMarkerStyle(8);
  grBPSD->SetMarkerSize(0.8);
  grBPSD->SetLineColor(kBlue);
  grBPSD->SetTitle(Form("%s #beta Mean PSD vs Time",title[alpha_type].Data()));
  TGraphErrors *grBPSDW = new TGraphErrors();
  grBPSDW->SetMarkerColor(kBlue);
  grBPSDW->SetMarkerStyle(8);
  grBPSDW->SetMarkerSize(0.8);
  grBPSDW->SetLineColor(kBlue);
  grBPSDW->SetTitle(Form("%s #beta PSD 1#sigma Width vs Time",title[alpha_type].Data()));
  for(int i=0;i<=p; i++){
    TF1 f("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1); 
    hBPSD[i][2] = (TH1D*)hBPSD[i][0]->Clone(Form("hBPSD%i_2",i));
    hBPSD[i][2]->Add(hBPSD[i][1], -1);
    f.SetParameters(hBPSD[i][2]->GetMaximum(), 0.14, 0.012);
    f.SetRange(lPpsd, hPpsd);
    hBPSD[i][2]->Fit("f", "rq");
    gPad->Update();
    if(slow) sleep(1);;
    double lnsig = (f.GetParameter(1) - lPpsd)/f.GetParameter(2);
    double hnsig = (hPpsd - f.GetParameter(1))/f.GetParameter(2);
    effBPSD[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
    grEffBPSD->SetPoint(i,t[i],effBPSD[i]);
    grBPSD->SetPoint(i, t[i], f.GetParameter(1));
    grBPSD->SetPointError(i, 0, f.GetParError(1));
    grBPSDW->SetPoint(i, t[i], f.GetParameter(2));
    grBPSDW->SetPointError(i, 0, f.GetParError(2));
  }
  grBPSD->Draw("ap");
  gPad->Update();
  grBPSD->GetYaxis()->SetTitle("#beta PSD");
  grBPSD->GetXaxis()->SetTitle("Hours since Mar. 5, 2018 18:36");
  grBPSD->GetXaxis()->SetTimeDisplay(1);
  grBPSD->GetXaxis()->SetTimeFormat("%m/%d");
  grBPSD->GetXaxis()->SetTitle("Date in 2018");
  grBPSD->Fit("pol1");
  gPad->Update();
  cBPSD->cd(2);
  grBPSDW->Draw("ap");
  gPad->Update();
  grBPSDW->GetYaxis()->SetTitle("#beta PSD Width (MeV)");
  grBPSDW->GetXaxis()->SetTimeDisplay(1);
  grBPSDW->GetXaxis()->SetTimeFormat("%m/%d");
  grBPSDW->GetXaxis()->SetTitle("Date in 2018");
  //  grBPSDW->GetYaxis()->SetTitleOffset(0.9);
  grBPSDW->Fit("pol0");
  gPad->Update();
  cBPSD->SaveAs(Form("../plots/BiPoBeta%iPSDvsT%s.png", alpha_type, fid.Data()));


  //BiPo Z plots
  TCanvas *cZ = new TCanvas("cZ","cZ",0,0,1200,600);
  cZ->Divide(2,1);
  cZ->cd(1);
  TGraphErrors *grZ = new TGraphErrors();
  grZ->SetMarkerColor(kBlue);
  grZ->SetMarkerStyle(8);
  grZ->SetMarkerSize(0.8);
  grZ->SetLineColor(kBlue);
  grZ->SetTitle(Form("%s #alpha Z-distribution Mean vs Time",title[alpha_type].Data()));
  TGraphErrors *grZW = new TGraphErrors();
  grZW->SetMarkerColor(kBlue);
  grZW->SetMarkerStyle(8);
  grZW->SetMarkerSize(0.8);
  grZW->SetLineColor(kBlue);
  grZW->SetTitle(Form("%s #alpha Z-distibution Width vs Time",title[alpha_type].Data()));
  for(int i=0;i<=p; i++){
    hZ[i][2] = (TH1D*)hZ[i][0]->Clone(Form("hZ%i_2",i));
    hZ[i][2]->Add(hZ[i][1], -1);
    hZ[i][2]->Draw();
     gPad->Update();
    if(slow) sleep(1);;
    grZ->SetPoint(i, t[i], hZ[i][2]->GetMean());
    grZ->SetPointError(i, 0, hZ[i][2]->GetMeanError());
    grZW->SetPoint(i, t[i], hZ[i][2]->GetRMS());
    grZW->SetPointError(i, 0, hZ[i][2]->GetRMSError());
  }
  grZ->Draw("ap");
  gPad->Update();
  grZ->GetYaxis()->SetTitle("Z (mm)");
  grZ->GetXaxis()->SetTimeDisplay(1);
  grZ->GetXaxis()->SetTimeFormat("%m/%d");
  grZ->GetXaxis()->SetTitle("Date in 2018");
  grZ->Fit("pol0");
  gPad->Update();
  cZ->cd(2);
  grZW->Draw("ap");
  gPad->Update();
  grZW->GetYaxis()->SetTitle("Z RMS (mm)");
  grZW->GetXaxis()->SetTimeDisplay(1);
  grZW->GetXaxis()->SetTimeFormat("%m/%d");
  grZW->GetXaxis()->SetTitle("Date in 2018");
  grZW->Fit("pol0");
  gPad->Update();
  cZ->SaveAs(Form("../plots/BiPoZ%ivsT%s.png", alpha_type, fid.Data()));

  //BiPo dZ plots
  TCanvas *cdZ = new TCanvas("cdZ","cdZ",0,0,1200,600);
  cdZ->Divide(2,1);
  cdZ->cd(1);
  TGraphErrors *grdZ = new TGraphErrors();
  grdZ->SetMarkerColor(kBlue);
  grdZ->SetMarkerStyle(8);
  grdZ->SetMarkerSize(0.8);
  grdZ->SetLineColor(kBlue);
  grdZ->SetTitle(Form("%s #alpha-#beta dZ Mean vs Time",title[alpha_type].Data()));
  TGraphErrors *grdZW = new TGraphErrors();
  grdZW->SetMarkerColor(kBlue);
  grdZW->SetMarkerStyle(8);
  grdZW->SetMarkerSize(0.8);
  grdZW->SetLineColor(kBlue);
  grdZW->SetTitle(Form("%s #alpha-#beta dZ Width vs Time",title[alpha_type].Data()));

  for(int i=0;i<=p; i++){
    TF1 f("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1); 
    hdZ[i][2] = (TH1D*)hdZ[i][0]->Clone(Form("hdZ%i_2",i));
    hdZ[i][2]->Add(hdZ[i][1], -1);
    f.SetParameters(hdZ[i][2]->GetMaximum(), 0, 55);
    f.SetRange(-200, 200);
    hdZ[i][2]->Draw();
    hdZ[i][2]->Fit("f", "rq");
    double lnsig = (f.GetParameter(1) + 200)/f.GetParameter(2);
    double hnsig = (200 - f.GetParameter(1))/f.GetParameter(2);
    effdZ[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
    grEffdZ->SetPoint(i,t[i],effdZ[i]);
    gPad->Update();
    if(slow) sleep(1);;
    grdZ->SetPoint(i, t[i], f.GetParameter(1));
    grdZ->SetPointError(i, 0, f.GetParError(1));
    grdZW->SetPoint(i, t[i], f.GetParameter(2));
    grdZW->SetPointError(i, 0, f.GetParError(2));
  }
  grdZ->Draw("ap");
  gPad->Update();
  grdZ->GetYaxis()->SetTitle("dZ (mm)");
  grdZ->GetXaxis()->SetTimeDisplay(1);
  grdZ->GetXaxis()->SetTimeFormat("%m/%d");
  grdZ->GetXaxis()->SetTitle("Date in 2018");
  grdZ->Fit("pol0");
  gPad->Update();
  cdZ->cd(2);
  grdZW->Draw("ap");
  gPad->Update();
  grdZW->GetYaxis()->SetTitle("dZ Width (MeV)");
  grdZW->GetXaxis()->SetTimeDisplay(1);
  grdZW->GetXaxis()->SetTimeFormat("%m/%d");
  grdZW->GetXaxis()->SetTitle("Date in 2018");
  grdZW->Fit("pol0");
  gPad->Update();
  cdZ->SaveAs(Form("../plots/BiPodZ%ivsT%s.png", alpha_type, fid.Data()));


  //BiPo rate and efficiency plots
  TCanvas *cR = new TCanvas("cR","cR",0,0,1200,600);
  cR->Divide(2,1);
  cR->cd(1);
  grR->Draw("ap");
  gPad->Update();
  grR->GetYaxis()->SetTitle("BiPo Rate (mHz)");
  grR->GetXaxis()->SetTimeDisplay(1);
  grR->GetXaxis()->SetTimeFormat("%m/%d");
  grR->GetXaxis()->SetTitle("Date in 2018");
  //  TF1 fh("fh","[0]*pow(0.5,(x-[1])/[2])",0,1);
  TF1 fh("fh","[0]*(pow(0.5,(x-[1])/1.81456e8)+[2]*(x-[1]))",0,1);
  fh.SetParameters(25,1523923200,8e-10);
  grR->Fit("fh");
  TPaveText *pth = new TPaveText(0.7,0.8,0.99,0.9,"ndc");
  pth->SetFillColor(0);
  pth->SetShadowColor(0);
  pth->AddText(Form("#chi^{2}/NDF = %0.3f",fh.GetChisquare()/double(fh.GetNDF())));
  double secinyr = 3600*24*365.25;
  //  pth->AddText(Form("T_{1/2} (yr) = %0.2f #pm %0.2f",fh.GetParameter(2)/secinyr,fh.GetParError(2)/secinyr));
  pth->AddText(Form("Percent Change (yr^{-1}) = %0.2f #pm %0.2f",100*fh.GetParameter(2)*secinyr, 100*fh.GetParError(2)*secinyr));
  pth->Draw();
  gPad->Update();
  // TLine *line = new TLine(RxOffT,gPad->GetUymin(),RxOffT,gPad->GetUymax());
  // line->SetLineColor(kBlack);
  // line->SetLineStyle(2);
  // line->Draw();
  cR->cd(2);
  for(int i=0;i<=p; i++){
    grEff->SetPoint(i,t[i],effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i]);
  }
  mg->Draw("ap");
  mg->Add(grEff);
  gPad->Update();
  mg->GetYaxis()->SetTitle("Cut Efficiency");
  mg->GetXaxis()->SetTimeDisplay(1);
  mg->GetXaxis()->SetTimeFormat("%m/%d");
  mg->GetXaxis()->SetTitle("Date in 2018");
  mg->GetYaxis()->SetTitleOffset(2.25);
  pt->Draw();
  gPad->Update();
  cR->SaveAs(Form("../plots/BiPoRate%ivsT%s.png", alpha_type, fid.Data()));

  
  if(1){
    TFile f("BiPoPublicationPlots.root",(recreate == 1 ? "RECREATE" : "UPDATE"),"BiPoPlots");
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.08);
    gStyle->SetOptStat(0);
    TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,300);
    TGraphErrors *grEpub = new TGraphErrors();
    grEpub->SetName(Form("grEvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grEpub->SetTitle(Form("Po%i #alpha %sEnergy vs Time", (alpha_type == 1 ? 212 : 214), smeared.Data()));
    grEpub->SetMarkerStyle(kCircle);
    grEpub->SetMarkerSize(0.8);
    grEpub->SetMarkerColor(kBlue);
    grEpub->SetLineColor(kBlue);
    TF1 fp0("fp0","pol0",0,1);
    grE->Fit("fp0");
    double x, y, norm = fp0.GetParameter(0);
    for(int i=0;i<grE->GetN();++i){
      grE->GetPoint(i, x, y);
      grEpub->SetPoint(i, x, y/norm);
      grEpub->SetPointError(i, 0, grE->GetErrorY(i)/norm);
    }
    grEpub->Draw("ap");
    grEpub->GetYaxis()->SetTitle("E_{#alpha}/#LTE_{#alpha}#GT");
    grEpub->GetXaxis()->SetTitle("Epoch Seconds");
    grEpub->GetYaxis()->SetTitleOffset(0.4);
    grEpub->GetXaxis()->SetTitleOffset(0.7);
    grEpub->GetYaxis()->SetTitleSize(0.07);
    grEpub->GetXaxis()->SetTitleSize(0.07);
    if(!time_in_epoch_sec){
      grEpub->GetXaxis()->SetTimeDisplay(1);
      grEpub->GetXaxis()->SetTimeFormat("%b %d");
      grEpub->GetXaxis()->SetTitle("Date in 2018");
    }
    gPad->Update();
    grEpub->Write();
    c1->SaveAs(Form("%s/PubBiPo%iE%svsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), smear.Data(), fid.Data()));
    
    TCanvas *c2 = new TCanvas("c2","c2",0,0,1200,300);
    TGraphErrors *grEWpub = new TGraphErrors();
    grEWpub->SetName(Form("grsigmaEvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grEWpub->SetTitle(Form("Po%i #alpha %sEnergy 1#sigma Width vs Time", (alpha_type == 1 ? 212 : 214), smeared.Data()));
    grEWpub->SetMarkerStyle(kCircle);
    grEWpub->SetMarkerSize(0.8);
    grEWpub->SetMarkerColor(kBlue);
    grEWpub->SetLineColor(kBlue);
    grEW->Fit("fp0");
    norm = fp0.GetParameter(0);
    for(int i=0;i<grEW->GetN();++i){
      grEW->GetPoint(i, x, y);
      grEWpub->SetPoint(i, x, y/norm);
      grEWpub->SetPointError(i, 0, grEW->GetErrorY(i)/norm);
    }
    grEWpub->Draw("ap");
    grEWpub->GetYaxis()->SetTitle("#sigma_{E}/#LT#sigma_{E}#GT");
    grEWpub->GetXaxis()->SetTitle("Epoch Seconds");
    grEWpub->GetYaxis()->SetTitleOffset(0.4);
    grEWpub->GetXaxis()->SetTitleOffset(0.7);
    grEWpub->GetYaxis()->SetTitleSize(0.07);
    grEWpub->GetXaxis()->SetTitleSize(0.07);
    if(!time_in_epoch_sec){
      grEWpub->GetXaxis()->SetTimeDisplay(1);
      grEWpub->GetXaxis()->SetTimeFormat("%b %d");
      grEWpub->GetXaxis()->SetTitle("Date in 2018");
    }
    gPad->Update();
    grEWpub->Write();
    c2->SaveAs(Form("%s/PubBiPo%iE%sresvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), smear.Data(), fid.Data()));
    
    TCanvas *c3 = new TCanvas("c3","c3",0,0,1200,300);
    TGraphErrors *grdZWpub = new TGraphErrors();
    grdZWpub->SetName(Form("grsigmadZvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grdZWpub->SetTitle(Form("Po%i #DeltaZ 1#sigma Width vs Time", (alpha_type == 1 ? 212 : 214)));
    grdZWpub->SetMarkerStyle(kCircle);
    grdZWpub->SetMarkerSize(0.8);
    grdZWpub->SetMarkerColor(kBlue);
    grdZWpub->SetLineColor(kBlue);
    grdZW->Fit("fp0");
    norm = fp0.GetParameter(0);
    for(int i=0;i<grdZW->GetN();++i){
      grdZW->GetPoint(i, x, y);
      grdZWpub->SetPoint(i, x, y/norm);
      grdZWpub->SetPointError(i, 0, grdZW->GetErrorY(i)/norm);
    }
    grdZWpub->Draw("ap");
    grdZWpub->GetYaxis()->SetTitle("#sigma_{#DeltaZ}/#LT#sigma_{#DeltaZ}#GT");
    grdZWpub->GetXaxis()->SetTitle("Epoch Seconds");
    grdZWpub->GetYaxis()->SetTitleOffset(0.4);
    grdZWpub->GetXaxis()->SetTitleOffset(0.7);
    grdZWpub->GetYaxis()->SetTitleSize(0.07);
    grdZWpub->GetXaxis()->SetTitleSize(0.07);
    if(!time_in_epoch_sec){
      grdZWpub->GetXaxis()->SetTimeDisplay(1);
      grdZWpub->GetXaxis()->SetTimeFormat("%b %d");
      grdZWpub->GetXaxis()->SetTitle("Date in 2018");
    }
    gPad->Update();
    grdZWpub->Write();
    c3->SaveAs(Form("%s/PubBiPo%iZresvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));

    
    TCanvas *c4 = new TCanvas("c4","c4",0,0,1200,300);
    TGraphErrors *grZWpub = new TGraphErrors();
    grZWpub->SetName(Form("grZrmsvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grZWpub->SetTitle(Form("Po%i #alpha Z-distribution RMS Width vs Time", (alpha_type == 1 ? 212 : 214)));
    grZWpub->SetMarkerStyle(kCircle);
    grZWpub->SetMarkerSize(0.8);
    grZWpub->SetMarkerColor(kBlue);
    grZWpub->SetLineColor(kBlue);
    grZW->Fit("fp0");
    norm = fp0.GetParameter(0);
    for(int i=0;i<grZW->GetN();++i){
      grZW->GetPoint(i, x, y);
      grZWpub->SetPoint(i, x, y/norm);
      grZWpub->SetPointError(i, 0, grZW->GetErrorY(i)/norm);
    }
    grZWpub->Draw("ap");
    grZWpub->GetYaxis()->SetTitle("Z_{RMS}/#LTZ_{RMS}#GT");
    grZWpub->GetXaxis()->SetTitle("Epoch Seconds");
    grZWpub->GetYaxis()->SetTitleOffset(0.4);
    grZWpub->GetXaxis()->SetTitleOffset(0.7);
    grZWpub->GetYaxis()->SetTitleSize(0.07);
    grZWpub->GetXaxis()->SetTitleSize(0.07);
    if(!time_in_epoch_sec){
      grZWpub->GetXaxis()->SetTimeDisplay(1);
      grZWpub->GetXaxis()->SetTimeFormat("%b %d");
      grZWpub->GetXaxis()->SetTitle("Date in 2018");
    }
    gPad->Update();
    grZWpub->Write();
    c4->SaveAs(Form("%s/PubBiPo%iZrmsvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));



    f.Close();
  }
  delete bp;
  return 0;
}
