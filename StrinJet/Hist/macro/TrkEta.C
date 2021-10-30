#include "inc/PyJetUtils.h"

void TrkEta(){

  auto hD(GetDataC("data/HEPData_1004.3514v3.root", 6)); 
  auto gD = GetDataE("data/HEPData_1004.3514v3.root", 6); 
  TH1D* h[4];
  h[0] = Trketa("Monash");    //Para1: "Monash", "CR", "Rope", "CR+Rope"
  h[1] = Trketa("CR");    
  h[2] = Trketa("Rope");    
  h[3] = Trketa("CR+Rope");    
  
  TGraph* g[4];
  g[0] = new TGraph(h[0]);  
  g[1] = new TGraph(h[1]); 
  g[2] = new TGraph(h[2]); 
  g[3] = new TGraph(h[3]); 

//=============================================================================
  auto dflx(-3.), dfux(3.);
  auto dfly(5.), dfuy(8.9);
  
  auto dlsx(0.05), dlsy(0.06);
  auto dtsx(0.05), dtsy(0.06);
  auto dtox(1.30), dtoy(0.80);
  
  TString stnx("#eta");
  TString stny("d#it{N}/d#eta");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("TrkEta"));
  //can->SetLogy();
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
  //tex->DrawLatex(0.16, 0.8, "Track #eta distribution");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

