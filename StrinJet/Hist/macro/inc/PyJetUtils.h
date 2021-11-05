#include "TAliFigs.h"
#include "TPlotStd.h"
#include "TUtilHisto.h"
//=============================================================================

//const Double_t dIn[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 15. };
//const auto nIn(sizeof(dIn) / sizeof(Double_t) - 1);
//
//const Double_t dJE[] = { 0.6, 1.6, 2.2, 2.8, 3.7, 5., 8., 12., 15. };
//const auto nJE(sizeof(dJE) / sizeof(Double_t) - 1);

//const TString ss[] { "pp13TeV", "pp7TeV" };
//const auto ns(sizeof(ss)/sizeof(TString));

//const TString sm[] { "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope", "HardQCD_CR", "HardQCD_Rope", "HardQCD_CRandRope" };
//const auto nm(sizeof(sm) / sizeof(TString));

const TString sp[] = {"Kshort", "Lambda", "Xi", "Omega", "Phi", "Kstar", "Pion", "Kion", "Proton"};
const auto np(sizeof(sp) / sizeof(TString));

//const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
//const auto nc(sizeof(dCent)/sizeof(Double_t));

//const auto acc = 0.5;

//_____________________________________________________________________________
TH1D* dNmdEta(const TString sm = "Monash",
              const bool r = kFALSE)
{
  const TString sf(Form("sim/Results.root"));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get(sm)));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::TrkEta", "No list: listevent");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject("hMidTrk"));
  if(r){
    h->Rebin(5);
    NormBinningHistogram(h);
  }
  return h;
}


//_____________________________________________________________________________
TH1D* Trketa(const TString sm = "Monash")
{
  const TString sf(Form("sim/Results.root"));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get(sm)));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::TrkEta", "No list: listevent");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject("hTrEta"));
  //h->Rebin(20);
  //NormBinningHistogram(h);

  return h;
}

