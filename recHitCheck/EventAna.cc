#include "EventAna.h"
#include <iostream>

EventAna::EventAna(const std::string& inputFile, const std::string& outputFile) : 
    m_iFileName(inputFile), m_oFileName(outputFile)
{
    TH1::AddDirectory(kFALSE);
    m_reader.openFile(m_iFileName);
    
}


void EventAna::EventLoop() {
    OFileInit();
    auto nEvents = m_reader.getEntries("events");
    
    bool bTargetEV = false;
    m_vTargetEvents = {1};
    // 0, 5, 8, 10, 23, 36, 72, 85, 86, 118, 119, 151, 152, 158, 161, 162, 180, 188, 237, 238, 240, 243, 244, 254, 262, 264, 275, 287, 297, 304, 305, 312, 325, 340, 355, 359, 364, 378, 384, 395, 410, 415, 419, 428, 433, 438, 442, 443, 444, 446, 449, 451, 457, 461, 481, 497, 499, 502, 506, 508, 526, 527, 547, 560, 562, 563, 567, 571, 584, 585, 588, 593, 605, 616, 623, 636, 644, 653, 661, 666, 668, 670, 705, 710, 720, 742, 745, 755, 767, 772, 778, 807, 819, 820, 821, 824, 840, 853, 864, 868, 871, 906, 910, 912, 914, 918, 930, 933, 943, 944, 970, 981, 994

    // 36, 119, 305, 359, 506, 585, 636, 666, 820,

    // nEvents = 1000;
    nEvents= 1000;
    if(bTargetEV) nEvents = m_vTargetEvents.size();

    std::cout << "Number of events = " << nEvents << std::endl;

    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        unsigned tempIEvent = iEvent;
        if(bTargetEV) iEvent =  m_vTargetEvents.at(iEvent);
        m_pubEvNum = iEvent;

        if(iEvent%10==0) std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        Double_t physCollTime = FindPhysCollTime(frame);
        FillHitTimesDist(frame, physCollTime);
        
        // m_trkDetsHits = LoadTrackerHitsFromFrame(frame);
        // m_CalClusHits = LoadCalHitsFromFrame(frame);
        
        FillEachSubDetRecDepE(frame);
        // FillEachSubDetDepE();

        ResetValuesForEachEvent();

        iEvent = tempIEvent;
    }

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hTrkRecEDep[iTrkDet][iPKind]->Scale(1./nEvents);
        }
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrkTimeDist[iTrkDet][iPKind]->Scale(1./nEvents);
            // Int_t totCount = m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Integral();
            // m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Scale(1./totCount);
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Scale(1./nEvents);
        }
    }
    for(size_t iCalRec = 0; iCalRec < 9; iCalRec++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalRecEDep[iCalRec][iPKind]->Scale(1./nEvents);
        }
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hCalRecTimeDist[iCalRec][iPKind]->Scale(1./nEvents);
            m_hCalRecNumOfHitsInTS[iCalRec][iPKind]->Scale(1./nEvents);
        }
    }
    for(size_t iCalClu = 0; iCalClu < 9; iCalClu++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalCluEDep[iCalClu][iPKind]->Scale(1./nEvents);
        }
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hCalCluTimeDist[iCalClu][iPKind]->Scale(1./nEvents);
            m_hCalCluNumOfHitsInTS[iCalClu][iPKind]->Scale(1./nEvents);
        }
    }

    Double_t TrigRate_Phys = m_numOfPhysTrig / (1.0*nEvents);
    Double_t TrigRate_Fake = m_numOfFakeTrig / (1.0*nEvents);
    Double_t numOfTS = m_timeWindow / m_timeSliceWidth;
    TrigRate_Fake *= (numOfTS - 1);
    m_hTrigEfficiency->SetBinContent(1, TrigRate_Phys);
    m_hTrigEfficiency->SetBinContent(2, TrigRate_Fake);

    EditHists();
    OFileWrite();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;
    
}

Double_t EventAna::FindPhysCollTime(const podio::Frame& frame){
    const auto& mcP = frame.get<edm4hep::MCParticleCollection>("MCParticles");

    Double_t vtxT = -99999.;
    for(size_t iMcP = 0; iMcP < mcP.size(); iMcP++){
        // if(mcP.at(iMcP).getGeneratorStatus() != 61) continue;
        if(mcP.at(iMcP).getGeneratorStatus() == 1){
        // if(mcP.at(iMcP).getParents_begin() == 0){
            vtxT = mcP.at(iMcP).getTime();
            break;
        }
        
    }
    return vtxT;
}

