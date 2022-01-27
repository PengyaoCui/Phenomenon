#include "TAliFigs.h"
#include "TPlotStd.h"
#include "TUtilHisto.h"
#include "TH1D.h"

const TString sp[] = {"Kshort", "Lambda", "Xi", "Omega", "Phi", "Kstar", "Pion", "Kion", "Proton"};
const auto np(sizeof(sp) / sizeof(TString));

////=============================================================================
//const Double_t dIn[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 18. };
//const auto nIn(sizeof(dIn) / sizeof(Double_t) - 1);
//
//const Double_t dJE[] = { 0.6, 1.6, 2.2, 2.8, 3.7, 5., 8., 12., 18. };
//const auto nJE(sizeof(dJE) / sizeof(Double_t) - 1);
//

//const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
//const auto nc(sizeof(dCent)/sizeof(Double_t));
auto dEta = 2.;
//

//_____________________________________________________________________________
//TH2D* FwdMidTrk(const Int_t s,
//		const Int_t m)
//{
//  const TString sf(Form("%s/sim/%s/%s.root", path.Data(), ss[s].Data(), sm[m].Data()));
//  if (gSystem->AccessPathName(sf)) {
//    ::Error("utils::Spectrum", "No file: %s", sf.Data());
//    exit(-1);
//  }
//  auto file(TFile::Open(sf, "read"));
//  auto list(static_cast<TList*>(file->Get("list_results")));
//  file->Close();
//
//  if (list==nullptr) {
//    ::Error("utils::Spectrum", "No list: list_results");
//    exit(-2);
//  }
//
//  auto h((TH2D*)list->FindObject("hFwdVsMid"));
//  return h;
//}
//
//
//TH1D* dNfwddEta(const int s,
//	     const int m)
//{
//  auto h2D = (TH2D*)FwdMidTrk(s, m);
//  auto hf = (TH1D*) h2D->ProjectionY();
//  //hf->Scale(1./6.);//FwdTrk 2<|eta|<5
//  hf->Scale(1./hf->Integral(1, hf->GetNbinsX()));
//  hf->GetXaxis()->SetTitle("dN_{fwd}/d#eta"); 
//  NormBinningHistogram(hf);
//  return hf;
//
//}
////TH1D* dNfwddEta(const int s,
////	     const int m){
////  auto h2D = (TH2D*)FwdMidTrk(s, m);
////  auto hf = (TH1D*) h2D->ProjectionY();
////  auto dAvNfwd = 0.;
////  for(Int_t i = 1; i<=hf->GetNbinsX(); i++){
////    dAvNfwd  += hf->GetBinContent(i)*hf->GetBinCenter(i)/hf->Integral(1, hf->GetNbinsX()); 
////  }
////  //auto hF=(TH1D*)hf->Clone("Nfwd/<Nfwd>");
////  auto hF=new TH1D("Nfwd/<Nfwd>", "", 1000, 0., 100.);
////  for(Int_t i = 1; i<=hf->GetNbinsX(); i++){
////    hF->SetBinContent(hF->FindBin(hf->GetBinCenter(i)/dAvNfwd), hf->GetBinContent(i));
////  }
////  hF->Scale(1./hF->Integral(1, hF->GetNbinsX()));
////  //NormBinningHistogram(hF);
////  //hF->Rebin(5);
////  return hF;
////}
//TH1D* dNmiddEta(const int s,
//	     const int m)
//{
//  auto h2D = (TH2D*)FwdMidTrk(s, m);
//  auto hm = (TH1D*) h2D->ProjectionX();
//  //auto hM = new TH1D("Nmid", "", 1000, 0., 200.); 
//  //for(Int_t i = 1; i<=hm->GetNbinsX(); i++){
//  //  hM->SetBinContent(hM->FindBin(hf->GetBinCenter(i)/2.), hf->GetBinContent(i)); 
//  //}//MidTrk |eta|<0.5
//  hm->Scale(1./hm->Integral(1, hm->GetNbinsX()));
//  hm->Scale(0.5);
//  hm->GetXaxis()->SetTitle("dN_{mid}/d#eta"); 
//  NormBinningHistogram(hm);
//  return hm;
//
//}
////TH1D* dNmiddEta(const int s,
////	     const int m){
////  auto h2D = (TH2D*)FwdMidTrk(s, m);
////  auto hm = (TH1D*) h2D->ProjectionX();
////  auto dAvNmid = 0.;
////  for(Int_t i = 1; i<=hm->GetNbinsX(); i++){
////    dAvNmid  += hm->GetBinContent(i)*hm->GetBinCenter(i)/hm->Integral(1, hm->GetNbinsX()); 
////  }
////  auto hM=new TH1D("Nmid/<Nmid>", "", 1000, 0., 100.);
////  for(Int_t i = 1; i<=hm->GetNbinsX(); i++){
////    hM->SetBinContent(hM->FindBin(hm->GetBinCenter(i)/dAvNmid), hm->GetBinContent(i));
////  }
////  hM->Scale(1./hM->Integral(1, hM->GetNbinsX()));
////  //NormBinningHistogram(hM);
////  //hM->Rebin(5);
////  return hM;
////}
////=============================================================================
//void CentToFwdTrk(const int s,
//                  const int m,
//                  Double_t dFwdTrk[nc])
//{
//  auto h2D = (TH2D*)FwdMidTrk(s, m);
//  auto hf = (TH1D*) h2D->ProjectionY();
//  auto dt = (Double_t)hf->Integral();//number of event
//  Int_t b = hf->GetNbinsX(); dFwdTrk[0]=(Double_t)hf->GetBinCenter(b);
//  for(Int_t i = 1; i<nc; i++){
//    auto da = (Double_t)(dCent[i] - dCent[i-1])*dt/100.;
//    for(Int_t j = b; j>0; j--){
//      if(hf->Integral(j, b) >= da){
//      dFwdTrk[i] = (Double_t)hf->GetBinCenter(j);
//      b = j;
//      break;
//      }
//    }
//  }
//  return;
//}
//
//=============================================================================
void CentToFwdTrk(TH2D* hFwdVsMid,
		  Double_t dCentMin,
                  Double_t dCentMax,
                  Double_t &dMin,
                  Double_t &dMax)
{
  auto h2D = hFwdVsMid;
  auto hf = (TH1D*) h2D->ProjectionY();
  auto dt = (Double_t)hf->Integral();//number of event
  Int_t b = hf->GetNbinsX(); auto c =(Double_t)hf->GetBinCenter(b);

  auto dr = (Double_t)(dCentMin - 0.)*dt/100.;
  auto da = (Double_t)(dCentMax - dCentMin)*dt/100.;
  for(Int_t j = b; j>0; j--){
    if(hf->Integral(j, b) >= dr){
    dMin = (Double_t)hf->GetBinCenter(j);
    b = j;
    break;
    }
  }
  for(Int_t j = b; j>0; j--){
    if(hf->Integral(j, b) >= da){
    dMax = (Double_t)hf->GetBinCenter(j);
    break;
    }
  }
  return;
}