////=============================================================================
//TH1D* dNfwddEta(const int s,
//                const int m)
//{
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get("levent")));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::TrkEta", "No list: listevent");
//    exit(-2);
//  }
//
//  auto h((TH1D*)list->FindObject("hdNfwddEta"));
//  h->Rebin(5);
//
//  return h;
//}
//
//
////=============================================================================
//void dNdEtaVal(const int s,
//	       const int m,
//	       TH1D*h,
//	       Double_t dNdEta[nc-1])
//{
//  auto dndeta = 0.; int k = 0;
//  for(int i =1; i<= h->GetNbinsX(); i++){
//    if(h->GetBinContent(i) != 0.){
//      dNdEta[k] = h->GetBinCenter(i);
//      k++;
//    }
//  }
//}
//
////=============================================================================
//void IntegralVal(const int s,
//                 const int m,
//                 const int p,
//		 Double_t dNdEta[nc-1],
//	         Double_t dVal[nc-1],
//		 bool j = kFALSE,
//		 bool u = kFALSE)
//{
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  auto h((TH1D*)list->FindObject(Form("Integral_%s_In", sp[p].Data())));
//  if(j) h=(TH1D*)list->FindObject(Form("Integral_%s_JC", sp[p].Data()));
//  if(u) h=(TH1D*)list->FindObject(Form("Integral_%s_PC", sp[p].Data()));
//  
//  dNdEtaVal(s, m, h, dNdEta);
//  for(int i = 0; i<nc-1; i++){dVal[i] = h->GetBinContent(h->FindBin(dNdEta[i]));}
//
//  return;
//}
//
////=============================================================================
//TH1D* InteSpect(const int s,
//                 const int m,
//                 const int p,
//                 bool j = kFALSE,
//                 bool u = kFALSE,
//		 const int t = 1)
//{
//  auto Acc(acc); if(j || u) Acc = 0.75;
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  TH1D* h;
//  if(!j && !u){
//    h = ((TH1D*)list->FindObject(Form("Integral_%s_In", sp[p].Data())));
//    h->Scale(t);
//  }
//  if(j){
//    h=(TH1D*)list->FindObject(Form("Integral_%s_JC", sp[p].Data()));
//    auto H=(TH1D*)list->FindObject(Form("Integral_%s_PC", sp[p].Data())); H->Scale(-1.*0.25);
//    h->Add(H);
//    h->Scale(1./0.6);
//    h->Scale(t);
//  }
//  if(u){
//    h=(TH1D*)list->FindObject(Form("Integral_%s_PC", sp[p].Data()));
//    h->Scale(0.25/0.6);
//    h->Scale(t);
//  }
//  
//  if(!(p == 1 || p==2 || p==3)) h->Scale(1./(Acc*2.));
//  if(p == 1 || p==2 || p==3) h->Scale(1./(Acc));//2.*dPa[i]/(Acc*2.)
//
//  return h;
//}
//
//_____________________________________________________________________________
TGraphErrors* InteSpectrum(const TString sm,
                     const int p,
		     bool j = kFALSE,
		     bool u = kFALSE,
		     const double t = 1.)
{
 
  auto file(TFile::Open("sim/Results.root", "read"));
  auto list(static_cast<TList*>(file->Get(sm)));
  auto h((TH1D*)list->FindObject(Form("hIn%s", sp[p].Data())));
  if(j) h = (TH1D*)list->FindObject(Form("hJE%s", sp[p].Data()));
  if(u) h = (TH1D*)list->FindObject(Form("hPC%s", sp[p].Data()));
  h->Scale(t); h->SetName(sm);

  int k = 0;
  for(int i =1; i<= h->GetNbinsX(); i++){
    if(h->GetBinContent(i) != 0.){
      k++;
    }
  }
  const int nc = k;
  Double_t dvx[nc]; Double_t dvy[nc];
  Double_t dex[nc]; Double_t dey[nc];

  int c = 0;
  for(int i =1; i<= h->GetNbinsX(); i++){
    if(h->GetBinContent(i) != 0.){
      dvx[c] = h->GetBinCenter(i);
      dvy[c] = h->GetBinContent(i);
      dex[c] = 0.;
      dey[c] = h->GetBinError(i);
      c++;
    }
  }
  
  return(new TGraphErrors(nc,dvx,dvy,dex,dey));
}

//_____________________________________________________________________________
TGraphErrors* RatioToPi(const TString sm,
                     const int p,
                     bool j = kFALSE,
                     bool u = kFALSE,
                     const double t = 1.)
{

  auto file(TFile::Open("sim/Results.root", "read"));
  auto list(static_cast<TList*>(file->Get(sm)));
  auto h((TH1D*)list->FindObject(Form("hIn%stoPi", sp[p].Data())));
  if(j) h = (TH1D*)list->FindObject(Form("hJE%stoPi", sp[p].Data()));
  if(u) h = (TH1D*)list->FindObject(Form("hPC%stoPi", sp[p].Data()));
  //h->Scale(t); //h->SetName(sm);
  
  //auto hPi((TH1D*)list->FindObject(Form("hInPion")));
  //if(j) hPi = (TH1D*)list->FindObject(Form("hJEPion"));
  //if(u) hPi = (TH1D*)list->FindObject(Form("hPCPion"));

  //h->Divide(hPi);

  int k = 0;
  for(int i =1; i<= h->GetNbinsX(); i++){
    if(h->GetBinContent(i) != 0.){
      k++;
    }
  }
  const int nc = k;
  Double_t dvx[nc]; Double_t dvy[nc];
  Double_t dex[nc]; Double_t dey[nc];

  int c = 0;
  for(int i =1; i<= h->GetNbinsX(); i++){
    if(h->GetBinContent(i) != 0.){
      dvx[c] = h->GetBinCenter(i);
      dvy[c] = h->GetBinContent(i);
      dex[c] = 0.;
      dey[c] = h->GetBinError(i);
      c++;
    }
  }

  return(new TGraphErrors(nc,dvx,dvy,dex,dey));
}



