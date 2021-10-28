#include "inc/PyJetUtils.h"

void f15_Incl_LK_Cent_CR(){
//=============================================================================

  TH1D* h1[3]; TH1D*h2[3]; TH1D* hR[3]; TGraph*g[3];//Double_t dndeta[3];
  Int_t c[] = {0, 10, 40, 100}; Int_t n = sizeof(c)/sizeof(Int_t) - 1;
  for(int i=0; i<n; i++)h1[i] = PtSpectrum(1, 0, 0, c[i], c[i+1], kFALSE, kFALSE); //Para1: "pp13TeV", "pp7TeV" 
  for(int i=0; i<n; i++)h2[i] = PtSpectrum(1, 0, 1, c[i], c[i+1], kFALSE, kFALSE); //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
                                                                            //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
                                                                            //Para4:Centmin 
                                                                            //Para5:Centmax 
                                                                            //Para6: jet cone: kTRUE, kFALSE 
                                                                            //Para7: PC: kTRUE, kFALSE 
  //for(int i=0; i<n; i++)CentTodNdEta(1, 2, c[i], c[i+1], dndeta[i]);
  for(int i=0; i<3; i++){
    hR[i] = (TH1D*)h2[i]->Clone(Form("hR_%d", i));
    hR[i]->Divide(h1[i]); 
    g[i] = new TGraph(hR[i]);
  }
  
//=============================================================================
  auto dflx(0.), dfux(14.);
  auto dfly(0.), dfuy(1.3);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("#Lambda/K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("LKRatio_Incl_Cent_cr"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);
  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(1);
  g[2]->SetLineStyle(2);
  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "L");
  DrawGraph(g[1], wcl[1], "L");
  DrawGraph(g[2], wcl[2], "L");


  //auto leg(new TLegend(0.5, 0.60, 0.8, 0.82)); SetupLegend(leg);
  auto leg(new TLegend(0.6, 0.60, 0.9, 0.82)); SetupLegend(leg);
  leg->AddEntry(g[0], Form("%d-%d%%", c[0], c[1]), "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], Form("%d-%d%%", c[1], c[2]), "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], Form("%d-%d%%", c[2], c[3]), "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "sQCD + CR");
  tex->DrawLatex(0.16, 0.7, Form("Inclusive %s", stny.Data()));
  //tex->DrawLatex(0.55, 0.86, "Cent (<d#it{N}_{ch}/d#eta>_{|#eta|<0.5})");
  tex->DrawLatex(0.62, 0.86, "Centrality");

  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

