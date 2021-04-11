#include "inc/PyJetUtils.h"

void dNfwddEta(){

  TH1D* h[3];
  h[0] = dNfwddEta(1, 0);    //Para1: "pp13TeV", "pp7TeV"
  h[1] = dNfwddEta(1, 1);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2] = dNfwddEta(1, 2);

  TH1D* hR[2];
  hR[0]=(TH1D*)h[0]->Clone("hR0");hR[0]->Divide(h[2]);
  hR[1]=(TH1D*)h[1]->Clone("hR1");hR[1]->Divide(h[2]);
//=============================================================================
  auto dflx(0.), dfux(210.);
  auto dfly(1e-7), dfuy(2e2);
  
  auto dlsx(0.05), dlsy(0.06);
  auto dtsx(0.05), dtsy(0.06);
  auto dtox(1.30), dtoy(0.80);
  
  TString stnx("d#it{N}_{fwd}/d#eta");
  TString stny("Probability density");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("dNfwddEta"));
  auto padT = MakePadT("padT"); can->cd();
  auto padB = MakePadB("padB"); can->cd();
  padT->cd(); 
  padT->SetLogy();
  auto hfm(padT->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
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
  tex->DrawLatex(0.16, 0.85, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.75, "Track #eta distribution");

  can->cd();
  padB->cd(); 
  dfly = 0.85, dfuy = 1.6;
  
  dlsx = 0.11; dlsy = 0.11;
  dtsx = 0.11; dtsy = 0.11;
  dtox = 1.10; dtoy = 0.40;
  stny = "CR+Rope as Ref.";
  
  auto hfmb(padB->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmb, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmb->GetXaxis()->SetNdivisions(505);
  hfmb->GetYaxis()->SetNdivisions(503);
  hfmb->GetXaxis()->SetTickLength(0.07);
  
  DrawHisto(hR[0], wcl[0], wmk[0], "same");
  DrawHisto(hR[1], wcl[1], wmk[1], "same");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  return;
}

