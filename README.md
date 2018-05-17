# BiPoAnalysis
Code to manipulate and plot BiPo events in PROSPECT
Every time I run over the data using the plugin framework from P2X I give the
new pass a name in the form pass<_myname>. This "pass name" <_myname>, along with the Physics release uniquely identifies the data set.
To make BiPo analysis plots

1. Need to set the following environment variables:
BIPO_OUTDIR to location of BiPo physics release directories
  eg. export BIPO_OUTDIR=home/jonesdc/prospect/bipo_data/

2. Ensure that the root trees exist. If not copy them from Wright using 

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

4. Now make plots using BiPoPlotter.C and BiPovsTime.C