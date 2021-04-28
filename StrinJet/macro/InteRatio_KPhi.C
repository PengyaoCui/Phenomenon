#include "inc/PyJetUtils.h"

void InteRatio_KPhi(){
//=============================================================================
#if 0  //different multiplicity bin number
  auto hDPhi  (GetDataC("data/HEPData_1807.11321v2.root", 97)); //PhiPi
  auto hDK (GetDataC("data/HEPData_1606.07424v2.root", 36)); 

  Double_t dPhiVal[nc-1]; Double_t dKVal[nc-1]; Double_t dVal[nc-1]; 
  Double_t dPhiErr[nc-1]; Double_t dKErr[nc-1];
  Double_t dX[nc-1];
  Int_t j = 0;
  auto v(0.), e(0.);
  for(Int_t i = 1; i<=hDPhi->GetNbinsX(); i++){
    v = hDPhi->GetBinContent(i);
    e = hDPhi->GetBinError(i);
    if(v!=0.){
      dPhiVal[j] = v;
      dPhiErr[j] = e;
      j=j+1;
    }
    v=e=0.;
  }
  
  auto hD = (TH1D*)hDK->Clone("hD"); hD->Reset();
  j=0;
  for(Int_t i = 1; i<=hDK->GetNbinsX(); i++){
    v=e=0.; 
    v = hDK->GetBinContent(i);
    e = hDK->GetBinError(i);
    if(v==0.){
      hD->SetBinContent(i, 0.); 
      hD->SetBinError(i, 0.); 
    }
    if(v!=0.){
      dKVal[j] = v;
      dKErr[j] = e;
      cout<<j<<endl;
      cout<<dKVal[j]<<endl;
      dVal[j] =  dKVal[j]/dPhiVal[j];
      dX[j] = hD->GetBinCenter(i);
      hD->SetBinContent(i, dVal[j]);
      hD->SetBinError(i, TMath::Sqrt(dKErr[j]*dKErr[j] + dPhiErr[j]*dPhiErr[j]));
      j=j+1;
    }
  }
  auto gDPhi = GetDataE("data/HEPData_1807.11321v2.root", 97); 
  auto gDK = GetDataE("data/HEPData_1606.07424v2.root", 36); 
 
   
  Double_t dPhiEy[nc-2]; Double_t dKEy[nc-2]; Double_t dEy[nc-2];
  Double_t dPhiEx[nc-2]; Double_t dKEx[nc-2]; Double_t dEx[nc-2];
  for(Int_t i=1; i<=nc-2; i++){
    dPhiEy[i-1] = gDPhi->GetErrorY(i); dKEy[i-1] = gDK->GetErrorY(i); 
    dPhiEx[i-1] = gDPhi->GetErrorX(i); dKEx[i-1] = gDK->GetErrorX(i); 
    dEx[i-1] = dPhiEx[i-1];
    dEy[i] = TMath::Sqrt(dPhiEy[i]*dPhiEy[i] + dKEy[i]*dKEy[i]);
  }
  auto gD(new TGraphErrors(nc-2, dX, dVal, dEx, dEy));
#endif
  TGraph* g[3];
  g[0] = InteRatio(1, 0, 0, 4);    //Para1: "pp13TeV", "pp7TeV" 
  g[1] = InteRatio(1, 1, 0, 4);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  g[2] = InteRatio(1, 2, 0, 4);    //Para3:Nulmerator "Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
                                   //Para4:Denomenator "Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
//=============================================================================
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(25.);
  auto dfly(12.), dfuy(18.5);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
  TString stny("K^{0}_{S}/#phi");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("Inte_KshortPhiRatio"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(1);
  g[2]->SetLineStyle(2);
  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "L");
  DrawGraph(g[1], wcl[1], "L");
  DrawGraph(g[2], wcl[2], "L");

  auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
  //leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

