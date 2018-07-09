#include "TFile.h"
#include "TTree.h"

void copyTree(const char *infname, const char *outfname, const char* treename= "BiPoTreePlugin/BiPo") {

   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile(infname);
   TTree *oldtree = (TTree*)oldfile->Get(treename);

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile(outfname,"recreate");
   TTree *newtree = oldtree->CloneTree();

   newtree->Print();
   newfile->Write();
   delete oldfile;
   delete newfile;
}
