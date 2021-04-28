#include "utils.h"
//=============================================================================
const auto bsQCD(kTRUE);
const auto bCR(kTRUE);
const auto bRope(kTRUE);
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
  pythia.readString("Main:numberOfEvents = 50001");
  pythia.readString("Beams:eCM = 7000.");
  if(bsQCD) pythia.readString("SoftQCD:all = on");
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
  }
  // Enabling setting of vertex information.
  pythia.readString("PartonVertex:setVertex = on");
  pythia.readString("PartonVertex:protonRadius = 0.7");
  pythia.readString("PartonVertex:emissionWidth = 0.1");
//=============================================================================

  //pythia.readString("Tune:pp = 14");
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
  const auto dcEtaCut(0.5);

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
  auto hPtHat(new TH2D("hPtHat", "", 1000, 0., 1000., 2000, -0.5, 1999.5));
  list_results->Add(hPtHat);

  auto hJet(new TH1D("hJet", "", 500, 0., 500.));
  list_results->Add(hJet);
  
  auto hJetEta(new TH1D("hJetEta", "", 1000, -5., 5.));
  list_results->Add(hJetEta);

  auto hConsti(new TH1D("hConsti", "", 1000, 0., 100.));
  list_results->Add(hConsti);

  auto hFwdVsMid(new TH2D("hFwdVsMid", ";N_{trk}^{Mid}; N_{trk}^{Fwd}", 2000, -0.5, 1999.5, 2000, -0.5, 1999.5));
  list_results->Add(hFwdVsMid);

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
  list_results->Add(hFwdTrEta);

//=============================================================================
  //TTree *tree = new TTree("IncParticle","IncPar");
  //Int_t par;
  //Double_t fwdtrk;
  //Double_t midtrk;
  //Double_t pt;
  //Double_t eta;
  //tree->Branch("Particle",&par);//1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton; 9=Kstar
  //tree->Branch("FwdTrk",&fwdtrk);//Fwdtrack
  //tree->Branch("MidTrk",&midtrk);//MidTrack
  //tree->Branch("Pt",&pt);//Pt
  //tree->Branch("Eta",&eta);//Eta


  TTree *Tree = new TTree("particle","par");
  Int_t Par;
  Double_t Fwdtrk;
  Double_t Midtrk;
  Double_t Pt;
  Double_t Eta;
  Double_t Accep;
  Double_t DPartoJet;
  Tree->Branch("Species",&Par);//1=Kshort; 2=Lambda; 3=Xi; 4=Omega; 5=Phi; 6=Pion; 7=Kion; 8=Proton; 9=Kstar
  Tree->Branch("FwdTrk",&Fwdtrk);//Fwdtrack 
  Tree->Branch("MidTrk",&Midtrk);//MidTrack
  Tree->Branch("Pt",&Pt);//Pt
  Tree->Branch("Eta",&Eta);//Eta
  Tree->Branch("Acceptence",&Accep);//1=in jet cone; 2=PC; 3=OC
  Tree->Branch("DPartoJet",&DPartoJet);//Distance particle to jet axis
//=============================================================================
  
  CallSumw2(list_results);
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
    //fwdtrk=dFwdCh;
    //midtrk=dMidCh;
    hFwdVsMid->Fill(dMidCh, dFwdCh);
//=============================================================================

    for (auto i=0; i<pyReco.size(); ++i) {
      const auto &ap(pyReco[i]);
      const auto dpPt(ap.pT()), dpEta(ap.eta());

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
      if ((dpEta<dStrgEtaMin) || (dpEta>dStrgEtaMax)) continue;
//=============================================================================

      auto ks(EStrg::Undef);
      const auto id(ap.id());
      if(id==310) { ks = EStrg::Kshort; }//par = 1; }
      if(id==3122){ ks = EStrg::Lambda; }//par = 2; }
      if(id==3312){ ks = EStrg::Xi;     }//par = 3; }
      if(id==3334){ ks = EStrg::Omega;  }//par = 4; }
      if(id==333) { ks = EStrg::Phi;    }//par = 5; }
      
      if(id==211) { ks=EStrg::Pion;     }//par = 6;}
      if(id==321) { ks=EStrg::Kion;     }//par = 7;}
      if(id==2212){ ks=EStrg::Proton;   }//par = 8;}
      
      if(id==313) { ks = EStrg::Kstar; } //par = 9; }
      
      if(ks==EStrg::Undef) continue;
//===========================================================================

      vStrgs.emplace_back(ap);
      vStrgs.back().set_user_index(i);
      vStrgs.back().set_user_info(new StrgInfo(ks));

      const auto ss(StrgName(ks));
      //if (!ss.IsNull()) {pt = dpPt; eta = dpEta; }
      
      //tree->Fill();  
    }//end all particles loop in one event
//=============================================================================

    fastjet::ClusterSequenceArea acs(vConstis, aJetDef, aAreaDef);
    const auto &vJets(aSelEta(acs.inclusive_jets(dJetPtMin)));
    for (const auto &aj : vJets) if (aj.area()>dJetAreaMin) {hJet->Fill(aj.pt()); hJetEta->Fill(aj.eta());}
//=============================================================================

    for (const auto &av : vStrgs) { //loop all particles of intreast
      Fwdtrk = dFwdCh;
      Midtrk = dMidCh;
      auto ps(av.user_info_shared_ptr());
      const auto ks((static_cast<StrgInfo*>(ps.get()))->GetType());
      const auto ss(StrgName(ks));
      if(ss == "Kshort") Par = 1; 
      if(ss == "Lambda") Par = 2; 
      if(ss == "Xi")     Par = 3;
      if(ss == "Omega")  Par = 4;
      if(ss == "Phi")    Par = 5;
      if(ss == "Pion")   Par = 6;
      if(ss == "Kion")   Par = 7;
      if(ss == "Proton") Par = 8;
      if(ss == "Kstar")  Par = 9; 

      TVector3 strg, vj, vl1, vl2, vu1, vu2;
      strg.SetPtEtaPhi(av.pt(), av.eta(), av.phi());
      Pt = av.pt(); Eta = av.eta();
      
      bool bJC; bool bPC; bool bOC;
      const auto sj = gksJets;
      bJC = false;
      bOC = false;
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
        if (d>StrgJC(gksStrgJCs)) bOC = true;
        if (dl1<StrgJC(gksStrgJCs) || dl2<StrgJC(gksStrgJCs) || du1<StrgJC(gksStrgJCs) || du2<StrgJC(gksStrgJCs)) bPC = true; 
        if (bJC){bOC = bPC = false;}
      }

      DPartoJet = dmin;

      Accep = 10;
      if(bJC) Accep = 1;
      if(bOC) Accep = 3;
      if(bPC) Accep = 2;
      if(bOC && bPC) Accep = 2;//if bPC == 1; then !bJC == true;
      //if(bJC || bOC || bPC)
      Tree->Fill();
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
//=============================================================================

  file->cd();
  list_pyxsect->Write("list_pyxsect", TObject::kSingleKey);
  list_results->Write("list_results", TObject::kSingleKey);
  //tree->Write();
  Tree->Write();
  file->Close();
//=============================================================================

  ::Info(gksp.Data(), "DONE");
//=============================================================================

  return 0;
}
