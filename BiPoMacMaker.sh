#!/bin/bash                                                                     
RATE=0.165
i=0
N=5000
while read x; do
i=${x: -10}
echo $i
RUNNAME=${PG4_OUTDIR}/AD_Bi214_$x
MACFILE=${MACDIR}/AD_Bi214_$x.mac
CALFILE=$x
echo "/output/setRunNum $i">$MACFILE
echo "/output/filename ${RUNNAME}.h5">>$MACFILE
echo "/output/setRecordLevel 2">>$MACFILE
echo "/geom/mode PROSPECT">>$MACFILE
echo "/run/initialize">>$MACFILE

echo "/generator/module DecaySource">>$MACFILE
echo "/generator/decaySource/tcut 3 ms">>$MACFILE
echo "/generator/decaySource/type Bi214">>$MACFILE

echo "/generator/vertex/scintvol">>$MACFILE

echo "/run/beamOn $N">>$MACFILE

done<2019B_GoodRuns.txt

#Optional convert truth h5 into root file                                       
#$P2X_BUILD/bin/PG4_HDF5_to_ROOT ${RUNNAME}.h5

