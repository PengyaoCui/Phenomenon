#include "inc/PyJetUtils.h"

void InteSpect_In(){
//=============================================================================
  //auto hD(GetDataC("data/HEPData_1606.07424v2.root", 42)); 
  //auto gD = GetDataE("data/HEPData_1606.07424v2.root", 42); 

  TGraph* g[3][6]; TH1D* hD[6]; TGraph* gD[6];
  int p = 0;//{0="Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
  hD[p] = GetDataC("data/HEPData_1606.07424v2.root", 42); hD[p]->Scale(4);
  gD[p] = GetDataE("data/HEPData_1606.07424v2.root", 42); 
  g[0][p] = InteSpectrum(1, 0, p, kFALSE, kFALSE, 4);g[0][0]->SetName((sp[p] + sm[0]).Data());//Para1: "pp13TeV", "pp7TeV" 
  g[1][p] = InteSpectrum(1, 1, p, kFALSE, kFALSE, 4);g[1][0]->SetName((sp[p] + sm[1]).Data());//Para2: "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope"
  g[2][p] = InteSpectrum(1, 2, p, kFALSE, kFALSE, 4);g[2][0]->SetName((sp[p] + sm[2]).Data());
                                          
  p = 5;//Kstar                          
  hD[p] = GetDataC("data/HEPData_1910.14397v1.root", 41); hD[p]->Scale(6);
  gD[p] = GetDataE("data/HEPData_1910.14397v1.root", 41); 
  g[0][p] = InteSpectrum(1, 0, 8, kFALSE, kFALSE, 6);g[0][0]->SetName((sp[8] + sm[0]).Data());
  g[1][p] = InteSpectrum(1, 1, 8, kFALSE, kFALSE, 6);g[1][0]->SetName((sp[8] + sm[1]).Data());
  g[2][p] = InteSpectrum(1, 2, 8, kFALSE, kFALSE, 6);g[2][0]->SetName((sp[8] + sm[2]).Data());
                                           
                                          
  p = 4;//Phi                            
  hD[p] = GetDataC("data/HEPData_1910.14397v1.root", 42); hD[p]->Scale(12);
  gD[p] = GetDataE("data/HEPData_1910.14397v1.root", 42); 
  g[0][p] = InteSpectrum(1, 0, p, kFALSE, kFALSE, 12);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum(1, 1, p, kFALSE, kFALSE, 12);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum(1, 2, p, kFALSE, kFALSE, 12);g[2][0]->SetName((sp[p] + sm[2]).Data());
                                          
  p = 1;//Lambda                          
  hD[p] = GetDataC("data/HEPData_1606.07424v2.root", 43); hD[p]->Scale(1);
  gD[p] = GetDataE("data/HEPData_1606.07424v2.root", 43); 
  g[0][p] = InteSpectrum(1, 0, p, kFALSE, kFALSE, 1);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum(1, 1, p, kFALSE, kFALSE, 1);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum(1, 2, p, kFALSE, kFALSE, 1);g[2][0]->SetName((sp[p] + sm[2]).Data());
                                         
  p = 2;//Xi                             
  hD[p] = GetDataC("data/HEPData_1606.07424v2.root", 44); hD[p]->Scale(2);
  gD[p] = GetDataE("data/HEPData_1606.07424v2.root", 44); 
  g[0][p] = InteSpectrum(1, 0, p, kFALSE, kFALSE, 2);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum(1, 1, p, kFALSE, kFALSE, 2);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum(1, 2, p, kFALSE, kFALSE, 2);g[2][0]->SetName((sp[p] + sm[2]).Data());
                                        
  p = 3;//Omega                         
  hD[p] = GetDataC("data/HEPData_1606.07424v2.root", 45); hD[p]->Scale(12);
  gD[p] = GetDataE("data/HEPData_1606.07424v2.root", 45); 
  g[0][p] = InteSpectrum(1, 0, p, kFALSE, kFALSE, 12);g[0][0]->SetName((sp[p] + sm[0]).Data());
  g[1][p] = InteSpectrum(1, 1, p, kFALSE, kFALSE, 12);g[1][0]->SetName((sp[p] + sm[1]).Data());
  g[2][p] = InteSpectrum(1, 2, p, kFALSE, kFALSE, 12);g[2][0]->SetName((sp[p] + sm[2]).Data());
//=============================================================================
  //Double_t x, y;
  //g[2]->GetPoint(nc-2, x, y);
  //auto y = (Double_t)hD->GetMaximum();
  auto dflx(0.), dfux(30.);
  auto dfly(1.9e-3), dfuy(1.6e1);
  

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

  for(int i = 0; i < 6; i++ ){
    DrawHisto(hD[i], wcl[i], wmk[0], "same");
    //DrawGraph(gD[i], wcl[i], "E2");
    g[0][i]->SetLineStyle(5);
    g[1][i]->SetLineStyle(3);
    g[2][i]->SetLineStyle(0);
    DrawGraph(g[0][i], wcl[i], "L");
    DrawGraph(g[1][i], wcl[i], "L");
    DrawGraph(g[2][i], wcl[i], "L");
  }


  auto leg(new TLegend(0.15, 0.88, 0.8, 0.91)); SetupLegend(leg);
  leg->SetNColumns(3);
  //leg->AddEntry(hD, "Data(7 TeV Incl)",  "P")->SetTextSizePixels(24);
  leg->AddEntry(g[0][0], "BLC",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[1][0], "Rope",  "L")->SetTextSizePixels(24);
  leg->AddEntry(g[2][0], "BLC + Rope",  "L")->SetTextSizePixels(24);
  leg->Draw();


  auto tex(new TLatex());
  tex->SetNDC();
  tex->SetTextSizePixels(28);
  tex->DrawLatex(0.16, 0.92, "pp #sqrt{#it{s}} = 7 TeV  Strange particle in UE");
  
  
  tex->DrawLatex(0.74, 0.85, "#color[1]{K^{0}_{S} (#times 4)}");
  tex->DrawLatex(0.74, 0.74, "#color[799]{K*^{0} (#times 6)}");
  tex->DrawLatex(0.74, 0.64, "#color[617]{#phi (#times 12)}"); 
  tex->DrawLatex(0.74, 0.56, "#color[633]{#Lambda + #bar{#Lambda}}");
  tex->DrawLatex(0.72, 0.46, "#color[601]{#Xi^{-} + #bar{#Xi}^{+} (#times 2)}");
  tex->DrawLatex(0.72, 0.3, "#color[419]{#Omega^{-} + #bar{#Omega}^{+} (#times 12)}");

  //can->SaveAs(Form("./figure/eps/%s.eps", can->GetName()));
  //can->SaveAs(Form("./figure/pdf/%s.pdf", can->GetName()));
  //can->SaveAs(Form("./figure/png/%s.png", can->GetName()));
  can->Print(Form("./figure/pdf/%s.eps", can->GetName()));
  can->Print(Form("./figure/pdf/%s.pdf", can->GetName()));
  can->Print(Form("./figure/pdf/%s.png", can->GetName()));
  CanvasEnd(can);
    
  return;
}

