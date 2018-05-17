//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 17 13:54:32 2018 by ROOT version 6.13/01
// from TChain BiPoTreePlugin/BiPo/
//////////////////////////////////////////////////////////

#ifndef BP_h
#define BP_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class BP {
public:
   TChain         *chain;    //!TChain
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<int>     *pseg;
   vector<int>     *pPID;
   vector<double>  *pE;
   vector<double>  *pt;
   vector<double>  *ptclust;
   vector<double>  *ptspread;
   vector<double>  *pz;
   vector<double>  *pPSD;
   vector<double>  *pmaxdist;
   vector<double>  *pEtot;
   vector<int>     *pmult_clust;
   vector<int>     *pmult_clust_ioni;
   vector<int>     *fseg;
   vector<int>     *fPID;
   vector<double>  *fE;
   vector<double>  *ft;
   vector<double>  *ftclust;
   vector<double>  *ftspread;
   vector<double>  *fz;
   vector<double>  *fPSD;
   vector<double>  *fmaxdist;
   vector<double>  *fEtot;
   vector<int>     *fmult_clust;
   vector<int>     *fmult_clust_ioni;
   Int_t           aseg;
   Int_t           aPID;
   Double_t        aE;
   Double_t        at;
   Double_t        az;
   Double_t        aPSD;
   Int_t           mult_prompt;
   Int_t           mult_far;

   // List of branches
   TBranch        *b_pseg;   //!
   TBranch        *b_pPID;   //!
   TBranch        *b_pE;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_ptclust;   //!
   TBranch        *b_ptspread;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_pPSD;   //!
   TBranch        *b_pmaxdist;   //!
   TBranch        *b_pEtot;   //!
   TBranch        *b_pmult_clust;   //!
   TBranch        *b_pmult_clust_ioni;   //!
   TBranch        *b_fseg;   //!
   TBranch        *b_fPID;   //!
   TBranch        *b_fE;   //!
   TBranch        *b_ft;   //!
   TBranch        *b_ftclust;   //!
   TBranch        *b_ftspread;   //!
   TBranch        *b_fz;   //!
   TBranch        *b_fPSD;   //!
   TBranch        *b_fmaxdist;   //!
   TBranch        *b_fEtot;   //!
   TBranch        *b_fmult_clust;   //!
   TBranch        *b_fmult_clust_ioni;   //!
   TBranch        *b_aseg;   //!
   TBranch        *b_aPID;   //!
   TBranch        *b_aE;   //!
   TBranch        *b_at;   //!
   TBranch        *b_az;   //!
   TBranch        *b_aPSD;   //!
   TBranch        *b_mult_prompt;   //!
   TBranch        *b_mult_far;   //!

   BP(TTree *tree=0);
   virtual ~BP();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef BP_cxx
