#include <vector>
#include <map>
#include "BP.C"
#include "PROSPECT_Style.cc"
#include <iostream>
#include "TH1D.h"
#include "TVectorD.h"
#include "TChain.h"
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
const double n2f = 1.0/12.0;//ratio of lengths of near to far windows
const double f2n = 12.0;//ratio of lengths of far to near windows
const double tmin = 0.002;//start coincidence window tmin ms away from electron
const int kNcell = ncol * nrow;
const int ExcludeCellArr[31] = {0, 1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 18, 21, 23, 24, 27, 32, 34, 40, 44, 52, 68, 79, 86, 102, 115, 122, 127, 130, 139};

bool isET(int seg){
  return (seg%14 == 13 || seg%14 == 0 || seg >= 140);
}

double FWHM(TH1D *h){
  // h->SetBinContent(0,0);
  // h->SetBinContent(h->GetNbinsX()+1,0);
  // double height = h->GetMaximum()/2.0;//GetBinContent(h->GetNbinsX()/2)/2.0;
  // double fwhm = 0;
  // for(int i=h->GetNbinsX();i>0;--i){
  //   if(h->GetBinContent(i)>=height){
  //     fwhm = h->GetBinLowEdge(i+1);
  //     break;
  //   }
  // }
  // for(int i=1;i<h->GetNbinsX();++i){
  //   if(h->GetBinContent(i)>=height){
  //     fwhm -= h->GetBinLowEdge(i);
  //     break;
  //   }
  // }
  double fwhm = h->GetRMS();
  return fwhm;
}
double GetLiveTime(TChain *ch){
  TIter next(ch->GetListOfFiles());
  TChainElement *element;
  double tlive = 0;
  while((element = (TChainElement*)next())){
    TFile *file = TFile::Open(element->GetTitle());
    tlive += ((TVectorD*)file->Get("runtime"))->Norm1();
  }
  return tlive/3600.0;
}

