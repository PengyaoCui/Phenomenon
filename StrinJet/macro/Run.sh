#!/bin/bash
######################################################################
echo ==========================================
echo track information
root -l -b -q f1_TrkEta.C
root -l -b -q f2_dNfwddEta.C
root -l -b -q f2_dNmiddEta.C
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

echo ==========================================
echo pT spect
root -l -b -q f9_Incl_Kshort.C
root -l -b -q f9_Incl_Kstar.C
root -l -b -q f9_Incl_Lambda.C
root -l -b -q f9_Incl_Omega.C
root -l -b -q f9_Incl_Phi.C
root -l -b -q f9_Incl_Xi.C

root -l -b -q f10_JE_Kshort.C
root -l -b -q f10_JE_Kstar.C
root -l -b -q f10_JE_Lambda.C
root -l -b -q f10_JE_Omega.C
root -l -b -q f10_JE_Phi.C
root -l -b -q f10_JE_Xi.C

echo ==========================================
echo pT ratio
root -l -b -q f11_Incl_KstarK.C
root -l -b -q f11_Incl_LK.C
root -l -b -q f11_Incl_OK.C
root -l -b -q f11_Incl_OL.C
root -l -b -q f11_Incl_OPhi.C
root -l -b -q f11_Incl_OX.C
root -l -b -q f11_Incl_PhiK.C
root -l -b -q f11_Incl_XK.C
root -l -b -q f11_Incl_XL.C
root -l -b -q f11_Incl_XPhi.C

root -l -b -q f12_JE_KstarK.C
root -l -b -q f12_JE_LK.C
root -l -b -q f12_JE_OK.C
root -l -b -q f12_JE_OL.C
root -l -b -q f12_JE_OPhi.C
root -l -b -q f12_JE_OX.C
root -l -b -q f12_JE_PhiK.C
root -l -b -q f12_JE_XK.C
root -l -b -q f12_JE_XL.C
root -l -b -q f12_JE_XPhi.C

echo ==========================================
echo Incl ratio in center and peripheral
root -l -b -q f13_Incl_KstarK_Center.C
root -l -b -q f13_Incl_KstarK_Peripheral.C
root -l -b -q f13_Incl_LK_Center.C
root -l -b -q f13_Incl_LK_Peripheral.C
root -l -b -q f13_Incl_PhiK_Center.C
root -l -b -q f13_Incl_PhiK_Peripheral.C

echo ==========================================
echo Incl ratio in diff centrality 
root -l -b -q f14_Incl_KstarK_Cent_CRandRope.C
root -l -b -q f14_Incl_LK_Cent_CRandRope.C
root -l -b -q f14_Incl_OK_Cent_CRandRope.C
root -l -b -q f14_Incl_OL_Cent_CRandRope.C
root -l -b -q f14_Incl_OPhi_Cent_CRandRope.C
root -l -b -q f14_Incl_OX_Cent_CRandRope.C
root -l -b -q f14_Incl_PhiK_Cent_CRandRope.C
root -l -b -q f14_Incl_XK_Cent_CRandRope.C
root -l -b -q f14_Incl_XL_Cent_CRandRope.C
root -l -b -q f14_Incl_XPhi_Cent_CRandRope.C

root -l -b -q f15_Incl_KstarK_Cent_CR.C
root -l -b -q f15_Incl_LK_Cent_CR.C
root -l -b -q f15_Incl_OK_Cent_CR.C
root -l -b -q f15_Incl_OL_Cent_CR.C
root -l -b -q f15_Incl_OPhi_Cent_CR.C
root -l -b -q f15_Incl_OX_Cent_CR.C
root -l -b -q f15_Incl_PhiK_Cent_CR.C
root -l -b -q f15_Incl_XK_Cent_CR.C
root -l -b -q f15_Incl_XL_Cent_CR.C
root -l -b -q f15_Incl_XPhi_Cent_CR.C

root -l -b -q f16_Incl_KstarK_Cent_Rope.C
root -l -b -q f16_Incl_LK_Cent_Rope.C
root -l -b -q f16_Incl_OK_Cent_Rope.C
root -l -b -q f16_Incl_OL_Cent_Rope.C
root -l -b -q f16_Incl_OPhi_Cent_Rope.C
root -l -b -q f16_Incl_OX_Cent_Rope.C
root -l -b -q f16_Incl_PhiK_Cent_Rope.C
root -l -b -q f16_Incl_XK_Cent_Rope.C
root -l -b -q f16_Incl_XL_Cent_Rope.C
root -l -b -q f16_Incl_XPhi_Cent_Rope.C

