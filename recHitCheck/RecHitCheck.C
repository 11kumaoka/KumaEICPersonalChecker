// #define RecHitCheck_cxx
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

// #define RecHitCheck_cxx
#include "RecHitCheck.h"
#include "defRootVariables.h"
#include "defRootBranches.h"

#include <random>

#include <TStyle.h>
#include <TCanvas.h>

#include "rootDefoFunctions.cpp"

#include "LoadInputTrkHits.cpp"
#include "LoadInputCalHits.cpp"


void RecHitCheck::Loop()
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

   // 140
   // m_vTargetEvents = {56, 206, 284, 408, 424};
   // 0, 1, 2, 5, 7, 8, 10
   // m_vTargetEvents = {23, 84, 89, 92, 102};
   // m_vTargetEvents = {106};
   

   //  m_vTargetEvents = {0, 1 ,2, 3, 4, 5,6, 7, 8};
    m_vTargetEvents = {51, 123, 215, 330, 429, 578, 704, 859, 951, 958};
   //  51, 123, 215, 330, 429, 578, 704, 859, 951, 958, 
   // 444, 747, 756, 824

   Int_t numOfEventLoops = 1000;
   // Int_t numOfEventLoops = 5;
   // Int_t numOfEventLoops = nentries;
   if(bTargetEV) numOfEventLoops = m_vTargetEvents.size();

   // float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   // float m_timeslice_width = 20.0; // width of time split for a time frame [ns]   
   
   // for (Long64_t jentry=0; jentry<1000; jentry++) {
   for (Long64_t jentry = 0; jentry < numOfEventLoops; ++jentry) {
   // for (Long64_t jentry=0; jentry < nentries;++jentry) {
      Long64_t tempJEntry = jentry;
      if(bTargetEV) jentry =  m_vTargetEvents.at(jentry);
      m_pubEvNum = jentry;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if(jentry%100 == 0)std::cout << " == event" << jentry << " =====" << std::endl;
      std::cout << " == event" << jentry << " =====" << std::endl;
      numOfEvents[17]++;

      std::cout << "00<><><>EventHeader.eventNumber: " << EventHeader_eventNumber << std::endl;
      m_SimTrackerHitsKuma = LoadInputTrkHits();
      std::cout << "11<><><>EventHeader.eventNumber: " << EventHeader_eventNumber << std::endl;
      m_SimCalHitsKuma = LoadInputCalHits();
      std::cout << "22<><><>EventHeader.eventNumber: " << EventHeader_eventNumber << std::endl;

      // == s ==  Hit Time calibration ========================================
      for(int iDet = 0; iDet < m_triggerDetSize; ++iDet) m_SimTrackerHitsKuma.at(iDet).sortByTime();
      Double_t timeOffSet = 0.;
      
      // == e ==  Hit Time calibration ========================================
      Int_t checkPhysCount = 0;
      bool bPhysicsEvent = false; // Set the flag for physics event processing
      Double_t physEventTime = - 999999.;
      // physEventTime = FindFirstPhysParticle();
      std::cout << " <><><><><><><> First physics particle time: " << physEventTime << std::endl;
      Int_t iTimeSlice = 0;

      std::cout << "CHeeeeeeeeeeeeeeeeeeeeeeeeeeeeeecCkumaaaaa00111" << std::endl;
      ResetValuesForEachEvent();
      std::cout << "CHeeeeeeeeeeeeeeeeeeeeeeeeeeeeeecCkumaaaaa00112" << std::endl;

      if(checkPhysCount > 1) m_vTargetEvents.push_back(m_pubEvNum);
      std::cout << "CHeeeeeeeeeeeeeeeeeeeeeeeeeeeeeecCkumaaaaa00113" << std::endl;
      if(bTargetEV) jentry = tempJEntry;
      std::cout << "CHeeeeeeeeeeeeeeeeeeeeeeeeeeeeeecCkumaaaaa00114" << std::endl;
   } // == end of loop over events


   Double_t scaleV = (m_vTargetEvents.size()/2.)/(1000.);
   if(!bTargetEV) scaleV = 1. - scaleV;
   std::cout << "numOfEventLoops : scaleV = " << numOfEventLoops << " : " << scaleV << std::endl;


   WriteHists();


   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

   std::cout << "Number of noise events: " << numOfNoise << std::endl;

}




void RecHitCheck::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");


   m_hMCEtaDist = new TH1D(
      "m_hMCEtaDist",
      "MC Particles Eta Distribution; Eta; count",
      100, -5, 5
   );

   m_hMCThetaDist = new TH1D(
      "m_hMCThetaDist",
      "MC Particles Theta Distribution; Theta [rad]; count",
      70, 3.5, 3.5
   );

}


void RecHitCheck::ResetValuesForEachEvent(){
   std::cout <<"Kumaaaaaaaaaaaaaaaaaa22221"
   m_SimTrackerHitsKuma.clear();
   // m_SimTrackerHitsKuma.shrink_to_fit();
}

void RecHitCheck::WriteHists(){
   oFile->cd();

   m_hMCEtaDist->Write();
   m_hMCThetaDist->Write();

   oFile->Close();
}

