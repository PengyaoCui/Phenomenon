#include "inc/PyJetUtils.h"

void dNmiddEta(){
//=============================================================================
  auto hD(GetDataC("data/HEPData_1004.3514v3.root", 3)); 
  auto gD = GetDataE("data/HEPData_1004.3514v3.root", 3); 

  TH1D* h[4];
  h[0] = dNmdEta("Monash", kFALSE);    //Para1: "Monash", "CR", "Rope", "CR+Rope"
  h[1] = dNmdEta("CR", kFALSE);    //Para2: Rebin or not 
  h[2] = dNmdEta("Rope", kFALSE);
  h[3] = dNmdEta("CR+Rope", kFALSE);


  TGraph* g[4];
  g[0] = new TGraph(h[0]);  
  g[1] = new TGraph(h[1]); 
  g[2] = new TGraph(h[2]); 
  g[3] = new TGraph(h[3]); 

//=============================================================================
  auto dflx(0.), dfux(80.);
  auto dfly(7e-6), dfuy(4.);
  

  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("Multiplicity #it{N}_{ch}");
  TString stny("Probability #it{P}(#it{N}_{ch})");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("dNmiddEta")));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(2);
  g[2]->SetLineStyle(3);
  g[3]->SetLineStyle(5);
  DrawHisto(hD, wcl[0], wmk[0], "same");
  DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "L");
  DrawGraph(g[1], wcl[1], "L");
  DrawGraph(g[2], wcl[2], "L");
  DrawGraph(g[3], wcl[3], "L");

  auto leg(new TLegend(0.65, 0.65, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "Monash",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[3], "CR + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "|#eta| < 1");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

