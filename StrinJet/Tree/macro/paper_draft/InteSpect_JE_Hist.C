#include "inc/PyJetUtils.h"

void InteSpect_JE(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42)); 
  //auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42); 

  TGraph* g[3][6];
  TH1D* h[3][6];
  int p = 0;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
  h[0][p] = InteSpect(1, 0, p, kTRUE, kFALSE, 4);h[0][p]->SetName((sp[p] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
  h[1][p] = InteSpect(1, 1, p, kTRUE, kFALSE, 4);h[1][p]->SetName((sp[p] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  h[2][p] = InteSpect(1, 2, p, kTRUE, kFALSE, 4);h[2][p]->SetName((sp[p] + sm[2]).Data());


  p = 5;//Kstar
  h[0][p] = InteSpect(1, 0, 8, kTRUE, kFALSE, 6);h[0][0]->SetName((sp[8] + sm[0]).Data());
  h[1][p] = InteSpect(1, 1, 8, kTRUE, kFALSE, 6);h[1][0]->SetName((sp[8] + sm[1]).Data());
  h[2][p] = InteSpect(1, 2, 8, kTRUE, kFALSE, 6);h[2][0]->SetName((sp[8] + sm[2]).Data());


  p = 4;//Phi
  h[0][p] = InteSpect(1, 0, p, kTRUE, kFALSE, 12);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = InteSpect(1, 1, p, kTRUE, kFALSE, 12);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = InteSpect(1, 2, p, kTRUE, kFALSE, 12);h[2][0]->SetName((sp[p] + sm[2]).Data());
  
  p = 1;//Lambda
  h[0][p] = InteSpect(1, 0, p, kTRUE, kFALSE, 1);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = InteSpect(1, 1, p, kTRUE, kFALSE, 1);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = InteSpect(1, 2, p, kTRUE, kFALSE, 1);h[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 2;//Xi
  h[0][p] = InteSpect(1, 0, p, kTRUE, kFALSE, 2);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = InteSpect(1, 1, p, kTRUE, kFALSE, 2);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = InteSpect(1, 2, p, kTRUE, kFALSE, 2);h[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 3;//Omega
  h[0][p] = InteSpect(1, 0, p, kTRUE, kFALSE, 12);h[0][0]->SetName((sp[p] + sm[0]).Data());
  h[1][p] = InteSpect(1, 1, p, kTRUE, kFALSE, 12);h[1][0]->SetName((sp[p] + sm[1]).Data());
  h[2][p] = InteSpect(1, 2, p, kTRUE, kFALSE, 12);h[2][0]->SetName((sp[p] + sm[2]).Data());

//=============================================================================
  //Double_t x, y;
  //h[2]->GetPoint(nc-2, x, y);
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(30.);
  auto dfly(5e-3), dfuy(1.2);
  

  auto dlsx(0.04), dlsy(0.04);
  auto dtsx(0.04), dtsy(0.04);
  auto dtox(1.30), dtoy(1.2);

  TString stnx("#LTd#it{N}_{ch}/d#eta#GT_{|#eta|<0.5}");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #Delta#eta #Delta#varphi)");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #it{A}_{acc})");
  TString stny("#rho");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

  
  auto can(MakeCanvas("InteSpect_JE", 600, 800));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  for(int i = 0; i < 6; i++ ){
    //g[0][i]->SetLineStyle(5);
    //g[1][i]->SetLineStyle(3);
    //g[2][i]->SetLineStyle(0);
    //g[0][i]->SetMarkerColor(wcl[i]);
    //g[1][i]->SetMarkerColor(wcl[i]);
    //g[2][i]->SetMarkerColor(wcl[i]);
    //g[0][i]->SetMarkerSize(1.1);
    //g[1][i]->SetMarkerSize(1.1);
    //g[2][i]->SetMarkerSize(1.1);
    //g[0][i]->SetMarkerStyle(wmk[0]);
    //g[1][i]->SetMarkerStyle(wmk[1]);
    //g[2][i]->SetMarkerStyle(wmk[2]);

    //DrawGraph(g[0][i], wcl[i], "PL");
    //DrawGraph(g[1][i], wcl[i], "PL");
    //DrawGraph(g[2][i], wcl[i], "PL");
    DrawHisto(h[0][i], wcl[i], wmk[0], "same");
    DrawHisto(h[1][i], wcl[i], wmk[1], "same");
    DrawHisto(h[2][i], wcl[i], wmk[2], "same");
  }


  auto leg(new TLegend(0.15, 0.88, 0.8, 0.91)); SetupLegend(leg);
  leg->SetNColumns(3);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[0][0], "BLC",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1][0], "Rope",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[2][0], "BLC + Rope",  "P")->SetTextSizePixels(24);
  leg->Draw();


  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(28);
  tex->DrawLatex(0.16, 0.92, "pp #sqrt{#it{s}} = 7 TeV  Strange particle in jets");
  //tex->DrawLatex(0.16, 0.88, "Strange particle in jets");
  
  
  tex->DrawLatex(0.74, 0.85, "#color[1]{K^{0}_{S} (#times 4)}");
  tex->DrawLatex(0.74, 0.74, "#color[799]{K*^{0} (#times 6)}");
  tex->DrawLatex(0.74, 0.64, "#color[617]{#phi (#times 12)}"); 
  tex->DrawLatex(0.74, 0.56, "#color[633]{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.72, 0.46, "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}");
  tex->DrawLatex(0.72, 0.3, "#color[419]{#Omega^{-} + #bar{#Omega}^{+} (#times 12)}");

  //can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  //can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  //can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  can->Print(Form("./figure/eps/%s.eps", can->GetName()));
  can->Print(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->Print(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

