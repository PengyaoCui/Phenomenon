#include "inc/PyJetUtils.h"

void f10_JE_Phi(){
//=============================================================================
    //TH1D* hD; TGraphErrors* gD; 
    TH1D* h1[3]; TGraph* g[3];
    //hD = GetDataC("data/HEPData_2005.11120.root", 10); 
    //gD = GetDataE("data/HEPData_2005.11120.root", 10); 
    //Para1: "pp13TeV", "pp7TeV"
    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
    //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
    //Para6: jet cone: kTRUE, kFALSE
    //Para7: PC: kTRUE, kFALSE
    h1[0] = PtSpectrum(1, 0, 4, kTRUE, kFALSE);
    h1[1] = PtSpectrum(1, 1, 4, kTRUE, kFALSE); 
    h1[2] = PtSpectrum(1, 2, 4, kTRUE, kFALSE); 
    for(int i = 0; i<3; i++){
      h1[i]->Scale(1./(0.75*2*0.06*2.*TMath::Pi()));
      g[i] = new TGraph(h1[i]);
    }
//  =============================================================================
    
    //auto y = (Double_t)hD->GetMaximum();
    auto dflx(0.), dfux(21.);

    //auto dfly(1e-6), dfuy(2.*y);
    auto dfly(1e-5), dfuy(1e-1);
    
    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("#it{p}_{T}");
    TString stny("1/#it{N}_{ev} #times d^{2}#it{N}/(d#it{p}_{T}d#etad#varphi)");
    TString sPar("#phi");
    
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas("JE_PhiSpect"));
    can->SetLogy();
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

    auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);

    //leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
    leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();

    auto tex(new TLatex());
    tex->SetNDC();
    tex->SetTextSizePixels(24);
    tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
    tex->DrawLatex(0.16, 0.8, Form("%s in JE spectra", sPar.Data()));


    can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
    can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
    can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
    CanvasEnd(can);
  return;
}

