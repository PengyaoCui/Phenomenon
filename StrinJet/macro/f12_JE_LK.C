#include "inc/PyJetUtils.h"

void f12_JE_LK(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_2005.11120.root", 43)); 
  //auto gD = GetDataE("data/HEPData_2005.11120.root", 43); 
  Double_t dBin[] = {0.6, 1.6, 2.2, 2.8, 3.7, 5.0, 8.0, 12.}; Int_t nBin = sizeof(dBin)/sizeof(Double_t)-1;
  Double_t dVal[] = {0.116, 0.190, 0.214, 0.227, 0.230, 0.235, 0.236};
  Double_t dSta[] = {0.020, 0.020, 0.019, 0.019, 0.019, 0.022, 0.040};
  Double_t dSys[] = {0.012, 0.021, 0.022, 0.023, 0.024, 0.024, 0.030};
  TH1D* hD(new TH1D("hD", "", nBin, dBin));
  TH1D* hE(new TH1D("hE", "", nBin, dBin));
  for(int i=1; i<= nBin; i++){
    hD->SetBinContent(i, dVal[i-1]); 
    hD->SetBinError(i, dSta[i-1]); 
    hE->SetBinContent(i, dVal[i-1]); 
    hE->SetBinError(i, dSys[i-1]); 
  }
  auto gD = ConvHistogramToGraphErrors(hE);
//=============================================================================

  TH1D* h1[3]; TH1D*h2[3]; TH1D* hR[3]; TGraph* g[3];
  for(int i=0; i<3; i++)h1[i] = PtSpectrum(1, i, 0, kTRUE, kFALSE); //Para1: "pp13TeV", "pp7TeV" 
  for(int i=0; i<3; i++)h2[i] = PtSpectrum(1, i, 1, kTRUE, kFALSE); //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
                                                                      //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
  for(int i=0; i<3; i++){                                             //Para4: jet cone: kTRUE, kFALSE 
    hR[i] = (TH1D*)h2[i]->Clone(Form("hR_%d", i));                    //Para5: PC: kTRUE, kFALSE 
    hR[i]->Divide(h1[i]); 
    g[i] = new TGraph(hR[i]);
  }


  
//=============================================================================
  auto dflx(0.), dfux(12.);
  auto dfly(0.), dfuy(1.1);
  
  auto dlsx(0.05), dlsy(0.05);
  auto dtsx(0.05), dtsy(0.05);
  auto dtox(1.30), dtoy(1.10);
  
  TString stnx("#it{p}_{T} (GeV/#it{c})");
  TString stny("(#Lambda + #bar{#Lambda})/2K^{0}_{S}");
  
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);
  
  auto can(MakeCanvas("LKRatio_JE"));
  //can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(505);

  g[0]->SetLineStyle(0);
  g[1]->SetLineStyle(1);
  g[2]->SetLineStyle(2);
  DrawHisto(hD, wcl[0], wmk[0], "same");
  DrawGraph(gD, wcl[0], "E2");
  DrawGraph(g[0], wcl[0], "L");
  DrawGraph(g[1], wcl[1], "L");
  DrawGraph(g[2], wcl[2], "L");

  auto leg(new TLegend(0.6, 0.70, 0.9, 0.92)); SetupLegend(leg);
  //leg->AddEntry(hD, "Data(Inclusive 13 TeV)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);

  leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();

  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
  //tex->DrawLatex(0.16, 0.8, "sQCD");
  tex->DrawLatex(0.16, 0.8, Form("%s in jets", stny.Data()));


  can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
  return;
}

