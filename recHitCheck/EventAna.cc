#include "EventAna.h"
#include <iostream>

EventAna::EventAna(const std::string& inputFile, const std::string& outputFile) : 
    m_iFileName(inputFile), m_oFileName(outputFile)
{
    m_reader.openFile(m_iFileName);
}


void EventAna::EventLoop() {
    OFileInit();
    auto nEvents = m_reader.getEntries("events");
    std::cout << "Number of events = " << nEvents << std::endl;

    bool bTargetEV = false;
    m_vTargetEvents = {36, 119, 305, 359, 506, 585, 636, 666, 820};
    // 0, 5, 8, 10, 23, 36, 72, 85, 86, 118, 119, 151, 152, 158, 161, 162, 180, 188, 237, 238, 240, 243, 244, 254, 262, 264, 275, 287, 297, 304, 305, 312, 325, 340, 355, 359, 364, 378, 384, 395, 410, 415, 419, 428, 433, 438, 442, 443, 444, 446, 449, 451, 457, 461, 481, 497, 499, 502, 506, 508, 526, 527, 547, 560, 562, 563, 567, 571, 584, 585, 588, 593, 605, 616, 623, 636, 644, 653, 661, 666, 668, 670, 705, 710, 720, 742, 745, 755, 767, 772, 778, 807, 819, 820, 821, 824, 840, 853, 864, 868, 871, 906, 910, 912, 914, 918, 930, 933, 943, 944, 970, 981, 994

    // 36, 119, 305, 359, 506, 585, 636, 666, 820,

    nEvents = 1000;
    // nEvents= 5;
    if(bTargetEV) nEvents = m_vTargetEvents.size();

    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        unsigned tempIEvent = iEvent;
        if(bTargetEV) iEvent =  m_vTargetEvents.at(iEvent);
        m_pubEvNum = iEvent;

        if(iEvent%10==0) std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        Double_t physCollTime = FindPhysCollTime(frame);
        FillHitTimesDist(frame, physCollTime);

        // m_trkDetsHits = LoadTrackerHitsFromFrame(frame);
        // m_calDetsHits = LoadCalHitsFromFrame(frame);

        FillEachSubDetRecDepE(frame);
        // FillEachSubDetDepE();

        ResetValuesForEachEvent();

        iEvent = tempIEvent;
    }

    for(size_t iTrkDet = 0; iTrkDet < 4; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrkTimeDist[iTrkDet][iPKind]->Scale(1./nEvents);
            Int_t totCount = m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Integral();
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Scale(1./totCount);
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
        if(mcP.at(iMcP).getGeneratorStatus() != 61) continue;
        vtxT = mcP.at(iMcP).getTime();
    }
    return vtxT;
}

Double_t EventAna::calibT(Double_t hitT, Double_t hitR){
    Double_t calibT = hitT - hitR * 0.0034;
    return calibT;
}

