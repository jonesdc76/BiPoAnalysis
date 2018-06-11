#!/bin/bash
pass=$1
RELEASE=Phys_Neutrino_v2
ANARELEASE=Analyzed_20180601
FILE=AD1_Wet_Phys.root
if [ $# -lt 1 ];then
    echo "Pass argument required"
else
    for i in $(cat NeutrinoGoodRuns.txt);do
	if [ -d ${P2X_ANADAT}/${ANARELEASE}/${i} ];then
	    dir="$(cut -d'/' -f1 <<<$i)"
	    #echo $dir
	    if [ ! -d ${BIPO_OUTDIR}/${RELEASE}/${dir}/pass$pass ];then
		mkdir -p ${BIPO_OUTDIR}/${RELEASE}/${dir}/pass$pass
	    fi
	    cp ${P2X_ANADAT}/${ANARELEASE}/${i}/$FILE ${BIPO_OUTDIR}/${RELEASE}/${dir}/pass${pass}/${i: -24}.root
	else
	    echo "$i missing"
	fi
    done
fi
    
