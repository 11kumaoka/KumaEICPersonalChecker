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

   // 140
   m_vTargetEvents = {56, 206, 284, 408, 424};
   // 0, 1, 2, 5, 7, 8, 10
   // m_vTargetEvents = {23, 84, 89, 92, 102};
   // m_vTargetEvents = {106};
   

   // 0, 9, 16, 20, 25, 26, 41, 43, 44, 45, 50, 51, 55, 56, 57, 59, 66, 75, 90, 95, 104, 108, 110, 115, 120, 130, 131, 133, 142, 153, 155, 164, 170, 174, 177, 181, 187, 188, 190, 191, 194, 205, 209, 215, 220, 222, 224, 225, 248, 250, 259, 262, 264, 265, 266, 275, 277, 279, 281, 283, 286, 289, 295, 297, 298, 316, 317, 322, 331, 337, 345, 346, 355, 366, 371, 374, 378, 384, 389, 401, 403, 405, 425, 435, 444, 445, 450, 452, 453, 465, 467, 469, 470, 474, 477, 479, 481, 482, 488, 503, 514, 515, 516, 519, 520, 527, 529, 535, 541, 543, 544, 545, 549, 551, 552, 561, 564, 566, 574, 577, 578, 583, 588, 589, 590, 598, 602, 604, 606, 613, 614, 617, 621, 625, 628, 635, 643, 645, 648, 649, 650, 651, 657, 664, 667, 677, 681, 686, 691, 692, 710, 711, 717, 721, 722, 736, 744, 747, 751, 754, 756, 768, 770, 771, 774, 776, 777, 784, 791, 792, 793, 798, 805, 807, 811, 816, 822, 824, 825, 826, 834, 836, 840, 845, 850, 860, 864, 865, 872, 874, 883, 885, 886, 887, 893, 895, 898, 904, 907, 909, 910, 917, 923, 924, 928, 932, 942, 949, 950, 952, 955, 956, 959, 962, 965, 967, 973, 978, 989, 990, 994

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

      m_SimTrackerHitsKuma = LoadInputHits();

      // == s ==  Hit Time calibration ========================================
      for(int iDet = 0; iDet < m_triggerDetSize; ++iDet) m_SimTrackerHitsKuma.at(iDet).sortByTime();
      Double_t timeOffSet = 0.;
      HitTimeCalibration(timeOffSet);
      // == e ==  Hit Time calibration ========================================
      Int_t checkPhysCount = 0;
      bool bPhysicsEvent = false; // Set the flag for physics event processing
      Double_t physEventTime = - 999999.;
      physEventTime = FindFirstPhysParticle();
      // std::cout << " <><><><><><><> First physics particle time: " << physEventTime << std::endl;
      Int_t iTimeSlice = 0;

      bool bPhysCapture = false; // Flag to check if physics events are missed
      
      if(bTargetEV) FillEventDisplay(0., 0., true);


      // == s ==  Time-Slice Loop in a Time-Frame ========================================
      unsigned int startHitPoint[9] = {0};
      Int_t targetDetId = 0;
      // == s == Time-frame loop ========================================
      while (true){
         bool m_bTrigger = false;
         
         Int_t hitsCountsInTSDevInThetaPhi1[12][8] = {}; // Theta 0-12, Phi 0-8
         Int_t hitsCountsInTSDevInThetaPhi2[12][8] = {}; // Theta 0-11, Phi 0-8

         // == s == Register hits of TOF and MPGD detectors in the time slice ==================
         if(bInitialLoop){
            m_vOrigHitId.resize(m_triggerDetSize);
            m_vSameTSHitId.resize(m_triggerDetSize);
            m_vOutputHitContainer.resize(m_triggerDetSize);
            for (std::size_t iSub = 0; iSub < m_triggerDetSize; ++iSub){
               Int_t subDet = detId[iSub];
               size_t vHitSize = m_SimTrackerHitsKuma.at(subDet).getSize();
               std::vector<unsigned int > m_vOrigHitId_sub;
               m_vOrigHitId_sub.reserve(vHitSize);
               for (std::size_t i = 0; i < vHitSize; ++i) m_vOrigHitId_sub.push_back(i);

               m_vOrigHitId[iSub] = std::move(m_vOrigHitId_sub);
            }
            bInitialLoop = false;

            // for(std::size_t iSub = 0; iSub < m_triggerDetSize; ++iSub){
            //    for(std::size_t iHit = 0; iHit <  m_SimTrackerHitsKuma.at(iSub).getSize(); ++iHit){
            //       std::cout << "Detector " << detId[iSub] << " Hit " << iHit << " Time: " << m_SimTrackerHitsKuma.at(detId[iSub]).getTime(iHit) << std::endl;
            //    }
            // }


            for(Int_t iMCP = 0; iMCP < MCParticles_; ++iMCP) {
               if(MCParticles_generatorStatus[iMCP] != 1 && MCParticles_generatorStatus[iMCP] != 2) continue; // only final state particles

      bool bTargetEVTest = false;
      for(size_t i = 0; i < m_vTargetEvents.size(); ++i){
         if(jentry == m_vTargetEvents.at(i)){
            bTargetEVTest = true;
            break;
         }
      }
      if(!bTargetEV && bTargetEVTest) continue;

               Double_t pT_MC = std::sqrt(MCParticles_momentum_x[iMCP]*MCParticles_momentum_x[iMCP] + MCParticles_momentum_y[iMCP]*MCParticles_momentum_y[iMCP]);
               Double_t theta_MC = std::atan2(pT_MC, MCParticles_momentum_z[iMCP]) * (180.0 / TMath::Pi());
               Double_t eta_MC = -std::log(std::tan(theta_MC * TMath::DegToRad() / 2.0));
               m_hMCThetaDist->Fill(theta_MC);
               m_hMCEtaDist->Fill(eta_MC);
            }
         }
         // == e == Register hits of TOF and MPGD detectors in the time slice ==================

         // == s == Time-slice base detector loop ================================================
         for (size_t iBaseDet = targetDetId; iBaseDet < m_triggerDetSize; ++iBaseDet){
            // std::cout << "   >>>>> Time-slice base Detector ID: " << detId[iBaseDet] << std::endl;
            if(iBaseDet > 5 && m_bOnceTriggered){
               m_bScanedAllTimeWindows = true;
               break;
            }
            
            Int_t baseDetID = detId[iBaseDet];
            Double_t baseDetTimeRes = m_timeResolution_TOF;
            if(iBaseDet > 5) baseDetTimeRes = m_timeResolution_Silicon;
            else if(iBaseDet > 1) baseDetTimeRes = m_timeResolution_MPGD;
            
            // == s == Time-slice base detector hits loop =======================================
            Int_t baseDetNumOfHits = m_vOrigHitId.at(iBaseDet).size();
            if(startHitPoint[iBaseDet] >= baseDetNumOfHits){
               m_bDetLastHits[iBaseDet] = true;
               targetDetId++;
               if(targetDetId > m_triggerDetSize -1) m_bScanedAllTimeWindows = true;
               continue;
            }
            
            for(size_t iBaseHit = startHitPoint[iBaseDet]; iBaseHit < baseDetNumOfHits; ++iBaseHit){
               unsigned int baseHitID = m_vOrigHitId.at(iBaseDet).at(iBaseHit);
               Double_t baseHitTime = m_SimTrackerHitsKuma.at(baseDetID).getTime(baseHitID);
               Int_t baseThetaID1 = 999;
               Int_t baseThetaID2 = 999;
               Int_t basePhiID1 = 999;
               Int_t basePhiID2 = 999;
               thetaPhiBinCalc(m_SimTrackerHitsKuma.at(baseDetID), baseHitID,\
                  baseThetaID1, basePhiID1, baseThetaID2, basePhiID2);
               m_vSameTSHitId.at(iBaseDet).push_back(baseHitID);

               // Own detectors loop
               Int_t iCompDet = iBaseDet;
               Int_t compDetID = detId[iCompDet];
               for (size_t iCompHit = iBaseHit+1; iCompHit < baseDetNumOfHits; ++iCompHit) {
                  unsigned int compHitID = m_vOrigHitId.at(iCompDet).at(iCompHit);
                  Double_t compHitTime = m_SimTrackerHitsKuma.at(compDetID).getTime(compHitID);

                  Double_t compDetTimeRes = m_timeResolution_TOF;
                  if(iCompDet > 5) compDetTimeRes = m_timeResolution_Silicon;
                  else if(iCompDet > 1) compDetTimeRes = m_timeResolution_MPGD;

                  unsigned int iInTS = 1;
                  if(compHitTime - compDetTimeRes < baseHitTime + baseDetTimeRes){
                     if(compHitTime + compDetTimeRes > baseHitTime - baseDetTimeRes){
                        Int_t thetaID1 = 999;
                        Int_t thetaID2 = 999;
                        Int_t phiID1 = 999;
                        Int_t phiID2 = 999;
                        thetaPhiBinCalc(m_SimTrackerHitsKuma.at(compDetID), compHitID,\
                           thetaID1, phiID1, thetaID2, phiID2);
                        hitsCountsInTSDevInThetaPhi1[thetaID1][phiID1]++;
                        hitsCountsInTSDevInThetaPhi2[thetaID2][phiID2]++;
                        iInTS = 0;
                     }else iInTS = 2;
                  }
                  if(iInTS == 0){
                     // Register hits into container
                     m_vSameTSHitId.at(iCompDet).push_back(compHitID);
                  }else if(iInTS == 1){
                     // Update the start point for the next iteration
                     startHitPoint[iBaseDet] = iCompHit;
                     break; // Break if the hit time exceeds the current time slice
                  }
               }

               // Other detectors loop
               for (size_t iCompDet = iBaseDet + 1; iCompDet < m_triggerDetSize; ++iCompDet){
                  // std::cout << "     OOOO Comparing with Detector ID: " << detId[iCompDet] << std::endl;
                  Int_t compDetID = detId[iCompDet];
                  Int_t compDetNumOfHits = m_vOrigHitId.at(iCompDet).size();

                  for (size_t iCompHit = 0; iCompHit < compDetNumOfHits; ++iCompHit) {
                     unsigned int compHitID = m_vOrigHitId.at(iCompDet).at(iCompHit);
                     Double_t compHitTime = m_SimTrackerHitsKuma.at(compDetID).getTime(compHitID);
                     Double_t compDetTimeRes = m_timeResolution_TOF;
                     if(iCompDet > 5) compDetTimeRes = m_timeResolution_Silicon;
                     else if(iCompDet > 1) compDetTimeRes = m_timeResolution_MPGD;
                     
                     unsigned int iInTS = 1;
                     if(compHitTime - compDetTimeRes < baseHitTime + baseDetTimeRes){
                        if(compHitTime + compDetTimeRes > baseHitTime - baseDetTimeRes){
                           Int_t thetaID1 = 999;
                           Int_t thetaID2 = 999;
                           Int_t phiID1 = 999;
                           Int_t phiID2 = 999;
                           thetaPhiBinCalc(m_SimTrackerHitsKuma.at(compDetID), compHitID,\
                              thetaID1, phiID1, thetaID2, phiID2);
                           hitsCountsInTSDevInThetaPhi1[thetaID1][phiID1]++;
                           hitsCountsInTSDevInThetaPhi2[thetaID2][phiID2]++;
                           iInTS = 0;
                        }else iInTS = 2;
                     }
                     // std::cout << "         Comparing Hit ID: " << compHitID 
                     // << ", sbaseTime = " << baseHitTime - baseDetTimeRes
                     // << ", ebaseTime = " << baseHitTime + baseDetTimeRes
                     // << ", scompTime = " << compHitTime - compDetTimeRes
                     // << ", ecompTime = " << compHitTime + compDetTimeRes
                     // << ", Time: " << compHitTime \
                     //    << " => Trigger Judge: " << iInTS << std::endl;

                     if(iInTS == 0){
                        // Register hits into container
                        m_vSameTSHitId.at(iCompDet).push_back(compHitID);
                     }else if(iInTS == 1) break;
                  }
               }
               if(iBaseHit == baseDetNumOfHits-1 || startHitPoint[iBaseDet] == baseDetNumOfHits-1){
                  m_bDetLastHits[iBaseDet] = true;
                  targetDetId++;
               }

               // == s ==  Trigger Judgement ================================================
               for(size_t iThetaBin = 0; iThetaBin < 12; ++iThetaBin){
                  for(size_t iPhiBin = 0; iPhiBin < 8; ++iPhiBin){
                     if(hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin] > 2) m_bTrigger = true;
                     if(hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin] > 2) m_bTrigger = true;

                     // if(hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin] > 1 ||\
                     // hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin] > 1) \
                     // std::cout << "Theta:" << iThetaBin << ", Phi: " << iPhiBin\
                     //    << " numOfhits1 = " << hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin]\
                     //    << " numOfhits2 = " << hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin]\
                     //    << std::endl;
                  }
               }
               // == e ==  Trigger Judgement ==================================================
               if(m_bTrigger){
                  // == s == Check this trigger is for physics event (for this test code) 
                  if(physEventTime > baseHitTime - baseDetTimeRes\
                     && physEventTime < baseHitTime + baseDetTimeRes) bPhysicsEvent = true;
                  if(bPhysicsEvent) m_bOncePhysicsTriggered = true;
                  // == e == Check this trigger is for physics event (for this test code) 

                  // std::cout << " >>>>> Time-slice ID: " << iTimeSlice << " <<<<< " << std::endl;
                  // Register all hits in the same time slice into output container
                  for(size_t iDet = 0; iDet < m_triggerDetSize; ++iDet){
                     for(size_t iHit = 0; iHit < m_vSameTSHitId.at(iDet).size(); ++iHit){
                        Int_t hitID = m_vSameTSHitId.at(iDet).at(iHit);
                        m_vOutputHitContainer.at(iDet).push_back(hitID);
                        size_t origHitSize = m_vOrigHitId.at(iDet).size();
                        for(size_t iOrigHit = 0; iOrigHit < origHitSize; ++iOrigHit){
                           if(hitID != m_vOrigHitId.at(iDet).at(iOrigHit)) continue;
                           m_vOrigHitId.at(iDet).erase(m_vOrigHitId.at(iDet).begin() + iOrigHit);
                           iOrigHit--; // Adjust index after erasure
                           origHitSize--;
                        }
                        
                        if(startHitPoint[targetDetId] >= m_vOrigHitId.at(iBaseDet).size()-1){
                           m_bDetLastHits[targetDetId] = true;
                           if(targetDetId > 5 && m_bOnceTriggered) m_bScanedAllTimeWindows = true;
                        }
                        // if(m_bOncePhysicsTriggered) std::cout << " >><<>><< PhysTime = " << physEventTime << "  <><><><> Triggered Det " << iDet << " Hit " << hitID \
                        //    << " Time: " << m_SimTrackerHitsKuma.at(iDet).getTime(hitID) << std::endl;
                        // std::cout << "     >>>>> Registered TRK DetID: " << iDet << ", HitID: " << hitID << ", Time: " << m_SimTrackerHitsKuma.at(iDet).getTime(hitID) << std::endl;
                     }
                  }
                  m_bOnceTriggered = true;

                  if(iBaseHit != baseDetNumOfHits - 1) startHitPoint[iBaseDet]++;

                  iTimeSlice++;

// for(size_t iThetaBin = 0; iThetaBin < 12; ++iThetaBin){
//    for(size_t iPhiBin = 0; iPhiBin < 8; ++iPhiBin){
//       if(hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin] > 0 ||\
//       hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin] > 0) \
//       std::cout << "Theta:" << iThetaBin << ", Phi: " << iPhiBin\
//          << " numOfhits1 = " << hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin]\
//          << " numOfhits2 = " << hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin]\
//          << std::endl;
//    }
// }
               }
               
               for(size_t iDet = 0; iDet < m_triggerDetSize; ++iDet){
                  m_vSameTSHitId.at(iDet).clear();
                  std::vector<unsigned int>().swap(m_vSameTSHitId.at(iDet));
               }
               
               if(m_bTrigger) break;
            } // == e == Time-slice base detector hits loop ==================================
            if(m_bTrigger) break;
         } // == e == Time-slice base detector loop ==================================
         
         // == s == Trigger efficiency check  (for this test code) ==============================
         if(m_bTrigger){
            if(bPhysicsEvent) m_hTriggerCounts->Fill(1);
            else m_hTriggerCounts->Fill(3);

            if(bPhysicsEvent) checkPhysCount++;
         }
         if(m_bScanedAllTimeWindows&&!m_bOncePhysicsTriggered){
            m_hTriggerCounts->Fill(2);
            m_vTargetEvents.push_back(m_pubEvNum);
         }

         if(bPhysicsEvent && (!m_bTrigger)){
            int a = 0;
            // m_vTargetEvents.push_back(m_pubEvNum);
            // FillEventDisplay(eTime - m_timeslice_width, eTime, false);
         }

         bPhysicsEvent = false;
         // == e == Trigger efficiency check  (for this test code) ==============================
         
         if(m_bDetLastHits[8]) m_bScanedAllTimeWindows = true;
         if(m_bScanedAllTimeWindows){
            bInitialLoop = true;
            m_bOnceTriggered = false;
            
            for(size_t iDet = 0; iDet < m_triggerDetSize; ++iDet){
               m_vOrigHitId.at(iDet).clear();
               std::vector<unsigned int >().swap(m_vOrigHitId.at(iDet));
               startHitPoint[iDet] = 0;
               m_bDetLastHits[iDet] = false;
            }
            m_vOrigHitId.clear();

            m_bScanedAllTimeWindows = false;
            break;
         }

         // == s == Rest output container (for this test code)
         for(size_t iDet = 0; iDet < m_triggerDetSize; ++iDet){
            m_vOutputHitContainer.at(iDet).clear();
            std::vector<unsigned int >().swap(m_vOutputHitContainer.at(iDet));
         }
         // == e == Rest output container (for this test code)
      } // == e == time-frame loop
      m_bOncePhysicsTriggered = false;
      
      ResetValuesForEachEvent();

      if(checkPhysCount > 1) m_vTargetEvents.push_back(m_pubEvNum);
      if(bTargetEV) jentry = tempJEntry;
   } // == end of loop over events


   for(size_t iTrig = 0; iTrig < 3; ++iTrig) m_hTriggerCounts->SetBinError(iTrig + 1, 0.0);

   Double_t scaleV = (m_vTargetEvents.size()/2.)/(1000.);
   if(!bTargetEV) scaleV = 1. - scaleV;
   std::cout << "numOfEventLoops : scaleV = " << numOfEventLoops << " : " << scaleV << std::endl;
   m_hMCEtaDist->Scale(scaleV);
   m_hMCThetaDist->Scale(scaleV);

   WriteHists();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

   std::cout << "Number of noise events: " << numOfNoise << std::endl;

}

