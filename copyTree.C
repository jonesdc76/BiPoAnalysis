#include "TFile.h"
#include "TTree.h"

void copyTree(const char *infname, const char *outfname) {

   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile(infname);
   TTree *oldtree = (TTree*)oldfile->Get("BiPoTreePlugin/BiPo");

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile(outfname,"recreate");
   TTree *newtree = oldtree->CloneTree();

   newtree->Print();
   newfile->Write();
   delete oldfile;
   delete newfile;
}
