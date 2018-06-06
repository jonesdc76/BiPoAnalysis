#!/bin/bash
pass=pass$1
release=Phys_Neutrino_v2
dir=prospect/data/Analyzed
if [ $# -ne 1 ]
then 
    echo "pass string required as command line argument"
else
    n=0
    series[${n}]=WetCommissioning; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180316_Background; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180417_Background; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180420_Background; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180501_ReactorOn; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180525_Background; echo "Adding  ${series[$n]}";  ((n++))

    for i in "${series[@]}"
    do
	rm -rf ${BIPO_OUTDIR}/${release}/${i}/${pass}/*.root
	if [ ! -d ${BIPO_OUTDIR}/${release}/$i/${pass} ];then
	    mkdir ${BIPO_OUTDIR}/${release}
	    mkdir ${BIPO_OUTDIR}/${release}/$i
	    mkdir ${BIPO_OUTDIR}/${release}/$i/${pass}
	fi
	scp -r Yale:${dir}/${release}/${i}/${pass}/*.root ${BIPO_OUTDIR}/${release}/${i}/${pass}/
    done

fi
