#include "math.h"
#include "TF1.h"
#include "TCanvas.h"
class chisquare{
public:
  chisquare();
  chisquare(int ndf_t, double chisq_t);
  double GetChisquare(){return chisq;};
  int GetNDF(){return ndf;};
  double GetProb(int ndf_t, double chisq_t);
  double GetProb();
  void SetChisquare(double chisq_t);
  void SetNDF(int ndf_t);
  void Draw(int ndf_t);
  void Draw();
  
  TF1 *f;

private:
  int ndf = 0;
  double prob = 0;
  double chisq = 0;
  TCanvas *c;
};
