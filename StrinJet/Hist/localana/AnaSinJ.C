#include "inc/AnaSinJ.h"
#include <stdio.h>

const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
const auto nc(sizeof(dCent)/sizeof(Double_t));
Double_t dFwd[nc]; Double_t dNdEta[nc-1];

void AnaSinJ(){

  TString sm = "Monash";//"CR", "Rope", "CR+Rope", "Monash"
//==Read generated files=======================================================
  auto fs(TFile::Open(("sim/" + sm + ".root").Data() , "read"));//Open Monash output
  auto lresults(static_cast<TList*>(fs->Get("list_results")));
  auto lI(static_cast<TList*>(fs->Get("list_I")));
  auto lJ(static_cast<TList*>(fs->Get("list_J")));
  auto lP(static_cast<TList*>(fs->Get("list_P")));
  fs->Close();
//=============================================================================
  
  auto f(TFile::Open(("Results_" + sm + ".root").Data() , "recreate"));

  auto l(new TList());

//-----------------------------------------------------------------------------
  
  auto hPtHat((TH2D*)lresults->FindObject("hPtHat")); 
  const auto nEvent(hPtHat->GetEntries()); 
  Int_t nJEvent; 
  

//--General used information--------------------------------------------------------------------------
  auto hEvent(new TH1D("hEvent", "", 10, 0.5, 10.5)); hEvent->SetBinContent(1, nEvent); l->Add(hEvent);
  auto hJEvent((TH1D*)lresults->FindObject("hJEvent")); l->Add(hJEvent);
  nJEvent = hJEvent->GetEntries();

  auto hFwdVsMid((TH2D*)lresults->FindObject("hFwdVsMid"));
  for(int i = 1; i<nc; i++){
    CentToFwdTrk(hFwdVsMid, dCent[i-1], dCent[i], dFwd[i-1], dFwd[i]);
    CentTodNdEta(hFwdVsMid, dCent[i-1], dCent[i], dNdEta[i-1]);
  }
//--Save the dNdEta and N_Fwd value-------------------------------------------------------------------
  ofstream OutFile;
  OutFile.open(Form("CenttodNdEta_%s.txt", sm.Data()));
  //dNdEta larger->small
  for(Int_t i = 0; i< nc-1; i++){
    OutFile<<left<<setw(15)<<Form("%.1f--%.1f", dCent[i], dCent[i+1])<<Form("<dNdEta> = %.1f", dNdEta[i]);
    OutFile<<endl;
  }
  OutFile<<left<<"================================ "<<endl;
  //N_Fwd larger->small
  for(Int_t i = 0; i< nc-1; i++){
    OutFile<<left<<setw(15)<<Form("%.1f--%.1f", dCent[i], dCent[i+1])<<Form("N_Fwd = %.1f--%.1f", dFwd[i], dFwd[i+1]);
    OutFile<<endl;
  }
  OutFile<<left<<"================================ "<<endl;

//--Get track eta distribution-------------------------------------------------
  //auto hMidTrEta((TH1D*)lresults->FindObject("hMidTrEta")); l->Add(hMidTrEta);
  auto hTrEta((TH1D*)lresults->FindObject("hTrEta"));
  hTrEta->Rebin(10);
  hTrEta->Scale(1./nEvent); 
  NormBinningHistogram(hTrEta);
  l->Add(hTrEta);

//--Get Nmid track distribution------------------------------------------------
  auto hMidTrk((TH1D*)hFwdVsMid->ProjectionX());hMidTrk->SetName("hMidTrk");
  hMidTrk->Rebin(10);
  hMidTrk->Scale(1./hMidTrk->GetEntries());
  NormBinningHistogram(hMidTrk);
  l->Add(hMidTrk);

//--Get NFwd track distribution------------------------------------------------
  auto hFwdTrk((TH1D*)hFwdVsMid->ProjectionY());hFwdTrk->SetName("hFwdTrk");

//--Get integral yield of inclusive--------------------------------------------
  auto hKshortFwd((TH1D*)lI->FindObject("hKshortFwd"));
  TH1D* hKshortI = new TH1D("hKshortI", "", 400, 0., 40); 
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hKshortFwd->Integral(hKshortFwd->FindBin(dFwd[i]), hKshortFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hKshortI->SetBinContent(hKshortI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hKshortI->SetBinError(hKshortI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hKshortI);

  auto hLambdaFwd((TH1D*)lI->FindObject("hLambdaFwd"));
  TH1D* hLambdaI = new TH1D("hLambdaI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hLambdaFwd->Integral(hLambdaFwd->FindBin(dFwd[i]), hLambdaFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hLambdaI->SetBinContent(hLambdaI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hLambdaI->SetBinError(hLambdaI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hLambdaI);

  auto hXiFwd((TH1D*)lI->FindObject("hXiFwd"));
  TH1D* hXiI = new TH1D("hXiI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hXiFwd->Integral(hXiFwd->FindBin(dFwd[i]), hXiFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hXiI->SetBinContent(hXiI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hXiI->SetBinError(hXiI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hXiI);

  auto hOmegaFwd((TH1D*)lI->FindObject("hOmegaFwd"));
  TH1D* hOmegaI = new TH1D("hOmegaI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hOmegaFwd->Integral(hOmegaFwd->FindBin(dFwd[i]), hOmegaFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hOmegaI->SetBinContent(hOmegaI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hOmegaI->SetBinError(hOmegaI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hOmegaI);

  auto hPhiFwd((TH1D*)lI->FindObject("hPhiFwd"));
  TH1D* hPhiI = new TH1D("hPhiI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hPhiFwd->Integral(hPhiFwd->FindBin(dFwd[i]), hPhiFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hPhiI->SetBinContent(hPhiI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hPhiI->SetBinError(hPhiI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hPhiI);

  auto hKstarFwd((TH1D*)lI->FindObject("hKstarFwd"));
  TH1D* hKstarI = new TH1D("hKstarI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hKstarFwd->Integral(hKstarFwd->FindBin(dFwd[i]), hKstarFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hKstarI->SetBinContent(hKstarI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hKstarI->SetBinError(hKstarI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hKstarI);

  auto hPionFwd((TH1D*)lI->FindObject("hPionFwd"));
  TH1D* hPionI = new TH1D("hPionI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hPionFwd->Integral(hPionFwd->FindBin(dFwd[i]), hPionFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hPionI->SetBinContent(hPionI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hPionI->SetBinError(hPionI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hPionI);

  auto hKionFwd((TH1D*)lI->FindObject("hKionFwd"));
  TH1D* hKionI = new TH1D("hKionI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hKionFwd->Integral(hKionFwd->FindBin(dFwd[i]), hKionFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hKionI->SetBinContent(hKionI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hKionI->SetBinError(hKionI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hKionI);

  auto hProtonFwd((TH1D*)lI->FindObject("hProtonFwd"));
  TH1D* hProtonI = new TH1D("hProtonI", "", 400, 0., 40);
  for(Int_t i = 1; i< nc; i++){
    auto Npar(hProtonFwd->Integral(hProtonFwd->FindBin(dFwd[i]), hProtonFwd->FindBin(dFwd[i-1])));
    auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
    hProtonI->SetBinContent(hProtonI->FindBin(dNdEta[i-1]), Npar/dEvent);
    hProtonI->SetBinError(hProtonI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/dEvent);
  } l->Add(hProtonI);

//--Get integral yield of JC--------------------------------------------


//=============================================================================

  CallSumw2(l);
  l->Print();
  f->cd();
  l->Write(sm, TObject::kSingleKey);

  f->Close();
  return;
}

