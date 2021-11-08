#include "inc/AnaSinJ.h"
#include <stdio.h>

const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
const auto nc(sizeof(dCent)/sizeof(Double_t));
Double_t dFwd[nc]; Double_t dNdEta[nc-1];

void AnaSinJ(const TString sm = "Monash"){

  //sm = "CR", "Rope", "CR+Rope", "Monash"
//==Read generated files=======================================================
  auto fs(TFile::Open(("sim/" + sm + ".root").Data() , "read"));//Open Monash output
  auto lresults(static_cast<TList*>(fs->Get("list_results")));
  auto lI(static_cast<TList*>(fs->Get("list_I")));CallSumw2(lI);
  auto lJ(static_cast<TList*>(fs->Get("list_J")));CallSumw2(lJ);
  auto lP(static_cast<TList*>(fs->Get("list_P")));CallSumw2(lP);
  fs->Close();
//=============================================================================
  
  //auto f(TFile::Open(("Results_" + sm + ".root").Data() , "recreate"));
  auto f(TFile::Open("Results.root", "update"));

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
  
  
  OutFile<<left<<"=========="<<sm<<"==================== "<<endl;
  //dNdEta larger->small
  for(Int_t i = 0; i< nc-1; i++){
    OutFile<<left<<setw(15)<<Form("%.2f--%.2f", dCent[i], dCent[i+1])<<Form("<dNdEta> = %.2f", dNdEta[i]);
    OutFile<<endl;
  }
  OutFile<<left<<"================================ "<<endl;
  //N_Fwd larger->small
  for(Int_t i = 0; i< nc-1; i++){
    OutFile<<left<<setw(15)<<Form("%.2f--%.2f", dCent[i], dCent[i+1])<<Form("N_Fwd = %.2f--%.2f", dFwd[i], dFwd[i+1]);
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
  auto hJFwdVsMid((TH2D*)lresults->FindObject("hJFwdVsMid"));
  auto hJFwdTrk((TH1D*)hJFwdVsMid->ProjectionY());hJFwdTrk->SetName("hJFwdTrk");

  for(int p = 0; p<np; p++){
    //--Get integral yield of inclusive----------------------------------
    auto hFwd((TH1D*)lI->FindObject(Form("h%sFwd", sp[p].Data())));
    TH1D* hI = new TH1D(Form("hIn%s", sp[p].Data()), "", 400, 0., 40); 
    for(Int_t i = 1; i< nc; i++){
      auto Npar(hFwd->Integral(hFwd->FindBin(dFwd[i]), hFwd->FindBin(dFwd[i-1])));
      auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwd[i]), hFwdTrk->FindBin(dFwd[i-1]));
      hI->SetBinContent(hI->FindBin(dNdEta[i-1]), Npar/(dEvent * 0.5 * 2.));
      hI->SetBinError(hI->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/(dEvent * 0.5 *2.));
    }
    l->Add(hI);

    //--Get integral yield of JC----------------------------------------
    auto hJCFwd((TH1D*)lJ->FindObject(Form("hJC%sFwd", sp[p].Data())));
    TH1D* hJC = new TH1D(Form("hJC%s", sp[p].Data()), "", 400, 0., 40);
    for(Int_t i = 1; i< nc; i++){
      auto Npar(hJCFwd->Integral(hJCFwd->FindBin(dFwd[i]), hJCFwd->FindBin(dFwd[i-1])));
      auto dJEvent = hJFwdTrk->Integral(hJFwdTrk->FindBin(dFwd[i]), hJFwdTrk->FindBin(dFwd[i-1]));
      hJC->SetBinContent(hJC->FindBin(dNdEta[i-1]), Npar/(dJEvent*2.*0.75*TMath::TwoPi()*0.06));
      hJC->SetBinError(hJC->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/(dJEvent*2.*0.75*TMath::TwoPi()*0.06));
    }
    l->Add(hJC);

    //--Get integral yield of PC----------------------------------------
    auto hPCFwd((TH1D*)lP->FindObject(Form("hPC%sFwd", sp[p].Data())));
    TH1D* hPC = new TH1D(Form("hPC%s", sp[p].Data()), "", 400, 0., 40);
    for(Int_t i = 1; i< nc; i++){
      auto Npar(hPCFwd->Integral(hPCFwd->FindBin(dFwd[i]), hPCFwd->FindBin(dFwd[i-1])));
      auto dJEvent = hJFwdTrk->Integral(hJFwdTrk->FindBin(dFwd[i]), hJFwdTrk->FindBin(dFwd[i-1]));
      hPC->SetBinContent(hPC->FindBin(dNdEta[i-1]), Npar/(dJEvent*2.*0.75*TMath::TwoPi()*0.06*4.));
      hPC->SetBinError(hPC->FindBin(dNdEta[i-1]), TMath::Sqrt(Npar)/(dJEvent*2.*0.75*TMath::TwoPi()*0.06*4.));
    }
    l->Add(hPC);
    
    //--Get integral yield of JE----------------------------------------
    TH1D* hJE = (TH1D*)hJC->Clone(Form("hJE%s", sp[p].Data())); hJE->Add(hPC, -1.);
    l->Add(hJE);
  
  }
  
