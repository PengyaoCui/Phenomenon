#include "inc/PyJetUtils.h"

void PtSpectra(){
//=============================================================================
  //Double_t dNdEta[nc-1]; 
  //CentTodNdEta(0, 1, dNdEta);//CR
  //for(Int_t i = 1; i<nc; i++)cout<<dCent[i-1]<<"-"<<dCent[i]<<" = "<<dNdEta[i-1]<<endl;
  
  auto h = PtSpectrum(1, 0, 0); //Para1: "pp13TeV", "pp7TeV" 
                               //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
			       //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"

//=============================================================================
  auto dflx(0.), dfux(30.);
  auto dfly(1e-1), dfuy(1e7);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
  TString stny("#Omega/#pi");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("KSpectra"));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

  DrawHisto(h, wcl[0], wmk[0], "same");

  auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
  leg->AddEntry(h, "Kshort",  "P")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.16, 0.8, "2<|#eta_{fwd}|<5");


  //can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  //can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  //can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