Double_t EventAna::calibT(Double_t hitT, Double_t hitR){
    Double_t calibT = hitT - hitR * 0.0034;
    return calibT;
}

void EventAna::FillHitTimesDist(const podio::Frame& frame, Double_t vtxTime){
    Int_t trigHitCounts[5][2] = {{},{},{}};

    const auto& mcP = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    Int_t tempDetID = 0;

    // == s == TrkRec loop ==
    for(size_t iDet = 0; iDet < InputDataConfig::kTrkRecCollections.size(); iDet++){
        Int_t repDetId = 8; // FarForwardRomanPot
        if(tempDetID>9) repDetId = 7; // FarForwardMT
        else if(tempDetID>8) repDetId = 6; // B0
        else if(tempDetID>7) repDetId = 5; // ETOF
        else if(tempDetID>6) repDetId = 4; // BTOF
        else if(tempDetID>4) repDetId = 3; // EMPGD
        else if(tempDetID>2) repDetId = 2; // BMPGD
        else if(tempDetID>1) repDetId = 1; // ESi
        else repDetId = 0; // BSi

        const auto& recHits = frame.get<edm4eic::TrackerHitCollection>(std::string(InputDataConfig::kTrkRecCollections.at(iDet)));
        const auto& rawHits = frame.get<edm4eic::RawTrackerHitCollection>(std::string(InputDataConfig::kTrkRawCollections.at(iDet)));
        const auto& associations \
            = frame.get<edm4eic::MCRecoTrackerHitAssociationCollection>(std::string(InputDataConfig::kTrkRawAssociationCollections.at(iDet)));
        const auto& simHits =frame.get<edm4hep::SimTrackerHitCollection>(std::string(InputDataConfig::kTrkSimCollections.at(iDet)));

        Int_t countOfHitsInTS[2] = {0, 0};
        for(size_t iHit = 0; iHit < recHits.size(); iHit++){
            auto recHit = recHits.at(iHit);
            auto rawHitFromRec = recHit.getRawHit();
            auto recRawID = rawHitFromRec.getObjectID();
            
            for (const auto& assoc : associations) {
                auto rawHitFromAssoc = assoc.getRawHit();
                auto assocRawID = rawHitFromAssoc.getObjectID();
                if(recRawID.index == assocRawID.index && recRawID.collectionID == assocRawID.collectionID) {
                    auto simHit = assoc.getSimHit();
                    auto relMcP = simHit.getParticle();
                    auto relMcPId = relMcP.getObjectID();
                    Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();

                    // Int_t pKindId = relMcPIdGenId/1000 -1;
                    // if(pKindId < 0) pKindId = 0;
                    Int_t bPhys = 1;
                    if(relMcPIdGenId < 1999) bPhys = 0;
                    
                    const auto pos = recHit.getPosition();
                    Double_t recHitR = std::sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
                    Double_t calibedTime = calibT(recHit.getTime(), recHitR);
                    
                    Double_t calibedTimeAlined = calibedTime - vtxTime;
                    m_hTrkTimeDist[repDetId][bPhys]->Fill(calibedTimeAlined);
                    if((calibedTimeAlined + m_TrkTimeRes[repDetId] > -5.)&&(calibedTimeAlined - m_TrkTimeRes[repDetId] < 10.)) countOfHitsInTS[bPhys]++;
                }
            }

        }
        tempDetID++;

        if(repDetId<2) continue;
        // std::cout << "repDetId-2: bPhys" << repDetId-2 << std::endl;
        m_hTrkNumOfHitsInTS[repDetId-2][0]->Fill(countOfHitsInTS[0]);
        m_hTrkNumOfHitsInTS[repDetId-2][1]->Fill(countOfHitsInTS[1]);

        if((repDetId == 2)||(repDetId == 4)){
            trigHitCounts[0][0] += countOfHitsInTS[0]+countOfHitsInTS[1];
            trigHitCounts[0][1] += countOfHitsInTS[1];
        }else if((repDetId == 3)||(repDetId == 5)){
            trigHitCounts[1][0] += countOfHitsInTS[0]+countOfHitsInTS[1];
            trigHitCounts[1][1] += countOfHitsInTS[1];
        }else if(repDetId == 6){
            trigHitCounts[2][0] += countOfHitsInTS[0]+countOfHitsInTS[1];
            trigHitCounts[2][1] += countOfHitsInTS[1];
        }
        
    }
    // == e == TrkRec loop ==

    // == s == CalRec loop ==
    for(size_t iCalRec = 0; iCalRec < InputDataConfig::kCalRecCollections.size(); iCalRec++){
        const auto& recs = frame.get<edm4eic::CalorimeterHitCollection>(std::string(InputDataConfig::kCalRecCollections.at(iCalRec)));
        const auto& rawHits = frame.get<edm4hep::RawCalorimeterHitCollection>(std::string(InputDataConfig::kCalRawCollections.at(iCalRec)));
        const auto& associations \
            = frame.get<edm4eic::MCRecoCalorimeterHitAssociationCollection>(std::string(InputDataConfig::kCalRawAssociations.at(iCalRec)));
        Int_t countOfHitsInTS[2] = {0, 0};
        for(size_t iCalRecHit = 0; iCalRecHit < recs.size(); iCalRecHit++){
            auto calRecHit = recs.at(iCalRecHit);
            auto rawHitFromRec = calRecHit.getRawHit();
            auto recRawID = rawHitFromRec.getObjectID();
            
            for (const auto& assoc : associations) {
                auto rawHitFromAssoc = assoc.getRawHit();
                auto assocRawID = rawHitFromAssoc.getObjectID();
                if(recRawID.index == assocRawID.index && recRawID.collectionID == assocRawID.collectionID) {
                    auto simHit = assoc.getSimHit();
                    for (const auto& contrib : simHit.getContributions()) {
                        const auto& relMcP = contrib.getParticle();
                        auto relMcPId = relMcP.getObjectID();
                    

                        Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
                        Int_t bPhys = 1;
                        if(relMcPIdGenId < 1999) bPhys = 0;
                            
                        const auto pos = calRecHit.getPosition();
                        Double_t recHitR = std::sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
                        Double_t calibedTime = calibT(calRecHit.getTime(), recHitR);
                        Double_t calibedTimeAlined = calibedTime - vtxTime;

                        m_hCalRecTimeDist[iCalRec][bPhys]->Fill(calibedTimeAlined);
                        if((calibedTimeAlined + m_CalTimeRes[iCalRec] > -5.)&&(calibedTimeAlined - m_CalTimeRes[iCalRec] < 10.)) countOfHitsInTS[bPhys]++;
                    }
                }
            }
        }
        if(countOfHitsInTS[0] > 100) countOfHitsInTS[0] = 99;
        if(countOfHitsInTS[1] > 100) countOfHitsInTS[1] = 99;
        m_hCalRecNumOfHitsInTS[iCalRec][0]->Fill(countOfHitsInTS[0]);
        m_hCalRecNumOfHitsInTS[iCalRec][1]->Fill(countOfHitsInTS[1]);

        if(iCalRec == 4) { // ECalEP
            trigHitCounts[3][0] += countOfHitsInTS[0]+countOfHitsInTS[1]; 
            trigHitCounts[3][1] += countOfHitsInTS[1];
        }
        if(iCalRec == 5) { // ZDC
            trigHitCounts[4][0] += countOfHitsInTS[0]+countOfHitsInTS[1]; 
            trigHitCounts[4][1] += countOfHitsInTS[1];
        } 

        
    }// == e == CalRec loop ends ==


    // == s == CalClu loop ==
    // for(size_t iCalClu = 0; iCalClu < InputDataConfig::kCalCluCollections.size(); iCalClu++){
    //     const auto& clus = frame.get<edm4eic::ClusterCollection>(std::string(InputDataConfig::kCalCluCollections.at(iCalClu)));
    //     const auto& associations \
    //         = frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>(std::string(InputDataConfig::kCalCluAssociations.at(iCalClu)));
    //     Int_t countOfHitsInTS[2] = {0, 0};
    //     for(size_t iClu = 0; iClu < clus.size(); iClu++){
    //         auto clu = clus.at(iClu);
    //         for (const auto& assoc : associations) {
    //             if (assoc.getRec() != clu)continue;
    //             const auto& mcP = assoc.getSim();
    //             // Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
    //             Int_t relMcPIdGenId = mcP.getGeneratorStatus();
    //             Int_t bPhys = 1;
    //             if(relMcPIdGenId < 1999) bPhys = 0;
    //             // 
    //             const auto pos = clu.getPosition();
    //             Double_t cluR = std::sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
    //             Double_t calibedTime = calibT(clu.getTime(), cluR);
    //             Double_t calibedTimeAlined = calibedTime - vtxTime;
    //             m_hCalCluTimeDist[iCalClu][bPhys]->Fill(calibedTimeAlined);
    //             if((calibedTimeAlined + m_CalTimeRes[iCalClu] > -5.)&&(calibedTimeAlined - m_CalTimeRes[iCalClu] < 10.)) countOfHitsInTS[bPhys]++; 
    //         }
    //     }  
    //     m_hCalCluNumOfHitsInTS[iCalClu][0]->Fill(countOfHitsInTS[0]);
    //     m_hCalCluNumOfHitsInTS[iCalClu][1]->Fill(countOfHitsInTS[1]);
    // }// == e == CalClu loop ends ==


    for(size_t iTrig = 0; iTrig < 5; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->Fill(trigHitCounts[iTrig][iPKind]);
        }
    }

    // Trig1
    // if(trigHitCounts[0][0]>18 || trigHitCounts[1][0]>2) m_numOfPhysTrig++; // Barrel || Endcap
    // if(trigHitCounts[0][1]>18 || trigHitCounts[1][1]>2) m_numOfFakeTrig++; // Barrel || Endcap

    // Trig2
    if(trigHitCounts[2][0]>0) m_numOfPhysTrig++; // B0Trk
    else if(trigHitCounts[1][0]>2) m_numOfPhysTrig++; // EMPGD || ETOF
    else if(trigHitCounts[3][0]>20) m_numOfPhysTrig++; // EcalEP
    else if(trigHitCounts[4][0]>20) m_numOfPhysTrig++; // EcalZDC
    if(trigHitCounts[2][1]>0) m_numOfFakeTrig++; // B0Trk
    else if(trigHitCounts[1][1]>2) m_numOfFakeTrig++; // EMPGD || ETOF
    else if(trigHitCounts[3][1]>20) m_numOfFakeTrig++; // EcalEP
    else if(trigHitCounts[4][1]>20) m_numOfFakeTrig++; // EcalZDC
    
    // if(trigHitCounts[1][0]<3) m_vTargetEvents.push_back(m_pubEvNum);
    if((trigHitCounts[2][0]<1)&&(trigHitCounts[3][0]<21)&&(trigHitCounts[4][0]<21)) m_vTargetEvents.push_back(m_pubEvNum);
}



