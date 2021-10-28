#include "inc/AnaSinJ.h"
#include <stdio.h>

void AnaSinJ(Int_t m = 0){
  Int_t s = 1;// s: { "pp13TeV", "pp7TeV_Eta", "pp7TeV_Rap" };
  //TFile* f(TFile::Open(("Results_" + ss[s] + "_" + sm[m] + ".root").Data() , "recreate"));
  TFile* f(TFile::Open(("Results_pp7TeV_" + sm[m] + ".root").Data() , "recreate"));

//=============================================================================
  auto levent(new TList());
  auto hEvent(new TH1D("hEvent", "", 10, 0.5, 10.5)); hEvent->SetBinContent(1, nEvent(s,m));levent->Add(hEvent);
  auto hJEvent(new TH1D("hJEvent", "", 10, 0.5, 10.5)); hJEvent->SetBinContent(1, nJEvent(s,m));levent->Add(hJEvent);
  auto hFwdTrk((TH1D*)FwdTrk(s, m));hFwdTrk->SetName("hFwdTrk");levent->Add(hFwdTrk);
  auto hJFwdTrk((TH1D*)JFwdTrk(s, m));hJFwdTrk->SetName("hJFwdTrk");levent->Add(hJFwdTrk);
  auto hTrkEta((TH1D*)TrkEta(s, m)); hTrkEta->SetName("hTrkEta"); levent->Add(hTrkEta);
  auto hdNfwddEta((TH1D*)dNfwddEta(s, m)); hdNfwddEta->SetName("hdNfwddEta"); levent->Add(hdNfwddEta);
  auto hdNmiddEta((TH1D*)dNmiddEta(s, m)); hdNmiddEta->SetName("hdNmiddEta"); levent->Add(hdNmiddEta);


//=============================================================================
  CallSumw2(levent);
  levent->Print();
  f->cd();
  levent->Write("levent", TObject::kSingleKey);

  f->Close();
  return;
}

