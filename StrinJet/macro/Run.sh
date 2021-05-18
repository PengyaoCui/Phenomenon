#!/bin/bash
######################################################################
echo ==========================================
echo track information
root -l -b -q f1_TrkEta.C
root -l -b -q f2_dNfwddEta.C

echo ==========================================
echo InteSpectra
#root -l -b -q InteSpect.C
root -l -b -q f3_InteSpect_Kshort.C
root -l -b -q f3_InteSpect_Lambda.C
root -l -b -q f3_InteSpect_Xi.C
root -l -b -q f3_InteSpect_Omega.C
root -l -b -q f3_InteSpect_Kstar.C
root -l -b -q f3_InteSpect_Phi.C

root -l -b -q f4_InteSpect_Kshort_JE.C
root -l -b -q f4_InteSpect_Kstar_JE.C
root -l -b -q f4_InteSpect_Lambda_JE.C
root -l -b -q f4_InteSpect_Omega_JE.C
root -l -b -q f4_InteSpect_Phi_JE.C
root -l -b -q f4_InteSpect_Xi_JE.C

echo ==========================================
echo InteRatio
#root -l -b -q InteRatio.C
root -l -b -q f5_InteRatio_KPi.C
root -l -b -q f5_InteRatio_LPi.C
root -l -b -q f5_InteRatio_XPi.C
root -l -b -q f5_InteRatio_OPi.C
root -l -b -q f5_InteRatio_PhiPi.C
root -l -b -q f5_InteRatio_KstarPi.C

root -l -b -q f7_InteRatio_OL.C
root -l -b -q f7_InteRatio_XL.C
root -l -b -q f7_InteRatio_PhiK.C
root -l -b -q f7_InteRatio_LPhi.C
root -l -b -q f7_InteRatio_OPhi.C
root -l -b -q f7_InteRatio_XPhi.C
root -l -b -q f7_InteRatio_KstarK.C
 
root -l -b -q f8_InteRatio_KstarK_JE.C
root -l -b -q f8_InteRatio_LPhi_JE.C
root -l -b -q f8_InteRatio_OL_JE.C
root -l -b -q f8_InteRatio_OPhi_JE.C
root -l -b -q f8_InteRatio_PhiK_JE.C
root -l -b -q f8_InteRatio_XL_JE.C
root -l -b -q f8_InteRatio_XPhi_JE.C

#root -l -b -q InteRatio_JE.C
root -l -b -q InteRatio_KPi_JE.C
root -l -b -q InteRatio_LPi_JE.C
root -l -b -q InteRatio_XPi_JE.C
root -l -b -q InteRatio_OPi_JE.C
root -l -b -q InteRatio_PhiPi_JE.C

root -l -b -q InteRatio_OL_JE.C
root -l -b -q InteRatio_XL_JE.C
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

root -l -b -q Incl_KstarK_Center.C
root -l -b -q Incl_KstarK_Peripheral.C
root -l -b -q Incl_PhiK_Center.C
root -l -b -q Incl_PhiK_Peripheral.C
root -l -b -q Incl_LK_Cent.C
root -l -b -q Incl_OK_Cent.C
root -l -b -q Incl_XK_Cent.C
root -l -b -q Incl_XL_Cent.C
root -l -b -q Incl_OL_Cent.C
root -l -b -q Incl_OX_Cent.C
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
root -l -b -q Incl_LPhi_Cent_CR.C
root -l -b -q Incl_XPhi_Cent_CR.C
root -l -b -q Incl_OPhi_Cent_CR.C
 
root -l -b -q Incl_LK_Cent_Rope.C
root -l -b -q Incl_OK_Cent_Rope.C
root -l -b -q Incl_XK_Cent_Rope.C
root -l -b -q Incl_XL_Cent_Rope.C
root -l -b -q Incl_OL_Cent_Rope.C
root -l -b -q Incl_OX_Cent_Rope.C
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
