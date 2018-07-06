#!/bin/bash
RELEASE=Phys_NuFact_v1
ANARELEASE=Analyzed_NuFact_v1
FILE=AD1_Extra_Phys.root

for i in $(cat NeutrinoGoodRuns.txt);do
    if [ -d ${P2X_ANADAT}/${ANARELEASE}/${i} ];then
	dir="$(cut -d'/' -f1 <<<$i)"
	    #echo $dir
	if [ ! -d ${BIPO_OUTDIR}/${RELEASE}/${i} ];then
	    mkdir -p ${BIPO_OUTDIR}/${RELEASE}/${i}
	fi
	infname=${P2X_ANADAT}/${ANARELEASE}/${i}/$FILE
	outfname=${BIPO_OUTDIR}/${ANARELEASE}/${i}/$FILE
	root -b -l -q "copyTree.C+(\"$infname\", \"$outfname\")"
    else
	echo "$i missing"
    fi
done

    
