#ifndef ROOT_PY_FJ_UTILS_H
#define ROOT_PY_FJ_UTILS_H

#include "PyParticle.h"
#include <cassert>

#include "TSystem.h"
#include "TDatime.h"
#include "TStopwatch.h"

#include "TMath.h"
#include "TVector3.h"
#include "TString.h"

#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "TList.h"

#include "TH1D.h"
#include "TH2D.h"
#include "THnSparse.h"
#include "TProfile.h"

#include "Pythia8/Pythia.h"
#include "Pythia8/ColourReconnection.h"

#include "Pythia8Plugins/FastJet3.h"
#include "Pythia8Plugins/ColourReconnectionHooks.h"

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/ClusterSequenceArea.hh"

//#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
//#include "fastjet/tools/Subtractor.hh"
//#include "fastjet/tools/Filter.hh"
//=============================================================================

//const TString gksStrgs[] = { "Kshort", "Lambda", "AntiLa", "LambdaFd", "AntiLaFd", "XiNeg", "XiPos", "OmegaNeg", "OmegaPos" };
//enum struct EStrg : unsigned int { Kshort=0, Lambda, AntiLa, LambdaFd, AntiLaFd, XiNeg, XiPos, OmegaNeg, OmegaPos, Undef };
const TString gksStrgs[] = {"Kshort", "Lambda", "Xi", "Omega", "Phi", "Pion", "Kion", "Proton"};
enum struct EStrg : unsigned int {  Kshort=0, Lambda, Xi, Omega, Phi, Pion, Kion, Proton, Undef };
TString StrgName(EStrg e)
{
  if (e==EStrg::Undef) return TString("");
  return gksStrgs[static_cast<unsigned int>(e)];
}

//=============================================================================

//const TString gksJets[] = { "Jet08", "Jet09", "Jet10", "Jet11", "Jet12", "Jet15", "Jet18", "Jet20", "Jet22" };
const TString gksJets[] = { "Jet10"};

float JetVal(TString s)
{
  s.ReplaceAll("Jet", "");
  return s.Atof();
}
//=============================================================================

//const TString gksStrgJCs[] = { "C02", "C03", "C04" };
const TString gksStrgJCs[] = { "C04" };
const auto gknStrgJCs(sizeof(gksStrgJCs) / sizeof(TString));

//const TString gksStrgOCs[] = { "C04", "C06", "C08" };
const TString gksStrgOCs[] = { "C06" };
const auto gknOCs(sizeof(gksStrgOCs) / sizeof(TString));


float StrgJC(TString s)
{
  s.ReplaceAll("C", "");
  return s.Atof() / 10.;
}
//=============================================================================

class StrgInfo : public fastjet::PseudoJet::UserInfoBase {

 public :

  StrgInfo() = default;
  StrgInfo(EStrg e) : UserInfoBase(), fType(e) { }

  StrgInfo(const StrgInfo &src) : UserInfoBase(src), fType(src.fType) { }

  StrgInfo &operator=(const StrgInfo &src) {
    if(&src==this) return *this;

    fType = src.fType;
    return *this;
  }
//=============================================================================

  EStrg GetType() const { return fType; }
//=============================================================================

 private :

  EStrg fType = EStrg::Undef;
};

//_____________________________________________________________________________
int RandomSeed()
{
  TDatime adt;
  if (!gSystem) new TSystem();
  const auto kTime((UInt_t)adt.Get());
  const auto kProc((UInt_t)gSystem->GetPid());

  const auto kInit(kTime - kProc);
  return ((int)kInit - (int)(((int)(kInit/1e8))*1e8));
}

//=============================================================================
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

#endif
