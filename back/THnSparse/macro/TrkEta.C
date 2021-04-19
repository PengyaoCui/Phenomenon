#include "inc/PyJetUtils.h"

void TrkEta(){
//=============================================================================
  
  TH1D* h[3];
  h[0] = TrkEta(1, 0);    //Para1: "pp13TeV", "pp7TeV" 
  h[1] = TrkEta(1, 1);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2] = TrkEta(1, 2);    

//=============================================================================
  auto dflx(-5.), dfux(5.);
  auto dfly(0.), dfuy(0.038);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#eta_{trk}");
  TString stny("Probability density");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("TrkEta"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(503);
  hfm->GetYaxis()->SetNdivisions(503);

  DrawHisto(h[0], wcl[0], wmk[0], "same");
  DrawHisto(h[1], wcl[1], wmk[1], "same");
  DrawHisto(h[2], wcl[2], wmk[2], "same");

  auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(h[0], "CR",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "Rope",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "CR + Rope",  "P")->SetTextSizePixels(24);
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

