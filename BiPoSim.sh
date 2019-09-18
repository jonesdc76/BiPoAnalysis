#!/bin/bash
#Runs multiple Bi-214 beta decay simulations inside PG4 framework

RATE=0.165
i=0
N=5000
while read x; do
echo $i
RUNNAME=${PG4_OUTDIR}/AD_Bi214_$x
CALFILE=$x
echo "/output/setRunNum $i">BiPo214.mac
echo "/output/filename ${RUNNAME}.h5">>BiPo214.mac
echo "/output/setRecordLevel 2">>BiPo214.mac
echo "/geom/mode PROSPECT">>BiPo214.mac
echo "/run/initialize">>BiPo214.mac

echo "/generator/module DecaySource">>BiPo214.mac
echo "/generator/decaySource/tcut 3 ms">>BiPo214.mac
echo "/generator/decaySource/type Bi214">>BiPo214.mac

echo "/generator/vertex/scintvol">>BiPo214.mac

echo "/run/beamOn $N">>BiPo214.mac

#Run simulation                                                                 
$PG4_BUILD/bin/PROSPECT-G4 BiPo214.mac

#Convert to detector response - phys pulse                                      
$P2X_BUILD/bin/CalcDetectorPulseResponse $P2X_ANALYSIS_CODE/PulseCruncher/Config/Crunch_AD1_Production.cfg ${RUNNAME}.h5 -o phys -r $RATE -c $CALFILE

#Apply plugin                                                                   
$P2X_BUILD/bin/AnalyzeCalibrated ${RUNNAME}_DetSim.h5 $HOME/PG4_OUTPUT/ $P2X_ANALYSIS_CODE/Analysis/AnalyzerConfig/AD1_BiPo.cfg -c $CALFILE

#Optional convert detector response into root file                              
#$P2X_BUILD/bin/PhysPulse_HDF5_to_ROOT ${RUNNAME}_DetSim.h5

((i+=1001))
done<2019B_GoodRuns.txt

#Optional convert truth h5 into root file                                       
#$P2X_BUILD/bin/PG4_HDF5_to_ROOT ${RUNNAME}.h5

