//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 13 16:46:16 2018 by ROOT version 6.13/01
// from TChain P2kIBDPlugin/Tibd/
//////////////////////////////////////////////////////////

#ifndef IBDon_h
#define IBDon_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class IBDon {
public:
   TChain         *chain;    //!TChain
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        evt;
   Double_t        t_abs;
   Float_t         Encapt;
   Float_t         E;
   Float_t         Esmear;
   Int_t           maxseg;
   Float_t         xyz[3];
   Float_t         E_maxseg;
   Float_t         E_adjacent;
   Float_t         ncapt_psd;
   Float_t         prompt_psd;
   Int_t           segmult;
   Float_t         diameter;
   Float_t         tspread;
   Float_t         ncapt_dt;
   Int_t           n_seg;
   Float_t         n_xyz[3];
   Float_t         veto_t;
   Int_t           cut;
   Int_t           detgeom;
   Float_t         rxpwr;

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_t_abs;   //!
   TBranch        *b_Encapt;   //!
   TBranch        *b_E;   //!
   TBranch        *b_Esmear;   //!
   TBranch        *b_maxseg;   //!
   TBranch        *b_xyz;   //!
   TBranch        *b_E_maxseg;   //!
   TBranch        *b_E_adjacent;   //!
   TBranch        *b_ncapt_psd;   //!
   TBranch        *b_prompt_psd;   //!
   TBranch        *b_segmult;   //!
   TBranch        *b_diameter;   //!
   TBranch        *b_tspread;   //!
   TBranch        *b_ncapt_dt;   //!
   TBranch        *b_n_seg;   //!
   TBranch        *b_n_xyz;   //!
   TBranch        *b_veto_t;   //!
   TBranch        *b_cut;   //!
   TBranch        *b_detgeom;   //!
   TBranch        *b_rxpwr;   //!

   IBDon(TTree *tree=0);
   virtual ~IBDon();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef IBDon_cxx
