// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

// #define triggerCombineChecker_cxx
#include "triggerCombineChecker.h"

#include <random>

#include <TStyle.h>
#include <TCanvas.h>

#include "LoadInputHits.cpp"

triggerCombineChecker::triggerCombineChecker(TTree *tree, std::string iTempFileName,std::string oTempFileName) : fChain(0) 
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

triggerCombineChecker::~triggerCombineChecker()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

void triggerCombineChecker::Loop()
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
   // m_vTargetEvents = {75, 97, 131, 173, 199, 203, 203, 223, 235, 246, 277, 281, 328, 363, 369};
   // Case1: 42, 222, 245, 301, 774, 790, 795, 851
   // Case2: 43, 59, 122, 140, 164, 174, 181, 236, 372, 387, 455, 491, 497, 515, 523, 658, 709, 724, 732, 785, 800, 845, 926, 931, 951, 982
   // Case3: 

   // 140
   m_vTargetEvents = {236};
   // m_vTargetEvents = {106};
   

   Int_t numOfEventLoops = 1000;
   // Int_t numOfEventLoops = 1;
   // Int_t numOfEventLoops = nentries;
   if(bTargetEV) numOfEventLoops = m_vTargetEvents.size();

   // float m_timewindow = 2000.0; // width of time split for a time frame [ns]
   // float m_timeslice_width = 20.0; // width of time split for a time frame [ns]
   Double_t m_timeWindows[17] = {148.05, 14.25, 13.05, 55.25, 1.25, 0, 0, 0, 15.65, 10.85, 0, 27.55, 16.25, 15.25, 0, 18.45, 14.25};


   // for (Long64_t jentry=0; jentry<1000; jentry++) {
   for (Long64_t jentry = 0; jentry < numOfEventLoops; ++jentry) {
   // for (Long64_t jentry=0; jentry < nentries;++jentry) {
      Long64_t tempJEntry = jentry;
      if(bTargetEV) jentry =  m_vTargetEvents.at(jentry);
      m_pubEvNum = jentry;

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // if(jentry%100 == 0)std::cout << " == event" << jentry << " =====" << std::endl;
      std::cout << " == event" << jentry << " =====" << std::endl;
      numOfEvents[17]++;

      m_SimTrackerHitsKuma = LoadInputHits();

      // == s ==  Hit Time calibration ========================================
      for(int iDet = 0; iDet < 17; ++iDet) m_SimTrackerHitsKuma.at(iDet).sortByTime();
      Double_t timeOffSet = 0.;
      HitTimeCalibration(timeOffSet);
      // == e ==  Hit Time calibration ========================================
      
      bool bPhysicsEvent = false; // Set the flag for physics event processing
      Double_t physEventTime = - 999999.;
      physEventTime = FindFirstPhysParticle();

      bool bAdmitedInterval = false;
      Int_t iTimeSlice = 0;
      float sTime = m_timeslice_width * iTimeSlice;
      float eTime = sTime + m_timeslice_width;

      Int_t startHitPoint[17] = {0};
      bool bLastHit[17] = {};
      
      bool bPhysCapture = false; // Flag to check if physics events are missed
      bAdmitedInterval = false; // Reset the admission flag for the next time slice

      if(bTargetEV) FillEventDisplay(0., 0., true);

      // == s ==  Time-Slice Loop in a Time-Frame ========================================      
      while (eTime <= m_timewindow){
         // std::cout << "== s 00 Time slice: " << iTimeSlice << ", eTime: " << eTime << ":: physics event time: " << physEventTime <<  " === "<< std::endl;
         bPhysicsEvent = false;
         if(sTime <= physEventTime && physEventTime < eTime){
            bPhysicsEvent = true; // Check if the time slice is within the physics event time window
            numOfPhys++;
         } else numOfNoise++;

         Int_t hitsCountsInTS[17] = {0};
         m_bTrigger = false;

         Int_t hitsCountsInTSDevInThetaPhi1[12][8] = {}; // Theta 0-12, Phi 0-8
         Int_t hitsCountsInTSDevInThetaPhi2[12][8] = {}; // Theta 0-11, Phi 0-8
         for(size_t iDet = 0; iDet < 17; ++iDet){
            if(bLastHit[iDet]) continue; // Skip if the detector has no hits left to process
            bool bInitialHit = false;

            Int_t numberOfHits = m_SimTrackerHitsKuma.at(iDet).getSize();
            for (size_t iHit = startHitPoint[iDet]; iHit < numberOfHits; ++iHit) {
               Double_t time = m_SimTrackerHitsKuma.at(iDet).getTime(iHit);

               Double_t detTimeRes = 2000.; // default 2000 ns
               if(iDet == 1 || iDet == 2 || iDet == 8 || iDet == 9) detTimeRes = m_timeResolution_MPGD;
               else if(iDet == 12 || iDet == 13) detTimeRes = m_timeResolution_TOF;
               
               if(time - detTimeRes < eTime){
                  Double_t hitX = m_SimTrackerHitsKuma.at(iDet).getPosiX(iHit);
                  Double_t hitY = m_SimTrackerHitsKuma.at(iDet).getPosiY(iHit);
                  Double_t hitZ = m_SimTrackerHitsKuma.at(iDet).getPosiZ(iHit);         
                  Double_t hitR = TMath::Sqrt(hitX*hitX + hitY*hitY + hitZ*hitZ);
                  Double_t hit_Theta = TMath::ACos(hitZ/hitR);
                  Double_t hit_Phi = TMath::ATan2(hitY, hitX) + 2*TMath::Pi();
                  Int_t thetaID1 = hit_Theta / (TMath::Pi()/12.);
                  Int_t thetaID2 = (hit_Theta + TMath::Pi()/24.) / (TMath::Pi()/12.);
                  Int_t phiID1 = hit_Phi / (TMath::Pi()/8.);
                  Int_t phiID2 = (hit_Phi + TMath::Pi()/16.) / (TMath::Pi()/8.);

                  if(time + detTimeRes > sTime){
                     //MPGD or TOF
                     if(iDet == 1 || iDet == 2 || iDet == 8 || iDet == 9 || iDet == 12 || iDet == 13){
                        hitsCountsInTSDevInThetaPhi1[thetaID1][phiID1]++;
                        hitsCountsInTSDevInThetaPhi2[thetaID2][phiID2]++;
                        // std::cout << "iDet: " << iDet << ", iHit: " << iHit\
                        //    << ", sTime: " << sTime << ", time: " << m_SimTrackerHitsKuma.at(iDet).getTime(iHit)\
                        //    << ", time + detTimeRes = " << time + detTimeRes << ", eTime: " << eTime<< std::endl;
                     }
                     
                     if(bInitialHit == false){
                        // Update the start point for the next iteration
                        startHitPoint[iDet] = iHit;
                        bInitialHit = true;
                     }

                  }else{
                     if(iHit == numberOfHits - 1){
                        bLastHit[iDet] = true;
                        break; // Break if the hit time exceeds the current time slice
                     }
                  }
               }else{
                  if(time - detTimeRes > eTime){
                     startHitPoint[iDet] = iHit; // Update the start point for the next iteration
                     bInitialHit = true;
                     if(time + detTimeRes < sTime && startHitPoint[iDet] == numberOfHits - 1){
                        bLastHit[iDet] = true;
                        break; // Break if the hit time exceeds the current time slice
                     }
                     // std::cout << "Skipped" << std::endl;
                  }
                  break; // Break if the hit time exceeds the current time slice
               };
               
            }
         }

         // == s ==  Trigger Judgement =============================================================
         for(size_t iThetaBin = 0; iThetaBin < 12; ++iThetaBin){
            for(size_t iPhiBin = 0; iPhiBin < 8; ++iPhiBin){
               if(hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin] > 1) m_bTrigger = true;
               if(hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin] > 1) m_bTrigger = true;

               // if(hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin] > 1 ||\
               // hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin] > 1) \
               // std::cout << "Theta:" << iThetaBin << ", Phi: " << iPhiBin\
               //    << " numOfhits1 = " << hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin]\
               //    << " numOfhits2 = " << hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin]\
               //    << std::endl;
            }
         }

         if(bPhysicsEvent){
            if(m_bTrigger){
               m_hTriggerCounts->Fill(1);
               bPhysCapture = true;
            }
         }else{
            if(!bPhysCapture
               && (eTime - 2*m_timeslice_width <= physEventTime && physEventTime < eTime - m_timeslice_width)
               && (m_bTrigger)){
               m_hTriggerCounts->Fill(1);
               m_vTargetEvents.pop_back();
            }else if(m_bTrigger) m_hTriggerCounts->Fill(3);
         }

         if(bPhysicsEvent && (!m_bTrigger)){
            m_vTargetEvents.push_back(m_pubEvNum);
            FillEventDisplay(eTime - m_timeslice_width, eTime, false);
         }
         // == s ==  Trigger Judgement =============================================================

         iTimeSlice++;
         sTime = m_timeslice_width * iTimeSlice;
         eTime = sTime + m_timeslice_width;
      }
      // == e ==  Time-Slice Loop in a Time-Frame ==================================================

      ResetValuesForEachEvent();

      if(bTargetEV) jentry = tempJEntry;
   } // == end of loop over events


   std::cout << "Number of events: " << numOfPhys << ", numOfNoise: " << numOfNoise << std::endl;
   m_hTriggerCounts->SetBinContent(2, numOfPhys);
   m_hTriggerCounts->SetBinContent(4, numOfNoise);
   for(size_t iTrig = 0; iTrig < 5; ++iTrig) m_hTriggerCounts->SetBinError(iTrig + 1, 0.0);

   WriteHists();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

   std::cout << "Number of noise events: " << numOfNoise << std::endl;

}


void triggerCombineChecker::HitTimeCalibration(Double_t timeOffSet){
   for(int iDet = 0; iDet < 17; ++iDet){
      Int_t numberOfHits = m_SimTrackerHitsKuma.at(iDet).getSize();
      if(numberOfHits == 0) continue;
      
      for (size_t iHit = 0; iHit < numberOfHits; ++iHit) {
         Double_t hitTime = m_SimTrackerHitsKuma.at(iDet).getTime(iHit);
         
         Double_t hitX = m_SimTrackerHitsKuma.at(iDet).getPosiX(iHit);
         Double_t hitY = m_SimTrackerHitsKuma.at(iDet).getPosiY(iHit);
         Double_t hitZ = m_SimTrackerHitsKuma.at(iDet).getPosiZ(iHit);         
         Double_t hitR = TMath::Sqrt(hitX*hitX + hitY*hitY + hitZ*hitZ);
         
         Double_t calibratedTime = HitTimeCalibrationByR(hitTime, hitR) + timeOffSet;
         m_SimTrackerHitsKuma.at(iDet).setTime(iHit, calibratedTime);
      }
      m_SimTrackerHitsKuma.at(iDet).sortByTime();
   }
}


Double_t triggerCombineChecker::FindFirstPhysParticle(){

   Double_t fastestMCHitTime = 9999999.;
   for(Int_t iMCHit = 0; iMCHit < MCParticles_; ++iMCHit) {
      Int_t pType = MCParticles_generatorStatus[iMCHit];      
      if(pType == 0 || pType >  1100) continue; // Skip if not a physics event
      Double_t mcHitTime = MCParticles_time[iMCHit];
      // std::cout << "mcHitTime = " << mcHitTime << std::endl;
      // if(mcHitTime != 0 && mcHitTime < fastestMCHitTime) fastestMCHitTime = mcHitTime;
      if(MCParticles_parents_begin[iMCHit] == 0) fastestMCHitTime = mcHitTime; // Ensure the status is set correctly 
   }
   // fastestMCHitTime += 2.; // + 2 ns offset to avoid the zero time issue

   return fastestMCHitTime;
}