////=============================================================================
//TGraph* InteRatio(const int s,
//                  const int m,
//                  const int p,
//		  const int p0,
//                  bool j = kFALSE,
//                  bool u = kFALSE)
//{
//
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  Double_t dNdEta[nc-1];
//  Double_t dP[nc-1];  IntegralVal(s, m, p,  dNdEta, dP,  j, u);
//  Double_t dP0[nc-1]; IntegralVal(s, m, p0, dNdEta, dP0, j, u);
//  //for(int i = 0; i< nc-1; i++) cout<<dP[i]/dP0[i]<<endl;
//  if(j){
//    Double_t dPaU[nc-1]; IntegralVal(s, m, p, dNdEta, dPaU, kFALSE, kTRUE);
//    Double_t dPiU[nc-1]; IntegralVal(s, m, p0, dNdEta, dPiU, kFALSE, kTRUE);
//    for(int i = 0; i< nc-1; i++){
//      dP[i]  = dP[i] - 0.25*dPaU[i];
//      dP0[i] = dP0[i] - 0.25*dPiU[i];
//    }
//  }
//  Double_t dR[nc-1];
//  TGraph *gR = new TGraph();
//
//  for(Int_t i = 1; i<nc; i++) {
//    dR[i-1] = dP[i-1]/dP0[i-1];
//    gR->SetPoint(i-1, dNdEta[i-1], dR[i-1]);
//    if(p==2 && p0==4) gR->SetPoint(i-1, dNdEta[i-1], 2.*dR[i-1]);
//  }
//  return gR;
//}
//
//_____________________________________________________________________________
TGraphErrors* GetDataE(TString sf = "data/HEPData.root",
		      int t = 36, 
		      TString sGraph = "Graph1D_y1")
{
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list((TDirectoryFile*)file->Get(Form("Table %d", t)));

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list");
    exit(-2);
  }

  auto gD((TGraphErrors*)list->Get(sGraph));
  file->Close();
  return gD;
}

//=============================================================================
TH1D* GetDataC(TString sf = "data/HEPData.root",
               int t = 36,
               TString sHist = "Hist1D_y1",
	       TString sE = "Hist1D_y1_e1")
{
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list((TDirectoryFile*)file->Get(Form("Table %d", t)));

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list");
    exit(-2);
  }

  auto hD((TH1D*)list->Get(sHist));
  auto he((TH1D*)list->Get(sE));

  for(Int_t i = 1; i<= hD->GetNbinsX(); i++) hD->SetBinError(i, he->GetBinContent(i)); 
  //file->Close();

  return hD;

}