IBDon::IBDon(TTree *tree) : fChain(0) 
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
      f->GetObject("P2kIBDPlugin/Tibd",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      chain = new TChain("P2kIBDPlugin/Tibd","");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00000_ts1520293010/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00001_ts1520296742/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00002_ts1520300359/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00003_ts1520304327/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00004_ts1520308055/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00005_ts1520311673/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00006_ts1520315292/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00007_ts1520319016/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00008_ts1520322635/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00009_ts1520326253/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00010_ts1520329873/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00011_ts1520333492/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00012_ts1520337149/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00013_ts1520340807/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00014_ts1520344562/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00015_ts1520348256/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00016_ts1520352002/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00017_ts1520355624/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00018_ts1520359240/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00019_ts1520362892/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00020_ts1520366514/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series015/s015_f00021_ts1520370177/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00000_ts1520376529/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00001_ts1520380146/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00002_ts1520383829/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00003_ts1520387710/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00004_ts1520391325/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00005_ts1520395132/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00006_ts1520398747/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00007_ts1520402510/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00008_ts1520406194/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00009_ts1520409847/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00010_ts1520413466/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00011_ts1520417083/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00012_ts1520420833/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00013_ts1520424652/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00014_ts1520428272/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00015_ts1520431889/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series016/s016_f00016_ts1520435668/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series017/s017_f00001_ts1520439608/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series017/s017_f00002_ts1520439880/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series017/s017_f00003_ts1520443530/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series017/s017_f00004_ts1520447151/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series017/s017_f00005_ts1520450770/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00001_ts1520460145/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00002_ts1520463763/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00003_ts1520467378/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00004_ts1520471028/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00005_ts1520474817/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00006_ts1520478621/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00007_ts1520482279/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00008_ts1520485897/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00009_ts1520489514/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00010_ts1520493129/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00011_ts1520496785/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00012_ts1520500403/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00013_ts1520504056/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00014_ts1520507699/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00015_ts1520511348/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00016_ts1520514968/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00017_ts1520518690/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00018_ts1520522418/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00019_ts1520526066/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00020_ts1520529817/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00021_ts1520533438/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00022_ts1520537119/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series018/s018_f00023_ts1520540811/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00000_ts1520546270/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00001_ts1520547017/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00004_ts1520547517/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00005_ts1520551182/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00006_ts1520554956/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00007_ts1520558572/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00008_ts1520562331/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00009_ts1520565957/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00010_ts1520569658/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00011_ts1520573357/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00012_ts1520577124/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00013_ts1520580913/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00014_ts1520584579/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00015_ts1520588200/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00016_ts1520591934/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00017_ts1520595594/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00018_ts1520599534/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00019_ts1520603152/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00020_ts1520606919/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00021_ts1520610609/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00022_ts1520614295/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00023_ts1520617913/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series019/s019_f00024_ts1520621667/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00001_ts1520628585/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00002_ts1520632201/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00003_ts1520635882/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00004_ts1520639502/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00005_ts1520643345/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00006_ts1520646961/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00007_ts1520650581/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00008_ts1520654200/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00009_ts1520657817/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00010_ts1520661436/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00011_ts1520665053/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00012_ts1520668671/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00013_ts1520672289/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00014_ts1520675944/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00015_ts1520679719/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00016_ts1520683335/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00017_ts1520687177/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00018_ts1520690955/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series020/s020_f00019_ts1520694577/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series021/s021_f00000_ts1520696538/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series021/s021_f00001_ts1520700225/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series021/s021_f00002_ts1520702852/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series021/s021_f00003_ts1520703406/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series021/s021_f00004_ts1520707109/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00000_ts1520714879/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00001_ts1520718617/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00002_ts1520722234/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00003_ts1520725921/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00004_ts1520729543/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00005_ts1520733231/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00006_ts1520736937/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00007_ts1520740555/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00008_ts1520744173/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00009_ts1520747858/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00010_ts1520751591/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00011_ts1520755213/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00012_ts1520758833/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00013_ts1520762453/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00014_ts1520766076/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00015_ts1520769735/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00016_ts1520773421/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00017_ts1520775516/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00018_ts1520779135/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series022/s022_f00019_ts1520782756/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00000_ts1520789749/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00001_ts1520793369/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00002_ts1520796990/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00003_ts1520800611/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00004_ts1520804340/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00005_ts1520807960/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00006_ts1520811610/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00007_ts1520815229/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00008_ts1520818928/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00009_ts1520822545/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00010_ts1520826301/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00011_ts1520829922/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00012_ts1520833544/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00013_ts1520837191/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00014_ts1520840922/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00015_ts1520844574/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00016_ts1520848228/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00017_ts1520851887/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00018_ts1520855647/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00019_ts1520859339/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00020_ts1520862956/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00021_ts1520866614/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00022_ts1520870441/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00023_ts1520874063/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00024_ts1520879793/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00025_ts1520883513/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00026_ts1520887172/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00027_ts1520890824/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00028_ts1520894475/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00029_ts1520898094/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00030_ts1520901751/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00031_ts1520905408/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00032_ts1520909167/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00033_ts1520912950/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00034_ts1520916567/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00035_ts1520920290/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00036_ts1520924240/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00037_ts1520927856/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00038_ts1520931541/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00039_ts1520935194/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00040_ts1520938821/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00041_ts1520942510/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00042_ts1520946126/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00043_ts1520949779/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00044_ts1520951291/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00045_ts1520955058/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00046_ts1520958673/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00047_ts1520962294/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00048_ts1520965945/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00049_ts1520969562/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00050_ts1520973180/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00051_ts1520976800/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00052_ts1520980419/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00053_ts1520984041/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00054_ts1520985046/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00055_ts1520988698/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00056_ts1520992317/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00057_ts1520996143/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00058_ts1520999766/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00059_ts1521003386/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00060_ts1521007038/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00061_ts1521010655/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00062_ts1521014339/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00063_ts1521017998/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00064_ts1521021619/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00065_ts1521025276/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00066_ts1521028993/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00067_ts1521032736/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00068_ts1521036357/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00069_ts1521040184/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00070_ts1521043928/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00071_ts1521047579/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00072_ts1521051204/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00073_ts1521054962/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00074_ts1521055298/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00075_ts1521058948/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00076_ts1521062565/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00077_ts1521066223/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00078_ts1521070029/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00079_ts1521073741/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00080_ts1521077359/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00081_ts1521081015/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00082_ts1521084821/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00083_ts1521088437/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00084_ts1521092090/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00085_ts1521095833/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00086_ts1521099490/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00087_ts1521103145/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00088_ts1521106844/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00089_ts1521110463/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00090_ts1521114087/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00091_ts1521117803/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00092_ts1521121559/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00093_ts1521125261/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00094_ts1521128881/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00095_ts1521132540/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00096_ts1521136234/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00097_ts1521139921/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00098_ts1521143845/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00099_ts1521147534/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00100_ts1521151185/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00101_ts1521154842/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00102_ts1521158466/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00103_ts1521162085/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00104_ts1521165905/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00105_ts1521169524/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00106_ts1521173175/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00107_ts1521176795/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00108_ts1521180413/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00109_ts1521184099/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00110_ts1521187781/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00111_ts1521191403/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/WetCommissioning/series023/s023_f00112_ts1521195058/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180420_Background/series000/s000_f00251_ts1525164995/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180420_Background/series000/s000_f00252_ts1525168849/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180420_Background/series000/s000_f00253_ts1525172531/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180420_Background/series000/s000_f00254_ts1525176326/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180420_Background/series000/s000_f00255_ts1525179987/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00000_ts1525183676/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00001_ts1525187324/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00002_ts1525191006/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00003_ts1525194625/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00004_ts1525198244/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00005_ts1525201929/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00006_ts1525205549/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00007_ts1525209622/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00008_ts1525213831/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00009_ts1525217497/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00010_ts1525221117/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00011_ts1525224840/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00012_ts1525228463/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00013_ts1525232083/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00014_ts1525235766/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00015_ts1525239419/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00016_ts1525243071/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00017_ts1525246757/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00018_ts1525250442/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00019_ts1525254156/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00020_ts1525257807/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00021_ts1525261577/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00022_ts1525265231/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00023_ts1525268848/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00024_ts1525272498/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00025_ts1525276265/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00026_ts1525279884/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00027_ts1525283570/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00028_ts1525287189/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00029_ts1525290880/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00030_ts1525294502/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00031_ts1525298123/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00032_ts1525301743/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00033_ts1525305431/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00034_ts1525309049/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00035_ts1525312701/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00036_ts1525316558/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00037_ts1525320283/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00038_ts1525324056/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00039_ts1525327675/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00040_ts1525331293/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00041_ts1525334995/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00042_ts1525338737/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00043_ts1525342356/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00044_ts1525346043/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00045_ts1525349855/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00046_ts1525353584/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00047_ts1525357272/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00048_ts1525360927/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00049_ts1525364618/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series000/s000_f00050_ts1525368239/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00000_ts1525370836/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00001_ts1525374560/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00002_ts1525378252/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00003_ts1525381904/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00004_ts1525385553/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00005_ts1525389240/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00006_ts1525392895/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00007_ts1525396545/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00008_ts1525400162/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00009_ts1525403855/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00010_ts1525407508/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00011_ts1525411207/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00012_ts1525414858/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00013_ts1525418505/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00014_ts1525422428/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00016_ts1525426810/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00017_ts1525430437/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00018_ts1525434054/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00019_ts1525437750/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00020_ts1525441370/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00021_ts1525444989/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00022_ts1525448607/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00023_ts1525452369/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00024_ts1525455986/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00025_ts1525459639/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00026_ts1525463262/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00027_ts1525467125/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00028_ts1525470855/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00029_ts1525474476/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00030_ts1525478093/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00031_ts1525481746/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00032_ts1525485368/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00033_ts1525488988/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00034_ts1525492610/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00035_ts1525496231/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00036_ts1525499992/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00037_ts1525503751/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00038_ts1525507471/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00039_ts1525511225/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00040_ts1525515052/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00041_ts1525518818/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00042_ts1525522440/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00043_ts1525526056/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00044_ts1525529706/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00045_ts1525533326/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00046_ts1525537079/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00047_ts1525540854/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00048_ts1525544473/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00049_ts1525548090/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00050_ts1525551744/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00051_ts1525555364/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00052_ts1525558983/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00053_ts1525562637/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00054_ts1525566258/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00055_ts1525569952/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00056_ts1525573608/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00057_ts1525577226/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00058_ts1525580947/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00059_ts1525584567/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00060_ts1525588186/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00061_ts1525591808/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00063_ts1525599200/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00064_ts1525602855/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00065_ts1525606475/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00066_ts1525610093/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00067_ts1525613715/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00068_ts1525617366/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00069_ts1525620987/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00070_ts1525624605/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00071_ts1525628369/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00072_ts1525632019/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00073_ts1525635636/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00074_ts1525639287/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00075_ts1525642904/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00076_ts1525646560/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00077_ts1525650179/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00078_ts1525653963/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00079_ts1525657694/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00080_ts1525661312/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00081_ts1525664929/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00082_ts1525668621/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00083_ts1525672352/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00084_ts1525676004/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00085_ts1525679622/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00086_ts1525683317/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00087_ts1525686940/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00088_ts1525690558/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00089_ts1525694178/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00090_ts1525698036/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00091_ts1525701658/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00092_ts1525705310/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00093_ts1525709009/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00094_ts1525712628/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00095_ts1525716245/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00096_ts1525719866/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00097_ts1525723486/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00098_ts1525727144/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00099_ts1525730866/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00100_ts1525734489/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00102_ts1525738671/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00103_ts1525742394/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00104_ts1525746058/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00105_ts1525749744/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00106_ts1525753398/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00107_ts1525757335/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00108_ts1525760951/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00110_ts1525768205/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00111_ts1525771869/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00112_ts1525775523/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00113_ts1525779145/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00114_ts1525782765/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00115_ts1525786419/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00116_ts1525790074/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00117_ts1525793728/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00118_ts1525797412/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00119_ts1525801033/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00120_ts1525804656/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00121_ts1525808274/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00122_ts1525811931/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00123_ts1525815624/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00124_ts1525819244/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00125_ts1525822984/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00127_ts1525830238/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00128_ts1525833859/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00129_ts1525837614/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00130_ts1525841307/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00131_ts1525845106/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00132_ts1525848786/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00133_ts1525852443/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00134_ts1525856064/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00135_ts1525859850/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00136_ts1525863472/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00137_ts1525867128/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00138_ts1525870744/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00139_ts1525874612/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00140_ts1525878233/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00141_ts1525881926/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00142_ts1525885578/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00143_ts1525889234/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00144_ts1525892996/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00145_ts1525896648/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00146_ts1525900303/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00147_ts1525903957/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00148_ts1525907644/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00149_ts1525911265/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00150_ts1525914925/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00151_ts1525918545/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00152_ts1525922200/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00153_ts1525925821/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00154_ts1525929535/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00155_ts1525933388/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00156_ts1525937081/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00157_ts1525940698/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00158_ts1525944318/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00159_ts1525947971/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00160_ts1525951661/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00161_ts1525955279/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00162_ts1525958898/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00163_ts1525962516/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00164_ts1525966201/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00165_ts1525969859/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00166_ts1525973482/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00167_ts1525977170/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00168_ts1525980824/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00169_ts1525984447/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00170_ts1525988236/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00171_ts1525989044/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00172_ts1525990019/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00173_ts1525993755/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00174_ts1525997376/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00175_ts1526000997/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00176_ts1526004616/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00177_ts1526008304/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00178_ts1526011959/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00179_ts1526015608/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00180_ts1526019266/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00182_ts1526026560/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00183_ts1526030203/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00184_ts1526033824/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00185_ts1526037566/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00186_ts1526041186/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00187_ts1526044807/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00188_ts1526048458/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00189_ts1526052115/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00190_ts1526055735/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00191_ts1526056357/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00192_ts1526060300/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00193_ts1526063915/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00194_ts1526067567/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00195_ts1526071187/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00196_ts1526074803/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00197_ts1526078485/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00198_ts1526082135/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00199_ts1526085753/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00200_ts1526089475/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00201_ts1526093097/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00202_ts1526096847/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00203_ts1526100577/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00204_ts1526104260/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00205_ts1526107971/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00206_ts1526111590/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00207_ts1526115208/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00208_ts1526118826/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00209_ts1526122442/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00210_ts1526126199/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00211_ts1526129898/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00212_ts1526133579/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00213_ts1526137196/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00214_ts1526140844/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00215_ts1526144520/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00216_ts1526148198/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00217_ts1526151852/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00218_ts1526155509/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00219_ts1526159198/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00220_ts1526162852/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00221_ts1526166531/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00222_ts1526170152/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00223_ts1526173769/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00224_ts1526177425/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00225_ts1526181043/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00226_ts1526184665/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00227_ts1526188517/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00228_ts1526192163/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00229_ts1526195844/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00230_ts1526199462/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00231_ts1526203084/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00232_ts1526206701/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00233_ts1526210316/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00234_ts1526213963/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00235_ts1526217578/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00236_ts1526221226/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00237_ts1526224844/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00238_ts1526228463/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00239_ts1526232078/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00240_ts1526235696/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00241_ts1526239315/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00242_ts1526242934/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00243_ts1526246582/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00244_ts1526250295/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00245_ts1526253947/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00246_ts1526257572/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00247_ts1526261220/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00248_ts1526264902/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00249_ts1526268750/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00250_ts1526272370/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00251_ts1526275985/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00252_ts1526279641/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00253_ts1526283258/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00254_ts1526287006/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00255_ts1526290624/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00256_ts1526294239/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00257_ts1526297981/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00258_ts1526301729/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00259_ts1526305354/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00260_ts1526309082/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00261_ts1526312731/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00262_ts1526316385/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series001/s001_f00263_ts1526320097/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00000_ts1526340755/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00001_ts1526344409/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00002_ts1526348061/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00003_ts1526351849/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00004_ts1526355608/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00005_ts1526359223/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00006_ts1526362902/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00007_ts1526366664/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00008_ts1526370281/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00009_ts1526373932/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00010_ts1526377552/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00011_ts1526381235/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00012_ts1526384854/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00013_ts1526388506/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00014_ts1526392123/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00015_ts1526395772/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00016_ts1526399390/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00017_ts1526403075/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00018_ts1526406723/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00019_ts1526410343/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00020_ts1526413992/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00021_ts1526417711/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00022_ts1526421396/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00023_ts1526425051/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00024_ts1526428702/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00025_ts1526432320/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00026_ts1526435969/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00027_ts1526439780/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00028_ts1526443401/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00029_ts1526447052/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00030_ts1526450668/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00031_ts1526454284/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00032_ts1526457933/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00033_ts1526461611/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00034_ts1526465228/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00035_ts1526468847/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00036_ts1526472594/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00037_ts1526476211/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00038_ts1526479862/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00039_ts1526483477/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00040_ts1526487157/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00041_ts1526490943/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00042_ts1526494596/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00043_ts1526498212/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00044_ts1526501856/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series002/s002_f00045_ts1526505475/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00000_ts1526507152/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00001_ts1526511076/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00002_ts1526514753/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00003_ts1526518369/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00004_ts1526522053/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00005_ts1526525704/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00006_ts1526529358/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00007_ts1526532975/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00008_ts1526536591/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00009_ts1526540208/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00010_ts1526543825/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00011_ts1526547443/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00012_ts1526551094/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00013_ts1526554713/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00014_ts1526558331/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00015_ts1526561984/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00016_ts1526565606/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00017_ts1526569223/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00018_ts1526572840/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00019_ts1526576523/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00020_ts1526580176/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00021_ts1526583793/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00022_ts1526587579/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00023_ts1526591261/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00024_ts1526595005/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00025_ts1526598621/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00026_ts1526602242/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00027_ts1526605988/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00028_ts1526609829/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00029_ts1526613477/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00030_ts1526617133/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00031_ts1526620753/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00032_ts1526624371/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00033_ts1526628094/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00034_ts1526631847/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00035_ts1526635466/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00036_ts1526639145/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00037_ts1526642796/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00038_ts1526646441/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00039_ts1526650313/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00040_ts1526653929/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00041_ts1526657574/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00042_ts1526661197/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00043_ts1526664945/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00044_ts1526668562/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00045_ts1526672182/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00046_ts1526675861/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00047_ts1526679544/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00048_ts1526683193/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00049_ts1526686840/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00050_ts1526690525/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00051_ts1526694268/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00052_ts1526697921/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00053_ts1526701537/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00054_ts1526705152/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00055_ts1526708771/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00056_ts1526712556/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00057_ts1526716170/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00058_ts1526719822/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00059_ts1526723441/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00060_ts1526727125/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00061_ts1526730810/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00062_ts1526734521/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00063_ts1526738139/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00064_ts1526741825/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00065_ts1526745544/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00066_ts1526749286/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00067_ts1526752903/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00068_ts1526756519/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00069_ts1526760203/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00070_ts1526764071/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00071_ts1526767687/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00072_ts1526771379/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00073_ts1526774999/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00074_ts1526778685/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00075_ts1526782509/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00076_ts1526786124/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00077_ts1526789739/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00078_ts1526793390/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00079_ts1526797044/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00080_ts1526800664/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00081_ts1526804308/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00082_ts1526807924/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00083_ts1526811648/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00084_ts1526815268/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00085_ts1526819014/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00086_ts1526822633/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00087_ts1526826316/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00088_ts1526829938/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00089_ts1526833586/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00090_ts1526837203/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00091_ts1526840853/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00092_ts1526844505/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00093_ts1526848356/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00094_ts1526852101/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00095_ts1526855719/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00096_ts1526859338/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00097_ts1526862954/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00098_ts1526866707/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00099_ts1526870323/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00100_ts1526873981/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00101_ts1526877631/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00102_ts1526881411/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00103_ts1526885029/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00104_ts1526888703/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00105_ts1526892323/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00106_ts1526896142/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00107_ts1526899792/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00108_ts1526903445/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00109_ts1526907195/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00110_ts1526910846/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00111_ts1526914524/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00112_ts1526918139/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00113_ts1526921761/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00114_ts1526925380/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00115_ts1526929033/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00116_ts1526932649/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00117_ts1526936299/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00118_ts1526939951/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00119_ts1526943603/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00120_ts1526947218/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00121_ts1526950834/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00122_ts1526954546/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00123_ts1526958166/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00124_ts1526961788/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00125_ts1526965443/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00126_ts1526969167/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00127_ts1526972880/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00128_ts1526976501/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00129_ts1526980121/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00130_ts1526983833/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00131_ts1526987454/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00132_ts1526991111/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00133_ts1526994764/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00134_ts1526998446/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00135_ts1527002064/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00136_ts1527005681/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00137_ts1527009296/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00138_ts1527012916/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00139_ts1527016536/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00140_ts1527020184/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00141_ts1527023867/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00142_ts1527027684/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00143_ts1527031331/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00144_ts1527035052/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00145_ts1527038671/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00146_ts1527042347/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00147_ts1527046033/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00148_ts1527049652/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00149_ts1527053274/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00150_ts1527056929/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00151_ts1527060546/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00152_ts1527064166/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00153_ts1527067851/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00154_ts1527071574/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00155_ts1527075288/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00156_ts1527078909/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00157_ts1527082565/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00158_ts1527086215/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00159_ts1527089834/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00160_ts1527093481/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00161_ts1527097098/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00162_ts1527100811/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00163_ts1527104526/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00164_ts1527108143/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00165_ts1527111763/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00166_ts1527115380/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00167_ts1527118998/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00168_ts1527122645/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00169_ts1527126297/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00170_ts1527129914/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00171_ts1527133788/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00172_ts1527137407/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00173_ts1527141031/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00174_ts1527144650/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00175_ts1527148302/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00176_ts1527151918/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00177_ts1527155538/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00178_ts1527159258/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00179_ts1527163187/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00180_ts1527166872/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00181_ts1527170491/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00182_ts1527174199/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00183_ts1527177915/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00184_ts1527181630/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00185_ts1527185249/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00186_ts1527188865/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00187_ts1527192483/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00188_ts1527196171/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00190_ts1527203561/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00191_ts1527207315/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00192_ts1527211031/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00193_ts1527214706/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00194_ts1527218386/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00195_ts1527222061/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00196_ts1527225778/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00197_ts1527229400/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00198_ts1527233019/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00199_ts1527236636/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00200_ts1527240253/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Analyzed_NuFact_v1/180501_ReactorOn/series004/s004_f00201_ts1527243901/AD1_Wet_Phys.root/P2kIBDPlugin/Tibd");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

IBDon::~IBDon()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t IBDon::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t IBDon::LoadTree(Long64_t entry)
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

void IBDon::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evt", &evt, &b_evt);
   fChain->SetBranchAddress("t_abs", &t_abs, &b_t_abs);
   fChain->SetBranchAddress("Encapt", &Encapt, &b_Encapt);
   fChain->SetBranchAddress("E", &E, &b_E);
   fChain->SetBranchAddress("Esmear", &Esmear, &b_Esmear);
   fChain->SetBranchAddress("maxseg", &maxseg, &b_maxseg);
   fChain->SetBranchAddress("xyz", xyz, &b_xyz);
   fChain->SetBranchAddress("E_maxseg", &E_maxseg, &b_E_maxseg);
   fChain->SetBranchAddress("E_adjacent", &E_adjacent, &b_E_adjacent);
   fChain->SetBranchAddress("ncapt_psd", &ncapt_psd, &b_ncapt_psd);
   fChain->SetBranchAddress("prompt_psd", &prompt_psd, &b_prompt_psd);
   fChain->SetBranchAddress("segmult", &segmult, &b_segmult);
   fChain->SetBranchAddress("diameter", &diameter, &b_diameter);
   fChain->SetBranchAddress("tspread", &tspread, &b_tspread);
   fChain->SetBranchAddress("ncapt_dt", &ncapt_dt, &b_ncapt_dt);
   fChain->SetBranchAddress("n_seg", &n_seg, &b_n_seg);
   fChain->SetBranchAddress("n_xyz", n_xyz, &b_n_xyz);
   fChain->SetBranchAddress("veto_t", &veto_t, &b_veto_t);
   fChain->SetBranchAddress("cut", &cut, &b_cut);
   fChain->SetBranchAddress("detgeom", &detgeom, &b_detgeom);
   fChain->SetBranchAddress("rxpwr", &rxpwr, &b_rxpwr);
   Notify();
}

Bool_t IBDon::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void IBDon::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t IBDon::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef IBDon_cxx
