#include "inc/PyJetUtils.h"

void dNmiddEta_TwoPad(){
//=============================================================================
  auto hD(GetDataC("data/HEPData_1004.3514v3.root", 3)); 
  auto gD = GetDataE("data/HEPData_1004.3514v3.root", 3); 

  TH1D* h[3];
  TH1D* hRebin[3];
  h[0] = dNmiddEta(1, 0, kFALSE);   //Para1: "pp13TeV", "pp7TeV"
  h[1] = dNmiddEta(1, 1, kFALSE);   //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2] = dNmiddEta(1, 2, kFALSE);
  hRebin[0] = (TH1D*)h[0]->Clone("hRebin_0");   //Para1: "pp13TeV", "pp7TeV"
  hRebin[1] = (TH1D*)h[1]->Clone("hRebin_1");   //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  hRebin[2] = (TH1D*)h[2]->Clone("hRebin_2");
  h[0] -> Rebin(5);NormBinningHistogram(h[0]);
  h[1] -> Rebin(5);NormBinningHistogram(h[1]); 
  h[2] -> Rebin(5);NormBinningHistogram(h[2]);
  //DeNormBinningHistogram(hRebin[0]); 
  //DeNormBinningHistogram(hRebin[1]); 
  //DeNormBinningHistogram(hRebin[2]);
  hRebin[0] = MakeRebinTH1D(hRebin[0], hD); NormBinningHistogram(hRebin[0]);
  hRebin[1] = MakeRebinTH1D(hRebin[1], hD); NormBinningHistogram(hRebin[1]);   
  hRebin[2] = MakeRebinTH1D(hRebin[2], hD); NormBinningHistogram(hRebin[2]);

  for(int i = 0; i<3; i++) hRebin[i]->Divide(hD);

  auto G = new TGraph(hD);
  TGraph* g[3];
  TGraph* gRebin[3];
  g[0] = new TGraph(h[0]);  gRebin[0] = new TGraph(hRebin[0]);
  g[1] = new TGraph(h[1]);  gRebin[1] = new TGraph(hRebin[1]);
  g[2] = new TGraph(h[2]);  gRebin[2] = new TGraph(hRebin[2]);

//=============================================================================
  auto dflx(0.), dfux(80.);
  auto dfly(4e-5), dfuy(1.2);

  auto dlsx(0.06), dlsy(0.06);
  auto dtsx(0.06), dtsy(0.06);
  auto dtox(1.30), dtoy(0.90);
  
  TString stnx("Multiplicity #it{N}_{ch}");
  TString stny("Probability #it{P}(#it{N}_{ch})");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("dNmiddEta"), 700, 700));
  auto padT = MakePadT("padT"); can->cd();
  auto padB = MakePadB("padB"); can->cd();
  padT->cd();

  padT->SetLogy();
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
  leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "BLC",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "BLC + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "|#eta| < 1");
//==============================================
  can->cd();
  padB->cd();
  dfly = 0., dfuy = 1.3;

  dlsx = 0.1; dlsy = 0.11;
  dtsx = 0.11; dtsy = 0.11;
  dtox = 1.1; dtoy = 0.50;
  stny = "Ratio to Data";

  auto hfmb(padB->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmb, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmb->GetXaxis()->SetNdivisions(505);
  hfmb->GetYaxis()->SetNdivisions(505);
  hfmb->GetXaxis()->SetTickLength(0.07);
  gRebin[0]->SetLineStyle(0);
  gRebin[1]->SetLineStyle(1);
  gRebin[2]->SetLineStyle(2);
  
  DrawGraph(gRebin[0], wcl[0], "L");
  DrawGraph(gRebin[1], wcl[1], "L");
  DrawGraph(gRebin[2], wcl[2], "L");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

