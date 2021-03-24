void merge(TString inputFileList="file.txt", 
	   TString outFileName = "MergedResultsAll.root"){
  //uncomment the following lines if merge via alien
  //  gSystem->Load("libNetx.so") ; 
  //gSystem->Load("libRAliEn.so");
  //TGrid::Connect("alien://");

  gSystem->Load("libSTEER");
  gSystem->Load("libSTEERBase");
  gSystem->Load("libCDB");
  gSystem->Load("libRAWDatabase");
  gSystem->Load("libRAWDatarec");
  gSystem->Load("libESD");
  gSystem->Load("libAOD");
  //gSystem->Load("libSTEER");
  gSystem->Load("libANALYSIS");
  gSystem->Load("libANALYSISalice");
  gSystem->Load("libTOFbase");
  gSystem->Load("libTOFrec");

  gSystem->Load("libPWGflowBase");
  gSystem->Load("libPWGflowTasks");

  TFileMerger *fmerge = new TFileMerger();

  ifstream in1;
  in1.open(inputFileList.Data(),ios::in);

  char fileName[256];
  TString fff="";
  //  char outFileName[256];
  //Int_t i = 0;
  while(in1>>fileName){
    //printf("> %s \n",fileName);
    //sprintf(fileName, "alien://%s", fileName);
    sprintf(fileName, "%s", fileName);
    //    cout<<fileName<<endl;
    //i++;
    //if(i<=2200) continue;
    fff=fileName;
    //fff+="/pPb_5TeV_2016_Data_LHC16t_6Cents_Results_CENT_woSDD_AOD190.root";
    fmerge->AddFile(fff.Data());
    //    if(i>2) break;

    /*    if(i%100==0){
      sprintf(outFileName, "%sMerged%d.root", inputFileList.Data(),i/100);
      fmerge->OutputFile(outFileName);
      fmerge->Merge();
      fmerge->Reset();
    }
    */  
    /*
    if(in1.eof()){
      //sprintf(outFileName, "%sMerged%d.root", inputFileList.Data(),i/100+1);
      sprintf(outFileName, "%sMerged.root", inputFileList.Data());
      fmerge->OutputFile(outFileName);
      fmerge->Merge();
      fmerge->Reset();
    }
    */
  }

  fmerge->OutputFile(outFileName.Data());
  fmerge->Merge();
  fmerge->Reset();
}
