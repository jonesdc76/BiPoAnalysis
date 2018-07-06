#!/bin/bash
pass=$1
RELEASE=Phys_NuFact_v1
ANARELEASE=Analyzed_NuFact_v1
FILE=AD1_Extra_Phys.root
if [ $# -lt 1 ];then
    echo "Pass argument required"
else
    for i in $(cat RunList.txt);do
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
    
