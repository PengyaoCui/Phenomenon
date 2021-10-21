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

  TH1D* h[3][6]; TGraph* g[3][5];
  int p = 0;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());
 
  p = 5;//Kstar
  h[0][p] = PartoJet(1, 0, 8);h[0][0]->SetName((sp[8] + sm[0]).Data());
  h[1][p] = PartoJet(1, 1, 8);h[1][0]->SetName((sp[8] + sm[1]).Data());
  h[2][p] = PartoJet(1, 2, 8);h[2][0]->SetName((sp[8] + sm[2]).Data());

  p = 4;//Phi
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 1;//Lambda
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 2;//Xi
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 3;//Omega
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());h[0][p]->Scale(10);
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());h[1][p]->Scale(10);
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());h[2][p]->Scale(10);

  
 
                                                  
  //for(int i=0; i<6; i++){                         
  //  h[0][i]->Divide(hPi[0]);
  //  h[1][i]->Divide(hPi[1]);
  //  h[2][i]->Divide(hPi[2]);

  //  g[0][i] = new TGraph(h[0][i]);
  //  g[1][i] = new TGraph(h[1][i]);
  //  g[2][i] = new TGraph(h[2][i]);
  //}

  for(int i=1; i<6; i++){                         
    h[0][i]->Divide(h[0][0]);
    h[1][i]->Divide(h[1][0]);
    h[2][i]->Divide(h[2][0]);

    g[0][i-1] = new TGraph(h[0][i]);
    g[1][i-1] = new TGraph(h[1][i]);
    g[2][i-1] = new TGraph(h[2][i]);
  }



  
//=============================================================================
  auto dflx(0.), dfux(0.4);
  auto dfly(0.), dfuy(0.49);
  

  auto dlsx(0.035), dlsy(0.035);
  auto dtsx(0.035), dtsy(0.035);
  auto dtox(1.30), dtoy(1.30);
 
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
  for(int i = 0; i < 5; i++ ){
    g[0][i]->SetLineStyle(5);
    g[1][i]->SetLineStyle(3);
    g[2][i]->SetLineStyle(0);
  }
  DrawGraph(g[0][0], wcl[1], "L");
  DrawGraph(g[1][0], wcl[1], "L");
  DrawGraph(g[2][0], wcl[1], "L");
  
  DrawGraph(g[0][3], wcl[4], "L");
  DrawGraph(g[1][3], wcl[4], "L");
  DrawGraph(g[2][3], wcl[4], "L");
  
  DrawGraph(g[0][4], wcl[5], "L");
  DrawGraph(g[1][4], wcl[5], "L");
  DrawGraph(g[2][4], wcl[5], "L");

  auto leg(new TLegend(0.16, 0.81, 0.8, 0.9)); SetupLegend(leg);
  leg->SetNColumns(3);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0][0], "BLC",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1][0], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2][0], "BLC + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.91, "pp #sqrt{#it{s}} = 7 TeV  Strange particle to K^{0}_{S} ratio in jets");
  //tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));

  tex->DrawLatex(0.74, 0.75, "#color[799]{K*^{0}/K^{0}_{S}}");
  tex->DrawLatex(0.44, 0.32, "#color[617]{#phi/K^{0}_{S}}");
  tex->DrawLatex(0.24, 0.65, "#color[633]{#Lambda/K^{0}_{S}}");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);


  auto Can(MakeCanvas("MultiStrtoK", 700, 700));
  dfuy = 0.35;
  auto hFm(can->DrawFrame(dflx, dfly, dfux, dfuy));

  SetupFrame(hFm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hFm->GetXaxis()->SetNdivisions(505);
  hFm->GetYaxis()->SetNdivisions(505);

  for(int i = 1; i<3; i++){
    DrawGraph(g[0][i], wcl[i+1], "L");
    DrawGraph(g[1][i], wcl[i+1], "L");
    DrawGraph(g[2][i], wcl[i+1], "L");
  }

  auto Leg(new TLegend(0.16, 0.81, 0.8, 0.9)); SetupLegend(Leg);
  Leg->SetNColumns(3);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  Leg->AddEntry(g[0][1], "BLC",  "L")->SetTextSizePixels(24);
  Leg->AddEntry(g[1][1], "Rope",  "L")->SetTextSizePixels(24);
  Leg->AddEntry(g[2][1], "BLC + Rope",  "L")->SetTextSizePixels(24);
  Leg->Draw();

  auto Tex(new TLatex());
  Tex->SetNDC();
  Tex->SetTextSizePixels(24);
  Tex->DrawLatex(0.16, 0.91, "pp #sqrt{#it{s}} = 7 TeV  Strange particle to K^{0}_{S} ratio in jets");
  //tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));

  Tex->DrawLatex(0.3, 0.55, "#color[601]{#Xi^{-}/K^{0}_{S}}");
  Tex->DrawLatex(0.16, 0.2, "#color[419]{#Omega^{-}/K^{0}_{S} (#times 10)}");

  Can->SaveAs(Form("./figure/eps/%s.eps", Can->GetName()));
  Can->SaveAs(Form("./figure/pdf/%s.pdf", Can->GetName()));
  Can->SaveAs(Form("./figure/png/%s.png", Can->GetName()));
  CanvasEnd(Can);

  return;
}