////_____________________________________________________________________________
//TH1D* PtSpectrum(const int s,
//                 const int m,
//                 const int p,
//                 bool j = kFALSE,
//                 bool u = kFALSE)
//{
//
//  auto Acc(acc); if(j || u) Acc = 0.75;
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  auto h((TH1D*)list->FindObject(Form("%s_In", sp[p].Data())));
//  if(j){
//    h=(TH1D*)list->FindObject(Form("%s_JC", sp[p].Data()));
//    auto h0=(TH1D*)list->FindObject(Form("%s_PC", sp[p].Data())); h0->Scale(0.25);
//    h->Add(h0, -1.);
//  }
//  if(u) h=(TH1D*)list->FindObject(Form("%s_PC", sp[p].Data()));
//  
//  Double_t bin[]= {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 16.,  20};
//  
//  //Double_t bin[] = {0., 0.6, 1.6, 2.2, 2.8, 3.7, 5, 8, 12., 16., 20.};
//  Int_t nbin=sizeof(bin)/sizeof(Double_t)-1;
//  Double_t jbin[] = {0., 0.6, 1.6, 2.2, 2.8, 3.7, 5, 8, 12., 16., 20.};
//  Int_t njbin=sizeof(jbin)/sizeof(Double_t)-1;
//  
//  TH1D* h2;
//  if(!j && !u) h2 = (TH1D*)h->Rebin(nbin, ("hPt"+ sp[p] + (j ? "_Jet" : "") + (u ? "_UE" : "")).Data(), bin);
//  h2 = (TH1D*)h->Rebin(njbin, ("hPt"+ sp[p] + (j ? "_Jet" : "") + (u ? "_UE" : "")).Data(), jbin);
//  h2->Sumw2();
//  //if(p==1 || p==2 || p==3) h2->Scale(2.);
//  NormBinningHistogram(h2);
//  h2->Scale(1./(Acc*2.));
//  return h2;
//}
//
////_____________________________________________________________________________
//TH1D* PtSpectrum(const int s,
//                 const int m,
//                 const int p,
//                 const int dCentMin,
//                 const int dCentMax,
//                 bool j = kFALSE,
//                 bool u = kFALSE)
//{
//
//  auto Acc(acc); if(j || u) Acc = 0.75;
//  Double_t dNdEta[nc-1];
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//  
//  auto h((TH1D*)list->FindObject(Form("%s_In_%d%d",  sp[p].Data(), dCentMin, dCentMax)));
//  if(j){
//    h=(TH1D*)list->FindObject(Form("%s_JC_%d%d", sp[p].Data(), dCentMin, dCentMax));
//    auto h0=(TH1D*)list->FindObject(Form("%s_PC_%d%d", sp[p].Data(), dCentMin, dCentMax)); h0->Scale(0.25);
//    h->Add(h0, -1.);
//  }
//  if(u) h=(TH1D*)list->FindObject(Form("%s_PC_%d%d", sp[p].Data(), dCentMin, dCentMax));
//
//  Double_t bin[]= {0., 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 16.,  20};
//  Int_t nbin=sizeof(bin)/sizeof(Double_t)-1;
//  Double_t jbin[] = {0., 0.6, 1.6, 2.2, 2.8, 3.7, 5, 8, 12., 16., 20.};
//  Int_t njbin=sizeof(jbin)/sizeof(Double_t)-1;
//  
//  TH1D* h2;
//  if(!j && !u) h2 = (TH1D*)h->Rebin(nbin, ("hPt"+ sp[p] + (j ? "_Jet" : "") + (u ? "_UE" : "")).Data(), bin);
//  h2 = (TH1D*)h->Rebin(njbin, ("hPt"+ sp[p] + (j ? "_Jet" : "") + (u ? "_UE" : "")).Data(), jbin);
//  NormBinningHistogram(h2);
//  h2->Scale(1./(Acc*2.));
//  h2->Sumw2();
//  NormBinningHistogram(h2);
//  return h2;
//}
//
////=============================================================================
//TH1D* PtSpectrum(const int s,
//                 const int m,
//                 const int p,
//                 const Double_t dCentMin,
//                 const Double_t dCentMax,
//                 bool j = kFALSE,
//                 bool u = kFALSE)
//{
//
//  auto Acc(acc); if(j || u) Acc = 0.75;
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  auto h((TH1D*)list->FindObject(Form("%s_In_%.2f%.2f",  sp[p].Data(), dCentMin, dCentMax)));
//  if(j){
//    h=(TH1D*)list->FindObject(Form("%s_JC_%.2f%.2f", sp[p].Data(), dCentMin, dCentMax));
//    auto h0=(TH1D*)list->FindObject(Form("%s_JC_%.2f%.2f", sp[p].Data(), dCentMin, dCentMax)); h0->Scale(0.25);
//    h->Add(h0, -1.);
//  }
//  if(u) h=(TH1D*)list->FindObject(Form("%s_PC_%.2f%.2f", sp[p].Data(), dCentMin, dCentMax));
//
//  Double_t bin[]= {0., 0.3, 0.5, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.6, 2.8, 3.7, 5.0, 8.0, 16., 22.};
//  Int_t nbin=sizeof(bin)/sizeof(Double_t)-1;
//  Double_t jbin[] = {0., 0.6, 1.6, 2.2, 2.8, 3.7,  5, 8, 12., 16., 20.};
//  Int_t njbin=sizeof(jbin)/sizeof(Double_t)-1;
//  TH1D* h2;
//  if(!j && !u) h2 = (TH1D*)h->Rebin(nbin, ("hPt"+ sp[p] + (j ? "_Jet" : "") + (u ? "_UE" : "")).Data(), bin);
//  h2 = (TH1D*)h->Rebin(njbin, ("hPt"+ sp[p] + (j ? "_Jet" : "") + (u ? "_UE" : "")).Data(), jbin);
//  NormBinningHistogram(h2);
//  h2->Scale(1./(Acc*2.));
//  h2->Sumw2();
//  NormBinningHistogram(h2);
//  return h2;
//}
//
////=============================================================================
//TH1D* PartoJet(const int s,
//               const int m,
//               const int p)
//{
//
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  auto h((TH1D*)list->FindObject(Form("%s_dJP", sp[p].Data())));
//  //auto hPC((TH1D*)list->FindObject(Form("%s_PC", sp[p].Data())));
//  //hPC->Scale(1./(4.*0.75*2.*0.06));
//  //auto u = hPC->Integral(1, hPC->GetNbinsX());
//
//  //for(Int_t i = 1; i<=h->GetNbinsX(); i++){
//  //  auto dVal = h->GetBinContent(i); 
//  //  auto dErr = h->GetBinError(i); 
//  //  Double_t dLower = h->GetXaxis()->GetBinLowEdge(i);
//  //  Double_t dUpper = h->GetXaxis()->GetBinUpEdge(i);
//  //  //h->SetBinContent(i, (dVal/(TMath::Pi()*(dUpper*dUpper - dLower*dLower))-u)); 
//  //  //h->SetBinError(i, (dErr/(TMath::Pi()*(dUpper*dUpper - dLower*dLower)))); 
//  //  Double_t dv = dVal-u*TMath::Pi()*(dUpper*dUpper - dLower*dLower);
//  //  if (dv < 0.) dv = 0.;
//  //  h->SetBinContent(i, dv); 
//  //  h->SetBinError(i, dErr); 
//  //} 
//   
//
// return h;
//}
//
//
////=============================================================================
//TH1D* PartoJet(const int s,
//               const int m,
//               const int p,
//	       const int dCentMin,
//               const int dCentMax)
//{
//
//  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get(sp[p])));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  auto h((TH1D*)list->FindObject(Form("%s_dJP_%d%d", sp[p].Data(), dCentMin, dCentMax)));
//
//  h->Rebin(5);
// return h;
//}
////_____________________________________________________________________________
//TH1D* RebinTH1D(TH1D const *hRaw, TH1D const *hRef)
//{
//  if ((!hRaw) || (!hRef)) return 0x0;
//
//  const Int_t nRef = hRef->GetNbinsX();
//
//  const Double_t dLower = hRef->GetXaxis()->GetBinLowEdge(1);
//  const Double_t dUpper = hRef->GetXaxis()->GetBinUpEdge(nRef);
//
//  auto hNew =(TH1D*)hRef->Clone(Form("h_%s_%s", hRaw->GetName(),
//                                           hRef->GetName()));
//  hNew->Reset();
//  //=============================================================================
//
//  for (Int_t k=1; k<=hRaw->GetNbinsX(); k++) {
//    Double_t dXvar = hRaw->GetBinCenter(k);
//    if ((dXvar<dLower) || (dXvar>=dUpper)) continue;
//
//    Int_t iBinX = hNew->FindBin(dXvar);
//    Double_t dYvar = hRaw->GetBinContent(k);
//    Double_t dYerr = hRaw->GetBinError(k);
//    Double_t dYsw2 = hNew->GetBinError(iBinX);
//
//    hNew->SetBinContent(iBinX, hNew->GetBinContent(iBinX) + dYvar);
//    hNew->SetBinError(iBinX, TMath::Sqrt(dYsw2*dYsw2 + dYerr*dYerr));
//  }
//
//  return hNew;
//}
//
