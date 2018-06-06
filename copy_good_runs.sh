#!/bin/bash
pass=$1
RELEASE=Phys_Neutrino_v2
FILE=AD1_Wet_Phys${pass}.root
if [ $# -lt 1 ];then
    echo "Pass argument required"
else
    for i in $(cat NeutrinoGoodRuns.txt);do
	if [ -d ${BIPO_OUTDIR}/${RELEASE}/$i ];then
	    cd ${BIPO_OUTDIR}/${RELEASE}/$i
	    cp $FILE ../../pass${pass}/${i: -24}.root
	else
	    echo "$i missing"
	fi
    done
fi
    
