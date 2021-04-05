#include "TAliFigs.h"
#include "TPlotStd.h"
#include "TUtilHisto.h"
//=============================================================================

const Double_t dIn[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 15. };
const auto nIn(sizeof(dIn) / sizeof(Double_t) - 1);

const Double_t dJE[] = { 0.6, 1.6, 2.2, 2.8, 3.7, 5., 8., 12., 15. };
const auto nJE(sizeof(dJE) / sizeof(Double_t) - 1);

const TString ss[] { "pp13TeV", "pp7TeV" };
const auto ns(sizeof(ss)/sizeof(TString));

const TString sm[] { "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope", "HardQCD_CR", "HardQCD_Rope", "HardQCD_CRandRope" };
const auto nm(sizeof(sm) / sizeof(TString));

const TString sp[] = {"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"};
const auto np(sizeof(sp) / sizeof(TString));

//const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
const Double_t dCent[] = { 0., 100. };
const auto nc(sizeof(dCent)/sizeof(Double_t));
auto dEta = 1.;

//=============================================================================

//_____________________________________________________________________________
TH2D* FwdMidTrk(const int s,
		const int m)
{
  const TString sf(Form("sim/%s/%s.root", ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get("list_results")));
  file->Close();
  
  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: list_results");
    exit(-2);
  }
  
  auto h((TH2D*)list->FindObject("hFwdVsMid"));
  return h;
}

//_____________________________________________________________________________
void CentToFwdTrk(const int s,
		  const int m,
		  Double_t dFwdTrk[nc])
{
  auto h2D = (TH2D*)FwdMidTrk(s, m);
  auto hf = (TH1D*) h2D->ProjectionY();
  auto dt = (Double_t)hf->Integral();//number of event
  Int_t b = hf->GetNbinsX(); dFwdTrk[0]=(Double_t)hf->GetBinCenter(b);
  for(Int_t i = 1; i<nc; i++){
    auto da = (Double_t)(dCent[i] - dCent[i-1])*dt/100.;
    for(Int_t j = b; j>0; j--){
      if(hf->Integral(j, b) >= da){
      dFwdTrk[i] = (Double_t)hf->GetBinCenter(j);
      b = j;
      break;
      }
    } 
  }
  return;
}		

//_____________________________________________________________________________
void CentTodNdEta(const int s,
		  const int m,
	          Double_t dNdEta[nc-1])
{
  Double_t dFwdTrk[nc];
  CentToFwdTrk(s, m, dFwdTrk);
  
  Int_t b[nc];
  auto h2D = (TH2D*)FwdMidTrk(s, m);
  for(Int_t i = 0; i< nc; i++){ b[i] = (Int_t)h2D->GetYaxis()->FindBin(dFwdTrk[i]); }
  for(Int_t i = 1; i< nc; i++){
    auto hm = (TH1D*)h2D->ProjectionX(Form("hm_%d", i), b[i], b[i-1]);
    auto ne = (Double_t)hm->Integral();
    auto nt =0.;
    for(Int_t j = 1; j<=hm->GetNbinsX(); j++){ 
      auto nT= (Double_t)(hm->GetBinCenter(j)*hm->GetBinContent(j));
      nt = nt+nT;
    }
    dNdEta[i-1] = (Double_t)(nt/(ne*dEta)); 
  }

  return;
}

//_____________________________________________________________________________
TH1D* TrkEta(const int s,
            const int m)
{

  const TString sf(Form("sim/%s/%s.root", ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get("list_results")));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: list_results");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject("hTrEta"));
  h->Scale(1./(h->GetEntries()));
  h->Rebin(20); 

  return h;
}

//_____________________________________________________________________________
void IntegralSpectrum(const int s,
		      const int m,
		      const int p,
		      Double_t nP[nc-1])
{
  Double_t dFwdTrk[nc];  CentToFwdTrk(s, m, dFwdTrk);
  Double_t dNdEta[nc-1]; CentTodNdEta(s, m, dNdEta);
  
  const TString sf(Form("sim/%s/%s.root", ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get("list_results")));
  file->Close();
  
  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: list_results");
    exit(-2);
  }
  
  const auto hN((THnSparseD*)list->FindObject("hInclN"));
  TH1D* h1[nc-1];

  for(Int_t ft = 1; ft<nc; ft++){
    auto h = (THnSparseD*)hN->Clone(("hN"+ sp[p] + "_" + dNdEta[ft-1]).Data());
    auto bp = (Int_t)h->GetAxis(0)->FindBin(p+1);
    h->GetAxis(0)->SetRange(bp, bp);
    auto bfmin = (Int_t)h->GetAxis(1)->FindBin(dFwdTrk[ft]); 
    auto bfmax = (Int_t)h->GetAxis(1)->FindBin(dFwdTrk[ft-1]);
    h->GetAxis(1)->SetRange(bfmin, bfmax);
    h1[ft-1] = (TH1D*)h->Projection(0); h1[ft-1]->SetName(("h"+ sp[p] + "_" + dNdEta[ft-1]).Data());
    nP[ft-1] = h1[ft-1]->Integral();
    //if(p == 0) nP[ft-1]= 2*nP[ft-1];
  }

  return; 
}

//_____________________________________________________________________________
TH1D* PtSpectrum(const int s,
                 const int m,
                 const int p)
{
  Double_t dFwdTrk[nc];  CentToFwdTrk(s, m, dFwdTrk);
  Double_t dNdEta[nc-1]; CentTodNdEta(s, m, dNdEta);

  const TString sf(Form("sim/%s/%s.root", ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get("list_results")));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: list_results");
    exit(-2);
  }

  const auto hN((THnSparseD*)list->FindObject("hInclN"));
  TH1D* h1;

  auto h = (THnSparseD*)hN->Clone(("hN"+ sp[p]).Data());
  auto bp = (Int_t)h->GetAxis(0)->FindBin(p+1);
  h->GetAxis(0)->SetRange(bp, bp);
  h1 = (TH1D*)h->Projection(3); h1->SetName(("hPt"+ sp[p]).Data());
  return h1;
}

//_____________________________________________________________________________
TGraph* RatioToPi(const int s,
		  const int m,
                  const int p)
{
  Double_t dNdEta[nc-1]; CentTodNdEta(s, m, dNdEta);
  auto gR = new TGraph();
  
  Double_t dPa[nc-1];IntegralSpectrum(s, m, p, dPa);
  Double_t dPi[nc-1];IntegralSpectrum(s, m, 5, dPi);
  Double_t dR[nc-1];
  for(Int_t i = 1; i<nc; i++) { 
    dR[i-1] = dPa[i-1]/dPi[i-1]; 
    gR->SetPoint(i-1, dNdEta[i-1], dR[i-1]);
  }
  return gR;
}

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

//_____________________________________________________________________________
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

  return hD;

}

//_____________________________________________________________________________
