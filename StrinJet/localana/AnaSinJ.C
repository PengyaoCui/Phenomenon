#include "inc/AnaSinJ.h"
#include <stdio.h>

//Int_t s = 1;// s: { "pp13TeV", "pp7TeV_Eta", "pp7TeV_Rap" };
//Int_t m = 2;;// m: { "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope", ... see inc/.h };
Int_t c[] = {0, 10, 40, 100}; Int_t nC = sizeof(c)/sizeof(Int_t);

//_____________________________________________________________________________

void AnaSinJ(Int_t m = 2){
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
  TList *l[np];
  for (Int_t i=0; i<np; i++) {
    auto list(l[i] = new TList());  //{"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton", "Kstar"};
   
    list->Add(new TH1D(Form("Integral_%s_In", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("Integral_%s_EtaIn", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("Integral_%s_JC", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("Integral_%s_PC", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("integral_%s_In", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("integral_%s_EtaIn", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("integral_%s_JC", sp[i].Data()), "", 1000, 0., 100.));
    list->Add(new TH1D(Form("integral_%s_PC", sp[i].Data()), "", 1000, 0., 100.));
    
    list->Add(new TH1D(Form("%s_In", sp[i].Data()), "", 500, 0., 25.));
    list->Add(new TH1D(Form("%s_EtaIn", sp[i].Data()), "", 500, 0., 25.));
    list->Add(new TH1D(Form("%s_JC", sp[i].Data()), "", 500, 0., 25.));
    list->Add(new TH1D(Form("%s_dJP", sp[i].Data()), "", 500, 0., 25.));
    list->Add(new TH1D(Form("%s_PC", sp[i].Data()), "", 500, 0., 25.));
  
    for(Int_t j=0; j<nC-1; j++){
      list->Add(new TH1D(Form("%s_In_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_EtaIn_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_JC_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_PC_%d%d", sp[i].Data(), c[j], c[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_dJP_%d%d", sp[i].Data(), c[j], c[j+1]), "", 200, 0., 2.));
    }
    for(Int_t j=0; j<nc-1; j++){
      list->Add(new TH1D(Form("%s_In_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_EtaIn_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_JC_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_PC_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]), "", 500, 0., 25.));
      list->Add(new TH1D(Form("%s_dJP_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]), "", 200, 0., 2.));
    }
    CallSumw2(l[i]);
  }

//_____________________________________________________________________________
  Double_t dFwdTrk[nc];  CentToFwdTrk(s, m, dFwdTrk);
  Double_t dNdEta[nc-1]; CentTodNdEta(s, m, dNdEta);

  ofstream OutFile;
  OutFile.open(Form("CenttodNdEta_%s_%s.txt", ss[s].Data(), sm[m].Data()));

  for(Int_t i = 0; i< nc-1; i++){
    OutFile<<left<<setw(15)<<Form("%.1f--%.1f", dCent[i], dCent[i+1])<<Form("<dNdEta> = %.1f", dNdEta[i]);
    OutFile<<endl;
  }
  OutFile<<left<<"================================ "<<endl;

  Double_t df[nC]; for(Int_t i = 0; i<nC-1; i++) {  CentToFwdTrk(s, m, c[i], c[i+1], df[i], df[i+1]);}//nfwdtrk larger->small
  Double_t dm[nC-1]; for(Int_t i = 0; i<nC-1; i++){
    CentTodNdEta(s, m, c[i], c[i+1], dm[i]);
    OutFile<<left<<setw(15)<<Form("%d--%d", c[i], c[i+1])<<Form("<dNdEta> = %.1f", dm[i]);
    OutFile<<endl;
  }//dNdEta larger->small


//_____________________________________________________________________________
  auto Chain((TChain*)CreateChain(s, m));
                                         
 
  printf("Number of particle: %d\n",(Int_t)Chain->GetEntries());

//=============================================================================
  Int_t Par;
  Double_t Fwdtrk;
  Double_t Midtrk;
  Double_t Pt;
  Double_t Eta;
  Double_t Rap;
  Double_t Accep;
  Double_t DPartoJet;
  Chain->SetBranchAddress("Species",&Par);//1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton; 9=Kstar
  Chain->SetBranchAddress("FwdTrk",&Fwdtrk);//Fwdtrack
  Chain->SetBranchAddress("MidTrk",&Midtrk);//MidTrack
  Chain->SetBranchAddress("Pt",&Pt);//Pt
  Chain->SetBranchAddress("Eta",&Eta);//Eta
  Chain->SetBranchAddress("Rapidity",&Rap);//Rapidity
  Chain->SetBranchAddress("Acceptence",&Accep);//1=in jet cone; 2=PC; 3=OC; 10=wo accepted jet in event
  Chain->SetBranchAddress("DPartoJet",&DPartoJet);//distance of particle to jet axis
 
//_____________________________________________________________________________
  for(int p=0;p<Chain->GetEntries();p++) {
    if(p%1000000==0) cout<<"Analysised particles ~ "<<p/1000000<< "M"<<endl;
    Chain->GetEntry(p);
 
//=============================================================================
    //np 1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton; 9=Kstar
    for(Int_t i = 0; i<np; i++) if(Par == i+1 ){
      for(Int_t j = 0; j<nc-1; j++) if (Fwdtrk<dFwdTrk[j] && Fwdtrk>dFwdTrk[j+1]){
        auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(dFwdTrk[j+1]), hFwdTrk->FindBin(dFwdTrk[j]));
        auto dJEvent = hJFwdTrk->Integral(hJFwdTrk->FindBin(dFwdTrk[j+1]), hJFwdTrk->FindBin(dFwdTrk[j]));
        (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_EtaIn", sp[i].Data()))))->Fill(dNdEta[j], 1./dEvent);
        if(Accep == 1) (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_JC", sp[i].Data()))))->Fill(dNdEta[j], 1./dJEvent);
        if(Accep == 2) (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_PC", sp[i].Data()))))->Fill(dNdEta[j], 1./dJEvent);
	
	(static_cast<TH1D*>(l[i]->FindObject(Form("%s_EtaIn_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]))))->Fill(Pt, 1./dEvent);
        if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_JC_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]))))->Fill(Pt, 1./dJEvent);
        if(Accep == 2)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_PC_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]))))->Fill(Pt, 1./dJEvent);
        if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_dJP_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]))))->Fill(DPartoJet, 1./dJEvent);
      }

      for(Int_t k = 0; k<nC-1; k++) if(Fwdtrk<df[k] && Fwdtrk>df[k+1]){
        auto dEvent = hFwdTrk->Integral(hFwdTrk->FindBin(df[k+1]), hFwdTrk->FindBin(df[k]));
        auto dJEvent = hJFwdTrk->Integral(hJFwdTrk->FindBin(df[k+1]), hJFwdTrk->FindBin(df[k]));
        (static_cast<TH1D*>(l[i]->FindObject(Form("integral_%s_EtaIn", sp[i].Data()))))->Fill(dm[k], 1./dEvent);
        if(Accep == 1) (static_cast<TH1D*>(l[i]->FindObject(Form("integral_%s_JC", sp[i].Data()))))->Fill(dm[k], 1./dJEvent);
        if(Accep == 2) (static_cast<TH1D*>(l[i]->FindObject(Form("integral_%s_PC", sp[i].Data()))))->Fill(dm[k], 1./dJEvent);
        
	(static_cast<TH1D*>(l[i]->FindObject(Form("%s_EtaIn_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(Pt, 1./dEvent);
        if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_JC_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(Pt, 1./dJEvent);
        if(Accep == 2)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_PC_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(Pt, 1./dJEvent);
        if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_dJP_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(DPartoJet, 1./dJEvent);
      }

      (static_cast<TH1D*>(l[i]->FindObject(Form("%s_EtaIn", sp[i].Data()))))->Fill(Pt, 1./hEvent->GetBinContent(1));
      if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_JC", sp[i].Data()))))->Fill(Pt, 1./hJEvent->GetBinContent(1));
      if(Accep == 2)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_PC", sp[i].Data()))))->Fill(Pt, 1./hJEvent->GetBinContent(1));
      if(Accep == 1)(static_cast<TH1D*>(l[i]->FindObject(Form("%s_dJP", sp[i].Data()))))->Fill(DPartoJet, 1./hJEvent->GetBinContent(1));
    }
  
  }

//_____________________________________________________________________________
  
  //get inclusive results with rap
  s=2;
  
  auto hevent(new TH1D("hevent", "", 10, 0.5, 10.5)); hevent->SetBinContent(1, nEvent(s,m));levent->Add(hevent);
  auto hfwdtrk((TH1D*)FwdTrk(s, m));hfwdtrk->SetName("hfwdtrk");levent->Add(hfwdtrk);
  auto htrketa((TH1D*)TrkEta(s, m)); htrketa->SetName("htrketa"); levent->Add(htrketa);
  auto hdnfwddeta((TH1D*)dNfwddEta(s, m)); hdnfwddeta->SetName("hdnfwddeta"); levent->Add(hdnfwddeta);
  auto hdnmiddeta((TH1D*)dNmiddEta(s, m)); hdnmiddeta->SetName("hdnmiddeta"); levent->Add(hdnmiddeta);
  
  
  Double_t dfwdtrk[nc];  CentToFwdTrk(s, m, dfwdtrk);
  Double_t dndeta[nc-1]; CentTodNdEta(s, m, dndeta);

  Double_t dF[nC]; for(Int_t i = 0; i<nC-1; i++)   CentToFwdTrk(s, m, c[i], c[i+1], dF[i], dF[i+1]);//nfwdtrk larger->small
  Double_t dM[nC-1]; for(Int_t i = 0; i<nC-1; i++) CentTodNdEta(s, m, c[i], c[i+1], dM[i]);

  auto chain((TChain*)CreateChain(s, m));
  printf("Number of particle: %d\n",(Int_t)chain->GetEntries());

//=============================================================================
  Int_t par;
  Double_t fwdtrk;
  Double_t midtrk;
  Double_t pt;
  Double_t eta;
  Double_t rap;
  Double_t accep;
  Double_t dpartojet;
  chain->SetBranchAddress("Species",&par);//1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton; 9=Kstar
  chain->SetBranchAddress("FwdTrk",&fwdtrk);//Fwdtrack
  chain->SetBranchAddress("MidTrk",&midtrk);//MidTrack
  chain->SetBranchAddress("Pt",&pt);//Pt
  chain->SetBranchAddress("Eta",&eta);//Eta
  chain->SetBranchAddress("Rapidity",&rap);//Rapidity
  chain->SetBranchAddress("Acceptence",&accep);//1=in jet cone; 2=PC; 3=OC; 10=wo accepted jet in event
  chain->SetBranchAddress("DPartoJet",&dpartojet);//distance of particle to jet axis


  //_____________________________________________________________________________
  for(int p=0;p<chain->GetEntries();p++) {
    if(p%1000000==0) cout<<"Analysised particles ~ "<<p/1000000<< "M"<<endl;
    chain->GetEntry(p);

//=============================================================================
    //np 1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton; 9=Kstar
    for(Int_t i = 0; i<np; i++) if(par == i+1 ){
      for(Int_t j = 0; j<nc-1; j++) if (fwdtrk<dfwdtrk[j] && fwdtrk>dfwdtrk[j+1]){
        auto devent = hfwdtrk->Integral(hfwdtrk->FindBin(dfwdtrk[j+1]), hfwdtrk->FindBin(dfwdtrk[j]));
        (static_cast<TH1D*>(l[i]->FindObject(Form("Integral_%s_In", sp[i].Data()))))->Fill(dndeta[j], 1./devent);
        (static_cast<TH1D*>(l[i]->FindObject(Form("%s_In_%.2f%.2f", sp[i].Data(), dCent[j], dCent[j+1]))))->Fill(pt, 1./devent);
      }

      for(Int_t k = 0; k<nC-1; k++) if(fwdtrk<df[k] && fwdtrk>df[k+1]){
        auto devent = hfwdtrk->Integral(hfwdtrk->FindBin(dF[k+1]), hfwdtrk->FindBin(dF[k]));
        (static_cast<TH1D*>(l[i]->FindObject(Form("integral_%s_In", sp[i].Data()))))->Fill(dM[k], 1./devent);
        (static_cast<TH1D*>(l[i]->FindObject(Form("%s_In_%d%d", sp[i].Data(), c[k], c[k+1]))))->Fill(pt, 1./devent);
      }
      (static_cast<TH1D*>(l[i]->FindObject(Form("%s_In", sp[i].Data()))))->Fill(pt, 1./hevent->GetBinContent(1));
    }

  }
//_____________________________________________________________________________
  CallSumw2(levent);
  levent->Print();
  for (unsigned int i=0; i<np; ++i) l[i]->Print();
  
//=============================================================================
  f->cd();
  levent->Write("levent", TObject::kSingleKey);
  for (unsigned int i=0; i<np; ++i) l[i]->Write(sp[i], TObject::kSingleKey);
  f->Close();
  return;
}