void triggerCombineChecker::thetaPhiBinCalc(SimTrackerHitKuma& simHitsKuma, Int_t hitId,\
      Int_t& thetaID1, Int_t& phiID1, Int_t& thetaID2, Int_t& phiID2){
   
      Double_t hitX = simHitsKuma.getPosiX(hitId);
      Double_t hitY = simHitsKuma.getPosiY(hitId);
      Double_t hitZ = simHitsKuma.getPosiZ(hitId);
      Double_t hitR = TMath::Sqrt(hitX*hitX + hitY*hitY + hitZ*hitZ);
      Double_t hit_Theta = 0.;
      hit_Theta = TMath::ACos(hitZ/hitR);
      if(hit_Theta >  1.0) hit_Theta = 1.0;
      if(hit_Theta < -1.0) hit_Theta = -1.0;

      Double_t hit_Phi = TMath::ATan2(hitY, hitX) + 2*TMath::Pi();
      if(hit_Phi < 0) hit_Phi += 2*TMath::Pi();
      thetaID1 = hit_Theta / (TMath::Pi()/12.);
      thetaID2 = (hit_Theta + TMath::Pi()/24.) / (TMath::Pi()/12.);
      phiID1 = hit_Phi / (TMath::Pi()/8.);
      phiID2 = (hit_Phi + TMath::Pi()/16.) / (TMath::Pi()/8.);
      // std::cout << "      >>>>> hit x, y, z, R, theta: " << hitX << ", " << hitY << ", " <<hitZ << ", " << hitR << ", " << hit_Theta << ", thetaID1: " << thetaID1 << ", phiID1: "<< phiID1 << std::endl;
      // std::cout << "thetaID1: " << thetaID1 << ", phiID1: " << phiID1 << ", thetaID2: " <<thetaID2 << ", phiID2: " << phiID2 << std::endl;
}


