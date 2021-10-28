#include "inc/PyJetUtils.h"

void f9_Incl_Kshort(){
//=============================================================================
    TH1D* hD; TGraphErrors* gD; TH1D* h1[3]; TGraph* g[3];
    hD = GetDataC("data/HEPData_2005.11120.root", 10); 
    gD = GetDataE("data/HEPData_2005.11120.root", 10); 
    //Para1: "pp13TeV", "pp7TeV"
    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
    //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
    //Para6: jet cone: kTRUE, kFALSE
    //Para7: PC: kTRUE, kFALSE
    h1[0] = PtSpectrum(1, 0, 0, kFALSE, kFALSE);
    h1[1] = PtSpectrum(1, 1, 0, kFALSE, kFALSE); 
    h1[2] = PtSpectrum(1, 2, 0, kFALSE, kFALSE); 
    for(int i = 0; i<3; i++){
      //h1[i]->Scale(1./(0.75*2.));
      g[i] = new TGraph(h1[i]);
    }
//  =============================================================================
    
    auto y = (Double_t)hD->GetMaximum();
    auto dflx(0.), dfux(21.);
    //auto dfly(1e-6), dfuy(2.*y);
    auto dfly(5e-7), dfuy(2e2);
    
    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("#it{p}_{T} (GeV/#it{c})");
    TString stny("1/#it{N}_{ev} #times d^{2}#it{N}/(d#it{p}_{T}d#eta) (#it{c}/GeV)");
    TString sPar("K^{0}_{S}");
    
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas("Incl_KshortSpect"));
    can->SetLogy();
    auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
    SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
    hfm->GetXaxis()->SetNdivisions(505);
    hfm->GetYaxis()->SetNdivisions(505);

    g[0]->SetLineStyle(0);
    g[1]->SetLineStyle(1);
    g[2]->SetLineStyle(2);
    DrawHisto(hD, wcl[0], wmk[0], "same");
    DrawGraph(gD, wcl[0], "E2");
    DrawGraph(g[0], wcl[0], "L");
    DrawGraph(g[1], wcl[1], "L");
    DrawGraph(g[2], wcl[2], "L");

    auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);

    leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
    leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();
    //auto Leg(new TLegend(0.55, 0.2, 0.9, 0.3)); SetupLegend(Leg);
    //Leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
    //Leg->Draw();

    auto tex(new TLatex());
    tex->SetNDC();
    tex->SetTextSizePixels(24);
    tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
    tex->DrawLatex(0.16, 0.8, Form("Inclsive %s spectra", sPar.Data()));


    can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
    can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
    can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
    CanvasEnd(can);
  return;
}