void EventAna::FillEachSubDetDepE(){
    for(size_t iDet = 0; iDet < m_trkDetsHits.size(); iDet++){
        for(size_t iHit = 0; iHit < m_trkDetsHits.at(iDet).getHitSize(); iHit++){
            Double_t eDep = m_trkDetsHits.at(iDet).getEDep(iHit);
            if(iDet==0||iDet==1) m_hBSiRecDepE->Fill(eDep);
            else if(iDet==2) m_hESiRecDepE->Fill(eDep);
            else if(iDet==3||iDet==4) m_hBMPGDRecDepE->Fill(eDep);
            else if(iDet==5||iDet==6) m_hEMPGDRecDepE->Fill(eDep);
            else if(iDet==7) m_hBTOFRecDepE->Fill(eDep);
            else if(iDet==8) m_hETOFRecDepE->Fill(eDep);
            else if(iDet==9) m_hB0RecDepE->Fill(eDep);

        }
    }
}

void EventAna::FillEachSubDetRecDepE(const podio::Frame& frame){

    const auto& mcP = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    Int_t tempDetID = 0;

    // == s == TrkRec loop ==
    for(size_t iDet = 0; iDet < InputDataConfig::kTrkRecCollections.size(); iDet++){
        Int_t repDetId = 8;
        if(tempDetID>9) repDetId = 7;
        else if(tempDetID>8) repDetId = 6;
        else if(tempDetID>7) repDetId = 5;
        else if(tempDetID>6) repDetId = 4;
        else if(tempDetID>4) repDetId = 3;
        else if(tempDetID>2) repDetId = 2;
        else if(tempDetID>1) repDetId = 1;
        else repDetId = 0;

        const auto& recHits = frame.get<edm4eic::TrackerHitCollection>(std::string(InputDataConfig::kTrkRecCollections.at(iDet)));
        const auto& rawHits = frame.get<edm4eic::RawTrackerHitCollection>(std::string(InputDataConfig::kTrkRawCollections.at(iDet)));
        const auto& associations \
            = frame.get<edm4eic::MCRecoTrackerHitAssociationCollection>(std::string(InputDataConfig::kTrkRawAssociationCollections.at(iDet)));
        const auto& simHits =frame.get<edm4hep::SimTrackerHitCollection>(std::string(InputDataConfig::kTrkSimCollections.at(iDet)));

        for(size_t iHit = 0; iHit < recHits.size(); iHit++){
            auto recHit = recHits.at(iHit);
            auto rawHitFromRec = recHit.getRawHit();
            auto recRawID = rawHitFromRec.getObjectID();

            Double_t depE = 1000 * recHit.getEdep();

            for (const auto& assoc : associations) {
                auto rawHitFromAssoc = assoc.getRawHit();
                auto assocRawID = rawHitFromAssoc.getObjectID();
                if(recRawID.index == assocRawID.index && recRawID.collectionID == assocRawID.collectionID) {
                    auto simHit = assoc.getSimHit();
                    auto relMcP = simHit.getParticle();
                    auto relMcPId = relMcP.getObjectID();
                    Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();

                    Int_t pKindId = relMcPIdGenId/1000 -1;
                    if(pKindId < 0) pKindId = 0;
                    m_hTrkRecEDep[repDetId][pKindId]->Fill(depE);
                }
            }

        }
        tempDetID++;
    }


    // == s == CalRec loop ==
    for(size_t iCalRec = 0; iCalRec < InputDataConfig::kCalRecCollections.size(); iCalRec++){

        const auto& recs = frame.get<edm4eic::CalorimeterHitCollection>(std::string(InputDataConfig::kCalRecCollections.at(iCalRec)));
        const auto& rawHits = frame.get<edm4hep::RawCalorimeterHitCollection>(std::string(InputDataConfig::kCalRawCollections.at(iCalRec)));
        const auto& associations \
            = frame.get<edm4eic::MCRecoCalorimeterHitAssociationCollection>(std::string(InputDataConfig::kCalRawAssociations.at(iCalRec)));

        for(size_t iCalRecHit = 0; iCalRecHit < recs.size(); iCalRecHit++){
            auto calRecHit = recs.at(iCalRecHit);
            auto rawHitFromRec = calRecHit.getRawHit();
            auto recRawID = rawHitFromRec.getObjectID();
            
            Double_t depE = 1000 * calRecHit.getEnergy();
            for (const auto& assoc : associations) {
                auto rawHitFromAssoc = assoc.getRawHit();
                auto assocRawID = rawHitFromAssoc.getObjectID();
                if(recRawID.index == assocRawID.index && recRawID.collectionID == assocRawID.collectionID) {
                    auto simHit = assoc.getSimHit();
                    for (const auto& contrib : simHit.getContributions()) {
                        const auto& relMcP = contrib.getParticle();
                        auto relMcPId = relMcP.getObjectID();
                  
                        Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
                        Int_t bPhys = 1;
                        if(relMcPIdGenId < 1999) bPhys = 0;

                        Int_t pKindId = relMcPIdGenId/1000 -1;
                        if(pKindId < 0) pKindId = 0;
                        m_hCalRecEDep[iCalRec][pKindId]->Fill(depE);
                    }
                }
                
            }

        }

    }// == e == CalRec loop ends ==

    // // == s == CalClu loop ==
    // for(size_t iCalClu = 0; iCalClu < InputDataConfig::kCalCluCollections.size(); iCalClu++){
    //     const auto& clus = frame.get<edm4eic::ClusterCollection>(std::string(InputDataConfig::kCalCluCollections.at(iCalClu)));
    //     const auto& associations \
    //         = frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>(std::string(InputDataConfig::kCalCluAssociations.at(iCalClu)));
    //     for(size_t iClu = 0; iClu < clus.size(); iClu++){
    //         auto clu = clus.at(iClu);
    //         Double_t depE = 1000 * clu.getEnergy();
    //         for (const auto& assoc : associations) {
    //             if (assoc.getRec() != clu)continue;
    //             const auto& mcP = assoc.getSim();
    //             // Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
    //             Int_t relMcPIdGenId = mcP.getGeneratorStatus();
    //             Int_t pKindId = relMcPIdGenId/1000 -1;
    //             if(pKindId < 0) pKindId = 0;
    //             m_hCalCluEDep[iCalClu][pKindId]->Fill(depE);
    //         }
    //     }
    // }// == e == CalClu loop ==


}



