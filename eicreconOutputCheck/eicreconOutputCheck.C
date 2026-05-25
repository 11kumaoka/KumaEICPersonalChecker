// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

// #define eicreconOutputCheck_cxx
#include "eicreconOutputCheck.h"

#include <random>

#include <TStyle.h>
#include <TCanvas.h>

// #include "LoadInputTrkHits.cpp"
// #include "LoadInputCalHits.cpp"

eicreconOutputCheck::eicreconOutputCheck(TTree *tree, std::string iTempFileName,std::string oTempFileName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   iFileName = iTempFileName;
   oFileName = oTempFileName;

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(iFileName.c_str());
      if (!f || !f->IsOpen()) {
         f = new TFile(iFileName.c_str());
      }
      // "kuma example": you need to replace "tree" to your tree name in the input root file.
      f->GetObject("events",tree);

   }
   Init(tree);
}

eicreconOutputCheck::~eicreconOutputCheck()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void eicreconOutputCheck::Loop()
{
   if (fChain == 0) return;

   HistInit();

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   Double_t numOfEvents[18] = {};
   Double_t numOfEvents_EachDet_TrigRegion[4][18] = {};
   Double_t numOfEvents_TrigRegion[4] = {}; // 0: Phys W/O Trig23, 1: Phys W Trig23, 2: Noise W/O Trig23, 3: Noise W Trig23
   
   size_t numOfPhys = 0;
   size_t numOfNoise = 0;

   bool bTargetEV = false;

    m_vTargetEvents = {0};


   // Int_t numOfEventLoops = 1000;
   Int_t numOfEventLoops = 5;
   // Int_t numOfEventLoops = nentries;
   if(bTargetEV) numOfEventLoops = m_vTargetEvents.size();

   // for (Long64_t jentry=0; jentry<1000; jentry++) {
   for (Long64_t jentry = 0; jentry < numOfEventLoops; ++jentry) {
   // for (Long64_t jentry=0; jentry < nentries;++jentry) {
      Long64_t tempJEntry = jentry;
      if(bTargetEV) jentry =  m_vTargetEvents.at(jentry);
      m_pubEvNum = jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      std::cout << "CheeeeeeeeeeeeeeeeCkuma00001" << std::endl;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      std::cout << "CheeeeeeeeeeeeeeeeCkuma00003" << std::endl;
      // if(jentry%100 == 0)std::cout << " == event" << jentry << " =====" << std::endl;
      std::cout << " == event" << jentry << " =====" << std::endl;
      numOfEvents[17]++;

      // m_SimTrackerHitsKuma = LoadInputTrkHits();
      // m_SimCalHitsKuma = LoadInputCalHits();


      for(Int_t iHit = 0; iHit < TOFBarrelRecHits_; iHit++){

         Double_t eDep = TOFBarrelRecHits_edep[iHit] * 1000;
         m_hEDep_BTOF->Fill(eDep);
      }
      std::cout << "CheeeeeeeeeeeeeeeeCkuma002" << std::endl;
      
   } // == end of loop over events

   std::cout << "CheeeeeeeeeeeeeeeeCkuma005" << std::endl;


   WriteHists();


   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

   std::cout << "Number of noise events: " << numOfNoise << std::endl;

}




void eicreconOutputCheck::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");

   m_hEDep_BTOF = new TH1D(
      "m_hEDep_BTOF",
      "m_hEDep_BTOF;eDep [MeV]; count", 1000, 0, 0.1
   );

   m_hTriggerCounts_MAPS = new TH1D(
      "m_hTriggerCounts_MAPS",
      "m_hTriggerCounts_MAPS;; count",
      3, 0.5, 3
   );

}


void eicreconOutputCheck::ResetValuesForEachEvent(){
   m_SimTrackerHitsKuma.clear();
   m_SimTrackerHitsKuma.shrink_to_fit();

}

void eicreconOutputCheck::WriteHists(){
   oFile->cd();

   m_hEDep_BTOF->Write();
   m_hTriggerCounts_MAPS->Write();

   oFile->Close();
}