echo ==========================================
echo JE ratio in diff centrality 
root -l -b -q f17_JE_KstarK_Cent_CRandRope.C
root -l -b -q f17_JE_LK_Cent_CRandRope.C
root -l -b -q f17_JE_OK_Cent_CRandRope.C
root -l -b -q f17_JE_OL_Cent_CRandRope.C
root -l -b -q f17_JE_OPhi_Cent_CRandRope.C
root -l -b -q f17_JE_OX_Cent_CRandRope.C
root -l -b -q f17_JE_PhiK_Cent_CRandRope.C
root -l -b -q f17_JE_XK_Cent_CRandRope.C
root -l -b -q f17_JE_XL_Cent_CRandRope.C
root -l -b -q f17_JE_XPhi_Cent_CRandRope.C

root -l -b -q f18_JE_KstarK_Cent_CR.C
root -l -b -q f18_JE_LK_Cent_CR.C
root -l -b -q f18_JE_OK_Cent_CR.C
root -l -b -q f18_JE_OL_Cent_CR.C
root -l -b -q f18_JE_OPhi_Cent_CR.C
root -l -b -q f18_JE_OX_Cent_CR.C
root -l -b -q f18_JE_PhiK_Cent_CR.C
root -l -b -q f18_JE_XK_Cent_CR.C
root -l -b -q f18_JE_XL_Cent_CR.C
root -l -b -q f18_JE_XPhi_Cent_CR.C

root -l -b -q f19_JE_KstarK_Cent_Rope.C
root -l -b -q f19_JE_LK_Cent_Rope.C
root -l -b -q f19_JE_OK_Cent_Rope.C
root -l -b -q f19_JE_OL_Cent_Rope.C
root -l -b -q f19_JE_OPhi_Cent_Rope.C
root -l -b -q f19_JE_OX_Cent_Rope.C
root -l -b -q f19_JE_PhiK_Cent_Rope.C
root -l -b -q f19_JE_XK_Cent_Rope.C
root -l -b -q f19_JE_XL_Cent_Rope.C
root -l -b -q f19_JE_XPhi_Cent_Rope.C

echo ==========================================
echo particle ratio to jet axis
root -l -b -q f20_KstarK_toJetRange.C
root -l -b -q f20_LK_toJetRange.C
root -l -b -q f20_OK_toJetRange.C
root -l -b -q f20_OL_toJetRange.C
root -l -b -q f20_OPhi_toJetRange.C
root -l -b -q f20_OX_toJetRange.C
root -l -b -q f20_PhiK_toJetRange.C
root -l -b -q f20_XK_toJetRange.C
root -l -b -q f20_XL_toJetRange.C
root -l -b -q f20_XPhi_toJetRange.C

root -l -b -q f21_KstarK_toJetRange_CR.C
root -l -b -q f21_LK_toJetRange_CR.C
root -l -b -q f21_OK_toJetRange_CR.C
root -l -b -q f21_OL_toJetRange_CR.C
root -l -b -q f21_OPhi_toJetRange_CR.C
root -l -b -q f21_OX_toJetRange_CR.C
root -l -b -q f21_PhiK_toJetRange_CR.C
root -l -b -q f21_XK_toJetRange_CR.C
root -l -b -q f21_XL_toJetRange_CR.C
root -l -b -q f21_XPhi_toJetRange_CR.C

root -l -b -q f22_KstarK_toJetRange_CRandRope.C
root -l -b -q f22_LK_toJetRange_CRandRope.C
root -l -b -q f22_OK_toJetRange_CRandRope.C
root -l -b -q f22_OL_toJetRange_CRandRope.C
root -l -b -q f22_OPhi_toJetRange_CRandRope.C
root -l -b -q f22_OX_toJetRange_CRandRope.C
root -l -b -q f22_PhiK_toJetRange_CRandRope.C
root -l -b -q f22_XK_toJetRange_CRandRope.C
root -l -b -q f22_XL_toJetRange_CRandRope.C
root -l -b -q f22_XPhi_toJetRange_CRandRope.C

root -l -b -q f23_KstarK_toJetRange_Rope.C
root -l -b -q f23_LK_toJetRange_Rope.C
root -l -b -q f23_OK_toJetRange_Rope.C
root -l -b -q f23_OL_toJetRange_Rope.C
root -l -b -q f23_OPhi_toJetRange_Rope.C
root -l -b -q f23_OX_toJetRange_Rope.C
root -l -b -q f23_PhiK_toJetRange_Rope.C
root -l -b -q f23_XK_toJetRange_Rope.C
root -l -b -q f23_XL_toJetRange_Rope.C
root -l -b -q f23_XPhi_toJetRange_Rope.C
echo ==========================================
echo cp figures
cp ./figure/pdf/* /home/cuipengyao/Phenomenon/note/figures/rope
cp ./figure/pdf/* /home/cuipengyao/Phenomenon/paper/draft/figures

exit 0
