#include "inc/PyJetUtils.h"

void JE_OK_Cent_Rope(){
//=============================================================================

  TH1D* h1[3]; TH1D*h2[3]; TH1D* h1u[3]; TH1D*h2u[3]; TH1D* hR[3]; //Double_t dndeta[3];
  Int_t c[] = {0, 10, 40, 100}; Int_t n = sizeof(c)/sizeof(Int_t) - 1;
  for(int i=0; i<n; i++)h1[i]  = PtSpectrum(1, 1, 0, c[i], c[i+1], kTRUE, kFALSE); //Para1: "pp13TeV", "pp7TeV" 
  for(int i=0; i<n; i++)h2[i]  = PtSpectrum(1, 1, 3, c[i], c[i+1], kTRUE, kFALSE); //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  for(int i=0; i<n; i++)h1u[i] = PtSpectrum(1, 1, 0, c[i], c[i+1], kFALSE, kTRUE); //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
  for(int i=0; i<n; i++)h2u[i] = PtSpectrum(1, 1, 3, c[i], c[i+1], kFALSE, kTRUE); //Para4:Centmin 
                                                                                  //Para5:Centmax 
                                                                                  //Para6: jet cone: kTRUE, kFALSE 
                                                                                  //Para7: PC: kTRUE, kFALSE 
  //for(int i=0; i<n; i++)CentTodNdEta(1, 2, c[i], c[i+1], dndeta[i]);
  for(int i=0; i<3; i++){
    h1u[i]->Scale(0.25);     h2u[i]->Scale(0.25); 
    h1[i]->Add(h1u[i], -1.); h2[i]->Add(h2u[i], -1.);
    hR[i] = (TH1D*)h2[i]->Clone(Form("hR_%d", i));                  
    hR[i]->Divide(h1[i]); 
  }
  
//=============================================================================
  auto dflx(0.), dfux(9.);
  auto dfly(0.), dfuy(0.071);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("#Omega/K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("OKRatio_JE_Cent_rope"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(hR[0], wcl[0], wmk[0], "same");
  DrawHisto(hR[1], wcl[1], wmk[1], "same");
  DrawHisto(hR[2], wcl[2], wmk[2], "same");

  //auto leg(new TLegend(0.5, 0.60, 0.8, 0.82)); SetupLegend(leg);
  auto leg(new TLegend(0.7, 0.60, 0.8, 0.82)); SetupLegend(leg);
  leg->AddEntry(hR[0], Form("%d-%d%%", c[0], c[1]), "P")->SetTextSizePixels(24);
  leg->AddEntry(hR[1], Form("%d-%d%%", c[1], c[2]), "P")->SetTextSizePixels(24);
  leg->AddEntry(hR[2], Form("%d-%d%%", c[2], c[3]), "P")->SetTextSizePixels(24);
  //leg->AddEntry(hR[0], Form("%d-%d%%(%.1f)", c[0], c[1], dndeta[0]), "P")->SetTextSizePixels(24);
  //leg->AddEntry(hR[1], Form("%d-%d%%(%.1f)", c[1], c[2], dndeta[1]), "P")->SetTextSizePixels(24);
  //leg->AddEntry(hR[2], Form("%d-%d%%(%.1f)", c[2], c[3], dndeta[2]), "P")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "sQCD + Rope");
  tex->DrawLatex(0.16, 0.7, Form("%s in jet", stny.Data()));
  //tex->DrawLatex(0.55, 0.86, "Cent (<d#it{N}_{ch}/d#eta>_{|#eta|<0.5})");
  tex->DrawLatex(0.72, 0.86, "Cent");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