int BiPoPlotter(bool fiducialize = 0, int alpha_type = 0, bool P2_style = 1){
  //alpha_type = 0, strictly Bi214-->Po214-->Pb210
  //alpha_type = 1, strictly Bi212-->Po212-->Pb208
  //alpha_type = 2, include both
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
  plots.insert(pair<const char*, int>("psd",0));
  plots.insert(pair<const char*, int>("z",1));
  plots.insert(pair<const char*, int>("dt",0));
  plots.insert(pair<const char*, int>("E",0));
  plots.insert(pair<const char*, int>("by_cell",0));
  
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
  double live = GetLiveTime(bp->chain);
  cout<<"Live time: "<<live<<" hours\n";
  
  //Set boundary cut values on energy, psd, z-pos and time
  //-------------------------------------------------------
  double hAE = 1.0, lAE = 0.75, hApsd = 0.32, lApsd = 0.2;//alpha
  double highBE = 5.0, lowBE = 0, hPpsd = 0.26, lPpsd = 0;//beta
  double t_start = 0.01, t_end = 3 * tauBiPo;//prompt window
  double ft_offset = 10 * tauBiPo;//far window time offset
  double ft_start = ft_offset + (t_start * f2n);//start time of far window 
  double ft_end = ft_start + f2n * (t_end - t_start);//far window
  double  ldZ = -200, hdZ = 200, fidZ = fiducialize ? 1000.0 : 448.0;
  if(alpha_type == 1){
    t_start = 2e-4;
    t_end = 6e-3;
    hAE = 1.26;
    lAE = 0.97;
    ft_end = ft_start + f2n * (t_end - t_start);
  }else if(alpha_type == 2){
    t_start = 2e-4;
    hAE = 1.26;
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
      hBPSDvE[i] = new TH2D(Form("hBPSDvE%i",i),Form("%s #beta PSD vs. Energy", title[alpha_type].Data()),200,0,5,200,lPpsd,hPpsd);
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
  TF1 *fdz = new TF1("fdz","[0]*exp(-x*x/(2*pow([1],2)))", ldZ/2.0, hdZ/2.0);
  fdz->SetParName(0,"A");
  fdz->SetParName(1,"#sigma (mm)");
  if(bool(plots["z"] & which_plots)){
    cout<<"Including z plots"<<endl;
    for(int i=0;i<N;++i){
      hAZ[i] = new TH1D(Form("hAZ%i",i),Form("%s #alpha Z-Distribution", title[alpha_type].Data()),200,-1000,1000);
      hAZ[i]->Sumw2();
      hAZ[i]->SetMarkerColor(col[i]);
      hAZ[i]->SetLineColor(col[i]);
      hAdZ[i] = new TH1D(Form("hAdZ%i",i),Form("%s #DeltaZ-Distribution", title[alpha_type].Data()),220,-300,300);
      hAdZ[i]->Sumw2();
      hAdZ[i]->SetMarkerColor(col[i]);
      hAdZ[i]->SetLineColor(col[i]);
    }
  }
  
  //3. Time distribution plot
  TH1D *hABdt[N];
  TCanvas *cdT;
  double lt = alpha_type == 1 ? 0.00066 : t_start;//avoid empty bins that are artifact of analyzer holdoff 
  TF1 *fdt = new TF1("fdt","[0]*pow(2,-x/[1])",lt, t_end);
  fdt->SetParName(0, "N");
  fdt->SetParName(1, "T_{1/2}");
  if(bool(plots["dt"] & which_plots)){
    cout<<"Including dt plots"<<endl;
    for(int i=0;i<N;++i){
      hABdt[i] = new TH1D(Form("hABdt%i",i),Form("%s #alpha-#beta #DeltaT-Distribution", title[alpha_type].Data()),370,0, 1.01*t_end);
      hABdt[i]->Sumw2();
      hABdt[i]->SetMarkerColor(col[i]);
      hABdt[i]->SetLineColor(col[i]);
    }
  }
  
  //4. Alpha and beta energy distribution plots
  TH1D *h_AE[N], *hBE[N];
  TCanvas *cE;
  if(bool(plots["E"] & which_plots)){
    cout<<"Including E plots"<<endl;
    for(int i=0;i<N;++i){
      h_AE[i] = new TH1D(Form("hAE%i",i),Form("%s #alpha Energy Distribution", title[alpha_type].Data()),100,lAE,hAE);
      h_AE[i]->Sumw2();
      h_AE[i]->SetMarkerColor(col[i]);
      h_AE[i]->SetLineColor(col[i]);
      
      hBE[i] = new TH1D(Form("hBE%i",i),Form("%s #beta Energy Distribution", title[alpha_type].Data()),200,0,(alpha_type == 1 ? 3.5 : 5));
      hBE[i]->Sumw2();
      hBE[i]->SetMarkerColor(col[i]);
      hBE[i]->SetLineColor(col[i]);
    }
  }


  //5. By cell plots
  TH1D *hCellAE[kNcell][N], *hCellAPSD[kNcell][N], *hCellBPSD[kNcell][N], *hCelldZ[kNcell][N], *hCellZ[kNcell][N];
  TCanvas *cCellAE,*cCellAdE, *cCellApsd, *cCellBpsd,  *cCelldZ,  *cCellZ, *cCellRate;
  if(bool(plots["by_cell"] & which_plots)){
    cout<<"Including by_cell plots"<<endl;
    for(int i=0;i<N;++i){
      for(int j=0;j<kNcell;++j){
	hCellAE[j][i] = new TH1D(Form("hCellAE[%i][%i]",j,i), Form("hCellAE[%i][%i]",j,i),30, lAE, hAE);
	hCellAE[j][i]->Sumw2();
	hCellAE[j][i]->SetMarkerColor(col[i]);
	hCellAE[j][i]->SetLineColor(col[i]);

	hCellAPSD[j][i] = new TH1D(Form("hCellAPSD[%i][%i]",j,i), Form("hCellAPSD[%i][%i]",j,i),50, lApsd, hApsd);
	hCellAPSD[j][i]->Sumw2();
	hCellAPSD[j][i]->SetMarkerColor(col[i]);
	hCellAPSD[j][i]->SetLineColor(col[i]);

	hCellBPSD[j][i] = new TH1D(Form("hCellBPSD[%i][%i]",j,i), Form("hCellBPSD[%i][%i]",j,i),50, lPpsd, hPpsd);
	hCellBPSD[j][i]->Sumw2();
	hCellBPSD[j][i]->SetMarkerColor(col[i]);
	hCellBPSD[j][i]->SetLineColor(col[i]);

	hCelldZ[j][i] = new TH1D(Form("hCelldZ[%i][%i]",j,i), Form("hCelldZ[%i][%i]",j,i),50,-200, 200);
	hCelldZ[j][i]->Sumw2();
	hCelldZ[j][i]->SetMarkerColor(col[i]);
	hCelldZ[j][i]->SetLineColor(col[i]);

	hCellZ[j][i] = new TH1D(Form("hCellZ[%i][%i]",j,i), Form("hCellZ[%i][%i]",j,i),200,-1000, 1000);
	hCellZ[j][i]->Sumw2();
	hCellZ[j][i]->SetMarkerColor(col[i]);
	hCellZ[j][i]->SetLineColor(col[i]);
      }
    }
  }



  //Loop over tree
  //-------------------------------------------
  Long64_t nEnt = Long64_t(bp->fChain->GetEntries()/10);
  cout<<nEnt<<endl;
  for(Long64_t i=0;i<bp->fChain->GetEntries();++i){
    bp->GetEntry(i);
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
      double dt = bp->at - bp->pt->at(j);
      if(dt > t_start && dt < t_end){
	if(bool(plots["psd"] & which_plots)){
	  hAPSDvZ[0]->Fill(bp->az, bp->aPSD);
	  hBPSDvZ[0]->Fill(bp->az, bp->pPSD->at(j));
	  hAPSDvE[0]->Fill(bp->aE, bp->aPSD);
	  hBPSDvE[0]->Fill(bp->pE->at(j),bp->pPSD->at(j));
	}
	if(bool(plots["z"] & which_plots)){
	  hAZ[0]->Fill(bp->az);
	  hAdZ[0]->Fill(bp->az-bp->pz->at(j));
	}
	if(bool(plots["dt"] & which_plots)){
	  hABdt[0]->Fill(dt);
	}
	if(bool(plots["E"] & which_plots)){
	  h_AE[0]->Fill(bp->aE);
	  hBE[0]->Fill(bp->pEtot->at(j));
	}
	if(bool(plots["by_cell"] & which_plots)){
	  if( bp->pPSD->at(j) > lPpsd && bp->pPSD->at(j) < hPpsd &&
	      fabs(bp->pz->at(j)) < 1000 ){
	    hCellAE[bp->aseg][0]->Fill(bp->aE);
	    hCellAPSD[bp->aseg][0]->Fill(bp->aPSD);
	    hCellBPSD[bp->pseg->at(j)][0]->Fill(bp->pPSD->at(j));
	    hCellZ[bp->aseg][0]->Fill(bp->az);
	    hCelldZ[bp->aseg][0]->Fill(bp->az-bp->pz->at(j));
	  }
	}
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
      double dt = bp->ft->at(j) - bp->at - ft_offset;
      dt *= n2f;
      if(dt > t_start && dt < t_end){
	if(bool(plots["psd"] & which_plots)){
	  hAPSDvZ[1]->Fill(bp->az, bp->aPSD, n2f);
	  hBPSDvZ[1]->Fill(bp->fz->at(j), bp->fPSD->at(j), n2f);
	  hAPSDvE[1]->Fill(bp->aE, bp->aPSD, n2f);
	  hBPSDvE[1]->Fill(bp->fE->at(j),bp->fPSD->at(j),n2f);
	}
	if(bool(plots["z"] & which_plots)){
	  hAZ[1]->Fill(bp->az, n2f);
	  hAdZ[1]->Fill(bp->az-bp->fz->at(j), n2f);
	}
	if(bool(plots["dt"] & which_plots)){
	  hABdt[1]->Fill(dt, n2f);
	}
	if(bool(plots["E"] & which_plots)){
	  h_AE[1]->Fill(bp->aE, n2f);
	  hBE[1]->Fill(bp->fEtot->at(j), n2f);
	}
	if(bool(plots["by_cell"] & which_plots)){
	  if( bp->fPSD->at(j) > lPpsd && bp->fPSD->at(j) < hPpsd &&
	      fabs(bp->fz->at(j)) < 1000 ){
	    hCellAE[bp->aseg][1]->Fill(bp->aE, n2f);
	    hCellAPSD[bp->aseg][1]->Fill(bp->aPSD, n2f);
	    hCellBPSD[bp->fseg->at(j)][1]->Fill(bp->fPSD->at(j), n2f);
	    hCellZ[bp->aseg][1]->Fill(bp->az, n2f);
	    hCelldZ[bp->aseg][1]->Fill(bp->az-bp->fz->at(j), n2f);
	  }
	}
      }
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
    hAPSDvE[0]->Draw("colz");
    gPad->Update();
    hAPSDvE[0]->GetXaxis()->SetTitle("#alpha Energy (MeV)");
    hAPSDvE[0]->GetYaxis()->SetTitle("#alpha PSD");
    hAPSDvE[2] = (TH2D*)hAPSDvE[0]->Clone("hAPSDvE2");
    hAPSDvE[2]->Add(hAPSDvE[1],-1);
    gPad->Update();

    cPSD->cd(2);
    hBPSDvE[0]->Draw("colz");
    gPad->Update();
    hBPSDvE[0]->GetXaxis()->SetTitle("#beta Energy (MeV)");
    hBPSDvE[0]->GetYaxis()->SetTitle("#beta PSD");
    hBPSDvE[2] = (TH2D*)hBPSDvE[0]->Clone("hBPSDvE2");
    hBPSDvE[2]->Add(hBPSDvE[1],-1);

    cPSD->cd(3);
    hAPSDvZ[0]->Draw("colz");
    gPad->Update();
    hAPSDvZ[0]->GetXaxis()->SetTitle("#alpha Z-position (mm)");
    hAPSDvZ[0]->GetYaxis()->SetTitle("#alpha PSD");

    cPSD->cd(4);
    hBPSDvZ[0]->Draw("colz");
    gPad->Update();
    hBPSDvZ[0]->GetXaxis()->SetTitle("#betaZ-position (mm)");
    hBPSDvZ[0]->GetYaxis()->SetTitle("#beta PSD");
    cPSD->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoPSD%i%s.png", alpha_type, fid.Data()));
    
    //cPSDBkSub =  new TCanvas("cPSDBkSub", "cPSDBkSub",0,0,1200,900);
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
    hAZ[2]->SetMarkerColor(col[2]);;
    hAZ[2]->SetLineColor(col[2]);;
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
    fdz->SetParameters(0.7*hAdZ[2]->GetMaximum(), 60);
    hAdZ[2]->Fit(fdz,"r");
    gPad->Update();
    cZ->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoZposition%i%s.png", alpha_type,fid.Data()));
    gStyle->SetOptFit(0);
    gStyle->SetPadLeftMargin(0.1);
    gStyle->SetPadRightMargin(0.07);
    gStyle->SetPadTopMargin(0.06);
    
    TCanvas *cNeutrino1 = new TCanvas("cN1","cN1",0,0,800,700);
    hAZ[2]->SetMarkerColor(kBlue);
    hAZ[2]->SetLineColor(kBlue);
    hAZ[2]->Draw();
    hAZ[2]->GetXaxis()->SetTitle("#alpha z-position (mm)");
    hAZ[2]->GetYaxis()->SetTitle("Counts/mm");
    hAZ[2]->GetXaxis()->SetRangeUser(-900,900);
    hAZ[2]->GetYaxis()->SetTitleOffset(1);
    gPad->Update();
    cNeutrino1->SaveAs(Form("/home/jonesdc/prospect/plots/NeutrinoBiPoZposition%i%s.png", alpha_type,fid.Data()));
   TCanvas *cNeutrino2 = new TCanvas("cN2","cN2",0,0,800,700);
    hAdZ[2]->SetMarkerColor(kBlue);
    hAdZ[2]->SetLineColor(kBlue);
    hAdZ[2]->Draw();
    hAdZ[2]->GetXaxis()->SetTitle("z_{#alpha}-z_{#beta} (mm)");
    hAdZ[2]->GetYaxis()->SetTitle("Counts/mm");
    hAdZ[2]->GetYaxis()->SetTitleOffset(1);
    gPad->Update();
    cNeutrino2->SaveAs(Form("/home/jonesdc/prospect/plots/NeutrinoBiPodZ%i%s.png", alpha_type,fid.Data()));

  }
  //---------------------------------------------


  //3. Time distribution plot
  //---------------------------------------------
  if(bool(plots["dt"] & which_plots)){
    cdT = new TCanvas("cdT", "cdT",0,0,800,600);
    gStyle->SetOptStat(1111);
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
    fdt->SetParameters(hABdt[2]->GetMaximum(), alpha_type == 1 ? 0.0003: 0.164 );
    hABdt[2]->Fit(fdt, "rM");
    TF1* fdt2 = (TF1*)fdt->Clone("fdt2");
    fdt2->SetRange(t_start, t_end);
    fdt2->SetLineStyle(4);
    fdt2->Draw("same");
    gPad->Update();
    TPaveText *ptt = new TPaveText(0.3,0.8,0.6,0.89,"NDC");
    ptt->SetShadowColor(0);
    ptt->SetFillColor(0);
    ptt->SetTextColor(kBlue);
    ptt->AddText("Coincidence");  
    TText *tt = ptt->AddText("Accidental");
    tt->SetTextColor(kMagenta);
    tt = ptt->AddText("Acc-Subtracted");
    tt->SetTextColor(kRed);
    ptt->Draw();
    cdT->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoDeltaTSpectrum%i%s.png", alpha_type, fid.Data()));
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
    h_AE[0]->GetXaxis()->SetTitle("Energy (MeV)");
    h_AE[2] = (TH1D*)h_AE[0]->Clone("h_AE[2]");
    h_AE[2]->Add(h_AE[1],-1);
    h_AE[2]->SetMarkerColor(col[2]);;
    h_AE[2]->SetLineColor(col[2]);;
    h_AE[2]->Fit("gaus");
    h_AE[2]->Draw("sames");
    gPad->Update();
    cE->cd(2);
    hBE[0]->Scale(1/hBE[0]->GetBinWidth(1));
    hBE[1]->Scale(1/hBE[1]->GetBinWidth(1));
    hBE[0]->Draw();
    hBE[1]->Draw("same");
    gPad->Update();
    hBE[0]->GetYaxis()->SetTitle("Counts/MeV");
    hBE[0]->GetXaxis()->SetTitle("Energy (MeV)");
    hBE[2] = (TH1D*)hBE[0]->Clone("hBE[2]");
    hBE[2]->Add(hBE[1],-1);
    hBE[2]->SetMarkerColor(col[2]);;
    hBE[2]->SetLineColor(col[2]);;
    hBE[2]->Draw("same");
    cE->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoEspectra%i%s.png", alpha_type, fid.Data()));
  }
  //---------------------------------------------

  
  //5. By Cell plots
  //---------------------------------------------
  TCanvas *c1;
  if(bool(plots["by_cell"] & which_plots)){
    c1 = new TCanvas("c1","c1",0,0,1600,1000);
    c1->Divide(2,2);
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
    
    //Alpha energy diff from cell 76 (5,6)
    int cseg = 76;
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
    TGraph *gAZW = new TGraph();
    TGraphErrors *gAZ_ET = new TGraphErrors();
    TGraph *gAZW_ET = new TGraph();

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
    int nAE_ET = 0, nApsd_ET = 0, nBpsd_ET = 0, ndZ_ET = 0, nZ_ET = 0;
    double  y76 = 0, y76W = 0;
    for(int i=0;i<kNcell;++i){
      if(exclude_cells)
	if( find(begin(ExcludeCellArr), end(ExcludeCellArr), i)
	    != end(ExcludeCellArr) )
	  continue;
      if(hCellAE[i][0]->GetEntries()>0){//Alpha E
	c1->cd(1);
	hCellAE[i][2] = (TH1D*)hCellAE[i][0]->Clone(Form("hCellAE[%i][2]",i));
	hCellAE[i][2]->Add(hCellAE[i][1],-1);
	double guess = alpha_type == 1 ? 1.12 : 0.89;
	double guessErr = 0.046/sqrt(guess);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",
			 guess-2*guessErr, guess + 2*guessErr);
	f->SetParameters(hCellAE[i][2]->GetMaximum(),guess,0.046/sqrt(guess));
	f->SetRange(lAE, hAE);
	hCellAE[i][2]->Draw();
	gPad->Update();
	hCellAE[i][2]->Fit(f,"rq");
	if(f->GetParameter(2)<0){//deal with negative width
	  f->SetParameter(2,fabs(f->GetParameter(2)));
	  hCellAE[i][2]->Fit(f,"rq"); 
	}
	if(i==76){
	  y76 = f->GetParameter(1);
	  y76W = f->GetParameter(2);
	}
	gAE->SetPoint(nAE, i, f->GetParameter(1));
	gAE->SetPointError(nAE, 0, f->GetParError(1));
	gAEW->SetPoint(nAE, i, f->GetParameter(2));
	gAEW->SetPointError(nAE, 0, f->GetParError(2));
	h_AE->Fill(f->GetParameter(1));
	hAEW->Fill(f->GetParameter(2));
	double lnsig = (f->GetParameter(1) - lAE)/f->GetParameter(2);
	double hnsig = (hAE - f->GetParameter(1))/f->GetParameter(2);
	effAE[i] = (erf(lnsig) + erf(hnsig))/2.0;
	grEffAE->SetPoint(nAE, i, effAE[i]);
	++nAE;
	if(isET(i)){
	  gAE_ET->SetPoint(nAE_ET, i, f->GetParameter(1));
	  gAE_ET->SetPointError(nAE_ET, 0, f->GetParError(1));
	  gAEW_ET->SetPoint(nAE_ET, i, f->GetParameter(2));
	  gAEW_ET->SetPointError(nAE_ET, 0, f->GetParError(2));
	  ++nAE_ET;
	}
	gAE->Fit("pol0");
      }
      
      if(hCellAPSD[i][0]->GetEntries()>0){//Alpha PSD
      	c1->cd(2);
      	hCellAPSD[i][2] = (TH1D*)hCellAPSD[i][0]->Clone(Form("hCellAPSD[%i][2]",i));
      	hCellAPSD[i][2]->Add(hCellAPSD[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0,1);
      	f->SetParameters(hCellAPSD[i][2]->GetMaximum(),0.25,0.017);
      	f->SetRange(lApsd, hApsd);
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
      	effAPSD[i] = (erf(lnsig) + erf(hnsig))/2.0;
	grEffApsd->SetPoint(nApsd, i, effAPSD[i]);
      	++nApsd;
      	if(isET(i)){
      	  gApsd_ET->SetPoint(nApsd_ET, i, f->GetParameter(1));
      	  gApsd_ET->SetPointError(nApsd_ET, 0, f->GetParError(1));
      	  gApsdW_ET->SetPoint(nApsd_ET, i, f->GetParameter(2));
      	  gApsdW_ET->SetPointError(nApsd_ET, 0, f->GetParError(2));
      	  ++nApsd_ET;
      	}
      	gApsd->Fit("pol0");
      }
      
      if(hCellBPSD[i][0]->GetEntries()>0){//beta PSD
      	c1->cd(3);
      	hCellBPSD[i][2] = (TH1D*)hCellBPSD[i][0]->Clone(Form("hCellBPSD[%i][2]",i));
      	hCellBPSD[i][2]->Add(hCellBPSD[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",0.11,0.2);
      	f->SetParameters(hCellBPSD[i][2]->GetMaximum(),0.14,0.012);
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
      	effBPSD[i] = (erf(lnsig) + erf(hnsig))/2.0;
	grEffBpsd->SetPoint(nBpsd, i, effBPSD[i]);
      	++nBpsd;
      	if(isET(i)){
      	  gBpsd_ET->SetPoint(nBpsd_ET, i, f->GetParameter(1));
      	  gBpsd_ET->SetPointError(nBpsd_ET, 0, f->GetParError(1));
      	  gBpsdW_ET->SetPoint(nBpsd_ET, i, f->GetParameter(2));
      	  gBpsdW_ET->SetPointError(nBpsd_ET, 0, f->GetParError(2));
      	  ++nBpsd_ET;
      	}
      	gBpsd->Fit("pol0");
      }
      
      if(hCelldZ[i][0]->GetEntries()>0){//dZ
      	c1->cd(4);
      	hCelldZ[i][2] = (TH1D*)hCelldZ[i][0]->Clone(Form("hCelldZ[%i][2]",i));
      	hCelldZ[i][2]->Add(hCelldZ[i][1],-1);
	TF1 *f = new TF1("f","[0]*exp(-pow(x-[1],2)/(2*pow([2],2)))",-100,100);
      	f->SetParameters(hCelldZ[i][2]->GetMaximum(),0,65);
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
      	double lnsig = (f->GetParameter(1) - ldZ)/f->GetParameter(2);
      	double hnsig = (hdZ - f->GetParameter(1))/f->GetParameter(2);
      	effdZ[i] = (erf(lnsig) + erf(hnsig))/2.0;
 	grEffdZ->SetPoint(ndZ, i, effdZ[i]);
     	++ndZ;
      	if(isET(i)){
      	  gdZ_ET->SetPoint(ndZ_ET, i, f->GetParameter(1));
      	  gdZ_ET->SetPointError(ndZ_ET, 0, f->GetParError(1));
      	  gdZW_ET->SetPoint(ndZ_ET, i, f->GetParameter(2));
      	  gdZW_ET->SetPointError(ndZ_ET, 0, f->GetParError(2));
      	  ++ndZ_ET;
      	}
      	gdZ->Fit("pol0");
      }
      
      if(hCellZ[i][0]->GetEntries()>0){//dZ
      	c1->cd(4);
      	hCellZ[i][2] = (TH1D*)hCellZ[i][0]->Clone(Form("hCellZ[%i][2]",i));
      	hCellZ[i][2]->Add(hCellZ[i][1],-1);
      	hCellZ[i][2]->Draw();
      	gPad->Update();
      	gAZ->SetPoint(nZ, i, hCellZ[i][2]->GetMean());
      	gAZ->SetPointError(nZ, 0, hCellZ[i][2]->GetMeanError());
      	gAZW->SetPoint(nZ, i, FWHM(hCellZ[i][2]));
     	++nZ;
      	if(isET(i)){
      	  gAZ_ET->SetPoint(nZ_ET, i, hCellZ[i][2]->GetMean());
      	  gAZ_ET->SetPointError(nZ_ET, 0, hCellZ[i][2]->GetMeanError());
      	  gAZW_ET->SetPoint(nZ_ET, i, FWHM(hCellZ[i][2]));
      	  ++nZ_ET;
      	}
      	gAZ->Fit("pol0");
      }
       grEff->SetPoint(nEff,i,effAE[i]*effAPSD[i]*effBPSD[i]*effdZ[i]);
      ++nEff;
    }

    //Plot Alpha E
    //-------------------
    cCellAE = new TCanvas("cCellAE","cCellAE",0,0,1600,900);
    cCellAE->Divide(2,2);
  
    cCellAE->cd(1);
    gAE->SetTitle(Form("^{%i}Po Alpha Energy Mean vs Cell",
		       (alpha_type==1?212:214)));
    gAE->SetMarkerColor(kBlue);
    gAE->SetLineColor(kBlue);
    gAE->SetMarkerStyle(8);
    gAE->SetMarkerSize(0.6);
    gAE->Draw("ap");
    gPad->Update();
    TPaveStats *ps = (TPaveStats*)gAE->FindObject("stats");
    ps->SetX1NDC(0.141);
    ps->SetX2NDC(0.49);
    ps->SetY1NDC(0.899);
    ps->SetY2NDC(0.78);
    gAE->GetXaxis()->SetTitle("Cell Number");
    gAE->GetYaxis()->SetTitle("Alpha Energy (MeV)");
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
    gAEW->Fit("pol0");
    gPad->Update();
    TPaveStats *ps1 = (TPaveStats*)gAEW->FindObject("stats");
    ps1->SetX1NDC(0.141);
    ps1->SetX2NDC(0.49);
    ps1->SetY1NDC(0.899);
    ps1->SetY2NDC(0.78);
  
    gAEW->GetXaxis()->SetTitle("Cell Number");
    gAEW->GetYaxis()->SetTitle("Alpha Energy Width (MeV)");
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
    hAEW->GetXaxis()->SetTitle("Alpha Energy Width (MeV)");
    gPad->Update();
    cCellAE->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoAlphaEvsCell%i%s.png", alpha_type, fid.Data()));
    //-------------------

    
    //Plot Alpha E relative to center segment 76
    //-------------------------------------------
    cCellAdE = new TCanvas("cCellAdE","cCellAdE",0,0,1600,600);
    cCellAdE->Divide(2,1);
  
    cCellAdE->cd(1);
    for(int i=0;i<gAE->GetN();++i){
      double x=0, y=0;
      gAE->GetPoint(i, x, y);
      gAdE->SetPoint(i, x, (y-y76)*1000);
      gAdE->SetPointError(i, 0, gAE->GetErrorY(i)*1000);
      gAEW->GetPoint(i, x, y);
      gAdEW->SetPoint(i, x, (y-y76W)*1000);
      gAdEW->SetPointError(i, 0, gAEW->GetErrorY(i)*1000);
    }

    for(int i=0;i<gAE_ET->GetN();++i){
      double x=0, y=0;
      gAE_ET->GetPoint(i, x, y);
      gAdE_ET->SetPoint(i, x, (y-y76)*1000);
      gAdE_ET->SetPointError(i, 0, gAE_ET->GetErrorY(i)*1000);
      gAEW_ET->GetPoint(i, x, y);
      gAdEW_ET->SetPoint(i, x, (y-y76W)*1000);
      gAdEW_ET->SetPointError(i, 0, gAEW_ET->GetErrorY(i)*1000);
    }
    gAdE->SetTitle(Form("^{%i}Po Alpha Energy Mean Relative to Cell 76 "
			"(%0.2f MeV)", (alpha_type==1? 212 : 214), y76));
    gAdE->SetMarkerColor(kBlue);
    gAdE->SetLineColor(kBlue);
    gAdE->SetMarkerStyle(8);
    gAdE->SetMarkerSize(0.6);
    gAdE->Draw("ap");
    gAdE->Fit("pol0");
    gPad->Update();
    ps = (TPaveStats*)gAdE->FindObject("stats");
    ps->SetX1NDC(0.141);
    ps->SetX2NDC(0.49);
    ps->SetY1NDC(0.899);
    ps->SetY2NDC(0.78);
    gAdE->GetXaxis()->SetTitle("Cell Number");
    gAdE->GetYaxis()->SetTitle("#DeltaE (keV)");
    gAdE_ET->SetMarkerColor(kRed);
    gAdE_ET->SetLineColor(kRed);
    gAdE_ET->SetMarkerStyle(8);
    gAdE_ET->SetMarkerSize(0.6);
    gAdE_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellAdE->cd(2);
    gAdEW->SetTitle(Form("^{%i}Po Alpha Energy Width Relative to Cell 76 "
			 "(%0.2f MeV)",(alpha_type==1 ? 212 : 214), y76));
    gAdEW->SetMarkerColor(kBlue);
    gAdEW->SetLineColor(kBlue);
    gAdEW->SetMarkerStyle(8);
    gAdEW->SetMarkerSize(0.6);
    gAdEW->Draw("ap");
    gAdEW->Fit("pol0");
    gPad->Update();
    ps1 = (TPaveStats*)gAdEW->FindObject("stats");
    ps1->SetX1NDC(0.141);
    ps1->SetX2NDC(0.49);
    ps1->SetY1NDC(0.899);
    ps1->SetY2NDC(0.78);
  
    gAdEW->GetXaxis()->SetTitle("Cell Number");
    gAdEW->GetYaxis()->SetTitle("#Delta#sigma (keV)");
    gAdEW_ET->SetMarkerColor(kRed);
    gAdEW_ET->SetLineColor(kRed);
    gAdEW_ET->SetMarkerStyle(8);
    gAdEW_ET->SetMarkerSize(0.6);
    gAdEW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellAdE->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoAlphadEvsCell%i%s.png", alpha_type, fid.Data()));
    //-------------------
    

    //Plot Alpha PSD
    //-------------------
    cCellApsd = new TCanvas("cCellApsd","cCellApsd",0,0,1600,900);
    cCellApsd->Divide(2,2);
  
    cCellApsd->cd(1);
    gApsd->SetTitle(Form("^{%i}Po Alpha PSD Mean vs Cell",
		       (alpha_type==1 ? 212 : 214)));
    gApsd->SetMarkerColor(kBlue);
    gApsd->SetLineColor(kBlue);
    gApsd->SetMarkerStyle(8);
    gApsd->SetMarkerSize(0.6);
    gApsd->Draw("ap");
    gPad->Update();
    ps = (TPaveStats*)gApsd->FindObject("stats");
    ps->SetX1NDC(0.141);
    ps->SetX2NDC(0.49);
    ps->SetY1NDC(0.899);
    ps->SetY2NDC(0.78);
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
    gApsdW->Fit("pol0");
    gPad->Update();
    ps1 = (TPaveStats*)gApsdW->FindObject("stats");
    ps1->SetX1NDC(0.141);
    ps1->SetX2NDC(0.49);
    ps1->SetY1NDC(0.899);
    ps1->SetY2NDC(0.78);
  
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
    cCellApsd->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoAlphaPSDvsCell%i%s.png", alpha_type, fid.Data()));
    //-------------------
    

    //Plot Beta PSD
    //-------------------
    cCellBpsd = new TCanvas("cCellBpsd","cCellBpsd",0,0,1600,900);
    cCellBpsd->Divide(2,2);
  
    cCellBpsd->cd(1);
    gBpsd->SetTitle(Form("^{%i}Bi Beta PSD Mean vs Cell",
			 (alpha_type==1 ? 212 : 214)));
    gBpsd->SetMarkerColor(kBlue);
    gBpsd->SetLineColor(kBlue);
    gBpsd->SetMarkerStyle(8);
    gBpsd->SetMarkerSize(0.6);
    gBpsd->Draw("ap");
    gPad->Update();
    ps = (TPaveStats*)gBpsd->FindObject("stats");
    ps->SetX1NDC(0.141);
    ps->SetX2NDC(0.49);
    ps->SetY1NDC(0.899);
    ps->SetY2NDC(0.78);
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
    gBpsdW->Fit("pol0");
    gPad->Update();
    ps1 = (TPaveStats*)gBpsdW->FindObject("stats");
    ps1->SetX1NDC(0.141);
    ps1->SetX2NDC(0.49);
    ps1->SetY1NDC(0.899);
    ps1->SetY2NDC(0.78);
  
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
    cCellBpsd->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoBetaPSDvsCell%i%s.png", alpha_type, fid.Data()));


    //Plot dZ
    //-------------------
    cCelldZ = new TCanvas("cCelldZ","cCelldZ",0,0,1600,900);
    cCelldZ->Divide(2,2);
  
    cCelldZ->cd(1);
    gdZ->SetTitle("Alpha-Beta dZ Mean vs Cell");
    gdZ->SetMarkerColor(kBlue);
    gdZ->SetLineColor(kBlue);
    gdZ->SetMarkerStyle(8);
    gdZ->SetMarkerSize(0.6);
    gdZ->Draw("ap");
    gPad->Update();
    ps = (TPaveStats*)gdZ->FindObject("stats");
    ps->SetX1NDC(0.141);
    ps->SetX2NDC(0.49);
    ps->SetY1NDC(0.899);
    ps->SetY2NDC(0.78);
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
    gdZW->Fit("pol0");
    gPad->Update();
    ps1 = (TPaveStats*)gdZW->FindObject("stats");
    ps1->SetX1NDC(0.141);
    ps1->SetX2NDC(0.49);
    ps1->SetY1NDC(0.899);
    ps1->SetY2NDC(0.78);
  
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
    cCelldZ->SaveAs(Form("/home/jonesdc/prospect/plots/BiPodZvsCell%i%s.png", alpha_type, fid.Data()));
    //-------------------



    //Plot dZ
    //-------------------
    cCellZ = new TCanvas("cCellZ","cCellZ",0,0,1400,600);
    cCellZ->Divide(2,1);
  
    cCellZ->cd(1);
    gAZ->SetTitle("Alpha Z-distribution Mean vs Cell");
    gAZ->SetMarkerColor(kBlue);
    gAZ->SetLineColor(kBlue);
    gAZ->SetMarkerStyle(8);
    gAZ->SetMarkerSize(0.6);
    gAZ->Draw("ap");
    gPad->Update();
    ps = (TPaveStats*)gAZ->FindObject("stats");
    ps->SetX1NDC(0.141);
    ps->SetX2NDC(0.49);
    ps->SetY1NDC(0.899);
    ps->SetY2NDC(0.78);
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
    gAZW->Fit("pol0");
    gPad->Update();
    ps1 = (TPaveStats*)gAZW->FindObject("stats");
    ps1->SetX1NDC(0.141);
    ps1->SetX2NDC(0.49);
    ps1->SetY1NDC(0.899);
    ps1->SetY2NDC(0.78);
  
    gAZW->GetXaxis()->SetTitle("Cell Number");
    gAZW->GetYaxis()->SetTitle("Alpha Z RMS (mm)");
    gAZW_ET->SetMarkerColor(kRed);
    gAZW_ET->SetLineColor(kRed);
    gAZW_ET->SetMarkerStyle(8);
    gAZW_ET->SetMarkerSize(0.6);
    gAZW_ET->Draw("samep");
    pt->Draw();
    gPad->Update();
    cCellZ->SaveAs(Form("/home/jonesdc/prospect/plots/BiPoZvsCell%i%s.png", alpha_type, fid.Data()));
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
    for(int i=0;i<kNcell;++i){
      if(exclude_cells)
	if( find(begin(ExcludeCellArr), end(ExcludeCellArr), i)
	    != end(ExcludeCellArr) )
	  continue;
      if(hCellAE[i][2]->GetEntries()>0){
	double err;
	double rate = double(hCellAE[i][2]->IntegralAndError(0,hCellAE[i][2]->GetNbinsX(), err))/live;
	err /= live;
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
    grRate->GetYaxis()->SetTitle("BiPo Rate (Counts/hr)");
    grRate->GetXaxis()->SetTitle("Cell Number");
    grRate->Fit("pol1");
    gPad->Update();
    ps = (TPaveStats*)grRate->FindObject("stats");
    ps->SetX1NDC(0.18);
    ps->SetX2NDC(0.6);
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
    grRateEffC->GetYaxis()->SetTitle("BiPo Rate (Counts/hr)");
    grRateEffC->GetXaxis()->SetTitle("Cell Number");
    grRateEffC->Fit("pol1");
    gPad->Update();
    ps = (TPaveStats*)grRateEffC->FindObject("stats");
    ps->SetX1NDC(0.18);
    ps->SetX2NDC(0.6);
    gPad->Update();
    if(!fiducialize)
      pt->Draw();

    cCellRate->cd(4)->SetRightMargin(0.14);
    hHeat->Draw("colz");
    gPad->Update();
    hHeat->SetTitle("Efficiency Corrected BiPo Rate by Cell");
    hHeat->SetTitleOffset(0.1);
    hHeat->GetYaxis()->SetTitle("Row Number");
    hHeat->GetXaxis()->SetTitle("Column Number");
    hHeat->GetXaxis()->SetTitleOffset(1.0);
    hHeat->GetZaxis()->SetTitle("Count Rate (/hr)");
    hHeat->GetZaxis()->SetRangeUser(hHeat->GetMaximum()*0.6,hHeat->GetMaximum());
    gPad->Update();
    cCellRate->SaveAs(Form("/home/jonesdc/prospect/plots/BiPRatevsCell%i%s.png", alpha_type, fid.Data()));
    if(1){
      gStyle->SetPadRightMargin(0.1);
      gStyle->SetOptStat(0);
      gStyle->SetOptFit(0);
      TCanvas *c5 = new TCanvas("c5","c5",0,0,800,600);
      TGraphErrors *grEsc = new TGraphErrors();
      TF1 *f5 = new TF1("f5","pol0",0,1);
      gAE->Fit(f5);
      double norm = f5->GetParameter(0);
      double x, y;
      for(int i=0;i<gAE->GetN();++i){
	gAE->GetPoint(i, x, y);
	grEsc->SetPoint(i, x, y/norm);
	grEsc->SetPointError(i, gAE->GetErrorX(i), gAE->GetErrorY(i)/norm);
      }
      grEsc->Fit("pol0");
      grEsc->SetTitle(gAE->GetTitle());
      grEsc->SetMarkerColor(kBlue);
      grEsc->SetMarkerStyle(8);
      grEsc->SetMarkerSize(0.8);
      grEsc->SetLineColor(kBlue);
      grEsc->Draw("ap");
      grEsc->GetXaxis()->SetTitle(gAE->GetXaxis()->GetTitle());
      grEsc->GetYaxis()->SetTitle(gAE->GetYaxis()->GetTitle());
      gPad->Update();      
      c5->SaveAs(Form("/home/jonesdc/prospect/plots/EscBiPoEvsCell%i%s.pdf", alpha_type, fid.Data()));
      gStyle->SetPadRightMargin(0.04);
      gStyle->SetPadLeftMargin(0.06);
      TCanvas *c6 = new TCanvas("c6","c6",0,0,1200,300);
      grEsc->SetMarkerStyle(kCircle);
      grEsc->GetYaxis()->SetTitleOffset(0.6);
      grEsc->Draw("ap");
      TFile f("BiPoNeutrino.root","update","bipo");
      grEsc->Write(Form("Po%iEvsCell%s",(alpha_type == 1 ? 212: 214), fid.Data()));
      f.Close();
    }
  }
  if(0){
    TCanvas *c0 = new TCanvas("c0","c0",0,0,700,500);
    gStyle->SetPadRightMargin(0.1);
    gStyle->SetOptStat(0);
    hAPSDvE[2]->SetTitle("BiPo #alpha PSD vs. Energy");
    hAPSDvE[2]->GetXaxis()->SetTitleSize(0.04);
    hAPSDvE[2]->GetYaxis()->SetTitleSize(0.04);
    hAPSDvE[2]->Draw("colz");

    TCanvas *c2 = new TCanvas("c2","c2",0,0,700,500);
    hBPSDvE[2]->SetTitle("BiPo #beta PSD vs. Energy");
    hBPSDvE[2]->GetXaxis()->SetTitleSize(0.04);
    hBPSDvE[2]->GetYaxis()->SetTitleSize(0.04);
    hBPSDvE[2]->Draw("colz");

    TCanvas *c3 = new TCanvas("c3","c3",0,0,700,500);
    hAdZ[2]->SetTitle("BiPo #alpha - #beta dZ Distribution");
    hAdZ[2]->GetXaxis()->SetTitle("dZ (mm)");
    hAdZ[2]->GetXaxis()->SetTitleSize(0.04);
    hAdZ[2]->GetYaxis()->SetTitleSize(0.04);
    hAdZ[2]->Draw();
  

    gStyle->SetOptStat(0);
    TCanvas *c4 = new TCanvas("c4","c4",0,0,700,500);
    hABdt[2]->Draw();
    hABdt[2]->GetXaxis()->SetTitle("dt (ms)");
    hABdt[2]->GetXaxis()->SetTitleSize(0.04);
    hABdt[2]->GetYaxis()->SetTitleSize(0.04);
  }


  delete bp;
  return 0;
}