BP::BP(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("BiPoTreePlugin/BiPo",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      chain = new TChain("BiPoTreePlugin/BiPo","");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00000_ts1520293010.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00001_ts1520296742.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00002_ts1520300359.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00003_ts1520304327.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00004_ts1520308055.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00005_ts1520311673.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00006_ts1520315292.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00007_ts1520319016.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00008_ts1520322635.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00009_ts1520326253.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00010_ts1520329873.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00011_ts1520333492.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00012_ts1520337149.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00013_ts1520340807.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00014_ts1520344562.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00015_ts1520348256.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00016_ts1520352002.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00017_ts1520355624.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00018_ts1520359240.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00019_ts1520362892.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00020_ts1520366514.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s015_f00021_ts1520370177.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00000_ts1520376529.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00001_ts1520380146.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00002_ts1520383829.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00003_ts1520387710.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00004_ts1520391325.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00005_ts1520395132.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00006_ts1520398747.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00007_ts1520402510.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00008_ts1520406194.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00009_ts1520409847.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00010_ts1520413466.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00011_ts1520417083.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00012_ts1520420833.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00013_ts1520424652.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00014_ts1520428272.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00015_ts1520431889.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s016_f00016_ts1520435668.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s017_f00001_ts1520439608.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s017_f00002_ts1520439880.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s017_f00003_ts1520443530.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s017_f00004_ts1520447151.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s017_f00005_ts1520450770.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00001_ts1520460145.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00002_ts1520463763.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00003_ts1520467378.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00004_ts1520471028.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00005_ts1520474817.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00006_ts1520478621.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00007_ts1520482279.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00008_ts1520485897.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00009_ts1520489514.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00010_ts1520493129.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00011_ts1520496785.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00012_ts1520500403.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00013_ts1520504056.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00014_ts1520507699.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00015_ts1520511348.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00016_ts1520514968.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00017_ts1520518690.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00018_ts1520522418.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00019_ts1520526066.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00020_ts1520529817.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00021_ts1520533438.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00022_ts1520537119.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s018_f00023_ts1520540811.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00000_ts1520546270.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00001_ts1520547017.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00004_ts1520547517.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00005_ts1520551182.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00006_ts1520554956.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00007_ts1520558572.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00008_ts1520562331.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00009_ts1520565957.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00010_ts1520569658.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00011_ts1520573357.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00012_ts1520577124.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00013_ts1520580913.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00014_ts1520584579.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00015_ts1520588200.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00016_ts1520591934.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00017_ts1520595594.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00018_ts1520599534.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00019_ts1520603152.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00020_ts1520606919.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00021_ts1520610609.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00022_ts1520614295.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00023_ts1520617913.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s019_f00024_ts1520621667.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00001_ts1520628585.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00002_ts1520632201.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00003_ts1520635882.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00004_ts1520639502.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00005_ts1520643345.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00006_ts1520646961.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00007_ts1520650581.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00008_ts1520654200.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00009_ts1520657817.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00010_ts1520661436.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00011_ts1520665053.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00012_ts1520668671.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00013_ts1520672289.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00014_ts1520675944.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00015_ts1520679719.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00016_ts1520683335.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00017_ts1520687177.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00018_ts1520690955.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s020_f00019_ts1520694577.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s021_f00000_ts1520696538.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s021_f00001_ts1520700225.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s021_f00002_ts1520702852.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s021_f00003_ts1520703406.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s021_f00004_ts1520707109.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00000_ts1520714879.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00001_ts1520718617.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00002_ts1520722234.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00003_ts1520725921.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00004_ts1520729543.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00005_ts1520733231.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00006_ts1520736937.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00007_ts1520740555.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00008_ts1520744173.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00009_ts1520747858.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00010_ts1520751591.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00011_ts1520755213.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00012_ts1520758833.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00013_ts1520762453.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00014_ts1520766076.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00016_ts1520773421.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00017_ts1520775516.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00018_ts1520779135.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s022_f00019_ts1520782756.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00000_ts1520789749.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00001_ts1520793369.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00002_ts1520796990.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00003_ts1520800611.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00004_ts1520804340.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00005_ts1520807960.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00006_ts1520811610.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00007_ts1520815229.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00008_ts1520818928.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00009_ts1520822545.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00010_ts1520826301.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00011_ts1520829922.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00012_ts1520833544.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00013_ts1520837191.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00014_ts1520840922.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00015_ts1520844574.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00016_ts1520848228.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00017_ts1520851887.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00018_ts1520855647.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00019_ts1520859339.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00020_ts1520862956.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00021_ts1520866614.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00022_ts1520870441.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00023_ts1520874063.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00024_ts1520879793.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00025_ts1520883513.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00026_ts1520887172.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00027_ts1520890824.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00028_ts1520894475.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00029_ts1520898094.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00030_ts1520901751.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00031_ts1520905408.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00032_ts1520909167.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00033_ts1520912950.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00034_ts1520916567.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00035_ts1520920290.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00036_ts1520924240.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00037_ts1520927856.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00038_ts1520931541.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00039_ts1520935194.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00040_ts1520938821.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00041_ts1520942510.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00042_ts1520946126.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00043_ts1520949779.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00044_ts1520951291.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00045_ts1520955058.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00046_ts1520958673.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00047_ts1520962294.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00048_ts1520965945.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00049_ts1520969562.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00050_ts1520973180.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00051_ts1520976800.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00052_ts1520980419.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00053_ts1520984041.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00054_ts1520985046.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00055_ts1520988698.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00056_ts1520992317.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00057_ts1520996143.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00058_ts1520999766.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00059_ts1521003386.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00060_ts1521007038.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00061_ts1521010655.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00062_ts1521014339.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00063_ts1521017998.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00064_ts1521021619.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00065_ts1521025276.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00066_ts1521028993.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00067_ts1521032736.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00068_ts1521036357.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00069_ts1521040184.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00070_ts1521043928.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00071_ts1521047579.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00072_ts1521051204.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00073_ts1521054962.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00074_ts1521055298.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00075_ts1521058948.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00076_ts1521062565.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00077_ts1521066223.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00078_ts1521070029.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00079_ts1521073741.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00080_ts1521077359.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00081_ts1521081015.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00082_ts1521084821.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00083_ts1521088437.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00084_ts1521092090.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00085_ts1521095833.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00086_ts1521099490.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00087_ts1521103145.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00088_ts1521106844.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00089_ts1521110463.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00090_ts1521114087.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00091_ts1521117803.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00092_ts1521121559.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00093_ts1521125261.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00094_ts1521128881.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00095_ts1521132540.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00096_ts1521136234.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00097_ts1521139921.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00098_ts1521143845.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00099_ts1521147534.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00100_ts1521151185.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00101_ts1521154842.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00102_ts1521158466.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00103_ts1521162085.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00104_ts1521165905.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00105_ts1521169524.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00106_ts1521173175.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00107_ts1521176795.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00108_ts1521180413.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00109_ts1521184099.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00110_ts1521187781.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00111_ts1521191403.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/WetCommissioning/pass_BiPo5/s023_f00112_ts1521195058.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00000_ts1521211900.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00001_ts1521215519.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00002_ts1521219136.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00003_ts1521222821.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00004_ts1521226440.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00005_ts1521230059.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00006_ts1521233681.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00007_ts1521237303.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00008_ts1521240958.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00009_ts1521244577.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00010_ts1521248230.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00011_ts1521248613.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00012_ts1521252233.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00013_ts1521255851.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00014_ts1521259475.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00015_ts1521263093.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00016_ts1521266713.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00017_ts1521270336.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00018_ts1521274044.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00019_ts1521277696.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00020_ts1521281481.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00021_ts1521285100.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s000_f00022_ts1521288717.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00000_ts1521292190.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00001_ts1521295807.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00002_ts1521299456.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00003_ts1521303074.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00004_ts1521306732.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00005_ts1521310386.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00006_ts1521314038.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00007_ts1521317659.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00008_ts1521321279.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00009_ts1521324897.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00010_ts1521328514.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00011_ts1521332128.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00012_ts1521335861.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00013_ts1521339480.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00014_ts1521343242.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00015_ts1521346859.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00016_ts1521350477.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00017_ts1521354097.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00018_ts1521357713.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00019_ts1521361333.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00020_ts1521364952.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00021_ts1521368694.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00022_ts1521372410.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00023_ts1521376030.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00024_ts1521379683.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00025_ts1521383303.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00026_ts1521386958.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00027_ts1521390576.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00028_ts1521394263.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00029_ts1521397911.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00030_ts1521401600.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00031_ts1521405250.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00032_ts1521408967.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00033_ts1521412682.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00034_ts1521416401.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00035_ts1521420083.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00036_ts1521423699.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00037_ts1521427317.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00038_ts1521430938.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00039_ts1521434621.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00040_ts1521438306.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00041_ts1521441922.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00042_ts1521445642.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00043_ts1521449362.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00044_ts1521452998.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00045_ts1521456688.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00046_ts1521460338.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00047_ts1521464027.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00048_ts1521467679.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00049_ts1521471299.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00050_ts1521475011.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00051_ts1521478634.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00052_ts1521482278.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00053_ts1521485957.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00054_ts1521489577.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00055_ts1521493194.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00056_ts1521496856.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00057_ts1521500575.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00058_ts1521504327.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00059_ts1521508046.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00060_ts1521511664.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00061_ts1521515414.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00062_ts1521519029.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00063_ts1521522681.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00064_ts1521526366.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00065_ts1521529982.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00066_ts1521533748.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00067_ts1521537500.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00068_ts1521541151.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00069_ts1521544770.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00070_ts1521548486.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00071_ts1521552101.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00072_ts1521555754.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00073_ts1521559372.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00074_ts1521562993.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00075_ts1521566645.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00076_ts1521570268.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00077_ts1521574005.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00078_ts1521577668.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00079_ts1521581330.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00080_ts1521584991.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00081_ts1521588612.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00082_ts1521592267.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00083_ts1521595884.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00084_ts1521599534.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00085_ts1521603206.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00086_ts1521606860.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00087_ts1521610483.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00088_ts1521614136.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00089_ts1521617790.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00090_ts1521621464.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00091_ts1521625114.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00092_ts1521628767.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00093_ts1521632491.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00094_ts1521636180.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00095_ts1521639797.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00096_ts1521643515.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00097_ts1521647172.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00098_ts1521650857.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00099_ts1521654506.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00100_ts1521658125.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00101_ts1521661867.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00102_ts1521665664.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00103_ts1521669283.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00104_ts1521672983.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00105_ts1521676602.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00106_ts1521680286.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00107_ts1521683907.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00108_ts1521687529.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00109_ts1521691241.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00110_ts1521694971.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00111_ts1521698593.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00112_ts1521702209.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00113_ts1521705939.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00114_ts1521709595.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00115_ts1521713211.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00116_ts1521716865.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00117_ts1521720481.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00118_ts1521724168.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00119_ts1521727822.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00120_ts1521731466.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00121_ts1521735162.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00122_ts1521738784.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00123_ts1521742406.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00124_ts1521746024.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00125_ts1521749676.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00126_ts1521753465.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00127_ts1521757124.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00128_ts1521761047.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00129_ts1521764670.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00130_ts1521768434.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00131_ts1521772081.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00132_ts1521775732.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00133_ts1521779350.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00134_ts1521782999.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00135_ts1521786655.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00136_ts1521790276.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00137_ts1521793926.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00138_ts1521797577.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00139_ts1521801234.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00140_ts1521804851.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00141_ts1521808563.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00142_ts1521812294.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00143_ts1521815976.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00144_ts1521819631.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00145_ts1521823247.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00146_ts1521826898.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00147_ts1521830782.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00148_ts1521834430.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00149_ts1521838092.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00150_ts1521841709.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00151_ts1521845401.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00152_ts1521849020.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00153_ts1521852794.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00154_ts1521856414.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00155_ts1521860210.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00156_ts1521863832.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00157_ts1521867514.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00158_ts1521871134.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00159_ts1521874819.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00160_ts1521878504.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00161_ts1521882124.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00162_ts1521885739.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00163_ts1521889452.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00164_ts1521893213.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00165_ts1521896834.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00166_ts1521900449.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00167_ts1521904069.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00168_ts1521907782.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00169_ts1521909739.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00170_ts1521913931.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00171_ts1521924828.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00172_ts1521928475.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00173_ts1521932096.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00174_ts1521935980.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00175_ts1521939632.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00176_ts1521943282.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00177_ts1521946931.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00178_ts1521950547.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00179_ts1521954193.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00180_ts1521957854.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00181_ts1521961543.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00182_ts1521965308.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00183_ts1521968995.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00184_ts1521972652.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00185_ts1521976271.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00186_ts1521980013.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00187_ts1521983633.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00188_ts1521987284.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00189_ts1521990933.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00190_ts1521994587.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00191_ts1521998275.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00192_ts1522002043.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00193_ts1522005765.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00194_ts1522009462.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00195_ts1522013106.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00196_ts1522016789.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00197_ts1522020501.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00198_ts1522024211.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00199_ts1522027828.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00200_ts1522031922.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00201_ts1522035805.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00202_ts1522039455.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00203_ts1522043170.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00204_ts1522046883.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00205_ts1522050503.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00206_ts1522054157.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00207_ts1522057775.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00208_ts1522061392.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00209_ts1522065012.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00210_ts1522068658.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00211_ts1522072338.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00212_ts1522075954.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00213_ts1522079569.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00214_ts1522083252.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00215_ts1522086966.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00216_ts1522090746.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00217_ts1522094430.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00218_ts1522098048.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00219_ts1522101699.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00220_ts1522105320.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00221_ts1522108973.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00222_ts1522112817.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00223_ts1522116436.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00224_ts1522120084.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00225_ts1522123701.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00227_ts1522131034.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00228_ts1522134780.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00229_ts1522138397.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00230_ts1522142018.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00231_ts1522145737.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00232_ts1522149495.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00233_ts1522153232.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00234_ts1522156917.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00235_ts1522160533.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00236_ts1522164189.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00237_ts1522167809.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00238_ts1522171425.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00239_ts1522175080.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00240_ts1522178702.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00241_ts1522182318.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00242_ts1522185939.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00243_ts1522189625.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00244_ts1522191724.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00245_ts1522195517.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00246_ts1522199390.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00247_ts1522203110.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00248_ts1522206730.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00249_ts1522210377.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00250_ts1522214089.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00251_ts1522217738.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00252_ts1522221390.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00253_ts1522225042.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00254_ts1522228693.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00255_ts1522232309.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00256_ts1522235988.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00257_ts1522239607.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00258_ts1522243221.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00259_ts1522246902.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00260_ts1522250629.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00261_ts1522254251.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00262_ts1522257997.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00263_ts1522261682.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00264_ts1522265332.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00265_ts1522268978.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00266_ts1522272597.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00267_ts1522276283.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00268_ts1522280003.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00269_ts1522283623.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00270_ts1522287284.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00271_ts1522290967.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00272_ts1522294615.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00274_ts1522301908.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00275_ts1522305597.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00276_ts1522309217.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00277_ts1522312836.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00278_ts1522316451.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00279_ts1522320072.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00280_ts1522323691.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00281_ts1522327372.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00282_ts1522330989.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00283_ts1522334672.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00284_ts1522338357.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00285_ts1522342009.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00286_ts1522345625.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00287_ts1522349244.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00288_ts1522352902.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00289_ts1522356760.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00290_ts1522360410.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00291_ts1522364032.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00292_ts1522367963.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00293_ts1522371613.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00294_ts1522375232.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00295_ts1522378848.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00296_ts1522382526.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00297_ts1522386292.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00299_ts1522393595.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00300_ts1522397213.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00301_ts1522400868.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00302_ts1522404516.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00303_ts1522408305.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00304_ts1522411925.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00305_ts1522415647.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00306_ts1522419262.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00307_ts1522422944.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00308_ts1522426599.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00309_ts1522430218.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00310_ts1522433868.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00311_ts1522437489.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00312_ts1522441106.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00313_ts1522444758.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00314_ts1522448519.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00315_ts1522452173.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00316_ts1522455791.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00317_ts1522459406.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00318_ts1522463175.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00319_ts1522466821.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00320_ts1522470557.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00321_ts1522474408.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00322_ts1522478095.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00323_ts1522481714.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00324_ts1522485331.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00325_ts1522488951.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00326_ts1522492572.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00327_ts1522496196.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00328_ts1522499815.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00329_ts1522503435.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00330_ts1522507053.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180316_Background/pass_BiPo5/s001_f00331_ts1522510768.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00003_ts1524021346.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00004_ts1524021591.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00005_ts1524025242.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00006_ts1524028859.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00007_ts1524032479.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00008_ts1524036099.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00009_ts1524039745.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00010_ts1524043364.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00011_ts1524047049.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180417_Background/pass_BiPo5/s000_f00012_ts1524050665.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00000_ts1524244664.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00001_ts1524248317.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00002_ts1524251999.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00003_ts1524255614.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00004_ts1524259369.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00005_ts1524263267.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00006_ts1524266918.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00007_ts1524270537.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00008_ts1524274153.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00009_ts1524277901.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00010_ts1524281550.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00011_ts1524285206.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00012_ts1524288852.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00013_ts1524292468.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00014_ts1524296181.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00015_ts1524299799.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00016_ts1524303494.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00017_ts1524307110.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00018_ts1524310763.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00019_ts1524314445.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00020_ts1524318128.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00021_ts1524321770.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00022_ts1524325390.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00023_ts1524329010.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00024_ts1524332665.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00025_ts1524336308.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00026_ts1524339927.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00027_ts1524343545.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00028_ts1524347199.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00029_ts1524350857.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00030_ts1524354472.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00031_ts1524358219.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00032_ts1524361939.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00033_ts1524365601.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00034_ts1524369254.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00035_ts1524372901.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00036_ts1524376552.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00037_ts1524380168.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00039_ts1524387538.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00040_ts1524391155.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00041_ts1524394771.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00042_ts1524398520.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00043_ts1524402137.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00044_ts1524405785.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00045_ts1524409437.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00046_ts1524413057.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00048_ts1524420323.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00049_ts1524424066.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00050_ts1524427696.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00051_ts1524431316.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00052_ts1524434937.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00053_ts1524438588.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00054_ts1524442206.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00055_ts1524445860.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00056_ts1524449477.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00057_ts1524453130.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00058_ts1524456784.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00059_ts1524460437.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00060_ts1524464088.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00061_ts1524467708.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00063_ts1524475147.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00064_ts1524478795.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00065_ts1524482444.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00066_ts1524486101.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00067_ts1524489719.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00068_ts1524493335.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00069_ts1524496987.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00070_ts1524500641.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00071_ts1524504528.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00072_ts1524508309.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00073_ts1524511993.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00074_ts1524515681.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00075_ts1524519303.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00076_ts1524522952.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00077_ts1524526571.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00078_ts1524530292.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00079_ts1524534011.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00080_ts1524537632.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00081_ts1524541252.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00082_ts1524544902.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00083_ts1524548578.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00084_ts1524552194.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00085_ts1524555814.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00086_ts1524559604.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00087_ts1524563223.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00088_ts1524567004.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00089_ts1524571109.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00090_ts1524574727.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00091_ts1524578379.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00092_ts1524581997.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00093_ts1524585616.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00094_ts1524589234.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00095_ts1524592918.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00096_ts1524596539.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00097_ts1524600228.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00098_ts1524603843.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00099_ts1524607463.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00100_ts1524611080.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00102_ts1524618318.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00103_ts1524621970.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00104_ts1524625622.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00105_ts1524629276.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00106_ts1524632955.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00107_ts1524636573.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00108_ts1524640192.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00109_ts1524643808.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00110_ts1524647461.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00111_ts1524651112.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00112_ts1524654829.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00113_ts1524658511.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00114_ts1524662164.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00115_ts1524665783.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00116_ts1524669462.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00117_ts1524673119.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00118_ts1524676734.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00119_ts1524680418.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00120_ts1524684111.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00121_ts1524687827.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00122_ts1524691480.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00123_ts1524695099.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00124_ts1524698719.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00125_ts1524702369.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00126_ts1524705991.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00127_ts1524709610.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00128_ts1524713229.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00129_ts1524716883.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00130_ts1524720503.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00131_ts1524724286.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00132_ts1524727903.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00133_ts1524731526.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00134_ts1524735243.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00135_ts1524738889.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00136_ts1524742541.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00137_ts1524746423.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00138_ts1524750144.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00139_ts1524753792.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00140_ts1524757660.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00141_ts1524761403.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00142_ts1524765049.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00143_ts1524768669.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00144_ts1524772288.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00145_ts1524775937.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00146_ts1524779757.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00147_ts1524783409.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00148_ts1524787027.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00149_ts1524790644.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00150_ts1524794291.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00151_ts1524797909.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00152_ts1524801661.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00153_ts1524805310.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00154_ts1524808928.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00155_ts1524812578.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00156_ts1524816234.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00157_ts1524819954.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00158_ts1524823572.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00159_ts1524827220.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00160_ts1524830864.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00161_ts1524834486.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00162_ts1524838263.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00163_ts1524841879.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00164_ts1524845500.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00165_ts1524849192.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00166_ts1524852878.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00167_ts1524856497.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00168_ts1524860115.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00169_ts1524863731.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00170_ts1524867429.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00171_ts1524871054.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00172_ts1524874709.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00173_ts1524878331.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00174_ts1524881951.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00175_ts1524885652.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00176_ts1524889278.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00177_ts1524892930.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00178_ts1524896545.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00179_ts1524900325.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00180_ts1524903944.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00181_ts1524907563.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00183_ts1524914801.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00184_ts1524918524.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00185_ts1524922317.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00186_ts1524926007.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00187_ts1524929797.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00188_ts1524933478.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00189_ts1524937200.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00190_ts1524940853.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00191_ts1524944510.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00192_ts1524948165.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00193_ts1524951992.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00194_ts1524955646.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00195_ts1524959297.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00196_ts1524963014.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00197_ts1524966735.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00198_ts1524970356.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00199_ts1524974702.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00200_ts1524978422.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00201_ts1524982078.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00202_ts1524985695.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00203_ts1524989315.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00204_ts1524993060.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00205_ts1524996675.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00206_ts1525000291.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00207_ts1525003945.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00208_ts1525007563.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00209_ts1525011286.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00210_ts1525014936.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00211_ts1525018559.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00212_ts1525022243.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00213_ts1525026007.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00214_ts1525029627.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00215_ts1525033247.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00216_ts1525036895.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00217_ts1525040513.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00218_ts1525044265.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00220_ts1525051507.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00221_ts1525055128.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00222_ts1525058749.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00223_ts1525062498.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00224_ts1525066155.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00225_ts1525069771.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00226_ts1525073467.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00227_ts1525077224.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00229_ts1525084458.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00230_ts1525088075.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00231_ts1525091695.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00232_ts1525095382.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00233_ts1525099135.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00234_ts1525102840.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00235_ts1525106523.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00236_ts1525110170.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00237_ts1525113788.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00238_ts1525117438.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00239_ts1525121091.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00240_ts1525124893.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00241_ts1525128546.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00242_ts1525132201.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00243_ts1525135823.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00244_ts1525139467.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00245_ts1525143088.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00246_ts1525146708.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00247_ts1525150328.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00248_ts1525153974.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00249_ts1525157591.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00250_ts1525161271.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00251_ts1525164995.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00252_ts1525168849.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00253_ts1525172531.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00254_ts1525176326.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180420_Background/pass_BiPo5/s000_f00255_ts1525179987.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00000_ts1525183676.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00001_ts1525187324.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00002_ts1525191006.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00003_ts1525194625.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00004_ts1525198244.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00005_ts1525201929.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00006_ts1525205549.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00007_ts1525209622.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00008_ts1525213831.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00009_ts1525217497.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00010_ts1525221117.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00011_ts1525224840.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00012_ts1525228463.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00013_ts1525232083.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00014_ts1525235766.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00015_ts1525239419.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00016_ts1525243071.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00017_ts1525246757.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00018_ts1525250442.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00019_ts1525254156.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00020_ts1525257807.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00021_ts1525261577.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00022_ts1525265231.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00023_ts1525268848.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00024_ts1525272498.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00025_ts1525276265.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00026_ts1525279884.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00027_ts1525283570.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00028_ts1525287189.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00029_ts1525290880.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00030_ts1525294502.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00031_ts1525298123.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00032_ts1525301743.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00033_ts1525305431.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00034_ts1525309049.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00035_ts1525312701.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00036_ts1525316558.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00037_ts1525320283.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00038_ts1525324056.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00039_ts1525327675.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00040_ts1525331293.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00041_ts1525334995.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00042_ts1525338737.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00043_ts1525342356.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00044_ts1525346043.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00045_ts1525349855.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00046_ts1525353584.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00047_ts1525357272.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00048_ts1525360927.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00049_ts1525364618.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s000_f00050_ts1525368239.root/BiPoTreePlugin/BiPo");
      chain->Add("/home/jonesdc/prospect/bipo_data//Phys_20180510/180501_ReactorOn/pass_BiPo5/s001_f00000_ts1525370836.root/BiPoTreePlugin/BiPo");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

BP::~BP()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t BP::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t BP::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void BP::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pseg = 0;
   pPID = 0;
   pE = 0;
   pt = 0;
   ptclust = 0;
   ptspread = 0;
   pz = 0;
   pPSD = 0;
   pmaxdist = 0;
   pEtot = 0;
   pmult_clust = 0;
   pmult_clust_ioni = 0;
   fseg = 0;
   fPID = 0;
   fE = 0;
   ft = 0;
   ftclust = 0;
   ftspread = 0;
   fz = 0;
   fPSD = 0;
   fmaxdist = 0;
   fEtot = 0;
   fmult_clust = 0;
   fmult_clust_ioni = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("pseg", &pseg, &b_pseg);
   fChain->SetBranchAddress("pPID", &pPID, &b_pPID);
   fChain->SetBranchAddress("pE", &pE, &b_pE);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("ptclust", &ptclust, &b_ptclust);
   fChain->SetBranchAddress("ptspread", &ptspread, &b_ptspread);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   fChain->SetBranchAddress("pPSD", &pPSD, &b_pPSD);
   fChain->SetBranchAddress("pmaxdist", &pmaxdist, &b_pmaxdist);
   fChain->SetBranchAddress("pEtot", &pEtot, &b_pEtot);
   fChain->SetBranchAddress("pmult_clust", &pmult_clust, &b_pmult_clust);
   fChain->SetBranchAddress("pmult_clust_ioni", &pmult_clust_ioni, &b_pmult_clust_ioni);
   fChain->SetBranchAddress("fseg", &fseg, &b_fseg);
   fChain->SetBranchAddress("fPID", &fPID, &b_fPID);
   fChain->SetBranchAddress("fE", &fE, &b_fE);
   fChain->SetBranchAddress("ft", &ft, &b_ft);
   fChain->SetBranchAddress("ftclust", &ftclust, &b_ftclust);
   fChain->SetBranchAddress("ftspread", &ftspread, &b_ftspread);
   fChain->SetBranchAddress("fz", &fz, &b_fz);
   fChain->SetBranchAddress("fPSD", &fPSD, &b_fPSD);
   fChain->SetBranchAddress("fmaxdist", &fmaxdist, &b_fmaxdist);
   fChain->SetBranchAddress("fEtot", &fEtot, &b_fEtot);
   fChain->SetBranchAddress("fmult_clust", &fmult_clust, &b_fmult_clust);
   fChain->SetBranchAddress("fmult_clust_ioni", &fmult_clust_ioni, &b_fmult_clust_ioni);
   fChain->SetBranchAddress("aseg", &aseg, &b_aseg);
   fChain->SetBranchAddress("aPID", &aPID, &b_aPID);
   fChain->SetBranchAddress("aE", &aE, &b_aE);
   fChain->SetBranchAddress("at", &at, &b_at);
   fChain->SetBranchAddress("az", &az, &b_az);
   fChain->SetBranchAddress("aPSD", &aPSD, &b_aPSD);
   fChain->SetBranchAddress("mult_prompt", &mult_prompt, &b_mult_prompt);
   fChain->SetBranchAddress("mult_far", &mult_far, &b_mult_far);
   Notify();
}

Bool_t BP::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void BP::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t BP::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef BP_cxx
