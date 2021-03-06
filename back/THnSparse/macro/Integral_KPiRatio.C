#include "inc/PyJetUtils.h"

void Integral_KPiRatio(){
//=============================================================================
  //Double_t dNdEta[nc-1]; 
  //CentTodNdEta(0, 1, dNdEta);//CR
  //for(Int_t i = 1; i<nc; i++)cout<<dCent[i-1]<<"-"<<dCent[i]<<" = "<<dNdEta[i-1]<<endl;
  
  auto hD(GetDataC("data/HEPData.root", 36)); 
  auto gD = GetDataE("data/HEPData.root", 36); 
  TGraph* g[3];
  g[0] = RatioToPi(1, 0, 0);    //Para1: "pp13TeV", "pp7TeV" 
  g[1] = RatioToPi(1, 1, 0);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  g[2] = RatioToPi(1, 2, 0);    //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"

//=============================================================================
  auto dflx(0.), dfux(30.);
  auto dfly(0.), dfuy(0.3);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
  TString stny("K^{0}_{S}/#pi");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("KPiRatio"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(1);
  g[2]->SetLineStyle(2);
  DrawHisto(hD, wcl[0], wmk[0], "same");
  DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "C");
  DrawGraph(g[1], wcl[1], "C");
  DrawGraph(g[2], wcl[2], "C");

  auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "2<|#eta_{fwd}|<5");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