//=============================================================================
void CentTodNdEta(TH2D* hFwdVsMid,
		  Double_t dCentMin,
                  Double_t dCentMax,
                  Double_t &dndeta)
{
  Double_t dMin; Double_t dMax;  CentToFwdTrk(hFwdVsMid, dCentMin, dCentMax, dMin, dMax);

  Int_t bmin; Int_t bmax;
  auto h2D = hFwdVsMid;
  bmax = (Int_t)h2D->GetYaxis()->FindBin(dMin);
  bmin = (Int_t)h2D->GetYaxis()->FindBin(dMax);

  auto hm = (TH1D*)h2D->ProjectionX("hm", bmin, bmax);
  auto ne = (Double_t)hm->Integral();
  auto nt =0.;
  for(Int_t j = 1; j<=hm->GetNbinsX(); j++){
    auto nT= (Double_t)(hm->GetBinCenter(j)*hm->GetBinContent(j));
    nt = nt+nT;
  }
  dndeta = (Double_t)(nt/(ne*dEta));

  return;
}

void CallSumw2(TList *list)
{
  TObject *p(nullptr);
  TIter next(list);
  while ((p = next())) {
    auto h(dynamic_cast<TH1*>(p));
    if (h) h->Sumw2();
  }

  return;
}
//_____________________________________________________________________________
