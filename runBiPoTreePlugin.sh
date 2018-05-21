#!/bin/bash
##Launches batch of AnalyzeCalibrated jobs to extract BiPo's from physics data
##and copies BiPo tree to common named pass directory
##Requires P2X_ANALYSIS to be set to the dir where releases are located 
##Requires P2X_ANALYZED to be set to the dir where data is to be stored
##Requires P2X_ANALYSIS_CODE to be set to the PROSPECT2X_ANALYSIS dir
##Edit series below to add or remove data to be analayzed

LAUNCH=0 #Set to 1 if batch launch desired. Leave at 0 to just copy files to pass dir
pass=pass$1
name=AD1_Wet_Phys$1
file=${name}.root
if [ $# -ne 1 ]
then 
    echo "pass string required as command line argument"
else
    cd ${P2X_ANALYSIS_CODE}/ControlScripts
    RELEASE=Phys_20180510
    if [ ! -d ${P2X_ANALYZED}/${RELEASE} ];then
	mkdir $P2X_ANALYZED/${RELEASE}
    fi
    export P2X_ANALYZED=${P2X_ANALYZED}/${RELEASE}
    ANALYZER=AD1_Wet_Phys_${pass}
    export P2X_PHYSDAT=/projects/prospect/converted_data/Phys/${RELEASE}
    n=0
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
    series[${n}]=180417_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180420_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180501_ReactorOn/series000; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180501_ReactorOn/series001; echo "Adding  ${series[$n]}";  ((n++))
    
#Launch analysis batches
    for i in "${series[@]}"
    do
	export SERIES=$i
	echo " ${P2X_ANALYZED}/${i}"
	if [ $LAUNCH -eq 1 ];then
	    ./LaunchBatch.py --anacal=$SERIES --mode=$ANALYZER --new --jmax=8
	fi
    done
    
#Copy BiPo tree root files to common directory
    for i in "${series[@]}"
    do
	cd ${P2X_ANALYZED}/$i
	if [ ! -d  ../$pass ];then
	    echo "Making directory $pass"
	    mkdir ../${pass}
	fi
	pwd
	for dir in $(ls -d s*); 
	do
	    if [ -e ${dir}/${file} ]
	    then
		cp  ${dir}/$file ../${pass}/${dir}.root
	    else
		echo "${dir}/${file} not found in directory ${dir}"
	    fi
	done
    done
fi

#export SERIES=WetCommissioning/series015
#./LaunchBatch.py --anacal=$SERIES --mode=$ANALYZER --new --jmax=8