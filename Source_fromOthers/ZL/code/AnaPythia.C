#include <iostream>
#include <vector>

#include "Pythia8/Pythia.h"
#include "Pythia8/Analysis.h"
#include "Pythia8/ColourReconnection.h"
#include "Pythia8Plugins/ColourReconnectionHooks.h"

#include "TDatime.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TString.h"
#include "TMath.h"
#include "TFile.h"
#include "TList.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TVector3.h"
//=============================================================================

using namespace std;
using namespace Pythia8;
//=============================================================================

void PrintInfo();
bool CheckQCDFlag(TString);
bool CheckCRFlag (TString);
int  CheckCRMode (TString);

int GetRandomSeed();//得到种子
bool findIn(int, int, int, std::vector<int>);

const TString srcName = "AnaPythiaCR";
//=============================================================================

int main(int argc, char* argv[])
{
  const TString sMethod = Form("%s::main", srcName.Data());
//=============================================================================

  TApplication theApp(srcName.Data(), &argc, argv);
  for (int i=0; i<argc; i++) ::Info(sMethod.Data(), "argv[%d] = %s", i, argv[i]);

  if (argc<3) {
	  ::Error(sMethod.Data(), "Number of arguments (= %d) < required value", argc);
	  PrintInfo();
	  return -1;
  }
//=============================================================================

  const TString sID  = argv[1];
  const TString sQCD = argv[2]; CheckQCDFlag(sQCD);
//=============================================================================

  bool bCRf = CheckCRFlag(argv[3]);
  int  kCRm = (bCRf ? CheckCRMode(argv[4]) : 1);
  int kSeed = GetRandomSeed();
//=============================================================================

  Pythia8::Pythia pythia;//定义一个pythia
  Pythia8::Event& event = pythia.event;//固定的写法
  Pythia8::Info&  info  = pythia.info;//固定的写法

  pythia.readString("Main:numberOfEvents = 1000");//对一组参数做了设定

  //mode  Tune:pp (default = 5; minimum = -1; maximum = 14)
  pythia.readString("Tune:pp = 5"); //tune 4C
  //pythia.readString("Tune:pp = 14"); //Monash 2013 tune
  //pythia.readString("Tune:pp = 18"); //CMS Monashstar

  pythia.readString("Beams:eCM = 13000.");//13TeV

  if (sQCD=="Soft") {
	  pythia.readString("SoftQCD:nonDiffractive = on");//对应实验上的 minimum-bias trigger
  
  }

  if (sQCD=="Hard") {
	  pythia.readString("HardQCD:all = on");//Common switch for the group of all hard QCD processes
	  //pythia.readFile(Form("%s.cmnd",srcName.Data()));//????
	  //pythia.readString("PhaseSpace:pTHatMin = 20.");
	  //pythia.readString(Form("PhaseSpace:pTHatMax = %f", dHard[lHard+1]));
  }

  pythia.readString("Next:numberShowInfo = 0");//The number of events to list the Info information for, where relevant. default = 1
  pythia.readString("Next:numberShowProcess = 0");//The number of events to list the process record for, where relevant. default = 1
  pythia.readString("Next:numberShowEvent = 0");//The number of events to list the event record for, where relevant. default = 1 

  pythia.readString("ParticleDecays:limitTau0 = on");//only particles with tau0 < tau0Max are decayed.
  pythia.readString("ParticleDecays:tau0Max = 10.");//only particles with tau0 < tau0Max are decayed.

  pythia.readString("310:mayDecay = off");// \KShort will not decay
  pythia.readString("3122:mayDecay = off");// \Lambda will not decay
  pythia.readString("3312:mayDecay = off");// \Xi will not decay
  pythia.readString("3334:mayDecay = off");// \Omega will not decay
  pythia.readString("333:mayDecay = off");// \Phi will not decay
  pythia.readString("211:mayDecay = off");// \Pi charge will not decay
  pythia.readString("321:mayDecay = off");// \KCharge will not decay
  pythia.readString("2212:mayDecay = off");// \Proton will not decay

  pythia.readString("random:setseed = on");//用自己定义的种子
  pythia.readString(Form("Random:seed = %d",kSeed));

  if (bCRf) {
	  pythia.readString(Form("ColourReconnection:mode  = %d",kCRm));//0-4
	  pythia.readString(Form("BeamRemnants:remnantMode = %d",kCRm));// if ColourReconnection:mode == 1, then must BeamRemnants:remnantMode ==1
  } else {
	  pythia.readString("ColourReconnection:reconnect = off");
  }

  pythia.init();

  if (bCRf) {
	  ::Info(sMethod.Data(), "ColourReconnection:mode  = %d", pythia.mode("ColourReconnection:mode"));
	  ::Info(sMethod.Data(), "BeamRemnants:remnantMode = %d", pythia.mode("BeamRemnants:remnantMode"));
  }
//=============================================================================
  //Define out put file
  TFile *file = TFile::Open(Form("%s_%d_%s_%s.root",srcName.Data(),kSeed,sID.Data(),sQCD.Data()),"NEW");
 
  TList *list = new TList();
  TList *l = new TList();
  
  //Define Histograms....
  TH1D *hTrials    = new TH1D("hTrials", "", 1, 0., 1.); list->Add(hTrials);
  TProfile *hXsect = new TProfile("hXsect",  "", 1, 0., 1.); list->Add(hXsect);
  TH2D *hEvent = new TH2D("hEvent", "", 1000, 0., 1000., 2000, -0.5, 1999.5); hEvent->Sumw2(); list->Add(hEvent);

  TH2D *hFwdVsMid    = new TH2D("hFwdVsMid", ";N_{trk}^{Mid}; N_{trk}^{Fwd}", 2000, -0.5, 1999.5, 2000, -0.5, 1999.5); hFwdVsMid->Sumw2(); list->Add(hFwdVsMid);

  TH2D *hTrkPtEta  = new TH2D("hTrkPtEta", "Eta vs p_{T}; p_{T} [GeV]; Eta", 200, 0., 20., 1000, -5., 5.); hTrkPtEta->Sumw2(); list->Add(hTrkPtEta);
  TH1D *hTrEta     = new TH1D("hTrEta", ";#eta; N_{trig}", 1000, -5., 5.); hTrEta->Sumw2(); list->Add(hTrEta);
  TH1D *hMidTrkEta = new TH1D("hMidTrkEta", ";#eta; N_{trig}", 400, -2., 2.); hMidTrkEta->Sumw2(); list->Add(hMidTrkEta);
  TH1D *hFwdTrkEta = new TH1D("hFwdTrkEta", ";#eta; N_{trig}", 1000, -5, 5.); hFwdTrkEta->Sumw2(); list->Add(hFwdTrkEta);

  TH1D *hTrPt  = new TH1D("hTrPt", ";p_{T}; N_{trig}", 200, 0, 20.); hTrPt->Sumw2(); list->Add(hTrPt);
  TH1D *hFwdTrPt  = new TH1D("hFwdTrPt", ";p_{T}; N_{trig}", 200, 0, 20.); hFwdTrPt->Sumw2(); list->Add(hFwdTrPt);
  TH1D *hMidTrPt  = new TH1D("hMidTrPt", ";p_{T}; N_{trig}", 200, 0, 20.); hMidTrPt->Sumw2(); list->Add(hMidTrPt);

  TH2D *hKshortPt = new TH2D("hKshortPt", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hKshortPt->Sumw2(); l->Add(hKshortPt);
  TH2D *hLambdaPt = new TH2D("hLambdaPt", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hLambdaPt->Sumw2(); l->Add(hLambdaPt);
  TH2D *hXiPt     = new TH2D("hXiPt", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hXiPt->Sumw2(); l->Add(hXiPt);
  TH2D *hOmegaPt  = new TH2D("hOmegaPt", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hOmegaPt->Sumw2(); l->Add(hOmegaPt);
  TH2D *hResPhi    = new TH2D("hResPhi", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hResPhi->Sumw2(); l->Add(hResPhi);
  TH2D *hPiCh      = new TH2D("hPiCh", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hPiCh->Sumw2(); l->Add(hPiCh);
  TH2D *hKCh       = new TH2D("hKCh", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hKCh->Sumw2(); l->Add(hKCh);
  TH2D *hProton    = new TH2D("hProton", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hProton->Sumw2(); l->Add(hProton);

  TH2D *hKshortMid = new TH2D("hKshortMid", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hKshortMid->Sumw2(); l->Add(hKshortMid);
  TH2D *hLambdaMid = new TH2D("hLambdaMid", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hLambdaMid->Sumw2(); l->Add(hLambdaMid);
  TH2D *hXiMid = new TH2D("hXiMid", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hXiMid->Sumw2(); l->Add(hXiMid);
  TH2D *hOmegaMid = new TH2D("hOmegaMid", "N_{trk} vs p_{T}; p_{T} [GeV]; N_{trk}", 200, 0., 20., 2000, -0.5, 1999.5); hOmegaMid->Sumw2(); l->Add(hOmegaMid);


  TProfile *hProfKshort = new TProfile("hProfKshort", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfKshort);
  TProfile *hProfKCh    = new TProfile("hProfKCh", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfKCh);
  TProfile *hProfLambda = new TProfile("hProfLambda", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfLambda);
  TProfile *hProfXi = new TProfile("hProfXi", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfXi);
  TProfile *hProfOmega = new TProfile("hProfOmega", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfOmega);
  TProfile *hProfProton = new TProfile("hProfProton", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfProton);
  TProfile *hProfPiCh   = new TProfile("hProfPiCh", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfPiCh);
  TProfile *hProfResPhi = new TProfile("hProfResPhi", ";N_{trk}; <p_{T}> [GeV]", 2000, -0.5, 1999.5); l->Add(hProfResPhi);

  const double pi = TMath::Pi();
  
  
  //TH3D *hNchDEtaDPhiMixEventCascade  = new TH3D("hNchDEtaDPhiMixEventCascade", "; #Delta#phi; #Delta#eta; N_{trk}^{mid}", 40, -0.5*pi, 1.5*pi, 40, -4, 4, 300, -0.5, 299.5); hNchDEtaDPhiMixEventCascade->Sumw2(); list->Add(hNchDEtaDPhiMixEventCascade);
  


//=============================================================================

  //cuts
  const double dcEtaCut  = 0.9;//Mid rapidity eta cut
  const double dfEtaMin  = 2.;//forward rapidity eta min
  const double dfEtaMax  = 5.;//forward rapidity eta max
  const double dPtCut    = 0.15;// all track pT cut

  
  //temperary containers
  TVector3 vec_tmp;
  vector<int> iTrIndex;
  vector<int> iAsIndex;
  vector<TVector3> vTrArray;
  const int iMixSize=20;
  vector< vector<TVector3> > vTrArrayPool;

//=============================================================================

//event loop starts
  for (int iEvent=0; iEvent<pythia.mode("Main:numberOfEvents"); iEvent++) if (pythia.next()) { //pythia.next() Generate an(other) event
	  //event wise initializations 
	  double dFwdCh = 0.;
	  double dMidCh = 0.;
	  iTrIndex.clear();
	  iAsIndex.clear();
	  vTrArray.clear();

//=============================================================================
         //determine charged track number in mid/fwd rapidity in this event
	 
	 //track && particles loop
	 for (int i=0; i<event.size(); i++) if (event[i].isFinal()   &&
                                           event[i].isVisible() &&
                                           //event[i].isCharged() &&
                                           (event[i].pT()>dPtCut)) { 
		 double dEtaAbs = TMath::Abs(event[i].eta());
		 if( event[i].isCharged() ){
			 iTrIndex.push_back(i);
                         vec_tmp.SetXYZ(event[i].px(), event[i].py(), event[i].pz());
                         vTrArray.push_back(vec_tmp);
			 
			 hTrEta->Fill(vec_tmp.Eta());
			 hTrPt->Fill(vec_tmp.Pt());
			 hTrkPtEta->Fill(vec_tmp.Pt(), vec_tmp.Eta());

			 if ((dEtaAbs>dfEtaMin) && (dEtaAbs<=dfEtaMax)){ //2<|\eta|<5
				 dFwdCh += 1.;
				 hFwdTrkEta->Fill(vec_tmp.Eta());
				 hFwdTrPt->Fill(vec_tmp.Pt());
			 }
			 if( dEtaAbs<dcEtaCut ){ //|\eta|<2
				 dMidCh++;
				 hMidTrkEta->Fill(vec_tmp.Eta());
				 hMidTrPt->Fill(vec_tmp.Pt());
			 }

		 } 
	 }
	 hFwdVsMid->Fill(dMidCh, dFwdCh);
//=============================================================================
         //connect the inclusive particle properties with the forward charged
         //track number
         for (int i=0; i<event.size(); i++) if (event[i].isFinal() &&
                                           event[i].isVisible()) { 
		 double dEtaAbs = TMath::Abs(event[i].eta()); if (dEtaAbs>=dcEtaCut) continue;

                 int  id  = event[i].idAbs();

                 bool bKshort = (id==310);
                 bool bLambda = (id==3122);
		 bool bXi     = (id==3312); 
		 bool bOmega  = (id==3334);
                 bool bResPhi = (id==333);
                 bool bPiCh   = (id==211);
                 bool bKCh    = (id==321);
                 bool bProton = (id==2212);

		 if ((!bKshort) && (!bLambda) && (!bXi) && (!bOmega) && (!bResPhi) && (!bPiCh) && (!bKCh) && (!bProton)) continue; 

		 double dPt = event[i].pT();

		 if (bKshort) { hKshortPt->Fill(dPt,dFwdCh); hProfKshort->Fill(dFwdCh,dPt); hKshortMid->Fill(dPt, dMidCh); }
		 if (bLambda) { hLambdaPt->Fill(dPt,dFwdCh); hProfLambda->Fill(dFwdCh,dPt); hLambdaMid->Fill(dPt, dMidCh); }
		 if (bXi) { hXiPt->Fill(dPt,dFwdCh); hProfXi->Fill(dFwdCh,dPt); hXiMid->Fill(dPt, dMidCh); }
		 if (bOmega) { hOmegaPt->Fill(dPt,dFwdCh); hProfOmega->Fill(dFwdCh,dPt); hOmegaMid->Fill(dPt, dMidCh); }
		 if (bResPhi) { hResPhi->Fill(dPt,dFwdCh); hProfResPhi->Fill(dFwdCh,dPt); }
		 if (bPiCh) { hPiCh->Fill(dPt,dFwdCh); hProfPiCh->Fill(dFwdCh,dPt); }
		 if (bKCh) { hKCh->Fill(dPt,dFwdCh); hProfKCh->Fill(dFwdCh,dPt); }
		 if (bProton) { hProton->Fill(dPt,dFwdCh); hProfProton->Fill(dFwdCh,dPt); }
	 }


    hEvent->Fill(info.pTHat(), dFwdCh);
  }
//=============================================================================

  hXsect->Fill(0.5, info.sigmaGen());
  hTrials->Fill(0.5, info.weightSum());
  file->cd(); list->Write("Event", TObject::kSingleKey); l->Write("Particle", TObject::kSingleKey); file->Close();
//=============================================================================

  //pythia.stat();//obtain statistics on the number of events generated of the different kinds, and the estimated cross sections.
  ::Info(sMethod.Data(), "DONE");
  return 0;
}

//_____________________________________________________________________________
int GetRandomSeed()
{
  const TString sMethod = Form("%s::GetRandomSeed", srcName.Data());
//=============================================================================

  TDatime adt;
  new TSystem();
  UInt_t kTime = (UInt_t)adt.Get();//系统时间
  UInt_t kProc = (UInt_t)gSystem->GetPid();//Get process id.
  UInt_t kInit = kTime - kProc;
  int kSeed = (int)kInit - (int)(((int)(kInit/1e8))*1e8);//种子最大是8位数,对数位大的部分进行裁剪

  ::Info(sMethod.Data(), "Proc ID     = %d", kProc);
  ::Info(sMethod.Data(), "System time = %d", kTime);
  ::Info(sMethod.Data(), "Random number seed = %d", kSeed);

  return kSeed;
}

//_____________________________________________________________________________
bool CheckQCDFlag(TString s)
{
  const TString sMethod = Form("%s::CheckQCDFlag", srcName.Data());
//=============================================================================

  if (s.IsNull()) {
    ::Fatal(sMethod.Data(), "QCD processes has not yet been set!!");
  } else {
    if ((s!="Soft") && (s!="Hard")) {
      ::Fatal(sMethod.Data(), "QCD processe (= %s) is neither \'Soft\' nor \'Hard\'!!", s.Data());
      return true;
    } else {
      if (s=="Soft") ::Info(sMethod.Data(), "SoftQCD:nonDiffractive = on");
      if (s=="Hard") ::Info(sMethod.Data(), "HardQCD:all = on");
    }
  }

  return false;
}

//_____________________________________________________________________________
bool CheckCRFlag(TString s)
{
  const TString sMethod = Form("%s::CheckCRFlag", srcName.Data());
//=============================================================================

  ::Info(sMethod.Data(), "CR status: %s", s.Data());

  if (s.IsNull()) {
    ::Warning(sMethod.Data(), "CR flag has not yet been set, using defaul (= off)");
  } else {
    if (s=="ON") {
      ::Info(sMethod.Data(), "ColourReconnection:reconnect = on");
      return true;
    } else {
      ::Info(sMethod.Data(), "ColourReconnection:reconnect = off");
      return false;
    }
  }

  ::Info(sMethod.Data(), "ColourReconnection:reconnect = off");
  return false;
}

//_____________________________________________________________________________
int CheckCRMode(TString s)
{
  const TString sMethod = Form("%s::CheckCRMode", srcName.Data());
//=============================================================================

  int kMode = 1;
  if (s.IsNull()) {
    ::Warning(sMethod.Data(), "CR mode has not yet been set, using defaul (= 1)");
  } else {
    kMode = s.Atoi();
    if ((kMode<0) || (kMode>4)) {
      ::Fatal(sMethod.Data(), "CR mode (= %d) is invalidated!!", kMode);
    } else {
      ::Info(sMethod.Data(), "ColourReconnection:mode = %d", kMode);
    }
  }

  return kMode;
}

//_____________________________________________________________________________
void PrintInfo()
{
  const TString sMethod = Form("%s::PrintInfo", srcName.Data());
//=============================================================================

  ::Info(sMethod.Data(), "./%s.exe arg1 [arg2] [arg3]", srcName.Data());

  ::Info(sMethod.Data(), "arg1: QCD processes");
  ::Info(sMethod.Data(), "  = Soft: SoftQCD:nonDiffractive  = on");
  ::Info(sMethod.Data(), "  = Hard: HardQCD:all = on -- pT hat setting is required");
  ::Info(sMethod.Data(), "arg2: optional, CR flag (default = off)");
  ::Info(sMethod.Data(), "  = wCR: ColourReconnection:reconnect = on");
  ::Info(sMethod.Data(), "arg3: optional, CR mode (default = 1)");
  ::Info(sMethod.Data(), "  =  0: The MPI-based original Pythia 8 scheme");
  ::Info(sMethod.Data(), "  =  1: The new more QCD based scheme");
  ::Info(sMethod.Data(), "  =  2: The new gluon-move model");
  ::Info(sMethod.Data(), "  =  3: The SK  I e^{+} e^{-} CR model");
  ::Info(sMethod.Data(), "  =  4: The SK II e^{+} e^{-} CR model");

  return;
}

bool findIn(int start, int end, int object, std::vector<int> index){
	for(int iter=start; iter<end; iter++){
		if(index.at(iter)==object) 
			return true;
	} 
	return false;
}
  

