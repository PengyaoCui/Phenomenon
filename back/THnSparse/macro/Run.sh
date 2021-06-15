#!/bin/bash
######################################################################
echo ==========================================
echo run TrkEta distribution

root -l -b -q TrkEta.C

#echo ==========================================
#echo run Integral Yield to Pi ratio
##echo .q | sleep 10 | root -l IntegralYield.C
#
#root -l -b -q Integral_KPiRatio.C
#root -l -b -q Integral_LPiRatio.C
#root -l -b -q Integral_OPiRatio.C
#root -l -b -q Integral_XPRatio.C

echo ==========================================
echo run particle ratio with Pt
#root -l -b -q Incl_LK.C
#root -l -b -q Incl_OK.C
#root -l -b -q Incl_OL.C
#root -l -b -q Incl_OX.C
#root -l -b -q Incl_XK.C
#root -l -b -q Incl_XL.C

root -l -b -q JE_LK.C
root -l -b -q JE_OK.C
root -l -b -q JE_OL.C
root -l -b -q JE_OX.C
root -l -b -q JE_XK.C
root -l -b -q JE_XL.C

exit 0