void triggerCombineChecker::FillEventDisplay(Double_t sTime, Double_t eTime, bool bTF){
   for(size_t iDet = 0; iDet < 17; ++iDet){
      Int_t numberOfHits = m_SimTrackerHitsKuma.at(iDet).getSize();
      for (size_t iHit = 0; iHit < numberOfHits; ++iHit) {                        
         Double_t time = m_SimTrackerHitsKuma.at(iDet).getTime(iHit);
         if(!bTF && time < sTime) continue;
         if(!bTF && time > eTime) break; // Break if the hit time exceeds the current time slice
         
         Double_t hitX = m_SimTrackerHitsKuma.at(iDet).getPosiX(iHit);
         Double_t hitY = m_SimTrackerHitsKuma.at(iDet).getPosiY(iHit);
         Double_t hitR = std::sqrt(hitX*hitX + hitY*hitY);
         Double_t hitZ = m_SimTrackerHitsKuma.at(iDet).getPosiZ(iHit);
         if(!bTF) m_hEventDisplayZR_Det->Fill(hitZ, hitR);
         else m_hEventDisplayZR_Det_TF->Fill(hitZ, hitR);
      }
   }
}

Double_t triggerCombineChecker::HistCriticalValueEstimation(Double_t confidence, TH1D* hist) {
   // Calculate the cumulative distribution function (CDF) value for a given threshold
   // pThre: threshold value
   // hist: histogram to calculate CDF from
   Double_t cdf = 0.0;
   Int_t pThreXBin = 0;
   Double_t integral = hist->Integral();
   if (integral == 0) return 0; // Avoid division by zero
   for (int iBin = 1; iBin <= hist->GetNbinsX(); ++iBin) {
      if (cdf/integral > confidence){
         pThreXBin = iBin - 1;
         break;
      }
      cdf += hist->GetBinContent(iBin)/integral;
   }

   Double_t pThreX = hist->GetXaxis()->GetBinCenter(pThreXBin);

   return pThreX;
}



void triggerCombineChecker::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");

   m_hEventDisplayZR_Det = new TH2D(
      "m_hEventDisplayZR_Det",
      "Event Display; z [mm]; r [mm]",
      1000, -10000, 10000, 250, 0,2500
   );

   m_hEventDisplayZR_Det_TF = new TH2D(
      "m_hEventDisplayZR_Det_TF",
      "Event Display; z [mm]; r [mm]",
      1000, -10000, 10000, 250, 0,2500
   );

   m_hTriggerCounts = new TH1D(
      "m_hTriggerCounts",
      "m_hTriggerCounts;; count",
      4, 0.5, 4
   );

   TString triggerNames[4] = {"Triggered (Phys)", "All Events (Phys)", "Triggered (BKG)", "All Events (BKG)"};
   for (int i = 0; i < 4; ++i) {
      m_hTriggerCounts->GetXaxis()->SetBinLabel(i + 1, triggerNames[i].Data());
   }


}


void triggerCombineChecker::ResetValuesForEachEvent(){
   m_SimTrackerHitsKuma.clear();
   m_SimTrackerHitsKuma.shrink_to_fit();

}

void triggerCombineChecker::WriteHists(){
   oFile->cd();

   m_hEventDisplayZR_Det->Write();
   m_hEventDisplayZR_Det_TF->Write();

   m_hTriggerCounts->Write();

   oFile->Close();
}


// == s == MakeClass Default Functions == s ==
Int_t triggerCombineChecker::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

Long64_t triggerCombineChecker::LoadTree(Long64_t entry)
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

