#include "inc/PyJetUtils.h"

void a(){
//=============================================================================
  auto h(Cent(0));//CR
  h->Draw();
#if 0
  l[0]= (TList*)f->Get("Kshort_0100");
  l[1]= (TList*)f->Get("Kshort_010");
  l[2]= (TList*)f->Get("Kshort_1040");
  l[3]= (TList*)f->Get("Kshort_40100");
  TH1D *h[4]; TGraph *gE[4];
  for(Int_t i = 0; i<4; i++){
    h[i] = (TH1D*)l[i]->FindObject(Form("InclCen")); gE[i] = (TGraphErrors*)l[i]->FindObject(Form("Inclerr"));
  }
//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(2e-6), dfuy(2e0);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("d#it{#rho}/d#it{p}_{T} (GeV/#it{c} rad)^{-1}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("f06_1"));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h[0], wcl[0], wmk[0], "same"); DrawGraph(gE[0], wcl[0], "E2");
  DrawHisto(h[1], wcl[1], wmk[1], "same"); DrawGraph(gE[1], wcl[1], "E2");
  DrawHisto(h[2], wcl[2], wmk[2], "same"); DrawGraph(gE[2], wcl[2], "E2");
  DrawHisto(h[3], wcl[3], wmk[3], "same"); DrawGraph(gE[3], wcl[3], "E2");

  auto leg(new TLegend(0.72, 0.60, 0.98, 0.86)); SetupLegend(leg);
  leg->AddEntry(h[0], "0-100%",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[1], "0-10%",   "P")->SetTextSizePixels(24);
  leg->AddEntry(h[2], "10-40%",  "P")->SetTextSizePixels(24);
  leg->AddEntry(h[3], "40-100%", "P")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  tex->DrawLatex(0.16, 0.2, "Inclusive K^{0}_{S}, |#eta| < 0.75");
  tex->DrawLatex(0.82, 0.9, "ALICE");


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);

#endif
  return;
}

