// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 
// 2024/11/28 Template a macro to compile written by Kumaoka
// Please replace the name Algorithm to your analysis name, (anyname ok).
// KumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKumaKuma 

// #define triggerCombineChecker_cxx
#include "triggerCombineChecker.h"
#include "defRootVariables.h"
#include "defRootBranches.h"

#include <random>

#include <TStyle.h>
#include <TCanvas.h>

#include "rootDefoFunctions.cpp"

#include "LoadInputHits.cpp"
#include "LoadInputCalHits.cpp"


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

      m_SimTrackerHitsKuma = LoadInputHits();
      m_SimCalHitsKuma = LoadInputCalHits();

      if(m_iDisplayCount < 9){
         recordEventsForED();
         std::vector<SimTrackerHitKuma > tempSimTrackerHitsKuma = m_SimTrackerHitsKuma;
         std::vector<SimTrackerHitKuma > tempSimCalHitsKuma = m_SimCalHitsKuma;
         m_SimTrackerHitsForED.push_back(std::move(tempSimTrackerHitsKuma));
         m_SimCalHitsForED.push_back(std::move(tempSimCalHitsKuma));
      }

      // Checkuma:: Print MCParticle information for debugging
      // for(size_t iMcP = 0; iMcP < MCParticles_; ++iMcP){
      //    Int_t currentPStatus = MCParticles_generatorStatus[iMcP];

      //    Int_t parentBId = MCParticles_parents_begin[iMcP];
      //    Int_t parentEId = MCParticles_parents_end[iMcP];
         
      //    for(size_t iParentMcP = parentBId; iParentMcP < parentEId; ++iParentMcP){
      //       std::cout << "MCParticle " << iMcP << ", target PStatus = " << currentPStatus << " PID:: " << MCParticles_PDG[iMcP] << " Parent MCParticle " << iParentMcP << " Status: " << MCParticles_generatorStatus[iParentMcP] << ", PID:: " << MCParticles_PDG[iParentMcP] << std::endl;
      //    }

      //    Int_t daughterBId = MCParticles_daughters_begin[iMcP];
      //    Int_t daughterEId = MCParticles_daughters_end[iMcP];
      //    for(size_t iDaughterMcP = daughterBId; iDaughterMcP < daughterEId; ++iDaughterMcP){
      //       std::cout << "MCParticle " << iMcP << ", target PStatus = " << currentPStatus << " PID:: " << MCParticles_PDG[iMcP] << " Daughter MCParticle " << iDaughterMcP << " Status: " << MCParticles_generatorStatus[iDaughterMcP] << ", PID:: " << MCParticles_PDG[iDaughterMcP] << std::endl;
      //    }

      // }

      // std::cout << " ==== Checkuma Number of hits Checks:: B0TrackerRecHits_ = " << B0TrackerRecHits_ \
      // << ", EcalBarrelScFiClusters = " << EcalBarrelScFiClusters_ << ", EcalEndcapNClusters = " << EcalEndcapNClusters_
      // << ", EcalEndcapPClusters = " << EcalEndcapPClusters_ << ", EcalLumiSpecClusters = " << EcalLumiSpecClusters_ \
      // << ", ForwardOffMTrackerRecHits = " << ForwardOffMTrackerRecHits_ << ", ForwardRomanPotRecHits = " << ForwardRomanPotRecHits_\
      // << ", LFHCALClusters = " << LFHCALClusters_<< std::endl;

      DetHitCheck(m_SimCalHitsKuma, m_hDetNumOfHits, m_hDetHitsCombination);

      // == s ==  Hit Time calibration ========================================
      for(int iDet = 0; iDet < m_triggerDetSize; ++iDet) m_SimTrackerHitsKuma.at(iDet).sortByTime();
      Double_t timeOffSet = 0.;
      HitTimeCalibration(timeOffSet);
      // == e ==  Hit Time calibration ========================================
      Int_t checkPhysCount = 0;
      bool bPhysicsEvent = false; // Set the flag for physics event processing
      Double_t physEventTime = - 999999.;
      physEventTime = FindFirstPhysParticle();
      std::cout << " <><><><><><><> First physics particle time: " << physEventTime << std::endl;
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
         
            // == s == ChecKuma:: Print hit times for debugging  ========================
            // for(std::size_t iSub = 0; iSub < m_triggerDetSize; ++iSub){
            //    for(std::size_t iHit = 0; iHit <  m_SimTrackerHitsKuma.at(iSub).getSize(); ++iHit){
            //       std::cout << "Detector " << detId[iSub] << " Hit " << iHit << " Time: " << m_SimTrackerHitsKuma.at(detId[iSub]).getTime(iHit) << std::endl;
            //    }
            // }
            // == e == ChecKuma:: Print hit times for debugging  ========================


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
                     // std::cout << "BaseDet:" << iBaseDet << ", Theta:" << iThetaBin << ", Phi: " << iPhiBin\
                     //    << " numOfhits1 = " << hitsCountsInTSDevInThetaPhi1[iThetaBin][iPhiBin]\
                     //    << " numOfhits2 = " << hitsCountsInTSDevInThetaPhi2[iThetaBin][iPhiBin]\
                     //    << ", baseHitTime = " << baseHitTime << std::endl;
                  }
               }
               // == e ==  Trigger Judgement ==================================================
               if(m_bTrigger){
                  // == s == Check this trigger is for physics event (for this test code) 
                  
                  // 1. Time window Trigger
                  // if(physEventTime > baseHitTime - baseDetTimeRes\
                  //    && physEventTime < baseHitTime + baseDetTimeRes) bPhysicsEvent = true;

                  if(physEventTime > baseHitTime - looseFixTimeWidth\
                     && physEventTime < baseHitTime + looseFixTimeWidth) bPhysicsEvent = true;
                  // 3. Physics Hit Trigger
                  Int_t numOfPhysChMCP = 0;
                  Int_t numOfTrigedPhysChMCP = 0;
                  for (size_t iMcP = 0; iMcP < MCParticles_; ++iMcP) {
                     // == s == Particle Selection  #############################################
                     if(MCParticles_generatorStatus[iMcP] != 1 && MCParticles_generatorStatus[iMcP] != 2) continue;
                     if(MCParticles_generatorStatus[iMcP] > 1999) continue;
                     // if(MCParticles_generatorStatus[iMcP] > 1999) std::cout << "Parent index: " << iMcP << ", status: " << MCParticles_generatorStatus[iMcP] << std::endl;
                     bool bBkgParent = false;
                     for (size_t iParent = MCParticles_parents_begin[iMcP]; iParent < MCParticles_parents_end[iMcP]; ++iParent) {
                        if(MCParticles_generatorStatus[iParent] > 1999){
                           bBkgParent = true;
                           break;
                        }
                     }
                     if(bBkgParent) continue;
                     if(MCParticles_charge[iMcP] == 0) continue;
                     numOfPhysChMCP++;
                     // == e == Particle Selection  #############################################

                     Double_t mcPEdnPointX = MCParticles_endpoint_x[iMcP];
                     Double_t mcPEdnPointY = MCParticles_endpoint_y[iMcP];
                     Double_t mcPEdnPointZ = MCParticles_endpoint_z[iMcP];
                     Double_t mcPEdnPointR = TMath::Sqrt(mcPEdnPointX*mcPEdnPointX + mcPEdnPointY*mcPEdnPointY + mcPEdnPointZ*mcPEdnPointZ);
                     Double_t mcPDirTheta = 0.;
                     if(mcPEdnPointR!=0) mcPDirTheta = TMath::ACos(mcPEdnPointZ/mcPEdnPointR);
                     if(mcPDirTheta >  1.0) mcPDirTheta = 1.0;
                     if(mcPDirTheta < -1.0) mcPDirTheta = -1.0;
                     
                     Double_t mcPDirPhi = TMath::ATan2(mcPEdnPointY, mcPEdnPointX);
                     if(mcPDirPhi < 0) mcPDirPhi += 2*TMath::Pi();
                     Int_t mcPThetaID1 = mcPDirTheta / (2*TMath::Pi()/12.);
                     Int_t mcPThetaID2 = (mcPDirTheta + 2*TMath::Pi()/24.) / (2*TMath::Pi()/12.);
                     Int_t mcPPhiID1 = mcPDirPhi / (2*TMath::Pi()/8.);
                     Int_t mcPPhiID2 = (mcPDirPhi + 2*TMath::Pi()/16.) / (2*TMath::Pi()/8.);
                     

                     bool bDetTrigger1 = false;
                     bool bDetTrigger2 = false;
                     if(hitsCountsInTSDevInThetaPhi1[mcPThetaID1][mcPPhiID1] > 2) bDetTrigger1 = true;
                     if(hitsCountsInTSDevInThetaPhi2[mcPThetaID2][mcPPhiID2] > 2) bDetTrigger2 = true;
                     // std::cout << "mcPThetaID1:" << mcPThetaID1 << ", mcPPhiID1: " << mcPPhiID1 \
                     //    << ", hitsCountsInTSDevInThetaPhi1 = " << hitsCountsInTSDevInThetaPhi1[mcPThetaID1][mcPPhiID1]\
                     //    << ", bDetTrigger1 = " << bDetTrigger1 << std::endl;
                     // std::cout << "mcPThetaID2:" << mcPThetaID2 << ", mcPPhiID2: " << mcPPhiID2 \
                     //    << ", hitsCountsInTSDevInThetaPhi2 = " << hitsCountsInTSDevInThetaPhi2[mcPThetaID2][mcPPhiID2]\
                     //    << ", bDetTrigger2 = " << bDetTrigger2 << std::endl;
                     if((bDetTrigger1 || bDetTrigger2) && (physEventTime - 100. < baseHitTime && baseHitTime < physEventTime + 100.)) numOfTrigedPhysChMCP++;
                  }
                  // if((1.0*numOfTrigedPhysChMCP) / (1.0*numOfPhysChMCP) > 0.49) m_bTrigger = true;
                  if(numOfTrigedPhysChMCP > 0) bPhysicsEvent = true;


                  if(bPhysicsEvent) m_bOncePhysicsTriggered = true;
                  // std::cout << "## det min time = " << baseHitTime - baseDetTimeRes << ", PhysEventTime = " << physEventTime << ", max time = " << baseHitTime + baseDetTimeRes \
                  //     << std::endl;
                  // std::cout << "baseHitTime = " << baseHitTime << ", baseDetTimeRes = " << baseDetTimeRes<< std::endl;
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
                     }
                  }
                  m_bOnceTriggered = true;
                  std::cout << " >>>>> m_bOncePhysicsTriggered: " << m_bOncePhysicsTriggered << " <<<<< " << std::endl;

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
            // if(bPhysicsEvent) m_hTriggerCountsCheck->Fill(1);
            if(bPhysicsEvent&&(checkPhysCount==0)){
               m_hTriggerCountsCheck->Fill(1);
               m_hTriggerCounts_All->Fill(1);
               if(targetDetId < 2) m_hTriggerCounts_ACLGAD->Fill(1);
               else if(targetDetId < 5) m_hTriggerCounts_MPGD->Fill(1);
               else m_hTriggerCounts_MAPS->Fill(1);
            }else{
               m_hTriggerCountsCheck->Fill(3);
               m_hTriggerCounts_All->Fill(2);
               if(targetDetId < 2) m_hTriggerCounts_ACLGAD->Fill(2);
               else if(targetDetId < 5) m_hTriggerCounts_MPGD->Fill(2);
               else m_hTriggerCounts_MAPS->Fill(2);
            }
            if(bPhysicsEvent) checkPhysCount++;
         }

         if(m_bScanedAllTimeWindows&&!m_bOncePhysicsTriggered){
            m_hTriggerCountsCheck->Fill(2);
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


   for(size_t iTrig = 0; iTrig < 3; ++iTrig) m_hTriggerCountsCheck->SetBinError(iTrig + 1, 0.0);
   for(size_t iTrig = 0; iTrig < 2; ++iTrig) m_hTriggerCounts_ACLGAD->SetBinError(iTrig + 1, 0.0);
   for(size_t iTrig = 0; iTrig < 2; ++iTrig) m_hTriggerCounts_MPGD->SetBinError(iTrig + 1, 0.0);
   for(size_t iTrig = 0; iTrig < 2; ++iTrig) m_hTriggerCounts_MAPS->SetBinError(iTrig + 1, 0.0);

   Double_t scaleV = (m_vTargetEvents.size()/2.)/(1000.);
   if(!bTargetEV) scaleV = 1. - scaleV;
   std::cout << "numOfEventLoops : scaleV = " << numOfEventLoops << " : " << scaleV << std::endl;
   m_hMCEtaDist->Scale(scaleV);
   m_hMCThetaDist->Scale(scaleV);

   WriteHists();

   // TApplication app("app", &argc, argv);
   

   for (size_t nHist = 0; nHist < 8; nHist++) {
      m_hEventDisplays[nHist] = nullptr;
      m_hEventDisplays[nHist] = new TH3D(
         Form("hEventDisplays%zu", nHist), ";z [mm];x [mm]; y [mm]", 100, -5000, 5000, 100, -2000, 2000, 100, -2000, 2000
      );
   }
   drawEightEvents();

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

      Double_t hit_Phi = TMath::ATan2(hitY, hitX);
      if(hit_Phi < 0) hit_Phi += 2*TMath::Pi();
      thetaID1 = hit_Theta / (2*TMath::Pi()/12.);
      thetaID2 = (hit_Theta + 2*TMath::Pi()/24.) / (2*TMath::Pi()/12.);
      phiID1 = hit_Phi / (2*TMath::Pi()/8.);
      phiID2 = (hit_Phi + 2*TMath::Pi()/16.) / (2*TMath::Pi()/8.);
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


void triggerCombineChecker::DetHitCheck(std::vector<SimTrackerHitKuma > simCalHits, TH1D* hNumOfHitLists, TH2D* hDetHitLists) {
   for(size_t iDet = 0; iDet < 8; ++iDet){
      if(simCalHits.at(iDet).getHitSize() > 0) hNumOfHitLists->Fill(iDet + 1);
      for(size_t jDet = 0; jDet < 8; ++jDet){
         if(simCalHits.at(iDet).getHitSize() > 0 && simCalHits.at(jDet).getHitSize() > 0) hDetHitLists->Fill(iDet + 1, jDet + 1);

      }
   }
}



// === s === For Event Display =========== #########################################################
void triggerCombineChecker::recordEventsForED(){
   m_iDisplayCount++;
   Event ev;

   for (size_t i = 0; i < MCParticles_; ++i) {

      // == s == Particle Selection  #############################################
      // if(MCParticles_generatorStatus[i] != 1 && MCParticles_generatorStatus[i] != 2) continue;
      // if(MCParticles_generatorStatus[i] > 1999) continue;
      
      if(MCParticles_generatorStatus[i] < 1999) continue;


      // if(MCParticles_generatorStatus[i] > 1999) std::cout << "Parent index: " << i << ", status: " << MCParticles_generatorStatus[i] << std::endl;
      bool bBkgParent = false;
      for (size_t iParent = MCParticles_parents_begin[i]; iParent < MCParticles_parents_end[i]; ++iParent) {
         // if(MCParticles_generatorStatus[iParent] > 1999) std::cout << "Parent index: " << iParent << ", status: " << MCParticles_generatorStatus[iParent] << std::endl;
         // if(MCParticles_generatorStatus[iParent] > 1999){
         if(MCParticles_generatorStatus[iParent] < 1999){
            bBkgParent = true;
            break;
         }
      }
      if(bBkgParent) continue;

      // == e == Particle Selection  #############################################

      Particle p;
      p.vertex = {MCParticles_vertex_x[i], MCParticles_vertex_y[i], MCParticles_vertex_z[i]};
      p.momentum = {MCParticles_momentum_x[i], MCParticles_momentum_y[i], MCParticles_momentum_z[i]};
      p.pdg = MCParticles_PDG[i];
      p.charge = MCParticles_charge[i];
      p.hasEndpoint = true;
      p.endpoint = {MCParticles_endpoint_x[i], MCParticles_endpoint_y[i], MCParticles_endpoint_z[i]};

      ev.particles.push_back(p);
   }
   m_eventsForED.push_back(ev);

}

void triggerCombineChecker::drawOneEvent(const Event& ev, int eventIndex, double fallbackLength) {
  double xmin, xmax, ymin, ymax, zmin, zmax;
   
   computeEventBounds(ev, xmin, xmax, ymin, ymax, zmin, zmax, fallbackLength);
   
   m_hEventDisplays[0]->SetStats(0);
   m_hEventDisplays[eventIndex]->Draw();
   gStyle->SetOptStat(0);
   for (size_t i = 0; i < ev.particles.size(); ++i) {
      
      const auto& p = ev.particles[i];
      const Vec3 a = p.vertex;
      const Vec3 b = getTrackEnd(p, fallbackLength);

      if (mag(sub(b, a)) < 1e-12) continue;

      auto* line = new TPolyLine3D(2);
      line->SetPoint(0, a.z, a.x, a.y);
      line->SetPoint(1, b.z, b.x, b.y);
      line->SetLineColor(colorFromPDG(p.pdg));
      line->SetLineWidth(2);
      line->Draw("same");
   
   }
   

   for (size_t iDet = 0; iDet < m_SimTrackerHitsForED.at(eventIndex).size(); ++iDet) {
      auto* markers = new TPolyMarker3D(m_SimTrackerHitsForED.at(eventIndex).at(iDet).getHitSize());
      for(size_t iHit = 0; iHit < m_SimTrackerHitsForED.at(eventIndex).at(iDet).getHitSize(); ++iHit){
         Double_t hitX = m_SimTrackerHitsForED.at(eventIndex).at(iDet).getPosiX(iHit);
         Double_t hitY = m_SimTrackerHitsForED.at(eventIndex).at(iDet).getPosiY(iHit);
         Double_t hitZ = m_SimTrackerHitsForED.at(eventIndex).at(iDet).getPosiZ(iHit);

         markers->SetPoint(iHit, hitZ, hitX, hitY);
      }
      markers->SetMarkerStyle(20);
      markers->SetMarkerSize(0.4);
      markers->SetMarkerColor(m_TrackDetColors[iDet]);
      markers->Draw("same");
   }
   
   for (size_t iDet = 0; iDet < m_SimCalHitsForED.at(eventIndex).size(); ++iDet) {
      auto* markers = new TPolyMarker3D(m_SimCalHitsForED.at(eventIndex).at(iDet).getHitSize());
      for(size_t iHit = 0; iHit < m_SimCalHitsForED.at(eventIndex).at(iDet).getHitSize(); ++iHit){
         Double_t hitX = m_SimCalHitsForED.at(eventIndex).at(iDet).getPosiX(iHit);
         Double_t hitY = m_SimCalHitsForED.at(eventIndex).at(iDet).getPosiY(iHit);
         Double_t hitZ = m_SimCalHitsForED.at(eventIndex).at(iDet).getPosiZ(iHit);

         markers->SetPoint(iHit, hitZ, hitX, hitY);
      }
      markers->SetMarkerStyle(20);
      markers->SetMarkerSize(0.4);
      markers->SetMarkerColor(m_CalDetColors[iDet]);
      markers->Draw("same");
   }

//   TLatex latex;
//   latex.SetNDC(true);
//   latex.SetTextSize(0.05);
//   latex.DrawLatex(0.12, 0.92, Form("Event %d, N = %zu", eventIndex, ev.particles.size()));
}

void triggerCombineChecker::drawEightEvents(double fallbackLength) {
  auto* c = new TCanvas("c_events", "MCParticle Event Display", 1800, 900);
  c->Divide(4, 2, 0.001, 0.001);
   gStyle->SetOptStat(0);
  const int nPads = 8;
//   const int nDraw = std::min<int>(nPads, m_eventsForED.size());

  for (int i = 0; i < 8; ++i) {
// for (int i = 0; i < nDraw; ++i) {
      c->cd(i + 1);
      gStyle->SetOptStat(0);
      gPad->SetTheta(20);
      gPad->SetPhi(30);
      gPad->SetLeftMargin(0.02);
      gPad->SetRightMargin(0.02);
      gPad->SetTopMargin(0.08);
      gPad->SetBottomMargin(0.02);
      drawOneEvent(m_eventsForED[i], i, fallbackLength);
  }
  c->Update();

  TFile fout("EventDisplays.root", "RECREATE");
  c->Write();
  fout.Close();

  c->SaveAs("EventDisplays.pdf");
}
// === e === For Event Display =========== #########################################################



void triggerCombineChecker::HistInit(){
   oFile = new TFile(oFileName.c_str(), "recreate");

   m_hDetNumOfHits = new TH1D(
      "m_hDetNumOfHits",
      "m_hDetNumOfHits;;number of hits",
      9, 0.5, 9
   );

   m_hDetHitsCombination = new TH2D(
      "m_hDetHitsCombination",
      "m_hDetHitsCombination; trigger; count",
      9, 0.5, 9, 9, 0.5, 9
   );
   for (int i = 0; i < 8; ++i) {
      m_hDetNumOfHits->GetXaxis()->SetBinLabel(i + 1, m_simCalDetNames[i].Data());
      m_hDetHitsCombination->GetXaxis()->SetBinLabel(i + 1, m_simCalDetNames[i].Data());
      m_hDetHitsCombination->GetYaxis()->SetBinLabel(i + 1, m_simCalDetNames[i].Data());
   }
   m_hDetHitsCombination->GetXaxis()->SetBinLabel(9, "CentralTrackers");
   m_hDetHitsCombination->GetYaxis()->SetBinLabel(9, "CentralTrackers");
whi
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

   m_hTriggerCountsCheck = new TH1D(
      "m_hTriggerCountsCheck",
      "m_hTriggerCountsCheck;; count",
      4, 0.5, 4
   );

   TString triggerNamesCheck[3] = {"Triggered (Phys)", "Missed (Phys)", "Fake Trig"};
   for (int i = 0; i < 3; ++i) {
      m_hTriggerCountsCheck->GetXaxis()->SetBinLabel(i + 1, triggerNamesCheck[i].Data());
   }

   m_hTriggerCounts_All = new TH1D(
      "m_hTriggerCounts_All",
      "m_hTriggerCounts_All;; count",
      3, 0.5, 3
   );
   m_hTriggerCounts_ACLGAD = new TH1D(
      "m_hTriggerCounts_ACLGAD",
      "m_hTriggerCounts_ACLGAD;; count",
      3, 0.5, 3
   );
   m_hTriggerCounts_MPGD = new TH1D(
      "m_hTriggerCounts_MPGD",
      "m_hTriggerCounts_MPGD;; count",
      3, 0.5, 3
   );
   m_hTriggerCounts_MAPS = new TH1D(
      "m_hTriggerCounts_MAPS",
      "m_hTriggerCounts_MAPS;; count",
      3, 0.5, 3
   );


   TString triggerNames[2] = {"Phys Trig","Fake Trig"};
   for (int i = 0; i < 2; ++i) {
      m_hTriggerCounts_All->GetXaxis()->SetBinLabel(i + 1, triggerNames[i].Data());
      m_hTriggerCounts_ACLGAD->GetXaxis()->SetBinLabel(i + 1, triggerNames[i].Data());
      m_hTriggerCounts_MPGD->GetXaxis()->SetBinLabel(i + 1, triggerNames[i].Data());
      m_hTriggerCounts_MAPS->GetXaxis()->SetBinLabel(i + 1, triggerNames[i].Data());
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

   // for(size_t nHist = 0; nHist < 8; nHist++) m_hMomEventDisplays[nHist] = new TH2D(Form("hEventDisplays%d", nHist),"", nBins[nHist], minX[nHist],maxX[nHist]);

   
   // for (size_t nHist = 0; nHist < 8; nHist++) {
   //    m_hEventDisplays[nHist] = nullptr;
   //    m_hEventDisplays[nHist] = new TH3D(
   //       Form("hEventDisplays%zu", nHist), "",
   //       100, -5000, 5000,
   //       100, -5000, 5000,
   //       100, -5000, 5000
   //    );
   // }
}


void triggerCombineChecker::ResetValuesForEachEvent(){
   m_SimTrackerHitsKuma.clear();
   m_SimTrackerHitsKuma.shrink_to_fit();

}

void triggerCombineChecker::WriteHists(){
   oFile->cd();

   m_hDetNumOfHits->Write();
   m_hDetHitsCombination->Write();

   m_hEventDisplayZR_Det->Write();
   m_hEventDisplayZR_Det_TF->Write();

   m_hTriggerCountsCheck->Write();
   m_hTriggerCounts_All->Write();
   m_hTriggerCounts_ACLGAD->Write();
   m_hTriggerCounts_MPGD->Write();
   m_hTriggerCounts_MAPS->Write();

   m_hMCEtaDist->Write();
   m_hMCThetaDist->Write();

   oFile->Close();
}


