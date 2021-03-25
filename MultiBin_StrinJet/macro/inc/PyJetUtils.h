#include "TAliFigs.h"
#include "TPlotStd.h"
#include "TUtilHisto.h"
//=============================================================================

const Double_t dIn[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12., 15. };
const auto nIn(sizeof(dIn) / sizeof(Double_t) - 1);

const Double_t dJE[] = { 0.6, 1.6, 2.2, 2.8, 3.7, 5., 8., 12., 15. };
const auto nJE(sizeof(dJE) / sizeof(Double_t) - 1);

const TString sm[] { "SoftQCD_CR", "SoftQCD_Rope", "SoftQCD_CRandRope", "HardQCD_CR", "HardQCD_Rope", "HardQCD_CRandRope" };
const auto nm(sizeof(sm) / sizeof(TString));

const Double_t dCent[] = { 0., 0.01, 0.1, 0.4,  1. };
const auto nc(sizeof(dCent)/sizeof(Double_t));
Double_t dFwdTrk[nc];


//=============================================================================

//_____________________________________________________________________________
TH2D* FwdMidTrk(const int m)
{
  const TString sf(Form("sim/%s.root", sm[m].Data()));
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
TH1D* Cent(const int m)
{
  auto h2D = (TH2D*)FwdMidTrk(m);
  auto hf = (TH1D*) h2D->ProjectionY();
  auto dt = (Double_t)hf->Integral();//number of event
  Int_t b = hf->GetNbinsX(); dFwdTrk[0]=(Double_t)hf->GetBinCenter(b);
  for(Int_t i = 1; i<nc; i++){
    auto da = (Double_t)(dCent[i] - dCent[i-1])*dt;
    cout<<"==dArea=="<<da<<endl; 

    for(Int_t j = b; j>0; j--){
      if(hf->Integral(j, b) >= da){
      dFwdTrk[i] = (Double_t)hf->GetBinCenter(j);
      b = j;
      break;
      }
    } 

  }
  
  for(Int_t i = 0; i< nc; i++)cout<<"dFwdTrk=="<<dFwdTrk[i]<<endl;
  return hf;
}		

//_____________________________________________________________________________
TH1D *Spectrum(const int m,
               const TString sd,
               const TString ss,
               const TString sj = "Jet10",
               const TString st = "",
               const TString sb = "")
{
  const TString sf(Form("data/PySjets/PySjets_%s/AnalysisOutputs_%s.root",sd.Data(),sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }

  auto file(TFile::Open(sf));
  const TString sl(Form("list_%s_%s",ss.Data(),sj.Data()));
  auto list(static_cast<TList*>(file->Get(sl)));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: %s", sl.Data());
    exit(-2);
  }
//=============================================================================

  const auto b(st.IsNull());
  auto hf(static_cast<TH1D*>(list->FindObject(("h" + ss + (b ? st : ("_" + st))).Data())));

  if (!(st.IsNull() || sb.IsNull())) {
    auto hf(static_cast<TH1D*>(list->FindObject(("h" + ss + "_" + sb).Data())));
    hf->SetName(Form("%s_%s",hf->GetName(),sb.Data()));
    hf->Add(hf, -1.);
  }
//=============================================================================

  auto hr(static_cast<TH1D*>(hf->Rebin((b ? nIn : nJE), Form("%s_RB",hf->GetName()), (b ? dIn : dJE))));
  NormBinningHistogram(hr);
//=============================================================================

  delete list;
  list = nullptr;
//=============================================================================

  return hr;
}

//_____________________________________________________________________________
TH1D *RatioLK(const int m,
              const TString sd,
              const TString sj = "Jet10",
              const TString st = "",
              const TString sb = "")
{
  auto hK(Spectrum(m, sd, "Kshort", sj, st, sb));
  auto hL(Spectrum(m, sd, "Lambda", sj, st, sb));
//=============================================================================

  const TString sh("hRatioV" + sm[m] + sj + (st.IsNull() ? st : ("_" + st)) + (sb.IsNull() ? sb : ("_" + sb)));
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}

