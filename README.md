# BiPoAnalysis +  Technote plot generation
BiPo analysis happens in two steps. First, a TTree of BiPo events is made for
each run in the selected data sets. This is done using the P2X PhysPulse plugin
framework. Second, the data in these TTrees is manipulated and plotted to obtain
interesting results. Many of the generated plots automatically repopulate an 
already generated technote with the latest results.
# BiPoSimulation
In addition to data analysis there are also scripts for producing a Bi214 beta
spectrum from PG4 simulation

**Make the BiPo TTrees
----------------------
This assumes that you have the P2X (PROSPECT2x_Analysis) framework installed and
working and the required environment variables set for P2X and that you are 
running on Borax at LLNL. It also assumes that you have PG4 installed.

1. Make sure a configuration file is up to data. It can be found on the Github at
PROSPECT2X_Analysis/Analysis/AnalyzerConfig/AD1_BiPo.cfg. Up to date means that the
"resSmear", "trigThresh" and "exclude" variables match those in the production IBD
configuration file "AD1_Production_Phys.cfg" 

2. Make sure the following environment variables are set:
P2X_ANALYSIS_CODE  set to the "PROSPECT2x_ANALYSIS" directory
P2X_BUILD          set to directory where PROSPECT2x_ANALYSIS executable lives
P2X_ANALYZED       set to your personal directory where you want ROOT Trees
                     eg. /p/lustre2/psptexp/user/<username>/data/Analyzed/
P2X_DATA           set to the converted data directory 
	             eg. /p/lustre2/psptexp/converted

3.Pass over the data making the TTrees by running the script
RunAnalysisPass.sh. Edit PHYSRELEASE found on line 33 of the script to point to the
current physics release number/name. This script will automatically run over all 
files by looking for the automatically generated file "all_runs.txt".

** Optional copy trees to personal computer
-------------------------------------------
The trees are small enough that they can be copied to your personal computer.
If you do this, then build the BiPoAnalysis code on your own computer as well.

**Plot the BiPo events
----------------------
Assumes you have downloaded and built the BiPoAnalysis code from this repository
and that you have a working version of ROOT. 

1. Set the following environment variables:
BIPO_OUTDIR to location of BiPo physics release directories
  eg. export BIPO_OUTDIR=home/jonesdc/prospect/bipo_data/ Inside this directory
  you will see Analyzed_2019A, Analyzed_2019B for example.
  
BIPO_ANALYSIS      set to the "BiPoAnalysis" directory (Github repos directory)
                   where the code lives
		   
TECHNOTE           set to the current technote directory inside the BiPoAnalysis
                   folder. eg $BIPO_ANALYSIS/technote/2019B/
2. Check that you have the most up to date runlist for the current analysis release.
For the 2019B analysis pass this runlist is called 2019B_GoodRuns.txt which should
match the same file found on the Github in the following directory:
PROSPECT2x_ANALYSIS/Analysis/AnalyzerConfig/

3. Inside the BiPoAnalysis directory open a ROOT session and at the command line
run the macro makeBiPoClassFromRunlist.C to make the BP class, a class that includes
the full TChain of BiPo ROOT trees. This creates the files "BP.h" and "BP.C".
Args: runlist file name  eg. 2019B_GoodRuns.txt
      TFilename          eg. name of ROOT Tree
      release            eg. Analyzed_2019B
Watch what is written to the screen during the generation of this class to make sure
there are no missing files.

5. Now make plots inside a ROOT session using BiPoPlotter.C and BiPovsTime.C. These
will produce plots for the technote and automatically populate the technote directory.
In addition some of the graphs and histograms used in previous publications will be 
saved to a ROOT file called BiPoPublicationPlots.root. 
First edit the array "ExcludeCellArr" in both to match the excluded segments list
used in the configuration file AD1_BiPo.cfg. For both of these macros
     fiducialize      tells whether or not to include a fiducial cut.
     alpha_type       tells which alpha to analysze and takes one of three values:
                         0 plot Bi214->Po214
                         1 plot Bi212->Po212
                         2 include both (no guarantees will produce meaningful results)
     P2_style         use PROSPECT plotting style?
     recreate         recreate ROOT files of plots (list of plots output for PRD)
     
To properly generate the publications plots and overwrite existing ones in the file
BiPoPublicationPlots.root run the script from the bash command line ./makePubPlots.sh

6. Now if you go to the technote directory you should be able to produce a new technote
by running latex on main.tex.

7. You may notice that a plot of simulation vs. data for the Bi214 beta spectrum was
included in the technote. A version of this simulated spectrum is included in 
"SimBi214BetaSpectrum.root". The next section will show how to create this simulation,
plot and .root file.

**Simulation of Bi214 spectrum
---------------------------------
Assumes you have a working and up to date version of PG4 and that you are working on 
Borax. Also assumes you have all environment variables prescribed in step 2 of the
section "Making the BiPo Trees"

1. Set the following environment variables:
     MACDIR           set to directory where you want to store your .mac files for G4 
                      simulations
     PG4_BUILD        set to directory of working build of PROSPECT-G4 code
     
     PG4_OUTDIR       set to directory where you want output of simulations to go
                      eg. /p/lustre2/psptexp/user/jonesdc/data/PG4_OUTPUT/

2. Edit line 25 of script BiPoMacMaker.sh to have the current run list then run the
script to produce a .mac file for each run in the runlist. Each file calls for 5000
BiPo214 events to be generated which is a factor of 5-10 greater than is seen per
run in the data.

3. Edit line 26 of RunSimulationPass.sh to reflect the current analysis release then
run the script. This will produce ROOT Trees of BiPo only events produced by running
the simulated events through the same PulseCruncher and BiPoTreePlugin as the data.

4. Now go to your BIPO_ANALYSIS directory. If this is on your personal computer you
will need to copy the trees over.

5. Make a simulated BiPo class by running makeBiPoSimClassFromRunlist.C at the ROOT
command line. This creates the files "BPsim.h" and "BPsim.C".
Args: runlist file name  eg. 2019B_GoodRuns.txt
      TFilename          eg. name of ROOT Tree
      release            eg. Analyzed_2019B
Watch what is written to the screen during the generation of this class to make sure
there are no missing files. 

6. Now that you have the BPsim class you can create the spectrum plots and ROOT files
by running simBi214.C.

7. To get an optimized comparison between the simulated spectrum and data run SimComp.C.
     
