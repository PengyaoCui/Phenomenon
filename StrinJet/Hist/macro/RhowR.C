#include "inc/PyJetUtils.h"

void RhowR(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_2005.11120.root", 43)); 
  //auto gD = GetDataE("data/HEPData_2005.11120.root", 43); 
//=============================================================================
 //Para1: "pp13TeV", "pp7TeV"
 //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
 //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
 //Para4: centmin
 //Para5: centmax

 TGraphErrors* g[4][6];
  int p;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Kstar", "Pion", "Kion", "Proton"};
  p=0;
  g[0][p] = (TGraphErrors*) PartoJet("Monash",  p, 4.);
  g[1][p] = (TGraphErrors*) PartoJet("CR",      p, 4.);
  g[2][p] = (TGraphErrors*) PartoJet("Rope",    p, 4.);
  g[3][p] = (TGraphErrors*) PartoJet("CR+Rope", p, 4.);

  p=1;
  g[0][p] = (TGraphErrors*) PartoJet("Monash",  p, 1.);
  g[1][p] = (TGraphErrors*) PartoJet("CR",      p, 1.);
  g[2][p] = (TGraphErrors*) PartoJet("Rope",    p, 1.);
  g[3][p] = (TGraphErrors*) PartoJet("CR+Rope", p, 1.);
 
  p=2;
  g[0][p] = (TGraphErrors*) PartoJet("Monash",  p, 2.);
  g[1][p] = (TGraphErrors*) PartoJet("CR",      p, 2.);
  g[2][p] = (TGraphErrors*) PartoJet("Rope",    p, 2.);
  g[3][p] = (TGraphErrors*) PartoJet("CR+Rope", p, 2.);
 
  p=3;
  g[0][p] = (TGraphErrors*) PartoJet("Monash",  p, 12.);
  g[1][p] = (TGraphErrors*) PartoJet("CR",      p, 12.);
  g[2][p] = (TGraphErrors*) PartoJet("Rope",    p, 12.);
  g[3][p] = (TGraphErrors*) PartoJet("CR+Rope", p, 12.);
 
  p = 4;
  g[0][p] = (TGraphErrors*) PartoJet("Monash",  p, 12.);
  g[1][p] = (TGraphErrors*) PartoJet("CR",      p, 12.);
  g[2][p] = (TGraphErrors*) PartoJet("Rope",    p, 12.);
  g[3][p] = (TGraphErrors*) PartoJet("CR+Rope", p, 12.);
  
  p = 5;
  g[0][p] = (TGraphErrors*) PartoJet("Monash",  p, 6.);
  g[1][p] = (TGraphErrors*) PartoJet("CR",      p, 6.);
  g[2][p] = (TGraphErrors*) PartoJet("Rope",    p, 6.);
  g[3][p] = (TGraphErrors*) PartoJet("CR+Rope", p, 6.);
 
                                                  
  //for(int i=0; i<6; i++){                         
  //  h[0][i]->Divide(hPi[0]);
  //  h[1][i]->Divide(hPi[1]);
  //  h[2][i]->Divide(hPi[2]);

  //  g[0][i] = new TGraph(h[0][i]);
  //  g[1][i] = new TGraph(h[1][i]);
  //  g[2][i] = new TGraph(h[2][i]);
  //}

  
//=============================================================================
  auto dflx(0.), dfux(0.4);
  auto dfly(4e-2), dfuy(9e0);
  

  auto dlsx(0.035), dlsy(0.035);
  auto dtsx(0.035), dtsy(0.035);
  auto dtox(1.30), dtoy(1.60);
 
  TString stnx("#it{R}(p, jet)");
  TString stny("#rho");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("StrtoJ", 700, 700));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  //DrawGraph(gD, wcl[0], "E2");
  for(int i = 0; i < 6; i++ ){
    if(i == 2 || i==3) continue;
    g[0][i]->SetLineStyle(0);
    g[1][i]->SetLineStyle(2);
    g[2][i]->SetLineStyle(3);
    g[3][i]->SetLineStyle(5);
    DrawGraphError(g[0][i], wcl[i], wmk[0], "E3 PML same");
    DrawGraphError(g[1][i], wcl[i], wmk[1], "E3 PML same");
    DrawGraphError(g[2][i], wcl[i], wmk[2], "E3 PML same");
    DrawGraphError(g[3][i], wcl[i], wmk[3], "E3 PML same");
  }


  auto leg(new TLegend(0.16, 0.81, 1., 0.9)); SetupLegend(leg);
  leg->SetNColumns(4);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0][0], "Monash",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[1][0], "CR",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[2][0], "Rope",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[3][0], "CR + Rope",  "LP")->SetTextSizePixels(24);
  leg->Draw();
 

  //auto leg(new TLegend(0.16, 0.81, 0.8, 0.9)); SetupLegend(leg);
  //leg->SetNColumns(3);
  ////leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  //leg->AddEntry(g[0][0], "BLC",  "L")->SetTextSizePixels(24);
  //leg->AddEntry(g[1][0], "Rope",  "L")->SetTextSizePixels(24);
  //leg->AddEntry(g[2][0], "BLC + Rope",  "L")->SetTextSizePixels(24);
  //leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.91, "pp #sqrt{#it{s}} = 7 TeV  Strange particle in jets");

  
  tex->DrawLatex(0.5, 0.72, "#color[1]{K^{0}_{S} (#times 4)}");
  tex->DrawLatex(0.15, 0.74, "#color[799]{K*^{0} (#times 6)}");
  tex->DrawLatex(0.15, 0.54, "#color[617]{#phi (#times 12)}"); 
  tex->DrawLatex(0.3, 0.35, "#color[633]{#Lambda + #bar{#Lambda}}");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

  auto Can(MakeCanvas("MultiStrtoJ", 700, 700));
  Can->SetLogy();
  dfly = 1e-4; dfuy = 4e0;
  auto hFm(Can->DrawFrame(dflx, dfly, dfux, dfuy));

  SetupFrame(hFm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hFm->GetXaxis()->SetNdivisions(505);
  hFm->GetYaxis()->SetNdivisions(505);

  for(int i = 2; i < 4; i++ ){
    g[0][i]->SetLineStyle(0);
    g[1][i]->SetLineStyle(2);
    g[2][i]->SetLineStyle(3);
    g[3][i]->SetLineStyle(5);
    DrawGraphError(g[0][i], wcl[i], wmk[0], "E3 PML same");
    DrawGraphError(g[1][i], wcl[i], wmk[1], "E3 PML same");
    DrawGraphError(g[2][i], wcl[i], wmk[2], "E3 PML same");
    DrawGraphError(g[3][i], wcl[i], wmk[3], "E3 PML same");
  }
  auto Leg(new TLegend(0.16, 0.81, 1., 0.9)); SetupLegend(Leg);
  Leg->SetNColumns(4);
  Leg->AddEntry(g[0][0], "Monash",  "LP")->SetTextSizePixels(24);
  Leg->AddEntry(g[1][0], "CR",  "LP")->SetTextSizePixels(24);
  Leg->AddEntry(g[2][0], "Rope",  "LP")->SetTextSizePixels(24);
  Leg->AddEntry(g[3][0], "CR + Rope",  "LP")->SetTextSizePixels(24);
  Leg->Draw();



  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(24);
  Tex->DrawLatex(0.16, 0.91, "pp #sqrt{#it{s}} = 7 TeV  Strange particle in jets");
  //tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));
  Tex->DrawLatex(0.70, 0.62, "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}");
  Tex->DrawLatex(0.42, 0.43, "#color[419]{#Omega^{-} + #bar{#Omega}^{+} (#times 12)}");


  Can->SaveAs(Form("./figure/eps/%s.eps", Can->GetName()));
  Can->SaveAs(Form("./figure/pdf/%s.pdf", Can->GetName()));
  Can->SaveAs(Form("./figure/png/%s.png", Can->GetName()));
  CanvasEnd(Can);
  return;
}

