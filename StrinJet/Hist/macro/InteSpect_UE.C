#include "inc/PyJetUtils.h"

void InteSpect_UE(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42)); 
  //auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42); 

  TGraphErrors* g[4][6];
  int p = 0;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
  g[0][p] = InteSpectrum("Monash",  p, kFALSE, kTRUE, 4.); //g[0][0]->SetName((sp[p] + sm[0]).Data());//Para1: 
  g[1][p] = InteSpectrum("CR",      p, kFALSE, kTRUE, 4.); //g[1][0]->SetName((sp[p] + sm[1]).Data());//Para2: 
  g[2][p] = InteSpectrum("Rope",    p, kFALSE, kTRUE, 4.); //g[2][0]->SetName((sp[p] + sm[2]).Data());
  g[3][p] = InteSpectrum("CR+Rope", p, kFALSE, kTRUE, 4.); //g[2][0]->SetName((sp[p] + sm[2]).Data());

  p = 5;//Kstar
  g[0][p] = InteSpectrum("Monash",  p, kFALSE, kTRUE, 6); //g[0][0]->SetName((sp[8] + sm[0]).Data());
  g[1][p] = InteSpectrum("CR",      p, kFALSE, kTRUE, 6); //g[1][0]->SetName((sp[8] + sm[1]).Data());
  g[2][p] = InteSpectrum("Rope",    p, kFALSE, kTRUE, 6); //g[2][0]->SetName((sp[8] + sm[2]).Data());
  g[3][p] = InteSpectrum("CR+Rope", p, kFALSE, kTRUE, 6); //g[2][0]->SetName((sp[8] + sm[2]).Data());
                                                   
                                                   
  p = 4;//Phi                                      
  g[0][p] = InteSpectrum("Monash",  p, kFALSE, kTRUE, 12);//g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum("CR",      p, kFALSE, kTRUE, 12);//g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum("Rope",    p, kFALSE, kTRUE, 12);//g[2][0]->SetName((sp[p] + sm[2]).Data());
  g[3][p] = InteSpectrum("CR+Rope", p, kFALSE, kTRUE, 12);//g[2][0]->SetName((sp[p] + sm[2]).Data());
                                                   
  p = 1;//Lambda                                   
  g[0][p] = InteSpectrum("Monash",  p, kFALSE, kTRUE, 1.); //g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum("CR",      p, kFALSE, kTRUE, 1.); //g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum("Rope",    p, kFALSE, kTRUE, 1.); //g[2][0]->SetName((sp[p] + sm[2]).Data());
  g[3][p] = InteSpectrum("CR+Rope", p, kFALSE, kTRUE, 1.); //g[2][0]->SetName((sp[p] + sm[2]).Data());
                                                   
  p = 2;//Xi                                       
  g[0][p] = InteSpectrum("Monash",  p, kFALSE, kTRUE, 2); //g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum("CR",      p, kFALSE, kTRUE, 2); //g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum("Rope",    p, kFALSE, kTRUE, 2); //g[2][0]->SetName((sp[p] + sm[2]).Data());
  g[3][p] = InteSpectrum("CR+Rope", p, kFALSE, kTRUE, 2); //g[2][0]->SetName((sp[p] + sm[2]).Data());
                                                   
  p = 3;//Omega                                    
  g[0][p] = InteSpectrum("Monash",  p, kFALSE, kTRUE, 12);//g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum("CR",      p, kFALSE, kTRUE, 12);//g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum("Rope",    p, kFALSE, kTRUE, 12);//g[2][0]->SetName((sp[p] + sm[2]).Data());
  g[3][p] = InteSpectrum("CR+Rope", p, kFALSE, kTRUE, 12);//g[2][0]->SetName((sp[p] + sm[2]).Data());
//=============================================================================
  //Double_t x, y;
  //g[2]->GetPoint(nc-2, x, y);
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(30.);
  auto dfly(4e-5), dfuy(2.);
  

  auto dlsx(0.04), dlsy(0.04);
  auto dtsx(0.04), dtsy(0.04);
  auto dtox(1.30), dtoy(1.2);

  TString stnx("#LTd#it{N}_{ch}/d#eta#GT_{|#eta|<0.5}");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #Delta#eta #Delta#varphi)");
  //TString stny("#it{N}_{par} / (#it{N}_{ev} #it{A}_{acc})");
  TString stny("#rho");
 
  SetStyle(kTRUE);
  gStyle->SetErrorX(0);

  
  auto can(MakeCanvas("InteSpectrum_UE", 600, 800));
  can->SetLogy();
  auto hfm(can->DrawFrame(dflx, dfly, dfux, dfuy));
  SetupFrame(hfm, stnx, stny, dlsx, dlsy, dtsx, dtsy, dtox, dtoy);
  hfm->GetXaxis()->SetNdivisions(505);
  hfm->GetYaxis()->SetNdivisions(505);

  //DrawHisto(hD, wcl[0], wmk[0], "same");
  //DrawGraph(gD, wcl[0], "E2");
  for(int i = 0; i < 6; i++ ){
    g[0][i]->SetLineStyle(0);
    g[1][i]->SetLineStyle(2);
    g[2][i]->SetLineStyle(3);
    g[3][i]->SetLineStyle(5);
    DrawGraphError(g[0][i], wcl[i], wmk[0], "E3 PML same");
    DrawGraphError(g[1][i], wcl[i], wmk[1], "E3 PML same");
    DrawGraphError(g[2][i], wcl[i], wmk[2], "E3 PML same");
    DrawGraphError(g[3][i], wcl[i], wmk[3], "E3 PML same");
  }


  auto leg(new TLegend(0.15, 0.88, 0.99, 0.91)); SetupLegend(leg);
  leg->SetNColumns(4);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0][0], "Monash",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[1][0], "CR",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[2][0], "Rope",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(g[3][0], "CR + Rope",  "LP")->SetTextSizePixels(24);
  leg->Draw();


  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(28);
  tex->DrawLatex(0.16, 0.93, "pp #sqrt{#it{s}} = 7 TeV  Strange particle in UE");
  //tex->DrawLatex(0.16, 0.88, "Strange particle in UE");
  
  
  tex->DrawLatex(0.74, 0.85, "#color[1]{K^{0}_{S} (#times 4)}");
  tex->DrawLatex(0.74, 0.79, "#color[799]{K*^{0} (#times 6)}");
  tex->DrawLatex(0.74, 0.74, "#color[617]{#phi (#times 12)}"); 
  tex->DrawLatex(0.74, 0.67, "#color[633]{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.72, 0.54, "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}");
  tex->DrawLatex(0.72, 0.45, "#color[419]{#Omega^{-} + #bar{#Omega}^{+} (#times 12)}");

  //can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  //can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  //can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  can->Print(Form("./figure/eps/%s.eps", can->GetName()));
  can->Print(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->Print(Form("./figure/png/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

