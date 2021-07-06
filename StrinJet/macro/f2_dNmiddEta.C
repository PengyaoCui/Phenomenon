#include "inc/PyJetUtils.h"

void f2_dNmiddEta(){
//=============================================================================
  auto hD(GetDataC("data/HEPData_1004.3514v3.root", 3)); 
  auto gD = GetDataE("data/HEPData_1004.3514v3.root", 3); 

  TH1D* h[3];
  h[0] = dNmiddEta(1, 0);    //Para1: "pp13TeV", "pp7TeV"
  h[1] = dNmiddEta(1, 1);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2] = dNmiddEta(1, 2);


  TGraph* g[3];
  g[0] = new TGraph(h[0]);  
  g[1] = new TGraph(h[1]); 
  g[2] = new TGraph(h[2]); 

//=============================================================================
  auto dflx(0.), dfux(80.);
  auto dfly(7e-6), dfuy(4.);
  

  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("d#it{N}_{mid}");
  TString stny("Probability density");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("dNmiddEta")));
  can->SetLogy();
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
  leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "|#eta_{Trk}| < 0.5");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

