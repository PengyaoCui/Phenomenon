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

  TH1D* h[3][6]; TGraph* g[3][6]; TH1D* hPi[3];
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
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());h[0][p]->Scale(2.);
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());h[1][p]->Scale(2.);
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());h[2][p]->Scale(2.);

  p = 2;//Xi
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());h[0][p]->Scale(2.);
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());h[1][p]->Scale(2.);
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());h[2][p]->Scale(2.);

  p = 3;//Omega
  h[0][p] = PartoJet(1, 0, p);h[0][0]->SetName((sp[p] + sm[0]).Data());h[0][p]->Scale(2.);
  h[1][p] = PartoJet(1, 1, p);h[1][0]->SetName((sp[p] + sm[1]).Data());h[1][p]->Scale(2.);
  h[2][p] = PartoJet(1, 2, p);h[2][0]->SetName((sp[p] + sm[2]).Data());h[2][p]->Scale(2.);
  
  hPi[0] = PartoJet(1, 0, 5);h[0][0]->SetName((sp[5] + sm[0]).Data());h[0][p]->Scale(2.);
  hPi[1] = PartoJet(1, 1, 5);h[1][0]->SetName((sp[5] + sm[1]).Data());h[1][p]->Scale(2.);
  hPi[2] = PartoJet(1, 2, 5);h[2][0]->SetName((sp[5] + sm[2]).Data());h[2][p]->Scale(2.);
 
                                                  
  for(int i=0; i<6; i++){                         
    //hR[i] = (TH1D*)h2[i]->Clone(Form("hR_%d", i));
    //h[0][i]->Divide(hPi[0]);
    //h[1][i]->Divide(hPi[1]);
    //h[2][i]->Divide(hPi[2]);

    g[0][i] = new TGraph(h[0][i]);
    g[1][i] = new TGraph(h[1][i]);
    g[2][i] = new TGraph(h[2][i]);


  }




  
//=============================================================================
  auto dflx(0.), dfux(0.4);
  auto dfly(1e-4), dfuy(0.8);
  
  auto dlsx(0.04), dlsy(0.04);
  auto dtsx(0.04), dtsy(0.04);
  auto dtox(1.30), dtoy(1.2);
  
  TString stnx("#it{R}(p, jet)");
  TString stny("Yield ratio of #pi");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("RatiotoPi", 600, 800));
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

  auto leg(new TLegend(0.15, 0.88, 0.8, 0.91)); SetupLegend(leg);
  leg->SetNColumns(3);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0][0], "BLC",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1][0], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2][0], "BLC + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  //tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