void triggerCombineChecker::HitTimeCalibration(Double_t timeOffSet){
   for(int iDet = 0; iDet < m_triggerDetSize; ++iDet){
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
   for(size_t iDet = 0; iDet < m_triggerDetSize; ++iDet){
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

   TString triggerNames[3] = {"Triggered (Phys)", "Missed (Phys)", "Fake Trig"};
   for (int i = 0; i < 3; ++i) {
      m_hTriggerCounts->GetXaxis()->SetBinLabel(i + 1, triggerNames[i].Data());
   }

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


void triggerCombineChecker::ResetValuesForEachEvent(){
   m_SimTrackerHitsKuma.clear();
   m_SimTrackerHitsKuma.shrink_to_fit();

}

void triggerCombineChecker::WriteHists(){
   oFile->cd();

   m_hEventDisplayZR_Det->Write();
   m_hEventDisplayZR_Det_TF->Write();

   m_hTriggerCounts->Write();

   
   m_hMCEtaDist->Write();
   m_hMCThetaDist->Write();

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

   fChain->SetBranchAddress("B0ECalClusters", &B0ECalClusters_, &b_B0ECalClusters_);
   fChain->SetBranchAddress("B0ECalClusters.type", B0ECalClusters_type, &b_B0ECalClusters_type);
   fChain->SetBranchAddress("B0ECalClusters.energy", B0ECalClusters_energy, &b_B0ECalClusters_energy);
   fChain->SetBranchAddress("B0ECalClusters.energyError", B0ECalClusters_energyError, &b_B0ECalClusters_energyError);
   fChain->SetBranchAddress("B0ECalClusters.time", B0ECalClusters_time, &b_B0ECalClusters_time);
   fChain->SetBranchAddress("B0ECalClusters.timeError", B0ECalClusters_timeError, &b_B0ECalClusters_timeError);
   fChain->SetBranchAddress("B0ECalClusters.nhits", B0ECalClusters_nhits, &b_B0ECalClusters_nhits);
   fChain->SetBranchAddress("B0ECalClusters.position.x", B0ECalClusters_position_x, &b_B0ECalClusters_position_x);
   fChain->SetBranchAddress("B0ECalClusters.position.y", B0ECalClusters_position_y, &b_B0ECalClusters_position_y);
   fChain->SetBranchAddress("B0ECalClusters.position.z", B0ECalClusters_position_z, &b_B0ECalClusters_position_z);
   fChain->SetBranchAddress("B0ECalClusters.positionError.xx", B0ECalClusters_positionError_xx, &b_B0ECalClusters_positionError_xx);
   fChain->SetBranchAddress("B0ECalClusters.positionError.yy", B0ECalClusters_positionError_yy, &b_B0ECalClusters_positionError_yy);
   fChain->SetBranchAddress("B0ECalClusters.positionError.zz", B0ECalClusters_positionError_zz, &b_B0ECalClusters_positionError_zz);
   fChain->SetBranchAddress("B0ECalClusters.positionError.xy", B0ECalClusters_positionError_xy, &b_B0ECalClusters_positionError_xy);
   fChain->SetBranchAddress("B0ECalClusters.positionError.xz", B0ECalClusters_positionError_xz, &b_B0ECalClusters_positionError_xz);
   fChain->SetBranchAddress("B0ECalClusters.positionError.yz", B0ECalClusters_positionError_yz, &b_B0ECalClusters_positionError_yz);

   fChain->SetBranchAddress("B0ECalRecHits", &B0ECalRecHits_, &b_B0ECalRecHits_);
   fChain->SetBranchAddress("B0ECalRecHits.cellID", B0ECalRecHits_cellID, &b_B0ECalRecHits_cellID);
   fChain->SetBranchAddress("B0ECalRecHits.energy", B0ECalRecHits_energy, &b_B0ECalRecHits_energy);
   fChain->SetBranchAddress("B0ECalRecHits.energyError", B0ECalRecHits_energyError, &b_B0ECalRecHits_energyError);
   fChain->SetBranchAddress("B0ECalRecHits.time", B0ECalRecHits_time, &b_B0ECalRecHits_time);
   fChain->SetBranchAddress("B0ECalRecHits.timeError", B0ECalRecHits_timeError, &b_B0ECalRecHits_timeError);
   fChain->SetBranchAddress("B0ECalRecHits.position.x", B0ECalRecHits_position_x, &b_B0ECalRecHits_position_x);
   fChain->SetBranchAddress("B0ECalRecHits.position.y", B0ECalRecHits_position_y, &b_B0ECalRecHits_position_y);
   fChain->SetBranchAddress("B0ECalRecHits.position.z", B0ECalRecHits_position_z, &b_B0ECalRecHits_position_z);


   fChain->SetBranchAddress("DIRCRawHits", &DIRCRawHits_, &b_DIRCRawHits_);
   fChain->SetBranchAddress("DIRCRawHits.cellID", DIRCRawHits_cellID, &b_DIRCRawHits_cellID);
   fChain->SetBranchAddress("DIRCRawHits.charge", DIRCRawHits_charge, &b_DIRCRawHits_charge);
   fChain->SetBranchAddress("DIRCRawHits.timeStamp", DIRCRawHits_timeStamp, &b_DIRCRawHits_timeStamp);

   fChain->SetBranchAddress("DRICHRawHits", &DRICHRawHits_, &b_DRICHRawHits_);
   fChain->SetBranchAddress("DRICHRawHits.cellID", DRICHRawHits_cellID, &b_DRICHRawHits_cellID);
   fChain->SetBranchAddress("DRICHRawHits.charge", DRICHRawHits_charge, &b_DRICHRawHits_charge);
   fChain->SetBranchAddress("DRICHRawHits.timeStamp", DRICHRawHits_timeStamp, &b_DRICHRawHits_timeStamp);


   fChain->SetBranchAddress("EcalBarrelClusters", &EcalBarrelClusters_, &b_EcalBarrelClusters_);
   fChain->SetBranchAddress("EcalBarrelClusters.type", EcalBarrelClusters_type, &b_EcalBarrelClusters_type);
   fChain->SetBranchAddress("EcalBarrelClusters.energy", EcalBarrelClusters_energy, &b_EcalBarrelClusters_energy);
   fChain->SetBranchAddress("EcalBarrelClusters.energyError", EcalBarrelClusters_energyError, &b_EcalBarrelClusters_energyError);
   fChain->SetBranchAddress("EcalBarrelClusters.time", EcalBarrelClusters_time, &b_EcalBarrelClusters_time);
   fChain->SetBranchAddress("EcalBarrelClusters.timeError", EcalBarrelClusters_timeError, &b_EcalBarrelClusters_timeError);
   fChain->SetBranchAddress("EcalBarrelClusters.nhits", EcalBarrelClusters_nhits, &b_EcalBarrelClusters_nhits);
   fChain->SetBranchAddress("EcalBarrelClusters.position.x", EcalBarrelClusters_position_x, &b_EcalBarrelClusters_position_x);
   fChain->SetBranchAddress("EcalBarrelClusters.position.y", EcalBarrelClusters_position_y, &b_EcalBarrelClusters_position_y);
   fChain->SetBranchAddress("EcalBarrelClusters.position.z", EcalBarrelClusters_position_z, &b_EcalBarrelClusters_position_z);
   fChain->SetBranchAddress("EcalBarrelClusters.positionError.xx", EcalBarrelClusters_positionError_xx, &b_EcalBarrelClusters_positionError_xx);
   fChain->SetBranchAddress("EcalBarrelClusters.positionError.yy", EcalBarrelClusters_positionError_yy, &b_EcalBarrelClusters_positionError_yy);
   fChain->SetBranchAddress("EcalBarrelClusters.positionError.zz", EcalBarrelClusters_positionError_zz, &b_EcalBarrelClusters_positionError_zz);
   fChain->SetBranchAddress("EcalBarrelClusters.positionError.xy", EcalBarrelClusters_positionError_xy, &b_EcalBarrelClusters_positionError_xy);
   fChain->SetBranchAddress("EcalBarrelClusters.positionError.xz", EcalBarrelClusters_positionError_xz, &b_EcalBarrelClusters_positionError_xz);
   fChain->SetBranchAddress("EcalBarrelClusters.positionError.yz", EcalBarrelClusters_positionError_yz, &b_EcalBarrelClusters_positionError_yz);

   fChain->SetBranchAddress("EcalBarrelImagingClusters", &EcalBarrelImagingClusters_, &b_EcalBarrelImagingClusters_);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.type", EcalBarrelImagingClusters_type, &b_EcalBarrelImagingClusters_type);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.energy", EcalBarrelImagingClusters_energy, &b_EcalBarrelImagingClusters_energy);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.energyError", EcalBarrelImagingClusters_energyError, &b_EcalBarrelImagingClusters_energyError);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.time", EcalBarrelImagingClusters_time, &b_EcalBarrelImagingClusters_time);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.timeError", EcalBarrelImagingClusters_timeError, &b_EcalBarrelImagingClusters_timeError);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.nhits", EcalBarrelImagingClusters_nhits, &b_EcalBarrelImagingClusters_nhits);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.position.x", EcalBarrelImagingClusters_position_x, &b_EcalBarrelImagingClusters_position_x);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.position.y", EcalBarrelImagingClusters_position_y, &b_EcalBarrelImagingClusters_position_y);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.position.z", EcalBarrelImagingClusters_position_z, &b_EcalBarrelImagingClusters_position_z);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.positionError.xx", EcalBarrelImagingClusters_positionError_xx, &b_EcalBarrelImagingClusters_positionError_xx);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.positionError.yy", EcalBarrelImagingClusters_positionError_yy, &b_EcalBarrelImagingClusters_positionError_yy);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.positionError.zz", EcalBarrelImagingClusters_positionError_zz, &b_EcalBarrelImagingClusters_positionError_zz);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.positionError.xy", EcalBarrelImagingClusters_positionError_xy, &b_EcalBarrelImagingClusters_positionError_xy);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.positionError.xz", EcalBarrelImagingClusters_positionError_xz, &b_EcalBarrelImagingClusters_positionError_xz);
   fChain->SetBranchAddress("EcalBarrelImagingClusters.positionError.yz", EcalBarrelImagingClusters_positionError_yz, &b_EcalBarrelImagingClusters_positionError_yz);

   fChain->SetBranchAddress("EcalBarrelImagingRecHits", &EcalBarrelImagingRecHits_, &b_EcalBarrelImagingRecHits_);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.cellID", EcalBarrelImagingRecHits_cellID, &b_EcalBarrelImagingRecHits_cellID);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.energy", EcalBarrelImagingRecHits_energy, &b_EcalBarrelImagingRecHits_energy);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.energyError", EcalBarrelImagingRecHits_energyError, &b_EcalBarrelImagingRecHits_energyError);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.time", EcalBarrelImagingRecHits_time, &b_EcalBarrelImagingRecHits_time);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.timeError", EcalBarrelImagingRecHits_timeError, &b_EcalBarrelImagingRecHits_timeError);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.position.x", EcalBarrelImagingRecHits_position_x, &b_EcalBarrelImagingRecHits_position_x);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.position.y", EcalBarrelImagingRecHits_position_y, &b_EcalBarrelImagingRecHits_position_y);
   fChain->SetBranchAddress("EcalBarrelImagingRecHits.position.z", EcalBarrelImagingRecHits_position_z, &b_EcalBarrelImagingRecHits_position_z);

   fChain->SetBranchAddress("EcalBarrelScFiClusters", &EcalBarrelScFiClusters_, &b_EcalBarrelScFiClusters_);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.type", EcalBarrelScFiClusters_type, &b_EcalBarrelScFiClusters_type);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.energy", EcalBarrelScFiClusters_energy, &b_EcalBarrelScFiClusters_energy);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.energyError", EcalBarrelScFiClusters_energyError, &b_EcalBarrelScFiClusters_energyError);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.time", EcalBarrelScFiClusters_time, &b_EcalBarrelScFiClusters_time);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.timeError", EcalBarrelScFiClusters_timeError, &b_EcalBarrelScFiClusters_timeError);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.nhits", EcalBarrelScFiClusters_nhits, &b_EcalBarrelScFiClusters_nhits);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.position.x", EcalBarrelScFiClusters_position_x, &b_EcalBarrelScFiClusters_position_x);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.position.y", EcalBarrelScFiClusters_position_y, &b_EcalBarrelScFiClusters_position_y);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.position.z", EcalBarrelScFiClusters_position_z, &b_EcalBarrelScFiClusters_position_z);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.positionError.xx", EcalBarrelScFiClusters_positionError_xx, &b_EcalBarrelScFiClusters_positionError_xx);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.positionError.yy", EcalBarrelScFiClusters_positionError_yy, &b_EcalBarrelScFiClusters_positionError_yy);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.positionError.zz", EcalBarrelScFiClusters_positionError_zz, &b_EcalBarrelScFiClusters_positionError_zz);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.positionError.xy", EcalBarrelScFiClusters_positionError_xy, &b_EcalBarrelScFiClusters_positionError_xy);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.positionError.xz", EcalBarrelScFiClusters_positionError_xz, &b_EcalBarrelScFiClusters_positionError_xz);
   fChain->SetBranchAddress("EcalBarrelScFiClusters.positionError.yz", EcalBarrelScFiClusters_positionError_yz, &b_EcalBarrelScFiClusters_positionError_yz);

   fChain->SetBranchAddress("EcalBarrelScFiRecHits", &EcalBarrelScFiRecHits_, &b_EcalBarrelScFiRecHits_);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.cellID", EcalBarrelScFiRecHits_cellID, &b_EcalBarrelScFiRecHits_cellID);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.energy", EcalBarrelScFiRecHits_energy, &b_EcalBarrelScFiRecHits_energy);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.energyError", EcalBarrelScFiRecHits_energyError, &b_EcalBarrelScFiRecHits_energyError);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.time", EcalBarrelScFiRecHits_time, &b_EcalBarrelScFiRecHits_time);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.timeError", EcalBarrelScFiRecHits_timeError, &b_EcalBarrelScFiRecHits_timeError);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.position.x", EcalBarrelScFiRecHits_position_x, &b_EcalBarrelScFiRecHits_position_x);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.position.y", EcalBarrelScFiRecHits_position_y, &b_EcalBarrelScFiRecHits_position_y);
   fChain->SetBranchAddress("EcalBarrelScFiRecHits.position.z", EcalBarrelScFiRecHits_position_z, &b_EcalBarrelScFiRecHits_position_z);

   fChain->SetBranchAddress("EcalEndcapNClusters", &EcalEndcapNClusters_, &b_EcalEndcapNClusters_);
   fChain->SetBranchAddress("EcalEndcapNClusters.type", EcalEndcapNClusters_type, &b_EcalEndcapNClusters_type);
   fChain->SetBranchAddress("EcalEndcapNClusters.energy", EcalEndcapNClusters_energy, &b_EcalEndcapNClusters_energy);
   fChain->SetBranchAddress("EcalEndcapNClusters.energyError", EcalEndcapNClusters_energyError, &b_EcalEndcapNClusters_energyError);
   fChain->SetBranchAddress("EcalEndcapNClusters.time", EcalEndcapNClusters_time, &b_EcalEndcapNClusters_time);
   fChain->SetBranchAddress("EcalEndcapNClusters.timeError", EcalEndcapNClusters_timeError, &b_EcalEndcapNClusters_timeError);
   fChain->SetBranchAddress("EcalEndcapNClusters.nhits", EcalEndcapNClusters_nhits, &b_EcalEndcapNClusters_nhits);
   fChain->SetBranchAddress("EcalEndcapNClusters.position.x", EcalEndcapNClusters_position_x, &b_EcalEndcapNClusters_position_x);
   fChain->SetBranchAddress("EcalEndcapNClusters.position.y", EcalEndcapNClusters_position_y, &b_EcalEndcapNClusters_position_y);
   fChain->SetBranchAddress("EcalEndcapNClusters.position.z", EcalEndcapNClusters_position_z, &b_EcalEndcapNClusters_position_z);
   fChain->SetBranchAddress("EcalEndcapNClusters.positionError.xx", EcalEndcapNClusters_positionError_xx, &b_EcalEndcapNClusters_positionError_xx);
   fChain->SetBranchAddress("EcalEndcapNClusters.positionError.yy", EcalEndcapNClusters_positionError_yy, &b_EcalEndcapNClusters_positionError_yy);
   fChain->SetBranchAddress("EcalEndcapNClusters.positionError.zz", EcalEndcapNClusters_positionError_zz, &b_EcalEndcapNClusters_positionError_zz);
   fChain->SetBranchAddress("EcalEndcapNClusters.positionError.xy", EcalEndcapNClusters_positionError_xy, &b_EcalEndcapNClusters_positionError_xy);
   fChain->SetBranchAddress("EcalEndcapNClusters.positionError.xz", EcalEndcapNClusters_positionError_xz, &b_EcalEndcapNClusters_positionError_xz);
   fChain->SetBranchAddress("EcalEndcapNClusters.positionError.yz", EcalEndcapNClusters_positionError_yz, &b_EcalEndcapNClusters_positionError_yz);

   fChain->SetBranchAddress("EcalEndcapNRecHits", &EcalEndcapNRecHits_, &b_EcalEndcapNRecHits_);
   fChain->SetBranchAddress("EcalEndcapNRecHits.cellID", EcalEndcapNRecHits_cellID, &b_EcalEndcapNRecHits_cellID);
   fChain->SetBranchAddress("EcalEndcapNRecHits.energy", EcalEndcapNRecHits_energy, &b_EcalEndcapNRecHits_energy);
   fChain->SetBranchAddress("EcalEndcapNRecHits.energyError", EcalEndcapNRecHits_energyError, &b_EcalEndcapNRecHits_energyError);
   fChain->SetBranchAddress("EcalEndcapNRecHits.time", EcalEndcapNRecHits_time, &b_EcalEndcapNRecHits_time);
   fChain->SetBranchAddress("EcalEndcapNRecHits.timeError", EcalEndcapNRecHits_timeError, &b_EcalEndcapNRecHits_timeError);
   fChain->SetBranchAddress("EcalEndcapNRecHits.position.x", EcalEndcapNRecHits_position_x, &b_EcalEndcapNRecHits_position_x);
   fChain->SetBranchAddress("EcalEndcapNRecHits.position.y", EcalEndcapNRecHits_position_y, &b_EcalEndcapNRecHits_position_y);
   fChain->SetBranchAddress("EcalEndcapNRecHits.position.z", EcalEndcapNRecHits_position_z, &b_EcalEndcapNRecHits_position_z);

   fChain->SetBranchAddress("EcalEndcapPClusters", &EcalEndcapPClusters_, &b_EcalEndcapPClusters_);
   fChain->SetBranchAddress("EcalEndcapPClusters.type", EcalEndcapPClusters_type, &b_EcalEndcapPClusters_type);
   fChain->SetBranchAddress("EcalEndcapPClusters.energy", EcalEndcapPClusters_energy, &b_EcalEndcapPClusters_energy);
   fChain->SetBranchAddress("EcalEndcapPClusters.energyError", EcalEndcapPClusters_energyError, &b_EcalEndcapPClusters_energyError);
   fChain->SetBranchAddress("EcalEndcapPClusters.time", EcalEndcapPClusters_time, &b_EcalEndcapPClusters_time);
   fChain->SetBranchAddress("EcalEndcapPClusters.timeError", EcalEndcapPClusters_timeError, &b_EcalEndcapPClusters_timeError);
   fChain->SetBranchAddress("EcalEndcapPClusters.nhits", EcalEndcapPClusters_nhits, &b_EcalEndcapPClusters_nhits);
   fChain->SetBranchAddress("EcalEndcapPClusters.position.x", EcalEndcapPClusters_position_x, &b_EcalEndcapPClusters_position_x);
   fChain->SetBranchAddress("EcalEndcapPClusters.position.y", EcalEndcapPClusters_position_y, &b_EcalEndcapPClusters_position_y);
   fChain->SetBranchAddress("EcalEndcapPClusters.position.z", EcalEndcapPClusters_position_z, &b_EcalEndcapPClusters_position_z);
   fChain->SetBranchAddress("EcalEndcapPClusters.positionError.xx", EcalEndcapPClusters_positionError_xx, &b_EcalEndcapPClusters_positionError_xx);
   fChain->SetBranchAddress("EcalEndcapPClusters.positionError.yy", EcalEndcapPClusters_positionError_yy, &b_EcalEndcapPClusters_positionError_yy);
   fChain->SetBranchAddress("EcalEndcapPClusters.positionError.zz", EcalEndcapPClusters_positionError_zz, &b_EcalEndcapPClusters_positionError_zz);
   fChain->SetBranchAddress("EcalEndcapPClusters.positionError.xy", EcalEndcapPClusters_positionError_xy, &b_EcalEndcapPClusters_positionError_xy);
   fChain->SetBranchAddress("EcalEndcapPClusters.positionError.xz", EcalEndcapPClusters_positionError_xz, &b_EcalEndcapPClusters_positionError_xz);
   fChain->SetBranchAddress("EcalEndcapPClusters.positionError.yz", EcalEndcapPClusters_positionError_yz, &b_EcalEndcapPClusters_positionError_yz);

   fChain->SetBranchAddress("EcalEndcapPRecHits", &EcalEndcapPRecHits_, &b_EcalEndcapPRecHits_);
   fChain->SetBranchAddress("EcalEndcapPRecHits.cellID", EcalEndcapPRecHits_cellID, &b_EcalEndcapPRecHits_cellID);
   fChain->SetBranchAddress("EcalEndcapPRecHits.energy", EcalEndcapPRecHits_energy, &b_EcalEndcapPRecHits_energy);
   fChain->SetBranchAddress("EcalEndcapPRecHits.energyError", EcalEndcapPRecHits_energyError, &b_EcalEndcapPRecHits_energyError);
   fChain->SetBranchAddress("EcalEndcapPRecHits.time", EcalEndcapPRecHits_time, &b_EcalEndcapPRecHits_time);
   fChain->SetBranchAddress("EcalEndcapPRecHits.timeError", EcalEndcapPRecHits_timeError, &b_EcalEndcapPRecHits_timeError);
   fChain->SetBranchAddress("EcalEndcapPRecHits.position.x", EcalEndcapPRecHits_position_x, &b_EcalEndcapPRecHits_position_x);
   fChain->SetBranchAddress("EcalEndcapPRecHits.position.y", EcalEndcapPRecHits_position_y, &b_EcalEndcapPRecHits_position_y);
   fChain->SetBranchAddress("EcalEndcapPRecHits.position.z", EcalEndcapPRecHits_position_z, &b_EcalEndcapPRecHits_position_z);

   fChain->SetBranchAddress("EcalFarForwardZDCClusters", &EcalFarForwardZDCClusters_, &b_EcalFarForwardZDCClusters_);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.type", EcalFarForwardZDCClusters_type, &b_EcalFarForwardZDCClusters_type);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.energy", EcalFarForwardZDCClusters_energy, &b_EcalFarForwardZDCClusters_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.energyError", EcalFarForwardZDCClusters_energyError, &b_EcalFarForwardZDCClusters_energyError);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.time", EcalFarForwardZDCClusters_time, &b_EcalFarForwardZDCClusters_time);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.timeError", EcalFarForwardZDCClusters_timeError, &b_EcalFarForwardZDCClusters_timeError);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.nhits", EcalFarForwardZDCClusters_nhits, &b_EcalFarForwardZDCClusters_nhits);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.position.x", EcalFarForwardZDCClusters_position_x, &b_EcalFarForwardZDCClusters_position_x);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.position.y", EcalFarForwardZDCClusters_position_y, &b_EcalFarForwardZDCClusters_position_y);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.position.z", EcalFarForwardZDCClusters_position_z, &b_EcalFarForwardZDCClusters_position_z);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.positionError.xx", EcalFarForwardZDCClusters_positionError_xx, &b_EcalFarForwardZDCClusters_positionError_xx);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.positionError.yy", EcalFarForwardZDCClusters_positionError_yy, &b_EcalFarForwardZDCClusters_positionError_yy);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.positionError.zz", EcalFarForwardZDCClusters_positionError_zz, &b_EcalFarForwardZDCClusters_positionError_zz);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.positionError.xy", EcalFarForwardZDCClusters_positionError_xy, &b_EcalFarForwardZDCClusters_positionError_xy);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.positionError.xz", EcalFarForwardZDCClusters_positionError_xz, &b_EcalFarForwardZDCClusters_positionError_xz);
   fChain->SetBranchAddress("EcalFarForwardZDCClusters.positionError.yz", EcalFarForwardZDCClusters_positionError_yz, &b_EcalFarForwardZDCClusters_positionError_yz);

   fChain->SetBranchAddress("EcalFarForwardZDCRecHits", &EcalFarForwardZDCRecHits_, &b_EcalFarForwardZDCRecHits_);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.cellID", EcalFarForwardZDCRecHits_cellID, &b_EcalFarForwardZDCRecHits_cellID);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.energy", EcalFarForwardZDCRecHits_energy, &b_EcalFarForwardZDCRecHits_energy);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.energyError", EcalFarForwardZDCRecHits_energyError, &b_EcalFarForwardZDCRecHits_energyError);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.time", EcalFarForwardZDCRecHits_time, &b_EcalFarForwardZDCRecHits_time);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.timeError", EcalFarForwardZDCRecHits_timeError, &b_EcalFarForwardZDCRecHits_timeError);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.position.x", EcalFarForwardZDCRecHits_position_x, &b_EcalFarForwardZDCRecHits_position_x);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.position.y", EcalFarForwardZDCRecHits_position_y, &b_EcalFarForwardZDCRecHits_position_y);
   fChain->SetBranchAddress("EcalFarForwardZDCRecHits.position.z", EcalFarForwardZDCRecHits_position_z, &b_EcalFarForwardZDCRecHits_position_z);

   fChain->SetBranchAddress("EcalLumiSpecClusters", &EcalLumiSpecClusters_, &b_EcalLumiSpecClusters_);
   fChain->SetBranchAddress("EcalLumiSpecClusters.type", &EcalLumiSpecClusters_type, &b_EcalLumiSpecClusters_type);
   fChain->SetBranchAddress("EcalLumiSpecClusters.energy", &EcalLumiSpecClusters_energy, &b_EcalLumiSpecClusters_energy);
   fChain->SetBranchAddress("EcalLumiSpecClusters.energyError", &EcalLumiSpecClusters_energyError, &b_EcalLumiSpecClusters_energyError);
   fChain->SetBranchAddress("EcalLumiSpecClusters.time", &EcalLumiSpecClusters_time, &b_EcalLumiSpecClusters_time);
   fChain->SetBranchAddress("EcalLumiSpecClusters.timeError", &EcalLumiSpecClusters_timeError, &b_EcalLumiSpecClusters_timeError);
   fChain->SetBranchAddress("EcalLumiSpecClusters.nhits", &EcalLumiSpecClusters_nhits, &b_EcalLumiSpecClusters_nhits);
   fChain->SetBranchAddress("EcalLumiSpecClusters.position.x", &EcalLumiSpecClusters_position_x, &b_EcalLumiSpecClusters_position_x);
   fChain->SetBranchAddress("EcalLumiSpecClusters.position.y", &EcalLumiSpecClusters_position_y, &b_EcalLumiSpecClusters_position_y);
   fChain->SetBranchAddress("EcalLumiSpecClusters.position.z", &EcalLumiSpecClusters_position_z, &b_EcalLumiSpecClusters_position_z);
   fChain->SetBranchAddress("EcalLumiSpecClusters.positionError.xx", &EcalLumiSpecClusters_positionError_xx, &b_EcalLumiSpecClusters_positionError_xx);
   fChain->SetBranchAddress("EcalLumiSpecClusters.positionError.yy", &EcalLumiSpecClusters_positionError_yy, &b_EcalLumiSpecClusters_positionError_yy);
   fChain->SetBranchAddress("EcalLumiSpecClusters.positionError.zz", &EcalLumiSpecClusters_positionError_zz, &b_EcalLumiSpecClusters_positionError_zz);
   fChain->SetBranchAddress("EcalLumiSpecClusters.positionError.xy", &EcalLumiSpecClusters_positionError_xy, &b_EcalLumiSpecClusters_positionError_xy);
   fChain->SetBranchAddress("EcalLumiSpecClusters.positionError.xz", &EcalLumiSpecClusters_positionError_xz, &b_EcalLumiSpecClusters_positionError_xz);
   fChain->SetBranchAddress("EcalLumiSpecClusters.positionError.yz", &EcalLumiSpecClusters_positionError_yz, &b_EcalLumiSpecClusters_positionError_yz);

   fChain->SetBranchAddress("EcalLumiSpecRecHits", &EcalLumiSpecRecHits_, &b_EcalLumiSpecRecHits_);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.cellID", EcalLumiSpecRecHits_cellID, &b_EcalLumiSpecRecHits_cellID);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.energy", EcalLumiSpecRecHits_energy, &b_EcalLumiSpecRecHits_energy);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.energyError", EcalLumiSpecRecHits_energyError, &b_EcalLumiSpecRecHits_energyError);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.time", EcalLumiSpecRecHits_time, &b_EcalLumiSpecRecHits_time);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.timeError", EcalLumiSpecRecHits_timeError, &b_EcalLumiSpecRecHits_timeError);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.position.x", EcalLumiSpecRecHits_position_x, &b_EcalLumiSpecRecHits_position_x);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.position.y", EcalLumiSpecRecHits_position_y, &b_EcalLumiSpecRecHits_position_y);
   fChain->SetBranchAddress("EcalLumiSpecRecHits.position.z", EcalLumiSpecRecHits_position_z, &b_EcalLumiSpecRecHits_position_z);

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

   fChain->SetBranchAddress("LFHCALClusters", &LFHCALClusters_, &b_LFHCALClusters_);
   fChain->SetBranchAddress("LFHCALClusters.type", LFHCALClusters_type, &b_LFHCALClusters_type);
   fChain->SetBranchAddress("LFHCALClusters.energy", LFHCALClusters_energy, &b_LFHCALClusters_energy);
   fChain->SetBranchAddress("LFHCALClusters.energyError", LFHCALClusters_energyError, &b_LFHCALClusters_energyError);
   fChain->SetBranchAddress("LFHCALClusters.time", LFHCALClusters_time, &b_LFHCALClusters_time);
   fChain->SetBranchAddress("LFHCALClusters.timeError", LFHCALClusters_timeError, &b_LFHCALClusters_timeError);
   fChain->SetBranchAddress("LFHCALClusters.nhits", LFHCALClusters_nhits, &b_LFHCALClusters_nhits);
   fChain->SetBranchAddress("LFHCALClusters.position.x", LFHCALClusters_position_x, &b_LFHCALClusters_position_x);
   fChain->SetBranchAddress("LFHCALClusters.position.y", LFHCALClusters_position_y, &b_LFHCALClusters_position_y);
   fChain->SetBranchAddress("LFHCALClusters.position.z", LFHCALClusters_position_z, &b_LFHCALClusters_position_z);
   fChain->SetBranchAddress("LFHCALClusters.positionError.xx", LFHCALClusters_positionError_xx, &b_LFHCALClusters_positionError_xx);
   fChain->SetBranchAddress("LFHCALClusters.positionError.yy", LFHCALClusters_positionError_yy, &b_LFHCALClusters_positionError_yy);
   fChain->SetBranchAddress("LFHCALClusters.positionError.zz", LFHCALClusters_positionError_zz, &b_LFHCALClusters_positionError_zz);
   fChain->SetBranchAddress("LFHCALClusters.positionError.xy", LFHCALClusters_positionError_xy, &b_LFHCALClusters_positionError_xy);
   fChain->SetBranchAddress("LFHCALClusters.positionError.xz", LFHCALClusters_positionError_xz, &b_LFHCALClusters_positionError_xz);
   fChain->SetBranchAddress("LFHCALClusters.positionError.yz", LFHCALClusters_positionError_yz, &b_LFHCALClusters_positionError_yz);

   fChain->SetBranchAddress("LFHCALRecHits", &LFHCALRecHits_, &b_LFHCALRecHits_);
   fChain->SetBranchAddress("LFHCALRecHits.cellID", LFHCALRecHits_cellID, &b_LFHCALRecHits_cellID);
   fChain->SetBranchAddress("LFHCALRecHits.energy", LFHCALRecHits_energy, &b_LFHCALRecHits_energy);
   fChain->SetBranchAddress("LFHCALRecHits.energyError", LFHCALRecHits_energyError, &b_LFHCALRecHits_energyError);
   fChain->SetBranchAddress("LFHCALRecHits.time", LFHCALRecHits_time, &b_LFHCALRecHits_time);
   fChain->SetBranchAddress("LFHCALRecHits.timeError", LFHCALRecHits_timeError, &b_LFHCALRecHits_timeError);
   fChain->SetBranchAddress("LFHCALRecHits.position.x", LFHCALRecHits_position_x, &b_LFHCALRecHits_position_x);
   fChain->SetBranchAddress("LFHCALRecHits.position.y", LFHCALRecHits_position_y, &b_LFHCALRecHits_position_y);
   fChain->SetBranchAddress("LFHCALRecHits.position.z", LFHCALRecHits_position_z, &b_LFHCALRecHits_position_z);




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