// == s == MakeClass Default Functions == s ==
Int_t eicreconOutputCheck::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t eicreconOutputCheck::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void eicreconOutputCheck::Init(TTree *tree)
{

   GPIntKeys = 0;
   GPIntValues = 0;
   GPFloatKeys = 0;
   GPFloatValues = 0;
   GPDoubleKeys = 0;
   GPDoubleValues = 0;
   GPStringKeys = 0;
   GPStringValues = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchStatus("*", 0);

   fChain->SetBranchStatus("EventHeader", 1);
   fChain->SetBranchStatus("EventHeader.*", 1);

   fChain->SetBranchStatus("MCParticles", 1);
   fChain->SetBranchStatus("MCParticles.*", 1);
   fChain->SetBranchStatus("_MCParticles_parents", 1);
   fChain->SetBranchStatus("_MCParticles_parents.*", 1);
   fChain->SetBranchStatus("_MCParticles_daughters", 1);
   fChain->SetBranchStatus("_MCParticles_daughters.*", 1);

   fChain->SetBranchStatus("B0TrackerRecHits", 1);
   fChain->SetBranchStatus("B0TrackerRecHits.*", 1);

   fChain->SetBranchStatus("BackwardMPGDEndcapRecHits", 1);
   fChain->SetBranchStatus("BackwardMPGDEndcapRecHits.*", 1);
   fChain->SetBranchStatus("ForwardMPGDEndcapRecHits", 1);
   fChain->SetBranchStatus("ForwardMPGDEndcapRecHits.*", 1);
   fChain->SetBranchStatus("MPGDBarrelRecHits", 1);
   fChain->SetBranchStatus("MPGDBarrelRecHits.*", 1);
   fChain->SetBranchStatus("OuterMPGDBarrelRecHits", 1);
   fChain->SetBranchStatus("OuterMPGDBarrelRecHits.*", 1);

   fChain->SetBranchStatus("SiBarrelVertexRecHits", 1);
   fChain->SetBranchStatus("SiBarrelVertexRecHits.*", 1);
   fChain->SetBranchStatus("SiBarrelTrackerRecHits", 1);
   fChain->SetBranchStatus("SiBarrelTrackerRecHits.*", 1);
   fChain->SetBranchStatus("SiEndcapTrackerRecHits", 1);
   fChain->SetBranchStatus("SiEndcapTrackerRecHits.*", 1);

   fChain->SetBranchStatus("TOFBarrelRecHits", 1);
   fChain->SetBranchStatus("TOFBarrelRecHits.*", 1);
   fChain->SetBranchStatus("TOFEndcapRecHits", 1);
   fChain->SetBranchStatus("TOFEndcapRecHits.*", 1);


   fChain->SetBranchAddress("EventHeader", &EventHeader_, &b_EventHeader_);
   fChain->SetBranchAddress("EventHeader.eventNumber", EventHeader_eventNumber, &b_EventHeader_eventNumber);
   fChain->SetBranchAddress("EventHeader.runNumber", EventHeader_runNumber, &b_EventHeader_runNumber);
   fChain->SetBranchAddress("EventHeader.timeStamp", EventHeader_timeStamp, &b_EventHeader_timeStamp);
   fChain->SetBranchAddress("EventHeader.weight", EventHeader_weight, &b_EventHeader_weight);
   fChain->SetBranchAddress("EventHeader.weights_begin", EventHeader_weights_begin, &b_EventHeader_weights_begin);
   fChain->SetBranchAddress("EventHeader.weights_end", EventHeader_weights_end, &b_EventHeader_weights_end);

   fChain->SetBranchAddress("MCParticles", &MCParticles_, &b_MCParticles_);
   fChain->SetBranchAddress("MCParticles.PDG", MCParticles_PDG, &b_MCParticles_PDG);
   fChain->SetBranchAddress("MCParticles.generatorStatus", MCParticles_generatorStatus, &b_MCParticles_generatorStatus);
   fChain->SetBranchAddress("MCParticles.simulatorStatus", MCParticles_simulatorStatus, &b_MCParticles_simulatorStatus);
   fChain->SetBranchAddress("MCParticles.charge", MCParticles_charge, &b_MCParticles_charge);
   fChain->SetBranchAddress("MCParticles.time", MCParticles_time, &b_MCParticles_time);
   fChain->SetBranchAddress("MCParticles.mass", MCParticles_mass, &b_MCParticles_mass);
   fChain->SetBranchAddress("MCParticles.vertex.x", MCParticles_vertex_x, &b_MCParticles_vertex_x);
   fChain->SetBranchAddress("MCParticles.vertex.y", MCParticles_vertex_y, &b_MCParticles_vertex_y);
   fChain->SetBranchAddress("MCParticles.vertex.z", MCParticles_vertex_z, &b_MCParticles_vertex_z);
   fChain->SetBranchAddress("MCParticles.endpoint.x", MCParticles_endpoint_x, &b_MCParticles_endpoint_x);
   fChain->SetBranchAddress("MCParticles.endpoint.y", MCParticles_endpoint_y, &b_MCParticles_endpoint_y);
   fChain->SetBranchAddress("MCParticles.endpoint.z", MCParticles_endpoint_z, &b_MCParticles_endpoint_z);
   fChain->SetBranchAddress("MCParticles.momentum.x", MCParticles_momentum_x, &b_MCParticles_momentum_x);
   fChain->SetBranchAddress("MCParticles.momentum.y", MCParticles_momentum_y, &b_MCParticles_momentum_y);
   fChain->SetBranchAddress("MCParticles.momentum.z", MCParticles_momentum_z, &b_MCParticles_momentum_z);
   fChain->SetBranchAddress("MCParticles.momentumAtEndpoint.x", MCParticles_momentumAtEndpoint_x, &b_MCParticles_momentumAtEndpoint_x);
   fChain->SetBranchAddress("MCParticles.momentumAtEndpoint.y", MCParticles_momentumAtEndpoint_y, &b_MCParticles_momentumAtEndpoint_y);
   fChain->SetBranchAddress("MCParticles.momentumAtEndpoint.z", MCParticles_momentumAtEndpoint_z, &b_MCParticles_momentumAtEndpoint_z);
   fChain->SetBranchAddress("MCParticles.parents_begin", MCParticles_parents_begin, &b_MCParticles_parents_begin);
   fChain->SetBranchAddress("MCParticles.parents_end", MCParticles_parents_end, &b_MCParticles_parents_end);
   fChain->SetBranchAddress("MCParticles.daughters_begin", MCParticles_daughters_begin, &b_MCParticles_daughters_begin);
   fChain->SetBranchAddress("MCParticles.daughters_end", MCParticles_daughters_end, &b_MCParticles_daughters_end);
   fChain->SetBranchAddress("_MCParticles_parents", &_MCParticles_parents_, &b__MCParticles_parents_);
   fChain->SetBranchAddress("_MCParticles_parents.index", _MCParticles_parents_index, &b__MCParticles_parents_index);
   fChain->SetBranchAddress("_MCParticles_parents.collectionID", _MCParticles_parents_collectionID, &b__MCParticles_parents_collectionID);
   fChain->SetBranchAddress("_MCParticles_daughters", &_MCParticles_daughters_, &b__MCParticles_daughters_);
   fChain->SetBranchAddress("_MCParticles_daughters.index", _MCParticles_daughters_index, &b__MCParticles_daughters_index);
   fChain->SetBranchAddress("_MCParticles_daughters.collectionID", _MCParticles_daughters_collectionID, &b__MCParticles_daughters_collectionID);



   fChain->SetBranchAddress("SiBarrelVertexRecHits", &SiBarrelVertexRecHits_, &b_SiBarrelVertexRecHits_);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.cellID", SiBarrelVertexRecHits_cellID, &b_SiBarrelVertexRecHits_cellID);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.position.x", SiBarrelVertexRecHits_position_x, &b_SiBarrelVertexRecHits_position_x);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.position.y", SiBarrelVertexRecHits_position_y, &b_SiBarrelVertexRecHits_position_y);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.position.z", SiBarrelVertexRecHits_position_z, &b_SiBarrelVertexRecHits_position_z);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.positionError.xx", SiBarrelVertexRecHits_positionError_xx, &b_SiBarrelVertexRecHits_positionError_xx);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.positionError.yy", SiBarrelVertexRecHits_positionError_yy, &b_SiBarrelVertexRecHits_positionError_yy);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.positionError.zz", SiBarrelVertexRecHits_positionError_zz, &b_SiBarrelVertexRecHits_positionError_zz);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.time", SiBarrelVertexRecHits_time, &b_SiBarrelVertexRecHits_time);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.timeError", SiBarrelVertexRecHits_timeError, &b_SiBarrelVertexRecHits_timeError);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.edep", SiBarrelVertexRecHits_edep, &b_SiBarrelVertexRecHits_edep);
   fChain->SetBranchAddress("SiBarrelVertexRecHits.edepError", SiBarrelVertexRecHits_edepError, &b_SiBarrelVertexRecHits_edepError);
   fChain->SetBranchAddress("_SiBarrelVertexRecHits_rawHit", &_SiBarrelVertexRecHits_rawHit_, &b__SiBarrelVertexRecHits_rawHit_);
   fChain->SetBranchAddress("_SiBarrelVertexRecHits_rawHit.index", _SiBarrelVertexRecHits_rawHit_index, &b__SiBarrelVertexRecHits_rawHit_index);
   fChain->SetBranchAddress("_SiBarrelVertexRecHits_rawHit.collectionID", _SiBarrelVertexRecHits_rawHit_collectionID, &b__SiBarrelVertexRecHits_rawHit_collectionID);

   fChain->SetBranchAddress("SiBarrelTrackerRecHits", &SiBarrelTrackerRecHits_, &b_SiBarrelTrackerRecHits_);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.cellID", SiBarrelTrackerRecHits_cellID, &b_SiBarrelTrackerRecHits_cellID);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.position.x", SiBarrelTrackerRecHits_position_x, &b_SiBarrelTrackerRecHits_position_x);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.position.y", SiBarrelTrackerRecHits_position_y, &b_SiBarrelTrackerRecHits_position_y);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.position.z", SiBarrelTrackerRecHits_position_z, &b_SiBarrelTrackerRecHits_position_z);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.positionError.xx", SiBarrelTrackerRecHits_positionError_xx, &b_SiBarrelTrackerRecHits_positionError_xx);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.positionError.yy", SiBarrelTrackerRecHits_positionError_yy, &b_SiBarrelTrackerRecHits_positionError_yy);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.positionError.zz", SiBarrelTrackerRecHits_positionError_zz, &b_SiBarrelTrackerRecHits_positionError_zz);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.time", SiBarrelTrackerRecHits_time, &b_SiBarrelTrackerRecHits_time);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.timeError", SiBarrelTrackerRecHits_timeError, &b_SiBarrelTrackerRecHits_timeError);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.edep", SiBarrelTrackerRecHits_edep, &b_SiBarrelTrackerRecHits_edep);
   fChain->SetBranchAddress("SiBarrelTrackerRecHits.edepError", SiBarrelTrackerRecHits_edepError, &b_SiBarrelTrackerRecHits_edepError);
   fChain->SetBranchAddress("_SiBarrelTrackerRecHits_rawHit", &_SiBarrelTrackerRecHits_rawHit_, &b__SiBarrelTrackerRecHits_rawHit_);
   fChain->SetBranchAddress("_SiBarrelTrackerRecHits_rawHit.index", _SiBarrelTrackerRecHits_rawHit_index, &b__SiBarrelTrackerRecHits_rawHit_index);
   fChain->SetBranchAddress("_SiBarrelTrackerRecHits_rawHit.collectionID", _SiBarrelTrackerRecHits_rawHit_collectionID, &b__SiBarrelTrackerRecHits_rawHit_collectionID);

   fChain->SetBranchAddress("SiEndcapTrackerRecHits", &SiEndcapTrackerRecHits_, &b_SiEndcapTrackerRecHits_);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.cellID", SiEndcapTrackerRecHits_cellID, &b_SiEndcapTrackerRecHits_cellID);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.position.x", SiEndcapTrackerRecHits_position_x, &b_SiEndcapTrackerRecHits_position_x);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.position.y", SiEndcapTrackerRecHits_position_y, &b_SiEndcapTrackerRecHits_position_y);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.position.z", SiEndcapTrackerRecHits_position_z, &b_SiEndcapTrackerRecHits_position_z);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.positionError.xx", SiEndcapTrackerRecHits_positionError_xx, &b_SiEndcapTrackerRecHits_positionError_xx);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.positionError.yy", SiEndcapTrackerRecHits_positionError_yy, &b_SiEndcapTrackerRecHits_positionError_yy);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.positionError.zz", SiEndcapTrackerRecHits_positionError_zz, &b_SiEndcapTrackerRecHits_positionError_zz);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.time", SiEndcapTrackerRecHits_time, &b_SiEndcapTrackerRecHits_time);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.timeError", SiEndcapTrackerRecHits_timeError, &b_SiEndcapTrackerRecHits_timeError);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.edep", SiEndcapTrackerRecHits_edep, &b_SiEndcapTrackerRecHits_edep);
   fChain->SetBranchAddress("SiEndcapTrackerRecHits.edepError", SiEndcapTrackerRecHits_edepError, &b_SiEndcapTrackerRecHits_edepError);
   fChain->SetBranchAddress("_SiEndcapTrackerRecHits_rawHit", &_SiEndcapTrackerRecHits_rawHit_, &b__SiEndcapTrackerRecHits_rawHit_);
   fChain->SetBranchAddress("_SiEndcapTrackerRecHits_rawHit.index", _SiEndcapTrackerRecHits_rawHit_index, &b__SiEndcapTrackerRecHits_rawHit_index);
   fChain->SetBranchAddress("_SiEndcapTrackerRecHits_rawHit.collectionID", _SiEndcapTrackerRecHits_rawHit_collectionID, &b__SiEndcapTrackerRecHits_rawHit_collectionID);


   fChain->SetBranchAddress("MPGDBarrelRecHits", &MPGDBarrelRecHits_, &b_MPGDBarrelRecHits_);
   fChain->SetBranchAddress("MPGDBarrelRecHits.cellID", MPGDBarrelRecHits_cellID, &b_MPGDBarrelRecHits_cellID);
   fChain->SetBranchAddress("MPGDBarrelRecHits.position.x", MPGDBarrelRecHits_position_x, &b_MPGDBarrelRecHits_position_x);
   fChain->SetBranchAddress("MPGDBarrelRecHits.position.y", MPGDBarrelRecHits_position_y, &b_MPGDBarrelRecHits_position_y);
   fChain->SetBranchAddress("MPGDBarrelRecHits.position.z", MPGDBarrelRecHits_position_z, &b_MPGDBarrelRecHits_position_z);
   fChain->SetBranchAddress("MPGDBarrelRecHits.positionError.xx", MPGDBarrelRecHits_positionError_xx, &b_MPGDBarrelRecHits_positionError_xx);
   fChain->SetBranchAddress("MPGDBarrelRecHits.positionError.yy", MPGDBarrelRecHits_positionError_yy, &b_MPGDBarrelRecHits_positionError_yy);
   fChain->SetBranchAddress("MPGDBarrelRecHits.positionError.zz", MPGDBarrelRecHits_positionError_zz, &b_MPGDBarrelRecHits_positionError_zz);
   fChain->SetBranchAddress("MPGDBarrelRecHits.time", MPGDBarrelRecHits_time, &b_MPGDBarrelRecHits_time);
   fChain->SetBranchAddress("MPGDBarrelRecHits.timeError", MPGDBarrelRecHits_timeError, &b_MPGDBarrelRecHits_timeError);
   fChain->SetBranchAddress("MPGDBarrelRecHits.edep", MPGDBarrelRecHits_edep, &b_MPGDBarrelRecHits_edep);
   fChain->SetBranchAddress("MPGDBarrelRecHits.edepError", MPGDBarrelRecHits_edepError, &b_MPGDBarrelRecHits_edepError);
   fChain->SetBranchAddress("_MPGDBarrelRecHits_rawHit", &_MPGDBarrelRecHits_rawHit_, &b__MPGDBarrelRecHits_rawHit_);
   fChain->SetBranchAddress("_MPGDBarrelRecHits_rawHit.index", _MPGDBarrelRecHits_rawHit_index, &b__MPGDBarrelRecHits_rawHit_index);
   fChain->SetBranchAddress("_MPGDBarrelRecHits_rawHit.collectionID", _MPGDBarrelRecHits_rawHit_collectionID, &b__MPGDBarrelRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("OuterMPGDBarrelRecHits", &OuterMPGDBarrelRecHits_, &b_OuterMPGDBarrelRecHits_);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.cellID", OuterMPGDBarrelRecHits_cellID, &b_OuterMPGDBarrelRecHits_cellID);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.position.x", OuterMPGDBarrelRecHits_position_x, &b_OuterMPGDBarrelRecHits_position_x);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.position.y", OuterMPGDBarrelRecHits_position_y, &b_OuterMPGDBarrelRecHits_position_y);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.position.z", OuterMPGDBarrelRecHits_position_z, &b_OuterMPGDBarrelRecHits_position_z);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.positionError.xx", OuterMPGDBarrelRecHits_positionError_xx, &b_OuterMPGDBarrelRecHits_positionError_xx);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.positionError.yy", OuterMPGDBarrelRecHits_positionError_yy, &b_OuterMPGDBarrelRecHits_positionError_yy);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.positionError.zz", OuterMPGDBarrelRecHits_positionError_zz, &b_OuterMPGDBarrelRecHits_positionError_zz);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.time", OuterMPGDBarrelRecHits_time, &b_OuterMPGDBarrelRecHits_time);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.timeError", OuterMPGDBarrelRecHits_timeError, &b_OuterMPGDBarrelRecHits_timeError);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.edep", OuterMPGDBarrelRecHits_edep, &b_OuterMPGDBarrelRecHits_edep);
   fChain->SetBranchAddress("OuterMPGDBarrelRecHits.edepError", OuterMPGDBarrelRecHits_edepError, &b_OuterMPGDBarrelRecHits_edepError);
   fChain->SetBranchAddress("_OuterMPGDBarrelRecHits_rawHit", &_OuterMPGDBarrelRecHits_rawHit_, &b__OuterMPGDBarrelRecHits_rawHit_);
   fChain->SetBranchAddress("_OuterMPGDBarrelRecHits_rawHit.index", _OuterMPGDBarrelRecHits_rawHit_index, &b__OuterMPGDBarrelRecHits_rawHit_index);
   fChain->SetBranchAddress("_OuterMPGDBarrelRecHits_rawHit.collectionID", _OuterMPGDBarrelRecHits_rawHit_collectionID, &b__OuterMPGDBarrelRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("ForwardMPGDEndcapRecHits", &ForwardMPGDEndcapRecHits_, &b_ForwardMPGDEndcapRecHits_);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.cellID", ForwardMPGDEndcapRecHits_cellID, &b_ForwardMPGDEndcapRecHits_cellID);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.position.x", ForwardMPGDEndcapRecHits_position_x, &b_ForwardMPGDEndcapRecHits_position_x);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.position.y", ForwardMPGDEndcapRecHits_position_y, &b_ForwardMPGDEndcapRecHits_position_y);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.position.z", ForwardMPGDEndcapRecHits_position_z, &b_ForwardMPGDEndcapRecHits_position_z);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.positionError.xx", ForwardMPGDEndcapRecHits_positionError_xx, &b_ForwardMPGDEndcapRecHits_positionError_xx);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.positionError.yy", ForwardMPGDEndcapRecHits_positionError_yy, &b_ForwardMPGDEndcapRecHits_positionError_yy);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.positionError.zz", ForwardMPGDEndcapRecHits_positionError_zz, &b_ForwardMPGDEndcapRecHits_positionError_zz);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.time", ForwardMPGDEndcapRecHits_time, &b_ForwardMPGDEndcapRecHits_time);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.timeError", ForwardMPGDEndcapRecHits_timeError, &b_ForwardMPGDEndcapRecHits_timeError);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.edep", ForwardMPGDEndcapRecHits_edep, &b_ForwardMPGDEndcapRecHits_edep);
   fChain->SetBranchAddress("ForwardMPGDEndcapRecHits.edepError", ForwardMPGDEndcapRecHits_edepError, &b_ForwardMPGDEndcapRecHits_edepError);
   fChain->SetBranchAddress("_ForwardMPGDEndcapRecHits_rawHit", &_ForwardMPGDEndcapRecHits_rawHit_, &b__ForwardMPGDEndcapRecHits_rawHit_);
   fChain->SetBranchAddress("_ForwardMPGDEndcapRecHits_rawHit.index", _ForwardMPGDEndcapRecHits_rawHit_index, &b__ForwardMPGDEndcapRecHits_rawHit_index);
   fChain->SetBranchAddress("_ForwardMPGDEndcapRecHits_rawHit.collectionID", _ForwardMPGDEndcapRecHits_rawHit_collectionID, &b__ForwardMPGDEndcapRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("BackwardMPGDEndcapRecHits", &BackwardMPGDEndcapRecHits_, &b_BackwardMPGDEndcapRecHits_);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.cellID", BackwardMPGDEndcapRecHits_cellID, &b_BackwardMPGDEndcapRecHits_cellID);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.position.x", BackwardMPGDEndcapRecHits_position_x, &b_BackwardMPGDEndcapRecHits_position_x);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.position.y", BackwardMPGDEndcapRecHits_position_y, &b_BackwardMPGDEndcapRecHits_position_y);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.position.z", BackwardMPGDEndcapRecHits_position_z, &b_BackwardMPGDEndcapRecHits_position_z);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.positionError.xx", BackwardMPGDEndcapRecHits_positionError_xx, &b_BackwardMPGDEndcapRecHits_positionError_xx);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.positionError.yy", BackwardMPGDEndcapRecHits_positionError_yy, &b_BackwardMPGDEndcapRecHits_positionError_yy);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.positionError.zz", BackwardMPGDEndcapRecHits_positionError_zz, &b_BackwardMPGDEndcapRecHits_positionError_zz);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.time", BackwardMPGDEndcapRecHits_time, &b_BackwardMPGDEndcapRecHits_time);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.timeError", BackwardMPGDEndcapRecHits_timeError, &b_BackwardMPGDEndcapRecHits_timeError);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.edep", BackwardMPGDEndcapRecHits_edep, &b_BackwardMPGDEndcapRecHits_edep);
   fChain->SetBranchAddress("BackwardMPGDEndcapRecHits.edepError", BackwardMPGDEndcapRecHits_edepError, &b_BackwardMPGDEndcapRecHits_edepError);
   fChain->SetBranchAddress("_BackwardMPGDEndcapRecHits_rawHit", &_BackwardMPGDEndcapRecHits_rawHit_, &b__BackwardMPGDEndcapRecHits_rawHit_);
   fChain->SetBranchAddress("_BackwardMPGDEndcapRecHits_rawHit.index", _BackwardMPGDEndcapRecHits_rawHit_index, &b__BackwardMPGDEndcapRecHits_rawHit_index);
   fChain->SetBranchAddress("_BackwardMPGDEndcapRecHits_rawHit.collectionID", _BackwardMPGDEndcapRecHits_rawHit_collectionID, &b__BackwardMPGDEndcapRecHits_rawHit_collectionID);


   fChain->SetBranchAddress("TOFBarrelRecHits", &TOFBarrelRecHits_, &b_TOFBarrelRecHits_);
   fChain->SetBranchAddress("TOFBarrelRecHits.cellID", TOFBarrelRecHits_cellID, &b_TOFBarrelRecHits_cellID);
   fChain->SetBranchAddress("TOFBarrelRecHits.position.x", TOFBarrelRecHits_position_x, &b_TOFBarrelRecHits_position_x);
   fChain->SetBranchAddress("TOFBarrelRecHits.position.y", TOFBarrelRecHits_position_y, &b_TOFBarrelRecHits_position_y);
   fChain->SetBranchAddress("TOFBarrelRecHits.position.z", TOFBarrelRecHits_position_z, &b_TOFBarrelRecHits_position_z);
   fChain->SetBranchAddress("TOFBarrelRecHits.positionError.xx", TOFBarrelRecHits_positionError_xx, &b_TOFBarrelRecHits_positionError_xx);
   fChain->SetBranchAddress("TOFBarrelRecHits.positionError.yy", TOFBarrelRecHits_positionError_yy, &b_TOFBarrelRecHits_positionError_yy);
   fChain->SetBranchAddress("TOFBarrelRecHits.positionError.zz", TOFBarrelRecHits_positionError_zz, &b_TOFBarrelRecHits_positionError_zz);
   fChain->SetBranchAddress("TOFBarrelRecHits.time", TOFBarrelRecHits_time, &b_TOFBarrelRecHits_time);
   fChain->SetBranchAddress("TOFBarrelRecHits.timeError", TOFBarrelRecHits_timeError, &b_TOFBarrelRecHits_timeError);
   fChain->SetBranchAddress("TOFBarrelRecHits.edep", TOFBarrelRecHits_edep, &b_TOFBarrelRecHits_edep);
   fChain->SetBranchAddress("TOFBarrelRecHits.edepError", TOFBarrelRecHits_edepError, &b_TOFBarrelRecHits_edepError);
   fChain->SetBranchAddress("_TOFBarrelRecHits_rawHit", &_TOFBarrelRecHits_rawHit_, &b__TOFBarrelRecHits_rawHit_);
   fChain->SetBranchAddress("_TOFBarrelRecHits_rawHit.index", _TOFBarrelRecHits_rawHit_index, &b__TOFBarrelRecHits_rawHit_index);
   fChain->SetBranchAddress("_TOFBarrelRecHits_rawHit.collectionID", _TOFBarrelRecHits_rawHit_collectionID, &b__TOFBarrelRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("TOFEndcapRecHits", &TOFEndcapRecHits_, &b_TOFEndcapRecHits_);
   fChain->SetBranchAddress("TOFEndcapRecHits.cellID", TOFEndcapRecHits_cellID, &b_TOFEndcapRecHits_cellID);
   fChain->SetBranchAddress("TOFEndcapRecHits.position.x", TOFEndcapRecHits_position_x, &b_TOFEndcapRecHits_position_x);
   fChain->SetBranchAddress("TOFEndcapRecHits.position.y", TOFEndcapRecHits_position_y, &b_TOFEndcapRecHits_position_y);
   fChain->SetBranchAddress("TOFEndcapRecHits.position.z", TOFEndcapRecHits_position_z, &b_TOFEndcapRecHits_position_z);
   fChain->SetBranchAddress("TOFEndcapRecHits.positionError.xx", TOFEndcapRecHits_positionError_xx, &b_TOFEndcapRecHits_positionError_xx);
   fChain->SetBranchAddress("TOFEndcapRecHits.positionError.yy", TOFEndcapRecHits_positionError_yy, &b_TOFEndcapRecHits_positionError_yy);
   fChain->SetBranchAddress("TOFEndcapRecHits.positionError.zz", TOFEndcapRecHits_positionError_zz, &b_TOFEndcapRecHits_positionError_zz);
   fChain->SetBranchAddress("TOFEndcapRecHits.time", TOFEndcapRecHits_time, &b_TOFEndcapRecHits_time);
   fChain->SetBranchAddress("TOFEndcapRecHits.timeError", TOFEndcapRecHits_timeError, &b_TOFEndcapRecHits_timeError);
   fChain->SetBranchAddress("TOFEndcapRecHits.edep", TOFEndcapRecHits_edep, &b_TOFEndcapRecHits_edep);
   fChain->SetBranchAddress("TOFEndcapRecHits.edepError", TOFEndcapRecHits_edepError, &b_TOFEndcapRecHits_edepError);
   fChain->SetBranchAddress("_TOFEndcapRecHits_rawHit", &_TOFEndcapRecHits_rawHit_, &b__TOFEndcapRecHits_rawHit_);
   fChain->SetBranchAddress("_TOFEndcapRecHits_rawHit.index", _TOFEndcapRecHits_rawHit_index, &b__TOFEndcapRecHits_rawHit_index);
   fChain->SetBranchAddress("_TOFEndcapRecHits_rawHit.collectionID", _TOFEndcapRecHits_rawHit_collectionID, &b__TOFEndcapRecHits_rawHit_collectionID);



   fChain->SetBranchAddress("B0TrackerRecHits", &B0TrackerRecHits_, &b_B0TrackerRecHits_);
   fChain->SetBranchAddress("B0TrackerRecHits.cellID", B0TrackerRecHits_cellID, &b_B0TrackerRecHits_cellID);
   fChain->SetBranchAddress("B0TrackerRecHits.position.x", B0TrackerRecHits_position_x, &b_B0TrackerRecHits_position_x);
   fChain->SetBranchAddress("B0TrackerRecHits.position.y", B0TrackerRecHits_position_y, &b_B0TrackerRecHits_position_y);
   fChain->SetBranchAddress("B0TrackerRecHits.position.z", B0TrackerRecHits_position_z, &b_B0TrackerRecHits_position_z);
   fChain->SetBranchAddress("B0TrackerRecHits.positionError.xx", B0TrackerRecHits_positionError_xx, &b_B0TrackerRecHits_positionError_xx);
   fChain->SetBranchAddress("B0TrackerRecHits.positionError.yy", B0TrackerRecHits_positionError_yy, &b_B0TrackerRecHits_positionError_yy);
   fChain->SetBranchAddress("B0TrackerRecHits.positionError.zz", B0TrackerRecHits_positionError_zz, &b_B0TrackerRecHits_positionError_zz);
   fChain->SetBranchAddress("B0TrackerRecHits.time", B0TrackerRecHits_time, &b_B0TrackerRecHits_time);
   fChain->SetBranchAddress("B0TrackerRecHits.timeError", B0TrackerRecHits_timeError, &b_B0TrackerRecHits_timeError);
   fChain->SetBranchAddress("B0TrackerRecHits.edep", B0TrackerRecHits_edep, &b_B0TrackerRecHits_edep);
   fChain->SetBranchAddress("B0TrackerRecHits.edepError", B0TrackerRecHits_edepError, &b_B0TrackerRecHits_edepError);
   fChain->SetBranchAddress("_B0TrackerRecHits_rawHit", &_B0TrackerRecHits_rawHit_, &b__B0TrackerRecHits_rawHit_);
   fChain->SetBranchAddress("_B0TrackerRecHits_rawHit.index", _B0TrackerRecHits_rawHit_index, &b__B0TrackerRecHits_rawHit_index);
   fChain->SetBranchAddress("_B0TrackerRecHits_rawHit.collectionID", _B0TrackerRecHits_rawHit_collectionID, &b__B0TrackerRecHits_rawHit_collectionID);


   fChain->SetBranchAddress("B0ECalRecHits", &B0ECalRecHits_, &b_B0ECalRecHits_);
   fChain->SetBranchAddress("B0ECalRecHits.cellID", B0ECalRecHits_cellID, &b_B0ECalRecHits_cellID);
   fChain->SetBranchAddress("B0ECalRecHits.energy", B0ECalRecHits_energy, &b_B0ECalRecHits_energy);
   fChain->SetBranchAddress("B0ECalRecHits.energyError", B0ECalRecHits_energyError, &b_B0ECalRecHits_energyError);
   fChain->SetBranchAddress("B0ECalRecHits.time", B0ECalRecHits_time, &b_B0ECalRecHits_time);
   fChain->SetBranchAddress("B0ECalRecHits.timeError", B0ECalRecHits_timeError, &b_B0ECalRecHits_timeError);
   fChain->SetBranchAddress("B0ECalRecHits.position.x", B0ECalRecHits_position_x, &b_B0ECalRecHits_position_x);
   fChain->SetBranchAddress("B0ECalRecHits.position.y", B0ECalRecHits_position_y, &b_B0ECalRecHits_position_y);
   fChain->SetBranchAddress("B0ECalRecHits.position.z", B0ECalRecHits_position_z, &b_B0ECalRecHits_position_z);
   fChain->SetBranchAddress("B0ECalRecHits.dimension.x", B0ECalRecHits_dimension_x, &b_B0ECalRecHits_dimension_x);
   fChain->SetBranchAddress("B0ECalRecHits.dimension.y", B0ECalRecHits_dimension_y, &b_B0ECalRecHits_dimension_y);
   fChain->SetBranchAddress("B0ECalRecHits.dimension.z", B0ECalRecHits_dimension_z, &b_B0ECalRecHits_dimension_z);
   fChain->SetBranchAddress("B0ECalRecHits.sector", B0ECalRecHits_sector, &b_B0ECalRecHits_sector);
   fChain->SetBranchAddress("B0ECalRecHits.layer", B0ECalRecHits_layer, &b_B0ECalRecHits_layer);
   fChain->SetBranchAddress("B0ECalRecHits.local.x", B0ECalRecHits_local_x, &b_B0ECalRecHits_local_x);
   fChain->SetBranchAddress("B0ECalRecHits.local.y", B0ECalRecHits_local_y, &b_B0ECalRecHits_local_y);
   fChain->SetBranchAddress("B0ECalRecHits.local.z", B0ECalRecHits_local_z, &b_B0ECalRecHits_local_z);
   fChain->SetBranchAddress("_B0ECalRecHits_rawHit", &_B0ECalRecHits_rawHit_, &b__B0ECalRecHits_rawHit_);
   fChain->SetBranchAddress("_B0ECalRecHits_rawHit.index", _B0ECalRecHits_rawHit_index, &b__B0ECalRecHits_rawHit_index);
   fChain->SetBranchAddress("_B0ECalRecHits_rawHit.collectionID", _B0ECalRecHits_rawHit_collectionID, &b__B0ECalRecHits_rawHit_collectionID);

   fChain->SetBranchAddress("EcalBarrelImagingRecHits", &EcalBarrelImagingRecHits_, &b_EcalBarrelImagingRecHits_);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.cellID", EcalBarrelImagingRecHits_cellID, &b_EcalBarrelImagingRecHits_cellID);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.energy", EcalBarrelImagingRecHits_energy, &b_EcalBarrelImagingRecHits_energy);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.energyError", EcalBarrelImagingRecHits_energyError, &b_EcalBarrelImagingRecHits_energyError);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.time", EcalBarrelImagingRecHits_time, &b_EcalBarrelImagingRecHits_time);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.timeError", EcalBarrelImagingRecHits_timeError, &b_EcalBarrelImagingRecHits_timeError);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.position.x", EcalBarrelImagingRecHits_position_x, &b_EcalBarrelImagingRecHits_position_x);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.position.y", EcalBarrelImagingRecHits_position_y, &b_EcalBarrelImagingRecHits_position_y);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.position.z", EcalBarrelImagingRecHits_position_z, &b_EcalBarrelImagingRecHits_position_z);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.dimension.x", EcalBarrelImagingRecHits_dimension_x, &b_EcalBarrelImagingRecHits_dimension_x);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.dimension.y", EcalBarrelImagingRecHits_dimension_y, &b_EcalBarrelImagingRecHits_dimension_y);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.dimension.z", EcalBarrelImagingRecHits_dimension_z, &b_EcalBarrelImagingRecHits_dimension_z);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.sector", EcalBarrelImagingRecHits_sector, &b_EcalBarrelImagingRecHits_sector);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.layer", EcalBarrelImagingRecHits_layer, &b_EcalBarrelImagingRecHits_layer);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.local.x", EcalBarrelImagingRecHits_local_x, &b_EcalBarrelImagingRecHits_local_x);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.local.y", EcalBarrelImagingRecHits_local_y, &b_EcalBarrelImagingRecHits_local_y);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.local.z", EcalBarrelImagingRecHits_local_z, &b_EcalBarrelImagingRecHits_local_z);
   fChain->SetBranchAddress("_EcalBarrelImagingRecHits_rawHit", &_EcalBarrelImagingRecHits_rawHit_, &b__EcalBarrelImagingRecHits_rawHit_);
   fChain->SetBranchAddress("_EcalBarrelImagingRecHits_rawHit.index", _EcalBarrelImagingRecHits_rawHit_index, &b__EcalBarrelImagingRecHits_rawHit_index);
   fChain->SetBranchAddress("_EcalBarrelImagingRecHits_rawHit.collectionID", _EcalBarrelImagingRecHits_rawHit_collectionID, &b__EcalBarrelImagingRecHits_rawHit_collectionID);


   fChain->SetBranchAddress("EcalBarrelScFiRecHits", &EcalBarrelScFiRecHits_, &b_EcalBarrelScFiRecHits_);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.cellID", EcalBarrelScFiRecHits_cellID, &b_EcalBarrelScFiRecHits_cellID);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.energy", EcalBarrelScFiRecHits_energy, &b_EcalBarrelScFiRecHits_energy);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.energyError", EcalBarrelScFiRecHits_energyError, &b_EcalBarrelScFiRecHits_energyError);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.time", EcalBarrelScFiRecHits_time, &b_EcalBarrelScFiRecHits_time);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.timeError", EcalBarrelScFiRecHits_timeError, &b_EcalBarrelScFiRecHits_timeError);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.position.x", EcalBarrelScFiRecHits_position_x, &b_EcalBarrelScFiRecHits_position_x);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.position.y", EcalBarrelScFiRecHits_position_y, &b_EcalBarrelScFiRecHits_position_y);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.position.z", EcalBarrelScFiRecHits_position_z, &b_EcalBarrelScFiRecHits_position_z);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.dimension.x", EcalBarrelScFiRecHits_dimension_x, &b_EcalBarrelScFiRecHits_dimension_x);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.dimension.y", EcalBarrelScFiRecHits_dimension_y, &b_EcalBarrelScFiRecHits_dimension_y);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.dimension.z", EcalBarrelScFiRecHits_dimension_z, &b_EcalBarrelScFiRecHits_dimension_z);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.sector", EcalBarrelScFiRecHits_sector, &b_EcalBarrelScFiRecHits_sector);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.layer", EcalBarrelScFiRecHits_layer, &b_EcalBarrelScFiRecHits_layer);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.local.x", EcalBarrelScFiRecHits_local_x, &b_EcalBarrelScFiRecHits_local_x);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.local.y", EcalBarrelScFiRecHits_local_y, &b_EcalBarrelScFiRecHits_local_y);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.local.z", EcalBarrelScFiRecHits_local_z, &b_EcalBarrelScFiRecHits_local_z);
   fChain->SetBranchAddress("_EcalBarrelScFiRecHits_rawHit", &_EcalBarrelScFiRecHits_rawHit_, &b__EcalBarrelScFiRecHits_rawHit_);
   fChain->SetBranchAddress("_EcalBarrelScFiRecHits_rawHit.index", _EcalBarrelScFiRecHits_rawHit_index, &b__EcalBarrelScFiRecHits_rawHit_index);
   fChain->SetBranchAddress("_EcalBarrelScFiRecHits_rawHit.collectionID", _EcalBarrelScFiRecHits_rawHit_collectionID, &b__EcalBarrelScFiRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("EcalEndcapNRecHits", &EcalEndcapNRecHits_, &b_EcalEndcapNRecHits_);
   fChain->SetBranchAddress("EcalEndcapNRecHits.cellID", EcalEndcapNRecHits_cellID, &b_EcalEndcapNRecHits_cellID);
   fChain->SetBranchAddress("EcalEndcapNRecHits.energy", EcalEndcapNRecHits_energy, &b_EcalEndcapNRecHits_energy);
   fChain->SetBranchAddress("EcalEndcapNRecHits.energyError", EcalEndcapNRecHits_energyError, &b_EcalEndcapNRecHits_energyError);
   fChain->SetBranchAddress("EcalEndcapNRecHits.time", EcalEndcapNRecHits_time, &b_EcalEndcapNRecHits_time);
   fChain->SetBranchAddress("EcalEndcapNRecHits.timeError", EcalEndcapNRecHits_timeError, &b_EcalEndcapNRecHits_timeError);
   fChain->SetBranchAddress("EcalEndcapNRecHits.position.x", EcalEndcapNRecHits_position_x, &b_EcalEndcapNRecHits_position_x);
   fChain->SetBranchAddress("EcalEndcapNRecHits.position.y", EcalEndcapNRecHits_position_y, &b_EcalEndcapNRecHits_position_y);
   fChain->SetBranchAddress("EcalEndcapNRecHits.position.z", EcalEndcapNRecHits_position_z, &b_EcalEndcapNRecHits_position_z);
   fChain->SetBranchAddress("EcalEndcapNRecHits.dimension.x", EcalEndcapNRecHits_dimension_x, &b_EcalEndcapNRecHits_dimension_x);
   fChain->SetBranchAddress("EcalEndcapNRecHits.dimension.y", EcalEndcapNRecHits_dimension_y, &b_EcalEndcapNRecHits_dimension_y);
   fChain->SetBranchAddress("EcalEndcapNRecHits.dimension.z", EcalEndcapNRecHits_dimension_z, &b_EcalEndcapNRecHits_dimension_z);
   fChain->SetBranchAddress("EcalEndcapNRecHits.sector", EcalEndcapNRecHits_sector, &b_EcalEndcapNRecHits_sector);
   fChain->SetBranchAddress("EcalEndcapNRecHits.layer", EcalEndcapNRecHits_layer, &b_EcalEndcapNRecHits_layer);
   fChain->SetBranchAddress("EcalEndcapNRecHits.local.x", EcalEndcapNRecHits_local_x, &b_EcalEndcapNRecHits_local_x);
   fChain->SetBranchAddress("EcalEndcapNRecHits.local.y", EcalEndcapNRecHits_local_y, &b_EcalEndcapNRecHits_local_y);
   fChain->SetBranchAddress("EcalEndcapNRecHits.local.z", EcalEndcapNRecHits_local_z, &b_EcalEndcapNRecHits_local_z);
   fChain->SetBranchAddress("_EcalEndcapNRecHits_rawHit", &_EcalEndcapNRecHits_rawHit_, &b__EcalEndcapNRecHits_rawHit_);
   fChain->SetBranchAddress("_EcalEndcapNRecHits_rawHit.index", _EcalEndcapNRecHits_rawHit_index, &b__EcalEndcapNRecHits_rawHit_index);
   fChain->SetBranchAddress("_EcalEndcapNRecHits_rawHit.collectionID", _EcalEndcapNRecHits_rawHit_collectionID, &b__EcalEndcapNRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("EcalEndcapPRecHits", &EcalEndcapPRecHits_, &b_EcalEndcapPRecHits_);
   fChain->SetBranchAddress("EcalEndcapPRecHits.cellID", EcalEndcapPRecHits_cellID, &b_EcalEndcapPRecHits_cellID);
   fChain->SetBranchAddress("EcalEndcapPRecHits.energy", EcalEndcapPRecHits_energy, &b_EcalEndcapPRecHits_energy);
   fChain->SetBranchAddress("EcalEndcapPRecHits.energyError", EcalEndcapPRecHits_energyError, &b_EcalEndcapPRecHits_energyError);
   fChain->SetBranchAddress("EcalEndcapPRecHits.time", EcalEndcapPRecHits_time, &b_EcalEndcapPRecHits_time);
   fChain->SetBranchAddress("EcalEndcapPRecHits.timeError", EcalEndcapPRecHits_timeError, &b_EcalEndcapPRecHits_timeError);
   fChain->SetBranchAddress("EcalEndcapPRecHits.position.x", EcalEndcapPRecHits_position_x, &b_EcalEndcapPRecHits_position_x);
   fChain->SetBranchAddress("EcalEndcapPRecHits.position.y", EcalEndcapPRecHits_position_y, &b_EcalEndcapPRecHits_position_y);
   fChain->SetBranchAddress("EcalEndcapPRecHits.position.z", EcalEndcapPRecHits_position_z, &b_EcalEndcapPRecHits_position_z);
   fChain->SetBranchAddress("EcalEndcapPRecHits.dimension.x", EcalEndcapPRecHits_dimension_x, &b_EcalEndcapPRecHits_dimension_x);
   fChain->SetBranchAddress("EcalEndcapPRecHits.dimension.y", EcalEndcapPRecHits_dimension_y, &b_EcalEndcapPRecHits_dimension_y);
   fChain->SetBranchAddress("EcalEndcapPRecHits.dimension.z", EcalEndcapPRecHits_dimension_z, &b_EcalEndcapPRecHits_dimension_z);
   fChain->SetBranchAddress("EcalEndcapPRecHits.sector", EcalEndcapPRecHits_sector, &b_EcalEndcapPRecHits_sector);
   fChain->SetBranchAddress("EcalEndcapPRecHits.layer", EcalEndcapPRecHits_layer, &b_EcalEndcapPRecHits_layer);
   fChain->SetBranchAddress("EcalEndcapPRecHits.local.x", EcalEndcapPRecHits_local_x, &b_EcalEndcapPRecHits_local_x);
   fChain->SetBranchAddress("EcalEndcapPRecHits.local.y", EcalEndcapPRecHits_local_y, &b_EcalEndcapPRecHits_local_y);
   fChain->SetBranchAddress("EcalEndcapPRecHits.local.z", EcalEndcapPRecHits_local_z, &b_EcalEndcapPRecHits_local_z);
   fChain->SetBranchAddress("_EcalEndcapPRecHits_rawHit", &_EcalEndcapPRecHits_rawHit_, &b__EcalEndcapPRecHits_rawHit_);
   fChain->SetBranchAddress("_EcalEndcapPRecHits_rawHit.index", _EcalEndcapPRecHits_rawHit_index, &b__EcalEndcapPRecHits_rawHit_index);
   fChain->SetBranchAddress("_EcalEndcapPRecHits_rawHit.collectionID", _EcalEndcapPRecHits_rawHit_collectionID, &b__EcalEndcapPRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("EcalFarForwardZDCRecHits", &EcalFarForwardZDCRecHits_, &b_EcalFarForwardZDCRecHits_);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.cellID", EcalFarForwardZDCRecHits_cellID, &b_EcalFarForwardZDCRecHits_cellID);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.energy", EcalFarForwardZDCRecHits_energy, &b_EcalFarForwardZDCRecHits_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.energyError", EcalFarForwardZDCRecHits_energyError, &b_EcalFarForwardZDCRecHits_energyError);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.time", EcalFarForwardZDCRecHits_time, &b_EcalFarForwardZDCRecHits_time);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.timeError", EcalFarForwardZDCRecHits_timeError, &b_EcalFarForwardZDCRecHits_timeError);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.position.x", EcalFarForwardZDCRecHits_position_x, &b_EcalFarForwardZDCRecHits_position_x);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.position.y", EcalFarForwardZDCRecHits_position_y, &b_EcalFarForwardZDCRecHits_position_y);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.position.z", EcalFarForwardZDCRecHits_position_z, &b_EcalFarForwardZDCRecHits_position_z);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.dimension.x", EcalFarForwardZDCRecHits_dimension_x, &b_EcalFarForwardZDCRecHits_dimension_x);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.dimension.y", EcalFarForwardZDCRecHits_dimension_y, &b_EcalFarForwardZDCRecHits_dimension_y);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.dimension.z", EcalFarForwardZDCRecHits_dimension_z, &b_EcalFarForwardZDCRecHits_dimension_z);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.sector", EcalFarForwardZDCRecHits_sector, &b_EcalFarForwardZDCRecHits_sector);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.layer", EcalFarForwardZDCRecHits_layer, &b_EcalFarForwardZDCRecHits_layer);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.local.x", EcalFarForwardZDCRecHits_local_x, &b_EcalFarForwardZDCRecHits_local_x);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.local.y", EcalFarForwardZDCRecHits_local_y, &b_EcalFarForwardZDCRecHits_local_y);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.local.z", EcalFarForwardZDCRecHits_local_z, &b_EcalFarForwardZDCRecHits_local_z);
   fChain->SetBranchAddress("_EcalFarForwardZDCRecHits_rawHit", &_EcalFarForwardZDCRecHits_rawHit_, &b__EcalFarForwardZDCRecHits_rawHit_);
   fChain->SetBranchAddress("_EcalFarForwardZDCRecHits_rawHit.index", _EcalFarForwardZDCRecHits_rawHit_index, &b__EcalFarForwardZDCRecHits_rawHit_index);
   fChain->SetBranchAddress("_EcalFarForwardZDCRecHits_rawHit.collectionID", _EcalFarForwardZDCRecHits_rawHit_collectionID, &b__EcalFarForwardZDCRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("EcalLumiSpecRecHits", &EcalLumiSpecRecHits_, &b_EcalLumiSpecRecHits_);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.cellID", EcalLumiSpecRecHits_cellID, &b_EcalLumiSpecRecHits_cellID);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.energy", EcalLumiSpecRecHits_energy, &b_EcalLumiSpecRecHits_energy);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.energyError", EcalLumiSpecRecHits_energyError, &b_EcalLumiSpecRecHits_energyError);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.time", EcalLumiSpecRecHits_time, &b_EcalLumiSpecRecHits_time);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.timeError", EcalLumiSpecRecHits_timeError, &b_EcalLumiSpecRecHits_timeError);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.position.x", EcalLumiSpecRecHits_position_x, &b_EcalLumiSpecRecHits_position_x);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.position.y", EcalLumiSpecRecHits_position_y, &b_EcalLumiSpecRecHits_position_y);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.position.z", EcalLumiSpecRecHits_position_z, &b_EcalLumiSpecRecHits_position_z);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.dimension.x", EcalLumiSpecRecHits_dimension_x, &b_EcalLumiSpecRecHits_dimension_x);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.dimension.y", EcalLumiSpecRecHits_dimension_y, &b_EcalLumiSpecRecHits_dimension_y);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.dimension.z", EcalLumiSpecRecHits_dimension_z, &b_EcalLumiSpecRecHits_dimension_z);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.sector", EcalLumiSpecRecHits_sector, &b_EcalLumiSpecRecHits_sector);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.layer", EcalLumiSpecRecHits_layer, &b_EcalLumiSpecRecHits_layer);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.local.x", EcalLumiSpecRecHits_local_x, &b_EcalLumiSpecRecHits_local_x);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.local.y", EcalLumiSpecRecHits_local_y, &b_EcalLumiSpecRecHits_local_y);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.local.z", EcalLumiSpecRecHits_local_z, &b_EcalLumiSpecRecHits_local_z);
   fChain->SetBranchAddress("_EcalLumiSpecRecHits_rawHit", &_EcalLumiSpecRecHits_rawHit_, &b__EcalLumiSpecRecHits_rawHit_);
   fChain->SetBranchAddress("_EcalLumiSpecRecHits_rawHit.index", _EcalLumiSpecRecHits_rawHit_index, &b__EcalLumiSpecRecHits_rawHit_index);
   fChain->SetBranchAddress("_EcalLumiSpecRecHits_rawHit.collectionID", _EcalLumiSpecRecHits_rawHit_collectionID, &b__EcalLumiSpecRecHits_rawHit_collectionID);


      fChain->SetBranchAddress("ForwardOffMTrackerRecHits", &ForwardOffMTrackerRecHits_, &b_ForwardOffMTrackerRecHits_);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.cellID", ForwardOffMTrackerRecHits_cellID, &b_ForwardOffMTrackerRecHits_cellID);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.position.x", ForwardOffMTrackerRecHits_position_x, &b_ForwardOffMTrackerRecHits_position_x);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.position.y", ForwardOffMTrackerRecHits_position_y, &b_ForwardOffMTrackerRecHits_position_y);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.position.z", ForwardOffMTrackerRecHits_position_z, &b_ForwardOffMTrackerRecHits_position_z);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.positionError.xx", ForwardOffMTrackerRecHits_positionError_xx, &b_ForwardOffMTrackerRecHits_positionError_xx);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.positionError.yy", ForwardOffMTrackerRecHits_positionError_yy, &b_ForwardOffMTrackerRecHits_positionError_yy);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.positionError.zz", ForwardOffMTrackerRecHits_positionError_zz, &b_ForwardOffMTrackerRecHits_positionError_zz);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.time", ForwardOffMTrackerRecHits_time, &b_ForwardOffMTrackerRecHits_time);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.timeError", ForwardOffMTrackerRecHits_timeError, &b_ForwardOffMTrackerRecHits_timeError);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.edep", ForwardOffMTrackerRecHits_edep, &b_ForwardOffMTrackerRecHits_edep);
   fChain->SetBranchAddress("ForwardOffMTrackerRecHits.edepError", ForwardOffMTrackerRecHits_edepError, &b_ForwardOffMTrackerRecHits_edepError);
   fChain->SetBranchAddress("_ForwardOffMTrackerRecHits_rawHit", &_ForwardOffMTrackerRecHits_rawHit_, &b__ForwardOffMTrackerRecHits_rawHit_);
   fChain->SetBranchAddress("_ForwardOffMTrackerRecHits_rawHit.index", _ForwardOffMTrackerRecHits_rawHit_index, &b__ForwardOffMTrackerRecHits_rawHit_index);
   fChain->SetBranchAddress("_ForwardOffMTrackerRecHits_rawHit.collectionID", _ForwardOffMTrackerRecHits_rawHit_collectionID, &b__ForwardOffMTrackerRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("ForwardRomanPotRecHits", &ForwardRomanPotRecHits_, &b_ForwardRomanPotRecHits_);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.cellID", ForwardRomanPotRecHits_cellID, &b_ForwardRomanPotRecHits_cellID);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.position.x", ForwardRomanPotRecHits_position_x, &b_ForwardRomanPotRecHits_position_x);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.position.y", ForwardRomanPotRecHits_position_y, &b_ForwardRomanPotRecHits_position_y);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.position.z", ForwardRomanPotRecHits_position_z, &b_ForwardRomanPotRecHits_position_z);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.positionError.xx", ForwardRomanPotRecHits_positionError_xx, &b_ForwardRomanPotRecHits_positionError_xx);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.positionError.yy", ForwardRomanPotRecHits_positionError_yy, &b_ForwardRomanPotRecHits_positionError_yy);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.positionError.zz", ForwardRomanPotRecHits_positionError_zz, &b_ForwardRomanPotRecHits_positionError_zz);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.time", ForwardRomanPotRecHits_time, &b_ForwardRomanPotRecHits_time);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.timeError", ForwardRomanPotRecHits_timeError, &b_ForwardRomanPotRecHits_timeError);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.edep", ForwardRomanPotRecHits_edep, &b_ForwardRomanPotRecHits_edep);
   fChain->SetBranchAddress("ForwardRomanPotRecHits.edepError", ForwardRomanPotRecHits_edepError, &b_ForwardRomanPotRecHits_edepError);
   fChain->SetBranchAddress("_ForwardRomanPotRecHits_rawHit", &_ForwardRomanPotRecHits_rawHit_, &b__ForwardRomanPotRecHits_rawHit_);
   fChain->SetBranchAddress("_ForwardRomanPotRecHits_rawHit.index", _ForwardRomanPotRecHits_rawHit_index, &b__ForwardRomanPotRecHits_rawHit_index);
   fChain->SetBranchAddress("_ForwardRomanPotRecHits_rawHit.collectionID", _ForwardRomanPotRecHits_rawHit_collectionID, &b__ForwardRomanPotRecHits_rawHit_collectionID);

      fChain->SetBranchAddress("HcalBarrelRecHits", &HcalBarrelRecHits_, &b_HcalBarrelRecHits_);
   fChain->SetBranchAddress("HcalBarrelRecHits.cellID", HcalBarrelRecHits_cellID, &b_HcalBarrelRecHits_cellID);
   fChain->SetBranchAddress("HcalBarrelRecHits.energy", HcalBarrelRecHits_energy, &b_HcalBarrelRecHits_energy);
   fChain->SetBranchAddress("HcalBarrelRecHits.energyError", HcalBarrelRecHits_energyError, &b_HcalBarrelRecHits_energyError);
   fChain->SetBranchAddress("HcalBarrelRecHits.time", HcalBarrelRecHits_time, &b_HcalBarrelRecHits_time);
   fChain->SetBranchAddress("HcalBarrelRecHits.timeError", HcalBarrelRecHits_timeError, &b_HcalBarrelRecHits_timeError);
   fChain->SetBranchAddress("HcalBarrelRecHits.position.x", HcalBarrelRecHits_position_x, &b_HcalBarrelRecHits_position_x);
   fChain->SetBranchAddress("HcalBarrelRecHits.position.y", HcalBarrelRecHits_position_y, &b_HcalBarrelRecHits_position_y);
   fChain->SetBranchAddress("HcalBarrelRecHits.position.z", HcalBarrelRecHits_position_z, &b_HcalBarrelRecHits_position_z);
   fChain->SetBranchAddress("HcalBarrelRecHits.dimension.x", HcalBarrelRecHits_dimension_x, &b_HcalBarrelRecHits_dimension_x);
   fChain->SetBranchAddress("HcalBarrelRecHits.dimension.y", HcalBarrelRecHits_dimension_y, &b_HcalBarrelRecHits_dimension_y);
   fChain->SetBranchAddress("HcalBarrelRecHits.dimension.z", HcalBarrelRecHits_dimension_z, &b_HcalBarrelRecHits_dimension_z);
   fChain->SetBranchAddress("HcalBarrelRecHits.sector", HcalBarrelRecHits_sector, &b_HcalBarrelRecHits_sector);
   fChain->SetBranchAddress("HcalBarrelRecHits.layer", HcalBarrelRecHits_layer, &b_HcalBarrelRecHits_layer);
   fChain->SetBranchAddress("HcalBarrelRecHits.local.x", HcalBarrelRecHits_local_x, &b_HcalBarrelRecHits_local_x);
   fChain->SetBranchAddress("HcalBarrelRecHits.local.y", HcalBarrelRecHits_local_y, &b_HcalBarrelRecHits_local_y);
   fChain->SetBranchAddress("HcalBarrelRecHits.local.z", HcalBarrelRecHits_local_z, &b_HcalBarrelRecHits_local_z);
   fChain->SetBranchAddress("_HcalBarrelRecHits_rawHit", &_HcalBarrelRecHits_rawHit_, &b__HcalBarrelRecHits_rawHit_);
   fChain->SetBranchAddress("_HcalBarrelRecHits_rawHit.index", _HcalBarrelRecHits_rawHit_index, &b__HcalBarrelRecHits_rawHit_index);
   fChain->SetBranchAddress("_HcalBarrelRecHits_rawHit.collectionID", _HcalBarrelRecHits_rawHit_collectionID, &b__HcalBarrelRecHits_rawHit_collectionID);

   fChain->SetBranchAddress("HcalEndcapNRecHits", &HcalEndcapNRecHits_, &b_HcalEndcapNRecHits_);
   fChain->SetBranchAddress("HcalEndcapNRecHits.cellID", HcalEndcapNRecHits_cellID, &b_HcalEndcapNRecHits_cellID);
   fChain->SetBranchAddress("HcalEndcapNRecHits.energy", HcalEndcapNRecHits_energy, &b_HcalEndcapNRecHits_energy);
   fChain->SetBranchAddress("HcalEndcapNRecHits.energyError", HcalEndcapNRecHits_energyError, &b_HcalEndcapNRecHits_energyError);
   fChain->SetBranchAddress("HcalEndcapNRecHits.time", HcalEndcapNRecHits_time, &b_HcalEndcapNRecHits_time);
   fChain->SetBranchAddress("HcalEndcapNRecHits.timeError", HcalEndcapNRecHits_timeError, &b_HcalEndcapNRecHits_timeError);
   fChain->SetBranchAddress("HcalEndcapNRecHits.position.x", HcalEndcapNRecHits_position_x, &b_HcalEndcapNRecHits_position_x);
   fChain->SetBranchAddress("HcalEndcapNRecHits.position.y", HcalEndcapNRecHits_position_y, &b_HcalEndcapNRecHits_position_y);
   fChain->SetBranchAddress("HcalEndcapNRecHits.position.z", HcalEndcapNRecHits_position_z, &b_HcalEndcapNRecHits_position_z);
   fChain->SetBranchAddress("HcalEndcapNRecHits.dimension.x", HcalEndcapNRecHits_dimension_x, &b_HcalEndcapNRecHits_dimension_x);
   fChain->SetBranchAddress("HcalEndcapNRecHits.dimension.y", HcalEndcapNRecHits_dimension_y, &b_HcalEndcapNRecHits_dimension_y);
   fChain->SetBranchAddress("HcalEndcapNRecHits.dimension.z", HcalEndcapNRecHits_dimension_z, &b_HcalEndcapNRecHits_dimension_z);
   fChain->SetBranchAddress("HcalEndcapNRecHits.sector", HcalEndcapNRecHits_sector, &b_HcalEndcapNRecHits_sector);
   fChain->SetBranchAddress("HcalEndcapNRecHits.layer", HcalEndcapNRecHits_layer, &b_HcalEndcapNRecHits_layer);
   fChain->SetBranchAddress("HcalEndcapNRecHits.local.x", HcalEndcapNRecHits_local_x, &b_HcalEndcapNRecHits_local_x);
   fChain->SetBranchAddress("HcalEndcapNRecHits.local.y", HcalEndcapNRecHits_local_y, &b_HcalEndcapNRecHits_local_y);
   fChain->SetBranchAddress("HcalEndcapNRecHits.local.z", HcalEndcapNRecHits_local_z, &b_HcalEndcapNRecHits_local_z);
   fChain->SetBranchAddress("_HcalEndcapNRecHits_rawHit", &_HcalEndcapNRecHits_rawHit_, &b__HcalEndcapNRecHits_rawHit_);
   fChain->SetBranchAddress("_HcalEndcapNRecHits_rawHit.index", _HcalEndcapNRecHits_rawHit_index, &b__HcalEndcapNRecHits_rawHit_index);
   fChain->SetBranchAddress("_HcalEndcapNRecHits_rawHit.collectionID", _HcalEndcapNRecHits_rawHit_collectionID, &b__HcalEndcapNRecHits_rawHit_collectionID);

   fChain->SetBranchAddress("HcalEndcapPInsertRecHits", &HcalEndcapPInsertRecHits_, &b_HcalEndcapPInsertRecHits_);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.cellID", HcalEndcapPInsertRecHits_cellID, &b_HcalEndcapPInsertRecHits_cellID);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.energy", HcalEndcapPInsertRecHits_energy, &b_HcalEndcapPInsertRecHits_energy);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.energyError", HcalEndcapPInsertRecHits_energyError, &b_HcalEndcapPInsertRecHits_energyError);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.time", HcalEndcapPInsertRecHits_time, &b_HcalEndcapPInsertRecHits_time);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.timeError", HcalEndcapPInsertRecHits_timeError, &b_HcalEndcapPInsertRecHits_timeError);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.position.x", HcalEndcapPInsertRecHits_position_x, &b_HcalEndcapPInsertRecHits_position_x);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.position.y", HcalEndcapPInsertRecHits_position_y, &b_HcalEndcapPInsertRecHits_position_y);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.position.z", HcalEndcapPInsertRecHits_position_z, &b_HcalEndcapPInsertRecHits_position_z);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.dimension.x", HcalEndcapPInsertRecHits_dimension_x, &b_HcalEndcapPInsertRecHits_dimension_x);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.dimension.y", HcalEndcapPInsertRecHits_dimension_y, &b_HcalEndcapPInsertRecHits_dimension_y);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.dimension.z", HcalEndcapPInsertRecHits_dimension_z, &b_HcalEndcapPInsertRecHits_dimension_z);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.sector", HcalEndcapPInsertRecHits_sector, &b_HcalEndcapPInsertRecHits_sector);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.layer", HcalEndcapPInsertRecHits_layer, &b_HcalEndcapPInsertRecHits_layer);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.local.x", HcalEndcapPInsertRecHits_local_x, &b_HcalEndcapPInsertRecHits_local_x);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.local.y", HcalEndcapPInsertRecHits_local_y, &b_HcalEndcapPInsertRecHits_local_y);
   fChain->SetBranchAddress("HcalEndcapPInsertRecHits.local.z", HcalEndcapPInsertRecHits_local_z, &b_HcalEndcapPInsertRecHits_local_z);
   fChain->SetBranchAddress("_HcalEndcapPInsertRecHits_rawHit", &_HcalEndcapPInsertRecHits_rawHit_, &b__HcalEndcapPInsertRecHits_rawHit_);
   fChain->SetBranchAddress("_HcalEndcapPInsertRecHits_rawHit.index", _HcalEndcapPInsertRecHits_rawHit_index, &b__HcalEndcapPInsertRecHits_rawHit_index);
   fChain->SetBranchAddress("_HcalEndcapPInsertRecHits_rawHit.collectionID", _HcalEndcapPInsertRecHits_rawHit_collectionID, &b__HcalEndcapPInsertRecHits_rawHit_collectionID);


      fChain->SetBranchAddress("HcalFarForwardZDCRecHits", &HcalFarForwardZDCRecHits_, &b_HcalFarForwardZDCRecHits_);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.cellID", HcalFarForwardZDCRecHits_cellID, &b_HcalFarForwardZDCRecHits_cellID);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.energy", HcalFarForwardZDCRecHits_energy, &b_HcalFarForwardZDCRecHits_energy);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.energyError", HcalFarForwardZDCRecHits_energyError, &b_HcalFarForwardZDCRecHits_energyError);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.time", HcalFarForwardZDCRecHits_time, &b_HcalFarForwardZDCRecHits_time);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.timeError", HcalFarForwardZDCRecHits_timeError, &b_HcalFarForwardZDCRecHits_timeError);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.position.x", HcalFarForwardZDCRecHits_position_x, &b_HcalFarForwardZDCRecHits_position_x);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.position.y", HcalFarForwardZDCRecHits_position_y, &b_HcalFarForwardZDCRecHits_position_y);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.position.z", HcalFarForwardZDCRecHits_position_z, &b_HcalFarForwardZDCRecHits_position_z);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.dimension.x", HcalFarForwardZDCRecHits_dimension_x, &b_HcalFarForwardZDCRecHits_dimension_x);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.dimension.y", HcalFarForwardZDCRecHits_dimension_y, &b_HcalFarForwardZDCRecHits_dimension_y);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.dimension.z", HcalFarForwardZDCRecHits_dimension_z, &b_HcalFarForwardZDCRecHits_dimension_z);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.sector", HcalFarForwardZDCRecHits_sector, &b_HcalFarForwardZDCRecHits_sector);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.layer", HcalFarForwardZDCRecHits_layer, &b_HcalFarForwardZDCRecHits_layer);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.local.x", HcalFarForwardZDCRecHits_local_x, &b_HcalFarForwardZDCRecHits_local_x);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.local.y", HcalFarForwardZDCRecHits_local_y, &b_HcalFarForwardZDCRecHits_local_y);
   fChain->SetBranchAddress("HcalFarForwardZDCRecHits.local.z", HcalFarForwardZDCRecHits_local_z, &b_HcalFarForwardZDCRecHits_local_z);
   fChain->SetBranchAddress("_HcalFarForwardZDCRecHits_rawHit", &_HcalFarForwardZDCRecHits_rawHit_, &b__HcalFarForwardZDCRecHits_rawHit_);
   fChain->SetBranchAddress("_HcalFarForwardZDCRecHits_rawHit.index", _HcalFarForwardZDCRecHits_rawHit_index, &b__HcalFarForwardZDCRecHits_rawHit_index);
   fChain->SetBranchAddress("_HcalFarForwardZDCRecHits_rawHit.collectionID", _HcalFarForwardZDCRecHits_rawHit_collectionID, &b__HcalFarForwardZDCRecHits_rawHit_collectionID);

   fChain->SetBranchAddress("LFHCALRecHits", &LFHCALRecHits_, &b_LFHCALRecHits_);
   fChain->SetBranchAddress("LFHCALRecHits.cellID", LFHCALRecHits_cellID, &b_LFHCALRecHits_cellID);
   fChain->SetBranchAddress("LFHCALRecHits.energy", LFHCALRecHits_energy, &b_LFHCALRecHits_energy);
   fChain->SetBranchAddress("LFHCALRecHits.energyError", LFHCALRecHits_energyError, &b_LFHCALRecHits_energyError);
   fChain->SetBranchAddress("LFHCALRecHits.time", LFHCALRecHits_time, &b_LFHCALRecHits_time);
   fChain->SetBranchAddress("LFHCALRecHits.timeError", LFHCALRecHits_timeError, &b_LFHCALRecHits_timeError);
   fChain->SetBranchAddress("LFHCALRecHits.position.x", LFHCALRecHits_position_x, &b_LFHCALRecHits_position_x);
   fChain->SetBranchAddress("LFHCALRecHits.position.y", LFHCALRecHits_position_y, &b_LFHCALRecHits_position_y);
   fChain->SetBranchAddress("LFHCALRecHits.position.z", LFHCALRecHits_position_z, &b_LFHCALRecHits_position_z);
   fChain->SetBranchAddress("LFHCALRecHits.dimension.x", LFHCALRecHits_dimension_x, &b_LFHCALRecHits_dimension_x);
   fChain->SetBranchAddress("LFHCALRecHits.dimension.y", LFHCALRecHits_dimension_y, &b_LFHCALRecHits_dimension_y);
   fChain->SetBranchAddress("LFHCALRecHits.dimension.z", LFHCALRecHits_dimension_z, &b_LFHCALRecHits_dimension_z);
   fChain->SetBranchAddress("LFHCALRecHits.sector", LFHCALRecHits_sector, &b_LFHCALRecHits_sector);
   fChain->SetBranchAddress("LFHCALRecHits.layer", LFHCALRecHits_layer, &b_LFHCALRecHits_layer);
   fChain->SetBranchAddress("LFHCALRecHits.local.x", LFHCALRecHits_local_x, &b_LFHCALRecHits_local_x);
   fChain->SetBranchAddress("LFHCALRecHits.local.y", LFHCALRecHits_local_y, &b_LFHCALRecHits_local_y);
   fChain->SetBranchAddress("LFHCALRecHits.local.z", LFHCALRecHits_local_z, &b_LFHCALRecHits_local_z);
   fChain->SetBranchAddress("_LFHCALRecHits_rawHit", &_LFHCALRecHits_rawHit_, &b__LFHCALRecHits_rawHit_);
   fChain->SetBranchAddress("_LFHCALRecHits_rawHit.index", _LFHCALRecHits_rawHit_index, &b__LFHCALRecHits_rawHit_index);
   fChain->SetBranchAddress("_LFHCALRecHits_rawHit.collectionID", _LFHCALRecHits_rawHit_collectionID, &b__LFHCALRecHits_rawHit_collectionID);


   fChain->SetBranchAddress("GPIntKeys", &GPIntKeys, &b_GPIntKeys);
   fChain->SetBranchAddress("GPIntValues", &GPIntValues, &b_GPIntValues);
   fChain->SetBranchAddress("GPFloatKeys", &GPFloatKeys, &b_GPFloatKeys);
   fChain->SetBranchAddress("GPFloatValues", &GPFloatValues, &b_GPFloatValues);
   fChain->SetBranchAddress("GPDoubleKeys", &GPDoubleKeys, &b_GPDoubleKeys);
   fChain->SetBranchAddress("GPDoubleValues", &GPDoubleValues, &b_GPDoubleValues);
   fChain->SetBranchAddress("GPStringKeys", &GPStringKeys, &b_GPStringKeys);
   fChain->SetBranchAddress("GPStringValues", &GPStringValues, &b_GPStringValues);

   Notify();
}

Bool_t   eicreconOutputCheck::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void eicreconOutputCheck::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t eicreconOutputCheck::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

// == e == MakeClass Default Functions == s ==
