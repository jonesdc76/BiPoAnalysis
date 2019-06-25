#include "TChain.h"
#include "TGraph.h"
#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include "BPsim.C"
#include <iostream>
double GetChiSq(int lbin, int hbin, TH1D *h, TH1D *hsim){
  double chsq = 0, ndf=0;
  for(int i=lbin;i<=hbin;++i){
    double x = h->GetBinContent(i);
    double xs = hsim->GetBinContent(i);
    if(x!=0){
      double xe = h->GetBinError(i);
      double xse = hsim->GetBinError(i);
      chsq += pow(x-xs, 2) / (xe*xe+xse*xse);
      ++ndf;
    }else{
      cout<<"Bin "<<i<<" not included in minimization. "<<x<<" "<<xs<<endl;
    }
  }
  return chsq/ndf;
}

//////////////////////////////////////////////////////////////////////
//Optimizes simulated beta spectrum compared to data by scaling energy
//////////////////////////////////////////////////////////////////////
int SimScaledCompare(){
  const int lBIN = 11, hBIN = 100;
  BPsim *bps = new BPsim();
  TChain *ch = bps->chain;
  gStyle->SetPadLeftMargin(0.11);
  gStyle->SetPadRightMargin(0.15);
  TCanvas *c1 = new TCanvas("c1","c1",0,0,850,600);
  gStyle->SetOptStat(0);
  c1->cd(1)->SetGrid();
  TF1 *f = new TF1("f","pol0",0.48,4);
  TGraph *gr = new TGraph();
  const int N=40;
  TH1D *h[N*3];
  const double SCALE = 0.996;
  double scale = 1, norm = SCALE, step1 = 0.0001, step2 = 0.00025;
  double res = 1e100, res2 = 1e100, min_scale, min_norm, min_norm2;
  int minidx = 0, minidx2 = 0;
  TFile *file = new TFile("BiPoPublicationPlots.root");
  TH1D *hBE = (TH1D*)file->Get("hBE[2]_214");
  TH1D *hBE76 = (TH1D*)file->Get("hCellBE[76][2]_214");
  hBE->Sumw2();
  hBE->Scale(1/hBE->Integral(lBIN,hBIN));
  TH1D *hminres, *hminres2;
  TH2D *h2d = new TH2D("","",N*3,scale,scale+3*N*step1,N,norm,norm+N*step2);
  for(int i=0;i<N*3;++i){
    ch->Draw(Form("pEtot*%f>>h%i(100,0,4)",scale,i),"","goff");
    h[i] = (TH1D*)gDirectory->Get(Form("h%i",i));
    h[i]->Sumw2();
    h[i]->SetLineWidth(2);
    h[i]->Scale(1/h[i]->Integral(lBIN,hBIN));
    norm = SCALE;
    for(int k=0;k<N;++k){
      TH1D *hx = (TH1D*)h[i]->Clone("hx");
      hx->Scale(norm);
      double chsq = GetChiSq(lBIN,hBIN,hBE,hx);
      if(chsq < res){
	min_norm = norm;
	min_scale = scale;
	minidx = i;
	hminres = (TH1D*)hBE->Clone("hRes");
	hminres->Add(hx, -1);
	//hminres->Divide(hx);
	res = chsq;
      }
      if(scale == 1.0 && chsq < res2){
	min_norm2 = norm;
	minidx2 = i;
	hminres2 = (TH1D*)hBE->Clone("hRes");
	hminres2->Add(hx, -1);
	//hres->Divide(hx);
	res2 = chsq;
      }
      h2d->Fill(scale+0.0000001,norm+0.0000001, chsq);
      norm += step2;
      cout<<norm<<" "<<scale<<" "<<chsq<<endl;
    }
    scale += step1;
  }
  h2d->Draw("colz");
  h2d->SetTitle("#chi^{2} vs. Relative Normalization and Energy Scale;Energy Scale;Spectrum Normalization(a.u.);#chi^{2}/bin");
  gPad->Update();
  h2d->GetYaxis()->SetTitleOffset(1.4);

  TCanvas *c2 = new TCanvas("c2","c2",0,0,1600,600);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 0.5, 1.0);
  pad1->SetRightMargin(0.05);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetGridx();

  TPaveText *pt = new TPaveText(0.66,0.8,0.94,0.89,"ndc");
  pt->SetFillColor(0);
  pt->SetShadowColor(0);
  pt->SetBorderSize(0);
  pt->AddText("Simulation scaled to data");
  pt->AddText(Form("Energy scale factor: %0.4f", min_scale));
  h[minidx]->Draw();
  pt->Draw();
  h[minidx]->SetTitle("Scaled Bi-214 #beta Spectrum;Energy (Mev);Rate (mHz/MeV)");
  h[minidx]->SetLineColor(kGreen+2);
  h[minidx]->GetYaxis()->SetLimits(-0.001,0.024);
  h[minidx]->GetYaxis()->SetRangeUser(-0.001,0.024);
  hBE->SetLineColor(kBlue);
  hBE->Draw("same");
  h[minidx]->GetYaxis()->SetTitleSize(0.04);
  h[minidx]->GetYaxis()->SetTitleOffset(1.1);
  h[minidx]->GetYaxis()->SetLabelSize(0.0);
  gPad->Update();
  TGaxis *axis = new TGaxis(0,0.00,0,0.022,0.00,0.022,510,"");
  axis->SetLabelFont(43); 
  axis->SetLabelSize(15);
  axis->Draw();

  c2->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.005, 0.5, 0.3);
  pad2->SetRightMargin(0.05);
  pad2->SetTopMargin(0);
  pad2->SetGridx();
  TLine line(0,0,0,4);
  line.SetLineStyle(1);
  pad2->SetBottomMargin(0.27);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  hminres->SetLineColor(kBlack);
  hminres->Draw();
  //  hminres->SetTitle("Bi-214 #beta Spectrum Residual (Data-Sim);Energy (Mev);Rate (mHz/MeV)");
  gPad->Update();
  hminres->SetTitle("");
  hminres->GetXaxis()->SetTitle("Energy (Mev)");
  hminres->GetYaxis()->SetTitle("Residual (mHz/MeV)");
  //hminres->GetYaxis()->SetTitle("Ratio (Data/MC)");
  TF1 *fpol0 = new TF1("fpol0","pol0",hminres->GetBinLowEdge(lBIN),4);
  fpol0->SetLineColor(kBlack);
  hminres->Fit("fpol0","r");
  TPaveText *pt2 = new TPaveText(0.77,0.77,0.94,0.99,"ndc");
  pt2->SetFillColor(0);
  pt2->SetShadowColor(0);
  pt2->SetBorderSize(0);
  pt2->AddText(Form("#chi^{2}/NDF: %0.1f/%i", fpol0->GetChisquare(),fpol0->GetNDF()));
  pt2->AddText(Form("%0.5f#pm%0.5f", fpol0->GetParameter(0),fpol0->GetParError(0)));
  pt2->Draw();
  line.Draw();
  // Y axis ratio plot settings
  hminres->GetYaxis()->SetRangeUser(-0.0014,0.0014);
  hminres->GetYaxis()->SetNdivisions(505);
  hminres->GetYaxis()->SetTitleSize(16);
  hminres->GetYaxis()->SetTitleFont(43);
  hminres->GetYaxis()->SetTitleOffset(1.4);
  hminres->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  hminres->GetYaxis()->SetLabelSize(15);
  
  // X axis ratio plot settings
  hminres->GetXaxis()->SetNdivisions(510);
  hminres->GetXaxis()->SetTitleSize(22);
  hminres->GetXaxis()->SetTitleFont(43);
  hminres->GetXaxis()->SetTitleOffset(3.2);
  hminres->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  hminres->GetXaxis()->SetLabelSize(18);

  c2->cd();          // Go back to the main canvas before defining pad2  
  TPad *pad12 = new TPad("pad12", "pad12", 0.5, 0.3, 1, 1.0);
  pad12->SetRightMargin(0.05);
  pad12->SetBottomMargin(0); // Upper and lower plot are joined
  pad12->Draw();             // Draw the upper pad: pad1
  pad12->cd();               // pad1 becomes the current pad
  pad12->SetGridx();
  h[minidx2]->Draw();
  h[minidx2]->SetTitle("Bi-214 #beta Spectrum;Energy (Mev);Rate (mHz/MeV)");
  h[minidx2]->SetLineColor(kGreen+2);
  h[minidx2]->GetYaxis()->SetLimits(-0.001,0.024);
  h[minidx2]->GetYaxis()->SetRangeUser(-0.001,0.024);
  h[minidx2]->GetYaxis()->SetLabelSize(0.0);
  gPad->Update();
  hBE->Draw("same");
  h[minidx2]->GetYaxis()->SetTitleSize(0.04);
  h[minidx2]->GetYaxis()->SetTitleOffset(1.4);
  h[minidx2]->GetYaxis()->SetLabelSize(0.);
  axis->Draw();

  c2->cd();          // Go back to the main canvas before defining pad2
  TPad *pad22 = new TPad("pad22", "pad22", 0.5, 0.005, 1, 0.3);
  pad22->SetTopMargin(0);
  pad22->SetGridx();
  pad22->SetRightMargin(0.05);
  pad22->SetBottomMargin(0.27);
  pad22->Draw();
  pad22->cd();       // pad2 becomes the current pad

  hminres2->SetLineColor(kBlack);
  hminres2->Draw();
  //  hminres2->SetTitle("Bi-214 #beta Spectrum Residual (Data-Sim);Energy (Mev);Rate (mHz/MeV)");
  gPad->Update();
  hminres2->SetTitle("");
  hminres2->GetXaxis()->SetTitle("Energy (Mev)");
  hminres2->GetYaxis()->SetTitle("Residual (mHz/MeV)");
  //hminres->GetYaxis()->SetTitle("Ratio (Data/MC)");
  hminres2->Fit("fpol0","r");
  TPaveText *pt22 = new TPaveText(0.77,0.77,0.94,0.99,"ndc");
  pt22->SetFillColor(0);
  pt22->SetShadowColor(0);
  pt22->SetBorderSize(0);
  pt22->AddText(Form("#chi^{2}/NDF: %0.1f/%i", fpol0->GetChisquare(),fpol0->GetNDF()));
  pt22->AddText(Form("%0.5f#pm%0.5f", fpol0->GetParameter(0),fpol0->GetParError(0)));
  pt22->Draw();
  // Y axis ratio plot settings
  hminres2->GetYaxis()->SetRangeUser(-0.0014,0.0014);
  hminres2->GetYaxis()->SetNdivisions(505);
  hminres2->GetYaxis()->SetTitleSize(16);
  hminres2->GetYaxis()->SetTitleFont(43);
  hminres2->GetYaxis()->SetTitleOffset(1.2);
  hminres2->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  hminres2->GetYaxis()->SetLabelSize(15);
  
  // X axis ratio plot settings
  hminres2->GetXaxis()->SetNdivisions(510);
  hminres2->GetXaxis()->SetTitleSize(22);
  hminres2->GetXaxis()->SetTitleFont(43);
  hminres2->GetXaxis()->SetTitleOffset(3.2);
  hminres2->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  hminres2->GetXaxis()->SetLabelSize(18);
  c1->SaveAs(Form("%s/Bi214BetaSpectrumChisq.pdf",gSystem->Getenv("TECHNOTE")));
  c2->SaveAs(Form("%s/Bi214BetaSpectrumDataMC.pdf",gSystem->Getenv("TECHNOTE")));
  cout<<"Energy spectrum included in minimization from "<<hminres->GetBinLowEdge(lBIN)<<" to "<<hminres->GetBinLowEdge(hBIN+1)<<" MeV\n";
  return 0;
}
