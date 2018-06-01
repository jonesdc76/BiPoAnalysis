#!/bin/bash
series=$1
description=180316_Background
if [ "$series" -gt 2 ];then
 description=WetCommissioning
fi
date=Phys_20180316
date=Phys_20180409
datadir=/projects/prospect/converted_data/${date}/${description}/series${series}

date=Phys_20180510
datadir=/projects/prospect/converted_data/Phys/${date}/${description}/series${series}

outdir=/home/jonesdc/prospect/Chilly/Outdir/${date}/$description/
rundir=/home/jonesdc/prospect/PROSPECT2x_Analysis/Analysis
cfg=${rundir}/AnalyzerConfig/AD1_Wet_Phys_BiPoNeutrino.cfg


cd ${rundir}
for i in $(ls ${datadir}/*.h5); do
    echo "Analyzing $i"; 
    ./AnalyzeCalibrated $i $outdir ${cfg} 1
done;
