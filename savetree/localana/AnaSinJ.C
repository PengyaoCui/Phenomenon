#include "inc/AnaSinJ.h"

Int_t s = 1;// s: { "pp13TeV", "pp7TeV" };
Int_t m = 2;;// m: { "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope", ... see inc/.h };
Int_t c[] = {0, 10, 40, 100}; Int_t nC = sizeof(c)/sizeof(Int_t);

//_____________________________________________________________________________

void AnaSinJ(){

  TFile* f(TFile::Open(("Results_" + ss[s] + "_" + sm[m] + ".root").Data() , "recreate"));

//=============================================================================
  auto levent(new TList());
  auto hEvent(new TH1D("hEvent", "", 10, 0.5, 10.5)); hEvent->SetBinContent(1, nEvent(s,m));levent->Add(hEvent);
  auto hFwdTrk((TH1D*)FwdTrk(s, m));hFwdTrk->SetName("hFwdTrk");levent->Add(hFwdTrk);
  auto hTrkEta((TH1D*)TrkEta(s, m)); hTrkEta->SetName("hTrkEta"); levent->Add(hTrkEta);
  auto hdNfwddEta((TH1D*)dNfwddEta(s, m)); hdNfwddEta->SetName("hdNfwddEta"); levent->Add(hdNfwddEta);

  CallSumw2(levent);
//=============================================================================
  TList *l[np];
  for (Int_t i=0; i<np; i++) {
    auto list(l[i] = new TList());  //{"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"};
    list->Add(new TH1D(Form("Integral_%s_In", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("Integral_%s_JC", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("Integral_%s_PC", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("%s_In", sp[i].Data()), "", 500, 0., 25.));
    list->Add(new TH1D(Form("%s_JC", sp[i].Data()), "", 500, 0., 25.));
    list->Add(new TH1D(Form("%s_PC", sp[i].Data()), "", 500, 0., 25.));
    for(Int_t j=0; j<nC-1; j++){
      list->Add(new TH1D(Form("%s_In_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_JC_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_PC_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
    }
  }

//_____________________________________________________________________________
  Double_t dFwdTrk[nc];  CentToFwdTrk(s, m, dFwdTrk);
  Double_t dNdEta[nc-1]; CentTodNdEta(s, m, dNdEta);

  Double_t df[nC]; for(Int_t i = 0; i<nC-1; i++) CentToFwdTrk(s, m, c[i], c[i+1], df[i], df[i+1]);//nfwdtrk larger->small


//_____________________________________________________________________________
  auto chain((TChain*)CreateChain(s, m));
                                         
 
  printf("Number of particle: %d\n",(Int_t)chain->GetEntries());

//=============================================================================
  Int_t Par;
  Double_t Fwdtrk;
  Double_t Midtrk;
  Double_t Pt;
  Double_t Eta;
  Double_t Accep;
  chain->SetBranchAddress("Species",&Par);//1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton
  chain->SetBranchAddress("FwdTrk",&Fwdtrk);//Fwdtrack
  chain->SetBranchAddress("MidTrk",&Midtrk);//MidTrack
  chain->SetBranchAddress("Pt",&Pt);//Pt
  chain->SetBranchAddress("Eta",&Eta);//Eta
  chain->SetBranchAddress("Acceptence",&Accep);//1=in jet cone; 2=PC; 3=OC; 10=wo accepted jet in event
 
//_____________________________________________________________________________
  for(int p=0;p<chain->GetEntries();p++) {
    if(p%1000000==0) cout<<"Analysised particles ~ "<<p/1000000<< "M"<<endl;
    chain->GetEntry(p);
  
//=============================================================================
    //np 1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton
    for(Int_t i = 0; i<np; i++) if(Par == i+1 ){
      for(Int_t j = 0; j<nc-1; j++) if (Fwdtrk<dFwdTrk[j] && Fwdtrk>dFwdTrk[j+1]){
	auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwdTrk[j+1]), hFwdTrk->FindBin(dFwdTrk[j]));
        (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_In", sp[i].Data()))))->Fill(dNdEta[j], 1./dEvent);
        if(Accep == 1) (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_JC", sp[i].Data()))))->Fill(dNdEta[j]);
        if(Accep == 2) (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_PC", sp[i].Data()))))->Fill(dNdEta[j]);
      }
      for(Int_t k = 0; k<nC-1; k++) if(Fwdtrk<df[k] && Fwdtrk>df[k+1]){
        auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(df[k+1]), hFwdTrk->FindBin(df[k]));
        (static_cast<TH1D*>(l[i]->FindObject(Form("%s_In_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(Pt, 1./dEvent);
        if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_JC_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(Pt);
        if(Accep == 2)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_PC_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(Pt);
      }
      (static_cast<TH1D*>(l[i]->FindObject(Form("%s_In", sp[i].Data()))))->Fill(Pt);
      if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_JC", sp[i].Data()))))->Fill(Pt);
      if(Accep == 2)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_PC", sp[i].Data()))))->Fill(Pt);
    }
    
  
//=============================================================================
  
  
  }

  
//_____________________________________________________________________________
  levent->Print();
  for (unsigned int i=0; i<np; ++i) l[i]->Print();
  
//=============================================================================
  f->cd();
  levent->Write("levent", TObject::kSingleKey);
  for (unsigned int i=0; i<np; ++i) l[i]->Write(sp[i], TObject::kSingleKey);
  f->Close();
  return;
}

