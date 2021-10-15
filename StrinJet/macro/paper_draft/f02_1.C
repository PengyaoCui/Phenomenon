#include "inc/PyJetUtils.h"

void f02_1(){
  TString sType[] = {"Kshort", "Lambda", "Xi", "Omega"};
  TString sLeg[] = {"K^{0}_{S}", "#Lambda", "#Xi", "#Omega"};
  
  Int_t n = sizeof(sType)/sizeof(TString); 
 
  TH1D* hJE[5]; TH1D* hIn[5]; TH1D* hR[5];
  for(Int_t i = 0; i<n; i++){
    auto f = TFile::Open(Form("./data/pp/JE/%s/AnalysisOutputs_EffCorrJE.root", sType[i].Data()), "read");
    auto l = (TList*)f->Get(Form("listEffCorrJE_%s_Default_JC", sType[i].Data())); f->Close();    
    hJE[i] = (TH1D*)l->FindObject("hPtEffi");hJE[i]->SetName(Form("hJE_%d", i)); 
    f = TFile::Open(Form("./data/pp/JE/%s/AnalysisOutputs_EffInclMC.root", sType[i].Data()), "read");
    l = (TList*)f->Get(Form("listEffInclMC_%s_Default", sType[i].Data())); f->Close();    
    hIn[i] = (TH1D*)l->FindObject("hPtEffi"); hIn[i]->SetName(Form("hIn_%d", i));
    hR[i] = (TH1D*)hJE[i]->Clone(Form("hR_%d", i));hR[i]->SetName(Form("hR_%d", i));   
    hR[i]->Divide(hIn[i]);
 
  } 
//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.0001), dfuy(0.58);
  
  auto dlsx(0.07), dlsy(0.07);
  auto dtsx(0.08), dtsy(0.08);
  auto dtox(1.30), dtoy(0.70);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("Efficiency");
  
  SetStyle(kTRUE);
  
  auto can(MakeCanvas("f02_1", 700, 600));
  auto padT = MakePadT("padT"); can->cd();
  auto padB = MakePadB("padB"); can->cd();
  padT->cd(); 
  auto hfm(padT->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);
  
  for(Int_t i =0; i<n; i++){
    DrawHisto(hIn[i], wcl[i], wmk[0], "same");
    DrawHisto(hJE[i], wcl[i], wmk[1], "same");
  }

  auto leg(new TLegend(0.83, 0.45, 1.1, 0.9)); SetupLegend(leg);
  auto Leg(new TLegend(0.55, 0.50, 0.8, 0.75)); SetupLegend(leg);
  //leg -> SetNColumns(3);
  for(Int_t i =0; i<n; i++){
    leg->AddEntry(hIn[i], sLeg[i], "L")->SetTextSizePixels(20);
  
  }
  Leg->AddEntry(hIn[0], "Inclusive", "P")->SetTextSizePixels(20);
  Leg->AddEntry(hJE[0], "#it{R}(par, jet) < 0.4", "P")->SetTextSizePixels(20);
  Leg->Draw();
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(20);
  tex->DrawLatex(0.16, 0.89, "ALICE pp #sqrt{#it{s}} = 13 TeV, |#eta| < 0.75");
  tex->DrawLatex(0.16, 0.78, "Jet: anti-#it{k}_{T}, #it{R} = 0.4, #it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#eta_{jet}| < 0.35");

  can->cd();
  padB->cd(); 
  dfly = 0.8, dfuy = 1.5999;
  
  dlsx = 0.14; dlsy = 0.14;
  dtsx = 0.14; dtsy = 0.14;
  dtox = 0.95; dtoy = 0.40;
  stny = "Ratio to inclusive";
  
  auto hfmb(padB->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfmb, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfmb->GetXaxis()->SetNdivisions(510);
  hfmb->GetYaxis()->SetNdivisions(503);
  hfmb->GetXaxis()->SetTickLength(0.07);
  
  for(Int_t i =0; i<n; i++){
    DrawHisto(hR[i], wcl[i], wmk[1], "same");
  }

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));  
  CanvasEnd(can);

  return;
}

