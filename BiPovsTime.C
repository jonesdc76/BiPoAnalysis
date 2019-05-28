#include <time.h>
#include <vector>
#include <map>
#include <iostream>
#include "TSystem.h"
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

using namespace std;
const int N = 3, ncol = 14, nrow = 11, nBINS = 40;
const double kCellSize = 146.0;//cell cross sectional size in mm
const double kMaxDisplacement = 550.0;//maximum displacement between alpha and beta (max pulse in prompt cluster)
const double tauBiPo = 0.1643 / log(2);
const double F2N = 100.0;//ratio of lengths of far to near windows
const double MAX_DZ = 250;//maximum z-displacement between prompt and delay
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

void AddShade(TGraph *gr){
  gr->Draw("ap");
  gPad->Update();
  TGraph *g[nRxOn];
  for(int i=0;i<nRxOn;++i){
    g[i] = new TGraph(4);
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

TH1D* BiPovsTime(bool fiducialize = 0, int alpha_type = 0, bool P2_style = 1, bool recreate = 0){
  //alpha_type = 0, strictly Bi214-->Po214-->Pb210
  //alpha_type = 1, strictly Bi212-->Po212-->Pb208
  //alpha_type = 2, include both
  double HrPerPnt = (alpha_type == 1 ? 164.6 : 47.6);//hours of data per point
  bool slow = 0;

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  gStyle->SetTitleW(0.8);
  gStyle->SetTitleX(0.5);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadLeftMargin(0.15);
  TStyle *pStyle = new TStyle();
  if(P2_style) setup_PROSPECT_style(pStyle);
  bool exclude_cells = 1, modular_far_window = 0;
  TString fid = TString((fiducialize ? "fid":""));
  //Get the TChain
  //----------------
  BP *bp = new BP(); 
  double live = GetLiveTime(bp->chain);
  cout<<"Live time: "<<live<<" hours\n";
  
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
  double fidZ = fiducialize ? 1000.0 : 1000.0;//444.0;
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


  //Define histos
  //-------------------------------------------
  const int NP = 500;
  TH1D *hOnAPSD[2], *hOffAPSD[2];
  TH1D *hOnBPSD[2], *hOffBPSD[2];
  TH1D *hOndZ[2], *hOffdZ[2];
  TH1D *hOnZ[2], *hOffZ[2];
  TH1D *hOnE[2], *hOffE[2];
  TH1D *hOndt[2], *hOffdt[2];
  for(int i=0;i<2;++i){
    hOnAPSD[i] = new TH1D(Form("hOnAPSD%i",i), Form("hOnAPSD%i",i), 40, lApsd, hApsd);
    hOnAPSD[i]->Sumw2();
    hOffAPSD[i] = new TH1D(Form("hOffAPSD%i",i), Form("hOffAPSD%i",i), 40, lApsd, hApsd);
    hOffAPSD[i]->Sumw2();
    hOnBPSD[i] = new TH1D(Form("hOnBPSD%i",i), Form("hOnBPSD%i",i), 40, lPpsd, hPpsd);
    hOnBPSD[i]->Sumw2();
    hOffBPSD[i] = new TH1D(Form("hOffBPSD%i",i), Form("hOffBPSD%i",i), 40, lPpsd, hPpsd);
    hOffBPSD[i]->Sumw2();
    hOndZ[i] = new TH1D(Form("hOndZ%i",i), Form("hOndZ%i",i), 40, l_dZ, h_dZ);
    hOndZ[i]->Sumw2();
    hOffdZ[i] = new TH1D(Form("hOffdZ%i",i), Form("hOffdZ%i",i),40, l_dZ, h_dZ);
    hOffdZ[i]->Sumw2();
    hOnZ[i] = new TH1D(Form("hOnZ%i",i), Form("hOnZ%i",i), 40, -900, 900);
    hOnZ[i]->Sumw2();
    hOffZ[i] = new TH1D(Form("hOffZ%i",i), Form("hOffZ%i",i), 40, -900, 900);
    hOffZ[i]->Sumw2();
    hOnE[i] = new TH1D(Form("hOnE%i",i), Form("hOnE%i",i), 40, lAE, hAE);
    hOnE[i]->Sumw2();
    hOffE[i] = new TH1D(Form("hOffE%i",i), Form("hOffE%i",i), 40, lAE, hAE);
    hOffE[i]->Sumw2();
    hOndt[i] = new TH1D(Form("hOndt%i",i), Form("hOndt%i",i), 40, t_start, t_end);
    hOndt[i]->Sumw2();
    hOffdt[i] = new TH1D(Form("hOffdt%i",i), Form("hOffdt%i",i), 40, t_start, t_end);
    hOffdt[i]->Sumw2();
  }
  TH1D *hE[NP][N], *hEsmear[NP][N], *hAPSD[NP][N], *hBPSD[NP][N], *hBPSDcum[N];
  TH1D *hZ[NP][N],*hZcum[N], *hdZcum[N], *hdZ[NP][N];
  TH1D *hdt[NP][N], *hdtbkg[NP], *hdtcum[N], *hdtbkgcum;
  double l_t = 0.005, h_t = 3*tauBiPo;
  for(int i=0;i<NP;++i){
    hdtbkg[i] = new TH1D(Form("hdtbkg%i",i),Form("hdtbkg%i",i), 100, l_t, h_t);
    hdtbkg[i]->Sumw2();
    for(int j=0; j<N-1; ++j){
      hE[i][j] = new TH1D(Form("hE%i_%i",i,j),Form("hE%i_%i",i,j), nBINS, lAE, hAE);
      hE[i][j]->Sumw2();

      hEsmear[i][j] = new TH1D(Form("hEsmear%i_%i",i,j),Form("hEsmear%i_%i",i,j), nBINS, lAE, hAE);
      hEsmear[i][j]->Sumw2();
      
      hAPSD[i][j] = new TH1D(Form("hAPSD%i_%i",i,j),Form("hAPSD%i_%i",i,j), nBINS, lApsd, hApsd);
      hAPSD[i][j]->Sumw2();
      
      hBPSD[i][j] = new TH1D(Form("hBPSD%i_%i",i,j),Form("hBPSD%i_%i",i,j), nBINS, lPpsd, hPpsd);
      hBPSD[i][j]->Sumw2();
      
      hZ[i][j] = new TH1D(Form("hZ%i_%i",i,j),Form("hZ%i_%i",i,j), 100, -1000,1000);
      hZ[i][j]->Sumw2();

      hdZ[i][j] = new TH1D(Form("hdZ%i_%i",i,j),Form("hdZ%i_%i",i,j), nBINS, l_dZ, h_dZ);
      hdZ[i][j]->Sumw2();

      hdt[i][j] = new TH1D(Form("hdt%i_%i",i,j),Form("hdt%i_%i",i,j), nBINS, t_start, t_end);
      hdt[i][j]->Sumw2();
    }
  }
  int nbins = 100;
      
  hBPSDcum[0] = new TH1D("hBPSDcum0","hBPSDcum0", nBINS, lPpsd, hPpsd);
  hBPSDcum[0]->Sumw2();
  hBPSDcum[1] = new TH1D("hBPSDcum1","hBPSDcum1", nBINS, lPpsd, hPpsd);
  hBPSDcum[1]->Sumw2();
  hdtcum[0] = new TH1D(Form("hdtcum0"),Form("hdtcum0"), nbins, t_start, t_end);
  hdtcum[0]->Sumw2();
  hdtcum[1] = new TH1D(Form("hdtcum1"),Form("hdtcum1"), nbins, t_start, t_end);
  hdtcum[1]->Sumw2();
  hdtbkgcum = new TH1D(Form("hdtbkgcum"),Form("hdtbkgcum"), nbins, l_t, h_t);
  hdtbkgcum->Sumw2();
  hZcum[0] = new TH1D(Form("hZcum0"),Form("hZcum0"), nbins, -1000, 1000);
  hZcum[0]->Sumw2();
  hZcum[1] = new TH1D(Form("hZcum1"),Form("hZcum1"), nbins, -1000, 1000);
  hZcum[1]->Sumw2();
  hdZcum[0] = new TH1D(Form("hdZcum0"),Form("hdZcum0"), nbins, l_dZ, h_dZ);
  hdZcum[0]->Sumw2();
  hdZcum[1] = new TH1D(Form("hdZcum1"),Form("hdZcum1"), nbins, l_dZ, h_dZ);
  hdZcum[1]->Sumw2();
  //-------------------------------------------

  
  //Cut efficiencies
  //-------------------------------------------
  double effAE[NP], effAPSD[NP], effBPSD[NP], effdZ[NP];
  //-------------------------------------------


  //Loop over tree
  //-------------------------------------------
  bool isFirst = true;
  int file = 0, prev_file = -1, p = 0, nnear = 0, nfar = 0;
  double t[NP], terr[NP], tlive[NP], trun[NP];
  for(int i=0;i<NP;++i){
    t[i] = 0, terr[i] = 0, tlive[i] = 0, trun[i] = 0;
    effAE[i] = 0, effAPSD[i] = 0, effBPSD[i] = 0, effdZ[i] = 0;
  }

  double tot_live = 0, t_on = 0, t_off = 0;
  Long64_t nEnt = Long64_t(bp->fChain->GetEntries()/10);
  cout<<nEnt<<endl;
  bool prev_rxstat = 0, rxstat = 0;
  for(Long64_t i=0;i<bp->fChain->GetEntries();++i){
    bp->LoadTree(i);
    bp->GetEntry(i);
    file = bp->fCurrent;
    if(file != prev_file){
      double rt = ((TVectorD*)bp->chain->GetFile()->Get("runtime"))->Norm1();
      double deadt = ((TVectorD*)bp->chain->GetFile()->Get("BiPoTreePlugin/pileup_veto_dt"))->Norm1();
      TString st(bp->chain->GetFile()->GetName());
      double ts = TString(st(st.Last('/')-10,10)).Atof();

      //stop when statistics accumulated and break at detector off period
      rxstat = RxStat(int(ts));
      if(rxstat){
	t_on += rt - 2 * deadt;
      }else{
	t_off += rt - 2 * deadt;
      }
      double rxOnScale = (rxstat ? 3 : 1);
      if(alpha_type == 1)rxOnScale = 1.0;
      bool onoffchange = (prev_rxstat != rxstat && i!=0);
      prev_rxstat = rxstat;
      // if(hdt[p][0]->GetBinContent(nBINS)-hdt[p][1]->GetBinContent(nBINS) >= rxOnScale*(alpha_type==1 ? 25. : 100.)){
      if(trun[p]>HrPerPnt*rxOnScale*3600 || (onoffchange&&0)){
	t[p] /=  trun[p];
	cout<<"Rx:"<<prev_rxstat<<" Time"<<p<<": "<<t[p]/3600.<<" Livetime: "
	    <<tlive[p]/3600.0<<" Runtime: "<<trun[p]/3600.0<<endl;
	++p;
      }
      t[p] += (ts+rt/2.0)*rt;
      trun[p] += rt;
      tlive[p] += rt - 2 * deadt;
      tot_live += rt - 2 * deadt;
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
    if(bp->aPSD < lApsd || bp->aPSD > hApsd)continue;//alpha PSD
    if(fiducialize && (isET(bp->aseg) || fabs(bp->az) > fidZ) )
    	continue;//alpha fiducial
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
      if(fiducialize && (isET(bp->pseg->at(j)) || fabs(bp->pz->at(j))>fidZ))
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
	hdtbkgcum->Fill(dt);
	hdtbkg[p]->Fill(dt);
      }
      if(dt > t_start && dt < t_end){
	++nnear;
	++scale;
	hdZ[p][0]->Fill(dz);
	hdZcum[0]->Fill(dz);
	hBPSD[p][0]->Fill(bp->pPSD->at(j));
	hBPSDcum[0]->Fill(bp->pPSD->at(j));
	hdt[p][0]->Fill(dt);
	hdtcum[0]->Fill(dt);
	if(rxstat){
	  hOnAPSD[0]->Fill(bp->aPSD);
	  hOnBPSD[0]->Fill(bp->pPSD->at(j));
	  hOnZ[0]->Fill(bp->az);
	  hOndZ[0]->Fill(bp->az-bp->pz->at(j));
	  hOnE[0]->Fill(bp->aE);
	  hOndt[0]->Fill(dt);
	}else{
	  hOffAPSD[0]->Fill(bp->aPSD);
	  hOffBPSD[0]->Fill(bp->pPSD->at(j));
	  hOffZ[0]->Fill(bp->az);
	  hOffdZ[0]->Fill(bp->az-bp->pz->at(j));
	  hOffE[0]->Fill(bp->aE);
	  hOffdt[0]->Fill(dt);
	}
      }
    }
    hE[p][0]->Fill(bp->aE, scale);
    hEsmear[p][0]->Fill(bp->aEsmear, scale);
    hAPSD[p][0]->Fill(bp->aPSD, scale);
    hZ[p][0]->Fill(bp->az, scale);
    hZcum[0]->Fill(bp->az, scale);
    //-------------------------------------------

    
    //Fill Far Window Plots
    //-------------------------------------------
    scale = 0;
    for(int j=0;j<bp->mult_far;++j){
      if( (bp->fmult_clust->at(j) != bp->fmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->fEtot->at(j) < lowBE || bp->fEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      if(bp->fPSD->at(j) < lPpsd || bp->fPSD->at(j) > hPpsd)continue;
      if(!(fabs(bp->fz->at(j)) < 1000)) continue;
      if(fiducialize && (isET(bp->fseg->at(j)) || fabs(bp->fz->at(j)) > fidZ) )
	continue;
      double dx = kCellSize*((bp->aseg - bp->fseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->fseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->fz->at(j);
      if(dz < l_dZ || dz > h_dZ)continue;
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;
      double dt = bp->ft->at(j) - bp->at;
      if(dt > ft_start && dt < ft_end){
	++nfar;
	++scale;
	hdZ[p][1]->Fill(dz, n2f);
	hdZcum[1]->Fill(dz, n2f);
	dt -= ft_start;
	if(modular_far_window)
	  dt = (dt/(t_end-t_start)  - int(dt/(t_end-t_start)))*(t_end-t_start);
	else dt *= n2f;
	dt += t_start;
	//if(bp->aseg==bp->fseg->at(j))
	hBPSD[p][1]->Fill(bp->fPSD->at(j), n2f);
	hBPSDcum[1]->Fill(bp->fPSD->at(j), n2f);
	hdt[p][1]->Fill(dt, n2f);
	hdtcum[1]->Fill(dt, n2f);

	if(rxstat){
	  hOnAPSD[1]->Fill(bp->aPSD, n2f);
	  hOnBPSD[1]->Fill(bp->fPSD->at(j), n2f);
	  hOnZ[1]->Fill(bp->az, n2f);
	  hOndZ[1]->Fill(bp->az-bp->fz->at(j), n2f);
	  hOnE[1]->Fill(bp->aE, n2f);
	  hOndt[1]->Fill(dt, n2f);
	}else{
	  hOffAPSD[1]->Fill(bp->aPSD, n2f);
	  hOffBPSD[1]->Fill(bp->fPSD->at(j), n2f);
	  hOffZ[1]->Fill(bp->az, n2f);
	  hOffdZ[1]->Fill(bp->az-bp->fz->at(j), n2f);
	  hOffE[1]->Fill(bp->aE, n2f);
	  hOffdt[1]->Fill(dt, n2f);
	}
      }
    }
    hE[p][1]->Fill(bp->aE, n2f*scale);
    hEsmear[p][1]->Fill(bp->aEsmear, n2f*scale);
    hAPSD[p][1]->Fill(bp->aPSD, n2f*scale);
    hZ[p][1]->Fill(bp->az, n2f*scale);
    hZcum[1]->Fill(bp->az, n2f*scale);
    //-------------------------------------------
  }
  t[p] /=  trun[p];
  cout<<"Rx:"<<prev_rxstat<<" Time"<<p<<": "<<t[p]/3600.<<" Livetime: "
      <<tlive[p]/3600.0<<" Runtime: "<<trun[p]/3600.0<<endl;
  cout<<endl;
  cout<<"Total live time "<<tot_live<<endl;
  TString title[3] = {"(^{214}Bi-->^{214}Po-->^{208}Pb) ","(^{212}Bi-->^{212}Po-->^{210}Pb) ","(Bi-->Po-->Pb) "};

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
  AddShade(grEffAPSD);
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
  grE->SetTitle(Form("%s #alpha Mean Energy vs Time",title[alpha_type].Data()));
  TGraphErrors *grEW = new TGraphErrors();
  grEW->SetMarkerColor(kBlue);
  grEW->SetMarkerStyle(8);
  grEW->SetMarkerSize(0.8);
  grEW->SetLineColor(kBlue);
  grEW->SetTitle(Form("%s #alpha Energy 1#sigma Width vs Time",title[alpha_type].Data()));
  TGraphErrors *grEsmear = new TGraphErrors();
  grEsmear->SetMarkerColor(kBlue);
  grEsmear->SetMarkerStyle(8);
  grEsmear->SetMarkerSize(0.8);
  grEsmear->SetLineColor(kBlue);
  grEsmear->SetTitle(Form("%s #alpha Mean Smeared Energy vs Time",title[alpha_type].Data()));
  TGraphErrors *grEWsmear = new TGraphErrors();
  grEWsmear->SetMarkerColor(kBlue);
  grEWsmear->SetMarkerStyle(8);
  grEWsmear->SetMarkerSize(0.8);
  grEWsmear->SetLineColor(kBlue);
  grEWsmear->SetTitle(Form("%s #alpha Smeared Energy 1#sigma Width vs Time",title[alpha_type].Data()));
  TCanvas *ctemp = new TCanvas("ctemp","ctemp",0,0,700,500);
  double guess = alpha_type == 1 ? 1.064 : 0.845;
  double guessErr = 0.055*sqrt(guess);
  TF1 f("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))", 0, 1);
  
  //Time cut efficiency for Rate from integral of energy distribution
  double t_cut_eff = exp(-t_start/(alpha_type==1 ? 0.00043:tauBiPo));
  t_cut_eff -= exp(-t_end/(alpha_type==1 ? 0.00043:tauBiPo));
  
  for(int i=0;i<=p; i++){
    //Remove zero error bins which bias fits
    for(int j=1;j<=hE[i][0]->GetNbinsX();++j){
      if(hE[i][0]->GetBinContent(j)==0 && hE[i][1]->GetBinContent(j)>0){
	cout<<"Changing error for hE["<<j<<"][0] from "
	    <<hE[i][0]->GetBinError(j)<<" to 1.0"<<endl;
	hE[i][0]->SetBinError(j,1.0);
      }
      if(hE[i][1]->GetBinContent(j)==0 && hE[i][0]->GetBinContent(j)>0){
	cout<<"Changing error for hE["<<j<<"][1] from "
	    <<hE[i][1]->GetBinError(j)<<" to 1.0"<<endl;
	hE[i][1]->SetBinError(j,n2f);      }
    }
    hE[i][2] = (TH1D*)hE[i][0]->Clone(Form("hE%i_2",i));
    hE[i][2]->Add(hE[i][1], -1);
    hEsmear[i][2] = (TH1D*)hEsmear[i][0]->Clone(Form("hEsmear%i_2",i));
    hEsmear[i][2]->Add(hEsmear[i][1], -1);
    f.SetParameters(hE[i][2]->GetMaximum(), guess, guessErr);
    f.SetRange(guess-2*guessErr, guess+2*guessErr);
    hE[i][2]->Fit("f", "r");
    
    //Update guess for changing parameters
    guess = f.GetParameter(1); guessErr = f.GetParameter(2);
    
    if(1){//use for printing all energy fits for debugging
      hE[i][0]->Draw();
      hE[i][1]->SetLineColor(kMagenta);
      hE[i][1]->Draw("same");
      hE[i][2]->SetLineColor(kRed);
      hE[i][2]->Draw("same");
      TPaveText pt(0.75,0.75,1,1,"ndc");
      gPad->Update();
      hE[i][0]->GetYaxis()->SetLimits(-0.1*hE[i][0]->GetMaximum(),1.1*hE[i][0]->GetMaximum());
      hE[i][0]->GetYaxis()->SetRangeUser(-0.1*hE[i][0]->GetMaximum(),1.1*hE[i][0]->GetMaximum());
      pt.SetFillColor(0);
      pt.SetShadowColor(0);
      pt.AddText(Form("#chi^{2}/NDF:  %0.3f",f.GetChisquare()/double(f.GetNDF())));
      pt.AddText(Form("Mean E:  %0.3f#pm%0.3f",f.GetParameter(1),f.GetParError(1)));
      pt.AddText(Form("Width E:  %0.3f#pm%0.3f",f.GetParameter(2),f.GetParError(2)));
      pt.Draw();
      gPad->Update();
      TDatime td(t[i]);
      ctemp->SaveAs(Form("../plots/E%02i_%02i_%02i_%i.png", td.GetMonth(), td.GetDay(), td.GetHour(), (alpha_type == 1?212:214)));
    }
    double lnsig = (f.GetParameter(1) - lAE)/f.GetParameter(2);
    double hnsig = (hAE - f.GetParameter(1))/f.GetParameter(2);
    effAE[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
    //effAE[i] = f.Integral(lAE, hAE)/f.Integral(0,5);
    grEffE->SetPoint(i,t[i],effAE[i]);
    if(slow) sleep(1);
    double err;
    double rate = hE[i][2]->IntegralAndError(1,hE[i][2]->GetNbinsX(), err);
    rate/= tlive[i]*t_cut_eff;
    err /= tlive[i]*t_cut_eff;
    grR->SetPoint(i, t[i], rate);
    grR->SetPointError(i, 0, err);
    grE->SetPoint(i, t[i], f.GetParameter(1));
    grE->SetPointError(i, 0, f.GetParError(1));
    grEW->SetPoint(i, t[i], f.GetParameter(2));
    grEW->SetPointError(i, 0, f.GetParError(2));
    hEsmear[i][2]->Fit("f", "r");
    grEsmear->SetPoint(i, t[i], f.GetParameter(1));
    grEsmear->SetPointError(i, 0, f.GetParError(1));
    grEWsmear->SetPoint(i, t[i], f.GetParameter(2));
    grEWsmear->SetPointError(i, 0, f.GetParError(2));
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
  
  TCanvas *cEsmear = new TCanvas("cEsmear","cEsmear",0,0,1200,600);
  cEsmear->Divide(2,1);
  cEsmear->cd(1);
  grEsmear->Draw("ap");
  gPad->Update();
  grEsmear->GetYaxis()->SetTitle("E_{#alpha} (MeV)");
  grEsmear->GetXaxis()->SetTimeDisplay(1);
  grEsmear->GetXaxis()->SetTimeFormat("%m/%d");
  grEsmear->GetXaxis()->SetTitle("Date in 2018");
  grEsmear->Fit("pol0");
  gPad->Update();
  cE->cd(2);
  grEWsmear->Draw("ap");
  gPad->Update();
  grEWsmear->GetYaxis()->SetTitle("E_{#alpha} Width (MeV)");
  grEWsmear->GetXaxis()->SetTimeDisplay(1);
  grEWsmear->GetXaxis()->SetTimeFormat("%m/%d");
  grEWsmear->GetXaxis()->SetTitle("Date in 2018");
  grEWsmear->Fit("pol0");
  gPad->Update();
  cEsmear->SaveAs(Form("../plots/BiPoAlpha%iEsmearvsT%s.png", alpha_type, fid.Data()));

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
  
  double psd_m = 0.25, psd_w = 0.017;
  for(int i=0;i<=p; i++){
    //Remove zero error bins which bias fits
    for(int j=1;j<=hAPSD[i][0]->GetNbinsX();++j){
      if(hAPSD[i][0]->GetBinContent(j)==0 && hAPSD[i][1]->GetBinContent(j)>0){
	cout<<"Changing error for hAPSD["<<j<<"][0] from "
	    <<hAPSD[i][0]->GetBinError(j)<<" to 1.0"<<endl;
	hAPSD[i][0]->SetBinError(j,1.0);
      }
      if(hAPSD[i][1]->GetBinContent(j)==0 && hAPSD[i][0]->GetBinContent(j)>0){
	cout<<"Changing error for hAPSD["<<j<<"][1] from "
	    <<hAPSD[i][1]->GetBinError(j)<<" to "<<n2f<<endl;
	hAPSD[i][1]->SetBinError(j,n2f);
      }
    }
    TF1 f("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1); 
    hAPSD[i][2] = (TH1D*)hAPSD[i][0]->Clone(Form("hAPSD%i_2",i));
    hAPSD[i][2]->Add(hAPSD[i][1], -1);
    f.SetParameters(hAPSD[i][2]->GetMaximum(), psd_m, psd_w);
    f.SetRange(psd_m - 2.5*psd_w, psd_m + 2.5*psd_w);
    hAPSD[i][2]->Draw();
    hAPSD[i][2]->Fit("f", "rq");
    psd_m = f.GetParameter(1); psd_w = f.GetParameter(2);
    gPad->Update();
    if(slow) sleep(1);
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
  grAPSD->GetYaxis()->SetTitle("#alpha PSD (MeV)");
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

  TGraph *grFOM = new TGraph();
  grFOM->SetMarkerColor(kBlue);
  grFOM->SetMarkerStyle(8);
  grFOM->SetMarkerSize(0.8);
  grFOM->SetLineColor(kBlue);
  grFOM->SetTitle(Form("%s PSD FOM vs Time (#alpha_{PSD}-#beta_{PSD})/(#sigma_{#alpha}+#sigma_{#beta})",title[alpha_type].Data()));

  TF1 *fgaus2 = new TF1("fgaus2","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))+[3]*exp(-pow(x-[1],2)/(2*pow([4],2)))",0,1); 
  hBPSDcum[0]->Add(hBPSDcum[1],-1);
  fgaus2->SetRange(lPpsd, hPpsd);
  psd_m = 0.148; psd_w = 0.016;
  fgaus2->SetParameters(hBPSDcum[0]->GetMaximum()*0.9, psd_m,hBPSDcum[0]->GetMaximum()*0.1,psd_w);
  hBPSDcum[0]->Fit(fgaus2, "r");
  //  hBPSDcum[0]->Draw();
  double psd_w2 = fgaus2->GetParameter(4);
  
  for(int i=0;i<=p; i++){
    //Remove zero error bins which bias fits
    for(int j=1;j<=hBPSD[i][0]->GetNbinsX();++j){
      if(hBPSD[i][0]->GetBinContent(j)==0 && hBPSD[i][1]->GetBinContent(j)>0){
	cout<<"Changing error for hBPSD["<<j<<"][0] from "
	    <<hBPSD[i][0]->GetBinError(j)<<" to 1.0"<<endl;
	hBPSD[i][0]->SetBinError(j,1.0);
      }
      if(hBPSD[i][1]->GetBinContent(j)==0 && hBPSD[i][0]->GetBinContent(j)>0){
	cout<<"Changing error for hBPSD["<<j<<"][1] from "
	    <<hBPSD[i][1]->GetBinError(j)<<" to "<<n2f<<endl;
	hBPSD[i][1]->SetBinError(j,n2f);
      }
    }
    hBPSD[i][2] = (TH1D*)hBPSD[i][0]->Clone(Form("hBPSD%i_2",i));
    hBPSD[i][2]->Add(hBPSD[i][1], -1);
    fgaus2->SetParameters(hBPSD[i][2]->GetMaximum()*0.86, psd_m, psd_w,hBPSD[i][2]->GetMaximum()*0.14, psd_w2);
    fgaus2->SetRange(lPpsd, hPpsd);
    fgaus2->FixParameter(4, psd_w2);
    hBPSD[i][2]->Fit(fgaus2, "rb");
    psd_m = fgaus2->GetParameter(1); psd_w = fgaus2->GetParameter(2);
    gPad->Update();
    if(slow) sleep(1);
    effBPSD[i] = fgaus2->Integral(lPpsd, hPpsd)/fgaus2->Integral(-2,2);
    grEffBPSD->SetPoint(i,t[i],effBPSD[i]);
    grBPSD->SetPoint(i, t[i], fgaus2->GetParameter(1));
    grBPSD->SetPointError(i, 0, fgaus2->GetParError(1));
    grBPSDW->SetPoint(i, t[i], fgaus2->GetParameter(2));
    grBPSDW->SetPointError(i, 0, fgaus2->GetParError(2));
    double x, y;
    grAPSD->GetPoint(i, x, y);
    double fom = y-fgaus2->GetParameter(1);
    grAPSDW->GetPoint(i, x, y);
    fom /= (y + fgaus2->GetParameter(2));
    grFOM->SetPoint(i, t[i], fom);
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
  TCanvas *cFOM = new TCanvas("cFOM","cFOM",0,0,800,600);
  grFOM->Draw("ap");
  gPad->Update();
  grFOM->GetXaxis()->SetTimeDisplay(1);
  grFOM->GetXaxis()->SetTimeFormat("%b %d");
  grFOM->GetXaxis()->SetTitle("Date in 2018");
  grFOM->GetYaxis()->SetTitle("FOM");

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
    hZ[i][0]->Draw();
    hZ[i][2]->Draw();
     gPad->Update();
    if(slow) sleep(1);
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
  gStyle->SetOptFit(1111);
  TCanvas *cdZcum = new TCanvas("cdZcum","cdZcum",0,0,600,500);
  TF1 *fgaus = new TF1("fgaus","[0]*exp(-pow(x,2)/(2*pow([1],2)))+[2]*exp(-pow(x,2)/(2*pow([3],2)))",0,1);
  hdZcum[0]->Add(hdZcum[1],-1);
  fgaus->SetRange(-250, 250);
  fgaus->SetParameters(hdZcum[0]->GetMaximum()*0.9, 45,hdZcum[0]->GetMaximum()*0.1,90);
  hdZcum[0]->Fit(fgaus, "r");
  hdZcum[0]->Draw();
  double dz_w1 = fgaus->GetParameter(1);
  double dz_w2 = fgaus->GetParameter(3);
  TCanvas *cdbg = new TCanvas("cdbg","cdbg",0,0,600,500);
  for(int i=0;i<=p; i++){
    //Remove zero error bins which bias fits
    for(int j=1;j<=hdZ[i][0]->GetNbinsX();++j){
      if(hdZ[i][0]->GetBinContent(j)==0 && hdZ[i][1]->GetBinContent(j)>0){
	cout<<"Changing error for hdZ["<<j<<"][0] from "
	    <<hdZ[i][0]->GetBinError(j)<<" to 1.0"<<endl;
	hdZ[i][0]->SetBinError(j,1.0);
      }
      if(hdZ[i][1]->GetBinContent(j)==0 && hdZ[i][0]->GetBinContent(j)>0){
	cout<<"Changing error for hdZ["<<j<<"][1] from "
	    <<hdZ[i][1]->GetBinError(j)<<" to "<<1<<endl;
	hdZ[i][1]->SetBinError(j, 1);
      }
    }
    fgaus->SetRange(l_dZ, h_dZ);
    hdZ[i][2] = (TH1D*)hdZ[i][0]->Clone(Form("hdZ%i_2",i));
    hdZ[i][2]->SetLineColor(kRed);
    hdZ[i][1]->SetLineColor(kMagenta);
    hdZ[i][2]->Add(hdZ[i][1], -1);
    fgaus->SetParameters(hdZ[i][2]->GetMaximum()*0.9, dz_w1,hdZ[i][2]->GetMaximum()*0.1,dz_w2);
    fgaus->FixParameter(3, dz_w2);
    hdZ[i][0]->Draw();
    hdZ[i][1]->Draw("same");
    hdZ[i][2]->Draw("sames");
    hdZ[i][2]->Fit(fgaus, "rb");
    gPad->Update();
    hdZ[i][0]->GetYaxis()->SetRangeUser(-0.1*hdZ[i][0]->GetMaximum(), 1.1*hdZ[i][0]->GetMaximum());
    effdZ[i] = fgaus->Integral(l_dZ, h_dZ)/fgaus->Integral(-1000,1000);
    grEffdZ->SetPoint(i, t[i], effdZ[i]);
    gPad->Update();
    if(slow) sleep(1);
    grdZ->SetPoint(i, t[i], fgaus->GetParameter(0)/fgaus->GetParameter(2));
    double var = pow(fgaus->GetParError(0)/fgaus->GetParameter(0),2);
    var += pow(fgaus->GetParError(2)/fgaus->GetParameter(2),2);
    grdZ->SetPointError(i, 0, sqrt(var)*fgaus->GetParameter(0)/fgaus->GetParameter(2));
    grdZW->SetPoint(i, t[i], fgaus->GetParameter(1));
    grdZW->SetPointError(i, 0, fgaus->GetParError(1));
    TDatime td(t[i]);
    cdbg->SaveAs(Form("../plots/dZ%02i_%02i_%02i_%i.png", td.GetMonth(), td.GetDay(), td.GetHour(), (alpha_type == 1?212:214)));
  }
  cdZ->cd(1);
  grdZ->Draw("ap");
  gPad->Update();
  grdZ->SetTitle(Form("%s Distribution Amplitude Ratio vs Time", title[alpha_type].Data()));
  grdZ->GetYaxis()->SetTitle("Ratio");
  grdZ->GetXaxis()->SetTimeDisplay(1);
  grdZ->GetXaxis()->SetTimeFormat("%m/%d");
  grdZ->GetXaxis()->SetTitle("Date in 2018");
  grdZ->Fit("pol0");
  AddShade(grdZ);
  // TPaveText *pt1 = new TPaveText(0.15,0.7,0.5,0.8,"ndc");
  // pt1->SetFillColor(0);
  // pt1->SetShadowColor(0);
  // pt1->SetBorderSize(0);
  // pt1->AddText(Form("Width of D2: %0.2f#pm%0.2f",fgaus->GetParameter(3),fgaus->GetParError(3)));
  // pt1->Draw();
  gPad->Update();
  cdZ->cd(2);
  grdZW->Draw("ap");
  gPad->Update();
  grdZW->GetYaxis()->SetTitle("dZ Width (mm)");
  grdZW->GetXaxis()->SetTimeDisplay(1);
  grdZW->GetXaxis()->SetTimeFormat("%m/%d");
  grdZW->GetXaxis()->SetTitle("Date in 2018");
  grdZW->Fit("pol0");
  AddShade(grdZW);
  gPad->Update();
  cdZ->SaveAs(Form("../plots/BiPodZ%ivsT%s.png", alpha_type, fid.Data()));


  //BiPo rate and efficiency plots
  TCanvas *cR = new TCanvas("cR","cR",0,0,1200,600);
  cR->Divide(2,1);
  cR->cd(1);
  for(int i=0;i<grR->GetN();++i){
    double x, y, effx, eff = effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i];
    cout<<effAE[i]<<" "<<effAPSD[i]<<" "<<effBPSD[i]<<" "<<effdZ[i]<<endl;
    grR->GetPoint(i,x,y);
    y /= eff;
    grR->SetPoint(i, x, y);
    grR->SetPointError(i, grR->GetErrorX(i), grR->GetErrorY(i)/eff);
  }
  grR->Draw("ap");
  AddShade(grR);
  gPad->Update();
  grR->GetYaxis()->SetTitle(Form("Primarily Po%i Rate (Hz)", alpha_type == 1? 212: 214));
  grR->GetXaxis()->SetTimeDisplay(1);
  grR->GetXaxis()->SetTimeFormat("%m/%d");
  grR->GetXaxis()->SetTitle("Date in 2018");
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

   //dt distribution plots
  TCanvas *cdt = new TCanvas("cdt","cdt",0,0,1500,600);
  cdt->Divide(2,1);
  cdt->cd(1);
  TGraphErrors *grhl = new TGraphErrors();
  grhl->SetMarkerColor(kBlue);
  grhl->SetMarkerStyle(8);
  grhl->SetMarkerSize(0.8);
  grhl->SetLineColor(kBlue);
  grhl->SetTitle(Form("%s Half-Life vs Time",title[alpha_type].Data()));
  TGraphErrors *grR1 = new TGraphErrors();
  grR1->SetMarkerColor(kBlue);
  grR1->SetMarkerStyle(8);
  grR1->SetMarkerSize(0.8);
  grR1->SetLineColor(kBlue);
  grR1->SetTitle(Form("%s Rate vs Time",title[alpha_type].Data()));
  TGraphErrors *grR2 = new TGraphErrors();
  grR2->SetMarkerColor(kBlue);
  grR2->SetMarkerStyle(8);
  grR2->SetMarkerSize(0.8);
  grR2->SetLineColor(kBlue);
  grR2->SetTitle(Form("Po214 Rate vs Time"));
  TGraph *grChisq = new TGraph();
  grChisq->SetMarkerColor(kBlue);
  grChisq->SetMarkerStyle(8);
  grChisq->SetMarkerSize(0.8);
  grChisq->SetLineColor(kBlue);
  grChisq->SetTitle(Form("#chi^{2} vs Time"));
  TF1 *fpol0 = new TF1("fpol0","pol0",0,1);
  TF1 *fdecay = new TF1("fdecay","[0]*exp(-x/[1])+[2]",t_start, t_end);
  double tau = tauBiPo;
  if(alpha_type==1){
    fdecay = new TF1("fdecay",Form("[0]*exp(-x/[1])+[2]*exp(-x/%f)+[3]",tau),t_start, t_end);
  }
  for(int i=0;i<=p; i++){
    //Remove zero error bins which bias fits
    for(int j=1;j<=hdt[i][0]->GetNbinsX();++j){
      if(hdt[i][0]->GetBinContent(j)==0 && hdt[i][1]->GetBinContent(j)>0){
      	cout<<"Changing error for hdt["<<j<<"][0] from "
      	    <<hdt[i][0]->GetBinError(j)<<" to 1"<<endl;
      }
    }
    hdtbkg[i]->Scale(1/tlive[i]/hdtbkg[i]->GetBinWidth(1));
    hdt[i][0]->Scale(1/tlive[i]/hdt[i][0]->GetBinWidth(1));
    hdt[i][1]->Scale(1/tlive[i]/hdt[i][1]->GetBinWidth(1));
    hdt[i][2] = (TH1D*)hdt[i][0]->Clone(Form("hdt%i_2",i));
    hdt[i][2]->Add(hdt[i][1], -1);
    hdt[i][1]->Fit(fpol0);
    if(alpha_type==1){
      fdecay->ReleaseParameter(2);
      fdecay->ReleaseParameter(3);
      fdecay->SetParameters(0, 1, 0, fpol0->GetParameter(0));
      fdecay->FixParameter(3, fpol0->GetParameter(0));
      fdecay->FixParameter(0,0);
      fdecay->FixParameter(1,1);
      hdtbkg[i]->Fit(fdecay,"B");
      grR2->SetPoint(i,t[i], fdecay->GetParameter(2)*tau);
      grR2->SetPointError(i,0, fdecay->GetParError(2)*tau);
      fdecay->ReleaseParameter(0);
      fdecay->ReleaseParameter(1);
      fdecay->SetParameter(0, hdt[i][2]->GetMaximum()*5);
      fdecay->SetParameter(1, 0.00043);
      fdecay->FixParameter(2, fdecay->GetParameter(2));
      fdecay->FixParameter(3, fdecay->GetParameter(3));
    }
    if(alpha_type == 0){
      fdecay->SetParameters(hdt[i][2]->GetMaximum(), tauBiPo);
      fdecay->FixParameter(2, fpol0->GetParameter(0));
    }
    double eff = effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i];
    TFitResultPtr ftr = hdt[i][0]->Fit(fdecay, "SRB");
    TMatrixDSym cov = ftr->GetCovarianceMatrix();
    grR1->SetPoint(i, t[i],fdecay->GetParameter(1)*fdecay->GetParameter(0)/eff);
    double er = sqrt(cov[0][0]*pow(fdecay->GetParameter(1),2)+cov[1][1]*pow(fdecay->GetParameter(0),2)+2*cov[0][1]*fdecay->GetParameter(0)*fdecay->GetParameter(1))/eff;
    grR1->SetPointError(i, 0, er);
    grhl->SetPoint(i,t[i], fdecay->GetParameter(1)*log(2)*1000);
    grhl->SetPointError(i,0, fdecay->GetParError(1)*log(2)*1000);
    grChisq->SetPoint(i,t[i],fdecay->GetChisquare()/double(fdecay->GetNDF()));
  }
  gStyle->SetOptFit(1111);
  cdt->cd(1);
  gPad->SetLeftMargin(0.12);
  gPad->SetRightMargin(0.06);
  grhl->Draw("ap");
  AddShade(grhl);
  gPad->Update();
  gPad->SetLeftMargin(0.12);
  gPad->SetRightMargin(0.06);
  grhl->GetYaxis()->SetTitle("t_{1/2} (#mus)");
  grhl->GetXaxis()->SetTimeDisplay(1);
  grhl->GetXaxis()->SetTimeFormat("%m/%d");
  grhl->GetXaxis()->SetTitle("Date in 2018");
  grhl->Fit(fpol0);
  double pol0th212 = fpol0->GetParameter(0);
  double pol0th212err = fpol0->GetParError(0);
  double pol0th212prob = fpol0->GetProb();
  gPad->Update();
  cdt->cd(2);
  grChisq->Draw("ap");
  gPad->Update();
  grChisq->GetYaxis()->SetTitle("#chi^{2}");
  grChisq->GetXaxis()->SetTimeDisplay(1);
  grChisq->GetXaxis()->SetTimeFormat("%m/%d");
  grChisq->GetXaxis()->SetTitle("Date in 2018");
  grChisq->Fit(fpol0);
  AddShade(grChisq);
  gPad->Update();
  cdt->SaveAs(Form("%s/BiPo%idTvsT%s.pdf", gSystem->Getenv("TECHNOTE"),(alpha_type==1 ? 212:214), fid.Data()));
  TCanvas *cRate = new TCanvas("cRate","cRate",0,0,1500,600);
  cRate->SetLeftMargin(0.12);
  cRate->Divide(2,1);
  cRate->cd(1);
  grR1->Draw("ap");
  gPad->Update();
  grR1->GetYaxis()->SetTitle(Form("%s Rate (Hz)", title[alpha_type].Data()));
  grR1->GetXaxis()->SetTimeDisplay(1);
  grR1->GetXaxis()->SetTimeFormat("%m/%d");
  grR1->GetXaxis()->SetTitle("Date in 2018");
  grR1->Fit(fpol0);
  if(alpha_type == 1){
    cRate->cd(2);
    grR2->Draw("ap");
    gPad->Update();
    grR2->GetYaxis()->SetTitle(Form("Po214 Background Rate (Hz)"));
    grR2->GetXaxis()->SetTimeDisplay(1);
    grR2->GetXaxis()->SetTimeFormat("%m/%d");
    grR2->GetXaxis()->SetTitle("Date in 2018");
    grR2->Fit(fpol0);
  }
  double rate212 = alpha_type==0? 0 : fpol0->GetParameter(0);
  double rate212err = alpha_type==0? 0 : fpol0->GetParError(0);
  double rate212prob = alpha_type==0? 0 : fpol0->GetProb();
  double rate214 = fpol0->GetParameter(0);
  double rate214err = fpol0->GetParError(0);
  double rate214prob = fpol0->GetProb();
 
  if(1){
    TFile f("BiPoPublicationPlots.root",(recreate == 1 ? "RECREATE" : "UPDATE"),"BiPoPlots");
    gStyle->SetPadRightMargin(0.05);
    gStyle->SetPadLeftMargin(0.08);
    gStyle->SetOptStat(0);
    TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,300);
    TGraphErrors *grEpub = new TGraphErrors();
    grEpub->SetName(Form("grEvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grEpub->SetTitle(Form("Po%i #alpha Energy vs Time", (alpha_type == 1 ? 212 : 214)));
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
    grEpub->GetXaxis()->SetTimeDisplay(1);
    grEpub->GetXaxis()->SetTimeFormat("%b %d");
    grEpub->GetXaxis()->SetTitle("Date in 2018");
    gPad->Update();
    grEpub->Write();
    c1->SaveAs(Form("%s/PubBiPo%iEvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));
    
    TCanvas *c1smear = new TCanvas("c1smear","c1smear",0,0,1200,300);
    TGraphErrors *grEsmearpub = new TGraphErrors();
    grEsmearpub->SetName(Form("grEsmearvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grEsmearpub->SetTitle(Form("Po%i #alpha Smeared Energy vs Time", (alpha_type == 1 ? 212 : 214)));
    grEsmearpub->SetMarkerStyle(kCircle);
    grEsmearpub->SetMarkerSize(0.8);
    grEsmearpub->SetMarkerColor(kBlue);
    grEsmearpub->SetLineColor(kBlue);
    grEsmear->Fit("fp0");
    norm = fp0.GetParameter(0);
    for(int i=0;i<grEsmear->GetN();++i){
      grEsmear->GetPoint(i, x, y);
      grEsmearpub->SetPoint(i, x, y/norm);
      grEsmearpub->SetPointError(i, 0, grEsmear->GetErrorY(i)/norm);
    }
    grEsmearpub->Draw("ap");
    grEsmearpub->GetYaxis()->SetTitle("Smeared E_{#alpha}/#LTE_{#alpha}#GT");
    grEsmearpub->GetXaxis()->SetTitle("Epoch Seconds");
    grEsmearpub->GetYaxis()->SetTitleOffset(0.4);
    grEsmearpub->GetXaxis()->SetTitleOffset(0.7);
    grEsmearpub->GetYaxis()->SetTitleSize(0.07);
    grEsmearpub->GetXaxis()->SetTitleSize(0.07);
    grEsmearpub->GetXaxis()->SetTimeDisplay(1);
    grEsmearpub->GetXaxis()->SetTimeFormat("%b %d");
    grEsmearpub->GetXaxis()->SetTitle("Date in 2018");
    gPad->Update();
    grEpub->Write();
    c1smear->SaveAs(Form("%s/PubBiPo%iEsmearvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));
    
    TCanvas *c2 = new TCanvas("c2","c2",0,0,1200,300);
    TGraphErrors *grEWpub = new TGraphErrors();
    grEWpub->SetName(Form("grSigmaEvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grEWpub->SetTitle(Form("Po%i #alpha Energy 1#sigma Width vs Time", (alpha_type == 1 ? 212 : 214)));
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
    grEWpub->GetXaxis()->SetTimeDisplay(1);
    grEWpub->GetXaxis()->SetTimeFormat("%b %d");
    grEWpub->GetXaxis()->SetTitle("Date in 2018");
    gPad->Update();
    grEWpub->Write();
    c2->SaveAs(Form("%s/PubBiPo%iEresvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));
    
    TCanvas *c2smear = new TCanvas("c2smear","c2smear",0,0,1200,300);
    TGraphErrors *grEWsmearpub = new TGraphErrors();
    grEWsmearpub->SetName(Form("grSigmaEsmearvsTPo%i", (alpha_type == 1 ? 212 : 214)));
    grEWsmearpub->SetTitle(Form("Po%i #alpha Smeared Energy 1#sigma Width vs Time", (alpha_type == 1 ? 212 : 214)));
    grEWsmearpub->SetMarkerStyle(kCircle);
    grEWsmearpub->SetMarkerSize(0.8);
    grEWsmearpub->SetMarkerColor(kBlue);
    grEWsmearpub->SetLineColor(kBlue);
    grEWsmear->Fit("fp0");
    norm = fp0.GetParameter(0);
    for(int i=0;i<grEW->GetN();++i){
      grEWsmear->GetPoint(i, x, y);
      grEWsmearpub->SetPoint(i, x, y/norm);
      grEWsmearpub->SetPointError(i, 0, grEWsmear->GetErrorY(i)/norm);
    }
    grEWsmearpub->Draw("ap");
    grEWsmearpub->GetYaxis()->SetTitle("#sigma_{Esmear}/#LT#sigma_{Esmear}#GT");
    grEWsmearpub->GetXaxis()->SetTitle("Epoch Seconds");
    grEWsmearpub->GetYaxis()->SetTitleOffset(0.4);
    grEWsmearpub->GetXaxis()->SetTitleOffset(0.7);
    grEWsmearpub->GetYaxis()->SetTitleSize(0.07);
    grEWsmearpub->GetXaxis()->SetTitleSize(0.07);
    grEWsmearpub->GetXaxis()->SetTimeDisplay(1);
    grEWsmearpub->GetXaxis()->SetTimeFormat("%b %d");
    grEWsmearpub->GetXaxis()->SetTitle("Date in 2018");
    gPad->Update();
    grEWsmearpub->Write();
    c2smear->SaveAs(Form("%s/PubBiPo%iEsmearresvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));
    
    TCanvas *c3 = new TCanvas("c3","c3",0,0,1200,300);
    TGraphErrors *grdZWpub = new TGraphErrors();
    grdZWpub->SetName(Form("grSigmadZvsTPo%i", (alpha_type == 1 ? 212 : 214)));
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
    grdZWpub->GetXaxis()->SetTimeDisplay(1);
    grdZWpub->GetXaxis()->SetTimeFormat("%b %d");
    grdZWpub->GetXaxis()->SetTitle("Date in 2018");
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
    grZWpub->GetXaxis()->SetTimeDisplay(1);
    grZWpub->GetXaxis()->SetTimeFormat("%b %d");
    grZWpub->GetXaxis()->SetTitle("Date in 2018");
    gPad->Update();
    grZWpub->Write();
    c4->SaveAs(Form("%s/PubBiPo%iZrmsvsT%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));
    f.Close();
  }
  TCanvas *cZcum = new TCanvas("cZcum","cZcum",0,0,800,600);
  //  hZcum[0]->Scale(1/hZcum[0]->GetBinWidth(1));
  //  hZcum[1]->Scale(n2f/hZcum[1]->GetBinWidth(1));
  hZcum[2] = (TH1D*)hZcum[0]->Clone("hZcumsub");
  hZcum[2]->Add(hZcum[1],-1);
  hZcum[1]->SetLineColor(kMagenta);
  hZcum[2]->SetLineColor(kRed);
  hZcum[0]->Draw();
  gPad->Update();
  hZcum[0]->GetYaxis()->SetLimits(-0.1*hZcum[0]->GetMaximum(),hZcum[0]->GetMaximum()*1.1);
  hZcum[0]->GetYaxis()->SetRangeUser(-0.1*hZcum[0]->GetMaximum(),hZcum[0]->GetMaximum()*1.1);
  hZcum[1]->Draw("same");
  hZcum[2]->Draw("sames");
  gStyle->SetOptStat("rmen");
  gStyle->SetOptFit(1111);
  TCanvas *cdtcum = new TCanvas("cdtcum","cdtcum",0,0,1400,600);
  cdtcum->Divide(2,1);
  pStyle->SetOptStat("");
  pStyle->SetOptFit(1111);
  cdtcum->cd(1);
  gPad->SetLeftMargin(0.14);
  gPad->SetRightMargin(0.1);
  hdtbkgcum->Scale(1/hdtbkgcum->GetBinWidth(1)/live/3.6);
  hdtcum[0]->Scale(1/hdtcum[0]->GetBinWidth(1)/live/3.6);
  hdtcum[1]->Scale(1/hdtcum[1]->GetBinWidth(1)/live/3.6);
  hdtcum[2] = (TH1D*)hdtcum[0]->Clone("hdtcumsub");
  hdtcum[2]->Add(hdtcum[1],-1);
  hdtcum[0]->SetTitle(Form("Po-%i dt Distribution", alpha_type==1?212:214));
  hdtcum[0]->GetXaxis()->SetTitle("dt (ms)");
  hdtcum[0]->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  hdtcum[0]->GetXaxis()->SetMaxDigits(3);
  hdtcum[0]->GetYaxis()->SetMaxDigits(3);
  hdtcum[0]->SetLineColor(kBlue);
  hdtcum[0]->SetLineWidth(2);
  hdtcum[1]->SetLineColor(kMagenta);
  hdtcum[2]->SetLineColor(kRed);
  hdtcum[2]->SetMarkerColor(kRed);
  hdtcum[0]->Draw();
  gPad->Update();
  TPaveStats* ps = (TPaveStats*)hdtcum[0]->FindObject("stats");
  ps->SetX1NDC(0.6);
  TPaveText *ptt = new TPaveText(0.65,0.45,0.89,0.65,"NDC");
  ptt->SetShadowColor(0);
  ptt->SetBorderSize(0);
  ptt->SetFillColor(0);
  ptt->SetTextColor(kBlue);
  ptt->AddText("Coincidence");  
  tt = ptt->AddText("Accidental");
  tt->SetTextColor(kMagenta);
  tt = ptt->AddText("Bkg-Subtracted");
  tt->SetTextColor(kRed);
  gPad->Update();
  hdtcum[0]->GetYaxis()->SetLimits(-0.1*hdtcum[0]->GetMaximum(),hdtcum[0]->GetMaximum()*1.1);
  hdtcum[0]->GetYaxis()->SetRangeUser(-0.1*hdtcum[0]->GetMaximum(),hdtcum[0]->GetMaximum()*1.1);
  fdecay->SetLineColor(kBlue);
  fpol0->SetLineWidth(0);
  hdtcum[1]->Fit(fpol0);
  if(alpha_type == 1){
    fdecay->ReleaseParameter(2);
    fdecay->ReleaseParameter(3);
    fdecay->SetParameters(0, 1, 0, fpol0->GetParameter(0));
    fdecay->FixParameter(0,0);
    fdecay->FixParameter(1,1);
    fdecay->FixParameter(3, fpol0->GetParameter(0));
    hdtbkgcum->Fit(fdecay, "B");
    fdecay->ReleaseParameter(0);
    fdecay->ReleaseParameter(1);
    fdecay->SetParameter(0, hdtcum[2]->GetMaximum()*5);
    fdecay->SetParameter(1, 0.00043);
    fdecay->FixParameter(2, fdecay->GetParameter(2));
    fdecay->FixParameter(3, fdecay->GetParameter(3));
    //    cout<<"Setting par 0 to "<<hdtcum[2]->GetMaximum()*5<<endl;
  }
  if(alpha_type == 0){
    fdecay->SetParameters(hdtcum[2]->GetMaximum(), tauBiPo);
    fdecay->FixParameter(2, fpol0->GetParameter(0));
  }
  hdtcum[0]->Fit(fdecay,"B");
  hdtcum[1]->SetLineWidth(2);
  hdtcum[1]->Draw("same");
  hdtcum[2]->Draw("same");
  ptt->Draw();
  ps->Draw();
  gPad->Update();
  cdtcum->cd(2);
  gPad->SetLeftMargin(0.1);
  gPad->SetRightMargin(0.08);
  hdtbkgcum->SetTitle(Form("Accidental Background + Po-214 Events Passing Cuts"));
  hdtbkgcum->GetXaxis()->SetTitle("dt (ms)");
  hdtbkgcum->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  hdtbkgcum->SetLineColor(kGreen+2);
  hdtbkgcum->SetLineWidth(2);
  hdtbkgcum->Draw();
  if(alpha_type==1)
    cdtcum->SaveAs(Form("%s/Po212dtPlusBkg.pdf", gSystem->Getenv("TECHNOTE")));
  fpol0->SetLineWidth(1);
  double A212 = fdecay->GetParameter(0);
  double A212err = fdecay->GetParError(0);
  double th212 = fdecay->GetParameter(1)*log(2);
  double th212err = fdecay->GetParError(1)*log(2);
  double A214 = fdecay->GetParameter(2);
  double A214err = fdecay->GetParError(2);
  double probdt = fdecay->GetProb();
  
  
  delete bp;
  printf("t_start   t_end    f2n      lAE    ft_start     Rate_212       Prob       Rate_214    Prob       T_half(pol0)       Prob            A_212               T_half(exp)                 A214             Prob\n");
  printf("%7.1e   %7.1e %5.1f   %6.2f  %9.2e  %0.4f+/-%0.4f   %0.3f", t_start, t_end, f2n, lAE, ft_start, rate212, rate212err, rate212prob);
  printf("   %0.3f+/-%0.3f  %0.3f  %0.3e+/-%0.3e  %0.3f", rate214, rate214err, rate214prob, pol0th212, pol0th212err, pol0th212prob);
  printf("   %0.3e+/-%0.3e    %0.3e+/-%0.3e   %0.3e+/-%0.3e   %0.3f \n", A212, A212err, th212, th212err, A214, A214err, probdt);

  //On/Off comparison
  TCanvas *conoff = new TCanvas("conoff","conoff",0,0,1900,900);
  gStyle->SetOptStat(0);
  conoff->Divide(3,2);
  conoff->cd(1)->SetGrid();
  hOnAPSD[0]->Scale(1/t_on);
  hOnAPSD[1]->Scale(1/t_on);
  hOnAPSD[0]->Add(hOnAPSD[1],-1);
  hOnAPSD[0]->SetTitle("Alpha PSD");
  hOnAPSD[0]->SetLineColor(kRed);
  hOnAPSD[0]->SetLineWidth(2);
  hOnAPSD[0]->Draw();
  gPad->Update();
  hOnAPSD[0]->GetYaxis()->SetRangeUser(-0.2*hOnAPSD[0]->GetMaximum(),hOnAPSD[0]->GetMaximum()*1.1);
  hOffAPSD[0]->Scale(1/t_off);
  hOffAPSD[1]->Scale(1/t_off);
  hOffAPSD[0]->Add(hOffAPSD[1],-1);
  hOffAPSD[0]->SetLineWidth(2);
  hOffAPSD[0]->SetLineColor(kBlue);
  hOffAPSD[0]->Draw("sames");
  hOffAPSD[1]->Add(hOffAPSD[0],hOnAPSD[0],-1,1);
  hOffAPSD[1]->SetLineWidth(2);
  hOffAPSD[1]->SetLineColor(kGreen+2);
  hOffAPSD[1]->Draw("same");
  
  conoff->cd(2)->SetGrid();
  hOnBPSD[0]->Scale(1/t_on);
  hOnBPSD[1]->Scale(1/t_on);
  hOnBPSD[0]->Add(hOnBPSD[1],-1);
  hOnBPSD[0]->SetTitle("Beta PSD");
  hOnBPSD[0]->SetLineColor(kRed);
  hOnBPSD[0]->SetLineWidth(2);
  hOnBPSD[0]->Draw();
  gPad->Update();
  hOnBPSD[0]->GetYaxis()->SetRangeUser(-0.2*hOnBPSD[0]->GetMaximum(),hOnBPSD[0]->GetMaximum()*1.1);
  hOffBPSD[0]->Scale(1/t_off);
  hOffBPSD[1]->Scale(1/t_off);
  hOffBPSD[0]->Add(hOffBPSD[1],-1);
  hOffBPSD[0]->SetLineWidth(2);
  hOffBPSD[0]->SetLineColor(kBlue);
  hOffBPSD[0]->Draw("sames");
  hOffBPSD[1]->Add(hOffBPSD[0],hOnBPSD[0],-1,1);
  hOffBPSD[1]->SetLineWidth(2);
  hOffBPSD[1]->SetLineColor(kGreen+2);
  hOffBPSD[1]->Draw("same");
  
  conoff->cd(3)->SetGrid();
  hOnE[0]->Scale(1/t_on);
  hOnE[1]->Scale(1/t_on);
  hOnE[0]->Add(hOnE[1],-1);
  hOnE[0]->SetTitle("Alpha E");
  hOnE[0]->SetLineWidth(2);
  hOnE[0]->SetLineColor(kRed);
  hOnE[0]->Draw();
  gPad->Update();
  hOnE[0]->GetYaxis()->SetRangeUser(-0.2*hOnE[0]->GetMaximum(),hOnE[0]->GetMaximum()*1.1);
  hOffE[0]->Scale(1/t_off);
  hOffE[1]->Scale(1/t_off);
  hOffE[0]->Add(hOffE[1],-1);
  hOffE[0]->SetLineWidth(2);
  hOffE[0]->SetLineColor(kBlue);
  hOffE[0]->Draw("sames");
  hOffE[1]->Add(hOffE[0],hOnE[0],-1,1);
  hOffE[1]->SetLineWidth(2);
  hOffE[1]->SetLineColor(kGreen+2);
  hOffE[1]->Draw("same");
  
  conoff->cd(4)->SetGrid();
  hOnZ[0]->Scale(1/t_on);
  hOnZ[1]->Scale(1/t_on);
  hOnZ[0]->Add(hOnZ[1],-1);
  hOnZ[0]->SetTitle("Alpha Z");
  hOnZ[0]->SetLineWidth(2);
  hOnZ[0]->SetLineColor(kRed);
  hOnZ[0]->Draw();
  gPad->Update();
  hOnZ[0]->GetYaxis()->SetRangeUser(-0.3*hOnZ[0]->GetMaximum(),hOnZ[0]->GetMaximum()*1.1);
  hOffZ[0]->Scale(1/t_off);
  hOffZ[1]->Scale(1/t_off);
  hOffZ[0]->Add(hOffZ[1],-1);
  hOffZ[0]->SetLineWidth(2);
  hOffZ[0]->SetLineColor(kBlue);
  hOffZ[0]->Draw("sames");
  hOffZ[1]->Add(hOffZ[0],hOnZ[0],-1,1);
  hOffZ[1]->SetLineWidth(2);
  hOffZ[1]->SetLineColor(kGreen+2);
  hOffZ[1]->Draw("same");
  
  conoff->cd(5)->SetGrid();
  hOndZ[0]->Scale(1/t_on);
  hOndZ[1]->Scale(1/t_on);
  hOndZ[0]->Add(hOndZ[1],-1);
  hOndZ[0]->SetTitle("Alpha-Beta dZ");
  hOndZ[0]->SetLineWidth(2);
  hOndZ[0]->SetLineColor(kRed);
  hOndZ[0]->Draw();
  gPad->Update();
  hOndZ[0]->GetYaxis()->SetRangeUser(-0.2*hOndZ[0]->GetMaximum(),hOndZ[0]->GetMaximum()*1.1);
  hOffdZ[0]->Scale(1/t_off);
  hOffdZ[1]->Scale(1/t_off);
  hOffdZ[0]->Add(hOffdZ[1],-1);
  hOffdZ[0]->SetLineWidth(2);
  hOffdZ[0]->SetLineColor(kBlue);
  hOffdZ[0]->Draw("sames");
  hOffdZ[1]->Add(hOffdZ[0],hOndZ[0],-1,1);
  hOffdZ[1]->SetLineWidth(2);
  hOffdZ[1]->SetLineColor(kGreen+2);
  hOffdZ[1]->Draw("same");
  
  conoff->cd(6)->SetGrid();
  hOndt[0]->Scale(1/t_on);
  hOndt[1]->Scale(1/t_on);
  hOndt[0]->Add(hOndt[1],-1);
  hOndt[0]->SetTitle("Alpha-Beta dt");
  hOndt[0]->SetLineWidth(2);
  hOndt[0]->SetLineColor(kRed);
  hOndt[0]->Draw();
  gPad->Update();
  hOndt[0]->GetYaxis()->SetRangeUser(-0.1*hOndt[0]->GetMaximum(),hOndt[0]->GetMaximum()*1.1);
  hOffdt[0]->Scale(1/t_off);
  hOffdt[1]->Scale(1/t_off);
  hOffdt[0]->Add(hOffdt[1],-1);
  hOffdt[0]->SetLineWidth(2);
  hOffdt[0]->SetLineColor(kBlue);
  hOffdt[0]->Draw("sames");
  hOffdt[1]->Add(hOffdt[0],hOndt[0],-1,1);
  hOffdt[1]->SetLineWidth(2);
  hOffdt[1]->SetLineColor(kGreen+2);
  hOffdt[1]->Draw("same");
  printf("hdtcum %i  %i\n", (int)hdtcum[0]->GetEntries(),(int) hdtcum[1]->GetEntries());
  cout<<"Prompt beta candidates: "<<nnear<<endl;
  cout<<"Far beta candidates: "<<nfar<<endl;

  cout<<"Time on: "<<t_on/3600.<<". Time off: "<<t_off/3600.0<<endl;
  cout<<"Combined: "<<(t_on+t_off)/3600.<<" "<<tot_live<<endl;
  return hZcum[2];
}
