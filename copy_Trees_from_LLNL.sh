#!/bin/bash
IBD=1
RUNLIST=2018C_GoodRuns.txt
DATA_DIR=/p/lustre2/psptexp/user/jonesdc/data/Analyzed/
RELEASE=Phys_2018C
ANARELEASE=Analyzed_2018C
FILE=AD1_BiPo_DT.root
FILE=AD1_BiPo.root
if [ $IBD -eq 1 ];then
    FILE=AD1_Wet_Phys.root
fi
#SSHSOCKET=~/.ssh/jones291@borax.llnl.gov
#ssh -M -f -N -o ControlPath=$SSHSOCKET jones291@borax.llnl.gov
ssh -M -f -N borax
for i in $(cat $RUNLIST);do
    dir=$BIPO_OUTDIR/$ANARELEASE/$i
    if [ ! -d $dir ];then
	mkdir -p $dir
    fi
    echo "Copying $i"
    #scp borax:${DATA_DIR}/${ANARELEASE}/${i}/${FILE} ${dir}/AD1_BiPo_wDT.root
    scp borax:${DATA_DIR}/${ANARELEASE}/${i}/${FILE} ${dir}/${FILE}
    #scp oslic:${DATA_DIR}/${ANARELEASE}/${i}/${FILE} ${dir}/${FILE}
done
#ssh -S $SSHSOCKET -O exit jones291@borax.llnl.gov
