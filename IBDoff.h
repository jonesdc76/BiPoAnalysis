//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 22 14:04:19 2018 by ROOT version 6.13/01
// from TChain P2kIBDPlugin/Tibd/
//////////////////////////////////////////////////////////

#ifndef IBDoff_h
#define IBDoff_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class IBDoff {
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

   IBDoff(TTree *tree=0);
   virtual ~IBDoff();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef IBDoff_cxx
IBDoff::IBDoff(TTree *tree) : fChain(0) 
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
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00000_ts1521211900/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00001_ts1521215519/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00002_ts1521219136/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00003_ts1521222821/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00004_ts1521226440/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00005_ts1521230059/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00006_ts1521233681/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00007_ts1521237303/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00008_ts1521240958/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00009_ts1521244577/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00010_ts1521248230/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00011_ts1521248613/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00012_ts1521252233/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00013_ts1521255851/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00014_ts1521259475/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00015_ts1521263093/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00016_ts1521266713/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00017_ts1521270336/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00018_ts1521274044/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00019_ts1521277696/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00020_ts1521281481/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00021_ts1521285100/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series000/s000_f00022_ts1521288717/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00000_ts1521292190/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00001_ts1521295807/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00002_ts1521299456/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00003_ts1521303074/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00004_ts1521306732/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00005_ts1521310386/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00006_ts1521314038/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00007_ts1521317659/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00008_ts1521321279/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00009_ts1521324897/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00010_ts1521328514/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00011_ts1521332128/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00012_ts1521335861/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00013_ts1521339480/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00014_ts1521343242/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00015_ts1521346859/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00016_ts1521350477/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00017_ts1521354097/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00018_ts1521357713/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00019_ts1521361333/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00020_ts1521364952/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00021_ts1521368694/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00022_ts1521372410/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00023_ts1521376030/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00024_ts1521379683/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00025_ts1521383303/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00026_ts1521386958/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00027_ts1521390576/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00028_ts1521394263/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00029_ts1521397911/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00030_ts1521401600/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00031_ts1521405250/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00032_ts1521408967/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00033_ts1521412682/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00034_ts1521416401/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00035_ts1521420083/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00036_ts1521423699/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00037_ts1521427317/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00038_ts1521430938/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00039_ts1521434621/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00040_ts1521438306/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00041_ts1521441922/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00042_ts1521445642/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00043_ts1521449362/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00044_ts1521452998/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00045_ts1521456688/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00046_ts1521460338/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00047_ts1521464027/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00048_ts1521467679/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00049_ts1521471299/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00050_ts1521475011/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00051_ts1521478634/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00052_ts1521482278/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00053_ts1521485957/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00054_ts1521489577/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00055_ts1521493194/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00056_ts1521496856/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00057_ts1521500575/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00058_ts1521504327/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00059_ts1521508046/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00060_ts1521511664/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00061_ts1521515414/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00062_ts1521519029/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00063_ts1521522681/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00064_ts1521526366/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00065_ts1521529982/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00066_ts1521533748/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00067_ts1521537500/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00068_ts1521541151/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00069_ts1521544770/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00070_ts1521548486/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00071_ts1521552101/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00072_ts1521555754/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00073_ts1521559372/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00074_ts1521562993/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00075_ts1521566645/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00076_ts1521570268/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00077_ts1521574005/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00078_ts1521577668/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00079_ts1521581330/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00080_ts1521584991/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00081_ts1521588612/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00082_ts1521592267/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00083_ts1521595884/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00084_ts1521599534/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00085_ts1521603206/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00086_ts1521606860/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00087_ts1521610483/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00088_ts1521614136/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00089_ts1521617790/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00090_ts1521621464/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00091_ts1521625114/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00092_ts1521628767/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00093_ts1521632491/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00094_ts1521636180/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00095_ts1521639797/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00096_ts1521643515/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00097_ts1521647172/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00098_ts1521650857/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00099_ts1521654506/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00100_ts1521658125/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00101_ts1521661867/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00102_ts1521665664/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00103_ts1521669283/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00104_ts1521672983/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00105_ts1521676602/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00106_ts1521680286/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00107_ts1521683907/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00108_ts1521687529/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00109_ts1521691241/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00110_ts1521694971/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00111_ts1521698593/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00112_ts1521702209/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00113_ts1521705939/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00114_ts1521709595/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00115_ts1521713211/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00116_ts1521716865/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00117_ts1521720481/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00118_ts1521724168/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00119_ts1521727822/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00120_ts1521731466/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00121_ts1521735162/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00122_ts1521738784/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00123_ts1521742406/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00124_ts1521746024/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00125_ts1521749676/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00126_ts1521753465/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00127_ts1521757124/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00128_ts1521761047/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00129_ts1521764670/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00130_ts1521768434/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00131_ts1521772081/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00132_ts1521775732/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00133_ts1521779350/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00134_ts1521782999/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00135_ts1521786655/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00136_ts1521790276/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00137_ts1521793926/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00138_ts1521797577/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00139_ts1521801234/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00140_ts1521804851/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00141_ts1521808563/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00142_ts1521812294/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00143_ts1521815976/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00144_ts1521819631/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00145_ts1521823247/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00146_ts1521826898/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00147_ts1521830782/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00148_ts1521834430/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00149_ts1521838092/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00150_ts1521841709/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00151_ts1521845401/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00152_ts1521849020/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00153_ts1521852794/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00154_ts1521856414/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00155_ts1521860210/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00156_ts1521863832/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00157_ts1521867514/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00158_ts1521871134/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00159_ts1521874819/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00160_ts1521878504/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00161_ts1521882124/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00162_ts1521885739/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00163_ts1521889452/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00164_ts1521893213/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00165_ts1521896834/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00166_ts1521900449/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00167_ts1521904069/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00168_ts1521907782/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00169_ts1521909739/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series002/s002_f00001_ts1521910199/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00170_ts1521913931/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series002/s002_f00002_ts1521917597/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series002/s002_f00003_ts1521921213/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00171_ts1521924828/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00172_ts1521928475/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00173_ts1521932096/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00174_ts1521935980/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00175_ts1521939632/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00176_ts1521943282/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00177_ts1521946931/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00178_ts1521950547/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00179_ts1521954193/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00180_ts1521957854/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00181_ts1521961543/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00182_ts1521965308/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00183_ts1521968995/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00184_ts1521972652/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00185_ts1521976271/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00186_ts1521980013/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00187_ts1521983633/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00188_ts1521987284/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00189_ts1521990933/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00190_ts1521994587/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00191_ts1521998275/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00192_ts1522002043/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00193_ts1522005765/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00194_ts1522009462/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00195_ts1522013106/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00196_ts1522016789/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00197_ts1522020501/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00198_ts1522024211/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00199_ts1522027828/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00200_ts1522031922/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00201_ts1522035805/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00202_ts1522039455/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00203_ts1522043170/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00204_ts1522046883/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00205_ts1522050503/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00206_ts1522054157/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00207_ts1522057775/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00208_ts1522061392/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00209_ts1522065012/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00210_ts1522068658/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00211_ts1522072338/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00212_ts1522075954/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00213_ts1522079569/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00214_ts1522083252/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00215_ts1522086966/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00216_ts1522090746/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00217_ts1522094430/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00218_ts1522098048/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00219_ts1522101699/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00220_ts1522105320/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00221_ts1522108973/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00222_ts1522112817/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00223_ts1522116436/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00224_ts1522120084/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00225_ts1522123701/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00226_ts1522127350/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00227_ts1522131034/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00228_ts1522134780/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00229_ts1522138397/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00230_ts1522142018/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00231_ts1522145737/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00232_ts1522149495/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00233_ts1522153232/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00234_ts1522156917/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00235_ts1522160533/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00236_ts1522164189/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00237_ts1522167809/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00238_ts1522171425/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00239_ts1522175080/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00240_ts1522178702/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00241_ts1522182318/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00242_ts1522185939/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00243_ts1522189625/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00244_ts1522191724/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00245_ts1522195517/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00246_ts1522199390/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00247_ts1522203110/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00248_ts1522206730/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00249_ts1522210377/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00250_ts1522214089/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00251_ts1522217738/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00252_ts1522221390/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00253_ts1522225042/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00254_ts1522228693/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00255_ts1522232309/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00256_ts1522235988/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00257_ts1522239607/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00258_ts1522243221/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00259_ts1522246902/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00260_ts1522250629/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00261_ts1522254251/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180316_Background/series001/s001_f00262_ts1522257997/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00003_ts1524021346/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00004_ts1524021591/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00005_ts1524025242/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00006_ts1524028859/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00007_ts1524032479/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00008_ts1524036099/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00009_ts1524039745/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00010_ts1524043364/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00011_ts1524047049/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180417_Background/series000/s000_f00012_ts1524050665/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00000_ts1524244664/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00001_ts1524248317/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00002_ts1524251999/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00003_ts1524255614/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00004_ts1524259369/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00005_ts1524263267/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00006_ts1524266918/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00007_ts1524270537/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00008_ts1524274153/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00009_ts1524277901/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00010_ts1524281550/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00011_ts1524285206/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00012_ts1524288852/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00013_ts1524292468/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00014_ts1524296181/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00015_ts1524299799/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00016_ts1524303494/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00017_ts1524307110/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00018_ts1524310763/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00019_ts1524314445/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00020_ts1524318128/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00021_ts1524321770/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00022_ts1524325390/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00023_ts1524329010/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00024_ts1524332665/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00025_ts1524336308/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00026_ts1524339927/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00027_ts1524343545/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00028_ts1524347199/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00029_ts1524350857/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00030_ts1524354472/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00031_ts1524358219/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00032_ts1524361939/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00033_ts1524365601/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00034_ts1524369254/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00035_ts1524372901/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00036_ts1524376552/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00037_ts1524380168/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00038_ts1524383918/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00039_ts1524387538/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00040_ts1524391155/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00041_ts1524394771/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00042_ts1524398520/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00043_ts1524402137/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00044_ts1524405785/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00045_ts1524409437/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00046_ts1524413057/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00047_ts1524416676/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00048_ts1524420323/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00049_ts1524424066/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00050_ts1524427696/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00051_ts1524431316/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00052_ts1524434937/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00053_ts1524438588/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00054_ts1524442206/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00055_ts1524445860/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00056_ts1524449477/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00057_ts1524453130/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00058_ts1524456784/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00059_ts1524460437/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00060_ts1524464088/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00061_ts1524467708/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00062_ts1524471425/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00063_ts1524475147/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00064_ts1524478795/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00065_ts1524482444/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00066_ts1524486101/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00067_ts1524489719/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00068_ts1524493335/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00069_ts1524496987/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00070_ts1524500641/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00071_ts1524504528/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00072_ts1524508309/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00073_ts1524511993/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00074_ts1524515681/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00075_ts1524519303/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00076_ts1524522952/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00077_ts1524526571/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00078_ts1524530292/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00079_ts1524534011/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00080_ts1524537632/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00081_ts1524541252/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00082_ts1524544902/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00083_ts1524548578/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00084_ts1524552194/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00085_ts1524555814/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00086_ts1524559604/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00087_ts1524563223/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00088_ts1524567004/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00089_ts1524571109/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00090_ts1524574727/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00091_ts1524578379/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00092_ts1524581997/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00093_ts1524585616/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00094_ts1524589234/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00095_ts1524592918/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00096_ts1524596539/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00097_ts1524600228/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00098_ts1524603843/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00099_ts1524607463/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00100_ts1524611080/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00101_ts1524614700/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00102_ts1524618318/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00103_ts1524621970/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00104_ts1524625622/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00105_ts1524629276/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00106_ts1524632955/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00107_ts1524636573/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00108_ts1524640192/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00109_ts1524643808/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00110_ts1524647461/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00111_ts1524651112/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00112_ts1524654829/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00113_ts1524658511/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00114_ts1524662164/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00115_ts1524665783/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00116_ts1524669462/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00117_ts1524673119/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00118_ts1524676734/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00119_ts1524680418/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00120_ts1524684111/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00121_ts1524687827/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00122_ts1524691480/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00123_ts1524695099/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00124_ts1524698719/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00125_ts1524702369/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00126_ts1524705991/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00127_ts1524709610/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00128_ts1524713229/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00129_ts1524716883/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00130_ts1524720503/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00131_ts1524724286/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00132_ts1524727903/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00133_ts1524731526/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00134_ts1524735243/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00135_ts1524738889/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00136_ts1524742541/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00137_ts1524746423/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00138_ts1524750144/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00139_ts1524753792/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00140_ts1524757660/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00141_ts1524761403/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00142_ts1524765049/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00143_ts1524768669/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00144_ts1524772288/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00145_ts1524775937/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00146_ts1524779757/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00147_ts1524783409/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00148_ts1524787027/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00149_ts1524790644/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00150_ts1524794291/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00151_ts1524797909/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00152_ts1524801661/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00153_ts1524805310/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00154_ts1524808928/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00155_ts1524812578/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00156_ts1524816234/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00157_ts1524819954/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00158_ts1524823572/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00159_ts1524827220/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00160_ts1524830864/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00161_ts1524834486/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00162_ts1524838263/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00163_ts1524841879/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00164_ts1524845500/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00165_ts1524849192/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00166_ts1524852878/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00167_ts1524856497/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00168_ts1524860115/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00169_ts1524863731/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00170_ts1524867429/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00171_ts1524871054/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00172_ts1524874709/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00173_ts1524878331/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00174_ts1524881951/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00175_ts1524885652/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00176_ts1524889278/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00177_ts1524892930/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00178_ts1524896545/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00179_ts1524900325/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00180_ts1524903944/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00181_ts1524907563/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00182_ts1524911181/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00183_ts1524914801/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00184_ts1524918524/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00185_ts1524922317/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00186_ts1524926007/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00187_ts1524929797/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00188_ts1524933478/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00189_ts1524937200/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00190_ts1524940853/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00191_ts1524944510/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00192_ts1524948165/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00193_ts1524951992/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00194_ts1524955646/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00195_ts1524959297/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00196_ts1524963014/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00197_ts1524966735/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00198_ts1524970356/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00199_ts1524974702/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00200_ts1524978422/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00201_ts1524982078/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00202_ts1524985695/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00203_ts1524989315/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00204_ts1524993060/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00205_ts1524996675/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00206_ts1525000291/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00207_ts1525003945/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00208_ts1525007563/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00209_ts1525011286/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00210_ts1525014936/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00211_ts1525018559/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00212_ts1525022243/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00213_ts1525026007/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00214_ts1525029627/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00215_ts1525033247/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00216_ts1525036895/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00217_ts1525040513/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00218_ts1525044265/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00219_ts1525047886/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00220_ts1525051507/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00221_ts1525055128/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00222_ts1525058749/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00223_ts1525062498/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00224_ts1525066155/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00225_ts1525069771/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00226_ts1525073467/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00227_ts1525077224/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00228_ts1525080840/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00229_ts1525084458/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00230_ts1525088075/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00231_ts1525091695/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00232_ts1525095382/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00233_ts1525099135/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00234_ts1525102840/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00235_ts1525106523/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00236_ts1525110170/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00237_ts1525113788/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00238_ts1525117438/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00239_ts1525121091/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00240_ts1525124893/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00241_ts1525128546/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00242_ts1525132201/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00243_ts1525135823/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00244_ts1525139467/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00245_ts1525143088/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00246_ts1525146708/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00247_ts1525150328/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00248_ts1525153974/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00249_ts1525157591/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00250_ts1525161271/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00251_ts1525164995/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00252_ts1525168849/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00253_ts1525172531/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00254_ts1525176326/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180420_Background/series000/s000_f00255_ts1525179987/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00000_ts1527246158/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00001_ts1527249776/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00002_ts1527253433/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00003_ts1527257058/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00004_ts1527260708/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00005_ts1527264323/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00006_ts1527267973/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00007_ts1527271619/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00008_ts1527275338/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00009_ts1527278954/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00010_ts1527282679/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00011_ts1527286299/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00012_ts1527289915/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00013_ts1527293565/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00014_ts1527297216/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00015_ts1527300938/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00016_ts1527304554/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00017_ts1527308173/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00018_ts1527311793/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00019_ts1527315469/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00020_ts1527319152/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00021_ts1527322805/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00022_ts1527326428/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00023_ts1527330047/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00024_ts1527333697/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00025_ts1527337501/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00026_ts1527341121/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00027_ts1527344774/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00028_ts1527348520/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00029_ts1527352137/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00030_ts1527355756/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00031_ts1527359413/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00032_ts1527363031/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00033_ts1527366714/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00034_ts1527370391/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00035_ts1527374104/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00036_ts1527377721/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00037_ts1527381337/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00038_ts1527384954/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00039_ts1527388607/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00040_ts1527392227/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00041_ts1527395845/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00042_ts1527399467/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00043_ts1527403088/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00044_ts1527406769/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00045_ts1527410424/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00046_ts1527414071/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00047_ts1527417727/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00048_ts1527421415/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00049_ts1527425065/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00050_ts1527428682/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00051_ts1527432302/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00052_ts1527435921/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00053_ts1527439540/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00054_ts1527443253/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00055_ts1527446972/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00056_ts1527450592/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00057_ts1527454244/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00058_ts1527457861/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00059_ts1527461543/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00060_ts1527465157/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00061_ts1527468809/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00062_ts1527472426/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00063_ts1527476175/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00064_ts1527479854/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00065_ts1527483502/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00066_ts1527487117/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00067_ts1527490765/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00068_ts1527494381/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00069_ts1527498024/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00070_ts1527501646/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00071_ts1527505322/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00072_ts1527508974/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00073_ts1527512659/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00074_ts1527516282/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00075_ts1527519904/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00076_ts1527523521/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00077_ts1527527171/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00078_ts1527530821/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00079_ts1527534636/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00080_ts1527538321/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00081_ts1527541999/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00082_ts1527545616/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00083_ts1527549236/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00084_ts1527552854/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00085_ts1527556641/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00086_ts1527560259/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00087_ts1527563875/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00088_ts1527567527/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00089_ts1527571146/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00090_ts1527574829/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00091_ts1527578449/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00092_ts1527582167/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00093_ts1527585838/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00094_ts1527589511/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00095_ts1527593197/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00096_ts1527596849/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00097_ts1527600566/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00098_ts1527604215/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00099_ts1527607921/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00100_ts1527611638/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00101_ts1527615287/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00102_ts1527618973/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00103_ts1527622594/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00104_ts1527626244/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00105_ts1527629865/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00106_ts1527633618/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00107_ts1527637236/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00108_ts1527640979/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00109_ts1527644599/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00110_ts1527648218/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      chain->Add("file:///home/jonesdc/prospect/bipo_data//Phys_Neutrino_v2/180525_Background/series000/s000_f00111_ts1527651836/AD1_Wet_Phys_IBDwBiPo.root/P2kIBDPlugin/Tibd");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

IBDoff::~IBDoff()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t IBDoff::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t IBDoff::LoadTree(Long64_t entry)
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

void IBDoff::Init(TTree *tree)
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

Bool_t IBDoff::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void IBDoff::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t IBDoff::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef IBDoff_cxx
