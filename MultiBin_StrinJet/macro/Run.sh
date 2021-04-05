#!/bin/bash
######################################################################
echo ==========================================
echo run Integral Yield to Pi ratio
#echo .q | sleep 10 | root -l IntegralYield.C

root -l -b -q Integral_KPiRatio.C
root -l -b -q Integral_LPiRatio.C
root -l -b -q Integral_OPiRatio.C
root -l -b -q Integral_XPRatio.C

exit 0
