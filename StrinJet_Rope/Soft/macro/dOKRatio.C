#include "inc/PyJetUtils.h"

void dOKRatio(){
   //auto g = new TGraph(Spectrum("Kshort", sj, "C04", "PC"));
   auto hJCK = (TH1D*)Spectrum("Kshort", "Jet10", "C04");
   auto hPCK = (TH1D*)Spectrum("Kshort", "Jet10", "C04", "PC");
   auto hInK = (TH1D*)Spectrum("Kshort" );
   auto hJEK = (TH1D*)hJCK->Clone("hJEK"); hJEK->Add(hPCK, -0.25);
   
   auto hJCL = (TH1D*)Spectrum("OmegaNeg", "Jet10", "C04");
   auto hPCL = (TH1D*)Spectrum("OmegaNeg", "Jet10", "C04", "PC");
   auto hInL = (TH1D*)Spectrum("OmegaNeg" );
   auto hJEL = (TH1D*)hJCL->Clone("hJEL"); hJEL->Add(hPCL, -0.25);
   
   auto hJCA = (TH1D*)Spectrum("OmegaPos", "Jet10", "C04");
   auto hPCA = (TH1D*)Spectrum("OmegaPos", "Jet10", "C04", "PC");
   auto hInA = (TH1D*)Spectrum("OmegaPos" );
   auto hJEA = (TH1D*)hJCA->Clone("hJEA"); hJEA->Add(hPCA, -0.25);


   auto hInRatio = (TH1D*)hInL->Clone("hInRatio"); hInRatio->Add(hInA); hInRatio->Divide(hInK); hInRatio->Scale(0.5);
   auto hPCRatio = (TH1D*)hPCL->Clone("hPCRatio"); hPCRatio->Add(hPCA); hPCRatio->Divide(hPCK); hPCRatio->Scale(0.5);
   auto hJERatio = (TH1D*)hJEL->Clone("hJERatio"); hJERatio->Add(hJEA); hJERatio->Divide(hJEK); hJERatio->Scale(0.5);
   auto gIn = new TGraph(hInRatio);
   auto gPC = new TGraph(hPCRatio);
   auto gJE = new TGraph(hJERatio);

//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.), dfuy(0.06);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Omega^{-} + #bar{#Omega}^{+})/2K^{0}_{S}");

  SetStyle(kTRUE);
  
  auto can(MakeCanvas(Form("PyData")));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  //DrawGraph(gIn,  wcl[0], "C");
  //DrawGraph(gJE,  wcl[1], "C");
  //DrawGraph(gPC,  wcl[2], "C");
  DrawHisto(hInRatio, wcl[0], wmk[0], "same");
  DrawHisto(hJERatio, wcl[1], wmk[1], "same");
  DrawHisto(hPCRatio, wcl[2], wmk[2], "same");
  

  auto leg(new TLegend(0.72, 0.60, 0.98, 0.92)); SetupLegend(leg);
  leg->AddEntry(hInRatio, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hJERatio, "JE", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPCRatio, "UE", "LP")->SetTextSizePixels(24);
  leg->Draw();
  //leg->AddEntry(gE[0], "Sys. Error", "f")->SetTextSizePixels(24);

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "pp at #sqrt{#it{s}} = 13 TeV");
  tex->DrawLatex(0.16, 0.82, Form("PYTHIA 8"));
  tex->DrawLatex(0.16, 0.72, "sQCD + CR + rope");
  can->SaveAs(Form("./figure/eps/OKRatio_sQCD_CR_rope.eps"));
  can->SaveAs(Form("./figure/pdf/OKRatio_sQCD_CR_rope.pdf"));
  can->SaveAs(Form("./figure/png/OKRatio_sQCD_CR_rope.png"));
  CanvasEnd(can);
  
  return;  
}
