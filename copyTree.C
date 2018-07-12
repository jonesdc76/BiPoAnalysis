#include "TFile.h"
#include "TTree.h"
#include "TVectorD.h"
#include "TDirectory.h"

void copyTree(const char *infname, const char *outfname, const char* treename= "BiPo", const char* plugin = "BiPoTreePlugin") {

   //Get old file, old tree and set top branch address
   TFile *oldfile = new TFile(infname);
   TString name(Form("%s/%s", plugin, treename));
   TTree *oldtree = (TTree*)oldfile->Get(name.Data());

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile(outfname, "recreate");
   TVectorD *runtime = (TVectorD*)oldfile->Get("runtime");
   runtime->Write("runtime");
   TDirectory *plugindir = newfile->mkdir(plugin);
   plugindir->cd();
   TTree *newtree = oldtree->CloneTree();
   newtree->Print();
   newfile->Write();
   delete oldfile;
   delete newfile;
}
