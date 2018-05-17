{
  TCanvas *c = new TCanvas("c","c",0,0,800,600);
  TGraphErrors *gr = new TGraphErrors();
  gr->SetPoint(0,6.819,0.7004);//Rn219
  gr->SetPointError(0,0,0.0001);
  gr->SetPoint(1,7.386,0.8068);//Po215
  gr->SetPointError(1,0,0.0001);
  gr->SetPoint(2,7.687,0.8650);//Po214
  gr->SetPointError(2,0,0.0002);
  gr->SetPoint(3,8.785,1.0905);//Po212
  gr->SetPointError(3,0,0.0003);
  gr->SetMarkerStyle(8);
  gr->Draw("ap");
  gPad->Update();
  gr->GetXaxis()->SetTitle("Alpha Energy (MeV)");
  gr->GetYaxis()->SetTitle("Quenched Alpha Energy (MeV)");
  gr->SetTitle("Alpha Visible (Quenched) Energy vs Actual Energy");
  gStyle->SetOptFit(1111);
  gr->Fit("pol1");
  c->SaveAs("../plots/alpha_quenching_curve.png");

}
