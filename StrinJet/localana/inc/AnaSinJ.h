#include "TAliFigs.h"
#include "TPlotStd.h"
#include "TUtilHisto.h"
#include "TH1D.h"

const TString path("/home/cuipengyao/PythiaOutput");
//=============================================================================
const Double_t dIn[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 18. };
const auto nIn(sizeof(dIn) / sizeof(Double_t) - 1);

const Double_t dJE[] = { 0.6, 1.6, 2.2, 2.8, 3.7, 5., 8., 12., 18. };
const auto nJE(sizeof(dJE) / sizeof(Double_t) - 1);


const TString ss[] { "pp13TeV", "pp7TeV" };
const auto ns(sizeof(ss)/sizeof(TString));

const TString sm[] { "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope", "HardQCD_CR", "HardQCD_Rope", "HardQCD_CRandRope" };
const auto nm(sizeof(sm) / sizeof(TString));

const TString sp[] = {"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"};
const auto np(sizeof(sp) / sizeof(TString));

const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
const auto nc(sizeof(dCent)/sizeof(Double_t));
auto dEta = 1.;

Int_t nEvent(const Int_t s,
             const Int_t m)
{
  const TString sf(Form("%s/sim/%s/%s.root", path.Data(), ss[s].Data(), sm[m].Data()));
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

  auto h((TH2D*)list->FindObject("hPtHat"));
  auto n((Int_t)h->GetEntries()); 
  return n;

}

//_____________________________________________________________________________
TH2D* FwdMidTrk(const Int_t s,
		const Int_t m)
{
  const TString sf(Form("%s/sim/%s/%s.root", path.Data(), ss[s].Data(), sm[m].Data()));
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

//=============================================================================
TH1D* FwdTrk(const Int_t s,
             const Int_t m){

    auto h((TH1D*)FwdMidTrk(s, m)->ProjectionY());
    return h;
}


//_____________________________________________________________________________
TH1D* TrkEta(const int s,
             const int m)
{

  const TString sf(Form("%s/sim/%s/%s.root", path.Data(), ss[s].Data(), sm[m].Data()));
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
  h->Scale(1./(nEvent(s, m)));

  return h;
}

TH1D* dNfwddEta(const int s,
	     const int m)
{
  auto h2D = (TH2D*)FwdMidTrk(s, m);
  auto hf = (TH1D*) h2D->ProjectionY();
  hf->Scale(1./6.);//FwdTrk 2<|eta|<5
  hf->Scale(1./hf->Integral(1, hf->GetNbinsX()));
  hf->GetXaxis()->SetTitle("dN_{fwd}/d#eta"); 
  return hf;

}
//=============================================================================
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

//=============================================================================
void CentToFwdTrk(const int s,
                  const int m,
                  Double_t dCentMin,
                  Double_t dCentMax,
                  Double_t &dMin,
                  Double_t &dMax)
{
  auto h2D = (TH2D*)FwdMidTrk(s, m);
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

//=============================================================================
void CentTodNdEta(const int s,
                  const int m,
                  Double_t dCentMin,
                  Double_t dCentMax,
                  Double_t &dndeta)
{
  Double_t dMin; Double_t dMax;  CentToFwdTrk(s, m, dCentMin, dCentMax, dMin, dMax);

  Int_t bmin; Int_t bmax;
  auto h2D = (TH2D*)FwdMidTrk(s, m);
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



//_____________________________________________________________________________
TChain* CreateChain(const TString sDataset){
  if  (sDataset.IsNull()) return 0;
  if (!sDataset.EndsWith(".txt")) return 0;
  TString dataFile;
  TChain *chain = new TChain("particle");
  ifstream dataList(sDataset.Data(), ios::in);//input file stream
  while (!dataList.eof()) {
    dataFile.ReadLine(dataList,kTRUE);
    if (!dataFile.EndsWith(".root")) continue;
    if (!gSystem->AccessPathName(dataFile.Data())) chain->Add(dataFile.Data());
  } dataList.close();

  return chain;
}

//=============================================================================
TChain* CreateChain(const Int_t s,
                    const Int_t m)
{
  const TString sf(Form("%s/sim/%s/%s.root", path.Data(), ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  
  TChain *chain = new TChain("particle");
  chain->Add(sf);
  return chain;
}
//_____________________________________________________________________________


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
