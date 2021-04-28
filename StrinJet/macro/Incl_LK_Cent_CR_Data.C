#include "inc/PyJetUtils.h"

void Incl_LK_Cent_CR_Data(){
//=============================================================================

  TH1D* hD[2]; TGraphErrors* gD[2];
   hD[0] = GetDataC("data/HEPData_1807.11321v2.root", 82); 
   gD[0] = GetDataE("data/HEPData_1807.11321v2.root", 82); 
   hD[1] = GetDataC("data/HEPData_1807.11321v2.root", 78); 
   gD[1] = GetDataE("data/HEPData_1807.11321v2.root", 78); 

  TH1D* h1[2]; TH1D*h2[2]; TH1D* hR[2]; TGraph* gR[2];//Double_t dndeta[3];
  
  h1[0] = PtSpectrum(1, 0, 0, dCent[0], dCent[1], kFALSE, kFALSE); //Para1: "pp13TeV", "pp7TeV" 
  h2[0] = PtSpectrum(1, 0, 1, dCent[0], dCent[1], kFALSE, kFALSE); //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h1[1] = PtSpectrum(1, 0, 0, dCent[nc-2], dCent[nc-1], kFALSE, kFALSE); //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
  h2[1] = PtSpectrum(1, 0, 1, dCent[nc-2], dCent[nc-1], kFALSE, kFALSE); //Para4:Centmin 
                                                                   //Para5:Centmax 
                                                                   //Para6: jet cone: kTRUE, kFALSE 
                                                                   //Para7: PC: kTRUE, kFALSE 
  hR[0] = (TH1D*)h2[0]->Clone("hR_0"); hR[0]->Divide(h1[0]); 
  hR[1] = (TH1D*)h2[1]->Clone("hR_1"); hR[1]->Divide(h1[1]); 
 
  gR[0] = new TGraph(hR[0]); 
  gR[1] = new TGraph(hR[1]); 
//=============================================================================
  auto dflx(0.1), dfux(20.);
  auto dfly(0.), dfuy(1.3);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("#Lambda/K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("LKRatio_Incl_Cent_Data_cr"));
  can->SetLogx();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(hD[0], wcl[0], wmk[0], "same");
  DrawGraph(gD[0], wcl[0], "E2");
  DrawHisto(hD[1], wcl[1], wmk[1], "same");
  DrawGraph(gD[1], wcl[1], "E2");
  DrawGraph(gR[0], wcl[0], "L");
  DrawGraph(gR[1], wcl[1], "L");

  auto leg(new TLegend(0.54, 0.60, 0.8, 0.80)); SetupLegend(leg);
  leg->AddEntry(hD[0], Form("%.0f-%.2f%%(18.5)", dCent[0], dCent[1]), "L")->SetTextSizePixels(24);
  leg->AddEntry(hD[1], Form("%.0f-%.0f%%(0.2)", dCent[nc-2], dCent[nc-1]), "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV, V0M multiplicity class: 21.3, 2.3");
  tex->DrawLatex(0.16, 0.8, "sQCD + CR");
  tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));
  tex->DrawLatex(0.57, 0.82, "Cent(<d#it{N}_{ch}/d#eta>_{|#eta|<0.5})");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