void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;

    m_dirTrkRecDepE = oFile->mkdir("TrkRecDepEDirs");
    for (const auto& trkName : m_trkShortDetName) {
        m_mapTrkRecDepEDirs[trkName.Data()] = m_dirTrkRecDepE->mkdir(trkName.Data());
    }
    m_dirCalRecDepE = oFile->mkdir("CalRecDepEDirs");
    for (const auto& calName : m_calRecShortDetName) {
        m_mapCalRecDepEDirs[calName.Data()] = m_dirCalRecDepE->mkdir(calName.Data());
    }
    m_dirCalCluDepE = oFile->mkdir("CalCluDepEDirs");
    for (const auto& calName : m_calShortDetName) {
        m_mapCalCluDepEDirs[calName.Data()] = m_dirCalCluDepE->mkdir(calName.Data());
    }

    m_dirTrkRecTimeDist = oFile->mkdir("TrkRecTimeDistDirs");
    for (const auto& trkName : m_trkShortDetName) {
        m_mapTrkRecTimeDistDirs[trkName.Data()] = m_dirTrkRecTimeDist->mkdir(trkName.Data());
    }
    m_dirCalRecTimeDist = oFile->mkdir("CalRecTimeDistDirs");
    for (const auto& calName : m_calRecShortDetName) {
        m_mapCalRecTimeDistDirs[calName.Data()] = m_dirCalRecTimeDist->mkdir(calName.Data());
    }
    m_dirCalCluTimeDist = oFile->mkdir("CalCluTimeDistDirs");
    for (const auto& calName : m_calShortDetName) {
        m_mapCalCluTimeDistDirs[calName.Data()] = m_dirCalCluTimeDist->mkdir(calName.Data());
    }

    m_dirTrkRecNumOfHitsInTS = oFile->mkdir("TrkRecNumOfHitsInTSDirs");
    for (const auto& trkName : m_trkShortDetName) {
        m_mapTrkRecNumOfHitsInTSDirs[trkName.Data()] = m_dirTrkRecNumOfHitsInTS->mkdir(trkName.Data());
    }
    m_dirCalRecNumOfHitsInTS = oFile->mkdir("CalRecNumOfHitsInTSDirs");
    for (const auto& calName : m_calRecShortDetName) {
        m_mapCalRecNumOfHitsInTSDirs[calName.Data()] = m_dirCalRecNumOfHitsInTS->mkdir(calName.Data());
    }
    m_dirCalCluNumOfHitsInTS = oFile->mkdir("CalCluNumOfHitsInTSDirs");
    for (const auto& calName : m_calShortDetName) {
        m_mapCalCluNumOfHitsInTSDirs[calName.Data()] = m_dirCalCluNumOfHitsInTS->mkdir(calName.Data());
    }

    TString histName = "";
    TString histTitle = "";

    m_hBSiRecDepE = new TH1D("m_hBSiRecDepE", "m_hBSiRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hESiRecDepE = new TH1D("m_hESiRecDepE", "m_hESiRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hBMPGDRecDepE = new TH1D("m_hBMPGDRecDepE", "m_hBMPGDRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hEMPGDRecDepE = new TH1D("m_hEMPGDRecDepE", "m_hEMPGDRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hBTOFRecDepE = new TH1D("m_hBTOFRecDepE", "m_hBTOFRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hETOFRecDepE = new TH1D("m_hETOFRecDepE", "m_hETOFRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hB0RecDepE = new TH1D("m_hB0RecDepE", "m_hB0RecDepE; depE [MeV];count", 100, 0, 0.1);

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hDetRecDepE_%s_%s",m_trkShortDetName[iTrkDet].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hTrkRecEDep[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 0.50);
        }
    }

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempPhysName = "Phys";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hTrkTimeDist%s_%s",m_trkShortDetName[iTrkDet].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hTrkTimeDist[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hTrkNumOfHitsInTS%s_%s",m_trkShortDetName[iTrkDet].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 20, 0, 20);
        }
    }


    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hCalRecRecDepE_%s_%s",m_calRecShortDetName[iCalRec].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hCalRecEDep[iCalRec][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100.0);
        }
    }

    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempPhysName = "Phys";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hCalRecTimeDist%s_%s",m_calRecShortDetName[iCalRec].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hCalRecTimeDist[iCalRec][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hCalRecNumOfHitsInTS%s_%s",m_calRecShortDetName[iCalRec].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hCalRecNumOfHitsInTS[iCalRec][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100);
        }
    }


    for(size_t iCalClu = 0; iCalClu < 6; iCalClu++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hCalCluRecDepE_%s_%s",m_calShortDetName[iCalClu].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hCalCluEDep[iCalClu][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100.0);
        }
    }

    for(size_t iCalClu = 0; iCalClu < 6; iCalClu++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempPhysName = "Phys";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hCalCluTimeDist%s_%s",m_calShortDetName[iCalClu].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hCalCluTimeDist[iCalClu][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hCalCluNumOfHitsInTS%s_%s",m_calShortDetName[iCalClu].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hCalCluNumOfHitsInTS[iCalClu][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 20, 0, 20);
        }
    }


    for(size_t iTrig = 0; iTrig < 5; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempTrigName = "BTOF+BMPGD";
            if(iTrig == 1) tempTrigName = "ETOF+EMPGD";
            else if(iTrig == 2) tempTrigName = "B0";
            else if(iTrig == 3) tempTrigName = "EcalP";
            else if(iTrig == 4) tempTrigName = "ZDC";
            TString tempPhysName = "Phys+BKG";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hTrigDetNumOfHitsInTS_%s_%s", tempTrigName.Data(), tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count", histName.Data());
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 100);
        }
    }

    m_hTrigEfficiency = new TH1D("m_hTrigEfficiency", "m_hTrigEfficiency;;Efficiency", 2, 0, 2);
    m_hTrigEfficiency->GetXaxis()->SetBinLabel(1, "Phys");
    m_hTrigEfficiency->GetXaxis()->SetBinLabel(2, "Fake");

}

