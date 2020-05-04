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

MERGEDB () {
    rm $PROSPECT_ANADB
    rm -r ~/tmp/; mkdir ~/tmp/
    $P2X_ANALYSIS_CODE/ControlScripts/MergeDB.py -g --schema $P2X_ANALYSIS_CODE/GeneralUtils/AnalysisDB_NoIdx_Schema.sql ${PROSPECT_ANADB} $P2X_ANALYZED/*/*/*/$1 -r ~/tmp/
    sqlite3 $PROSPECT_ANADB 'CREATE UNIQUE INDEX idx_analysis_results ON analysis_results(run_id, var_id); CREATE INDEX idx_anaresults_var ON analysis_results(var_id); CREATE UNIQUE INDEX idx_analysis_xresults ON analysis_xresults(run_id, var_id); CREATE INDEX idx_anaxresults_var ON analysis_xresults(var_id);'
}

######################
# set up working paths

export PHYSRELEASE=2019X
export ANARELEASE=${PHYSRELEASE}

export P2X_PHYSDAT=${P2X_DATA}/Phys/Phys_${PHYSRELEASE}
export P2X_ANADAT=${P2X_DATA}/analyzed/Analyzed_${ANARELEASE}
export PROSPECT_CALDB=$P2X_PHYSDAT/PROSPECT_CalDB.sql
export PROSPECT_RUNSDB=$P2X_PHYSDAT/PROSPECT_RunsDB.sql
export P2X_ANALYZED=${P2X_ANALYZED}/Analyzed_${ANARELEASE}
mkdir -p $P2X_ANALYZED
export PROSPECT_ANADB=$P2X_ANALYZED/PROSPECT_AnaDB.sql

# special subselection:
# sqlite3 $PROSPECT_RUNSDB 'SELECT file_name FROM run_info WHERE file_name LIKE "180316_Background/series001/%"' > $P2X_ANALYZED/anaruns.txt

##############
# Run analysis

export ANALYZER=AD1_BiPo
while read x; do
    echo ${P2X_BUILD}/bin/AnalyzeCalibrated ${P2X_PHYSDAT}/${x}_Phys.h5 ${P2X_ANALYZED}/`dirname $x` ${P2X_ANALYSIS_CODE}/Analysis/AnalyzerConfig/${ANALYZER}.cfg -a ${P2X_ANALYZED}/${x}/AnaDB_${ANALYZER}.sql
done > $JOBFILE < ${P2X_PHYSDAT}/all_runs.txt

RUNTIME=1800
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

MERGEDB "AnaDB*.sql"

# combine analyzed

cd $P2X_ANALYZED
for f in */series*; do :
    echo $P2X_BUILD/bin/CombineAnalyzed $f $P2X_ANALYZED/$f $ANALYZER -n -a $P2X_ANALYZED/$f/AnaDB.sql
done > $JOBFILE

RUNTIME=1800
RUNJOBS

#####################
#####################
# release permissions

chmod g+rX -R $P2X_ANALYZED
chgrp prospect -R $P2X_ANALYZED

# copy file lists and DBs from Phys to Analyzed
cp $P2X_PHYSDAT/*.* $P2X_ANALYZED

#rsync -Pavu $P2X_ANALYZED/ Yale:/projects/prospect/converted_data/Analyzed/Analyzed_${ANARELEASE}/
#rsync -Pavu $P2X_ANALYZED/ Yale:/home/prospect-collab/converted_data/Analyzed/Analyzed_${ANARELEASE}/
