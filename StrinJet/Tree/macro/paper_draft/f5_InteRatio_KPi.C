#include "inc/PyJetUtils.h"

void f5_InteRatio_KPi(){
//=============================================================================
    auto hD(GetDataC("data/HEPData_1606.07424v2.root", 36)); 
    auto gD = GetDataE("data/HEPData_1606.07424v2.root", 36); 
    TGraph* g[3];
    g[0] = RatioToPi(1, 0, 0);    //Para1: "pp13TeV", "pp7TeV" 
    g[1] = RatioToPi(1, 1, 0);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
    g[2] = RatioToPi(1, 2, 0);    //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"

//  =============================================================================
    auto y = (Double_t)hD->GetMaximum();
    auto dflx(0.), dfux(25.);
    auto dfly(0.08), dfuy(0.2);
    
    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("#LTd#it{N}_{ch}/d#eta#GT_{|#eta|<0.5}");
    TString stny("K^{0}_{S}/#pi");
    
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas("Kshort_PiRatio"));
    //can->SetLogy();
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

    auto leg(new TLegend(0.73, 0.70, 0.95, 0.95)); SetupLegend(leg);
    auto Leg(new TLegend(0.16, 0.75, 0.5, 0.85)); SetupLegend(Leg);
    //Leg->AddEntry(hD, "ALICE: pp #sqrt{#it{s}} = 7 TeV",  "PF")->SetTextSizePixels(24);
    Leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
    leg->AddEntry(g[0], "BLC",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[2], "BLC + Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();
    Leg->Draw();

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

