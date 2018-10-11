#include "IBDoff.C"
#include "IBDon.C"
#include "TStyle.h"
#include "TCut.h"
#include "TF1.h"
#include "TChain.h"

int checkPSD(){
  gStyle->SetOptStat(0);
  IBDon *on = new IBDon();
  IBDoff *off = new IBDoff();
  TChain *chon = on->chain;
  TChain *choff = off->chain;
  const double tlow = 1e3, thigh = 120e3, tlowacc = 2e6, thighacc = 12e6;
  const double n2f = 0.0119;//ratio of lengths of near to far windows
  const double f2n = 1.0e4/119.0;//ratio of lengths of far to near windows
  const double tmin = 0.001;//start coincidence window tmin ms away from electron
  const double lowE = 0, highE = 8, EBW=0.2, highEncapt = 0.6;
  int col[3] = {kBlue, kBlack, kGreen+2};
  TCut cut = Form("ncapt_dt>%f&&ncapt_dt<%f&&E>%f&&E<%f&&Encapt<%f", tlow, thigh, lowE, highE, highEncapt);
  TCut cutacc = Form("fabs(ncapt_dt)>%f&&fabs(ncapt_dt)<%f&&E>%f&&E<%f&&Encapt<%f",tlowacc,thighacc, lowE, highE, highEncapt);
  TCanvas *c = new TCanvas("c","c",0,0,1400,600);
  c->Divide(2,1);
  c->cd(1);
  choff->Draw("prompt_psd:E>>hoff(200,0,8,200,0,0.6)", cut, "colz");
  TH1D* hoff = (TH1D*)gDirectory->Get("hoff");
  hoff->SetTitle("Prompt IBD PSD vs Energy");
  gPad->Update();
  c->cd(2);
  choff->Draw("ncapt_psd:Encapt>>hoff2(200,0,8,200,0,0.6)", cut, "colz");
  TH1D* hoff2 = (TH1D*)gDirectory->Get("hoff2");
  hoff2->SetTitle("Delayed IBD PSD vs Energy");

  TCanvas *c1 = new TCanvas("c1","c1",0,0,1400,600);
  c1->Divide(2,1);
  c1->cd(1);
  choff->Draw("xyz[2]>>hz(38,-462,462)",cut&&"E>2&&E<2.4");
  TH1D* hz = (TH1D*)gDirectory->Get("hz");
  hz->Sumw2();
  hz->SetLineColor(kRed);
  choff->Draw("xyz[2]>>hzacc(38,-462,462)",cutacc&&"E>2&&E<2.4","goff");
  TH1D* hzacc = (TH1D*)gDirectory->Get("hzacc");
  hzacc->SetLineColor(kMagenta);
  hzacc->Sumw2();
  hzacc->Scale(n2f);
  hzacc->Draw("same");
  TH1D *hdiffz = (TH1D*)hz->Clone("hdiffz");
  hdiffz->SetLineColor(kBlue);
  hdiffz->SetMarkerColor(kBlue);
  hdiffz->Add(hzacc,-1);
  hdiffz->Draw("same");
  
  c1->cd(2);
  choff->Draw("n_xyz[2]>>hnz(38,-462,462)",cut&&"E>2&&E<2.4");
  TH1D* hnz = (TH1D*)gDirectory->Get("hnz");
  hnz->Sumw2();
  hnz->SetLineColor(kRed);
  choff->Draw("n_xyz[2]>>hnzacc(38,-462,462)",cutacc&&"E>2&&E<2.4","goff");
  TH1D* hnzacc = (TH1D*)gDirectory->Get("hnzacc");
  hnzacc->SetLineColor(kMagenta);
  hnzacc->Sumw2();
  hnzacc->Scale(n2f);
  hnzacc->Draw("same");
  TH1D *hndiffz = (TH1D*)hnz->Clone("hndiffz");
  hndiffz->SetLineColor(kBlue);
  hndiffz->SetMarkerColor(kBlue);
  hndiffz->Add(hzacc,-1);
  hndiffz->Draw("same");

  gStyle->SetOptFit(1111);

  
  TCanvas *c2 = new TCanvas("c2","c2",0,0,1400,600);
  c2->Divide(2,1);
  c2->cd(1);
  double El = 2.0, Eh = 2.6;
  choff->Draw("ncapt_dt/1000.0>>hdt(125,0,125)", Form("E>%f&&E<%f",El,Eh));
  TH1D *hdt = (TH1D*)gDirectory->Get("hdt");
  hdt->Sumw2();
  hdt->SetLineColor(kRed);
  hdt->SetTitle(Form("Rx Off IBD Prompt/Delay #Deltat Peak Region (E>%0.2f, E<%0.2f)", El,Eh));
  gPad->Update();
  hdt->GetXaxis()->SetTitle("#Deltat (#mus)");
  hdt->GetYaxis()->SetTitle("Counts");
  choff->Draw(Form("(fabs(ncapt_dt)-%0.12e)*%0.12e+1>>hdtacc(125,0,125)",tlowacc,n2f/1000), Form("E>%f&&E<%f&&fabs(ncapt_dt)>%f&&fabs(ncapt_dt)<%f",El,Eh,tlowacc,thighacc),"goff");
  TH1D *hdtacc = (TH1D*)gDirectory->Get("hdtacc");
  hdtacc->Sumw2();
  hdtacc->Scale(n2f);
  hdtacc->SetLineColor(kMagenta);
  hdtacc->SetTitle(Form("Accidental Rx Off IBD Prompt/Delay #Deltat Peak Region (E>%0.2f, E<%0.2f)", El,Eh));
  hdtacc->Draw("same");
  TH1D *hdiffdt = (TH1D*)hdt->Clone("hdiffdt");
  hdiffdt->SetLineColor(kBlue);
  hdiffdt->Add(hdtacc,-1);
  hdiffdt->Draw("same");
  TF1 *f = new TF1("f","[0]*exp(-x/[1])",1,98);
  f->SetParNames("Amplitude","#tau");
  f->SetParameters(100,50);
  hdiffdt->Fit(f,"r");
  gPad->Update();
  c2->cd(2);
  hdiffdt->Draw();
  gPad->Update();
  TH1D *hdiffdt1 = (TH1D*)hdiffdt->Clone("hdiffdt1");
  hdiffdt1->SetTitle(Form("Rx Off IBD Prompt/Delay #Deltat Peak Region (E>%0.2f, E<%0.2f)", El,Eh));
  hdiffdt1->GetXaxis()->SetTitle("#Deltat (#mus)");
  hdiffdt1->GetYaxis()->SetTitle("Counts");
  TF1 *f1 = new TF1("f1","[0]+[1]*exp(-x/[2])+[2]",1,98);
  f1->SetParNames("Constant","Amplitude","#tau");
  f1->SetParameters(10,100,50);
  hdiffdt1->Fit(f1,"r");
  return 0;
}
