# BiPoAnalysis
BiPo analysis happens in two steps. First, a TTree of BiPo events is made for
each run in the selected data sets. This is done using the P2X PhysPulse plugin
framework. Second, the data in these TTrees is manipulated and plotted to obtain
interesting results.

**Make the BiPo TTrees
----------------------
This assumes that you have the P2X (PROSPECT2x_Analysis) framework installed and
working and the required environment variables set for P2X.
1. Make a config file in PROSPECT2X_Analysis/Analysis/AnalyzerConfig/. Copy the
configuration file "AD1_Wet_Phys.cfg" to AD1_Wet_Phys<_mypass>.cfg. Edit the
file to include the plugin "BiPoTreePlugin" and remove all other plugins. Note:
BiPoTreePlugin is not the same as BiPoPlugin. At the top of the config file
edit the line name = "AD1_Wet_Phys" to read name = "AD1_Wet_Phys<_mypassname>"

2. Set the following new environment variables:
P2X_ANALYSIS       set to the directory where physics releases are located
P2X_ANALYZED       set to the directory where data is to be stored
P2X_ANALYSIS_CODE  set to the "PROSPECT2X_ANALYSIS" directory

3.Pass over the data making the TTrees by running the script
runBiPoTreePlugin.sh. Edit the script directly to add or remove series from the
data to be analayzed and include the configuration file name suffix as an
argument. For example, if your configuration file is named
"AD1_Wet_Phys_BiPo.cfg", use the following command ./runBiPoTreePlugin.sh _BiPo
This will launch a batch of AnalyzeCalibrated jobs to extract BiPos from physics
data and copy the BiPo TTrees to a common named pass directory. The variables
"LAUNCH" and "COPY" inside this script should both set to 1 unless you only want
to use the runs included in the good runs list. If you want to use only the runs
in the good runs list (for example NeutrinoGoodRuns.txt in this Github repos),
then set COPY=0 and then run ./copy_good_runs.sh <_mypassname>


**Plot the BiPo events
----------------------
Every time I run over the data using the plugin framework from P2X I give the
new pass a name in the form pass<_myname>. This "pass name" <_myname>, along
with the Physics release uniquely identifies the data set.
To make BiPo analysis plots

1. Set the following environment variables:
BIPO_OUTDIR to location of BiPo physics release directories
  eg. export BIPO_OUTDIR=home/jonesdc/prospect/bipo_data/
BIPO_ANALYSIS      set to the "BiPoAnalysis" directory (Github repos directory)
  eg. export BIPO_OUTDIR=home/jonesdc/prospect/BiPoAnalysis/

2. Ensure that the root trees exist. If you are working on Wright go to step 4.
If you are working on your own machine, you can copy the TTrees using the
following script: 

copy_BiPo_pass.sh
Requires manual editing to set "release" = name of release and
"wright_dir" = directory on Wright where BiPo output files of a given pass live.
Copies everything in the release directory recursively.

3. Either a). Verify that all good runs exist using a file listing all good runs
              for a current physics release. Inside a ROOT session run
	      checkRunList.C. Edit this file to ensure the good
	      runs list and physics release are correct. If files are missing,
	      either create them or note that they are missing.
   OR     b). Make a run list file of all available runs. From the command line
   	      run ./make_runlist.sh. Edit this file to include all desired
	      series and to set the proper physics release. This will produce a
	      file called "runlist.txt" in the BiPoAnalysis directory.

4. Next make the BP class, a class that includes the full TChain of ROOT trees. Inside a ROOT session run the macro makeBiPoClassFromRunlist.C

Args: runlist file name  eg. NeutrinoGoodRuns.txt
      pass name          eg. _BiPoNeutrino_v2
      release name       eg. Phys_Neutrino_v2

If you have a good run list for the given physics release (preferred) use that
for the runlist file name. Otherwise, make a run list with the instructions in
step 3.

5. Now make plots inside a ROOT session using BiPoPlotter.C and BiPovsTime.C.
For both of these macros
The first argument "fiducialize" tells whether or not to include a fiducial cut.
The second argument "alpha_type" takes one of three values:
alpha_type==0 plot Bi214->Po214
alpha_type==1 plot Bi212->Po212
alpha_type==2 include both