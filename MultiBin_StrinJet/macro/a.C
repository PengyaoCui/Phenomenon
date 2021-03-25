#include "inc/PyJetUtils.h"

void a(){
//=============================================================================
  TH1D* h; 
  Double_t dNdEta[nc-1]; 
  CentTodNdEta(1, dNdEta);//CR
  for(Int_t i = 1; i<nc; i++)cout<<dCent[i-1]<<"-"<<dCent[i]<<" = "<<dNdEta[i-1]<<endl;
  //auto g = IntegralSpectrum(0, 1); 
  auto g = RatioToPi(2, 2); 
//=============================================================================

  auto dflx(0.), dfux(30.);
  auto dfly(0.), dfuy(1.);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("dNdEta");
  TString stny("Total Yield");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("f06_1"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  g->SetLineStyle(1);
  DrawGraph(g, wcl[0], "C");
  //DrawHisto(h, wcl[0], wmk[0], "same");

#if 0
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
#endif
  CanvasEnd(can);

  return;
}

