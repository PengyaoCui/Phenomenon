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

const Double_t dCent[] = { 0., 0.95, 4.7, 9.5, 14., 19., 28., 38., 48., 68., 100. };
const auto nc(sizeof(dCent)/sizeof(Double_t));

//_____________________________________________________________________________
TH1D* TrkEta(const int s,
             const int m)
{
  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get("levent")));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::TrkEta", "No list: listevent");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject("hTrkEta"));
  h->Rebin(20);
  NormBinningHistogram(h);

  return h;
}

//=============================================================================
TH1D* dNfwddEta(const int s,
                const int m)
{
  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get("levent")));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::TrkEta", "No list: listevent");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject("hdNfwddEta"));
  h->Rebin(10);

  return h;
}

//=============================================================================
void dNdEtaVal(const int s,
	       const int m,
	       TH1D*h,
	       Double_t dNdEta[nc-1])
{
  auto dndeta = 0.; int k = 0;
  for(int i =1; i<= h->GetNbinsX(); i++){
    if(h->GetBinContent(i) != 0.){
      dNdEta[k] = h->GetBinCenter(i);
      k++;
    }
  }
}

void IntegralVal(const int s,
                 const int m,
                 const int p,
		 Double_t dNdEta[nc-1],
	         Double_t dVal[nc-1],
		 bool j = kFALSE,
		 bool u = kFALSE)
{
  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get(sp[p])));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: list_results");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject(Form("Integral_%s_In", sp[p].Data())));
  if(j) h=(TH1D*)list->FindObject(Form("Integral_%s_JC", sp[p].Data()));
  if(u) h=(TH1D*)list->FindObject(Form("Integral_%s_PC", sp[p].Data()));
  
  dNdEtaVal(s, m, h, dNdEta);
  for(int i = 0; i<nc-1; i++){dVal[i] = h->GetBinContent(h->FindBin(dNdEta[i]));}

  return;

}
//_____________________________________________________________________________
TGraph* InteSpectrum(const int s,
                      const int m,
                      const int p,
		      bool j = kFALSE,
		      bool u = kFALSE)
{

  Double_t dNdEta[nc-1];
  Double_t dPa[nc-1]; IntegralVal(s, m, p, dNdEta, dPa, j, u);
  
  for(int i = 0; i<nc-1; i++){cout<<dPa[i]<<endl; }
 
  auto g = new TGraph();
  for(Int_t i = 0; i<nc-1; i++) g->SetPoint(i, dNdEta[i], dPa[i]);

  return g;
}


#if 0
//=============================================================================
TGraph* RatiotoPi(const int s,
                      const int m,
                      const int p,
		      bool j = kFALSE,
		      bool u = kFALSE)
{
 
  const TString sf(Form("sim/%s/Results_%s_%s.root", ss[s].Data(), ss[s].Data(), sm[m].Data()));
  if (gSystem->AccessPathName(sf)) {
    ::Error("utils::Spectrum", "No file: %s", sf.Data());
    exit(-1);
  }
  auto file(TFile::Open(sf, "read"));
  auto list(static_cast<TList*>(file->Get(sp[p])));
  file->Close();

  if (list==nullptr) {
    ::Error("utils::Spectrum", "No list: list_results");
    exit(-2);
  }

  auto h((TH1D*)list->FindObject(Form("Integral_%s_In", sp[p].Data())));
  if(j) h=(TH1D*)list->FindObject(Form("Integral_%s_JC", sp[p].Data()));
  if(u) h=(TH1D*)list->FindObject(Form("Integral_%s_PC", sp[p].Data()));

  Double_t dNdEta[nc-1];
  Double_t dPa[nc-1];
  Double_t dPi[nc-1];
  dNdEtaVal(s, m, h, dNdEta);

  for(int i = 0; i<nc-1; i++){dPa[i] = h->GetBinContent(h->FindBin(dNdEta[j]));}




  Double_t dPa[nc-1];IntegralSpectrum(s, m, p, dPa);
  Double_t dPi[nc-1];IntegralSpectrum(s, m, 5, dPi);
  Double_t dR[nc-1];
  for(Int_t i = 1; i<nc; i++) { 
    dR[i-1] = dPa[i-1]/dPi[i-1]; 
    gR->SetPoint(i-1, dNdEta[i-1], dR[i-1]);
  }
  return gR;
}
#endif
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

  return hD;

}

//_____________________________________________________________________________
