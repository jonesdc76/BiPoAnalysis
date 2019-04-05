#include <vector>
#include <map>
#include "BP.C"
#include "PROSPECT_Style.cc"
#include <iostream>
#include "TH1D.h"
#include "TSystem.h"
#include "TVectorD.h"
#include "TChain.h"
#include "TMatrixDSym.h"
#include "TFitResult.h"
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
const int N = 3, ncol = 14, nrow = 11, nBINS = 40;
const double kCellSize = 146.0;//cell cross sectional size in mm
const double kMaxDisplacement = 550.0;//maximum displacement between alpha and beta (max pulse in prompt cluster)
const double tauBiPo = 0.1643/log(2); 
const double F2N = 100.0;//ratio of lengths of far to near windows
const double tmin = 0.01;//start coincidence window tmin ms away from electron
const int kNcell = ncol * nrow;
const int ExcludeCellArr[63] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 17, 18, 21, 23, 24, 27, 28, 29, 31, 32, 34, 36, 40, 41, 42, 43, 44, 46, 47, 48, 50, 52, 55, 56, 60, 63, 68, 69, 70, 73, 79, 83, 86, 87, 94, 97, 102, 107, 115, 121, 122, 126, 127, 128, 130, 133, 136, 139, 141};

bool isET(int seg){
  return (seg%14 == 13 || seg%14 == 0 || seg >= 140);
}

double GetRunTime(TChain *ch){
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  double tlive = 0;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    tlive += ((TVectorD*)file->Get("runtime"))->Norm1();
  }
  return tlive/3600.0;
}

double GetDeadTime(TChain *ch){
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  double tdead = 0;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    tdead += ((TVectorD*)file->Get("BiPoTreePlugin/pileup_veto_dt"))->Norm1();
  }
  return tdead/3600.0;
}

