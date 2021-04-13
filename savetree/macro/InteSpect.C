#include "inc/PyJetUtils.h"

void InteSpect(){
//=============================================================================

  for(Int_t i = 0; i< np; i++){
    int p = i;
    TGraph* g[3];
    g[0] = InteSpectrum(1, 0, p);g[0]->SetName((sp[i] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
    g[1] = InteSpectrum(1, 1, p);g[1]->SetName((sp[i] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
    g[2] = InteSpectrum(1, 2, p);g[2]->SetName((sp[i] + sm[2]).Data());

//  =============================================================================
    Double_t x, y;
    g[2]->GetPoint(nc-2, x, y);
    auto dflx(0.), dfux(30.);
    auto dfly(0.), dfuy(2.*y);
   

    auto dlsx(0.05), dlsy(0.05);
    auto dtsx(0.05), dtsy(0.05);
    auto dtox(1.30), dtoy(1.10);
    
    TString stnx("<d#it{N}_{ch}/d#eta>_{|#eta|<0.5}");
    TString stny("#it{N}_{par} / (#it{N}_{ev} #Delta#eta #Delta#varphi)");
 
    SetStyle(kTRUE);
    gStyle->SetErrorX(0);
    
    auto can(MakeCanvas(Form("%s_InteSpectrum", sp[p].Data())));
    //can->SetLogy();
    auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
    SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
    hfm->GetXaxis()->SetNdivisions(503);
    hfm->GetYaxis()->SetNdivisions(503);

    g[0]->SetLineStyle(0);
    g[1]->SetLineStyle(1);
    g[2]->SetLineStyle(2);
    DrawGraph(g[0], wcl[0], "C");
    DrawGraph(g[1], wcl[1], "C");
    DrawGraph(g[2], wcl[2], "C");

    auto leg(new TLegend(0.65, 0.65, 0.9, 0.92)); SetupLegend(leg);
    //leg->AddEntry(hD, "Data(7 TeV)",  "P")->SetTextSizePixels(24);
    leg->AddEntry(g[0], "CR",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[1], "Rope",  "L")->SetTextSizePixels(24);
    leg->AddEntry(g[2], "CR+Rope",  "L")->SetTextSizePixels(24);
    leg->Draw();

    auto tex(new TLatex());
    tex->SetNDC();
    tex->SetTextSizePixels(24);
    tex->DrawLatex(0.16, 0.9, "pp #sqrt{#it{s}} = 7 TeV");
    tex->DrawLatex(0.16, 0.8, "2<|#eta_{fwd}|<5");
    tex->DrawLatex(0.16, 0.7, Form("Integrated yield of %s", sp[p].Data()));

    can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
    can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
    can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
    CanvasEnd(can);
    }
  return;
}