void EventAna::FillHitTimesDist(const podio::Frame& frame, Double_t vtxTime){
    Int_t trigHitCounts[3][2] = {{},{},{}};

    const auto& mcP = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    Int_t tempDetID = 0;
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
                    
                    if(repDetId<2) continue;
                    Double_t calibedTimeAlined = calibedTime - vtxTime;
                    m_hTrkTimeDist[repDetId-2][bPhys]->Fill(calibedTimeAlined);
                    if((calibedTimeAlined > -5.)&&(calibedTimeAlined < 10.)) countOfHitsInTS[bPhys]++;
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


    // == s == CalDet loop ==
    for(size_t iCalDet = 0; iCalDet < InputDataConfig::kCalCluCollections.size(); iCalDet++){

        const auto& clus = frame.get<edm4eic::ClusterCollection>(std::string(InputDataConfig::kCalCluCollections.at(iCalDet)));
        const auto& associations \
            = frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>(std::string(InputDataConfig::kCalClusterAssociations.at(iCalDet)));

        Int_t countOfHitsInTS[2] = {0, 0};
        for(size_t iClu = 0; iClu < clus.size(); iClu++){
            auto clu = clus.at(iClu);
            
            for (const auto& assoc : associations) {
                if (assoc.getRec() != clu)continue;

                const auto& mcP = assoc.getSim();
                // Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
                Int_t relMcPIdGenId = mcP.getGeneratorStatus();

                // auto simHit = assoc.getSimHit();
                // auto relMcP = simHit.getParticle();
                // auto relMcPId = relMcP.getObjectID();
                // Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
                // Int_t relMcPIdGenId = relMcP.getGeneratorStatus();

                // Int_t pKindId = relMcPIdGenId/1000 -1;
                // if(pKindId < 0) pKindId = 0;
                Int_t bPhys = 1;
                if(relMcPIdGenId < 1999) bPhys = 0;
                    
                const auto pos = clu.getPosition();
                Double_t cluR = std::sqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
                Double_t calibedTime = calibT(clu.getTime(), cluR);
                
                Double_t calibedTimeAlined = calibedTime - vtxTime;
                m_hCalDetTimeDist[iCalDet][bPhys]->Fill(calibedTimeAlined);
                if((calibedTimeAlined > -5.)&&(calibedTimeAlined < 10.)) countOfHitsInTS[bPhys]++;
                
            }

        }
        // tempDetID++;

        // if(repDetId<2) continue;
        // // std::cout << "repDetId-2: bPhys" << repDetId-2 << std::endl;
        // m_hTrkNumOfHitsInTS[iCalDet][0]->Fill(countOfHitsInTS[0]);
        // m_hTrkNumOfHitsInTS[iCalDet][1]->Fill(countOfHitsInTS[1]);

        // if((repDetId == 2)||(repDetId == 4)){
        //     trigHitCounts[0][0] += countOfHitsInTS[0]+countOfHitsInTS[1];
        //     trigHitCounts[0][1] += countOfHitsInTS[1];
        // }else if((repDetId == 3)||(repDetId == 5)){
        //     trigHitCounts[1][0] += countOfHitsInTS[0]+countOfHitsInTS[1];
        //     trigHitCounts[1][1] += countOfHitsInTS[1];
        // }else if(repDetId == 6){
        //     trigHitCounts[2][0] += countOfHitsInTS[0]+countOfHitsInTS[1];
        //     trigHitCounts[2][1] += countOfHitsInTS[1];
        // }
        
    }// == e == CalDet loop ends ==


    for(size_t iTrig = 0; iTrig < 3; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrigDetNumOfHitsInTS[iTrig][iPKind]->Fill(trigHitCounts[iTrig][iPKind]);
        }
    }

    // Trig1
    // if(trigHitCounts[0][0]>18 || trigHitCounts[1][0]>2) m_numOfPhysTrig++; // Barrel || Endcap
    // if(trigHitCounts[0][1]>18 || trigHitCounts[1][1]>2) m_numOfFakeTrig++; // Barrel || Endcap

    // Trig2
    if(trigHitCounts[1][0]>2) m_numOfPhysTrig++; // Barrel || Endcap
    else if(trigHitCounts[2][0]>0) m_numOfPhysTrig++;
    if(trigHitCounts[1][1]>2) m_numOfFakeTrig++; // Barrel || Endcap
    else if(trigHitCounts[2][1]>0) m_numOfFakeTrig++;
    
    // if(trigHitCounts[1][0]<3) m_vTargetEvents.push_back(m_pubEvNum);
    if((trigHitCounts[1][0]<3)&&(trigHitCounts[2][0]<1)) m_vTargetEvents.push_back(m_pubEvNum);
}



