#include "inc/PyJetUtils.h"

void f1_TrkEta(){

  auto hD(GetDataC("data/HEPData_1004.3514v3.root", 6)); 
  auto gD = GetDataE("data/HEPData_1004.3514v3.root", 6); 
  TH1D* h[3];
  h[0] = TrkEta(1, 0);    //Para1: "pp13TeV", "pp7TeV"
  h[1] = TrkEta(1, 1);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2] = TrkEta(1, 2);
  
  TGraph* g[3];
  g[0] = new TGraph(h[0]);  
  g[1] = new TGraph(h[1]); 
  g[2] = new TGraph(h[2]); 

//=============================================================================
  auto dflx(-3.), dfux(3.);
  auto dfly(5.), dfuy(8.9);
  
  auto dlsx(0.05), dlsy(0.06);
  auto dtsx(0.05), dtsy(0.06);
  auto dtox(1.30), dtoy(0.80);
  
  TString stnx("#eta_{trk}");
  TString stny("#frac{d#it{N}}{#it{N}_{ev}d#eta}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("TrkEta"));
  //can->SetLogy();
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

  auto leg(new TLegend(0.65, 0.65, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(hD, "Exp data",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "Track #eta distribution");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

