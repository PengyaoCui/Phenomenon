#include "inc/PyJetUtils.h"

void InteRatio_LPi(){
//=============================================================================
    auto hD(GetDataC("data/HEPData_1606.07424v2.root", 37)); 
    auto gD = GetDataE("data/HEPData_1606.07424v2.root", 37); 

    int p = 1;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Kstar", "Pion", "Kion", "Proton"};
    TGraphErrors* g[4];
    g[0] = RatioToPi("Monash",  p, kFALSE, kFALSE, 1.);//Para1: "Monash", "CR", "Rope", "CR+Rope" 
    g[1] = RatioToPi("CR",      p, kFALSE, kFALSE, 1.);//Para1: "Monash", "CR", "Rope", "CR+Rope" 
    g[2] = RatioToPi("Rope",    p, kFALSE, kFALSE, 1.);//Para1: "Monash", "CR", "Rope", "CR+Rope" 
    g[3] = RatioToPi("CR+Rope", p, kFALSE, kFALSE, 1.);//Para1: "Monash", "CR", "Rope", "CR+Rope" 

//  =============================================================================
    auto y = (Double_t)hD->GetMaximum();
    auto dflx(0.), dfux(25.);
    auto dfly(0.01), dfuy(0.07);
    
    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
    TString stny("#Lambda/#pi");
    
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas("Lambda_PiRatio"));
    //can->SetLogy();
    auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
    SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
    hfm->GetXaxis()->SetNdivisions(505);
    hfm->GetYaxis()->SetNdivisions(505);
    g[0]->SetLineStyle(0);
    g[1]->SetLineStyle(2);
    g[2]->SetLineStyle(3);
    g[3]->SetLineStyle(5);


    g[0]->SetLineStyle(0);
    g[1]->SetLineStyle(2);
    g[2]->SetLineStyle(3);
    g[3]->SetLineStyle(5);
    DrawHisto(hD, wcl[0], wmk[0], "same");
    DrawGraph(gD, wcl[0], "E2");
    DrawGraph(g[0], wcl[0], "L");
    DrawGraph(g[1], wcl[1], "L");
    DrawGraph(g[2], wcl[2], "L");
    DrawGraph(g[3], wcl[3], "L");
    auto leg(new TLegend(0.73, 0.70, 0.95, 0.95)); SetupLegend(leg);
    leg->AddEntry(g[0], "Monash",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[1], "CR",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[2], "Rope",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[3], "CR + Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();

    auto Leg(new TLegend(0.16, 0.75, 0.5, 0.85)); SetupLegend(Leg);
    Leg->AddEntry(hD, "Exp data",  "PF")->SetTextSizePixels(24);
    Leg->Draw();

    auto tex(new TLatex());
    tex->SetNDC();
    tex->SetTextSizePixels(24);
    tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
    auto Tex(new TLatex());
    Tex->SetNDC();
    Tex->SetTextSizePixels(34);
    Tex->DrawLatex(0.5, 0.9, "(d)");


    can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
    can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
    can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
    CanvasEnd(can);
  return;
}