void EventAna::EditHists() {
    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hTrkRecEDep[iTrkDet][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hTrkRecEDep[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hTrkTimeDist[iTrkDet][iPKind]->SetLineColor(histColor);
            m_hTrkTimeDist[iTrkDet][iPKind]->SetLineWidth(5);

            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->SetLineColor(histColor);
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalRec = 0; iCalRec < 6; iCalRec++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalCluEDep[iCalRec][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hCalCluEDep[iCalRec][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalRec = 0; iCalRec < 6; iCalRec++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hCalCluTimeDist[iCalRec][iPKind]->SetLineColor(histColor);
            m_hCalCluTimeDist[iCalRec][iPKind]->SetLineWidth(5);

            m_hCalCluNumOfHitsInTS[iCalRec][iPKind]->SetLineColor(histColor);
            m_hCalCluNumOfHitsInTS[iCalRec][iPKind]->SetLineWidth(5);
        }
    }



    for(size_t iCalClu = 0; iCalClu < 6; iCalClu++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalCluEDep[iCalClu][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hCalCluEDep[iCalClu][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalClu = 0; iCalClu < 6; iCalClu++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hCalCluTimeDist[iCalClu][iPKind]->SetLineColor(histColor);
            m_hCalCluTimeDist[iCalClu][iPKind]->SetLineWidth(5);

            m_hCalCluNumOfHitsInTS[iCalClu][iPKind]->SetLineColor(histColor);
            m_hCalCluNumOfHitsInTS[iCalClu][iPKind]->SetLineWidth(5);
        }
    }


    for(size_t iTrig = 0; iTrig < 3; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->SetLineColor(histColor);
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->SetLineWidth(5);
        }
    }

    m_hTrigEfficiency->SetLineColor(820+4);
    m_hTrigEfficiency->SetLineWidth(5);
}

void EventAna::OFileWrite() {
    std::cout << "OFileWrite" << std::endl;
    oFile->cd();

    m_hBSiRecDepE->Write();
    m_hESiRecDepE->Write();
    m_hBMPGDRecDepE->Write();
    m_hEMPGDRecDepE->Write();
    m_hBTOFRecDepE->Write();
    m_hETOFRecDepE->Write();
    m_hB0RecDepE->Write();

    for(size_t iTrkDet = 0; iTrkDet < 9; iTrkDet++){
        const auto& detName = m_trkShortDetName[iTrkDet];
        TDirectory* dirTrkRecDepE = m_dirTrkRecDepE->GetDirectory(detName.Data());
        if (!dirTrkRecDepE) dirTrkRecDepE = m_dirTrkRecDepE->mkdir(detName.Data());

        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            const auto& pKindName = m_physKindShortName[iPKind];
            dirTrkRecDepE->WriteObject(m_hTrkRecEDep[iTrkDet][iPKind], pKindName.Data());
        }

        TDirectory* dirTrkTimeDist = m_dirTrkRecTimeDist->GetDirectory(detName.Data());
        if (!dirTrkTimeDist) dirTrkTimeDist = m_dirTrkRecTimeDist->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirTrkTimeDist->WriteObject(m_hTrkTimeDist[iTrkDet][iPKind], pKindName.Data());
        }

        TDirectory* dirTrkNumOfHitsInTS = m_dirTrkRecNumOfHitsInTS->GetDirectory(detName.Data());
        if (!dirTrkNumOfHitsInTS) dirTrkNumOfHitsInTS = m_dirTrkRecNumOfHitsInTS->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirTrkNumOfHitsInTS->WriteObject(m_hTrkNumOfHitsInTS[iTrkDet][iPKind], pKindName.Data());
        }
    }
    
    
    for(size_t iCalRec = 0; iCalRec < 7; iCalRec++){
        const auto& detName = m_calRecShortDetName[iCalRec];
        TDirectory* dirCalRecDepE = m_dirCalRecDepE->GetDirectory(detName.Data());
        if (!dirCalRecDepE) dirCalRecDepE = m_dirCalRecDepE->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            const auto& pKindName = m_physKindShortName[iPKind];
            dirCalRecDepE->WriteObject(m_hCalRecEDep[iCalRec][iPKind], pKindName.Data());
        }
        TDirectory* dirCalRecTimeDist = m_dirCalRecTimeDist->GetDirectory(detName.Data());
        if (!dirCalRecTimeDist) dirCalRecTimeDist = m_dirCalRecTimeDist->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirCalRecTimeDist->WriteObject(m_hCalRecTimeDist[iCalRec][iPKind], pKindName.Data());
        }
        TDirectory* dirCalRecNumOfHitsInTS = m_dirCalRecNumOfHitsInTS->GetDirectory(detName.Data());
        if (!dirCalRecNumOfHitsInTS) dirCalRecNumOfHitsInTS = m_dirCalRecNumOfHitsInTS->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirCalRecNumOfHitsInTS->WriteObject(m_hCalRecNumOfHitsInTS[iCalRec][iPKind], pKindName.Data());
        }
    }

    for(size_t iCalClu = 0; iCalClu < 6; iCalClu++){
        const auto& detName = m_calShortDetName[iCalClu];
        TDirectory* dirCalCluDepE = m_dirCalCluDepE->GetDirectory(detName.Data());
        if (!dirCalCluDepE) dirCalCluDepE = m_dirCalCluDepE->mkdir(detName.Data());

        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            const auto& pKindName = m_physKindShortName[iPKind];
            dirCalCluDepE->WriteObject(m_hCalCluEDep[iCalClu][iPKind], pKindName.Data());
        }

        TDirectory* dirCalCluTimeDist = m_dirCalCluTimeDist->GetDirectory(detName.Data());
        if (!dirCalCluTimeDist) dirCalCluTimeDist = m_dirCalCluTimeDist->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirCalCluTimeDist->WriteObject(m_hCalCluTimeDist[iCalClu][iPKind], pKindName.Data());
        }

        TDirectory* dirCalCluNumOfHitsInTS = m_dirCalCluNumOfHitsInTS->GetDirectory(detName.Data());
        if (!dirCalCluNumOfHitsInTS) dirCalCluNumOfHitsInTS = m_dirCalCluNumOfHitsInTS->mkdir(detName.Data());
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            const auto& pKindName = m_biPhysName[iPKind];
            dirCalCluNumOfHitsInTS->WriteObject(m_hCalCluNumOfHitsInTS[iCalClu][iPKind], pKindName.Data());
        }
    }

    for(size_t iTrig = 0; iTrig < 3; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->Write();
        }
    }

    m_hTrigEfficiency->Write();
    
    oFile->Close();
}

void EventAna::ResetValuesForEachEvent() {
    m_trkDetsHits.clear();
}

