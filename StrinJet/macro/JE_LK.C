#include "inc/PyJetUtils.h"

void JE_LK(){
//=============================================================================

  TH1D* h1[3]; TH1D*h2[3]; TH1D* hR[3];
  TH1D* h1u[3]; TH1D*h2u[3];
  for(int i=0; i<3; i++)h1[i] = PtSpectrum(1, i, 0, kTRUE, kFALSE); //Para1: "pp13TeV", "pp7TeV" 
  for(int i=0; i<3; i++)h2[i] = PtSpectrum(1, i, 1, kTRUE, kFALSE); //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  for(int i=0; i<3; i++)h1u[i] = PtSpectrum(1, i, 0, kFALSE, kTRUE);//Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
  for(int i=0; i<3; i++)h2u[i] = PtSpectrum(1, i, 1, kFALSE, kTRUE);//Para4: jet cone: kTRUE, kFALSE
								    //Para5: PC: kTRUE, kFALSE 
  
  for(int i=0; i<3; i++){
    h1u[i]->Scale(0.25);     h2u[i]->Scale(0.25); 
    h1[i]->Add(h1u[i], -1.); h2[i]->Add(h2u[i], -1.);
    hR[i] = (TH1D*)h2[i]->Clone(Form("hR_%d", i));                  
    hR[i]->Divide(h1[i]); 
  }


  
//=============================================================================
  auto dflx(0.), dfux(20.);
  auto dfly(0.), dfuy(1.);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("#Lambda/K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("LKRatio_JE"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(hR[0], wcl[0], wmk[0], "same");
  DrawHisto(hR[1], wcl[1], wmk[1], "same");
  DrawHisto(hR[2], wcl[2], wmk[2], "same");

  auto leg(new TLegend(0.65, 0.70, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(hR[0], "CR",  "P")->SetTextSizePixels(24);
  leg->AddEntry(hR[1], "Rope",  "P")->SetTextSizePixels(24);
  leg->AddEntry(hR[2], "CR+Rope",  "P")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "sQCD");
  tex->DrawLatex(0.16, 0.7, Form("%s in jet", stny.Data()));


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

