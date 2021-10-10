#include "inc/PyJetUtils.h"

void InteRatio_JE(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42)); 
  //auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42); 

  TGraph* g[3][6];
  int p = 0;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
  g[0][p] = RatioToPi(1, 0, p, kTRUE, kFALSE, 4);g[0][0]->SetName((sp[p] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
  g[1][p] = RatioToPi(1, 1, p, kTRUE, kFALSE, 4);g[1][0]->SetName((sp[p] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  g[2][p] = RatioToPi(1, 2, p, kTRUE, kFALSE, 4);g[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 5;//Kstar
  g[0][p] = RatioToPi(1, 0, 8, kTRUE, kFALSE, 5);g[0][0]->SetName((sp[8] + sm[0]).Data());
  g[1][p] = RatioToPi(1, 1, 8, kTRUE, kFALSE, 5);g[1][0]->SetName((sp[8] + sm[1]).Data());
  g[2][p] = RatioToPi(1, 2, 8, kTRUE, kFALSE, 5);g[2][0]->SetName((sp[8] + sm[2]).Data());


  p = 4;//Phi
  g[0][p] = RatioToPi(1, 0, p, kTRUE, kFALSE, 12);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = RatioToPi(1, 1, p, kTRUE, kFALSE, 12);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = RatioToPi(1, 2, p, kTRUE, kFALSE, 12);g[2][0]->SetName((sp[p] + sm[2]).Data());
  
  p = 1;//Lambda
  g[0][p] = RatioToPi(1, 0, p, kTRUE, kFALSE, 1);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = RatioToPi(1, 1, p, kTRUE, kFALSE, 1);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = RatioToPi(1, 2, p, kTRUE, kFALSE, 1);g[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 2;//Xi
  g[0][p] = RatioToPi(1, 0, p, kTRUE, kFALSE, 2);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = RatioToPi(1, 1, p, kTRUE, kFALSE, 2);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = RatioToPi(1, 2, p, kTRUE, kFALSE, 2);g[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 3;//Omega
  g[0][p] = RatioToPi(1, 0, p, kTRUE, kFALSE, 12);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = RatioToPi(1, 1, p, kTRUE, kFALSE, 12);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = RatioToPi(1, 2, p, kTRUE, kFALSE, 12);g[2][0]->SetName((sp[p] + sm[2]).Data());
//=============================================================================
  //Double_t x, y;
  //g[2]->GetPoint(nc-2, x, y);
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(30.);
  auto dfly(1e-4), dfuy(2.);
  

  auto dlsx(0.04), dlsy(0.04);
  auto dtsx(0.04), dtsy(0.04);
  auto dtox(1.30), dtoy(1.2);

  TString stnx("#LTd#it{N}_{ch}/d#eta#GT_{|#eta|<0.5}");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #Delta#eta #Delta#varphi)");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #it{A}_{acc})");
  TString stny("Ratio of yields to #pi");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

  
  auto can(MakeCanvas("InteRatio_JE", 600, 800));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  for(int i = 0; i < 6; i++ ){
    g[0][i]->SetLineStyle(5);
    g[1][i]->SetLineStyle(3);
    g[2][i]->SetLineStyle(0);
    DrawGraph(g[0][i], wcl[i], "L");
    DrawGraph(g[1][i], wcl[i], "L");
    DrawGraph(g[2][i], wcl[i], "L");
  }


  auto leg(new TLegend(0.7, 0.18, 1., 0.34)); SetupLegend(leg);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0][0], "BLC",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1][0], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2][0], "BLC + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();


  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(28);
  tex->DrawLatex(0.16, 0.93, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.2, "Strange particle to #pi ratio in jets");
  
  
  tex->DrawLatex(0.74, 0.8, "#color[1]{K^{0}_{S} (#times 4)}");
  tex->DrawLatex(0.74, 0.74, "#color[799]{K*^{0} (#times 5)}");
  tex->DrawLatex(0.74, 0.68, "#color[617]{#phi (#times 12)}"); 
  tex->DrawLatex(0.74, 0.59, "#color[633]{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.72, 0.53, "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}");
  tex->DrawLatex(0.72, 0.45, "#color[419]{#Omega^{-} + #bar{#Omega}^{+} (#times 12)}");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

