#include "inc/PyJetUtils.h"

void Incl_Pi(){
//=============================================================================
    TH1D* hD[nc]; TGraphErrors* gD[nc]; TH1D* h1[nc]; TGraph* g[nc];

    //for(int i=0; i<nc-1; i++){
    for(int i=0; i<1; i++){
      hD[i] = GetDataC("data/HEPData_1807.11321v2.root", 11+i); 
      gD[i] = (TGraphErrors*)GetDataE("data/HEPData_1807.11321v2.root", 11+i); 
      h1[i] = PtSpectrum(1, 0, 5, dCent[i], dCent[i+1], kFALSE, kFALSE); //Para1: "pp13TeV", "pp7TeV"
      g[i] = new TGraph(h1[i]);                                          //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
    }                                                                    //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"
                                                                         //Para4:Centmin
                                                                         //Para5:Centmax
                                                                         //Para6: jet cone: kTRUE, kFALSE
                                                                         //Para7: PC: kTRUE, kFALSE
//  =============================================================================
    
    //auto ymax = (Double_t)hD[0]->GetMaximum();
    //auto ymin = (Double_t)hD[nc-1]->GetMinimum();
    auto dflx(0.), dfux(25.);
    //auto dfly(0.01*ymin), dfuy(3.*ymax);
    auto dfly(1e-8), dfuy(1e7);
    
    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("#it{p}_{T}");
    TString stny("#pi");
    
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas("Incl_PiSpect"));
    can->SetLogy();
    auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
    SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
    hfm->GetXaxis()->SetNdivisions(505);
    hfm->GetYaxis()->SetNdivisions(505);

    //for(int i=0; i<nc-1; i++){
    for(int i=0; i<1; i++){
      DrawHisto(hD[i], wcl[i], wmk[i], "same");
      DrawGraph(gD[i], wcl[i], "E2");
      DrawGraph(g[i], wcl[i], "L");
    }

    auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
    //leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
    //leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
    //leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
    //leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();

    auto tex(new TLatex());
    tex->SetNDC();
    tex->SetTextSizePixels(24);
    tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");


    can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
    can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
    can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
    CanvasEnd(can);
  return;
}