void triggerCombineChecker::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   // x = 0; // "kuma example"

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);


   // Set object pointer
   _EventHeader_weights = 0;
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

   fChain->SetBranchAddress("B0ECalHits", &B0ECalHits_, &b_B0ECalHits_);
   fChain->SetBranchAddress("B0ECalHits.cellID", B0ECalHits_cellID, &b_B0ECalHits_cellID);
   fChain->SetBranchAddress("B0ECalHits.energy", B0ECalHits_energy, &b_B0ECalHits_energy);
   fChain->SetBranchAddress("B0ECalHits.position.x", B0ECalHits_position_x, &b_B0ECalHits_position_x);
   fChain->SetBranchAddress("B0ECalHits.position.y", B0ECalHits_position_y, &b_B0ECalHits_position_y);
   fChain->SetBranchAddress("B0ECalHits.position.z", B0ECalHits_position_z, &b_B0ECalHits_position_z);
   fChain->SetBranchAddress("B0ECalHits.contributions_begin", B0ECalHits_contributions_begin, &b_B0ECalHits_contributions_begin);
   fChain->SetBranchAddress("B0ECalHits.contributions_end", B0ECalHits_contributions_end, &b_B0ECalHits_contributions_end);
   fChain->SetBranchAddress("_B0ECalHits_contributions", &_B0ECalHits_contributions_, &b__B0ECalHits_contributions_);
   fChain->SetBranchAddress("_B0ECalHits_contributions.index", _B0ECalHits_contributions_index, &b__B0ECalHits_contributions_index);
   fChain->SetBranchAddress("_B0ECalHits_contributions.collectionID", _B0ECalHits_contributions_collectionID, &b__B0ECalHits_contributions_collectionID);
   fChain->SetBranchAddress("B0ECalHitsContributions", &B0ECalHitsContributions_, &b_B0ECalHitsContributions_);
   fChain->SetBranchAddress("B0ECalHitsContributions.PDG", B0ECalHitsContributions_PDG, &b_B0ECalHitsContributions_PDG);
   fChain->SetBranchAddress("B0ECalHitsContributions.energy", B0ECalHitsContributions_energy, &b_B0ECalHitsContributions_energy);
   fChain->SetBranchAddress("B0ECalHitsContributions.time", B0ECalHitsContributions_time, &b_B0ECalHitsContributions_time);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepPosition.x", B0ECalHitsContributions_stepPosition_x, &b_B0ECalHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepPosition.y", B0ECalHitsContributions_stepPosition_y, &b_B0ECalHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("B0ECalHitsContributions.stepPosition.z", B0ECalHitsContributions_stepPosition_z, &b_B0ECalHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_B0ECalHitsContributions_particle", &_B0ECalHitsContributions_particle_, &b__B0ECalHitsContributions_particle_);
   fChain->SetBranchAddress("_B0ECalHitsContributions_particle.index", _B0ECalHitsContributions_particle_index, &b__B0ECalHitsContributions_particle_index);
   fChain->SetBranchAddress("_B0ECalHitsContributions_particle.collectionID", _B0ECalHitsContributions_particle_collectionID, &b__B0ECalHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("B0TrackerHits", &B0TrackerHits_, &b_B0TrackerHits_);
   fChain->SetBranchAddress("B0TrackerHits.cellID", B0TrackerHits_cellID, &b_B0TrackerHits_cellID);
   fChain->SetBranchAddress("B0TrackerHits.eDep", B0TrackerHits_eDep, &b_B0TrackerHits_eDep);
   fChain->SetBranchAddress("B0TrackerHits.time", B0TrackerHits_time, &b_B0TrackerHits_time);
   fChain->SetBranchAddress("B0TrackerHits.pathLength", B0TrackerHits_pathLength, &b_B0TrackerHits_pathLength);
   fChain->SetBranchAddress("B0TrackerHits.quality", B0TrackerHits_quality, &b_B0TrackerHits_quality);
   fChain->SetBranchAddress("B0TrackerHits.position.x", B0TrackerHits_position_x, &b_B0TrackerHits_position_x);
   fChain->SetBranchAddress("B0TrackerHits.position.y", B0TrackerHits_position_y, &b_B0TrackerHits_position_y);
   fChain->SetBranchAddress("B0TrackerHits.position.z", B0TrackerHits_position_z, &b_B0TrackerHits_position_z);
   fChain->SetBranchAddress("B0TrackerHits.momentum.x", B0TrackerHits_momentum_x, &b_B0TrackerHits_momentum_x);
   fChain->SetBranchAddress("B0TrackerHits.momentum.y", B0TrackerHits_momentum_y, &b_B0TrackerHits_momentum_y);
   fChain->SetBranchAddress("B0TrackerHits.momentum.z", B0TrackerHits_momentum_z, &b_B0TrackerHits_momentum_z);
   fChain->SetBranchAddress("_B0TrackerHits_particle", &_B0TrackerHits_particle_, &b__B0TrackerHits_particle_);
   fChain->SetBranchAddress("_B0TrackerHits_particle.index", _B0TrackerHits_particle_index, &b__B0TrackerHits_particle_index);
   fChain->SetBranchAddress("_B0TrackerHits_particle.collectionID", _B0TrackerHits_particle_collectionID, &b__B0TrackerHits_particle_collectionID);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits", &BackwardMPGDEndcapHits_, &b_BackwardMPGDEndcapHits_);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.cellID", BackwardMPGDEndcapHits_cellID, &b_BackwardMPGDEndcapHits_cellID);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.eDep", BackwardMPGDEndcapHits_eDep, &b_BackwardMPGDEndcapHits_eDep);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.time", BackwardMPGDEndcapHits_time, &b_BackwardMPGDEndcapHits_time);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.pathLength", BackwardMPGDEndcapHits_pathLength, &b_BackwardMPGDEndcapHits_pathLength);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.quality", BackwardMPGDEndcapHits_quality, &b_BackwardMPGDEndcapHits_quality);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.position.x", BackwardMPGDEndcapHits_position_x, &b_BackwardMPGDEndcapHits_position_x);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.position.y", BackwardMPGDEndcapHits_position_y, &b_BackwardMPGDEndcapHits_position_y);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.position.z", BackwardMPGDEndcapHits_position_z, &b_BackwardMPGDEndcapHits_position_z);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.momentum.x", BackwardMPGDEndcapHits_momentum_x, &b_BackwardMPGDEndcapHits_momentum_x);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.momentum.y", BackwardMPGDEndcapHits_momentum_y, &b_BackwardMPGDEndcapHits_momentum_y);
   fChain->SetBranchAddress("BackwardMPGDEndcapHits.momentum.z", BackwardMPGDEndcapHits_momentum_z, &b_BackwardMPGDEndcapHits_momentum_z);
   fChain->SetBranchAddress("_BackwardMPGDEndcapHits_particle", &_BackwardMPGDEndcapHits_particle_, &b__BackwardMPGDEndcapHits_particle_);
   fChain->SetBranchAddress("_BackwardMPGDEndcapHits_particle.index", _BackwardMPGDEndcapHits_particle_index, &b__BackwardMPGDEndcapHits_particle_index);
   fChain->SetBranchAddress("_BackwardMPGDEndcapHits_particle.collectionID", _BackwardMPGDEndcapHits_particle_collectionID, &b__BackwardMPGDEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("DIRCBarHits", &DIRCBarHits_, &b_DIRCBarHits_);
   fChain->SetBranchAddress("DIRCBarHits.cellID", DIRCBarHits_cellID, &b_DIRCBarHits_cellID);
   fChain->SetBranchAddress("DIRCBarHits.eDep", DIRCBarHits_eDep, &b_DIRCBarHits_eDep);
   fChain->SetBranchAddress("DIRCBarHits.time", DIRCBarHits_time, &b_DIRCBarHits_time);
   fChain->SetBranchAddress("DIRCBarHits.pathLength", DIRCBarHits_pathLength, &b_DIRCBarHits_pathLength);
   fChain->SetBranchAddress("DIRCBarHits.quality", DIRCBarHits_quality, &b_DIRCBarHits_quality);
   fChain->SetBranchAddress("DIRCBarHits.position.x", DIRCBarHits_position_x, &b_DIRCBarHits_position_x);
   fChain->SetBranchAddress("DIRCBarHits.position.y", DIRCBarHits_position_y, &b_DIRCBarHits_position_y);
   fChain->SetBranchAddress("DIRCBarHits.position.z", DIRCBarHits_position_z, &b_DIRCBarHits_position_z);
   fChain->SetBranchAddress("DIRCBarHits.momentum.x", DIRCBarHits_momentum_x, &b_DIRCBarHits_momentum_x);
   fChain->SetBranchAddress("DIRCBarHits.momentum.y", DIRCBarHits_momentum_y, &b_DIRCBarHits_momentum_y);
   fChain->SetBranchAddress("DIRCBarHits.momentum.z", DIRCBarHits_momentum_z, &b_DIRCBarHits_momentum_z);
   fChain->SetBranchAddress("_DIRCBarHits_particle", &_DIRCBarHits_particle_, &b__DIRCBarHits_particle_);
   fChain->SetBranchAddress("_DIRCBarHits_particle.index", _DIRCBarHits_particle_index, &b__DIRCBarHits_particle_index);
   fChain->SetBranchAddress("_DIRCBarHits_particle.collectionID", _DIRCBarHits_particle_collectionID, &b__DIRCBarHits_particle_collectionID);
   fChain->SetBranchAddress("DRICHHits", &DRICHHits_, &b_DRICHHits_);
   fChain->SetBranchAddress("DRICHHits.cellID", DRICHHits_cellID, &b_DRICHHits_cellID);
   fChain->SetBranchAddress("DRICHHits.eDep", DRICHHits_eDep, &b_DRICHHits_eDep);
   fChain->SetBranchAddress("DRICHHits.time", DRICHHits_time, &b_DRICHHits_time);
   fChain->SetBranchAddress("DRICHHits.pathLength", DRICHHits_pathLength, &b_DRICHHits_pathLength);
   fChain->SetBranchAddress("DRICHHits.quality", DRICHHits_quality, &b_DRICHHits_quality);
   fChain->SetBranchAddress("DRICHHits.position.x", DRICHHits_position_x, &b_DRICHHits_position_x);
   fChain->SetBranchAddress("DRICHHits.position.y", DRICHHits_position_y, &b_DRICHHits_position_y);
   fChain->SetBranchAddress("DRICHHits.position.z", DRICHHits_position_z, &b_DRICHHits_position_z);
   fChain->SetBranchAddress("DRICHHits.momentum.x", DRICHHits_momentum_x, &b_DRICHHits_momentum_x);
   fChain->SetBranchAddress("DRICHHits.momentum.y", DRICHHits_momentum_y, &b_DRICHHits_momentum_y);
   fChain->SetBranchAddress("DRICHHits.momentum.z", DRICHHits_momentum_z, &b_DRICHHits_momentum_z);
   fChain->SetBranchAddress("_DRICHHits_particle", &_DRICHHits_particle_, &b__DRICHHits_particle_);
   fChain->SetBranchAddress("_DRICHHits_particle.index", _DRICHHits_particle_index, &b__DRICHHits_particle_index);
   fChain->SetBranchAddress("_DRICHHits_particle.collectionID", _DRICHHits_particle_collectionID, &b__DRICHHits_particle_collectionID);
   fChain->SetBranchAddress("EcalBarrelImagingHits", &EcalBarrelImagingHits_, &b_EcalBarrelImagingHits_);
   fChain->SetBranchAddress("EcalBarrelImagingHits.cellID", EcalBarrelImagingHits_cellID, &b_EcalBarrelImagingHits_cellID);
   fChain->SetBranchAddress("EcalBarrelImagingHits.energy", EcalBarrelImagingHits_energy, &b_EcalBarrelImagingHits_energy);
   fChain->SetBranchAddress("EcalBarrelImagingHits.position.x", EcalBarrelImagingHits_position_x, &b_EcalBarrelImagingHits_position_x);
   fChain->SetBranchAddress("EcalBarrelImagingHits.position.y", EcalBarrelImagingHits_position_y, &b_EcalBarrelImagingHits_position_y);
   fChain->SetBranchAddress("EcalBarrelImagingHits.position.z", EcalBarrelImagingHits_position_z, &b_EcalBarrelImagingHits_position_z);
   fChain->SetBranchAddress("EcalBarrelImagingHits.contributions_begin", EcalBarrelImagingHits_contributions_begin, &b_EcalBarrelImagingHits_contributions_begin);
   fChain->SetBranchAddress("EcalBarrelImagingHits.contributions_end", EcalBarrelImagingHits_contributions_end, &b_EcalBarrelImagingHits_contributions_end);
   fChain->SetBranchAddress("_EcalBarrelImagingHits_contributions", &_EcalBarrelImagingHits_contributions_, &b__EcalBarrelImagingHits_contributions_);
   fChain->SetBranchAddress("_EcalBarrelImagingHits_contributions.index", _EcalBarrelImagingHits_contributions_index, &b__EcalBarrelImagingHits_contributions_index);
   fChain->SetBranchAddress("_EcalBarrelImagingHits_contributions.collectionID", _EcalBarrelImagingHits_contributions_collectionID, &b__EcalBarrelImagingHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions", &EcalBarrelImagingHitsContributions_, &b_EcalBarrelImagingHitsContributions_);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.PDG", EcalBarrelImagingHitsContributions_PDG, &b_EcalBarrelImagingHitsContributions_PDG);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.energy", EcalBarrelImagingHitsContributions_energy, &b_EcalBarrelImagingHitsContributions_energy);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.time", EcalBarrelImagingHitsContributions_time, &b_EcalBarrelImagingHitsContributions_time);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepPosition.x", EcalBarrelImagingHitsContributions_stepPosition_x, &b_EcalBarrelImagingHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepPosition.y", EcalBarrelImagingHitsContributions_stepPosition_y, &b_EcalBarrelImagingHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalBarrelImagingHitsContributions.stepPosition.z", EcalBarrelImagingHitsContributions_stepPosition_z, &b_EcalBarrelImagingHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalBarrelImagingHitsContributions_particle", &_EcalBarrelImagingHitsContributions_particle_, &b__EcalBarrelImagingHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalBarrelImagingHitsContributions_particle.index", _EcalBarrelImagingHitsContributions_particle_index, &b__EcalBarrelImagingHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalBarrelImagingHitsContributions_particle.collectionID", _EcalBarrelImagingHitsContributions_particle_collectionID, &b__EcalBarrelImagingHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalBarrelScFiHits", &EcalBarrelScFiHits_, &b_EcalBarrelScFiHits_);
   fChain->SetBranchAddress("EcalBarrelScFiHits.cellID", EcalBarrelScFiHits_cellID, &b_EcalBarrelScFiHits_cellID);
   fChain->SetBranchAddress("EcalBarrelScFiHits.energy", EcalBarrelScFiHits_energy, &b_EcalBarrelScFiHits_energy);
   fChain->SetBranchAddress("EcalBarrelScFiHits.position.x", EcalBarrelScFiHits_position_x, &b_EcalBarrelScFiHits_position_x);
   fChain->SetBranchAddress("EcalBarrelScFiHits.position.y", EcalBarrelScFiHits_position_y, &b_EcalBarrelScFiHits_position_y);
   fChain->SetBranchAddress("EcalBarrelScFiHits.position.z", EcalBarrelScFiHits_position_z, &b_EcalBarrelScFiHits_position_z);
   fChain->SetBranchAddress("EcalBarrelScFiHits.contributions_begin", EcalBarrelScFiHits_contributions_begin, &b_EcalBarrelScFiHits_contributions_begin);
   fChain->SetBranchAddress("EcalBarrelScFiHits.contributions_end", EcalBarrelScFiHits_contributions_end, &b_EcalBarrelScFiHits_contributions_end);
   fChain->SetBranchAddress("_EcalBarrelScFiHits_contributions", &_EcalBarrelScFiHits_contributions_, &b__EcalBarrelScFiHits_contributions_);
   fChain->SetBranchAddress("_EcalBarrelScFiHits_contributions.index", _EcalBarrelScFiHits_contributions_index, &b__EcalBarrelScFiHits_contributions_index);
   fChain->SetBranchAddress("_EcalBarrelScFiHits_contributions.collectionID", _EcalBarrelScFiHits_contributions_collectionID, &b__EcalBarrelScFiHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions", &EcalBarrelScFiHitsContributions_, &b_EcalBarrelScFiHitsContributions_);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.PDG", EcalBarrelScFiHitsContributions_PDG, &b_EcalBarrelScFiHitsContributions_PDG);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.energy", EcalBarrelScFiHitsContributions_energy, &b_EcalBarrelScFiHitsContributions_energy);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.time", EcalBarrelScFiHitsContributions_time, &b_EcalBarrelScFiHitsContributions_time);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepPosition.x", EcalBarrelScFiHitsContributions_stepPosition_x, &b_EcalBarrelScFiHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepPosition.y", EcalBarrelScFiHitsContributions_stepPosition_y, &b_EcalBarrelScFiHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalBarrelScFiHitsContributions.stepPosition.z", EcalBarrelScFiHitsContributions_stepPosition_z, &b_EcalBarrelScFiHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalBarrelScFiHitsContributions_particle", &_EcalBarrelScFiHitsContributions_particle_, &b__EcalBarrelScFiHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalBarrelScFiHitsContributions_particle.index", _EcalBarrelScFiHitsContributions_particle_index, &b__EcalBarrelScFiHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalBarrelScFiHitsContributions_particle.collectionID", _EcalBarrelScFiHitsContributions_particle_collectionID, &b__EcalBarrelScFiHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalEndcapNHits", &EcalEndcapNHits_, &b_EcalEndcapNHits_);
   fChain->SetBranchAddress("EcalEndcapNHits.cellID", EcalEndcapNHits_cellID, &b_EcalEndcapNHits_cellID);
   fChain->SetBranchAddress("EcalEndcapNHits.energy", EcalEndcapNHits_energy, &b_EcalEndcapNHits_energy);
   fChain->SetBranchAddress("EcalEndcapNHits.position.x", EcalEndcapNHits_position_x, &b_EcalEndcapNHits_position_x);
   fChain->SetBranchAddress("EcalEndcapNHits.position.y", EcalEndcapNHits_position_y, &b_EcalEndcapNHits_position_y);
   fChain->SetBranchAddress("EcalEndcapNHits.position.z", EcalEndcapNHits_position_z, &b_EcalEndcapNHits_position_z);
   fChain->SetBranchAddress("EcalEndcapNHits.contributions_begin", EcalEndcapNHits_contributions_begin, &b_EcalEndcapNHits_contributions_begin);
   fChain->SetBranchAddress("EcalEndcapNHits.contributions_end", EcalEndcapNHits_contributions_end, &b_EcalEndcapNHits_contributions_end);
   fChain->SetBranchAddress("_EcalEndcapNHits_contributions", &_EcalEndcapNHits_contributions_, &b__EcalEndcapNHits_contributions_);
   fChain->SetBranchAddress("_EcalEndcapNHits_contributions.index", _EcalEndcapNHits_contributions_index, &b__EcalEndcapNHits_contributions_index);
   fChain->SetBranchAddress("_EcalEndcapNHits_contributions.collectionID", _EcalEndcapNHits_contributions_collectionID, &b__EcalEndcapNHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions", &EcalEndcapNHitsContributions_, &b_EcalEndcapNHitsContributions_);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.PDG", EcalEndcapNHitsContributions_PDG, &b_EcalEndcapNHitsContributions_PDG);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.energy", EcalEndcapNHitsContributions_energy, &b_EcalEndcapNHitsContributions_energy);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.time", EcalEndcapNHitsContributions_time, &b_EcalEndcapNHitsContributions_time);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepPosition.x", EcalEndcapNHitsContributions_stepPosition_x, &b_EcalEndcapNHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepPosition.y", EcalEndcapNHitsContributions_stepPosition_y, &b_EcalEndcapNHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalEndcapNHitsContributions.stepPosition.z", EcalEndcapNHitsContributions_stepPosition_z, &b_EcalEndcapNHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalEndcapNHitsContributions_particle", &_EcalEndcapNHitsContributions_particle_, &b__EcalEndcapNHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalEndcapNHitsContributions_particle.index", _EcalEndcapNHitsContributions_particle_index, &b__EcalEndcapNHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalEndcapNHitsContributions_particle.collectionID", _EcalEndcapNHitsContributions_particle_collectionID, &b__EcalEndcapNHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalEndcapPHits", &EcalEndcapPHits_, &b_EcalEndcapPHits_);
   fChain->SetBranchAddress("EcalEndcapPHits.cellID", EcalEndcapPHits_cellID, &b_EcalEndcapPHits_cellID);
   fChain->SetBranchAddress("EcalEndcapPHits.energy", EcalEndcapPHits_energy, &b_EcalEndcapPHits_energy);
   fChain->SetBranchAddress("EcalEndcapPHits.position.x", EcalEndcapPHits_position_x, &b_EcalEndcapPHits_position_x);
   fChain->SetBranchAddress("EcalEndcapPHits.position.y", EcalEndcapPHits_position_y, &b_EcalEndcapPHits_position_y);
   fChain->SetBranchAddress("EcalEndcapPHits.position.z", EcalEndcapPHits_position_z, &b_EcalEndcapPHits_position_z);
   fChain->SetBranchAddress("EcalEndcapPHits.contributions_begin", EcalEndcapPHits_contributions_begin, &b_EcalEndcapPHits_contributions_begin);
   fChain->SetBranchAddress("EcalEndcapPHits.contributions_end", EcalEndcapPHits_contributions_end, &b_EcalEndcapPHits_contributions_end);
   fChain->SetBranchAddress("_EcalEndcapPHits_contributions", &_EcalEndcapPHits_contributions_, &b__EcalEndcapPHits_contributions_);
   fChain->SetBranchAddress("_EcalEndcapPHits_contributions.index", _EcalEndcapPHits_contributions_index, &b__EcalEndcapPHits_contributions_index);
   fChain->SetBranchAddress("_EcalEndcapPHits_contributions.collectionID", _EcalEndcapPHits_contributions_collectionID, &b__EcalEndcapPHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions", &EcalEndcapPHitsContributions_, &b_EcalEndcapPHitsContributions_);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.PDG", EcalEndcapPHitsContributions_PDG, &b_EcalEndcapPHitsContributions_PDG);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.energy", EcalEndcapPHitsContributions_energy, &b_EcalEndcapPHitsContributions_energy);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.time", EcalEndcapPHitsContributions_time, &b_EcalEndcapPHitsContributions_time);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepPosition.x", EcalEndcapPHitsContributions_stepPosition_x, &b_EcalEndcapPHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepPosition.y", EcalEndcapPHitsContributions_stepPosition_y, &b_EcalEndcapPHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalEndcapPHitsContributions.stepPosition.z", EcalEndcapPHitsContributions_stepPosition_z, &b_EcalEndcapPHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalEndcapPHitsContributions_particle", &_EcalEndcapPHitsContributions_particle_, &b__EcalEndcapPHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalEndcapPHitsContributions_particle.index", _EcalEndcapPHitsContributions_particle_index, &b__EcalEndcapPHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalEndcapPHitsContributions_particle.collectionID", _EcalEndcapPHitsContributions_particle_collectionID, &b__EcalEndcapPHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalEndcapPInsertHits", &EcalEndcapPInsertHits_, &b_EcalEndcapPInsertHits_);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.cellID", EcalEndcapPInsertHits_cellID, &b_EcalEndcapPInsertHits_cellID);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.energy", EcalEndcapPInsertHits_energy, &b_EcalEndcapPInsertHits_energy);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.position.x", EcalEndcapPInsertHits_position_x, &b_EcalEndcapPInsertHits_position_x);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.position.y", EcalEndcapPInsertHits_position_y, &b_EcalEndcapPInsertHits_position_y);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.position.z", EcalEndcapPInsertHits_position_z, &b_EcalEndcapPInsertHits_position_z);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.contributions_begin", EcalEndcapPInsertHits_contributions_begin, &b_EcalEndcapPInsertHits_contributions_begin);
   fChain->SetBranchAddress("EcalEndcapPInsertHits.contributions_end", EcalEndcapPInsertHits_contributions_end, &b_EcalEndcapPInsertHits_contributions_end);
   fChain->SetBranchAddress("_EcalEndcapPInsertHits_contributions", &_EcalEndcapPInsertHits_contributions_, &b__EcalEndcapPInsertHits_contributions_);
   fChain->SetBranchAddress("_EcalEndcapPInsertHits_contributions.index", _EcalEndcapPInsertHits_contributions_index, &b__EcalEndcapPInsertHits_contributions_index);
   fChain->SetBranchAddress("_EcalEndcapPInsertHits_contributions.collectionID", _EcalEndcapPInsertHits_contributions_collectionID, &b__EcalEndcapPInsertHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions", &EcalEndcapPInsertHitsContributions_, &b_EcalEndcapPInsertHitsContributions_);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions.PDG", EcalEndcapPInsertHitsContributions_PDG, &b_EcalEndcapPInsertHitsContributions_PDG);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions.energy", EcalEndcapPInsertHitsContributions_energy, &b_EcalEndcapPInsertHitsContributions_energy);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions.time", EcalEndcapPInsertHitsContributions_time, &b_EcalEndcapPInsertHitsContributions_time);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions.stepPosition.x", EcalEndcapPInsertHitsContributions_stepPosition_x, &b_EcalEndcapPInsertHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions.stepPosition.y", EcalEndcapPInsertHitsContributions_stepPosition_y, &b_EcalEndcapPInsertHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalEndcapPInsertHitsContributions.stepPosition.z", EcalEndcapPInsertHitsContributions_stepPosition_z, &b_EcalEndcapPInsertHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalEndcapPInsertHitsContributions_particle", &_EcalEndcapPInsertHitsContributions_particle_, &b__EcalEndcapPInsertHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalEndcapPInsertHitsContributions_particle.index", _EcalEndcapPInsertHitsContributions_particle_index, &b__EcalEndcapPInsertHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalEndcapPInsertHitsContributions_particle.collectionID", _EcalEndcapPInsertHitsContributions_particle_collectionID, &b__EcalEndcapPInsertHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalFarForwardZDCHits", &EcalFarForwardZDCHits_, &b_EcalFarForwardZDCHits_);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.cellID", EcalFarForwardZDCHits_cellID, &b_EcalFarForwardZDCHits_cellID);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.energy", EcalFarForwardZDCHits_energy, &b_EcalFarForwardZDCHits_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.position.x", EcalFarForwardZDCHits_position_x, &b_EcalFarForwardZDCHits_position_x);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.position.y", EcalFarForwardZDCHits_position_y, &b_EcalFarForwardZDCHits_position_y);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.position.z", EcalFarForwardZDCHits_position_z, &b_EcalFarForwardZDCHits_position_z);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.contributions_begin", EcalFarForwardZDCHits_contributions_begin, &b_EcalFarForwardZDCHits_contributions_begin);
   fChain->SetBranchAddress("EcalFarForwardZDCHits.contributions_end", EcalFarForwardZDCHits_contributions_end, &b_EcalFarForwardZDCHits_contributions_end);
   fChain->SetBranchAddress("_EcalFarForwardZDCHits_contributions", &_EcalFarForwardZDCHits_contributions_, &b__EcalFarForwardZDCHits_contributions_);
   fChain->SetBranchAddress("_EcalFarForwardZDCHits_contributions.index", _EcalFarForwardZDCHits_contributions_index, &b__EcalFarForwardZDCHits_contributions_index);
   fChain->SetBranchAddress("_EcalFarForwardZDCHits_contributions.collectionID", _EcalFarForwardZDCHits_contributions_collectionID, &b__EcalFarForwardZDCHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions", &EcalFarForwardZDCHitsContributions_, &b_EcalFarForwardZDCHitsContributions_);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.PDG", EcalFarForwardZDCHitsContributions_PDG, &b_EcalFarForwardZDCHitsContributions_PDG);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.energy", EcalFarForwardZDCHitsContributions_energy, &b_EcalFarForwardZDCHitsContributions_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.time", EcalFarForwardZDCHitsContributions_time, &b_EcalFarForwardZDCHitsContributions_time);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepPosition.x", EcalFarForwardZDCHitsContributions_stepPosition_x, &b_EcalFarForwardZDCHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepPosition.y", EcalFarForwardZDCHitsContributions_stepPosition_y, &b_EcalFarForwardZDCHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalFarForwardZDCHitsContributions.stepPosition.z", EcalFarForwardZDCHitsContributions_stepPosition_z, &b_EcalFarForwardZDCHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalFarForwardZDCHitsContributions_particle", &_EcalFarForwardZDCHitsContributions_particle_, &b__EcalFarForwardZDCHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalFarForwardZDCHitsContributions_particle.index", _EcalFarForwardZDCHitsContributions_particle_index, &b__EcalFarForwardZDCHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalFarForwardZDCHitsContributions_particle.collectionID", _EcalFarForwardZDCHitsContributions_particle_collectionID, &b__EcalFarForwardZDCHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EcalLumiSpecHits", &EcalLumiSpecHits_, &b_EcalLumiSpecHits_);
   fChain->SetBranchAddress("EcalLumiSpecHits.cellID", &EcalLumiSpecHits_cellID, &b_EcalLumiSpecHits_cellID);
   fChain->SetBranchAddress("EcalLumiSpecHits.energy", &EcalLumiSpecHits_energy, &b_EcalLumiSpecHits_energy);
   fChain->SetBranchAddress("EcalLumiSpecHits.position.x", &EcalLumiSpecHits_position_x, &b_EcalLumiSpecHits_position_x);
   fChain->SetBranchAddress("EcalLumiSpecHits.position.y", &EcalLumiSpecHits_position_y, &b_EcalLumiSpecHits_position_y);
   fChain->SetBranchAddress("EcalLumiSpecHits.position.z", &EcalLumiSpecHits_position_z, &b_EcalLumiSpecHits_position_z);
   fChain->SetBranchAddress("EcalLumiSpecHits.contributions_begin", &EcalLumiSpecHits_contributions_begin, &b_EcalLumiSpecHits_contributions_begin);
   fChain->SetBranchAddress("EcalLumiSpecHits.contributions_end", &EcalLumiSpecHits_contributions_end, &b_EcalLumiSpecHits_contributions_end);
   fChain->SetBranchAddress("_EcalLumiSpecHits_contributions", &_EcalLumiSpecHits_contributions_, &b__EcalLumiSpecHits_contributions_);
   fChain->SetBranchAddress("_EcalLumiSpecHits_contributions.index", &_EcalLumiSpecHits_contributions_index, &b__EcalLumiSpecHits_contributions_index);
   fChain->SetBranchAddress("_EcalLumiSpecHits_contributions.collectionID", &_EcalLumiSpecHits_contributions_collectionID, &b__EcalLumiSpecHits_contributions_collectionID);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions", &EcalLumiSpecHitsContributions_, &b_EcalLumiSpecHitsContributions_);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.PDG", &EcalLumiSpecHitsContributions_PDG, &b_EcalLumiSpecHitsContributions_PDG);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.energy", &EcalLumiSpecHitsContributions_energy, &b_EcalLumiSpecHitsContributions_energy);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.time", &EcalLumiSpecHitsContributions_time, &b_EcalLumiSpecHitsContributions_time);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepPosition.x", &EcalLumiSpecHitsContributions_stepPosition_x, &b_EcalLumiSpecHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepPosition.y", &EcalLumiSpecHitsContributions_stepPosition_y, &b_EcalLumiSpecHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("EcalLumiSpecHitsContributions.stepPosition.z", &EcalLumiSpecHitsContributions_stepPosition_z, &b_EcalLumiSpecHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_EcalLumiSpecHitsContributions_particle", &_EcalLumiSpecHitsContributions_particle_, &b__EcalLumiSpecHitsContributions_particle_);
   fChain->SetBranchAddress("_EcalLumiSpecHitsContributions_particle.index", &_EcalLumiSpecHitsContributions_particle_index, &b__EcalLumiSpecHitsContributions_particle_index);
   fChain->SetBranchAddress("_EcalLumiSpecHitsContributions_particle.collectionID", &_EcalLumiSpecHitsContributions_particle_collectionID, &b__EcalLumiSpecHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("EventHeader", &EventHeader_, &b_EventHeader_);
   fChain->SetBranchAddress("EventHeader.eventNumber", EventHeader_eventNumber, &b_EventHeader_eventNumber);
   fChain->SetBranchAddress("EventHeader.runNumber", EventHeader_runNumber, &b_EventHeader_runNumber);
   fChain->SetBranchAddress("EventHeader.timeStamp", EventHeader_timeStamp, &b_EventHeader_timeStamp);
   fChain->SetBranchAddress("EventHeader.weight", EventHeader_weight, &b_EventHeader_weight);
   fChain->SetBranchAddress("EventHeader.weights_begin", EventHeader_weights_begin, &b_EventHeader_weights_begin);
   fChain->SetBranchAddress("EventHeader.weights_end", EventHeader_weights_end, &b_EventHeader_weights_end);
   fChain->SetBranchAddress("_EventHeader_weights", &_EventHeader_weights, &b__EventHeader_weights);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits", &ForwardMPGDEndcapHits_, &b_ForwardMPGDEndcapHits_);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.cellID", ForwardMPGDEndcapHits_cellID, &b_ForwardMPGDEndcapHits_cellID);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.eDep", ForwardMPGDEndcapHits_eDep, &b_ForwardMPGDEndcapHits_eDep);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.time", ForwardMPGDEndcapHits_time, &b_ForwardMPGDEndcapHits_time);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.pathLength", ForwardMPGDEndcapHits_pathLength, &b_ForwardMPGDEndcapHits_pathLength);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.quality", ForwardMPGDEndcapHits_quality, &b_ForwardMPGDEndcapHits_quality);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.position.x", ForwardMPGDEndcapHits_position_x, &b_ForwardMPGDEndcapHits_position_x);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.position.y", ForwardMPGDEndcapHits_position_y, &b_ForwardMPGDEndcapHits_position_y);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.position.z", ForwardMPGDEndcapHits_position_z, &b_ForwardMPGDEndcapHits_position_z);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.momentum.x", ForwardMPGDEndcapHits_momentum_x, &b_ForwardMPGDEndcapHits_momentum_x);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.momentum.y", ForwardMPGDEndcapHits_momentum_y, &b_ForwardMPGDEndcapHits_momentum_y);
   fChain->SetBranchAddress("ForwardMPGDEndcapHits.momentum.z", ForwardMPGDEndcapHits_momentum_z, &b_ForwardMPGDEndcapHits_momentum_z);
   fChain->SetBranchAddress("_ForwardMPGDEndcapHits_particle", &_ForwardMPGDEndcapHits_particle_, &b__ForwardMPGDEndcapHits_particle_);
   fChain->SetBranchAddress("_ForwardMPGDEndcapHits_particle.index", _ForwardMPGDEndcapHits_particle_index, &b__ForwardMPGDEndcapHits_particle_index);
   fChain->SetBranchAddress("_ForwardMPGDEndcapHits_particle.collectionID", _ForwardMPGDEndcapHits_particle_collectionID, &b__ForwardMPGDEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("ForwardOffMTrackerHits", &ForwardOffMTrackerHits_, &b_ForwardOffMTrackerHits_);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.cellID", ForwardOffMTrackerHits_cellID, &b_ForwardOffMTrackerHits_cellID);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.eDep", ForwardOffMTrackerHits_eDep, &b_ForwardOffMTrackerHits_eDep);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.time", ForwardOffMTrackerHits_time, &b_ForwardOffMTrackerHits_time);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.pathLength", ForwardOffMTrackerHits_pathLength, &b_ForwardOffMTrackerHits_pathLength);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.quality", ForwardOffMTrackerHits_quality, &b_ForwardOffMTrackerHits_quality);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.position.x", ForwardOffMTrackerHits_position_x, &b_ForwardOffMTrackerHits_position_x);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.position.y", ForwardOffMTrackerHits_position_y, &b_ForwardOffMTrackerHits_position_y);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.position.z", ForwardOffMTrackerHits_position_z, &b_ForwardOffMTrackerHits_position_z);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.momentum.x", ForwardOffMTrackerHits_momentum_x, &b_ForwardOffMTrackerHits_momentum_x);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.momentum.y", ForwardOffMTrackerHits_momentum_y, &b_ForwardOffMTrackerHits_momentum_y);
   fChain->SetBranchAddress("ForwardOffMTrackerHits.momentum.z", ForwardOffMTrackerHits_momentum_z, &b_ForwardOffMTrackerHits_momentum_z);
   fChain->SetBranchAddress("_ForwardOffMTrackerHits_particle", &_ForwardOffMTrackerHits_particle_, &b__ForwardOffMTrackerHits_particle_);
   fChain->SetBranchAddress("_ForwardOffMTrackerHits_particle.index", _ForwardOffMTrackerHits_particle_index, &b__ForwardOffMTrackerHits_particle_index);
   fChain->SetBranchAddress("_ForwardOffMTrackerHits_particle.collectionID", _ForwardOffMTrackerHits_particle_collectionID, &b__ForwardOffMTrackerHits_particle_collectionID);
   fChain->SetBranchAddress("ForwardRomanPotHits", &ForwardRomanPotHits_, &b_ForwardRomanPotHits_);
   fChain->SetBranchAddress("ForwardRomanPotHits.cellID", ForwardRomanPotHits_cellID, &b_ForwardRomanPotHits_cellID);
   fChain->SetBranchAddress("ForwardRomanPotHits.eDep", ForwardRomanPotHits_eDep, &b_ForwardRomanPotHits_eDep);
   fChain->SetBranchAddress("ForwardRomanPotHits.time", ForwardRomanPotHits_time, &b_ForwardRomanPotHits_time);
   fChain->SetBranchAddress("ForwardRomanPotHits.pathLength", ForwardRomanPotHits_pathLength, &b_ForwardRomanPotHits_pathLength);
   fChain->SetBranchAddress("ForwardRomanPotHits.quality", ForwardRomanPotHits_quality, &b_ForwardRomanPotHits_quality);
   fChain->SetBranchAddress("ForwardRomanPotHits.position.x", ForwardRomanPotHits_position_x, &b_ForwardRomanPotHits_position_x);
   fChain->SetBranchAddress("ForwardRomanPotHits.position.y", ForwardRomanPotHits_position_y, &b_ForwardRomanPotHits_position_y);
   fChain->SetBranchAddress("ForwardRomanPotHits.position.z", ForwardRomanPotHits_position_z, &b_ForwardRomanPotHits_position_z);
   fChain->SetBranchAddress("ForwardRomanPotHits.momentum.x", ForwardRomanPotHits_momentum_x, &b_ForwardRomanPotHits_momentum_x);
   fChain->SetBranchAddress("ForwardRomanPotHits.momentum.y", ForwardRomanPotHits_momentum_y, &b_ForwardRomanPotHits_momentum_y);
   fChain->SetBranchAddress("ForwardRomanPotHits.momentum.z", ForwardRomanPotHits_momentum_z, &b_ForwardRomanPotHits_momentum_z);
   fChain->SetBranchAddress("_ForwardRomanPotHits_particle", &_ForwardRomanPotHits_particle_, &b__ForwardRomanPotHits_particle_);
   fChain->SetBranchAddress("_ForwardRomanPotHits_particle.index", _ForwardRomanPotHits_particle_index, &b__ForwardRomanPotHits_particle_index);
   fChain->SetBranchAddress("_ForwardRomanPotHits_particle.collectionID", _ForwardRomanPotHits_particle_collectionID, &b__ForwardRomanPotHits_particle_collectionID);
   fChain->SetBranchAddress("HcalBarrelHits", &HcalBarrelHits_, &b_HcalBarrelHits_);
   fChain->SetBranchAddress("HcalBarrelHits.cellID", HcalBarrelHits_cellID, &b_HcalBarrelHits_cellID);
   fChain->SetBranchAddress("HcalBarrelHits.energy", HcalBarrelHits_energy, &b_HcalBarrelHits_energy);
   fChain->SetBranchAddress("HcalBarrelHits.position.x", HcalBarrelHits_position_x, &b_HcalBarrelHits_position_x);
   fChain->SetBranchAddress("HcalBarrelHits.position.y", HcalBarrelHits_position_y, &b_HcalBarrelHits_position_y);
   fChain->SetBranchAddress("HcalBarrelHits.position.z", HcalBarrelHits_position_z, &b_HcalBarrelHits_position_z);
   fChain->SetBranchAddress("HcalBarrelHits.contributions_begin", HcalBarrelHits_contributions_begin, &b_HcalBarrelHits_contributions_begin);
   fChain->SetBranchAddress("HcalBarrelHits.contributions_end", HcalBarrelHits_contributions_end, &b_HcalBarrelHits_contributions_end);
   fChain->SetBranchAddress("_HcalBarrelHits_contributions", &_HcalBarrelHits_contributions_, &b__HcalBarrelHits_contributions_);
   fChain->SetBranchAddress("_HcalBarrelHits_contributions.index", _HcalBarrelHits_contributions_index, &b__HcalBarrelHits_contributions_index);
   fChain->SetBranchAddress("_HcalBarrelHits_contributions.collectionID", _HcalBarrelHits_contributions_collectionID, &b__HcalBarrelHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalBarrelHitsContributions", &HcalBarrelHitsContributions_, &b_HcalBarrelHitsContributions_);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.PDG", HcalBarrelHitsContributions_PDG, &b_HcalBarrelHitsContributions_PDG);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.energy", HcalBarrelHitsContributions_energy, &b_HcalBarrelHitsContributions_energy);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.time", HcalBarrelHitsContributions_time, &b_HcalBarrelHitsContributions_time);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepPosition.x", HcalBarrelHitsContributions_stepPosition_x, &b_HcalBarrelHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepPosition.y", HcalBarrelHitsContributions_stepPosition_y, &b_HcalBarrelHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalBarrelHitsContributions.stepPosition.z", HcalBarrelHitsContributions_stepPosition_z, &b_HcalBarrelHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_HcalBarrelHitsContributions_particle", &_HcalBarrelHitsContributions_particle_, &b__HcalBarrelHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalBarrelHitsContributions_particle.index", _HcalBarrelHitsContributions_particle_index, &b__HcalBarrelHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalBarrelHitsContributions_particle.collectionID", _HcalBarrelHitsContributions_particle_collectionID, &b__HcalBarrelHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("HcalEndcapNHits", &HcalEndcapNHits_, &b_HcalEndcapNHits_);
   fChain->SetBranchAddress("HcalEndcapNHits.cellID", HcalEndcapNHits_cellID, &b_HcalEndcapNHits_cellID);
   fChain->SetBranchAddress("HcalEndcapNHits.energy", HcalEndcapNHits_energy, &b_HcalEndcapNHits_energy);
   fChain->SetBranchAddress("HcalEndcapNHits.position.x", HcalEndcapNHits_position_x, &b_HcalEndcapNHits_position_x);
   fChain->SetBranchAddress("HcalEndcapNHits.position.y", HcalEndcapNHits_position_y, &b_HcalEndcapNHits_position_y);
   fChain->SetBranchAddress("HcalEndcapNHits.position.z", HcalEndcapNHits_position_z, &b_HcalEndcapNHits_position_z);
   fChain->SetBranchAddress("HcalEndcapNHits.contributions_begin", HcalEndcapNHits_contributions_begin, &b_HcalEndcapNHits_contributions_begin);
   fChain->SetBranchAddress("HcalEndcapNHits.contributions_end", HcalEndcapNHits_contributions_end, &b_HcalEndcapNHits_contributions_end);
   fChain->SetBranchAddress("_HcalEndcapNHits_contributions", &_HcalEndcapNHits_contributions_, &b__HcalEndcapNHits_contributions_);
   fChain->SetBranchAddress("_HcalEndcapNHits_contributions.index", _HcalEndcapNHits_contributions_index, &b__HcalEndcapNHits_contributions_index);
   fChain->SetBranchAddress("_HcalEndcapNHits_contributions.collectionID", _HcalEndcapNHits_contributions_collectionID, &b__HcalEndcapNHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions", &HcalEndcapNHitsContributions_, &b_HcalEndcapNHitsContributions_);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.PDG", HcalEndcapNHitsContributions_PDG, &b_HcalEndcapNHitsContributions_PDG);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.energy", HcalEndcapNHitsContributions_energy, &b_HcalEndcapNHitsContributions_energy);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.time", HcalEndcapNHitsContributions_time, &b_HcalEndcapNHitsContributions_time);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepPosition.x", HcalEndcapNHitsContributions_stepPosition_x, &b_HcalEndcapNHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepPosition.y", HcalEndcapNHitsContributions_stepPosition_y, &b_HcalEndcapNHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalEndcapNHitsContributions.stepPosition.z", HcalEndcapNHitsContributions_stepPosition_z, &b_HcalEndcapNHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_HcalEndcapNHitsContributions_particle", &_HcalEndcapNHitsContributions_particle_, &b__HcalEndcapNHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalEndcapNHitsContributions_particle.index", _HcalEndcapNHitsContributions_particle_index, &b__HcalEndcapNHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalEndcapNHitsContributions_particle.collectionID", _HcalEndcapNHitsContributions_particle_collectionID, &b__HcalEndcapNHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("HcalEndcapPInsertHits", &HcalEndcapPInsertHits_, &b_HcalEndcapPInsertHits_);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.cellID", HcalEndcapPInsertHits_cellID, &b_HcalEndcapPInsertHits_cellID);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.energy", HcalEndcapPInsertHits_energy, &b_HcalEndcapPInsertHits_energy);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.position.x", HcalEndcapPInsertHits_position_x, &b_HcalEndcapPInsertHits_position_x);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.position.y", HcalEndcapPInsertHits_position_y, &b_HcalEndcapPInsertHits_position_y);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.position.z", HcalEndcapPInsertHits_position_z, &b_HcalEndcapPInsertHits_position_z);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.contributions_begin", HcalEndcapPInsertHits_contributions_begin, &b_HcalEndcapPInsertHits_contributions_begin);
   fChain->SetBranchAddress("HcalEndcapPInsertHits.contributions_end", HcalEndcapPInsertHits_contributions_end, &b_HcalEndcapPInsertHits_contributions_end);
   fChain->SetBranchAddress("_HcalEndcapPInsertHits_contributions", &_HcalEndcapPInsertHits_contributions_, &b__HcalEndcapPInsertHits_contributions_);
   fChain->SetBranchAddress("_HcalEndcapPInsertHits_contributions.index", _HcalEndcapPInsertHits_contributions_index, &b__HcalEndcapPInsertHits_contributions_index);
   fChain->SetBranchAddress("_HcalEndcapPInsertHits_contributions.collectionID", _HcalEndcapPInsertHits_contributions_collectionID, &b__HcalEndcapPInsertHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions", &HcalEndcapPInsertHitsContributions_, &b_HcalEndcapPInsertHitsContributions_);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.PDG", HcalEndcapPInsertHitsContributions_PDG, &b_HcalEndcapPInsertHitsContributions_PDG);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.energy", HcalEndcapPInsertHitsContributions_energy, &b_HcalEndcapPInsertHitsContributions_energy);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.time", HcalEndcapPInsertHitsContributions_time, &b_HcalEndcapPInsertHitsContributions_time);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepPosition.x", HcalEndcapPInsertHitsContributions_stepPosition_x, &b_HcalEndcapPInsertHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepPosition.y", HcalEndcapPInsertHitsContributions_stepPosition_y, &b_HcalEndcapPInsertHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalEndcapPInsertHitsContributions.stepPosition.z", HcalEndcapPInsertHitsContributions_stepPosition_z, &b_HcalEndcapPInsertHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_HcalEndcapPInsertHitsContributions_particle", &_HcalEndcapPInsertHitsContributions_particle_, &b__HcalEndcapPInsertHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalEndcapPInsertHitsContributions_particle.index", _HcalEndcapPInsertHitsContributions_particle_index, &b__HcalEndcapPInsertHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalEndcapPInsertHitsContributions_particle.collectionID", _HcalEndcapPInsertHitsContributions_particle_collectionID, &b__HcalEndcapPInsertHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("HcalFarForwardZDCHits", &HcalFarForwardZDCHits_, &b_HcalFarForwardZDCHits_);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.cellID", HcalFarForwardZDCHits_cellID, &b_HcalFarForwardZDCHits_cellID);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.energy", HcalFarForwardZDCHits_energy, &b_HcalFarForwardZDCHits_energy);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.position.x", HcalFarForwardZDCHits_position_x, &b_HcalFarForwardZDCHits_position_x);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.position.y", HcalFarForwardZDCHits_position_y, &b_HcalFarForwardZDCHits_position_y);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.position.z", HcalFarForwardZDCHits_position_z, &b_HcalFarForwardZDCHits_position_z);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.contributions_begin", HcalFarForwardZDCHits_contributions_begin, &b_HcalFarForwardZDCHits_contributions_begin);
   fChain->SetBranchAddress("HcalFarForwardZDCHits.contributions_end", HcalFarForwardZDCHits_contributions_end, &b_HcalFarForwardZDCHits_contributions_end);
   fChain->SetBranchAddress("_HcalFarForwardZDCHits_contributions", &_HcalFarForwardZDCHits_contributions_, &b__HcalFarForwardZDCHits_contributions_);
   fChain->SetBranchAddress("_HcalFarForwardZDCHits_contributions.index", _HcalFarForwardZDCHits_contributions_index, &b__HcalFarForwardZDCHits_contributions_index);
   fChain->SetBranchAddress("_HcalFarForwardZDCHits_contributions.collectionID", _HcalFarForwardZDCHits_contributions_collectionID, &b__HcalFarForwardZDCHits_contributions_collectionID);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions", &HcalFarForwardZDCHitsContributions_, &b_HcalFarForwardZDCHitsContributions_);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.PDG", HcalFarForwardZDCHitsContributions_PDG, &b_HcalFarForwardZDCHitsContributions_PDG);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.energy", HcalFarForwardZDCHitsContributions_energy, &b_HcalFarForwardZDCHitsContributions_energy);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.time", HcalFarForwardZDCHitsContributions_time, &b_HcalFarForwardZDCHitsContributions_time);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepPosition.x", HcalFarForwardZDCHitsContributions_stepPosition_x, &b_HcalFarForwardZDCHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepPosition.y", HcalFarForwardZDCHitsContributions_stepPosition_y, &b_HcalFarForwardZDCHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("HcalFarForwardZDCHitsContributions.stepPosition.z", HcalFarForwardZDCHitsContributions_stepPosition_z, &b_HcalFarForwardZDCHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_HcalFarForwardZDCHitsContributions_particle", &_HcalFarForwardZDCHitsContributions_particle_, &b__HcalFarForwardZDCHitsContributions_particle_);
   fChain->SetBranchAddress("_HcalFarForwardZDCHitsContributions_particle.index", _HcalFarForwardZDCHitsContributions_particle_index, &b__HcalFarForwardZDCHitsContributions_particle_index);
   fChain->SetBranchAddress("_HcalFarForwardZDCHitsContributions_particle.collectionID", _HcalFarForwardZDCHitsContributions_particle_collectionID, &b__HcalFarForwardZDCHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("LFHCALHits", &LFHCALHits_, &b_LFHCALHits_);
   fChain->SetBranchAddress("LFHCALHits.cellID", LFHCALHits_cellID, &b_LFHCALHits_cellID);
   fChain->SetBranchAddress("LFHCALHits.energy", LFHCALHits_energy, &b_LFHCALHits_energy);
   fChain->SetBranchAddress("LFHCALHits.position.x", LFHCALHits_position_x, &b_LFHCALHits_position_x);
   fChain->SetBranchAddress("LFHCALHits.position.y", LFHCALHits_position_y, &b_LFHCALHits_position_y);
   fChain->SetBranchAddress("LFHCALHits.position.z", LFHCALHits_position_z, &b_LFHCALHits_position_z);
   fChain->SetBranchAddress("LFHCALHits.contributions_begin", LFHCALHits_contributions_begin, &b_LFHCALHits_contributions_begin);
   fChain->SetBranchAddress("LFHCALHits.contributions_end", LFHCALHits_contributions_end, &b_LFHCALHits_contributions_end);
   fChain->SetBranchAddress("_LFHCALHits_contributions", &_LFHCALHits_contributions_, &b__LFHCALHits_contributions_);
   fChain->SetBranchAddress("_LFHCALHits_contributions.index", _LFHCALHits_contributions_index, &b__LFHCALHits_contributions_index);
   fChain->SetBranchAddress("_LFHCALHits_contributions.collectionID", _LFHCALHits_contributions_collectionID, &b__LFHCALHits_contributions_collectionID);
   fChain->SetBranchAddress("LFHCALHitsContributions", &LFHCALHitsContributions_, &b_LFHCALHitsContributions_);
   fChain->SetBranchAddress("LFHCALHitsContributions.PDG", LFHCALHitsContributions_PDG, &b_LFHCALHitsContributions_PDG);
   fChain->SetBranchAddress("LFHCALHitsContributions.energy", LFHCALHitsContributions_energy, &b_LFHCALHitsContributions_energy);
   fChain->SetBranchAddress("LFHCALHitsContributions.time", LFHCALHitsContributions_time, &b_LFHCALHitsContributions_time);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepPosition.x", LFHCALHitsContributions_stepPosition_x, &b_LFHCALHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepPosition.y", LFHCALHitsContributions_stepPosition_y, &b_LFHCALHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("LFHCALHitsContributions.stepPosition.z", LFHCALHitsContributions_stepPosition_z, &b_LFHCALHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_LFHCALHitsContributions_particle", &_LFHCALHitsContributions_particle_, &b__LFHCALHitsContributions_particle_);
   fChain->SetBranchAddress("_LFHCALHitsContributions_particle.index", _LFHCALHitsContributions_particle_index, &b__LFHCALHitsContributions_particle_index);
   fChain->SetBranchAddress("_LFHCALHitsContributions_particle.collectionID", _LFHCALHitsContributions_particle_collectionID, &b__LFHCALHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("LumiDirectPCALHits", &LumiDirectPCALHits_, &b_LumiDirectPCALHits_);
   fChain->SetBranchAddress("LumiDirectPCALHits.cellID", &LumiDirectPCALHits_cellID, &b_LumiDirectPCALHits_cellID);
   fChain->SetBranchAddress("LumiDirectPCALHits.energy", &LumiDirectPCALHits_energy, &b_LumiDirectPCALHits_energy);
   fChain->SetBranchAddress("LumiDirectPCALHits.position.x", &LumiDirectPCALHits_position_x, &b_LumiDirectPCALHits_position_x);
   fChain->SetBranchAddress("LumiDirectPCALHits.position.y", &LumiDirectPCALHits_position_y, &b_LumiDirectPCALHits_position_y);
   fChain->SetBranchAddress("LumiDirectPCALHits.position.z", &LumiDirectPCALHits_position_z, &b_LumiDirectPCALHits_position_z);
   fChain->SetBranchAddress("LumiDirectPCALHits.contributions_begin", &LumiDirectPCALHits_contributions_begin, &b_LumiDirectPCALHits_contributions_begin);
   fChain->SetBranchAddress("LumiDirectPCALHits.contributions_end", &LumiDirectPCALHits_contributions_end, &b_LumiDirectPCALHits_contributions_end);
   fChain->SetBranchAddress("_LumiDirectPCALHits_contributions", &_LumiDirectPCALHits_contributions_, &b__LumiDirectPCALHits_contributions_);
   fChain->SetBranchAddress("_LumiDirectPCALHits_contributions.index", &_LumiDirectPCALHits_contributions_index, &b__LumiDirectPCALHits_contributions_index);
   fChain->SetBranchAddress("_LumiDirectPCALHits_contributions.collectionID", &_LumiDirectPCALHits_contributions_collectionID, &b__LumiDirectPCALHits_contributions_collectionID);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions", &LumiDirectPCALHitsContributions_, &b_LumiDirectPCALHitsContributions_);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.PDG", &LumiDirectPCALHitsContributions_PDG, &b_LumiDirectPCALHitsContributions_PDG);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.energy", &LumiDirectPCALHitsContributions_energy, &b_LumiDirectPCALHitsContributions_energy);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.time", &LumiDirectPCALHitsContributions_time, &b_LumiDirectPCALHitsContributions_time);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepPosition.x", &LumiDirectPCALHitsContributions_stepPosition_x, &b_LumiDirectPCALHitsContributions_stepPosition_x);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepPosition.y", &LumiDirectPCALHitsContributions_stepPosition_y, &b_LumiDirectPCALHitsContributions_stepPosition_y);
   fChain->SetBranchAddress("LumiDirectPCALHitsContributions.stepPosition.z", &LumiDirectPCALHitsContributions_stepPosition_z, &b_LumiDirectPCALHitsContributions_stepPosition_z);
   fChain->SetBranchAddress("_LumiDirectPCALHitsContributions_particle", &_LumiDirectPCALHitsContributions_particle_, &b__LumiDirectPCALHitsContributions_particle_);
   fChain->SetBranchAddress("_LumiDirectPCALHitsContributions_particle.index", &_LumiDirectPCALHitsContributions_particle_index, &b__LumiDirectPCALHitsContributions_particle_index);
   fChain->SetBranchAddress("_LumiDirectPCALHitsContributions_particle.collectionID", &_LumiDirectPCALHitsContributions_particle_collectionID, &b__LumiDirectPCALHitsContributions_particle_collectionID);
   fChain->SetBranchAddress("LumiSpecTrackerHits", &LumiSpecTrackerHits_, &b_LumiSpecTrackerHits_);
   fChain->SetBranchAddress("LumiSpecTrackerHits.cellID", &LumiSpecTrackerHits_cellID, &b_LumiSpecTrackerHits_cellID);
   fChain->SetBranchAddress("LumiSpecTrackerHits.eDep", &LumiSpecTrackerHits_eDep, &b_LumiSpecTrackerHits_eDep);
   fChain->SetBranchAddress("LumiSpecTrackerHits.time", &LumiSpecTrackerHits_time, &b_LumiSpecTrackerHits_time);
   fChain->SetBranchAddress("LumiSpecTrackerHits.pathLength", &LumiSpecTrackerHits_pathLength, &b_LumiSpecTrackerHits_pathLength);
   fChain->SetBranchAddress("LumiSpecTrackerHits.quality", &LumiSpecTrackerHits_quality, &b_LumiSpecTrackerHits_quality);
   fChain->SetBranchAddress("LumiSpecTrackerHits.position.x", &LumiSpecTrackerHits_position_x, &b_LumiSpecTrackerHits_position_x);
   fChain->SetBranchAddress("LumiSpecTrackerHits.position.y", &LumiSpecTrackerHits_position_y, &b_LumiSpecTrackerHits_position_y);
   fChain->SetBranchAddress("LumiSpecTrackerHits.position.z", &LumiSpecTrackerHits_position_z, &b_LumiSpecTrackerHits_position_z);
   fChain->SetBranchAddress("LumiSpecTrackerHits.momentum.x", &LumiSpecTrackerHits_momentum_x, &b_LumiSpecTrackerHits_momentum_x);
   fChain->SetBranchAddress("LumiSpecTrackerHits.momentum.y", &LumiSpecTrackerHits_momentum_y, &b_LumiSpecTrackerHits_momentum_y);
   fChain->SetBranchAddress("LumiSpecTrackerHits.momentum.z", &LumiSpecTrackerHits_momentum_z, &b_LumiSpecTrackerHits_momentum_z);
   fChain->SetBranchAddress("_LumiSpecTrackerHits_particle", &_LumiSpecTrackerHits_particle_, &b__LumiSpecTrackerHits_particle_);
   fChain->SetBranchAddress("_LumiSpecTrackerHits_particle.index", &_LumiSpecTrackerHits_particle_index, &b__LumiSpecTrackerHits_particle_index);
   fChain->SetBranchAddress("_LumiSpecTrackerHits_particle.collectionID", &_LumiSpecTrackerHits_particle_collectionID, &b__LumiSpecTrackerHits_particle_collectionID);
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
   fChain->SetBranchAddress("MCParticles.spin.x", MCParticles_spin_x, &b_MCParticles_spin_x);
   fChain->SetBranchAddress("MCParticles.spin.y", MCParticles_spin_y, &b_MCParticles_spin_y);
   fChain->SetBranchAddress("MCParticles.spin.z", MCParticles_spin_z, &b_MCParticles_spin_z);
   fChain->SetBranchAddress("MCParticles.colorFlow.a", MCParticles_colorFlow_a, &b_MCParticles_colorFlow_a);
   fChain->SetBranchAddress("MCParticles.colorFlow.b", MCParticles_colorFlow_b, &b_MCParticles_colorFlow_b);
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
   fChain->SetBranchAddress("MPGDBarrelHits", &MPGDBarrelHits_, &b_MPGDBarrelHits_);
   fChain->SetBranchAddress("MPGDBarrelHits.cellID", MPGDBarrelHits_cellID, &b_MPGDBarrelHits_cellID);
   fChain->SetBranchAddress("MPGDBarrelHits.eDep", MPGDBarrelHits_eDep, &b_MPGDBarrelHits_eDep);
   fChain->SetBranchAddress("MPGDBarrelHits.time", MPGDBarrelHits_time, &b_MPGDBarrelHits_time);
   fChain->SetBranchAddress("MPGDBarrelHits.pathLength", MPGDBarrelHits_pathLength, &b_MPGDBarrelHits_pathLength);
   fChain->SetBranchAddress("MPGDBarrelHits.quality", MPGDBarrelHits_quality, &b_MPGDBarrelHits_quality);
   fChain->SetBranchAddress("MPGDBarrelHits.position.x", MPGDBarrelHits_position_x, &b_MPGDBarrelHits_position_x);
   fChain->SetBranchAddress("MPGDBarrelHits.position.y", MPGDBarrelHits_position_y, &b_MPGDBarrelHits_position_y);
   fChain->SetBranchAddress("MPGDBarrelHits.position.z", MPGDBarrelHits_position_z, &b_MPGDBarrelHits_position_z);
   fChain->SetBranchAddress("MPGDBarrelHits.momentum.x", MPGDBarrelHits_momentum_x, &b_MPGDBarrelHits_momentum_x);
   fChain->SetBranchAddress("MPGDBarrelHits.momentum.y", MPGDBarrelHits_momentum_y, &b_MPGDBarrelHits_momentum_y);
   fChain->SetBranchAddress("MPGDBarrelHits.momentum.z", MPGDBarrelHits_momentum_z, &b_MPGDBarrelHits_momentum_z);
   fChain->SetBranchAddress("_MPGDBarrelHits_particle", &_MPGDBarrelHits_particle_, &b__MPGDBarrelHits_particle_);
   fChain->SetBranchAddress("_MPGDBarrelHits_particle.index", _MPGDBarrelHits_particle_index, &b__MPGDBarrelHits_particle_index);
   fChain->SetBranchAddress("_MPGDBarrelHits_particle.collectionID", _MPGDBarrelHits_particle_collectionID, &b__MPGDBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("OuterMPGDBarrelHits", &OuterMPGDBarrelHits_, &b_OuterMPGDBarrelHits_);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.cellID", OuterMPGDBarrelHits_cellID, &b_OuterMPGDBarrelHits_cellID);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.eDep", OuterMPGDBarrelHits_eDep, &b_OuterMPGDBarrelHits_eDep);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.time", OuterMPGDBarrelHits_time, &b_OuterMPGDBarrelHits_time);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.pathLength", OuterMPGDBarrelHits_pathLength, &b_OuterMPGDBarrelHits_pathLength);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.quality", OuterMPGDBarrelHits_quality, &b_OuterMPGDBarrelHits_quality);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.position.x", OuterMPGDBarrelHits_position_x, &b_OuterMPGDBarrelHits_position_x);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.position.y", OuterMPGDBarrelHits_position_y, &b_OuterMPGDBarrelHits_position_y);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.position.z", OuterMPGDBarrelHits_position_z, &b_OuterMPGDBarrelHits_position_z);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.momentum.x", OuterMPGDBarrelHits_momentum_x, &b_OuterMPGDBarrelHits_momentum_x);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.momentum.y", OuterMPGDBarrelHits_momentum_y, &b_OuterMPGDBarrelHits_momentum_y);
   fChain->SetBranchAddress("OuterMPGDBarrelHits.momentum.z", OuterMPGDBarrelHits_momentum_z, &b_OuterMPGDBarrelHits_momentum_z);
   fChain->SetBranchAddress("_OuterMPGDBarrelHits_particle", &_OuterMPGDBarrelHits_particle_, &b__OuterMPGDBarrelHits_particle_);
   fChain->SetBranchAddress("_OuterMPGDBarrelHits_particle.index", _OuterMPGDBarrelHits_particle_index, &b__OuterMPGDBarrelHits_particle_index);
   fChain->SetBranchAddress("_OuterMPGDBarrelHits_particle.collectionID", _OuterMPGDBarrelHits_particle_collectionID, &b__OuterMPGDBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("RICHEndcapNHits", &RICHEndcapNHits_, &b_RICHEndcapNHits_);
   fChain->SetBranchAddress("RICHEndcapNHits.cellID", &RICHEndcapNHits_cellID, &b_RICHEndcapNHits_cellID);
   fChain->SetBranchAddress("RICHEndcapNHits.eDep", &RICHEndcapNHits_eDep, &b_RICHEndcapNHits_eDep);
   fChain->SetBranchAddress("RICHEndcapNHits.time", &RICHEndcapNHits_time, &b_RICHEndcapNHits_time);
   fChain->SetBranchAddress("RICHEndcapNHits.pathLength", &RICHEndcapNHits_pathLength, &b_RICHEndcapNHits_pathLength);
   fChain->SetBranchAddress("RICHEndcapNHits.quality", &RICHEndcapNHits_quality, &b_RICHEndcapNHits_quality);
   fChain->SetBranchAddress("RICHEndcapNHits.position.x", &RICHEndcapNHits_position_x, &b_RICHEndcapNHits_position_x);
   fChain->SetBranchAddress("RICHEndcapNHits.position.y", &RICHEndcapNHits_position_y, &b_RICHEndcapNHits_position_y);
   fChain->SetBranchAddress("RICHEndcapNHits.position.z", &RICHEndcapNHits_position_z, &b_RICHEndcapNHits_position_z);
   fChain->SetBranchAddress("RICHEndcapNHits.momentum.x", &RICHEndcapNHits_momentum_x, &b_RICHEndcapNHits_momentum_x);
   fChain->SetBranchAddress("RICHEndcapNHits.momentum.y", &RICHEndcapNHits_momentum_y, &b_RICHEndcapNHits_momentum_y);
   fChain->SetBranchAddress("RICHEndcapNHits.momentum.z", &RICHEndcapNHits_momentum_z, &b_RICHEndcapNHits_momentum_z);
   fChain->SetBranchAddress("_RICHEndcapNHits_particle", &_RICHEndcapNHits_particle_, &b__RICHEndcapNHits_particle_);
   fChain->SetBranchAddress("_RICHEndcapNHits_particle.index", &_RICHEndcapNHits_particle_index, &b__RICHEndcapNHits_particle_index);
   fChain->SetBranchAddress("_RICHEndcapNHits_particle.collectionID", &_RICHEndcapNHits_particle_collectionID, &b__RICHEndcapNHits_particle_collectionID);
   fChain->SetBranchAddress("SiBarrelHits", &SiBarrelHits_, &b_SiBarrelHits_);
   fChain->SetBranchAddress("SiBarrelHits.cellID", SiBarrelHits_cellID, &b_SiBarrelHits_cellID);
   fChain->SetBranchAddress("SiBarrelHits.eDep", SiBarrelHits_eDep, &b_SiBarrelHits_eDep);
   fChain->SetBranchAddress("SiBarrelHits.time", SiBarrelHits_time, &b_SiBarrelHits_time);
   fChain->SetBranchAddress("SiBarrelHits.pathLength", SiBarrelHits_pathLength, &b_SiBarrelHits_pathLength);
   fChain->SetBranchAddress("SiBarrelHits.quality", SiBarrelHits_quality, &b_SiBarrelHits_quality);
   fChain->SetBranchAddress("SiBarrelHits.position.x", SiBarrelHits_position_x, &b_SiBarrelHits_position_x);
   fChain->SetBranchAddress("SiBarrelHits.position.y", SiBarrelHits_position_y, &b_SiBarrelHits_position_y);
   fChain->SetBranchAddress("SiBarrelHits.position.z", SiBarrelHits_position_z, &b_SiBarrelHits_position_z);
   fChain->SetBranchAddress("SiBarrelHits.momentum.x", SiBarrelHits_momentum_x, &b_SiBarrelHits_momentum_x);
   fChain->SetBranchAddress("SiBarrelHits.momentum.y", SiBarrelHits_momentum_y, &b_SiBarrelHits_momentum_y);
   fChain->SetBranchAddress("SiBarrelHits.momentum.z", SiBarrelHits_momentum_z, &b_SiBarrelHits_momentum_z);
   fChain->SetBranchAddress("_SiBarrelHits_particle", &_SiBarrelHits_particle_, &b__SiBarrelHits_particle_);
   fChain->SetBranchAddress("_SiBarrelHits_particle.index", _SiBarrelHits_particle_index, &b__SiBarrelHits_particle_index);
   fChain->SetBranchAddress("_SiBarrelHits_particle.collectionID", _SiBarrelHits_particle_collectionID, &b__SiBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("TaggerTrackerHits", &TaggerTrackerHits_, &b_TaggerTrackerHits_);
   fChain->SetBranchAddress("TaggerTrackerHits.cellID", &TaggerTrackerHits_cellID, &b_TaggerTrackerHits_cellID);
   fChain->SetBranchAddress("TaggerTrackerHits.eDep", &TaggerTrackerHits_eDep, &b_TaggerTrackerHits_eDep);
   fChain->SetBranchAddress("TaggerTrackerHits.time", &TaggerTrackerHits_time, &b_TaggerTrackerHits_time);
   fChain->SetBranchAddress("TaggerTrackerHits.pathLength", &TaggerTrackerHits_pathLength, &b_TaggerTrackerHits_pathLength);
   fChain->SetBranchAddress("TaggerTrackerHits.quality", &TaggerTrackerHits_quality, &b_TaggerTrackerHits_quality);
   fChain->SetBranchAddress("TaggerTrackerHits.position.x", &TaggerTrackerHits_position_x, &b_TaggerTrackerHits_position_x);
   fChain->SetBranchAddress("TaggerTrackerHits.position.y", &TaggerTrackerHits_position_y, &b_TaggerTrackerHits_position_y);
   fChain->SetBranchAddress("TaggerTrackerHits.position.z", &TaggerTrackerHits_position_z, &b_TaggerTrackerHits_position_z);
   fChain->SetBranchAddress("TaggerTrackerHits.momentum.x", &TaggerTrackerHits_momentum_x, &b_TaggerTrackerHits_momentum_x);
   fChain->SetBranchAddress("TaggerTrackerHits.momentum.y", &TaggerTrackerHits_momentum_y, &b_TaggerTrackerHits_momentum_y);
   fChain->SetBranchAddress("TaggerTrackerHits.momentum.z", &TaggerTrackerHits_momentum_z, &b_TaggerTrackerHits_momentum_z);
   fChain->SetBranchAddress("_TaggerTrackerHits_particle", &_TaggerTrackerHits_particle_, &b__TaggerTrackerHits_particle_);
   fChain->SetBranchAddress("_TaggerTrackerHits_particle.index", &_TaggerTrackerHits_particle_index, &b__TaggerTrackerHits_particle_index);
   fChain->SetBranchAddress("_TaggerTrackerHits_particle.collectionID", &_TaggerTrackerHits_particle_collectionID, &b__TaggerTrackerHits_particle_collectionID);
   fChain->SetBranchAddress("TOFBarrelHits", &TOFBarrelHits_, &b_TOFBarrelHits_);
   fChain->SetBranchAddress("TOFBarrelHits.cellID", TOFBarrelHits_cellID, &b_TOFBarrelHits_cellID);
   fChain->SetBranchAddress("TOFBarrelHits.eDep", TOFBarrelHits_eDep, &b_TOFBarrelHits_eDep);
   fChain->SetBranchAddress("TOFBarrelHits.time", TOFBarrelHits_time, &b_TOFBarrelHits_time);
   fChain->SetBranchAddress("TOFBarrelHits.pathLength", TOFBarrelHits_pathLength, &b_TOFBarrelHits_pathLength);
   fChain->SetBranchAddress("TOFBarrelHits.quality", TOFBarrelHits_quality, &b_TOFBarrelHits_quality);
   fChain->SetBranchAddress("TOFBarrelHits.position.x", TOFBarrelHits_position_x, &b_TOFBarrelHits_position_x);
   fChain->SetBranchAddress("TOFBarrelHits.position.y", TOFBarrelHits_position_y, &b_TOFBarrelHits_position_y);
   fChain->SetBranchAddress("TOFBarrelHits.position.z", TOFBarrelHits_position_z, &b_TOFBarrelHits_position_z);
   fChain->SetBranchAddress("TOFBarrelHits.momentum.x", TOFBarrelHits_momentum_x, &b_TOFBarrelHits_momentum_x);
   fChain->SetBranchAddress("TOFBarrelHits.momentum.y", TOFBarrelHits_momentum_y, &b_TOFBarrelHits_momentum_y);
   fChain->SetBranchAddress("TOFBarrelHits.momentum.z", TOFBarrelHits_momentum_z, &b_TOFBarrelHits_momentum_z);
   fChain->SetBranchAddress("_TOFBarrelHits_particle", &_TOFBarrelHits_particle_, &b__TOFBarrelHits_particle_);
   fChain->SetBranchAddress("_TOFBarrelHits_particle.index", _TOFBarrelHits_particle_index, &b__TOFBarrelHits_particle_index);
   fChain->SetBranchAddress("_TOFBarrelHits_particle.collectionID", _TOFBarrelHits_particle_collectionID, &b__TOFBarrelHits_particle_collectionID);
   fChain->SetBranchAddress("TOFEndcapHits", &TOFEndcapHits_, &b_TOFEndcapHits_);
   fChain->SetBranchAddress("TOFEndcapHits.cellID", TOFEndcapHits_cellID, &b_TOFEndcapHits_cellID);
   fChain->SetBranchAddress("TOFEndcapHits.eDep", TOFEndcapHits_eDep, &b_TOFEndcapHits_eDep);
   fChain->SetBranchAddress("TOFEndcapHits.time", TOFEndcapHits_time, &b_TOFEndcapHits_time);
   fChain->SetBranchAddress("TOFEndcapHits.pathLength", TOFEndcapHits_pathLength, &b_TOFEndcapHits_pathLength);
   fChain->SetBranchAddress("TOFEndcapHits.quality", TOFEndcapHits_quality, &b_TOFEndcapHits_quality);
   fChain->SetBranchAddress("TOFEndcapHits.position.x", TOFEndcapHits_position_x, &b_TOFEndcapHits_position_x);
   fChain->SetBranchAddress("TOFEndcapHits.position.y", TOFEndcapHits_position_y, &b_TOFEndcapHits_position_y);
   fChain->SetBranchAddress("TOFEndcapHits.position.z", TOFEndcapHits_position_z, &b_TOFEndcapHits_position_z);
   fChain->SetBranchAddress("TOFEndcapHits.momentum.x", TOFEndcapHits_momentum_x, &b_TOFEndcapHits_momentum_x);
   fChain->SetBranchAddress("TOFEndcapHits.momentum.y", TOFEndcapHits_momentum_y, &b_TOFEndcapHits_momentum_y);
   fChain->SetBranchAddress("TOFEndcapHits.momentum.z", TOFEndcapHits_momentum_z, &b_TOFEndcapHits_momentum_z);
   fChain->SetBranchAddress("_TOFEndcapHits_particle", &_TOFEndcapHits_particle_, &b__TOFEndcapHits_particle_);
   fChain->SetBranchAddress("_TOFEndcapHits_particle.index", _TOFEndcapHits_particle_index, &b__TOFEndcapHits_particle_index);
   fChain->SetBranchAddress("_TOFEndcapHits_particle.collectionID", _TOFEndcapHits_particle_collectionID, &b__TOFEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("TrackerEndcapHits", &TrackerEndcapHits_, &b_TrackerEndcapHits_);
   fChain->SetBranchAddress("TrackerEndcapHits.cellID", TrackerEndcapHits_cellID, &b_TrackerEndcapHits_cellID);
   fChain->SetBranchAddress("TrackerEndcapHits.eDep", TrackerEndcapHits_eDep, &b_TrackerEndcapHits_eDep);
   fChain->SetBranchAddress("TrackerEndcapHits.time", TrackerEndcapHits_time, &b_TrackerEndcapHits_time);
   fChain->SetBranchAddress("TrackerEndcapHits.pathLength", TrackerEndcapHits_pathLength, &b_TrackerEndcapHits_pathLength);
   fChain->SetBranchAddress("TrackerEndcapHits.quality", TrackerEndcapHits_quality, &b_TrackerEndcapHits_quality);
   fChain->SetBranchAddress("TrackerEndcapHits.position.x", TrackerEndcapHits_position_x, &b_TrackerEndcapHits_position_x);
   fChain->SetBranchAddress("TrackerEndcapHits.position.y", TrackerEndcapHits_position_y, &b_TrackerEndcapHits_position_y);
   fChain->SetBranchAddress("TrackerEndcapHits.position.z", TrackerEndcapHits_position_z, &b_TrackerEndcapHits_position_z);
   fChain->SetBranchAddress("TrackerEndcapHits.momentum.x", TrackerEndcapHits_momentum_x, &b_TrackerEndcapHits_momentum_x);
   fChain->SetBranchAddress("TrackerEndcapHits.momentum.y", TrackerEndcapHits_momentum_y, &b_TrackerEndcapHits_momentum_y);
   fChain->SetBranchAddress("TrackerEndcapHits.momentum.z", TrackerEndcapHits_momentum_z, &b_TrackerEndcapHits_momentum_z);
   fChain->SetBranchAddress("_TrackerEndcapHits_particle", &_TrackerEndcapHits_particle_, &b__TrackerEndcapHits_particle_);
   fChain->SetBranchAddress("_TrackerEndcapHits_particle.index", _TrackerEndcapHits_particle_index, &b__TrackerEndcapHits_particle_index);
   fChain->SetBranchAddress("_TrackerEndcapHits_particle.collectionID", _TrackerEndcapHits_particle_collectionID, &b__TrackerEndcapHits_particle_collectionID);
   fChain->SetBranchAddress("VertexBarrelHits", &VertexBarrelHits_, &b_VertexBarrelHits_);
   fChain->SetBranchAddress("VertexBarrelHits.cellID", VertexBarrelHits_cellID, &b_VertexBarrelHits_cellID);
   fChain->SetBranchAddress("VertexBarrelHits.eDep", VertexBarrelHits_eDep, &b_VertexBarrelHits_eDep);
   fChain->SetBranchAddress("VertexBarrelHits.time", VertexBarrelHits_time, &b_VertexBarrelHits_time);
   fChain->SetBranchAddress("VertexBarrelHits.pathLength", VertexBarrelHits_pathLength, &b_VertexBarrelHits_pathLength);
   fChain->SetBranchAddress("VertexBarrelHits.quality", VertexBarrelHits_quality, &b_VertexBarrelHits_quality);
   fChain->SetBranchAddress("VertexBarrelHits.position.x", VertexBarrelHits_position_x, &b_VertexBarrelHits_position_x);
   fChain->SetBranchAddress("VertexBarrelHits.position.y", VertexBarrelHits_position_y, &b_VertexBarrelHits_position_y);
   fChain->SetBranchAddress("VertexBarrelHits.position.z", VertexBarrelHits_position_z, &b_VertexBarrelHits_position_z);
   fChain->SetBranchAddress("VertexBarrelHits.momentum.x", VertexBarrelHits_momentum_x, &b_VertexBarrelHits_momentum_x);
   fChain->SetBranchAddress("VertexBarrelHits.momentum.y", VertexBarrelHits_momentum_y, &b_VertexBarrelHits_momentum_y);
   fChain->SetBranchAddress("VertexBarrelHits.momentum.z", VertexBarrelHits_momentum_z, &b_VertexBarrelHits_momentum_z);
   fChain->SetBranchAddress("_VertexBarrelHits_particle", &_VertexBarrelHits_particle_, &b__VertexBarrelHits_particle_);
   fChain->SetBranchAddress("_VertexBarrelHits_particle.index", _VertexBarrelHits_particle_index, &b__VertexBarrelHits_particle_index);
   fChain->SetBranchAddress("_VertexBarrelHits_particle.collectionID", _VertexBarrelHits_particle_collectionID, &b__VertexBarrelHits_particle_collectionID);
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

Bool_t   triggerCombineChecker::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void triggerCombineChecker::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}

Int_t triggerCombineChecker::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

// == e == MakeClass Default Functions == s ==
