#include "inc/PyJetUtils.h"

void InteRatio(){
//=============================================================================
  for(int i = 0; i< 5; i++){
    auto hD(GetDataC("data/HEPData_1606.07424v2.root", 36+i)); 
    auto gD = GetDataE("data/HEPData_1606.07424v2.root", 36+i); 
    TGraph* g[3];
    g[0] = RatioToPi(1, 0, i);    //Para1: "pp13TeV", "pp7TeV" 
    g[1] = RatioToPi(1, 1, i);    //Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
    g[2] = RatioToPi(1, 2, i);    //Para3:"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"

//  =============================================================================
    auto y = (Double_t)hD->GetMaximum();
    auto dflx(0.), dfux(25.);
    auto dfly(0.), dfuy(3.*y);
    
    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
    TString stny("K^{0}_{S}/#pi");
    if(i!=0) stny = Form("#%s/#pi", sp[i].Data()); 
    
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas((sp[i]+"_PiRatio").Data()));
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

    auto leg(new TLegend(0.6, 0.60, 0.9, 0.92)); SetupLegend(leg);
    leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
    leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();

    auto tex(new TLatex());
    tex->SetNDC();
    tex->SetTextSizePixels(24);
    tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");


    can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
    can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
    can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
    CanvasEnd(can);
  }
  return;
}

