{
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetLineWidth(2);
  gStyle->SetOptStat(0);
  TChain *ch1 = new TChain("P2kIBDPlugin/Tibd");
  TChain *ch2 = new TChain("P2kIBDPlugin/Tibd");
  TString pass = "";
  ifstream file("RunList.txt");
  int n1 = 0, n2 = 0;
  double lt1 = 0, lt2 = 0;
  while(file.good()&&!file.eof()){
  string line;
    getline(file,line);
    TString rel("Analyzed_NuFact_v1");
    // if(TString(line).Contains("180605_Background")){
    //   rel = "Phys_20180605";
    // }else if(TString(line).Contains("180525_Background")&&
    // 	     (TString(line).Contains("series000/s000_f0011") || 
    // 	      TString(line).Contains("series000/s000_f0012"))){
    //   rel = "Phys_20180605";
    // }
    if(TString(line).Contains("180316_Background")){
      TString fname(Form("%s/%s/%s/AD1_Wet_Phys%s.root",gSystem->Getenv("BIPO_OUTDIR"),rel.Data(),line.data(), pass.Data()));
      ch1->Add(fname.Data());
      TFile tfile(fname.Data());
      if(tfile.IsOpen()){
	lt1 += ((TVectorD*)tfile.Get("runtime"))->Norm1();
	++n1;
	tfile.Close();
      }
    }else if(TString(line).Contains("180525_Background")||
	     TString(line).Contains("180605_Background")){
      TString fname(Form("%s/%s/%s/AD1_Wet_Phys%s.root",gSystem->Getenv("BIPO_OUTDIR"),rel.Data(),line.data(), pass.Data()));
      ch2->Add(fname.Data());
      TFile tfile(fname.Data());
      if(tfile.IsOpen()){
	lt2 += ((TVectorD*)tfile.Get("runtime"))->Norm1();
	++n2;
	tfile.Close();
      }
    }
    file.peek();
  }
  cout<<n1<<" files added from 180316_Background\n";
  cout<<n2<<" files added from 180525_Background\n";
  cout<<lt1/3600.<<" total runtime hours from 180316_Background\n";
  cout<<lt2/3600.<<" total runtime hours from 180525_Background\n";
  const double tlow = 1e3, thigh = 120e3, tlowacc = 2e6, thighacc = 12e6;
  const double n2f = 0.0119;//ratio of lengths of near to far windows
  const double f2n = 1.0e4/119.0;//ratio of lengths of far to near windows
  const double tmin = 0.001;//start coincidence window tmin ms away from electron
  const double lowE = 0, highE = 8, EBW=0.2;
  int col[3] = {kBlue, kBlack, kGreen+2};
  TCut cut = Form("ncapt_dt>%f&&ncapt_dt<%f&&E>%f&&E<%f", tlow, thigh, lowE, highE);
  TCut cutacc = Form("fabs(ncapt_dt)>%f&&fabs(ncapt_dt)<%f&&E>%f&&E<%f",tlowacc,thighacc, lowE, highE);
  double timeratio = lt1/lt2;
  ch1->Draw(Form("E>>h1(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cut, "goff");
  TH1D* h1 = (TH1D*)gDirectory->Get("h1");
  h1->Sumw2();
  h1->Scale(1000/(lt1*h1->GetBinWidth(1)));
  h1->SetLineWidth(2);
  h1->SetLineColor(col[0]);
  h1->SetMarkerColor(col[0]);
  h1->SetTitle("Neutrino Energy Spectrum 180306_Background");
  
  ch1->Draw(Form("E>>h1acc(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cutacc,"goff");
  TH1D* h1acc = (TH1D*)gDirectory->Get("h1acc");
  h1acc->Sumw2();
  h1acc->SetLineWidth(2);
  h1acc->SetLineColor(col[1]);
  h1acc->SetMarkerColor(col[1]);
  h1acc->Scale(1000*n2f/(lt1*h1acc->GetBinWidth(1)));
  
  TCanvas *c1 = new TCanvas("c1", "c1",0,0,800,600);
  h1->Draw();
  gPad->Update();
  h1->GetXaxis()->SetTitle("Energy (MeV)");
  h1->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  h1acc->Draw("same");
  TH1D *h1diff = (TH1D*)h1->Clone("h1diff");
  h1diff->SetMarkerColor(col[2]);
  h1diff->SetLineColor(col[2]);
  h1diff->Add(h1acc,-1);
  h1diff->Draw("same");



  ch2->Draw(Form("E>>h2(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cut, "goff");
  TH1D* h2 = (TH1D*)gDirectory->Get("h2");
  h2->Sumw2();
  h2->Scale(1000/(lt2*h2->GetBinWidth(1)));
  h2->SetLineWidth(2);
  h2->SetLineColor(col[0]);
  h2->SetMarkerColor(col[0]);
  h2->SetTitle("Neutrino Energy Spectrum 180525_Background");
  
  ch2->Draw(Form("E>>h2acc(%i,%f,%f)",int((highE-lowE)/EBW),lowE, highE),cutacc,"goff");
  TH1D* h2acc = (TH1D*)gDirectory->Get("h2acc");
  h2acc->Sumw2();
  h2acc->Scale(1000*n2f/(lt2*h2acc->GetBinWidth(1)));
  h2acc->SetLineWidth(2);
  h2acc->SetLineColor(col[1]);
  h2acc->SetMarkerColor(col[1]);
  
  TCanvas *c2 = new TCanvas("c2", "c2",900,0,800,600);
  h2->Draw();
  gPad->Update();
  h2->GetXaxis()->SetTitle("Energy (MeV)");
  h2->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  h2acc->Draw("same");
  TH1D *h2diff = (TH1D*)h2->Clone("h2diff");
  h2diff->SetMarkerColor(col[2]);
  h2diff->SetLineColor(col[2]);
  h2diff->Add(h2acc,-1);
  h2diff->Draw("same");

  TCanvas *c3 = new TCanvas("c3", "c3",900,0,800,600);
  c3->SetGrid();
  h1diff->SetTitle("Background IBD-like Accidental Subtracted Spectrum");
  h1diff->SetLineColor(kRed);
  h1diff->SetMarkerColor(kRed);
  h2diff->SetLineColor(kBlue);
  h2diff->SetMarkerColor(kBlue);
  h1diff->Draw();
  gPad->Update();
  h1diff->GetYaxis()->SetTitle("Rate (mHz/MeV)");
  h1diff->GetYaxis()->SetLimits(-1,1);
  h1diff->GetYaxis()->SetRangeUser(-1, 7);
  h2diff->Draw("same");
  TH1D *hdiff = (TH1D*)h1diff->Clone("hdiff");
  hdiff->SetLineColor(kGreen+2);
  hdiff->Add(h2diff,-1);
  hdiff->Draw("same");
  TPaveText *pt = new TPaveText(0.7,0.7,0.99,0.899,"ndc");
  pt->SetShadowColor(0);
  pt->SetFillColor(0);
  TText *tt = pt->AddText("March Background");
  tt->SetTextColor(kRed);
  tt = pt->AddText("May/June Background");
  tt->SetTextColor(kBlue);
  tt = pt->AddText("Difference");
  tt->SetTextColor(kGreen+2);
  pt->Draw();
  gPad->Update();

  gStyle->SetOptFit(1111);
  TCanvas *c4 = new TCanvas("c4", "c4",900,0,800,600);
  c4->SetGrid();
  TH1D *hdiffpct = new TH1D("hdiffpct","hdiffpct",int((highE-lowE)/EBW),lowE, highE);
  hdiffpct->SetLineWidth(2);
  hdiffpct->SetLineColor(kGreen+2);
  for(int i=2;i<=hdiffpct->GetNbinsX();++i){
    //if(i>7&&i<11)continue;
    hdiffpct->SetBinContent(i,100*hdiff->GetBinContent(i)/h1diff->GetBinContent(i));
    hdiffpct->SetBinError(i,100*hdiff->GetBinError(i)/h1diff->GetBinContent(i));
  }
  hdiffpct->Draw();
  hdiffpct->SetTitle("Difference Between March and May/June Background Spectra");
  hdiffpct->GetXaxis()->SetTitle("Energy (MeV)");
  hdiffpct->GetYaxis()->SetTitle("Difference (%)");
  hdiffpct->GetYaxis()->SetRangeUser(-100,100);
  TF1 *f = new TF1("f","pol0",0.2,8);
  f->FixParameter(0,0);
  hdiffpct->Fit(f,"r");
  gPad->Update();
}
