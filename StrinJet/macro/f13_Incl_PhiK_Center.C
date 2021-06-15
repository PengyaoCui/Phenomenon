#include "inc/PyJetUtils.h"

void f13_Incl_PhiK_Center(){
//=============================================================================
  auto hD(GetDataC("data/HEPData_1910.14397v1.root", 49)); 
  auto gD = GetDataE("data/HEPData_1910.14397v1.root", 49); 

  TH1D* h1[3]; TH1D*h2[3]; TH1D* hR[3]; TGraph* g[3];
  Int_t c[] = {0, 10, 40, 100}; Int_t n = sizeof(c)/sizeof(Int_t) - 1;
  //Para1: "pp13TeV", "pp7TeV" 
  //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
  //Para4:Centmin 
  //Para5:Centmax 
  //Para6: jet cone: kTRUE, kFALSE 
  //Para7: PC: kTRUE, kFALSE 
  for(int i=0; i<3; i++)h1[i] = PtSpectrum(1, i, 0, dCent[1], dCent[2], kFALSE, kFALSE);
  for(int i=0; i<3; i++)h2[i] = PtSpectrum(1, i, 4, dCent[1], dCent[2], kFALSE, kFALSE);

  
  for(int i=0; i<3; i++){
    hR[i] = (TH1D*)h2[i]->Clone(Form("hR_%d", i));
    hR[i]->Divide(h1[i]); 
    g[i] = new TGraph(hR[i]);
  }
  
//=============================================================================
  auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(8.);
  auto dfly(0.), dfuy(2.*y);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("#phi/K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("PhiKRatio_Incl_Center"));
  //can->SetLogy();
  //can->SetLogx();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(1);
  g[2]->SetLineStyle(2);
  DrawHisto(hD, wcl[0], wmk[0], "same");
  DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "L");
  DrawGraph(g[1], wcl[1], "L");
  DrawGraph(g[2], wcl[2], "L");

  auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(hD, "Data(13 TeV)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "CR", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope", "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope", "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, Form("Cent: %.1f-%.1f%%", dCent[1], dCent[2]));
  tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

