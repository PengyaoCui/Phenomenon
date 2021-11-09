#include "inc/PyJetUtils.h"

void RatiowR(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_2005.11120.root", 43)); 
  //auto gD = GetDataE("data/HEPData_2005.11120.root", 43); 
//=============================================================================
 //Para1: "pp13TeV", "pp7TeV"
 //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
 //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
 //Para4: centmin
 //Para5: centmax

 TGraphErrors* g[4][5];
  int p;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Kstar", "Pion", "Kion", "Proton"};

  p=1;
  g[0][p-1] = (TGraphErrors*) PartoJet("Monash",  p, 0.5);
  g[1][p-1] = (TGraphErrors*) PartoJet("CR",      p, 0.5);
  g[2][p-1] = (TGraphErrors*) PartoJet("Rope",    p, 0.5);
  g[3][p-1] = (TGraphErrors*) PartoJet("CR+Rope", p, 0.5);
 
  p=2;
  g[0][p-1] = (TGraphErrors*) PartoJet("Monash",  p, 0.5);
  g[1][p-1] = (TGraphErrors*) PartoJet("CR",      p, 0.5);
  g[2][p-1] = (TGraphErrors*) PartoJet("Rope",    p, 0.5);
  g[3][p-1] = (TGraphErrors*) PartoJet("CR+Rope", p, 0.5);
 
  p=3;
  g[0][p-1] = (TGraphErrors*) PartoJet("Monash",  p, 5.);
  g[1][p-1] = (TGraphErrors*) PartoJet("CR",      p, 5.);
  g[2][p-1] = (TGraphErrors*) PartoJet("Rope",    p, 5.);
  g[3][p-1] = (TGraphErrors*) PartoJet("CR+Rope", p, 5.);
 
  p = 4; 
  g[0][p-1] = (TGraphErrors*) PartoJet("Monash",  p, 1.);
  g[1][p-1] = (TGraphErrors*) PartoJet("CR",      p, 1.);
  g[2][p-1] = (TGraphErrors*) PartoJet("Rope",    p, 1.);
  g[3][p-1] = (TGraphErrors*) PartoJet("CR+Rope", p, 1.);
  
  p = 5; 
  g[0][p-1] = (TGraphErrors*) PartoJet("Monash",  p, 1.);
  g[1][p-1] = (TGraphErrors*) PartoJet("CR",      p, 1.);
  g[2][p-1] = (TGraphErrors*) PartoJet("Rope",    p, 1.);
  g[3][p-1] = (TGraphErrors*) PartoJet("CR+Rope", p, 1.);
 
                                                  
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
  auto dfly(0.), dfuy(0.49);
  

  auto dlsx(0.035), dlsy(0.035);
  auto dtsx(0.035), dtsy(0.035);
  auto dtox(1.30), dtoy(1.60);
 
  TString stnx("#it{R}(p, jet)");
  TString stny("Ratio of yield to K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("StrtoK", 700, 700));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  //DrawGraph(gD, wcl[0], "E2");
  for(int i = 0; i < 5; i++ ){
    if(i == 1 || i==2) continue;
    g[0][i]->SetLineStyle(0);
    g[1][i]->SetLineStyle(2);
    g[2][i]->SetLineStyle(3);
    g[3][i]->SetLineStyle(5);
    DrawGraphError(g[0][i], wcl[i+1], wmk[0], "E3 PML same");
    DrawGraphError(g[1][i], wcl[i+1], wmk[1], "E3 PML same");
    DrawGraphError(g[2][i], wcl[i+1], wmk[2], "E3 PML same");
    DrawGraphError(g[3][i], wcl[i+1], wmk[3], "E3 PML same");
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
  tex->DrawLatex(0.16, 0.91, "pp #sqrt{#it{s}} = 7 TeV  Strange particle to K^{0}_{S} ratio in jets");

  tex->DrawLatex(0.74, 0.75, "#color[799]{K*^{0}/K^{0}_{S}}");
  tex->DrawLatex(0.44, 0.32, "#color[617]{#phi/K^{0}_{S}}");
  tex->DrawLatex(0.24, 0.65, "#color[633]{(#Lambda + #bar{#Lambda})/2K^{0}_{S}}");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);


  auto Can(MakeCanvas("MultiStrtoK", 700, 700));
  dfuy = 0.23;
  auto hFm(can->DrawFrame(dflx, dfly, dfux, dfuy));

  SetupFrame(hFm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hFm->GetXaxis()->SetNdivisions(505);
  hFm->GetYaxis()->SetNdivisions(505);

  for(int i = 1; i < 3; i++ ){
    g[0][i]->SetLineStyle(0);
    g[1][i]->SetLineStyle(2);
    g[2][i]->SetLineStyle(3);
    g[3][i]->SetLineStyle(5);
    DrawGraphError(g[0][i], wcl[i+1], wmk[0], "E3 PML same");
    DrawGraphError(g[1][i], wcl[i+1], wmk[1], "E3 PML same");
    DrawGraphError(g[2][i], wcl[i+1], wmk[2], "E3 PML same");
    DrawGraphError(g[3][i], wcl[i+1], wmk[3], "E3 PML same");
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
  Tex->DrawLatex(0.16, 0.91, "pp #sqrt{#it{s}} = 7 TeV  Strange particle to K^{0}_{S} ratio in jets");
  //tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));

  Tex->DrawLatex(0.45, 0.47, "#color[601]{(#Xi^{-} + #bar{#Xi}^{+})/2K^{0}_{S}}");
  Tex->DrawLatex(0.16, 0.2, "#color[419]{(#Omega^{-} + #bar{#Omega}^{+})/2K^{0}_{S} (#times 10)}");

  Can->SaveAs(Form("./figure/eps/%s.eps", Can->GetName()));
  Can->SaveAs(Form("./figure/pdf/%s.pdf", Can->GetName()));
  Can->SaveAs(Form("./figure/png/%s.png", Can->GetName()));
  CanvasEnd(Can);

  return;
}

