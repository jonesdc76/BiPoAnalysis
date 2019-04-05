#include "chisquare.hh"

chisquare::chisquare(){};
chisquare::chisquare(int ndf_t, double chisq_t){
  ndf = ndf_t;
  chisq = chisq_t;
  double d = 0.5*ndf;
  f = new TF1("f","pow(x,[0])*exp(-x/2.0)/[1]",0,10*ndf);
  f->SetParameters(d-1, pow(2, d)*tgamma(d));
}

double chisquare::GetProb(){
  if(ndf == 0){
    cout<<"NDF and Chi Square not set\n";
    return 0;
  }
  return f->Integral(chisq, 1000.0*ndf);
}

double chisquare::GetProb(int ndf_t, double chisq_t){
  ndf = ndf_t;
  chisq = chisq_t;
  double d = 0.5*ndf;
  f->SetParameters(d-1, pow(2, d)*tgamma(d));
  f->SetRange(0,10*ndf);
  return f->Integral(chisq, 1000.0*ndf);
}

void chisquare::SetChisquare(double chisq_t){
  chisq = chisq_t;
}

void chisquare::SetNDF(int ndf_t){
  ndf = ndf_t;
  double d = 0.5*ndf;
  f->SetParameters(d-1, pow(2, d)*tgamma(d));
  f->SetRange(0,10*ndf);
}

void chisquare::Draw(){
  f->Draw();
}

void chisquare::Draw(int ndf_t){
  ndf = ndf_t;
  double d = 0.5*ndf;
  f->SetParameters(d-1, pow(2, d)*tgamma(d));
  f->SetRange(0,10*ndf);
  f->Draw();
}
