#include "utils.h"
//=============================================================================
const auto bsQCD(kTRUE);
const auto bCR(kTRUE);
const auto bRope(kFALSE);
const auto bhQCD = !bsQCD;

int main(int argc, char *argv[])
{
  assert(argc>0);
//=============================================================================

  TString sf(__FILE__);
  sf.ReplaceAll(".C", "");
  const TString gksp(Form("%s::%s",sf.Data(),__FUNCTION__));
  for (auto i=0; i<argc; ++i) ::Info(gksp.Data(), "argv[%d] = %s", i, argv[i]);
//=============================================================================

  const auto dJetR(TString(argv[1]).Atof());
  ::Info(gksp.Data(), "Jet radius = %f", dJetR);

  const auto dEtaShift(TString(argv[2]).Atof());
  ::Info(gksp.Data(), "Rapidity shift = %f", dEtaShift);

  const auto kClusID(TString(argv[3]).Atoi());
  const auto kProcID(TString(argv[4]).Atoi());
  ::Info(gksp.Data(), "Cluster ID = %d", kClusID);
  ::Info(gksp.Data(), "Process ID = %d", kProcID);

  const auto kSeed(RandomSeed());
  ::Info(gksp.Data(), "Random seed = %d", kSeed);
//=============================================================================

//TApplication app(gksp.Data(), &argc, argv);
//=============================================================================

  Pythia8::Pythia pythia;
  auto &pyReco(pythia.event);
  auto &pyInfo(pythia.info);

  //pythia.readFile(Form("%s.cmnd",sf.Data()));

//=============================================================================
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 2212");
  if(!bCR && !bRope){
    pythia.readString("Tune:pp = 14");//Monash 2013 tune
  }
  //pythia.readString("Main:numberOfEvents = 100001");
  pythia.readString("Main:numberOfEvents = 10001");
  pythia.readString("Beams:eCM = 7000.");
  if(bsQCD){ 
	  //pythia.readString("SoftQCD:all = on");
          pythia.readString("SoftQCD:nonDiffractive = on");//NSD 
  }
  if(bhQCD){ pythia.readString("HardQCD:all = on"); pythia.readString("PhaseSpace:pTHatMin = 20."); }
 
  if(bCR){ 
    pythia.readString("MultiPartonInteractions:pT0Ref = 2.15");
    pythia.readString("BeamRemnants:remnantMode = 1");
    pythia.readString("BeamRemnants:saturation = 5");
    pythia.readString("ColourReconnection:reconnect = on");
    pythia.readString("ColourReconnection:mode = 1");
    pythia.readString("ColourReconnection:allowDoubleJunRem = off");
    pythia.readString("ColourReconnection:m0 = 0.3");
    pythia.readString("ColourReconnection:allowJunctions = on");
    pythia.readString("ColourReconnection:junctionCorrection = 1.2");
    pythia.readString("ColourReconnection:timeDilationMode = 2");
    pythia.readString("ColourReconnection:timeDilationPar = 0.18");
  }
  if(bRope){
    pythia.readString("Ropewalk:RopeHadronization = on");
    pythia.readString("Ropewalk:doShoving = on");
    pythia.readString("Ropewalk:tInit = 1.5");// # Propagation time
    pythia.readString("Ropewalk:deltat = 0.05");
    pythia.readString("Ropewalk:tShove = 0.1");
    pythia.readString("Ropewalk:gAmplitude = 0."); //# Set shoving strength to 0 explicitly
    
    pythia.readString("Ropewalk:doFlavour = on");
    pythia.readString("Ropewalk:r0 = 0.5");
    pythia.readString("Ropewalk:m0 = 0.2");
    pythia.readString("Ropewalk:beta = 0.1");
    
    // Enabling setting of vertex information.
    pythia.readString("PartonVertex:setVertex = on");
    pythia.readString("PartonVertex:protonRadius = 0.7");
    pythia.readString("PartonVertex:emissionWidth = 0.1");
  }
//=============================================================================

  pythia.readString("Next:numberShowInfo = 0");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");

  pythia.readString("ParticleDecays:limitTau0 = on");
  pythia.readString("ParticleDecays:tau0Max = 10");
  
  pythia.readString("310:mayDecay = off");// \KShort will not decay
  pythia.readString("313:mayDecay = off");// \K* will not decay
  pythia.readString("3122:mayDecay = off");// \Lambda will not decay
  pythia.readString("3312:mayDecay = off");// \Xi will not decay
  pythia.readString("3334:mayDecay = off");// \Omega will not decay
  pythia.readString("333:mayDecay = off");// \Phi will not decay
  pythia.readString("211:mayDecay = off");// \Pi charge will not decay
  pythia.readString("321:mayDecay = off");// \KCharge will not decay
  pythia.readString("2212:mayDecay = off");// \Proton will not decay

  pythia.readString("Random:setSeed = on");
  pythia.readString(Form("Random:seed = %d", kSeed - kClusID + 9*kProcID));

  pythia.init();
//=============================================================================
  //cuts
  const auto dTrkPtCut(0.15);
  const auto dfEtaMin(2.);//forward rapidity eta min
  const auto dfEtaMax(5.);//forward rapidity eta max
  const auto dcEtaCut(1.);

  const auto dJetPtMin(1.00);
  const auto dJetEtaMin(-0.35 + dEtaShift);
  const auto dJetEtaMax( 0.35 + dEtaShift);
  const auto dJetAreaMin(0.6 * TMath::Pi() * dJetR *dJetR);

  const auto dConstiPtMin(0.15);
  const auto dConstiEtaMin(-0.90 + dEtaShift);
  const auto dConstiEtaMax( 0.90 + dEtaShift);

  const auto dStrgEtaMin(-0.75 + dEtaShift);
  const auto dStrgEtaMax( 0.75 + dEtaShift);

  const fastjet::GhostedAreaSpec aGhostSpec(1.5);
  const fastjet::AreaDefinition  aAreaDef(fastjet::active_area, aGhostSpec);
  const fastjet::JetDefinition   aJetDef(fastjet::antikt_algorithm, dJetR, fastjet::BIpt_scheme, fastjet::Best);

  const auto aSelEta(fastjet::SelectorEtaRange(dJetEtaMin,dJetEtaMax));

  TVector3 vec_tmp;
  std::vector<fastjet::PseudoJet> vConstis, vStrgs;
  std::vector<int> iTrIndex;;
  std::vector<TVector3> vTrArray;
//=============================================================================

  auto file(TFile::Open(Form("AnalysisResults_%d_%d.root",kClusID,kProcID),"NEW"));
  //auto file(TFile::Open(Form("AnalysisResults_%d_%d_%d.root",kSeed,kClusID,kProcID),"NEW"));

  auto list_pyxsect(new TList());
  auto hTrials(new TH1D("hTrials",     "", 1, 0., 1.));
  list_pyxsect->Add(hTrials);

  auto hXsect (new TProfile("hXsect",  "", 1, 0., 1.));
  list_pyxsect->Add(hXsect);
  CallSumw2(list_pyxsect);
//=============================================================================

  auto list_results(new TList());
  auto list_I(new TList());
  auto list_J(new TList());
  auto list_P(new TList());

  auto hPtHat(new TH2D("hPtHat", "", 1000, 0., 1000., 500, -0.5, 499.5));
  list_results->Add(hPtHat);

  auto hJet(new TH1D("hJet", "", 500, 0., 500.));
  list_results->Add(hJet);
  
  auto hJetEta(new TH1D("hJetEta", "", 1000, -5., 5.));
  list_results->Add(hJetEta);
  
  auto hJEvent(new TH1D("hJEvent", "", 10, 0., 10.));
  list_results->Add(hJEvent);
  
  auto hjet(new TH1D("hjet", "", 500, 0., 500.));
  list_results->Add(hjet);
  
  auto hjetEta(new TH1D("hjetEta", "", 1000, -5., 5.));
  list_results->Add(hjetEta);

  auto hConsti(new TH1D("hConsti", "", 1000, 0., 100.));
  list_results->Add(hConsti);

  auto hFwdVsMid(new TH2D("hFwdVsMid", ";N_{trk}^{Mid}; N_{trk}^{Fwd}", 500, -0.5, 499.5, 500, -0.5, 499.5));
  list_results->Add(hFwdVsMid);
  
  auto hJFwdVsMid(new TH2D("hJFwdVsMid", ";JN_{trk}^{Mid}; JN_{trk}^{Fwd}", 500, -0.5, 499.5, 500, -0.5, 499.5));
  list_results->Add(hJFwdVsMid);
  
  auto hParPtEta(new TH2D("hParPtEta", ";Pt; Eta", 200, 0., 20., 100., -5., 5.));
  list_results->Add(hParPtEta);
  
//-----------------------------------------------------------------------------
  TH1D *hTrPt  = new TH1D("hTrPt", ";p_{T}; N_{trig}", 200, 0, 20.);
  list_results->Add(hTrPt);

  TH1D *hTrEta     = new TH1D("hTrEta", ";#eta; N_{trig}", 1000, -5., 5.);
  list_results->Add(hTrEta);

  TH2D *hTrkPtEta  = new TH2D("hTrkPtEta", "Eta vs p_{T}; p_{T} [GeV]; Eta", 200, 0., 20., 1000, -5., 5.);
  list_results->Add(hTrkPtEta);

//-----------------------------------------------------------------------------
  TH1D *hFwdTrPt  = new TH1D("hFwdTrPt", ";p_{T}; N_{trig}", 200, 0, 20.);
  list_results->Add(hFwdTrPt);

  TH1D *hFwdTrEta     = new TH1D("hFwdTrEta", ";#eta; N_{trig}", 1000, -5., 5.);
  list_results->Add(hFwdTrEta);
//-----------------------------------------------------------------------------
  TH1D *hMidTrPt  = new TH1D("hMidTrPt", ";p_{T}; N_{trig}", 200, 0, 20.);
  list_results->Add(hMidTrPt);

  TH1D *hMidTrEta     = new TH1D("hMidTrEta", ";#eta; N_{trig}", 1000, -5., 5.);
  list_results->Add(hMidTrEta);
  
//-----------------------------------------------------------------------------
  TH1D *hKshortFwd  = new TH1D("hKshortFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hKshortFwd);
  
  TH1D *hLambdaFwd  = new TH1D("hLambdaFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hLambdaFwd);
  
  TH1D *hXiFwd  = new TH1D("hXiFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hXiFwd);

  TH1D *hOmegaFwd  = new TH1D("hOmegaFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hOmegaFwd);
  
  TH1D *hPhiFwd  = new TH1D("hPhiFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hPhiFwd);
  
  TH1D *hKstarFwd  = new TH1D("hKstarFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hKstarFwd);
  
  TH1D *hPionFwd  = new TH1D("hPionFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hPionFwd);
  
  TH1D *hKionFwd  = new TH1D("hKionFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hKionFwd);
  
  TH1D *hProtonFwd  = new TH1D("hProtonFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_I->Add(hProtonFwd);

  TH2D *hKshortPtFwd  = new TH2D("hKshortPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hKshortPtFwd);
  
  TH2D *hLambdaPtFwd  = new TH2D("hLambdaPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hLambdaPtFwd);

  TH2D *hXiPtFwd  = new TH2D("hXiPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hXiPtFwd);
  
  TH2D *hOmegaPtFwd  = new TH2D("hOmegaPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hOmegaPtFwd);
  
  TH2D *hPhiPtFwd  = new TH2D("hPhiPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hPhiPtFwd);
  
  TH2D *hKstarPtFwd  = new TH2D("hKstarPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hKstarPtFwd);
  
  TH2D *hPionPtFwd  = new TH2D("hPionPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hPionPtFwd);
  
  TH2D *hKionPtFwd  = new TH2D("hKionPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hKionPtFwd);
  
  TH2D *hProtonPtFwd  = new TH2D("hProtonPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_I->Add(hProtonPtFwd);
//============================== 
  TH1D *hJCKshortFwd  = new TH1D("hJCKshortFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCKshortFwd);

  TH1D *hJCLambdaFwd  = new TH1D("hJCLambdaFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCLambdaFwd);

  TH1D *hJCXiFwd  = new TH1D("hJCXiFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCXiFwd);

  TH1D *hJCOmegaFwd  = new TH1D("hJCOmegaFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCOmegaFwd);
  
  TH1D *hJCPhiFwd  = new TH1D("hJCPhiFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCPhiFwd);

  TH1D *hJCKstarFwd  = new TH1D("hJCKstarFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCKstarFwd);

  TH1D *hJCPionFwd  = new TH1D("hJCPionFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCPionFwd);

  TH1D *hJCKionFwd  = new TH1D("hJCKionFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCKionFwd);

  TH1D *hJCProtonFwd  = new TH1D("hJCProtonFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_J->Add(hJCProtonFwd);
  
  TH2D *hJCKshortPtFwd  = new TH2D("hJCKshortPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCKshortPtFwd);

  TH2D *hJCLambdaPtFwd  = new TH2D("hJCLambdaPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCLambdaPtFwd);

  TH2D *hJCXiPtFwd  = new TH2D("hJCXiPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5); 
  list_J->Add(hJCXiPtFwd);

  TH2D *hJCOmegaPtFwd  = new TH2D("hJCOmegaPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCOmegaPtFwd);

  TH2D *hJCPhiPtFwd  = new TH2D("hJCPhiPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCPhiPtFwd);

  TH2D *hJCKstarPtFwd  = new TH2D("hJCKstarPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCKstarPtFwd);

  TH2D *hJCPionPtFwd  = new TH2D("hJCPionPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCPionPtFwd);

  TH2D *hJCKionPtFwd  = new TH2D("hJCKionPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCKionPtFwd);

  TH2D *hJCProtonPtFwd  = new TH2D("hJCProtonPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_J->Add(hJCProtonPtFwd);
  
  TH1D *hKshortPJ = new TH1D("hKshortPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hKshortPJ);
  
  TH1D *hLambdaPJ = new TH1D("hLambdaPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hLambdaPJ);

  TH1D *hXiPJ = new TH1D("hXiPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hXiPJ);
  
  TH1D *hOmegaPJ = new TH1D("hOmegaPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hOmegaPJ);
  
  TH1D *hPhiPJ = new TH1D("hPhiPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hPhiPJ);
  
  TH1D *hKstarPJ = new TH1D("hKstarPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hKstarPJ);
  
  TH1D *hPionPJ = new TH1D("hPionPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hPionPJ);
  
  TH1D *hKionPJ = new TH1D("hKionPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hKionPJ);
  
  TH1D *hProtonPJ = new TH1D("hProtonPJ", "PJ", 250, 0., 2.5);
  list_J->Add(hProtonPJ);
//============================== 
  TH1D *hPCKshortFwd  = new TH1D("hPCKshortFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCKshortFwd);

  TH1D *hPCLambdaFwd  = new TH1D("hPCLambdaFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCLambdaFwd);

  TH1D *hPCXiFwd  = new TH1D("hPCXiFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCXiFwd);

  TH1D *hPCOmegaFwd  = new TH1D("hPCOmegaFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCOmegaFwd);
  
  TH1D *hPCPhiFwd  = new TH1D("hPCPhiFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCPhiFwd);

  TH1D *hPCKstarFwd  = new TH1D("hPCKstarFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCKstarFwd);

  TH1D *hPCPionFwd  = new TH1D("hPCPionFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCPionFwd);

  TH1D *hPCKionFwd  = new TH1D("hPCKionFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCKionFwd);

  TH1D *hPCProtonFwd  = new TH1D("hPCProtonFwd", "N_{Fwd}", 500, -0.5, 499.5);
  list_P->Add(hPCProtonFwd);

  TH2D *hPCKshortPtFwd  = new TH2D("hPCKshortPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCKshortPtFwd);

  TH2D *hPCLambdaPtFwd  = new TH2D("hPCLambdaPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCLambdaPtFwd);

  TH2D *hPCXiPtFwd  = new TH2D("hPCXiPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCXiPtFwd);

  TH2D *hPCOmegaPtFwd  = new TH2D("hPCOmegaPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCOmegaPtFwd);

  TH2D *hPCPhiPtFwd  = new TH2D("hPCPhiPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCPhiPtFwd);

  TH2D *hPCKstarPtFwd  = new TH2D("hPCKstarPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCKstarPtFwd);

  TH2D *hPCPionPtFwd  = new TH2D("hPCPionPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCPionPtFwd);

  TH2D *hPCKionPtFwd  = new TH2D("hPCKionPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCKionPtFwd);

  TH2D *hPCProtonPtFwd  = new TH2D("hPCProtonPtFwd", "N_{Fwd} vs p_{T}; p_{T} [GeV]; N_{Fwd}", 200, 0., 20., 500, -0.5, 499.5);
  list_P->Add(hPCProtonPtFwd);

//============================== 
 
  TProfile *hProfAcc = new TProfile("hProfAcc", "", 4, -0.5, 3.5); list_results->Add(hProfAcc);

//=============================================================================
  
  CallSumw2(list_results);
  CallSumw2(list_I);
  CallSumw2(list_J);
  CallSumw2(list_P);
//=============================================================================

  TObject *p(nullptr);
  TIter next(list_results);
  while ((p = next())) {
    auto h(dynamic_cast<TH1*>(p));
    if (h) h->Sumw2();
  }
//=============================================================================

  TStopwatch timer; timer.Start();
  for (auto iEvent=0; iEvent<pythia.mode("Main:numberOfEvents"); ++iEvent) if (pythia.next()) {
    vConstis.resize(0);
    vStrgs.resize(0);
    auto dFwdCh(0.);
    auto dMidCh(0.);
    for (auto i=0; i<pyReco.size(); i++) if (pyReco[i].isFinal()   &&
                                             pyReco[i].isVisible() &&
                                           //pyReco[i].isCharged() &&
                                            (pyReco[i].pT()>dTrkPtCut)) {
      const auto &ap(pyReco[i]);
      Double_t dEtaAbs = TMath::Abs(ap.eta());
      if( ap.isCharged() ){
        iTrIndex.push_back(i);
        vec_tmp.SetXYZ(ap.px(), ap.py(), ap.pz());
        vTrArray.push_back(vec_tmp);
        hTrEta->Fill(vec_tmp.Eta());
        hTrPt->Fill(vec_tmp.Pt());
        hTrkPtEta->Fill(vec_tmp.Pt(), vec_tmp.Eta());
        if ((dEtaAbs>dfEtaMin) && (dEtaAbs<=dfEtaMax)){ //2<|\eta|<5
          dFwdCh += 1.;
          hFwdTrEta->Fill(vec_tmp.Eta());
	  hFwdTrPt->Fill(vec_tmp.Pt());
        }
        if( dEtaAbs<dcEtaCut ){ //|\eta|<1
          dMidCh++;
          hMidTrEta->Fill(vec_tmp.Eta());
          hMidTrPt->Fill(vec_tmp.Pt());
        }
      }
    }
    if(dFwdCh == 0 && dMidCh == 0) continue;//MB event at least V0 or SPD
    hFwdVsMid->Fill(dMidCh, dFwdCh);
//=============================================================================

    for (auto i=0; i<pyReco.size(); ++i) {
      const auto &ap(pyReco[i]);
      const auto dpPt(ap.pT()), dpEta(ap.eta()), dpRap(ap.y());

      if (ap.isFinal()       &&
          ap.isVisible()     &&
          ap.isCharged()     &&
         (dpPt>dConstiPtMin) && (dpEta>dConstiEtaMin)  && (dpEta<dConstiEtaMax)) {
        vConstis.emplace_back(ap.px(),ap.py(),ap.pz(),ap.p().pAbs());
        vConstis.back().set_user_index(i);
        hConsti->Fill(dpPt);
      }
//=============================================================================

      if (!(ap.isHadron())) continue;
     
      const auto id(ap.id());
      if ((dpRap>-0.5) && (dpRap<0.5)){
        if(id == 310 ){hKshortFwd->Fill(dFwdCh); hKshortPtFwd->Fill(dpPt, dFwdCh);}
        if(TMath::Abs(id) == 3122){hLambdaFwd->Fill(dFwdCh); hLambdaPtFwd->Fill(dpPt, dFwdCh);}
        if(TMath::Abs(id) == 3312){hXiFwd    ->Fill(dFwdCh); hXiPtFwd    ->Fill(dpPt, dFwdCh);}
        if(TMath::Abs(id) == 3334){hOmegaFwd ->Fill(dFwdCh); hOmegaPtFwd ->Fill(dpPt, dFwdCh);}
        if(id == 333 ){hPhiFwd   ->Fill(dFwdCh); hPhiPtFwd   ->Fill(dpPt, dFwdCh);}
        if(id == 313 ){hKstarFwd ->Fill(dFwdCh); hKstarPtFwd ->Fill(dpPt, dFwdCh);}
        if(TMath::Abs(id) == 211 ){hPionFwd  ->Fill(dFwdCh); hPionPtFwd  ->Fill(dpPt, dFwdCh);}
        if(TMath::Abs(id) == 321 ){hKionFwd  ->Fill(dFwdCh); hKionPtFwd  ->Fill(dpPt, dFwdCh);}
        if(TMath::Abs(id) == 2212){hProtonFwd->Fill(dFwdCh); hProtonPtFwd->Fill(dpPt, dFwdCh);}
      } 
      if ((dpEta<dStrgEtaMin) || (dpEta>dStrgEtaMax)) continue;
//=============================================================================

      auto ks(EStrg::Undef);
      if(id==310) { ks = EStrg::Kshort; }//par = 1; 
      if(TMath::Abs(id)==3122){ ks = EStrg::Lambda; }//par = 2; 
      if(TMath::Abs(id)==3312){ ks = EStrg::Xi;     }//par = 3; 
      if(TMath::Abs(id)==3334){ ks = EStrg::Omega;  }//par = 4; 
      if(id==333) { ks = EStrg::Phi;    }//par = 5; 
      if(id==313) { ks = EStrg::Kstar; } //par = 6; 
                                      
      if(TMath::Abs(id)==211) { ks=EStrg::Pion;     }//par = 7;
      if(TMath::Abs(id)==321) { ks=EStrg::Kion;     }//par = 8;
      if(TMath::Abs(id)==2212){ ks=EStrg::Proton;   }//par = 9;
                                                 
      
      if(ks==EStrg::Undef) continue;
//===========================================================================

      vStrgs.emplace_back(ap);
      vStrgs.back().set_user_index(i);
      vStrgs.back().set_user_info(new StrgInfo(ks));

      const auto ss(StrgName(ks));
      hParPtEta->Fill(dpPt, dpEta); 
    }//end all particles loop in one event
//=============================================================================

    TVector3 vJ, vL1, vL2, vU1, vU2, v3;
    
    fastjet::ClusterSequenceArea acs(vConstis, aJetDef, aAreaDef);
    const auto &vJets(aSelEta(acs.inclusive_jets(dJetPtMin)));
    for (const auto &aj : vJets) if (aj.area()>dJetAreaMin) { hJet->Fill(aj.pt()); hJetEta->Fill(aj.eta()); }
    Bool_t IsJet = kFALSE;
    for (const auto &aj : vJets) if (aj.area()>dJetAreaMin) {
      const auto dJ(aj.pt());
      if (dJ<10.) continue; 
      IsJet = kTRUE;
      hjet->Fill(aj.pt()); hjetEta->Fill(aj.eta()); 
      vJ.SetPtEtaPhi(aj.pt(), aj.eta(),aj.phi());
      vL1.SetPtEtaPhi(aj.pt(), aj.eta(),     aj.phi()); vL1.RotateZ(TMath::PiOver2());
      vL2.SetPtEtaPhi(aj.pt(), aj.eta(),     aj.phi()); vL2.RotateZ(-1.*TMath::PiOver2());
      vU1.SetPtEtaPhi(aj.pt(), -1.*aj.eta(), aj.phi()); vL1.RotateZ(TMath::PiOver2());
      vU2.SetPtEtaPhi(aj.pt(), -1.*aj.eta(), aj.phi()); vL2.RotateZ(-1.*TMath::PiOver2());
//=============================================================================
      TRandom3 rdm3(0);
      Double_t dAll = 0.;
      Double_t dInC = 0.;
      Double_t dOut = 0.;
      Double_t dInP = 0.;
      const Int_t ns = 1000;
      for (Int_t i=0; i<ns; i++) {
        bool bjc = false; bool bpc = false; bool boc = false;
        Double_t dPt=0., dEta=0.; hParPtEta->GetRandom2(dPt,dEta);
        v3.SetPtEtaPhi(dPt, dEta, rdm3.Uniform(0.,TMath::TwoPi()));
        double D(vJ.DeltaR(v3));
        double Dl1(vL1.DeltaR(v3));
        double Dl2(vL2.DeltaR(v3));
        double Du1(vU1.DeltaR(v3));
        double Du2(vU2.DeltaR(v3));
        if (D<StrgJC(gksStrgJCs)) bjc = true;
        if (D>StrgJC(gksStrgJCs)) boc = true;
        if (Dl1<StrgJC(gksStrgJCs) || Dl2<StrgJC(gksStrgJCs) || Du1<StrgJC(gksStrgJCs) || Du2<StrgJC(gksStrgJCs)) bpc = true; 
        if (bjc){boc = bpc = false;}
        
        if(bjc) { dInC += 1.; }
        if(bpc){ dInP += 1.; }
        if(boc){ dOut += 1.; }
        dAll += 1.;
      }

      hProfAcc->Fill(0., dAll);
      hProfAcc->Fill(1., dInC);
      hProfAcc->Fill(2., dInP);
      hProfAcc->Fill(3., dOut);
//=============================================================================
    }
    if(IsJet) {hJEvent->Fill(1.);} 
    if(IsJet) hJFwdVsMid->Fill(dMidCh, dFwdCh);
    
//=============================================================================

    for (const auto &av : vStrgs) { //loop all particles of intreast
      auto ps(av.user_info_shared_ptr());
      const auto ks((static_cast<StrgInfo*>(ps.get()))->GetType());
      const auto ss(StrgName(ks));

      TVector3 strg, vj, vl1, vl2, vu1, vu2;
      strg.SetPtEtaPhi(av.pt(), av.eta(), av.phi());
      auto dpPt = av.pt(); //Eta = av.eta(); Rap = av.rapidity();

      bool bJC; bool bPC;
      const auto sj = gksJets;
      bJC = false;
      bPC = false;

      const auto dJetPtCut(JetVal(sj));
      double dmin = 1000.; 
      for (const auto &aj : vJets) if (aj.area()>dJetAreaMin) {//loop all jet to check particle-jet relations
        const auto dj(aj.pt());
        if (dj<dJetPtCut) continue;
        vj.SetPtEtaPhi( dj, aj.eta(),     aj.phi());
        vl1.SetPtEtaPhi(dj, aj.eta(),     aj.phi()); vl1.RotateZ(TMath::PiOver2());
        vl2.SetPtEtaPhi(dj, aj.eta(),     aj.phi()); vl2.RotateZ(-1.*TMath::PiOver2());
        vu1.SetPtEtaPhi(dj, -1.*aj.eta(), aj.phi()); vu1.RotateZ(TMath::PiOver2());
        vu2.SetPtEtaPhi(dj, -1.*aj.eta(), aj.phi()); vu2.RotateZ(-1.*TMath::PiOver2());
        
        double d(vj.DeltaR(strg));
	if (d<= dmin) dmin=d;
        double dl1(vl1.DeltaR(strg));
        double dl2(vl2.DeltaR(strg));
        double du1(vu1.DeltaR(strg));
        double du2(vu2.DeltaR(strg));
        if (d<StrgJC(gksStrgJCs)) bJC = true;
        if (dl1<StrgJC(gksStrgJCs) || dl2<StrgJC(gksStrgJCs) || du1<StrgJC(gksStrgJCs) || du2<StrgJC(gksStrgJCs)) bPC = true; 
        if (bJC){bPC = false;}
      
      }
      if(bJC){
        if(ss == "Kshort"){hKshortPJ->Fill(dmin); hJCKshortFwd->Fill(dFwdCh); hJCKshortPtFwd->Fill(dpPt, dFwdCh);}
        if(ss == "Lambda"){hLambdaPJ->Fill(dmin); hJCLambdaFwd->Fill(dFwdCh); hJCLambdaPtFwd->Fill(dpPt, dFwdCh);}
        if(ss == "Xi")    {hXiPJ->Fill(dmin);     hJCXiFwd->Fill(dFwdCh);     hJCXiPtFwd    ->Fill(dpPt, dFwdCh);}
        if(ss == "Omega") {hOmegaPJ->Fill(dmin);  hJCOmegaFwd->Fill(dFwdCh);  hJCOmegaPtFwd ->Fill(dpPt, dFwdCh);}
        if(ss == "Phi")   {hPhiPJ->Fill(dmin);    hJCPhiFwd->Fill(dFwdCh);    hJCPhiPtFwd   ->Fill(dpPt, dFwdCh);}
        if(ss == "Kstar") {hKstarPJ->Fill(dmin);  hJCKstarFwd->Fill(dFwdCh);  hJCKstarPtFwd ->Fill(dpPt, dFwdCh);}
        if(ss == "Pion")  {hPionPJ->Fill(dmin);   hJCPionFwd->Fill(dFwdCh);   hJCPionPtFwd  ->Fill(dpPt, dFwdCh);}
        if(ss == "Kion")  {hKionPJ->Fill(dmin);   hJCKionFwd->Fill(dFwdCh);   hJCKionPtFwd  ->Fill(dpPt, dFwdCh);}
        if(ss == "Proton"){hProtonPJ->Fill(dmin); hJCProtonFwd->Fill(dFwdCh); hJCProtonPtFwd->Fill(dpPt, dFwdCh);}
      }
      if(bPC){
        if(ss == "Kshort"){hPCKshortFwd->Fill(dFwdCh);hPCKshortPtFwd->Fill(dpPt, dFwdCh);}
        if(ss == "Lambda"){hPCLambdaFwd->Fill(dFwdCh);hPCLambdaPtFwd->Fill(dpPt, dFwdCh);}
        if(ss == "Xi")    {hPCXiFwd->Fill(dFwdCh);    hPCXiPtFwd    ->Fill(dpPt, dFwdCh);}
        if(ss == "Omega") {hPCOmegaFwd->Fill(dFwdCh); hPCOmegaPtFwd ->Fill(dpPt, dFwdCh);}
        if(ss == "Phi")   {hPCPhiFwd->Fill(dFwdCh);   hPCPhiPtFwd   ->Fill(dpPt, dFwdCh);}
        if(ss == "Kstar") {hPCKstarFwd->Fill(dFwdCh); hPCKstarPtFwd ->Fill(dpPt, dFwdCh);}
        if(ss == "Pion")  {hPCPionFwd->Fill(dFwdCh);  hPCPionPtFwd  ->Fill(dpPt, dFwdCh);}
        if(ss == "Kion")  {hPCKionFwd->Fill(dFwdCh);  hPCKionPtFwd  ->Fill(dpPt, dFwdCh);}
        if(ss == "Proton"){hPCProtonFwd->Fill(dFwdCh);hPCProtonPtFwd->Fill(dpPt, dFwdCh);}
      }
    }
//=============================================================================

    hPtHat->Fill(pyInfo.pTHat(), dFwdCh);
    
  }

  timer.Stop();
  timer.Print();
//=============================================================================

  hXsect->Fill(0.5, pyInfo.sigmaGen());
  hTrials->Fill(0.5, pyInfo.weightSum());
//=============================================================================

  list_pyxsect->Print();
  list_results->Print();
  list_I->Print();
  list_J->Print();
  list_P->Print();
//=============================================================================

  file->cd();
  list_pyxsect->Write("list_pyxsect", TObject::kSingleKey);
  list_results->Write("list_results", TObject::kSingleKey);
  list_I->Write("list_I", TObject::kSingleKey);
  list_J->Write("list_J", TObject::kSingleKey);
  list_P->Write("list_P", TObject::kSingleKey);
  file->Close();
//=============================================================================

  ::Info(gksp.Data(), "DONE");
//=============================================================================

  return 0;
}
