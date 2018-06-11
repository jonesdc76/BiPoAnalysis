#!/bin/bash
RUNLIST=${BIPO_ANALYSIS}/runlist.txt
RELEASE=Phys_Neutrino_v2
cd ${BIPO_OUTDIR}/${RELEASE}
series[${n}]=WetCommissioning/series015; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series016; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series017; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series018; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series019; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series020; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series021; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series022; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=WetCommissioning/series023; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180316_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180316_Background/series001; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180316_Background/series002; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180417_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180420_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180501_ReactorOn/series000; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180501_ReactorOn/series001; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180501_ReactorOn/series002; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180501_ReactorOn/series003; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180501_ReactorOn/series004; echo "Adding  ${series[$n]}"; ((n++))
series[${n}]=180525_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
n=0
for i in "${series[@]}"
do
    export SERIES=$i
    for s in $(ls $i);do
	if [ $n -eq 0 ];then
	    echo "$i/$s">$RUNLIST
	    ((n++))
	else
	    echo "$i/$s">>$RUNLIST
	fi
    done
done