//==Ratio to pi================================================================
  for(int p = 0; p<np; p++){
    if(sp[p] == "Pion") continue;
    auto hIn((TH1D*)l->FindObject(Form("hIn%s", sp[p].Data())));
    auto hJE((TH1D*)l->FindObject(Form("hJE%s", sp[p].Data())));
    auto hPC((TH1D*)l->FindObject(Form("hPC%s", sp[p].Data())));
    
    auto hInPi((TH1D*)l->FindObject(Form("hInPion")));
    auto hJEPi((TH1D*)l->FindObject(Form("hJEPion")));
    auto hPCPi((TH1D*)l->FindObject(Form("hPCPion")));

    TH1D* hInRtoPi = (TH1D*)hIn->Clone(Form("hIn%stoPi", sp[p].Data())); 
    TH1D* hPCRtoPi = (TH1D*)hPC->Clone(Form("hPC%stoPi", sp[p].Data())); 
    TH1D* hJERtoPi = (TH1D*)hJE->Clone(Form("hJE%stoPi", sp[p].Data())); 
    hInRtoPi->Divide(hInPi); 
    hPCRtoPi->Divide(hPCPi); 
    hJERtoPi->Divide(hJEPi); 
    l->Add(hInRtoPi); 
    l->Add(hPCRtoPi); 
    l->Add(hJERtoPi); 
  }

//==Ratio to Kshort Vs Particle to Jet distance================================
  for(int p = 0; p<np-3; p++){
    if(sp[p] == "Kshort") continue;
    auto hPJK((TH1D*)lJ->FindObject(Form("hKshortPJ")));
    auto hPJP((TH1D*)lJ->FindObject(Form("h%sPJ", sp[p].Data())));

    auto dJEvent = hJFwdTrk->GetEntries();
    auto hPCFwd((TH1D*)lP->FindObject(Form("hPC%sFwd", sp[p].Data())));
    Double_t dUE = hPCFwd->GetEntries();
    dUE = dUE/(dJEvent*2.*0.75*TMath::TwoPi()*0.06*4.);

    for(int i = 1; i<= hPJK->GetNbinsX(); i++){
      auto dvK = hPJK->GetBinContent(i);
      auto deK = hPJK->GetBinError(i);
      
      auto dvP = hPJP->GetBinContent(i); 
      auto deP = hPJP->GetBinError(i);
      
      auto dLower(hPJK->GetXaxis()->GetBinLowEdge(i));
      auto dUpper(hPJK->GetXaxis()->GetBinUpEdge(i) );
      auto deltaR = (dUpper*dUpper - dLower*dLower); 
      
      dvK = (dvK - dUE*TMath::Pi()*deltaR); deK = deK; 
      dvP = (dvP - dUE*TMath::Pi()*deltaR); deP = deP; 
      hPJK->SetBinContent(i, dvK); hPJK->SetBinError(i, deK); 
      hPJP->SetBinContent(i, dvP); hPJP->SetBinError(i, deP); 
    }
    auto hJPRtoK = (TH1D*)hPJP->Clone(Form("hPJ%stoKshort", sp[p].Data()));
    hJPRtoK->Divide(hPJK); 
    l->Add(hPJP);
    if(sp[p] == "Lambda")l->Add(hPJK);
    l->Add(hJPRtoK);
  }
//=============================================================================

  CallSumw2(l);
  l->Print();
  f->cd();
  l->Write(sm, TObject::kSingleKey);

  f->Close();
  return;
}

