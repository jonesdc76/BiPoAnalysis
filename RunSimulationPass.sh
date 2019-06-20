#!/bin/bash
rm -r ~/jobs/*
#screen -R p2x
source ~/.profile # important setup in screen!

export PROSPECT_JOBSDB=$HOME/prospect_release_jobs.sql
rm $PROSPECT_JOBSDB
sqlite3 $PROSPECT_JOBSDB < $P2X_ANALYSIS_CODE/GeneralUtils/JobsDB_Schema.sql
export JOBFILE=$HOME/p_release_jobs.txt

RUNTIME=1800
RUNJOBS () {
    cd `dirname $JOBFILE`
    $P2X_ANALYSIS_CODE/GeneralUtils/JobManager.py --db=$PROSPECT_JOBSDB --account nuphys --queue=pbatch --limit 1000 --walltime $RUNTIME --cycle 30 --jobfile p_release_jobs.txt
    rm $JOBFILE
}

# helper to finish jobs if RUNJOBS canceled
RESUMEJOBS () {
    $P2X_ANALYSIS_CODE/GeneralUtils/JobManager.py --db=$PROSPECT_JOBSDB --account nuphys --queue=pbatch --limit 1000 --cycle 30
}

######################
# set up working paths

export PHYSRELEASE=2019B
export ANARELEASE=${PHYSRELEASE}

export P2X_PHYSDAT=/p/lustre2/psptexp/converted/Phys/Phys_${PHYSRELEASE}
export P2X_ANADAT=/p/lustre2/psptexp/converted/analyzed/Analyzed_${ANARELEASE}
export PROSPECT_CALDB=$P2X_PHYSDAT/PROSPECT_CalDB.sql
export PROSPECT_RUNSDB=$P2X_PHYSDAT/PROSPECT_RunsDB.sql
export P2X_ANALYZED=${P2X_ANALYZED}/Analyzed_${ANARELEASE}
mkdir -p $P2X_ANALYZED
export PROSPECT_ANADB=$P2X_ANALYZED/PROSPECT_AnaDB.sql

# special subselection:
# sqlite3 $PROSPECT_RUNSDB 'SELECT file_name FROM run_info WHERE file_name LIKE "180316_Background/series001/%"' > $P2X_ANALYZED/anaruns.txt

##############
# Run analysis

#Optional run script to create mac files for all runs in list
#./BiPoMacMaker.sh

#Simulate BiPo214 events
while read x; do
    CALFILE=$x
    RUNNAME=${PG4_OUTDIR}/AD_Bi214_$x
    MACFILE=${MACDIR}/AD_Bi214_$x.mac
    echo $PG4_BUILD/bin/PROSPECT-G4 ${MACFILE}
done > $JOBFILE < 2019B_GoodRuns.txt

RUNJOBS


#Run simulated events through PulseCruncher to produce detector output
RATE=0.165
while read x; do
    CALFILE=$x
    RUNNAME=${PG4_OUTDIR}/AD_Bi214_$x
    echo $P2X_BUILD/bin/CalcDetectorPulseResponse $P2X_ANALYSIS_CODE/PulseCruncher/Config/Crunch_AD1_Production.cfg ${RUNNAME}.h5 -o phys -r $RATE -c $CALFILE
done > $JOBFILE < 2019B_GoodRuns.txt

RUNJOBS


#Run detector output through plugin
while read x; do
    CALFILE=$x
    RUNNAME=${PG4_OUTDIR}/AD_Bi214_$x
    echo $P2X_BUILD/bin/AnalyzeCalibrated ${RUNNAME}_DetSim.h5 $HOME/PG4_OUTPUT/ $P2X_ANALYSIS_CODE/Analysis/AnalyzerConfig/AD1_BiPo.cfg -c $CALFILE
done > $JOBFILE < 2019B_GoodRuns.txt

RUNJOBS

# check processing success
cd $P2X_ANALYZED
rm missing_anaphys.txt
while read x; do
if ! [ -e $P2X_ANALYZED/$x/${ANALYZER}.root.xml ]
then
echo $x
fi
done > missing_anaphys.txt < $P2X_PHYSDAT/all_runs.txt
echo "Failed to run PhysPulse analysis on:"
cat missing_anaphys.txt

