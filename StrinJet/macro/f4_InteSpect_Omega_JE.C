#include "inc/PyJetUtils.h"

void f4_InteSpect_Omega_JE(){
//=============================================================================
  int i = 3;
  int p = i;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
  //auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42+i)); 
  //auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42+i); 

  TGraph* g[3];
  g[0] = InteSpectrum(1, 0, p, kTRUE);g[0]->SetName((sp[i] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
  g[1] = InteSpectrum(1, 1, p, kTRUE);g[1]->SetName((sp[i] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  g[2] = InteSpectrum(1, 2, p, kTRUE);g[2]->SetName((sp[i] + sm[2]).Data());

//=============================================================================
  //Double_t x, y;
  //g[2]->GetPoint(nc-2, x, y);
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(30.);
  auto dfly(0.), dfuy(0.01);
  

  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #Delta#eta #Delta#varphi)");
  TString stny("#it{N}_{par} / (#it{N}_{ev} #it{A}_{acc})");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("%s_InteSpectrum_JE", sp[p].Data())));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(503);
  hfm->GetYaxis()->SetNdivisions(502);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(1);
  g[2]->SetLineStyle(2);
  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "L");
  DrawGraph(g[1], wcl[1], "L");
  DrawGraph(g[2], wcl[2], "L");

  auto leg(new TLegend(0.65, 0.65, 0.9, 0.92)); SetupLegend(leg);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, Form("Integrated yield of %s in jet", sp[p].Data()));

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

