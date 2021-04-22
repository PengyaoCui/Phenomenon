#!/bin/bash/

root -l -b -q AnaSinJ.C\(0,0\)
root -l -b -q AnaSinJ.C\(0,1\)
root -l -b -q AnaSinJ.C\(0,2\)
root -l -b -q AnaSinJ.C\(1,0\)
root -l -b -q AnaSinJ.C\(1,1\)
root -l -b -q AnaSinJ.C\(1,2\)

echo mv pp7TeV
mv *7TeV*.root /home/cuipengyao/Phenomenon/StrinJet/macro/sim/pp7TeV
mv *7TeV*.txt /home/cuipengyao/Phenomenon/StrinJet/macro/sim/pp7TeV

echo mv pp13TeV
mv *13TeV*.root /home/cuipengyao/Phenomenon/StrinJet/macro/sim/pp13TeV
mv *13TeV*.txt /home/cuipengyao/Phenomenon/StrinJet/macro/sim/pp13TeV

