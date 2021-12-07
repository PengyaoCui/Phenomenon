#include "inc/PyJetUtils.h"

void InteSpect_Kshort(){
//=============================================================================
  auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42)); 
  auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42); 

  int p = 0;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Kstar", "Pion", "Kion", "Proton"};
  TGraphErrors* g[4];
  g[0] = InteSpectrum("Monash",  p, kFALSE, kFALSE, 1);//Para1: "Monash", "CR", "Rope", "CR+Rope" 
  g[1] = InteSpectrum("CR",      p, kFALSE, kFALSE, 1);//Para2: particle 
  g[2] = InteSpectrum("Rope",    p, kFALSE, kFALSE, 1);//Para3: Is JE? 
  g[3] = InteSpectrum("CR+Rope", p, kFALSE, kFALSE, 1);//Para4: Is UE?
                                                      //Para5: scale
  
  //TGraph* g[3];
  //g[0] = InteSpectrum(1, 0, p);g[0]->SetName((sp[i] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
  //g[1] = InteSpectrum(1, 1, p);g[1]->SetName((sp[i] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  //g[2] = InteSpectrum(1, 2, p);g[2]->SetName((sp[i] + sm[2]).Data());

//=============================================================================
  //Double_t x, y;
  //g[2]->GetPoint(nc-2, x, y);
  auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(30.);
  auto dfly(0.), dfuy(2.2);
  

  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#LTd#it{N}_{ch}/d#eta#GT_{|#eta|<0.5}");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #Delta#eta #Delta#varphi)");
  TString stny("d#it{N}/d#it{y}");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("%s_InteSpectrum", sp[p].Data())));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(2);
  g[2]->SetLineStyle(3);
  g[3]->SetLineStyle(5);


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
  //DrawGraph(g[0], wcl[0], "L");
  //DrawGraph(g[1], wcl[1], "L");
  //DrawGraph(g[2], wcl[2], "L");

  auto leg(new TLegend(0.7, 0.72, 1., 0.92)); SetupLegend(leg);
  leg->AddEntry(g[0], "Monash",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[3], "CR + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();
  auto Leg(new TLegend(0.16, 0.75, 0.6, 0.85)); SetupLegend(Leg);
  Leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
  Leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, " pp #sqrt{#it{s}} = 7 TeV");
  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(34);
  Tex->DrawLatex(0.2, 0.6, Form("K^{0}_{S}"));
  Tex->DrawLatex(0.85, 0.4, "(a)");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

