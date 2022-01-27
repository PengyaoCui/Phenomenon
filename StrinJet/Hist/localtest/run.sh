#!/bin/bash
#
echo =====================================
echo =======Remove results================

rm CenttodNdEta.txt Results.root 

echo ========run models===================


for i in \
"\"Monash\"" \

do

root -l -b -q AnaSinJ.C\(${i}\)

done

#echo ========cp results to macro==========
#cp *.root *.txt ../macro/sim/
exit
