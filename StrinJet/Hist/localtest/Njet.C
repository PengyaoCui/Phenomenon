#include "inc/PyJetUtils.h"

void Njet(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42)); 
  //auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42); 
  auto file(TFile::Open("sim/Monash.root", "read"));
  auto list(static_cast<TList*>(file->Get("list_results")));
  auto h((TH1D*)list->FindObject(Form("hNJet")));
  h->Scale(1./h->GetEntries());

//=============================================================================
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(5.);
  auto dfly(1e-4), dfuy(4.3);
  

  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{N}_{jet}");
  TString stny("Probability");
 
  SetStyle(kTRUE);
  //gStyle->SetErrorX(0);
  
  auto can(MakeCanvas(Form("Njet")));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  DrawHisto(h, wcl[0], wmk[0], "same");

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.66, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  tex->DrawLatex(0.56, 0.8, "Number of jet distribution");

  //can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/Njet.pdf"));
  //can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

