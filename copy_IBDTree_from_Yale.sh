#!/bin/bash
DATA_DIR=/projects/prospect/converted_data/Analyzed/
RELEASE=Phys_Neutrino_v2
ANARELEASE=Analyzed_NuFact_v1
FILE=AD1_Wet_Phys.root
SSHSOCKET=~/.ssh/jonesdc@wright.physics.yale.edu
ssh -M -f -N -o ControlPath=$SSHSOCKET jonesdc@wright.physics.yale.edu
for i in $(cat RunList.txt);do
    dir=$BIPO_OUTDIR/$ANARELEASE/$i
    if [ ! -d $dir ];then
	mkdir -p $dir
    fi
    scp -o ControlPath=$SSHSOCKET jonesdc@wright.physics.yale.edu:${DATA_DIR}/${ANARELEASE}/${i}/${FILE} ${dir}/${FILE}
done
ssh -S $SSHSOCKET -O exit jonesdc@wright.physics.yale.edu