void EventAna::FillEachSubDetDepE(){
    for(size_t iDet = 0; iDet < m_trkDetsHits.size(); iDet++){
        for(size_t iHit = 0; iHit < m_trkDetsHits.at(iDet).getHitSize(); iHit++){
            Double_t eDep = m_trkDetsHits.at(iDet).getEDep(iHit);
            // std::cout << "DepE = " << eDep << std::endl;
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


    for(size_t iCalDet = 0; iCalDet < InputDataConfig::kCalCluCollections.size(); iCalDet++){

        const auto& clus = frame.get<edm4eic::ClusterCollection>(std::string(InputDataConfig::kCalCluCollections.at(iCalDet)));
        const auto& associations \
            = frame.get<edm4eic::MCRecoClusterParticleAssociationCollection>(std::string(InputDataConfig::kCalClusterAssociations.at(iCalDet)));

        Int_t countOfHitsInTS[2] = {0, 0};
        for(size_t iClu = 0; iClu < clus.size(); iClu++){
            auto clu = clus.at(iClu);
            Double_t depE = 1000 * clu.getEnergy();
            
            for (const auto& assoc : associations) {
                if (assoc.getRec() != clu)continue;

                const auto& mcP = assoc.getSim();
                // Int_t relMcPIdGenId = mcP.at(relMcPId.index).getGeneratorStatus();
                Int_t relMcPIdGenId = mcP.getGeneratorStatus();

                Int_t pKindId = relMcPIdGenId/1000 -1;
                if(pKindId < 0) pKindId = 0;
                m_hCalRecEDep[iCalDet][pKindId]->Fill(depE);
                
            }

        }

    }// == e == CalDet loop ends ==


}



void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;

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
            histName = TString::Format("m_hTrkTimeDist%s_%s",m_trkShortDetName[iTrkDet+2].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hTrkTimeDist[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hTrkNumOfHitsInTS%s_%s",m_trkShortDetName[iTrkDet+2].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 20, 0, 20);
        }
    }

    for(size_t iCalDet = 0; iCalDet < 6; iCalDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hCalDetRecDepE_%s_%s",m_calShortDetName[iCalDet].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hCalRecEDep[iCalDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 0.50);
        }
    }

    for(size_t iCalDet = 0; iCalDet < 6; iCalDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempPhysName = "Phys";
            if(iPKind == 1) tempPhysName = "BKG";
            histName = TString::Format("m_hCalDetTimeDist%s_%s",m_calShortDetName[iCalDet].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;time_{calib} [ns];count",histName.Data());
            m_hCalDetTimeDist[iCalDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 220, -20, 200);

            histName = TString::Format("m_hCalDetNumOfHitsInTS%s_%s",m_calShortDetName[iCalDet].Data(),tempPhysName.Data());
            histTitle = TString::Format("%s;number of hits;count",histName.Data());
            m_hCalDetNumOfHitsInTS[iCalDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 20, 0, 20);
        }
    }


    for(size_t iTrig = 0; iTrig < 3; iTrig++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            TString tempTrigName = "BTOF+BMPGD";
            if(iTrig == 1) tempTrigName = "ETOF+EMPGD";
            if(iTrig == 2) tempTrigName = "B0";
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
    for(size_t iTrkDet = 0; iTrkDet < 8; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hTrkRecEDep[iTrkDet][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hTrkRecEDep[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iTrkDet = 0; iTrkDet < 8; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hTrkTimeDist[iTrkDet][iPKind]->SetLineColor(histColor);
            m_hTrkTimeDist[iTrkDet][iPKind]->SetLineWidth(5);

            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->SetLineColor(histColor);
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalDet = 0; iCalDet < 6; iCalDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalRecEDep[iCalDet][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hCalRecEDep[iCalDet][iPKind]->SetLineWidth(5);
        }
    }

    for(size_t iCalDet = 0; iCalDet < 6; iCalDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            Int_t histColor = 820+4;
            if(iPKind == 1) histColor = 880 -1;
            m_hCalDetTimeDist[iCalDet][iPKind]->SetLineColor(histColor);
            m_hCalDetTimeDist[iCalDet][iPKind]->SetLineWidth(5);

            m_hCalDetNumOfHitsInTS[iCalDet][iPKind]->SetLineColor(histColor);
            m_hCalDetNumOfHitsInTS[iCalDet][iPKind]->SetLineWidth(5);
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

    for(size_t iTrkDet = 0; iTrkDet < 8; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hTrkRecEDep[iTrkDet][iPKind]->Write();
        }
    }

    for(size_t iTrkDet = 0; iTrkDet < 8; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hTrkTimeDist[iTrkDet][iPKind]->Write();
            m_hTrkNumOfHitsInTS[iTrkDet][iPKind]->Write();
        }
    }

    for(size_t iCalDet = 0; iCalDet < 6; iCalDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hCalRecEDep[iCalDet][iPKind]->Write();
        }
    }

    for(size_t iCalDet = 0; iCalDet < 6; iCalDet++){
        for(size_t iPKind = 0; iPKind < 2; iPKind++){
            m_hCalDetTimeDist[iCalDet][iPKind]->Write();
            m_hCalDetNumOfHitsInTS[iCalDet][iPKind]->Write();
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