int BiPoPlotter(bool fiducialize = 0, int alpha_type = 0, bool P2_style = 1, bool recreate = 0){
  //alpha_type = 0, strictly Bi214-->Po214-->Pb210
  //alpha_type = 1, strictly Bi212-->Po212-->Pb208
  //alpha_type = 2, include both
  int nBINST = alpha_type == 1 ? 15 : 40;
  bool technote_plots = 1;
  int nnear = 0, nfar = 0, nalpha = 0;
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1111);
  gStyle->SetTitleW(0.8);
  gStyle->SetTitleX(0.5);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadLeftMargin(0.14);
  if(P2_style) setup_PROSPECT_style();
  bool exclude_cells = 1;
  TString fid = TString((fiducialize ? "fid":""));
  int which_plots = 0;
  map<const char*, int>plots;
  //set values to 1 if want plotted
  plots.insert(pair<const char*, int>("psd",1));
  plots.insert(pair<const char*, int>("z",1));
  plots.insert(pair<const char*, int>("dt",1));
  plots.insert(pair<const char*, int>("E",1));
  plots.insert(pair<const char*, int>("by_cell",1));
  
  int n = 0;
  vector<TString>name;
  for(auto a: plots){
    name.push_back(a.first);
    if(a.second == 1){
      plots[a.first] = 1<<n;
      which_plots += 1<<n;
    }else{
      plots[a.first] = 0;
     }
    //cout<<a.first<<" "<<plots[a.first]<<endl;
    ++n;
  }
  cout<<which_plots<<endl;
  //Get the TChain
  //----------------
  BP *bp = new BP(); 
  double runt = GetRunTime(bp->chain);
  double deadt = 2*GetDeadTime(bp->chain);
  double live = runt - deadt;
  cout<<"Run time: "<<runt<<" hours\n";
  cout<<"Dead time: "<<deadt<<" hours\n";
  cout<<"Live time: "<<live<<" hours\n";
  
  //Set boundary cut values on energy, psd, z-pos and time
  //-------------------------------------------------------
  double f2n = F2N > 12.0 ? 12.0 : F2N, n2f = 1.0/f2n;
  double hAE = 1.0, lAE = 0.72, hApsd = 0.34, lApsd = 0.18;//alpha
  double highBE = 4.0, lowBE = 0, hPpsd = 0.2, lPpsd = 0.06;//beta
  double t_start = 0.01, t_end = 3 * tauBiPo;//prompt window
  double ft_offset = 10 * tauBiPo;//far window time offset
  double ft_start = ft_offset;//start time of far window 
  double ft_end = ft_start + f2n * (t_end - t_start);//far window
  double  ldZ = -200, hdZ = 200, fidZ = fiducialize ? 1000.0 : 1000.0;//444.0;
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
  
  //Cut efficiencies
  //------------------
  double effAE[kNcell], effAPSD[kNcell], effBPSD[kNcell], effdZ[kNcell], effTot[kNcell];
  for(int i=0;i<kNcell;++i){effAE[i] = 0; effAPSD[i] = 0; effBPSD[i] = 0; effdZ[i] = 0; effTot[i] = 0;}
  
  //Miscellany useful for making plots
  //-------------------------------------------
  TString title[N] = {"(^{214}Bi-->^{214}Po-->^{210}Pb) ","(^{212}Bi-->^{212}Po-->^{208}Pb) ","(Bi-->Po-->Pb) "};
  int col[N] = {kBlue, kMagenta, kRed};
 
  //Define plots to make
  //A=delayed alpha, B=prompt beta/gamma
  //-------------------------------------------
  
  //1. PSD plots 
  TH2D *hBPSDvE[N], *hAPSDvE[N], *hBPSDvZ[N], *hAPSDvZ[N];
  TCanvas *cPSD, *cPSDBkSub;
  cout<<plots["psd"]<<endl;
  if(bool(plots["psd"] & which_plots)){
    cout<<"Including psd plots"<<endl;
    for(int i=0;i<N;++i){
      hAPSDvE[i] = new TH2D(Form("hAPSDvE%i",i),Form("%s #alpha PSD vs. Energy",title[alpha_type].Data()),200,lAE,hAE,200,lApsd,hApsd);
      hAPSDvE[i]->Sumw2();
      hBPSDvE[i] = new TH2D(Form("hBPSDvE%i",i),Form("%s #beta PSD vs. Total Energy", title[alpha_type].Data()),200,0,highBE,200,lPpsd,hPpsd);
      hBPSDvE[i]->Sumw2();
      hAPSDvZ[i] = new TH2D(Form("hAPSDvZ%i",i),Form("%s #alpha PSD vs. Z-position",title[alpha_type].Data()),200,-1000,1000,200,lApsd,hApsd);
      hAPSDvZ[i]->Sumw2();
      hBPSDvZ[i] = new TH2D(Form("hBPSDvZ%i",i),Form("%s #beta PSD vs. Z-position", title[alpha_type].Data()),200,-1000,1000,200,lPpsd,hPpsd);
      hBPSDvZ[i]->Sumw2();
    }
  }

  //2. Z-position distribution plots
  TH1D *hAZ[N], *hAdZ[N];
  TCanvas *cZ;
  TF1 *fdz = new TF1("fdz","[0]*exp(-0.5*pow(x/[1],2))", -100, 100);
  fdz->SetParName(0,"A{1}");
  fdz->SetParName(1,"#sigma_{1} (mm)");
  fdz->SetParName(2,"A{2}");
  fdz->SetParName(3,"#sigma_{2} (mm)");
  if(bool(plots["z"] & which_plots)){
    cout<<"Including z plots"<<endl;
    for(int i=0;i<N;++i){
      hAZ[i] = new TH1D(Form("hAZ%i",i),Form("%s #alpha Z-Distribution", title[alpha_type].Data()),100,-1000,1000);
      hAZ[i]->Sumw2();
      hAZ[i]->SetMarkerColor(col[i]);
      hAZ[i]->SetLineColor(col[i]);
      hAdZ[i] = new TH1D(Form("hAdZ%i",i),Form("%s #DeltaZ-Distribution", title[alpha_type].Data()),nBINS,-210,210);
      hAdZ[i]->Sumw2();
      hAdZ[i]->SetMarkerColor(col[i]);
      hAdZ[i]->SetLineColor(col[i]);
    }
  }
  
  //3. Time distribution plot
  TH1D *hABdt[N];

  TCanvas *cdT;
  TF1 *fdecay = new TF1("fdecay","[0]*exp(-x/[1])+[2]",t_start, t_end);
  double tau = 0.237;
  if(alpha_type==1)
    fdecay = new TF1("fdecay",Form("[0]*exp(-x/[1])+[2]*exp(-x/%f)+[3]",tau),t_start, t_end);
  fdecay->SetParName(0, "A_{1}");
  fdecay->SetParName(1, "#tau");
  fdecay->SetParName(2, "A_{2}");
  int nb = 100;
  if(bool(plots["dt"] & which_plots)){
    cout<<"Including dt plots"<<endl;
    for(int i=0;i<N;++i){
      hABdt[i] = new TH1D(Form("hABdt%i",i),Form("%s #alpha-#beta #DeltaT-Distribution", title[alpha_type].Data()), nb, t_start, t_end);
      hABdt[i]->Sumw2();
      hABdt[i]->SetMarkerColor(col[i]);
      hABdt[i]->SetLineColor(col[i]);
    }
  }
  double w = (t_end-t_start)/double(nb);
  int rebin_scale = 50;
  if(alpha_type == 1) w *= rebin_scale;
  nb = int( (3*tauBiPo - 0.005) / w);
  double l_t1 = 0.005, h_t1 = 0.005+nb*w;
  TH1D *hABdt214 = new TH1D("hABdt214","hABdt214", nb, l_t1, h_t1);
  //  cout<<hABdt[0]->GetBinWidth(1)<<" "<<hABdt214->GetBinWidth(1)<<endl;

  
  //4. Alpha and beta energy distribution plots
  TH1D *h_AE[N], *hBE[N], *h_AEsmear[N];
  TCanvas *cE, *cEsmear;
  if(bool(plots["E"] & which_plots)){
    cout<<"Including E plots"<<endl;
    for(int i=0;i<N;++i){
      h_AE[i] = new TH1D(Form("hAE%i",i),Form("%s#alpha Energy Distribution", title[alpha_type].Data()),nBINS,lAE,hAE);
      h_AE[i]->Sumw2();
      h_AE[i]->SetMarkerColor(col[i]);
      h_AE[i]->SetLineColor(col[i]);
      h_AEsmear[i] = new TH1D(Form("hAEsmear%i",i),Form("%sSmeared #alpha Energy Distribution", title[alpha_type].Data()),nBINS,lAE,hAE);
      h_AEsmear[i]->Sumw2();
      h_AEsmear[i]->SetMarkerColor(col[i]);
      h_AEsmear[i]->SetLineColor(col[i]);
     
      hBE[i] = new TH1D(Form("hBE%i",i),Form("%s #beta Energy Distribution", title[alpha_type].Data()),nBINS,0,(alpha_type == 1 ? 3.5 : highBE));
      hBE[i]->Sumw2();
      hBE[i]->SetMarkerColor(col[i]);
      hBE[i]->SetLineColor(col[i]);
    }
  }


  //5. By cell plots
  TH1D *hCellAE[kNcell][N], *hCellAEsmear[kNcell][N], *hCelldt[kNcell][N], *hCellBkgdt[kNcell], *hCellAPSD[kNcell][N], *hCellBPSD[kNcell][N], *hCelldZ[kNcell][N], *hCellZ[kNcell][N];
  TCanvas *cCellAE, *cCellAdE, *cCellAEsmear, *cCellAdEsmear, *cCellApsd, *cCellBpsd,  *cCelldZ,  *cCellZ, *cCellRate;
  w =  (t_end - t_start)/double(nBINST);
  if(alpha_type == 1) w *= rebin_scale;
  nb = int( (3*tauBiPo - 0.005) / w);
  double l_t2 = 0.005, h_t2 = 0.005+nb*w;
  if(bool(plots["by_cell"] & which_plots)){
    cout<<"Including by_cell plots"<<endl;
    for(int j=0;j<kNcell;++j){
      hCellBkgdt[j] = new TH1D(Form("hCellBkgdt[%i]",j), Form("hCellBkgdt[%i]",j), nb, l_t2, h_t2);
      for(int i=0;i<N;++i){
	hCellAE[j][i] = new TH1D(Form("hCellAE[%i][%i]",j,i), Form("hCellAE[%i][%i]",j,i),nBINS, lAE, hAE);
	hCellAE[j][i]->Sumw2();
	hCellAE[j][i]->SetMarkerColor(col[i]);
	hCellAE[j][i]->SetLineColor(col[i]);
	
	hCellAEsmear[j][i] = new TH1D(Form("hCellAEsmear[%i][%i]",j,i), Form("hCellAEsmear[%i][%i]",j,i),nBINS, lAE, hAE);
	hCellAEsmear[j][i]->Sumw2();
	hCellAEsmear[j][i]->SetMarkerColor(col[i]);
	hCellAEsmear[j][i]->SetLineColor(col[i]);
	
	hCelldt[j][i] = new TH1D(Form("hCelldt[%i][%i]",j,i), Form("hCelldt[%i][%i]",j,i),nBINST, t_start, t_end);
	hCelldt[j][i]->Sumw2();
	hCelldt[j][i]->SetMarkerColor(col[i]);
	hCelldt[j][i]->SetLineColor(col[i]);

	hCellAPSD[j][i] = new TH1D(Form("hCellAPSD[%i][%i]",j,i), Form("hCellAPSD[%i][%i]",j,i),nBINS, lApsd, hApsd);
	hCellAPSD[j][i]->Sumw2();
	hCellAPSD[j][i]->SetMarkerColor(col[i]);
	hCellAPSD[j][i]->SetLineColor(col[i]);

	hCellBPSD[j][i] = new TH1D(Form("hCellBPSD[%i][%i]",j,i), Form("hCellBPSD[%i][%i]",j,i),nBINS, lPpsd, hPpsd);
	hCellBPSD[j][i]->Sumw2();
	hCellBPSD[j][i]->SetMarkerColor(col[i]);
	hCellBPSD[j][i]->SetLineColor(col[i]);

	hCelldZ[j][i] = new TH1D(Form("hCelldZ[%i][%i]",j,i), Form("hCelldZ[%i][%i]",j,i),nBINS,-200, 200);
	hCelldZ[j][i]->Sumw2();
	hCelldZ[j][i]->SetMarkerColor(col[i]);
	hCelldZ[j][i]->SetLineColor(col[i]);

	hCellZ[j][i] = new TH1D(Form("hCellZ[%i][%i]",j,i), Form("hCellZ[%i][%i]",j,i),100,-1000, 1000);
	hCellZ[j][i]->Sumw2();
	hCellZ[j][i]->SetMarkerColor(col[i]);
	hCellZ[j][i]->SetLineColor(col[i]);
      }
    }
  }



  //Loop over tree
  //-------------------------------------------
  int ncut[8] = {0,0,0,0,0,0,0,0};
  Long64_t nEnt = Long64_t(bp->fChain->GetEntries()/10);
  cout<<nEnt<<endl;
  for(Long64_t i=0;i<bp->fChain->GetEntries();++i){
    bp->LoadTree(i);
    bp->GetEntry(i);
    if(i%nEnt==0)cout<<"*"<<flush;
    //Excluded cells cut
    //--------------------------------------------
    if(exclude_cells)
      if( find(begin(ExcludeCellArr), end(ExcludeCellArr), bp->aseg)
	  != end(ExcludeCellArr) ){
	continue;
      }
    //--------------------------------------------

    //Apply alpha cuts
    //-------------------------------------------
    if(!(abs(bp->az)<1000))continue;//alpha position
    if(bp->aE<lAE || bp->aE > hAE)continue;//alpha energy
    if(bp->aPSD<lApsd || bp->aPSD > hApsd)continue;//alpha PSD
    if(fiducialize)
      if( isET(bp->aseg) || fabs(bp->az) > fidZ)//exclude volume at cell ends
    	continue;//alpha fiducial
    ++nalpha;
    //--------------------------------------------
    
    //Fill Prompt Window Plots
    //-------------------------------------------
    ncut[7] +=  bp->mult_prompt;
    double scale = 0;
    for(int j=0;j<bp->mult_prompt;++j){
      //++ncut[7];
      if( (bp->pmult_clust->at(j) != bp->pmult_clust_ioni->at(j)) ){++ncut[0];
      	continue;}//throw out clusters with recoils mixed in
      if(bp->pEtot->at(j) < lowBE || bp->pEtot->at(j) > highBE){++ncut[1];
	continue;}//optional beta energy cut used for special studies     
      if( bp->pPSD->at(j) < lPpsd || bp->pPSD->at(j) > hPpsd){++ncut[2];
	continue;}
      if(!(fabs(bp->pz->at(j)) < 1000)){++ncut[3]; continue;}
      
      double dx = kCellSize*((bp->aseg - bp->pseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->pseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->pz->at(j);
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement){++ncut[4];//discard largely displaced prompt and delayed
	continue;}
      double dt = bp->at - bp->pt->at(j);
      if(dt > l_t1 && dt < h_t1){
	hABdt214->Fill(dt);
      }
      if(dt > l_t2 && dt < h_t2){
	hCellBkgdt[bp->aseg]->Fill(dt);
      }
      if(dt > t_start && dt < t_end){
	++nnear;
	++scale;
	if(bool(plots["psd"] & which_plots)){
	  hBPSDvZ[0]->Fill(bp->pz->at(j), bp->pPSD->at(j));
	  hBPSDvE[0]->Fill(bp->pEtot->at(j), bp->pPSD->at(j));
	}
	if(bool(plots["z"] & which_plots)){
	  hAdZ[0]->Fill(bp->az-bp->pz->at(j));
	}
	if(bool(plots["dt"] & which_plots)){
	  hABdt[0]->Fill(dt);
	}
	if(bool(plots["E"] & which_plots)){
	  hBE[0]->Fill(bp->pEtot->at(j));
	}
	if(bool(plots["by_cell"] & which_plots)){
	  hCelldt[bp->aseg][0]->Fill(dt);
	  hCellBPSD[bp->pseg->at(j)][0]->Fill(bp->pPSD->at(j));
	  hCelldZ[bp->aseg][0]->Fill(bp->az-bp->pz->at(j));
	}
      }else if(dt < t_start){
	++ncut[5];
      }else ++ncut[6];
    }
    if(bool(plots["psd"] & which_plots)){
      hAPSDvZ[0]->Fill(bp->az, bp->aPSD, scale);
      hAPSDvE[0]->Fill(bp->aE, bp->aPSD, scale);
    }
    if(bool(plots["z"] & which_plots)){
      hAZ[0]->Fill(bp->az, scale);
    }
    if(bool(plots["E"] & which_plots)){
      h_AE[0]->Fill(bp->aE, scale);
      h_AEsmear[0]->Fill(bp->aEsmear, scale);
    }
    if(bool(plots["by_cell"] & which_plots)){
      hCellAE[bp->aseg][0]->Fill(bp->aE, scale);
      hCellAEsmear[bp->aseg][0]->Fill(bp->aEsmear, scale);
      hCellAPSD[bp->aseg][0]->Fill(bp->aPSD, scale);
      hCellZ[bp->aseg][0]->Fill(bp->az, scale);
    }

    //-------------------------------------------

    
    //Fill Far Window Plots
    //-------------------------------------------
    scale = 0;
    for(int j=0;j<bp->mult_far;++j){
      if( (bp->fmult_clust->at(j) != bp->fmult_clust_ioni->at(j)) )
      	continue;//throw out clusters with recoils mixed in
      if(bp->fEtot->at(j) < lowBE || bp->fEtot->at(j) > highBE)
	continue;//optional beta energy cut used for special studies
      if( bp->fPSD->at(j) < lPpsd || bp->fPSD->at(j) > hPpsd ) continue;
      if( !(fabs(bp->fz->at(j)) < 1000) ) continue;
      
      double dx = kCellSize*((bp->aseg - bp->fseg->at(j))%ncol);
      double dy = int((bp->aseg - bp->fseg->at(j))/ncol)*kCellSize;
      double dz = bp->az - bp->fz->at(j);
      double d = sqrt(dx*dx+dy*dy+dz*dz);
      if(d > kMaxDisplacement)//discard largely displaced prompt and delayed
	continue;

      double dt = bp->ft->at(j) - bp->at;
      if(dt > ft_start && dt < ft_end){
	++nfar;
	++scale;
	dt = (dt - ft_start)*n2f + t_start;
	if(bool(plots["psd"] & which_plots)){
	  hBPSDvZ[1]->Fill(bp->fz->at(j), bp->fPSD->at(j), n2f);
	  hBPSDvE[1]->Fill(bp->fEtot->at(j), bp->fPSD->at(j), n2f);
	}
	if(bool(plots["z"] & which_plots)){
	  hAdZ[1]->Fill(bp->az-bp->fz->at(j), n2f);
	}
	if(bool(plots["dt"] & which_plots)){
	  hABdt[1]->Fill(dt, n2f);
	}
	if(bool(plots["E"] & which_plots)){
	  hBE[1]->Fill(bp->fEtot->at(j), n2f);
	}
	if(bool(plots["by_cell"] & which_plots)){
	  hCelldt[bp->aseg][1]->Fill(dt, n2f);
	  hCellBPSD[bp->fseg->at(j)][1]->Fill(bp->fPSD->at(j), n2f);
	  hCelldZ[bp->aseg][1]->Fill(bp->az-bp->fz->at(j), n2f);
	}
      }
    }
    if(bool(plots["psd"] & which_plots)){
      hAPSDvZ[1]->Fill(bp->az, bp->aPSD, n2f*scale);
      hAPSDvE[1]->Fill(bp->aE, bp->aPSD, n2f*scale);
    }
    if(bool(plots["z"] & which_plots)){
      hAZ[1]->Fill(bp->az, n2f*scale);
    }
    if(bool(plots["E"] & which_plots)){
      h_AE[1]->Fill(bp->aE, n2f*scale);
      h_AEsmear[1]->Fill(bp->aEsmear, n2f*scale);
    }
    if(bool(plots["by_cell"] & which_plots)){
      hCellAE[bp->aseg][1]->Fill(bp->aE, n2f*scale);
      hCellAEsmear[bp->aseg][1]->Fill(bp->aEsmear, n2f*scale);
      hCellAPSD[bp->aseg][1]->Fill(bp->aPSD, n2f*scale);
      hCellZ[bp->aseg][1]->Fill(bp->az, n2f*scale);
    }

    //-------------------------------------------
  }
  cout<<""<<endl;
  
  //1. PSD plots 
 //---------------------------------------------
  if(bool(plots["psd"] & which_plots)){
    cPSD = new TCanvas("cPSD", "cPSD",0,0,1200,900);
    cPSD->Divide(2,2);
    cPSD->cd(1);
    hAPSDvE[2] = (TH2D*)hAPSDvE[0]->Clone("hAPSDvE2");
    hAPSDvE[2]->Add(hAPSDvE[1],-1);
    hAPSDvE[2]->Draw("colz");
    gPad->Update();
    hAPSDvE[0]->GetXaxis()->SetTitle(Form("#alpha Energy (MeV)"));
    hAPSDvE[0]->GetYaxis()->SetTitle("#alpha PSD");

    cPSD->cd(2);
    hBPSDvE[2] = (TH2D*)hBPSDvE[0]->Clone("hBPSDvE2");
    hBPSDvE[2]->Add(hBPSDvE[1],-1);
    hBPSDvE[2]->Draw("colz");
    gPad->Update();
    hBPSDvE[2]->GetXaxis()->SetTitle("Total #beta Energy (MeV)");
    hBPSDvE[2]->GetYaxis()->SetTitle("#beta PSD");

    cPSD->cd(3);
    hAPSDvZ[2] = (TH2D*)hAPSDvZ[0]->Clone("hAPSDvZ2");
    hAPSDvZ[2]->Add(hAPSDvZ[1],-1);
    hAPSDvZ[2]->Draw("colz");
    gPad->Update();
    hAPSDvZ[2]->GetXaxis()->SetTitle("#alpha Z-position (mm)");
    hAPSDvZ[2]->GetYaxis()->SetTitle("#alpha PSD");

    cPSD->cd(4);
    hBPSDvZ[2] = (TH2D*)hBPSDvZ[0]->Clone("hBPSDvZ2");
    hBPSDvZ[2]->Add(hBPSDvZ[1],-1);
    hBPSDvZ[2]->Draw("colz");
    gPad->Update();
    hBPSDvZ[2]->GetXaxis()->SetTitle("#betaZ-position (mm)");
    hBPSDvZ[2]->GetYaxis()->SetTitle("#beta PSD");
    cPSD->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iPSD%s.pdf", (alpha_type == 1 ? 212:214), fid.Data()));
    if(technote_plots){
      TCanvas *cAPSDtn = new TCanvas("cAPSDtn", "cAPSDtn",0,0,800,600);
      TPaletteAxis *pal = (TPaletteAxis*)hAPSDvE[2]->FindObject("palette");
      pal->SetX1NDC(0.9);
      pal->SetX2NDC(0.93);
      cAPSDtn->SetRightMargin(0.11);
      hAPSDvE[2]->Draw("colz");      
      cAPSDtn->SaveAs(Form("%s/BiPo%iAlphaPSDvsE%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214),fid.Data()));
      TCanvas *cBPSDtn = new TCanvas("cBPSDtn", "cBPSDtn",0,0,800,600);
      cBPSDtn->SetRightMargin(0.11);
      hBPSDvE[2]->Draw("colz");
      pal = (TPaletteAxis*)hBPSDvE[2]->FindObject("palette");
      pal->SetX1NDC(0.9);
      pal->SetX2NDC(0.93);
      gPad->Modified();
      gPad->Update();
      cBPSDtn->SaveAs(Form("%s/BiPo%iBetaPSDvsE%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214),fid.Data()));
    }
    
  }
 //---------------------------------------------



  //2. Z-position distribution plots
  //---------------------------------------------
  if(bool(plots["z"] & which_plots)){
    cZ = new TCanvas("cZ", "cZ",0,0,1200,600);
    cZ->Divide(2,1);
    cZ->cd(1);
    gStyle->SetOptStat(0);
    hAZ[0]->Scale(1/hAZ[0]->GetBinWidth(1));
    hAZ[1]->Scale(1/hAZ[1]->GetBinWidth(1));
    hAZ[2] = (TH1D*)hAZ[0]->Clone("hAZ[2]");
    hAZ[2]->Add(hAZ[1],-1);
    hAZ[0]->Draw();
    gPad->Update();
    hAZ[0]->GetXaxis()->SetTitle("#alpha Z-position (mm)");
    hAZ[0]->GetYaxis()->SetTitle("Counts per mm");
    hAZ[1]->Draw("sames");
    hAZ[2]->SetMarkerColor(col[2]);
    hAZ[2]->SetLineColor(col[2]);
    hAZ[2]->Draw("sames");
    gPad->Update();
    cZ->cd(2);
    hAdZ[2] = (TH1D*)hAdZ[0]->Clone("hAdZ[2]");
    hAdZ[2]->Add(hAdZ[1],-1);
    hAdZ[0]->Draw();
    gPad->Update();
    hAdZ[0]->GetXaxis()->SetTitle("#DeltaZ (mm)");
    hAdZ[0]->GetYaxis()->SetTitle("Counts");
    hAdZ[1]->Draw("sames");
    hAdZ[2]->SetMarkerColor(col[2]);;
    hAdZ[2]->SetLineColor(col[2]);;
    hAdZ[2]->Draw("sames");
    fdz->SetParameters(hAdZ[2]->GetMaximum(), 50);
    hAdZ[2]->Fit(fdz,"r");
    gPad->Update();
    cZ->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iZposition%s.pdf", (alpha_type == 1 ? 212:214),fid.Data()));
    if(technote_plots){    
       //plot 12 from technote
       TCanvas *c12 = new TCanvas("c12","c12",0,0,800,700);
       hAZ[2]->SetMarkerColor(kBlue);
       hAZ[2]->SetLineColor(kBlue);
       hAZ[2]->Draw();
       hAZ[2]->GetXaxis()->SetTitle("#alpha Z-position (mm)");
       hAZ[2]->GetYaxis()->SetTitle("Counts/mm");
       hAZ[2]->GetXaxis()->SetRangeUser(-900,900);
       hAZ[2]->GetYaxis()->SetTitleOffset(1);
       gPad->Update();
       c12->SaveAs(Form("%s/PubBiPo%iZdistribution%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214),fid.Data()));
       //plot 13 from technote
       TCanvas *c13 = new TCanvas("c13","c13",0,0,800,700);
       hAdZ[2]->SetMarkerColor(kBlue);
       hAdZ[2]->SetLineColor(kBlue);
       hAdZ[2]->Draw();
       hAdZ[2]->GetXaxis()->SetTitle("Z_{#alpha}-Z_{#beta} (mm)");
       hAdZ[2]->GetYaxis()->SetTitle("Counts/mm");
       hAdZ[2]->GetYaxis()->SetTitleOffset(1);
       gPad->Update();
       c13->SaveAs(Form("%s/PubBiPo%idZ%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214),fid.Data()));
    }
 
  }
  //---------------------------------------------


  //3. Time distribution plot
  //---------------------------------------------
  if(bool(plots["dt"] & which_plots)){
    gStyle->SetOptStat("rmen");
    gStyle->SetOptFit(1111);
    cdT = new TCanvas("cdT", "cdT",0,0,1400,600);
    cdT->Divide(2,1);
    cdT->cd(1);
    hABdt[2] = (TH1D*)hABdt[0]->Clone("hABdt");
    hABdt[2]->Add(hABdt[1],-1);
    hABdt[0]->Draw();
    gPad->Update();
    hABdt[0]->GetXaxis()->SetTitle("#Deltat (ms)");
    hABdt[0]->GetYaxis()->SetTitle("Counts");
    hABdt[1]->Draw("sames");
    hABdt[2]->SetMarkerColor(col[2]);;
    hABdt[2]->SetLineColor(col[2]);;
    hABdt[2]->Draw("sames");
    TF1 *fpol0 = new TF1("fpol0","pol0",0,1);
    hABdt[1]->Fit(fpol0);
    fdecay->SetParameters(hABdt[2]->GetMaximum(), tauBiPo, 0 );
    if(alpha_type == 1){
      hABdt214->Scale(1/double(rebin_scale));
      fdecay->ReleaseParameter(2);
      fdecay->ReleaseParameter(3);
      fdecay->SetParameter(2, 0);
      fdecay->FixParameter(3, fpol0->GetParameter(0));
      fdecay->FixParameter(0, 0);
      hABdt214->Fit(fdecay, "B");
      fdecay->ReleaseParameter(0);
      fdecay->SetParameters(hABdt[2]->GetMaximum()*5, 0.00043, fdecay->GetParameter(2), fdecay->GetParameter(3));
      fdecay->FixParameter(2, fdecay->GetParameter(2));
      fdecay->FixParameter(3, fdecay->GetParameter(3));
    }
    if(alpha_type == 0)
      fdecay->FixParameter(2, fpol0->GetParameter(0));
    hABdt[0]->Fit(fdecay, "RB");
    TF1* fdt2 = (TF1*)fdecay->Clone("fdt2");
    fdt2->SetRange(t_start, t_end);
    fdt2->SetLineStyle(4);
    fdt2->Draw("same");
    gPad->SetLeftMargin(0.1);
    gPad->SetRightMargin(0.12);
    gPad->Update();
    hABdt[2]->GetYaxis()->SetTitleOffset(0.8);
    TPaveText *pts = new TPaveText(0.4,0.7,0.65,0.92,"NDC");
    pts->SetShadowColor(0);
    //ptt->SetBorderSize(0);
    pts->SetFillColor(0);
    pts->AddText(Form("#chi^{2}/NDF:  %0.2f",fdecay->GetChisquare()/fdecay->GetNDF()));
    pts->AddText(Form("Probability:  %0.3f",fdecay->GetProb()));
    pts->AddText(Form("#tau:  %0.4f #pm %0.4f #mus",fdecay->GetParameter(1)*1000,fdecay->GetParError(1)*1000));
    pts->Draw();
    TPaveText *ptt = new TPaveText(0.7,0.78,0.899,0.92,"NDC");
    ptt->SetShadowColor(0);
    ptt->SetBorderSize(0);
    ptt->SetFillColor(0);
    ptt->SetTextColor(kBlue);
    ptt->AddText("Coincidence");  
    TText *tt = ptt->AddText("Accidental");
    tt->SetTextColor(kMagenta);
    tt = ptt->AddText("Acc-Subtracted");
    tt->SetTextColor(kRed);
    ptt->Draw();
    cdT->cd(2);
    hABdt214->Draw();
    cdT->SaveAs(Form("%s/BiPo%iDeltaTSpectrum%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212:214), fid.Data()));
    //gStyle->SetOptStat(0);
    //gStyle->SetOptFit(0);
  }
  //---------------------------------------------

  
  //4. Alpha Beta energy spectrum plots
  //---------------------------------------------
  if(bool(plots["E"] & which_plots)){
    gStyle->SetOptStat(0);
    gStyle->SetOptFit(1111);
    cE = new TCanvas("cE","cE",0,0,1400,600);
    cE->Divide(2,1);
    cE->cd(1);
    h_AE[0]->Scale(1/h_AE[0]->GetBinWidth(1));
    h_AE[1]->Scale(1/h_AE[1]->GetBinWidth(1));
    h_AE[0]->Draw();
    h_AE[1]->Draw("same");
    gPad->Update();
    h_AE[0]->GetYaxis()->SetTitle("Counts/MeV");
    h_AE[0]->GetYaxis()->SetRangeUser(0,h_AE[0]->GetMaximum()*1.1);
    h_AE[0]->GetXaxis()->SetTitle(Form("Energy (MeV)"));
    h_AE[2] = (TH1D*)h_AE[0]->Clone("h_AE[2]");
    h_AE[2]->Add(h_AE[1],-1);
    h_AE[2]->SetMarkerColor(col[2]);
    h_AE[2]->SetLineColor(col[2]);
    double guessE = alpha_type == 1 ? 1.06 : 0.84;
    double guessEerr = 0.05 * sqrt(guessE);
    TF1 fg1("fg1","gaus",guessE-2*guessEerr, guessE+2*guessEerr);
    fg1.SetParameters(h_AE[2]->GetMaximum(), guessE, guessEerr);
    fg1.SetLineWidth(2);
    TF1 fg2("fg2","gaus",0,3);
    fg2.SetLineStyle(7);
    fg2.SetLineWidth(1);
    h_AE[2]->Fit("fg1", "r");
    fg2.SetParameters(fg1.GetParameter(0),fg1.GetParameter(1),fg1.GetParameter(2));
    h_AE[2]->Draw("sames");
    gPad->Update();
    cE->cd(2);
    hBE[0]->Scale(1/hBE[0]->GetBinWidth(1));
    hBE[1]->Scale(1/hBE[1]->GetBinWidth(1));
    hBE[0]->Draw();
    hBE[1]->Draw("same");
    gPad->Update();
    hBE[0]->GetYaxis()->SetTitle("Counts/MeV");
    hBE[0]->GetXaxis()->SetTitle("Total Energy (MeV)");
    hBE[2] = (TH1D*)hBE[0]->Clone("hBE[2]");
    hBE[2]->Add(hBE[1],-1);
    hBE[2]->SetMarkerColor(col[2]);;
    hBE[2]->SetLineColor(col[2]);;
    hBE[2]->Draw("same");
    cE->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iEspectra%s.png", (alpha_type == 1 ? 212:214), fid.Data()));
    cEsmear = new TCanvas("cEsmear","cEsmear",0,0,800,600);
    h_AEsmear[0]->Scale(1/h_AEsmear[0]->GetBinWidth(1));
    h_AEsmear[1]->Scale(1/h_AEsmear[1]->GetBinWidth(1));
    h_AEsmear[0]->Draw();
    h_AEsmear[1]->Draw("same");
    gPad->Update();
    h_AEsmear[0]->GetYaxis()->SetTitle("Counts/MeV");
    h_AEsmear[0]->GetYaxis()->SetRangeUser(0,h_AEsmear[0]->GetMaximum()*1.1);
    h_AEsmear[0]->GetXaxis()->SetTitle(Form("Smeared Energy (MeV)"));
    h_AEsmear[2] = (TH1D*)h_AEsmear[0]->Clone("h_AEsmear[2]");
    h_AEsmear[2]->Add(h_AEsmear[1],-1);
    h_AEsmear[2]->SetMarkerColor(col[2]);
    h_AEsmear[2]->SetLineColor(col[2]);
    fg1.SetParameters(h_AEsmear[2]->GetMaximum(), guessE, guessEerr);
    h_AEsmear[2]->Fit("fg1", "r");
    fg2.SetParameters(fg1.GetParameter(0),fg1.GetParameter(1),fg1.GetParameter(2));
    h_AEsmear[2]->Draw("sames");
    gPad->Update();
    cEsmear->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iEsmearSpectrum%s.png", (alpha_type == 1 ? 212:214), fid.Data()));
    gStyle->SetOptFit(0);
    if(technote_plots){
      //plot 10 from technote
       TCanvas *c10 = new TCanvas("c10","c10",0,0,800,600);
       h_AE[2]->SetLineColor(kBlue);
       h_AE[2]->SetTitle(Form("Po-%i Alpha Energy Distribution", (alpha_type==1 ? 212 : 214)));
       h_AE[2]->Draw();
       fg1.Draw("same");
       fg2.Draw("same");
       gPad->Update();
       h_AE[2]->GetXaxis()->SetTitle(Form("E_{#alpha} (MeV)"));
       gPad->Update();
       c10->SaveAs(Form("%s/PubBiPo%iAlphaE%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214),fid.Data()));
       TCanvas *c10smear = new TCanvas("c10smear","c10smear",0,0,800,600);
       h_AEsmear[2]->SetLineColor(kBlue);
       h_AEsmear[2]->SetTitle(Form("Po-%i Smeared Alpha Energy Distribution", (alpha_type==1 ? 212 : 214)));
       h_AEsmear[2]->Draw();
       fg1.Draw("same");
       fg2.Draw("same");
       gPad->Update();
       h_AEsmear[2]->GetXaxis()->SetTitle(Form("Smeared E_{#alpha} (MeV)"));
       gPad->Update();
       c10smear->SaveAs(Form("%s/PubBiPo%iAlphaEsmear%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214),fid.Data()));
       
       //plot 11 from technote
       TCanvas *c11 = new TCanvas("c11","c11",0,0,800,600);
       hBE[2]->SetMarkerColor(kBlue);
       hBE[2]->SetLineColor(kBlue);
       hBE[2]->SetTitle(Form("Bi-%i Beta Energy Distribution", (alpha_type==1 ? 212 : 214)));
       hBE[2]->Draw();
       gPad->Update();
       hBE[2]->GetXaxis()->SetTitle("E_{#beta} (MeV)");
       gPad->Update();
       c11->SaveAs(Form("%s/PubBiPo%iBetaE%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214), fid.Data()));
   }
  }
  //---------------------------------------------

  
  //5. By Cell plots
  //---------------------------------------------
  TCanvas *cByCell;
  if(bool(plots["by_cell"] & which_plots)){
    cByCell = new TCanvas("cByCell","cByCell",0,0,1700,1000);
    cByCell->Divide(3,2);
    TPaveText *pt = new TPaveText(0.8,0.8,0.995,0.89,"NDC");
    pt->SetShadowColor(0);
    pt->SetFillColor(0);
    pt->SetTextColor(kBlue);
    pt->AddText("Hamamatsu");  
    TText *t = (TText*)pt->AddText("ET");
    t->SetTextColor(kRed);
    
    //Alpha energy and width vs cell
    TGraphErrors *gAE = new TGraphErrors();
    TGraphErrors *gAEW = new TGraphErrors();
    TGraphErrors *gAE_ET = new TGraphErrors();
    TGraphErrors *gAEW_ET = new TGraphErrors();
    TH1D* h_AE = new TH1D("h_AE","h_AE",50, lAE, hAE);
    TH1D* hAEW = new TH1D("hAEW","hAEW",50, 0.01, 0.06);

    //Alpha smeared energy and width vs cell
    TGraphErrors *gAEsmear = new TGraphErrors();
    TGraphErrors *gAEsmearW = new TGraphErrors();
    TGraphErrors *gAEsmear_ET = new TGraphErrors();
    TGraphErrors *gAEsmearW_ET = new TGraphErrors();
    TH1D* h_AEsmear = new TH1D("h_AEsmear","h_AEsmear",50, lAE, hAE);
    TH1D* hAEsmearW = new TH1D("hAEsmearW","hAEsmearW",50, 0.01, 0.06);
     
    //Alpha energy norm
    TGraphErrors *gAdE = new TGraphErrors();
    TGraphErrors *gAdEW = new TGraphErrors();
    TGraphErrors *gAdE_ET = new TGraphErrors();
    TGraphErrors *gAdEW_ET = new TGraphErrors();

    //Alpha PSD and width vs cell
    TGraphErrors *gApsd = new TGraphErrors();
    TGraphErrors *gApsdW = new TGraphErrors();
    TGraphErrors *gApsd_ET = new TGraphErrors();
    TGraphErrors *gApsdW_ET = new TGraphErrors();
    TH1D* h_Apsd = new TH1D("h_Apsd","h_Apsd",30, lApsd, hApsd);
    TH1D* hApsdW = new TH1D("hApsdW","hApsdW",100, 0.0, 0.1);
 
    //Beta PSD and width vs cell
    TGraphErrors *gBpsd = new TGraphErrors();
    TGraphErrors *gBpsdW = new TGraphErrors();
    TGraphErrors *gBpsd_ET = new TGraphErrors();
    TGraphErrors *gBpsdW_ET = new TGraphErrors();
    TH1D* hBpsd = new TH1D("hBpsd","hBpsd",30, 0.1, 0.2);
    TH1D* hBpsdW = new TH1D("hBpsdW","hBpsdW",100, 0.0, 0.04);

    //Alpha Z distribution mean and width 
    TGraphErrors *gAZ = new TGraphErrors();
    TGraphErrors *gAZW = new TGraphErrors();
    TGraphErrors *gAZ_ET = new TGraphErrors();
    TGraphErrors *gAZW_ET = new TGraphErrors();

    //dZ mean and width vs cell
    TGraphErrors *gdZ = new TGraphErrors();
    TGraphErrors *gdZW = new TGraphErrors();
    TGraphErrors *gdZ_ET = new TGraphErrors();
    TGraphErrors *gdZW_ET = new TGraphErrors();
    TH1D* h_dZ = new TH1D("h_dZ","h_dZ",100, -50, 50);
    TH1D* hdZW = new TH1D("hdZW","hdZW",50, 30, 100);

    //Efficiency plots
    TPaveText *ptEff = new TPaveText(0.8, 0.15, 0.99, 0.35,"ndc");
    ptEff->SetFillColor(0);
    ptEff->SetTextColor(kBlack);
    ptEff->SetShadowColor(0);
    ptEff->AddText("Total efficiency");
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Cut Efficiencies by Cell");
    TGraph *grEff = new TGraph();
    grEff->SetMarkerColor(kBlack);
    grEff->SetMarkerStyle(8);
    TGraph *grEffAE = new TGraph();
    grEffAE->SetMarkerColor(kRed);
    grEffAE->SetMarkerStyle(8);
    TText *teff = ptEff->AddText("#alpha E cut efficiency");
    teff->SetTextColor(kRed);
    TGraph *grEffApsd = new TGraph();
    grEffApsd->SetMarkerColor(kBlue);
    grEffApsd->SetMarkerStyle(8);
    TText *teff2 = ptEff->AddText("#alpha PSD cut efficiency");
    teff2->SetTextColor(kBlue);
    TGraph *grEffBpsd = new TGraph();
    grEffBpsd->SetMarkerColor(kMagenta);
    grEffBpsd->SetMarkerStyle(8);
    TText *teff3 = ptEff->AddText("#beta PSD cuts efficiency");
    teff3->SetTextColor(kMagenta);
    TGraph *grEffdZ = new TGraph();
    grEffdZ->SetMarkerColor(kGreen+2);
    grEffdZ->SetMarkerStyle(8);
    TText *teff4 = ptEff->AddText("dZ cut efficiency");
    teff4->SetTextColor(kGreen+2);

    
    int nAE = 0, nApsd = 0, nBpsd = 0, ndZ = 0, nZ = 0 , nEff = 0;
    int nAE_ET = 0, nAEsmear_ET = 0, nApsd_ET = 0, nBpsd_ET = 0, ndZ_ET = 0,
      nZ_ET = 0;
    
    double guessE = alpha_type == 1 ?  1.06 : 0.84;
    double guessEerr = 0.05/sqrt(guessE);
    for(int i=0;i<kNcell;++i){
      //sleep(1);
      if(exclude_cells)
	if( find(begin(ExcludeCellArr), end(ExcludeCellArr), i)
	    != end(ExcludeCellArr) )
	  continue;
      if(hCellAE[i][0]->GetEntries()>0){//Alpha E
	cByCell->cd(1);
	hCellAE[i][2] = (TH1D*)hCellAE[i][0]->Clone(Form("hCellAE[%i][2]",i));
	hCellAE[i][2]->Add(hCellAE[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",
			 guessE-2*guessEerr, guessE + 2*guessEerr);
	f->SetParameters(hCellAE[i][2]->GetMaximum(),guessE,guessEerr);
	f->SetRange(guessE-2*guessEerr, guessE + 2*guessEerr);
	hCellAE[i][2]->Draw();
	gPad->Update();
	printf("\n\nCell %i\n", i);
	hCellAE[i][2]->Fit(f,"r");
	if(f->GetParameter(2)<0){//deal with negative width
	  f->SetParameter(2,fabs(f->GetParameter(2)));
	  hCellAE[i][2]->Fit(f,"r"); 
	}
	gAE->SetPoint(nAE, i, f->GetParameter(1));
	gAE->SetPointError(nAE, 0, f->GetParError(1));
	gAEW->SetPoint(nAE, i, f->GetParameter(2));
	gAEW->SetPointError(nAE, 0, f->GetParError(2));
	h_AE->Fill(f->GetParameter(1));
	hAEW->Fill(f->GetParameter(2));
	double lnsig = (f->GetParameter(1) - lAE)/f->GetParameter(2);
	double hnsig = (hAE - f->GetParameter(1))/f->GetParameter(2);
	effAE[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
	grEffAE->SetPoint(nAE, i, effAE[i]);
	++nAE;
	if(isET(i)){
	  gAE_ET->SetPoint(nAE_ET, i, f->GetParameter(1));
	  gAE_ET->SetPointError(nAE_ET, 0, f->GetParError(1));
	  gAEW_ET->SetPoint(nAE_ET, i, f->GetParameter(2));
	  gAEW_ET->SetPointError(nAE_ET, 0, f->GetParError(2));
	  ++nAE_ET;
	}
      }
      if(hCellAEsmear[i][0]->GetEntries()>0){//Alpha E
	cByCell->cd(1);
	hCellAEsmear[i][2] = (TH1D*)hCellAEsmear[i][0]->Clone(Form("hCellAEsmear[%i][2]",i));
	hCellAEsmear[i][2]->Add(hCellAEsmear[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1);
	double estE = alpha_type == 1 ? 1.06 : 0.845;
	double estEerr = sqrt(estE)*0.05;
	f->SetParameters(hCellAEsmear[i][2]->GetMaximum(), estE, estEerr);
	f->SetRange(estE-2*estEerr, estE+2*estEerr);
	hCellAEsmear[i][2]->Draw();
	gPad->Update();
	printf("\n\nCell %i\n", i);
	hCellAEsmear[i][2]->Fit(f,"r");
	if(f->GetParameter(2)<0){//deal with negative width
	  f->SetParameter(2,fabs(f->GetParameter(2)));
	  hCellAEsmear[i][2]->Fit(f,"r"); 
	}
	gAEsmear->SetPoint(nAE, i, f->GetParameter(1));
	gAEsmear->SetPointError(nAE, 0, f->GetParError(1));
	gAEsmearW->SetPoint(nAE, i, f->GetParameter(2));
	gAEsmearW->SetPointError(nAE, 0, f->GetParError(2));
	h_AEsmear->Fill(f->GetParameter(1));
	hAEsmearW->Fill(f->GetParameter(2));
	if(isET(i)){
	  gAEsmear_ET->SetPoint(nAE_ET, i, f->GetParameter(1));
	  gAEsmear_ET->SetPointError(nAE_ET, 0, f->GetParError(1));
	  gAEsmearW_ET->SetPoint(nAE_ET, i, f->GetParameter(2));
	  gAEsmearW_ET->SetPointError(nAE_ET, 0, f->GetParError(2));
	  ++nAEsmear_ET;
	}
      }
      
      if(hCellAPSD[i][0]->GetEntries()>0){//Alpha PSD
      	cByCell->cd(2);
      	hCellAPSD[i][2] = (TH1D*)hCellAPSD[i][0]->Clone(Form("hCellAPSD[%i][2]",i));
      	hCellAPSD[i][2]->Add(hCellAPSD[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1);
      	f->SetParameters(hCellAPSD[i][2]->GetMaximum(),0.248,0.017);
      	f->SetRange(0.248-0.043, 0.248+0.043);
      	hCellAPSD[i][2]->Draw();
      	gPad->Update();
      	hCellAPSD[i][2]->Fit(f,"rq");
	if(f->GetParameter(2)<0){
	  f->SetParameter(2,-f->GetParameter(2));
	  hCellAPSD[i][2]->Fit(f,"rq");
	}
      	gApsd->SetPoint(nApsd, i, f->GetParameter(1));
      	gApsd->SetPointError(nApsd, 0, f->GetParError(1));
      	gApsdW->SetPoint(nApsd, i, f->GetParameter(2));
      	gApsdW->SetPointError(nApsd, 0, f->GetParError(2));
      	h_Apsd->Fill(f->GetParameter(1));
      	hApsdW->Fill(f->GetParameter(2));
      	double lnsig = (f->GetParameter(1) - lApsd)/f->GetParameter(2);
      	double hnsig = (hApsd - f->GetParameter(1))/f->GetParameter(2);
      	effAPSD[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
	grEffApsd->SetPoint(nApsd, i, effAPSD[i]);
      	++nApsd;
      	if(isET(i)){
      	  gApsd_ET->SetPoint(nApsd_ET, i, f->GetParameter(1));
      	  gApsd_ET->SetPointError(nApsd_ET, 0, f->GetParError(1));
      	  gApsdW_ET->SetPoint(nApsd_ET, i, f->GetParameter(2));
      	  gApsdW_ET->SetPointError(nApsd_ET, 0, f->GetParError(2));
      	  ++nApsd_ET;
      	}
     }
      
      if(hCellBPSD[i][0]->GetEntries()>0){//beta PSD
      	cByCell->cd(3);
      	hCellBPSD[i][2] = (TH1D*)hCellBPSD[i][0]->Clone(Form("hCellBPSD[%i][2]",i));
      	hCellBPSD[i][2]->Add(hCellBPSD[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0.11,0.2);
      	f->SetParameters(hCellBPSD[i][2]->GetMaximum(),0.13,0.012);
      	f->SetRange(0.13 - 2.5*0.012, 0.13 + 2.5*0.012);
      	hCellBPSD[i][2]->Draw();
      	gPad->Update();
      	hCellBPSD[i][2]->Fit(f,"rq");
	if(f->GetParameter(2)<0){//deal with negative width
	  f->SetParameter(2,fabs(f->GetParameter(2)));
	  hCellBPSD[i][2]->Fit(f,"rq"); 
	}
      	gBpsd->SetPoint(nBpsd, i, f->GetParameter(1));
      	gBpsd->SetPointError(nBpsd, 0, f->GetParError(1));
      	gBpsdW->SetPoint(nBpsd, i, f->GetParameter(2));
      	gBpsdW->SetPointError(nBpsd, 0, f->GetParError(2));
      	hBpsd->Fill(f->GetParameter(1));
      	hBpsdW->Fill(f->GetParameter(2));
      	double lnsig = (f->GetParameter(1) - lPpsd)/f->GetParameter(2);
      	double hnsig = (hPpsd - f->GetParameter(1))/f->GetParameter(2);
      	effBPSD[i] = (erf(lnsig/sqrt(2)) + erf(hnsig/sqrt(2)))/2.0;
	grEffBpsd->SetPoint(nBpsd, i, effBPSD[i]);
      	++nBpsd;
      	if(isET(i)){
      	  gBpsd_ET->SetPoint(nBpsd_ET, i, f->GetParameter(1));
      	  gBpsd_ET->SetPointError(nBpsd_ET, 0, f->GetParError(1));
      	  gBpsdW_ET->SetPoint(nBpsd_ET, i, f->GetParameter(2));
      	  gBpsdW_ET->SetPointError(nBpsd_ET, 0, f->GetParError(2));
      	  ++nBpsd_ET;
      	}
      }
      
      if(hCelldZ[i][0]->GetEntries()>0){//dZ
      	cByCell->cd(4);
      	hCelldZ[i][2] = (TH1D*)hCelldZ[i][0]->Clone(Form("hCelldZ[%i][2]",i));
      	hCelldZ[i][2]->Add(hCelldZ[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow((x-[1])/[2],2))",-100,100);
      	f->SetParameters(hCelldZ[i][2]->GetMaximum(),0,60);
      	hCelldZ[i][2]->Draw();
      	gPad->Update();
      	hCelldZ[i][2]->Fit(f,"rq");
	if(f->GetParameter(2)<0){//deal with negative width
	  f->SetParameter(2,fabs(f->GetParameter(2)));
	  hCelldZ[i][2]->Fit(f,"rq"); 
	}
      	gdZ->SetPoint(ndZ, i, f->GetParameter(1));
      	gdZ->SetPointError(ndZ, 0, f->GetParError(1));
      	gdZW->SetPoint(ndZ, i, f->GetParameter(2));
      	gdZW->SetPointError(ndZ, 0, f->GetParError(2));
      	h_dZ->Fill(f->GetParameter(1));
      	hdZW->Fill(f->GetParameter(2));
      	effdZ[i] = f->Integral(ldZ, hdZ)/f->Integral(-1000,1000);
	if(effdZ[i]<0.95)sleep(3);
 	grEffdZ->SetPoint(ndZ, i, effdZ[i]);
     	++ndZ;
      	if(isET(i)){
      	  gdZ_ET->SetPoint(ndZ_ET, i, f->GetParameter(1));
      	  gdZ_ET->SetPointError(ndZ_ET, 0, f->GetParError(1));
      	  gdZW_ET->SetPoint(ndZ_ET, i, f->GetParameter(2));
      	  gdZW_ET->SetPointError(ndZ_ET, 0, f->GetParError(2));
      	  ++ndZ_ET;
      	}
      }
      
      if(hCellZ[i][0]->GetEntries()>0){//dZ
      	cByCell->cd(5);
      	hCellZ[i][2] = (TH1D*)hCellZ[i][0]->Clone(Form("hCellZ[%i][2]",i));
      	hCellZ[i][2]->Add(hCellZ[i][1],-1);
      	hCellZ[i][2]->Draw();
      	gPad->Update();
      	gAZ->SetPoint(nZ, i, hCellZ[i][2]->GetMean());
      	gAZ->SetPointError(nZ, 0, hCellZ[i][2]->GetMeanError());
      	gAZW->SetPoint(nZ, i, hCellZ[i][2]->GetRMS());
      	gAZW->SetPointError(nZ, 0, hCellZ[i][2]->GetRMSError());
     	++nZ;
      	if(isET(i)){
      	  gAZ_ET->SetPoint(nZ_ET, i, hCellZ[i][2]->GetMean());
      	  gAZ_ET->SetPointError(nZ_ET, 0, hCellZ[i][2]->GetMeanError());
      	  gAZW_ET->SetPoint(nZ_ET, i, hCellZ[i][2]->GetRMS());
      	  gAZ_ET->SetPointError(nZ_ET, 0, hCellZ[i][2]->GetRMSError());
      	  ++nZ_ET;
      	}
      }
       grEff->SetPoint(nEff,i,effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i]);
      ++nEff;
    }

    //Plot Alpha E
    //-------------------
    gStyle->SetOptStat("rmen");
    gStyle->SetOptFit(1111);
    cCellAE = new TCanvas("cCellAE","cCellAE",0,0,1600,900);
    cCellAE->Divide(2,2);
    cCellAE->cd(1);
    gAE->Draw("ap");
    TF1 fp0("fp0","pol0",0,1); 
    gAE->Fit("fp0");
    gPad->Update();
    printf("***AE\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gAE->SetTitle(Form("^{%i}Po Alpha Energy Mean vs Cell",
		       (alpha_type==1?212:214)));
    gAE->SetMarkerColor(kBlue);
    gAE->SetLineColor(kBlue);
    gAE->SetMarkerStyle(8);
    gAE->SetMarkerSize(0.6);
    TPaveStats *ps;
    if(!P2_style){
      cCellAE->Update();
      ps = (TPaveStats*)gAE->FindObject("stats");
      ps->SetX1NDC(0.141);
      ps->SetX2NDC(0.49);
      ps->SetY1NDC(0.899);
      ps->SetY2NDC(0.78);
    }
    gAE->GetXaxis()->SetTitle("Cell Number");
    gAE->GetYaxis()->SetTitle(Form("Alpha Energy (MeV)"));
    gAE_ET->SetMarkerColor(kRed);
    gAE_ET->SetLineColor(kRed);
    gAE_ET->SetMarkerStyle(8);
    gAE_ET->SetMarkerSize(0.6);
    gAE_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellAE->cd(2);
    h_AE->Draw();
    h_AE->SetTitle(Form("^{%i}Po Alpha Energy By Cell",
			(alpha_type==1 ? 212 : 214)));
    h_AE->GetXaxis()->SetTitle("Alpha Energy (MeV)");
    gPad->Update();
    cCellAE->cd(3);
    gAEW->SetTitle(Form("^{%i}Po Alpha Energy Width vs Cell",
		       (alpha_type==1 ? 212 : 214)));
    gAEW->SetMarkerColor(kBlue);
    gAEW->SetLineColor(kBlue);
    gAEW->SetMarkerStyle(8);
    gAEW->SetMarkerSize(0.6);
    gAEW->Draw("ap");
    gAEW->Fit("fp0");
    printf("***AEW\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gPad->Update();
    TPaveStats *ps1;
    if(!P2_style){
      ps1 = (TPaveStats*)gAEW->FindObject("stats");
      ps1->SetX1NDC(0.141);
      ps1->SetX2NDC(0.49);
      ps1->SetY1NDC(0.899);
      ps1->SetY2NDC(0.78);
    }
    gAEW->GetXaxis()->SetTitle("Cell Number");
    gAEW->GetYaxis()->SetTitle(Form("Alpha Energy Width (MeV)"));
    gAEW_ET->SetMarkerColor(kRed);
    gAEW_ET->SetLineColor(kRed);
    gAEW_ET->SetMarkerStyle(8);
    gAEW_ET->SetMarkerSize(0.6);
    gAEW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellAE->cd(4);
    hAEW->Draw();
    hAEW->SetTitle(Form("^{%i}Po Alpha Energy Width By Cell",
		       (alpha_type==1 ? 212 : 214)));
    hAEW->GetXaxis()->SetTitle(Form("Alpha Energy Width (MeV)"));
    gPad->Update();
    cCellAE->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iAlphaEvsCell%s.pdf", (alpha_type == 1 ? 212:214),fid.Data()));
    //-------------------

    
    //Plot Alpha Esmear
    //-------------------
    gStyle->SetOptStat("rmen");
    gStyle->SetOptFit(1111);
    cCellAEsmear = new TCanvas("cCellAEsmear","cCellAEsmear",0,0,1600,900);
    cCellAEsmear->Divide(2,2);
    cCellAEsmear->cd(1);
    gAEsmear->Draw("ap");
    gAEsmear->Fit("fp0");
    gPad->Update();
    printf("***AEsmear\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gAEsmear->SetTitle(Form("^{%i}Po Alpha Smeared Energy Mean vs Cell",
		       (alpha_type==1?212:214)));
    gAEsmear->SetMarkerColor(kBlue);
    gAEsmear->SetLineColor(kBlue);
    gAEsmear->SetMarkerStyle(8);
    gAEsmear->SetMarkerSize(0.6);
    if(!P2_style){
      cCellAEsmear->Update();
      ps = (TPaveStats*)gAEsmear->FindObject("stats");
      ps->SetX1NDC(0.141);
      ps->SetX2NDC(0.49);
      ps->SetY1NDC(0.899);
      ps->SetY2NDC(0.78);
    }
    gAEsmear->GetXaxis()->SetTitle("Cell Number");
    gAEsmear->GetYaxis()->SetTitle(Form("Smeared Alpha Energy (MeV)"));
    gAEsmear_ET->SetMarkerColor(kRed);
    gAEsmear_ET->SetLineColor(kRed);
    gAEsmear_ET->SetMarkerStyle(8);
    gAEsmear_ET->SetMarkerSize(0.6);
    gAEsmear_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellAEsmear->cd(2);
    h_AEsmear->Draw();
    h_AEsmear->SetTitle(Form("^{%i}Po Smeared Alpha Energy By Cell",
			(alpha_type==1 ? 212 : 214)));
    h_AEsmear->GetXaxis()->SetTitle("Alpha Energy (MeV)");
    gPad->Update();
    cCellAEsmear->cd(3);
    gAEsmearW->SetTitle(Form("^{%i}Po Smeared Alpha Energy Width vs Cell",
		       (alpha_type==1 ? 212 : 214)));
    gAEsmearW->SetMarkerColor(kBlue);
    gAEsmearW->SetLineColor(kBlue);
    gAEsmearW->SetMarkerStyle(8);
    gAEsmearW->SetMarkerSize(0.6);
    gAEsmearW->Draw("ap");
    gAEsmearW->Fit("fp0");
    printf("***AEsmearW\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gPad->Update();
    if(!P2_style){
      ps1 = (TPaveStats*)gAEsmearW->FindObject("stats");
      ps1->SetX1NDC(0.141);
      ps1->SetX2NDC(0.49);
      ps1->SetY1NDC(0.899);
      ps1->SetY2NDC(0.78);
    }
    gAEsmearW->GetXaxis()->SetTitle("Cell Number");
    gAEsmearW->GetYaxis()->SetTitle(Form("Smeared Alpha Energy Width (MeV)"));
    gAEsmearW_ET->SetMarkerColor(kRed);
    gAEsmearW_ET->SetLineColor(kRed);
    gAEsmearW_ET->SetMarkerStyle(8);
    gAEsmearW_ET->SetMarkerSize(0.6);
    gAEsmearW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellAE->cd(4);
    hAEsmearW->Draw();
    hAEsmearW->SetTitle(Form("^{%i}Po Smeared Alpha Energy Width By Cell",
		       (alpha_type==1 ? 212 : 214)));
    hAEW->GetXaxis()->SetTitle(Form("Smeared Alpha Energy Width (MeV)"));
    gPad->Update();
    cCellAEsmear->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iAlphaEsmearvsCell%s.pdf", (alpha_type == 1 ? 212:214),fid.Data()));
    //-------------------


    //Plot Alpha PSD
    //-------------------
    cCellApsd = new TCanvas("cCellApsd","cCellApsd",0,0,1600,900);
    cCellApsd->Divide(2,2);
  
    cCellApsd->cd(1);
    gApsd->Fit("fp0");
    printf("***Apsd\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gApsd->SetTitle(Form("^{%i}Po Alpha PSD Mean vs Cell",
		       (alpha_type==1 ? 212 : 214)));
    gApsd->SetMarkerColor(kBlue);
    gApsd->SetLineColor(kBlue);
    gApsd->SetMarkerStyle(8);
    gApsd->SetMarkerSize(0.6);
    gApsd->Draw("ap");
    gPad->Update();
    if(!P2_style){
      ps = (TPaveStats*)gApsd->FindObject("stats");
      ps->SetX1NDC(0.141);
      ps->SetX2NDC(0.49);
      ps->SetY1NDC(0.899);
      ps->SetY2NDC(0.78);
    }
    gApsd->GetXaxis()->SetTitle("Cell Number");
    gApsd->GetYaxis()->SetTitle("Alpha PSD");
    gApsd_ET->SetMarkerColor(kRed);
    gApsd_ET->SetLineColor(kRed);
    gApsd_ET->SetMarkerStyle(8);
    gApsd_ET->SetMarkerSize(0.6);
    gApsd_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellApsd->cd(2);
    h_Apsd->Draw();
    h_Apsd->SetTitle(Form("^{%i}Po Alpha PSD By Cell",
		       (alpha_type==1 ? 212 : 214)));
    h_Apsd->GetXaxis()->SetTitle("Alpha PSD");
    gPad->Update();
    cCellApsd->cd(3);
    gApsdW->SetTitle(Form("^{%i}Po Alpha PSD Width vs Cell",
		       (alpha_type==1 ? 212 : 214)));
    gApsdW->SetMarkerColor(kBlue);
    gApsdW->SetLineColor(kBlue);
    gApsdW->SetMarkerStyle(8);
    gApsdW->SetMarkerSize(0.6);
    gApsdW->Draw("ap");
    gApsdW->Fit("fp0");
    printf("***ApsdW\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gPad->Update();
    if(!P2_style){
      ps1 = (TPaveStats*)gApsdW->FindObject("stats");
      ps1->SetX1NDC(0.141);
      ps1->SetX2NDC(0.49);
      ps1->SetY1NDC(0.899);
      ps1->SetY2NDC(0.78);
    }  
    gApsdW->GetXaxis()->SetTitle("Cell Number");
    gApsdW->GetYaxis()->SetTitle("Alpha PSD Width");
    gApsdW_ET->SetMarkerColor(kRed);
    gApsdW_ET->SetLineColor(kRed);
    gApsdW_ET->SetMarkerStyle(8);
    gApsdW_ET->SetMarkerSize(0.6);
    gApsdW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellApsd->cd(4);
    hApsdW->Draw();
    hApsdW->SetTitle(Form("^{%i}Po Alpha PSD Width By Cell",
			  (alpha_type==1 ? 212 : 214)));
    hApsdW->GetXaxis()->SetTitle("Alpha PSD Width");
    gPad->Update();
    cCellApsd->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iAlphaPSDvsCell%s.pdf", (alpha_type == 1 ? 212:214), fid.Data()));
    //-------------------
    

    //Plot Beta PSD
    //-------------------
    cCellBpsd = new TCanvas("cCellBpsd","cCellBpsd",0,0,1600,900);
    cCellBpsd->Divide(2,2);
  
    cCellBpsd->cd(1);
    gBpsd->Fit("fp0");
    printf("***Bpsd\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));

    gBpsd->SetTitle(Form("^{%i}Bi Beta PSD Mean vs Cell",
			 (alpha_type==1 ? 212 : 214)));
    gBpsd->SetMarkerColor(kBlue);
    gBpsd->SetLineColor(kBlue);
    gBpsd->SetMarkerStyle(8);
    gBpsd->SetMarkerSize(0.6);
    gBpsd->Draw("ap");
    gPad->Update();
    if(!P2_style){
      ps = (TPaveStats*)gBpsd->FindObject("stats");
      ps->SetX1NDC(0.141);
      ps->SetX2NDC(0.49);
      ps->SetY1NDC(0.899);
      ps->SetY2NDC(0.78);
    }
    gBpsd->GetXaxis()->SetTitle("Cell Number");
    gBpsd->GetYaxis()->SetTitle("Beta PSD");
    gBpsd_ET->SetMarkerColor(kRed);
    gBpsd_ET->SetLineColor(kRed);
    gBpsd_ET->SetMarkerStyle(8);
    gBpsd_ET->SetMarkerSize(0.6);
    gBpsd_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellBpsd->cd(2);
    hBpsd->Draw();
    hBpsd->SetTitle(Form("^{%i}Bi Beta PSD By Cell",
			 (alpha_type==1 ? 212 : 214)));
    hBpsd->GetXaxis()->SetTitle("Beta PSD");
    gPad->Update();
    cCellBpsd->cd(3);
    gBpsdW->SetTitle(Form("^{%i}Bi Beta PSD Width vs Cell",
			  (alpha_type==1 ? 212 : 214)));
    gBpsdW->SetMarkerColor(kBlue);
    gBpsdW->SetLineColor(kBlue);
    gBpsdW->SetMarkerStyle(8);
    gBpsdW->SetMarkerSize(0.6);
    gBpsdW->Draw("ap");
    gBpsdW->Fit("fp0");
    printf("***BpsdW\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gPad->Update();
    if(!P2_style){
      ps1 = (TPaveStats*)gBpsdW->FindObject("stats");
      ps1->SetX1NDC(0.141);
      ps1->SetX2NDC(0.49);
      ps1->SetY1NDC(0.899);
      ps1->SetY2NDC(0.78);
    }
    gBpsdW->GetXaxis()->SetTitle("Cell Number");
    gBpsdW->GetYaxis()->SetTitle("Beta PSD Width");
    gBpsdW_ET->SetMarkerColor(kRed);
    gBpsdW_ET->SetLineColor(kRed);
    gBpsdW_ET->SetMarkerStyle(8);
    gBpsdW_ET->SetMarkerSize(0.6);
    gBpsdW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellBpsd->cd(4);
    hBpsdW->Draw();
    hBpsdW->SetTitle(Form("^{%i}Bi Beta PSD Width By Cell",
			  (alpha_type==1 ? 212 : 214)));
    hBpsdW->GetXaxis()->SetTitle("Beta PSD Width");
    gPad->Update();
    cCellBpsd->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iBetaPSDvsCell%s.pdf", (alpha_type == 1 ? 212:214), fid.Data()));


    //Plot dZ
    //-------------------
    cCelldZ = new TCanvas("cCelldZ","cCelldZ",0,0,1600,900);
    cCelldZ->Divide(2,2);
  
    cCelldZ->cd(1);

    gdZ->Fit("fp0");
    printf("***dZ\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gdZ->SetTitle("Alpha-Beta dZ Mean vs Cell");
    gdZ->SetMarkerColor(kBlue);
    gdZ->SetLineColor(kBlue);
    gdZ->SetMarkerStyle(8);
    gdZ->SetMarkerSize(0.6);
    gdZ->Draw("ap");
    gPad->Update();
    if(!P2_style){
      ps = (TPaveStats*)gdZ->FindObject("stats");
      ps->SetX1NDC(0.141);
      ps->SetX2NDC(0.49);
      ps->SetY1NDC(0.899);
      ps->SetY2NDC(0.78);
    }
    gdZ->GetXaxis()->SetTitle("Cell Number");
    gdZ->GetYaxis()->SetTitle("dZ (mm)");
    gdZ_ET->SetMarkerColor(kRed);
    gdZ_ET->SetLineColor(kRed);
    gdZ_ET->SetMarkerStyle(8);
    gdZ_ET->SetMarkerSize(0.6);
    gdZ_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCelldZ->cd(2);
    h_dZ->Draw();
    h_dZ->SetTitle("Alpha-Beta dZ Mean vs Cell");
    h_dZ->GetXaxis()->SetTitle("dZ (mm)");
    gPad->Update();
    cCelldZ->cd(3);
    gdZW->SetTitle("Alpha-Beta dZ Width vs Cell");
    gdZW->SetMarkerColor(kBlue);
    gdZW->SetLineColor(kBlue);
    gdZW->SetMarkerStyle(8);
    gdZW->SetMarkerSize(0.6);
    gdZW->Draw("ap");
    gdZW->Fit("fp0");
    gPad->Update();
    if(!P2_style){
      ps1 = (TPaveStats*)gdZW->FindObject("stats");
      ps1->SetX1NDC(0.141);
      ps1->SetX2NDC(0.49);
      ps1->SetY1NDC(0.899);
      ps1->SetY2NDC(0.78);
    }
    gdZW->GetXaxis()->SetTitle("Cell Number");
    gdZW->GetYaxis()->SetTitle("Alpha-Beta dZ Width vs Cell");
    gdZW_ET->SetMarkerColor(kRed);
    gdZW_ET->SetLineColor(kRed);
    gdZW_ET->SetMarkerStyle(8);
    gdZW_ET->SetMarkerSize(0.6);
    gdZW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCelldZ->cd(4);
    hdZW->Draw();
    hdZW->SetTitle("Alpha-Beta dZ Width vs Cell");
    hdZW->GetXaxis()->SetTitle("dZ (mm)");
    gPad->Update();
    cCelldZ->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%idZvsCell%s.pdf", (alpha_type == 1 ? 212:214), fid.Data()));
    //-------------------



    //Plot Z
    //-------------------
    cCellZ = new TCanvas("cCellZ","cCellZ",0,0,1400,600);
    cCellZ->Divide(2,1);
  
    cCellZ->cd(1);
    gAZ->Fit("fp0");
    printf("***AZ\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gAZ->SetTitle("Alpha Z-distribution Mean vs Cell");
    gAZ->SetMarkerColor(kBlue);
    gAZ->SetLineColor(kBlue);
    gAZ->SetMarkerStyle(8);
    gAZ->SetMarkerSize(0.6);
    gAZ->Draw("ap");
    gPad->Update();
    if(!P2_style){
      ps = (TPaveStats*)gAZ->FindObject("stats");
      ps->SetX1NDC(0.141);
      ps->SetX2NDC(0.49);
      ps->SetY1NDC(0.899);
      ps->SetY2NDC(0.78);
    }
    gAZ->GetXaxis()->SetTitle("Cell Number");
    gAZ->GetYaxis()->SetTitle("Alpha Z (mm)");
    gAZ_ET->SetMarkerColor(kRed);
    gAZ_ET->SetLineColor(kRed);
    gAZ_ET->SetMarkerStyle(8);
    gAZ_ET->SetMarkerSize(0.6);
    gAZ_ET->Draw("samep");
    pt->Draw();
    gPad->Update();

    cCellZ->cd(2);
    gAZW->SetTitle(Form("%s Alpha Z-distribution Width vs Cell",title[alpha_type].Data()));
    gAZW->SetMarkerColor(kBlue);
    gAZW->SetLineColor(kBlue);
    gAZW->SetMarkerStyle(8);
    gAZW->SetMarkerSize(0.6);
    gAZW->Draw("ap");
    gAZW->Fit("fp0");
    printf("***AZW\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fp0.GetChisquare(), fp0.GetNDF(), fp0.GetParameter(0), fp0.GetParError(0));
    gPad->Update();
    if(!P2_style){
      ps1 = (TPaveStats*)gAZW->FindObject("stats");
      ps1->SetX1NDC(0.141);
      ps1->SetX2NDC(0.49);
      ps1->SetY1NDC(0.899);
      ps1->SetY2NDC(0.78);
    }
    gAZW->GetXaxis()->SetTitle("Cell Number");
    gAZW->GetYaxis()->SetTitle("Alpha Z RMS (mm)");
    gAZW_ET->SetMarkerColor(kRed);
    gAZW_ET->SetLineColor(kRed);
    gAZW_ET->SetMarkerStyle(8);
    gAZW_ET->SetMarkerSize(0.6);
    gAZW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellZ->SaveAs(Form("/home/jonesdc/prospect/plots/BiPo%iZvsCell%s.pdf", (alpha_type == 1 ? 212:214), fid.Data()));
    //-------------------


    //plot rates and efficiencies
    //---------------------------
    gStyle->SetOptStat(0);
    cCellRate = new TCanvas("cCellRate","cCellRate",0,0,1400,1000);
    cCellRate->Divide(2,2);

    TH2D *hHeat = new TH2D("hHeat","hHeat", ncol, 0, ncol, nrow, 0, nrow);
    TGraphErrors *grRate = new TGraphErrors();
    grRate->SetMarkerColor(kBlue);
    grRate->SetLineColor(kBlue);
    grRate->SetMarkerStyle(8);
    TGraphErrors *grRate_ET = new TGraphErrors();
    grRate_ET->SetMarkerColor(kRed);
    grRate_ET->SetLineColor(kRed);
    grRate_ET->SetMarkerStyle(8);
    TGraphErrors *grRateEffC = new TGraphErrors();
    grRateEffC->SetMarkerColor(kBlue);
    grRateEffC->SetLineColor(kBlue);
    grRateEffC->SetMarkerStyle(8);
    TGraphErrors *grRateEffC_ET = new TGraphErrors();
    grRateEffC_ET->SetMarkerColor(kRed);
    grRateEffC_ET->SetLineColor(kRed);
    grRateEffC_ET->SetMarkerStyle(8);
    int npt = 0, nptET = 0;
    //Time cut efficiency for Rate from integral of energy distribution
    double t_cut_eff = exp(-t_start/(alpha_type==1 ? 0.00043:tauBiPo));
    t_cut_eff -= exp(-t_end/(alpha_type==1 ? 0.00043:tauBiPo));
    for(int i=0;i<kNcell;++i){
      if(exclude_cells)
	if( find(begin(ExcludeCellArr), end(ExcludeCellArr), i)
	    != end(ExcludeCellArr) )
	  continue;
      if(hCellAE[i][2]->GetEntries()>0){
	double err;
	double rate = double(hCellAE[i][2]->IntegralAndError(1,hCellAE[i][2]->GetNbinsX(), err))/live/t_cut_eff/3.6;
	err /= live*t_cut_eff*3.6;
	grRate->SetPoint(npt,i, rate);
	grRate->SetPointError(npt,0, err);
	double eff = effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i];
	double scale_err = 1.0;
	grRateEffC->SetPoint(npt,i, rate/eff);
	grRateEffC->SetPointError(npt,0, scale_err*err/eff);
	hHeat->SetBinContent(i%ncol+1,i/ncol+1,rate/eff);
	++npt;
	if(isET(i)){
	  grRate_ET->SetPoint(nptET,i, rate);
	  grRate_ET->SetPointError(nptET,0, err);
	  grRateEffC_ET->SetPoint(nptET,i, rate/eff);
	  grRateEffC_ET->SetPointError(nptET,0,  scale_err*err/eff);
	  ++nptET;
	}
      }
    }
    cCellRate->cd(1);
    grRate->Draw("ap");
    grRate_ET->Draw("samep");
    gPad->Update();
    grRate->SetTitle("BiPo Rate by Cell");
    grRate->GetYaxis()->SetTitle("BiPo Rate (mHz)");
    grRate->GetXaxis()->SetTitle("Cell Number");
    grRate->Fit("pol1");
    gPad->Update();
    if(!P2_style){
      ps = (TPaveStats*)grRate->FindObject("stats");
      ps->SetX1NDC(0.18);
      ps->SetX2NDC(0.6);
    }
    gPad->Update();
    if(!fiducialize)
      pt->Draw();


    cCellRate->cd(2);
    mg->Add(grEff);
    mg->Add(grEffAE);
    mg->Add(grEffApsd);
    mg->Add(grEffBpsd);
    mg->Add(grEffdZ);
    mg->Draw("ap");
    mg->GetXaxis()->SetTitle("Cell Number");
    mg->GetYaxis()->SetTitle("Cut Efficiency");
    //mg->GetYaxis()->SetRangeUser(0.9,1.001);
    ptEff->Draw();
    
    cCellRate->cd(3);
    grRateEffC->Draw("ap");
    grRateEffC_ET->Draw("samep");
    gPad->Update();
    grRateEffC->SetTitle("Efficiency Corrected BiPo Rate by Cell");
    grRateEffC->GetYaxis()->SetTitle("BiPo Rate (mHz)");
    grRateEffC->GetXaxis()->SetTitle("Cell Number");
    grRateEffC->Fit("pol1");
    gPad->Update();
    if(!P2_style){
      ps = (TPaveStats*)grRateEffC->FindObject("stats");
      ps->SetX1NDC(0.18);
      ps->SetX2NDC(0.6);
    }
    gPad->Update();
    if(!fiducialize)
      pt->Draw();

    cCellRate->cd(4)->SetRightMargin(0.2);
    hHeat->Draw("colz");
    gPad->Update();
    hHeat->SetTitle("Efficiency Corrected BiPo Rate by Cell");
    hHeat->SetTitleOffset(0.1);
    hHeat->GetYaxis()->SetTitle("Row Number");
    hHeat->GetXaxis()->SetTitle("Column Number");
    hHeat->GetXaxis()->SetTitleOffset(1.0);
    hHeat->GetZaxis()->SetTitle("Count Rate (/hr)");
    hHeat->GetZaxis()->SetRangeUser(hHeat->GetMaximum()*0.3,hHeat->GetMaximum());
    hHeat->GetZaxis()->SetTitleOffset(1);
    hHeat->GetYaxis()->SetTitleOffset(0.8);
    gPad->Update();
    cCellRate->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoRatevsCell%i%s.png", alpha_type, fid.Data()));
    TCanvas *cRate = new TCanvas("cRate","cRate",0,0,800,600);
    cRate->SetLeftMargin(0.1);
    cRate->SetRightMargin(0.2);
    hHeat->Draw("colz");
    cRate->SaveAs(Form("%s/BiPo%iHeatMap%s.pdf", gSystem->Getenv("TECHNOTE"), alpha_type, fid.Data()));
    if(technote_plots){
      TFile f("BiPoPublicationPlots.root",(recreate == 1 ? "RECREATE" : "UPDATE"),"BiPoPlots");
      gStyle->SetPadRightMargin(0.05);
      gStyle->SetPadLeftMargin(0.08);
      gStyle->SetOptStat(0);
      bool normalize = 1;//create plots normalized to average value
      //plot 1 from technote
      TCanvas *c0 = new TCanvas("c0","c0",0,0,1200,300);
      TGraphErrors *gAE1 = new TGraphErrors();
      gAE1->SetName(Form("grEvsCellPo%i", (alpha_type == 1 ? 212 : 214)));
      gAE1->SetTitle(Form("Po-%i #alpha Energy vs. Cell", (alpha_type == 1 ? 212 : 214)));
      TF1 fE("fE","pol0",0,1);
      gAE->Fit("fE");
      printf("***AE\nChiSquare/NDF: %0.5f/%i\nFit: %0.5f$\\pm$%0.5f\n",fE.GetChisquare(), fE.GetNDF(), fE.GetParameter(0), fE.GetParError(0));
      double x, y, norm = fE.GetParameter(0);
      if(!normalize)norm = 1.0;
      for(int i=0;i<gAE->GetN();++i){
	gAE->GetPoint(i, x, y);
	gAE1->SetPoint(i, x, y/norm);
	gAE1->SetPointError(i, 0, gAE->GetErrorY(i)/norm);
      }
      gAE1->SetMarkerColor(kBlue);
      gAE1->SetLineColor(kBlue);
      gAE1->SetMarkerStyle(kCircle);
      gAE1->SetMarkerSize(0.8);
      gAE1->Draw("ap");
      gAE1->GetXaxis()->SetTitle("Segment Number");
      gAE1->GetYaxis()->SetTitle("E_{#alpha}/#LTE_{#alpha}#GT");
      if(!normalize)gAE1->GetYaxis()->SetTitle("E_{#alpha} (MeV)");
      gAE1->GetYaxis()->SetTitleOffset(0.4);
      gAE1->GetXaxis()->SetTitleOffset(0.7);
      gAE1->GetYaxis()->SetTitleSize(0.07);
      gAE1->GetXaxis()->SetTitleSize(0.07);
      gPad->Update();
      gAE1->Write();
      c0->SaveAs(Form("%s/PubBiPo%iEvsCell%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214), fid.Data()));
      
      //plot 2 from technote
      bool sigma_at_1MeV = 0;
      TCanvas *c1 = new TCanvas("c1","c1",0,0,1200,300);
      TGraphErrors *gAEW1 = new TGraphErrors();
      gAEW1->SetName(Form("grE_resvsCellPo%i", (alpha_type == 1 ? 212 : 214)));
      gAEW1->SetTitle(Form("Po-%i #alpha Energy Resolution vs. Cell", (alpha_type == 1 ? 212 : 214)));
      
       if(sigma_at_1MeV){
	norm = sqrt(norm);
       }else{
	gAEW->Fit("fE");
	norm = fE.GetParameter(0);
	if(!normalize)norm = 1.0;
       }
       for(int i=0;i<gAEW->GetN();++i){
	 gAEW->GetPoint(i, x, y);
	 gAEW1->SetPoint(i, x, y/norm);
	 gAEW1->SetPointError(i, 0, gAEW->GetErrorY(i)/norm);
       }
       gAEW1->SetMarkerColor(kBlue);
       gAEW1->SetLineColor(kBlue);
       gAEW1->SetMarkerStyle(kCircle);
       gAEW1->SetMarkerSize(0.8);
       gAEW1->Draw("ap");
       //gAEW1->GetXaxis()->SetMaxDigits(4);
       gAEW1->GetXaxis()->SetTitle("Segment Number");
       gAEW1->GetYaxis()->SetTitleOffset(0.4);
       gAEW1->GetXaxis()->SetTitleOffset(0.7);
       gAEW1->GetYaxis()->SetTitleSize(0.07);
       gAEW1->GetXaxis()->SetTitleSize(0.07);
       if(sigma_at_1MeV)
	 gAEW1->GetYaxis()->SetTitle("#sigma_{E}/#sqrt{#LTE_{#alpha}#GT}");
       else{
	 gAEW1->GetYaxis()->SetTitle("#sigma_{E}/#LT#sigma_{E}#GT");
	 if(!normalize)gAEW1->GetYaxis()->SetTitle("#sigma_{E} (MeV)");
       }
       gPad->Update();
       gAEW1->Write();
       c1->SaveAs(Form("%s/PubBiPo%iEresvsCell%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214),fid.Data()));
       
      //plot 3 from technote
       TCanvas *c2 = new TCanvas("c2","c2",0,0,1200,300);
       TGraphErrors *gdZW1 = new TGraphErrors();
       gdZW1->SetName(Form("grsigmadZvsCellPo%i", (alpha_type == 1 ? 212 : 214)));
       gdZW1->SetTitle(Form("Po-%i #DeltaZ 1-#sigma Width vs. Cell", (alpha_type == 1 ? 212 : 214)));
       gdZW->Fit("fE");
       norm = fE.GetParameter(0);
       if(!normalize)norm = 1.0;
       for(int i=0;i<gdZW->GetN();++i){
	 gdZW->GetPoint(i, x, y);
	 gdZW1->SetPoint(i, x, y/norm);
	 gdZW1->SetPointError(i, 0, gdZW->GetErrorY(i)/norm);
       }
       gdZW1->SetMarkerColor(kBlue);
       gdZW1->SetLineColor(kBlue);
       gdZW1->SetMarkerStyle(kCircle);
       gdZW1->SetMarkerSize(0.8);
       gdZW1->Draw("ap");
       gdZW1->GetYaxis()->SetTitleOffset(0.4);
       gdZW1->GetXaxis()->SetTitleOffset(0.7);
       gdZW1->GetYaxis()->SetTitleSize(0.07);
       gdZW1->GetXaxis()->SetTitleSize(0.07);
       gdZW1->GetXaxis()->SetTitle("Segment Number");
       gdZW1->GetYaxis()->SetTitle("#sigma_{Z}/#LT#sigma_{Z}#GT");
       if(!normalize) gdZW1->GetYaxis()->SetTitle("#sigma_{Z} (mm)");
       gPad->Update();
       gdZW1->Write();
       c2->SaveAs(Form("%s/PubBiPo%idZWidthvsCell%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214), fid.Data()));

       //plot 4 from technote
       TCanvas *c3 = new TCanvas("c3","c3",0,0,1200,300);
       TGraphErrors *gAZW1 = new TGraphErrors();
       gAZW1->SetName(Form("grZRMSvsCellPo%i", (alpha_type == 1 ? 212 : 214)));
       gAZW1->SetTitle(Form("Po-%i Z-distribution RMS Width vs. Cell", (alpha_type == 1 ? 212 : 214)));
       gAZW->Fit("fE");
       norm = fE.GetParameter(0);
       if(!normalize)norm = 1.0;
       for(int i=0;i<gAZW->GetN();++i){
	 gAZW->GetPoint(i, x, y);
	 gAZW1->SetPoint(i, x, y/norm);
	 gAZW1->SetPointError(i, 0, gAZW->GetErrorY(i)/norm);
       }
       gAZW1->SetMarkerColor(kBlue);
       gAZW1->SetLineColor(kBlue);
       gAZW1->SetMarkerStyle(kCircle);
       gAZW1->SetMarkerSize(0.8);
       gAZW1->Draw("ap");
       gAZW1->GetYaxis()->SetTitleOffset(0.4);
       gAZW1->GetXaxis()->SetTitleOffset(0.7);
       gAZW1->GetYaxis()->SetTitleSize(0.07);
       gAZW1->GetXaxis()->SetTitleSize(0.07);
       gAZW1->GetXaxis()->SetTitle("Segment Number");
       gAZW1->GetYaxis()->SetTitle("Z_{RMS}/#LT Z_{RMS}#GT");
       if(!normalize) gAZW1->GetYaxis()->SetTitle("Z_{RMS} (mm)");
       gPad->Update();
       gAZW1->Write();
       c3->SaveAs(Form("%s/PubBiPo%iZRMSvsCell%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214), fid.Data()));

       //plot 9 from technote
       TCanvas *c4 = new TCanvas("c4","c4",0,0,1200,300);
       TGraphErrors *gAZ1 = new TGraphErrors();
       gAZ1->SetName(Form("grZvsCellPo%i", (alpha_type == 1 ? 212 : 214)));
       gAZ1->SetTitle(Form("Po-%i Mean of Z-distribution vs. Cell", (alpha_type == 1 ? 212 : 214)));
       gAZ->Fit("fE");
       norm = fE.GetParameter(0);
       normalize = 0;
       if(!normalize) norm = 1.0;
       for(int i=0;i<gAZ->GetN();++i){
	 gAZ->GetPoint(i, x, y);
	 gAZ1->SetPoint(i, x, y/norm);
	 gAZ1->SetPointError(i, 0, gAZ->GetErrorY(i)/norm);
       }
       gAZ1->SetMarkerColor(kBlue);
       gAZ1->SetLineColor(kBlue);
       gAZ1->SetMarkerStyle(kCircle);
       gAZ1->SetMarkerSize(0.8);
       gAZ1->Draw("ap");
       gAZ1->GetYaxis()->SetTitleOffset(0.4);
       gAZ1->GetXaxis()->SetTitleOffset(0.7);
       gAZ1->GetYaxis()->SetTitleSize(0.07);
       gAZ1->GetXaxis()->SetTitleSize(0.07);
       gAZ1->GetXaxis()->SetTitle("Segment Number");
       gAZ1->GetYaxis()->SetTitle("Mean Z/#LT Mean Z#GT");
       if(!normalize) gAZ1->GetYaxis()->SetTitle("Mean Z (mm)");
       gPad->Update();
       gAZ1->Write();
       c4->SaveAs(Form("%s/PubBiPo%imeanZvsCell%s.pdf", gSystem->Getenv("TECHNOTE"), (alpha_type == 1 ? 212 : 214), fid.Data()));

       f.Close();

    }

    //Rate and half-life info from dt distribution
    gStyle->SetOptFit(1111);
    TCanvas *cCelldt = new TCanvas("cCelldt","cCelldt",0,0,1400,1000);
    cCelldt->Divide(2,2);
    cCelldt->cd(1);
    cCelldt->SetLeftMargin(0.12);
    //BiPo rate from dt plot vs cell
    TGraphErrors *grR1 = new TGraphErrors();
    grR1->SetMarkerColor(kBlue);
    grR1->SetLineColor(kBlue);
    grR1->SetMarkerStyle(8);
    grR1->SetTitle(Form("BiPo%i Rate by Cell",(alpha_type == 1? 212:214)));
    grR1->GetYaxis()->SetTitle("BiPo Rate (mHz)");
    grR1->GetXaxis()->SetTitle("Cell Number");
    //2nd BiPo rate from dt plot vs cell
    TGraphErrors *grR2 = new TGraphErrors();
    grR2->SetMarkerColor(kBlue);
    grR2->SetLineColor(kBlue);
    grR2->SetMarkerStyle(8);
    grR2->SetTitle(Form("BiPo214 Rate by Cell"));
    grR2->GetYaxis()->SetTitle("BiPo Rate (mHz)");
    grR2->GetXaxis()->SetTitle("Cell Number");
    //Chi square vs cell
    TGraph *grchi = new TGraph();
    grchi->SetMarkerColor(kBlue);
    grchi->SetLineColor(kBlue);
    grchi->SetMarkerStyle(8);
    grchi->SetTitle(Form("#chi^{2} of Exponential Decay Fit by Cell"));
    grchi->GetYaxis()->SetTitle("#chi^{2}");
    grchi->GetXaxis()->SetTitle("Cell Number");
    //Half-life vs cell
    TGraphErrors *grth = new TGraphErrors();
    grth->SetMarkerColor(kBlue);
    grth->SetLineColor(kBlue);
    grth->SetMarkerStyle(8);
    grth->SetTitle(Form("BiPo%i Half-life by Cell",(alpha_type == 1? 212:214)));
    grth->GetYaxis()->SetTitle("t_{1/2} (#mus)");
    grth->GetXaxis()->SetTitle("Cell Number");
    TF1 *fpol0 = new TF1("fpol0","pol0",0,1);
    npt=0;
    for(int i=0;i<kNcell;++i){
      if(exclude_cells)
	if( find(begin(ExcludeCellArr), end(ExcludeCellArr), i)
	    != end(ExcludeCellArr) )
	  continue;
      hCelldt[i][1]->Fit("fpol0");
      hCellBkgdt[i]->Scale(1/hCellBkgdt[i]->GetBinWidth(1)/live/3.6);
      hCelldt[i][0]->Scale(1/hCelldt[i][0]->GetBinWidth(1)/live/3.6);
      hCelldt[i][1]->Scale(1/hCelldt[i][1]->GetBinWidth(1)/live/3.6);
      hCelldt[i][2]= (TH1D*)hCelldt[i][0]->Clone(Form("hCelldt[%i][2]",i));
      hCelldt[i][2]->Add(hCelldt[i][1],-1);
      fpol0->SetParameter(0,0);
      hCelldt[i][1]->Fit(fpol0);
      fdecay->SetParameters(hCelldt[i][2]->GetMaximum(),tauBiPo,0);
      if(alpha_type==1){
	//model background term as A*exp(-x/0.237)+const
	fdecay->ReleaseParameter(2);
	fdecay->ReleaseParameter(3);
	fdecay->FixParameter(0,0);
	fdecay->SetParameters(0,1,0, fpol0->GetParameter(0));
	fdecay->FixParameter(3,fpol0->GetParameter(0));
	hCellBkgdt[i]->Fit(fdecay,"B");
	fdecay->SetParameters(hCelldt[i][2]->GetMaximum()*5,0.00043,fdecay->GetParameter(2),fdecay->GetParameter(3));
	fdecay->FixParameter(2, fdecay->GetParameter(2));
	fdecay->FixParameter(3, fdecay->GetParameter(3));
	fdecay->ReleaseParameter(0);
      }
      if(alpha_type == 0){
	fdecay->FixParameter(2, fpol0->GetParameter(0));
      }
      TFitResultPtr ftr = hCelldt[i][0]->Fit(fdecay, "SRB");
      TMatrixDSym cov = ftr->GetCovarianceMatrix();
      double eff = effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i];
      double err = sqrt(cov[0][0]*pow(fdecay->GetParameter(1),2)+cov[1][1]*pow(fdecay->GetParameter(0),2)+2*cov[0][1]*fdecay->GetParameter(0)*fdecay->GetParameter(1))/eff;
      double rate = fdecay->GetParameter(0)*fdecay->GetParameter(1)/eff;
      hCelldt[i][0]->Draw();
      grR1->SetPoint(npt,i, rate);
      grR1->SetPointError(npt,0, err);
      if(alpha_type == 1){
	grR2->SetPoint(npt,i,fdecay->GetParameter(2)*tauBiPo);
	grR2->SetPointError(npt,0,fdecay->GetParError(2)*tauBiPo);
      }
      grth->SetPoint(npt,i,fdecay->GetParameter(1)*log(2)*1000);
      grth->SetPointError(npt,0,fdecay->GetParError(1)*log(2)*1000);
      grchi->SetPoint(npt, i, fdecay->GetChisquare()/double(fdecay->GetNDF()));
      cout<<"Pol0: "<<fpol0->GetParameter(0)<<endl;
      cout<<"chi: "<<fdecay->GetChisquare()<<endl;
      ++npt;
      
    }
    cCelldt->cd(1);
    grR1->Draw("ap");
    grR1->Fit(fpol0);
    if(alpha_type==1){
      cCelldt->cd(2);
      grR2->Draw("ap");
      grR2->Fit(fpol0);
    }
    cCelldt->cd(3);
    grth->Draw("ap");
    grth->Fit(fpol0);
    cCelldt->cd(4);
    grchi->Draw("ap");
    grchi->Fit(fpol0);
    
  }

  cout<<"Alpha candidates: "<<nalpha<<endl;
  cout<<"Prompt beta candidates: "<<nnear<<endl;
  cout<<"Far beta candidates: "<<nfar<<endl;
  cout<<"Near cuts: "<<ncut[0]<<" "<<ncut[1]<<" "<<ncut[2]<<" "<<ncut[3]<<" "<<ncut[4]<<" "<<ncut[5]<<" "<<ncut[6]<<" "<<ncut[7]<<endl;
  delete bp;
  return 0;
  }

