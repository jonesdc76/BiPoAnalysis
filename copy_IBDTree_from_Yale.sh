#!/bin/bash
DATA_DIR=/projects/prospect/converted_data/Analyzed/
DATA_DIR=/home/jonesdc/prospect/data/Analyzed/
RELEASE=Phys_NuFact_v1
ANARELEASE=Analyzed_NuFact_v1
FILE=AD1_Wet_Phys.root
SSHSOCKET=~/.ssh/jonesdc@wright.physics.yale.edu
ssh -M -f -N -o ControlPath=$SSHSOCKET jonesdc@wright.physics.yale.edu
for i in $(cat NuFactGoodRuns.txt);do
    dir=$BIPO_OUTDIR/$ANARELEASE/$i
    if [ ! -d $dir ];then
	mkdir -p $dir
    fi
    scp -o ControlPath=$SSHSOCKET jonesdc@wright.physics.yale.edu:${DATA_DIR}/${ANARELEASE}/${i}/${FILE} ${dir}/${FILE}
done
ssh -S $SSHSOCKET -O exit jonesdc@wright.physics.yale.edu
