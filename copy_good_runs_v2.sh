#!/bin/bash
IBD=0
export P2X_ANADAT=/home/prospect-collab/converted_data/Analyzed/Analyzed_20180718_Extra/
PLUGIN=BiPoTreePlugin
TREE=BiPo
FILE=AD1_Extra_Phys.root
if [ $IBD -eq 1 ]; then
    PLUGIN=P2kIBDPlugin
    TREE=Tibd
    FILE=AD1_Wet_Phys.root
fi
RELEASE=Phys_NuFact_v1
ANARELEASE=Analyzed_NuFact_v1
ANARELEASE=Analyzed_20180718


for i in $(cat NuFact18_GoodRuns.txt);do
    if [ -d ${P2X_ANADAT}/${ANARELEASE}/${i} ];then
	dir="$(cut -d'/' -f1 <<<$i)"
	    #echo $dir
	if [ ! -d ${BIPO_OUTDIR}/${ANARELEASE}/${i} ];then
	    mkdir -p ${BIPO_OUTDIR}/${ANARELEASE}/${i}
	fi
	infname=${P2X_ANADAT}/${ANARELEASE}/${i}/$FILE
	outfname=${BIPO_OUTDIR}/${ANARELEASE}/${i}/$FILE
	if [ ! -f $outfname ];then
	    root -b -l -q "copyTree.C+(\"$infname\", \"$outfname\", \"$TREE\", \"$PLUGIN\")"
	else
	    echo "$outfname already exists. Skipping."
	fi
    else
	echo "$i missing"
    fi
done
