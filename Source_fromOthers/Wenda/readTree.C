void readTree() {

  TChain *chain = new TChain("tree");
  chain->Add("MassTree.root");
  printf("Number of Track: %d\n",(Int_t)chain->GetEntries());

  TFile *fout = new TFile("newTree.root","recreate");  

  double px, py, pz, pt, mass, E, y;
  chain->SetBranchAddress("px",&px);
  chain->SetBranchAddress("py",&py);
  chain->SetBranchAddress("pz",&pz);
  chain->SetBranchAddress("E",&E);

  TTree *newTree = new TTree("aodTrack","aodTrack");
  newTree->Branch("px",&px);
  newTree->Branch("py",&py);
  newTree->Branch("pz",&pz);
  newTree->Branch("pt",&pt);
  newTree->Branch("E",&E); 
  newTree->Branch("Y",&y);
  newTree->Branch("mass",&mass);

  TH1F *hpx = new TH1F("hpx","",40,0,20000);
  hpx->Sumw2();
  TH1F *hpy = new TH1F("hpy","",40,0,20000);
  hpy->Sumw2();
  TH1F *hpz = new TH1F("hpz","",40,0,20000);
  hpz->Sumw2();
  TH1F *hpt = new TH1F("hpt","",40,0,20000);
  hpt->Sumw2();
  TH1F *hE = new TH1F("hE","",40,10000,200000);
  hE->Sumw2();
  TH1F *hy = new TH1F("hy","",400,-20,20);
  hy->Sumw2();
  TH1F *hMass = new TH1F("hMass","",600,5000,5600);
  hMass->Sumw2();

  for(int i=0;i<chain->GetEntries();i++) {
    chain->GetEntry(i);
    pt = sqrt(px*px + py*py);
    y = 0.5*TMath::Log( (E+pz)/(E-pz) );
    mass = sqrt( (E*E) - (px*px + py*py + pz*pz) );
    hpx->Fill(px);
    hpy->Fill(py);
    hpz->Fill(pz);
    hpt->Fill(pt);
    hE->Fill(E);
    hy->Fill(y);
    hMass->Fill(mass);
    newTree->Fill();
  }  
  
  TCanvas *c = new TCanvas("c","",700, 500);
  c->Divide(3,2);
  c->cd(1);
  hpx->Draw();
  c->cd(2);
  hpt->Draw();
  c->cd(3);
  hE->Draw();
  c->cd(4);
  hy->Draw();
  c->cd(5);
  hMass->Draw();

  fout->Write();
//  fout->Close();

}
