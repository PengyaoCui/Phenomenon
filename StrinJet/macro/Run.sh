#!/bin/bash
######################################################################
echo ==========================================
echo track information
root -l -b -q dNfwddEta.C
root -l -b -q TrkEta.C

echo ==========================================
echo InteSpectra
root -l -b -q InteSpect.C

echo ==========================================
echo InteRatio
#root -l -b -q InteRatio.C
root -l -b -q InteRatio_KPi.C
root -l -b -q InteRatio_LPi.C
root -l -b -q InteRatio_XPi.C
root -l -b -q InteRatio_OPi.C
root -l -b -q InteRatio_PhiPi.C

root -l -b -q InteRatio_OL.C
root -l -b -q InteRatio_XL.C
root -l -b -q InteRatio_KPhi.C
root -l -b -q InteRatio_LPhi.C
root -l -b -q InteRatio_OPhi.C
root -l -b -q InteRatio_XPhi.C
 
#root -l -b -q InteRatio_JE.C
root -l -b -q InteRatio_KPi_JE.C
root -l -b -q InteRatio_LPi_JE.C
root -l -b -q InteRatio_XPi_JE.C
root -l -b -q InteRatio_OPi_JE.C
root -l -b -q InteRatio_PhiPi_JE.C

root -l -b -q InteRatio_OL_JE.C
root -l -b -q InteRatio_XL_JE.C
root -l -b -q InteRatio_KPhi_JE.C
root -l -b -q InteRatio_LPhi_JE.C
root -l -b -q InteRatio_OPhi_JE.C
root -l -b -q InteRatio_XPhi_JE.C

echo ==========================================
echo InclRatio
root -l -b -q Incl_LK.C
root -l -b -q Incl_XK.C
root -l -b -q Incl_OK.C
root -l -b -q Incl_XL.C
root -l -b -q Incl_OL.C
root -l -b -q Incl_OX.C
 
root -l -b -q Incl_XiPhi.C
root -l -b -q Incl_OmegaPhi.C
root -l -b -q Incl_ProtonPion.C

echo ==========================================
echo InclRatio_Cent
root -l -b -q Incl_LK_Cent.C
root -l -b -q Incl_OK_Cent.C
root -l -b -q Incl_XK_Cent.C
root -l -b -q Incl_XL_Cent.C
root -l -b -q Incl_OL_Cent.C
root -l -b -q Incl_OX_Cent.C
root -l -b -q Incl_KPhi_Cent.C
root -l -b -q Incl_LPhi_Cent.C
root -l -b -q Incl_XPhi_Cent.C
root -l -b -q Incl_OPhi_Cent.C

root -l -b -q Incl_LK_Cent_Data.C
root -l -b -q Incl_LK_Cent_CR_Data.C
root -l -b -q Incl_LK_Cent_Rope_Data.C

root -l -b -q Incl_LK_Cent_CR.C
root -l -b -q Incl_OK_Cent_CR.C
root -l -b -q Incl_XK_Cent_CR.C
root -l -b -q Incl_XL_Cent_CR.C
root -l -b -q Incl_OL_Cent_CR.C
root -l -b -q Incl_OX_Cent_CR.C
root -l -b -q Incl_KPhi_Cent_CR.C
root -l -b -q Incl_LPhi_Cent_CR.C
root -l -b -q Incl_XPhi_Cent_CR.C
root -l -b -q Incl_OPhi_Cent_CR.C
 
root -l -b -q Incl_LK_Cent_Rope.C
root -l -b -q Incl_OK_Cent_Rope.C
root -l -b -q Incl_XK_Cent_Rope.C
root -l -b -q Incl_XL_Cent_Rope.C
root -l -b -q Incl_OL_Cent_Rope.C
root -l -b -q Incl_OX_Cent_Rope.C
root -l -b -q Incl_KPhi_Cent_Rope.C
root -l -b -q Incl_LPhi_Cent_Rope.C
root -l -b -q Incl_XPhi_Cent_Rope.C
root -l -b -q Incl_OPhi_Cent_Rope.C

echo ==========================================
echo JERatio
root -l -b -q JE_LK.C
root -l -b -q JE_OK.C
root -l -b -q JE_OL.C
root -l -b -q JE_OX.C
root -l -b -q JE_XK.C
root -l -b -q JE_XL.C

echo ==========================================
echo JERatio_Cent
root -l -b -q JE_LK_Cent.C
root -l -b -q JE_OK_Cent.C
root -l -b -q JE_XK_Cent.C
root -l -b -q JE_XL_Cent.C
root -l -b -q JE_OL_Cent.C
root -l -b -q JE_OX_Cent.C

root -l -b -q JE_LK_Cent_CR.C
root -l -b -q JE_OK_Cent_CR.C
root -l -b -q JE_XK_Cent_CR.C
root -l -b -q JE_XL_Cent_CR.C
root -l -b -q JE_OL_Cent_CR.C
root -l -b -q JE_OX_Cent_CR.C

root -l -b -q JE_LK_Cent_Rope.C
root -l -b -q JE_OK_Cent_Rope.C
root -l -b -q JE_XK_Cent_Rope.C
root -l -b -q JE_XL_Cent_Rope.C
root -l -b -q JE_OL_Cent_Rope.C
root -l -b -q JE_OX_Cent_Rope.C

echo ==========================================
echo cp figures

cp ./figure/eps/* /home/cuipengyao/Phenomenon/note/figures/rope




exit 0
