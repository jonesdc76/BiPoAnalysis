#!/bin/bash
##Launches batch of AnalyzeCalibrated jobs to extract BiPo's from physics data
##and copies BiPo tree to common named pass directory
##Requires P2X_ANALYSIS to be set to the dir where releases are located 
##Requires P2X_ANALYZED to be set to the dir where data is to be stored
##Requires P2X_ANALYSIS_CODE to be set to the PROSPECT2X_ANALYSIS dir
##Edit series below to add or remove data to be analayzed

MAX_CORES=10 #Maximum number of cores to utilize for launching batch analysis
LAUNCH=1 #Set to 1 if batch launch desired.
pass=pass$1
name=AD1_Wet_Phys$1
file=${name}.root
if [ $# -ne 1 ]
then 
    echo "pass string required as command line argument"
else
    cd ${P2X_ANALYSIS_CODE}/ControlScripts
    RELEASE=Phys_Neutrino_v2
    if [ ! -d ${P2X_ANALYZED}/${RELEASE} ];then
	mkdir $P2X_ANALYZED/${RELEASE}
    fi
    export P2X_ANALYZED=${P2X_ANALYZED}/${RELEASE}
    ANALYZER=$name
    export P2X_PHYSDAT=${P2X_PHYSDAT}/${RELEASE}
    echo "Copying sql databases from ${P2X_PHYSDAT} to ${APP_DIR}"
    cp $P2X_PHYSDAT/*.sql $APP_DIR/
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
    series[${n}]=180316_Background/series002; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180417_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180420_Background/series000; echo "Adding  ${series[$n]}"; ((n++))
    series[${n}]=180501_ReactorOn/series000; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180501_ReactorOn/series001; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180501_ReactorOn/series002; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180501_ReactorOn/series003; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180501_ReactorOn/series004; echo "Adding  ${series[$n]}";  ((n++))
    series[${n}]=180525_Background/series000; echo "Adding  ${series[$n]}";  ((n++))
    

    
#Launch analysis batches
    if [ $LAUNCH -eq 1 ]; then
	for i in "${series[@]}"
	do
	    export SERIES=$i
	    echo " ${P2X_ANALYZED}/${i}"
	    if [ ! -d ${P2X_ANALYZED}$i ];then
		mkdir  -p ${P2X_ANALYZED}/$i
	    fi
	    if [ $LAUNCH -eq 1 ];then
		./LaunchBatch.py --anacal=$SERIES --mode=$ANALYZER --new --jmax=$MAX_CORES
	    fi
	done
    fi
    
fi

#export SERIES=WetCommissioning/series015
#./LaunchBatch.py --anacal=$SERIES --mode=$ANALYZER --new --jmax=8
