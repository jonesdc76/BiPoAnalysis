# BiPoAnalysis
BiPo analysis happens in two steps. First, a TTree of BiPo events is made for
each run in the selected data sets. This is done using the P2X PhysPulse plugin
framework. Second, the data in these TTrees is manipulated and plotted to obtain
interesting results.

**Make the BiPo TTrees
----------------------
This assumes that you have the P2X (PROSPECT2x_Analysis) framework installed and
working and the required environment variables set for P2X. To make the TTrees
run the script runBiPoTreePlugin.sh. Edit the script directly to add or remove
series from the data to be analayzed.
This will launch a batch of AnalyzeCalibrated jobs to extract BiPos from physics
data and copy the BiPo TTrees to a common named pass directory
It requires that the following new environ-ment variables be set:
P2X_ANALYSIS to be set to the dir where releases are located 
P2X_ANALYZED to be set to the dir where data is to be stored
P2X_ANALYSIS_CODE to be set to the "PROSPECT2X_ANALYSIS" dir


**Plot the BiPo events
----------------------
Every time I run over the data using the plugin framework from P2X I give the
new pass a name in the form pass<_myname>. This "pass name" <_myname>, along with the Physics release uniquely identifies the data set.
To make BiPo analysis plots

1. Need to set the following environment variables:
BIPO_OUTDIR to location of BiPo physics release directories
  eg. export BIPO_OUTDIR=home/jonesdc/prospect/bipo_data/

2. Ensure that the root trees exist. If you are working on Wright, skip this
step. If you are working locally, you can copy the TTrees using the following
script: 

copy_pass_from_Yale.sh
Args: pass name     eg. _BiPo5
Requires manual editing to set "release" = name of release and "dir" = directory
on Wright where files of a given pass are stored.
Requires manual editing of "series" array to include or exclude data sets

3. Next make the BP class, a class that includes the full TChain of ROOT trees
using
makeBiPoClass.C
Args: pass name     eg. _BiPo5 and
      release name  eg. Phys_20180510
Requires manual editing to add all desired data sets to TChain

4. Now make plots inside a ROOT session using BiPoPlotter.C and BiPovsTime.C