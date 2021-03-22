#!/bin/bash/
root -l -b -q dLKRatio.C
root -l -b -q dOKRatio.C
root -l -b -q dOLRatio.C
root -l -b -q dOXRatio.C
root -l -b -q dXKRatio.C
root -l -b -q dXLRatio.C

cp ./figure/pdf/*.pdf /home/cuipengyao/Phenomenon/note/figures/rope
