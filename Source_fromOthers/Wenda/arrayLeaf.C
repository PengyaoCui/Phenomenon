void arrayLeaf() {
  TFile *fin = new TFile("arrayLeaf.root","recreate");
  TTree *tree = new TTree("tree","tree");
  Double_t x,y,z,v[3];
  tree->Branch("x",&x);
  tree->Branch("y",&y);
  tree->Branch("z",&z);
  tree->Branch("v[3]",v);
  for(Int_t i=0;i<1000;i++) {
    x = gRandom->Gaus(0,1);  
    y = gRandom->Gaus(1,0.5);  
    z = gRandom->Gaus(0,2);  
    x = y = z = 0.8;

    v[0] = x+y;
    v[1] = x-y;
    v[2] = x*y;
    tree->Fill();
  }

  AliReducedBaseEvent *event1 = new AliReducedBaseEvent("event1",AliReducedBaseEvent::kNoInit,AliReducedBaseEvent::kNoInit);
  AliReducedBaseEvent *event2 = new AliReducedBaseEvent("event2",AliReducedBaseEvent::kUseBaseTracks,AliReducedBaseEvent::kNoInit);
  AliReducedBaseEvent *event3 = new AliReducedBaseEvent("event3",AliReducedBaseEvent::kUseReducedTracks,AliReducedBaseEvent::kUseBaseTracks);
  AliReducedEventInfo *event4 = new AliReducedEventInfo("event4",AliReducedBaseEvent::kNoInit,AliReducedBaseEvent::kNoInit);
  AliReducedEventInfo *event5 = new AliReducedEventInfo("event5",AliReducedBaseEvent::kUseBaseTracks,AliReducedBaseEvent::kNoInit);
  AliReducedEventInfo *event6 = new AliReducedEventInfo("event6",AliReducedBaseEvent::kUseReducedTracks,AliReducedBaseEvent::kUseReducedTracks);
/*  tree->Branch("event1",&event1);
  tree->Branch("event2",&event2);
  tree->Branch("event3",&event3);
  tree->Branch("event4",&event4);
  tree->Branch("event5",&event5);
*/  tree->Branch("event6",&event6);
 
   TClonesArray *arr = new TClonesArray("AliReducedEventInfo",10000);
   TClonesArray *arr2 = new TClonesArray("AliReducedBaseTrack",10000);
   TClonesArray *arr3 = new TClonesArray("AliReducedTrackInfo",10000);
   tree->Branch("EVENTINFO",&arr);
   tree->Branch("track",&arr2);
   tree->Branch("track2",&arr3);
   tree->Write();


  Double_t vv[3];
  TH1F *h1 = new TH1F("h1","",1000,-5,5);
  TH1F *h2 = new TH1F("h2","",1000,-5,5);
  TH1F *h3 = new TH1F("h3","",1000,-5,5);
  tree->SetBranchAddress("v[3]",&vv);
  for(Int_t j=0;j<tree->GetEntriesFast();j++) {
    tree->GetEntry(j);
    h1->Fill(vv[0]);
    h2->Fill(vv[1]);
    h3->Fill(vv[2]);
  }
  TCanvas *c1 = new TCanvas();
  //h1->Sumw2();
  //h2->Sumw2();
  //h3->Sumw2();
  h1->SetMarkerStyle(22);
  h2->SetMarkerStyle(23);
  h3->SetMarkerStyle(24);
  h1->SetMarkerColor(2);
  h2->SetMarkerColor(4);
  h3->SetMarkerColor(6);
  h1->Draw("p");
  h2->Draw("psame");
  h3->Draw("psame");

}
