#!/bin/bash
#
echo =====================================
echo =======Remove results================

rm CenttodNdEta.txt Results.root 

echo ========run models===================

echo                                      

echo ===========Monash====================

for i in \
"\"Monash\"" \
"\"CR\"" \
#"\"Rope\"" \
#"\"CR+Rope\"" \

do

root -l -b -q AnaSinJ.C\(${i}\)

done

exit
