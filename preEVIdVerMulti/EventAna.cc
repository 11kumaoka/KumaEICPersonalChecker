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

    bool bTargetEV = false;
    m_vTargetEvents = {8, 10};

    nEvents = 1000;
    // nEvents= 5;
    if(bTargetEV) nEvents = m_vTargetEvents.size();
    std::cout << "Number of events = " << nEvents << std::endl;
    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        unsigned tempIEvent = iEvent;
        if(bTargetEV) iEvent =  m_vTargetEvents.at(iEvent);
        m_pubEvNum = iEvent;

        if(iEvent%1==0) std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        Double_t physCollTime = FindPhysCollTime(frame);
        m_trkDetsHits = LoadTrackerHitsFromFrame(frame);

        Int_t nTS = 0;
        bool trigMenus[1] = {false}; 
        // == s == Time-frame loop =======================================
        while (true){
            Double_t trigT0 = TrigCTRBarrel(nTS, m_trkDetsHits);
            if(trigT0 != -9999.) {
                Int_t tk = 1;
                if((trigT0 >= physCollTime - physTimeWMin)&&(trigT0 <= physCollTime + physTimeWMax)){

                }
            }

            nTS++;
            if(nTS * m_timeSliceWidth > m_timeWindow) break;
        } // == e == Time-slice base detector loop ==================================

        FillEachSubDetRecDepE(frame);

        ResetValuesForEachEvent();

    //   if(checkPhysCount > 1) m_vTargetEvents.push_back(m_pubEvNum);
      if(bTargetEV) iEvent = tempIEvent;
    }

    EditHists();
    OFileWrite();

    std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;

}

Double_t EventAna::TrigCTRBarrel(Int_t nTS, std::vector<SimTrackerHitKuma> m_trkDetsHits){
    // 3,4: BMPGD, 5,6: EMPGD, 7: BTOF, 8: ETOF 
    bool bTrig = false;
    Int_t trigDetID[6] = {3,4,5,6,7,8};
    Int_t nTrigMultiHits = 0;
    Double_t meanTimeDeno = 0.;
    Double_t meanTimeNume = 0.;
    for(size_t iDet = 0; iDet < 6; iDet++){
        Int_t detID = trigDetID[iDet];
        Double_t timeReso = 9999.;
        if(detID < 7) timeReso = m_trkDetTimeReso[1];
        else timeReso = m_trkDetTimeReso[2];
        for(Int_t iHit = m_trigCTRBarrelDetIniHitID[detID]; iHit < m_trkDetsHits.at(detID).getSize(); iHit++){
            Double_t hitT = m_trkDetsHits.at(detID).getTime(iHit);
            // *****ChecKuma**** :: Take care it cannot count minus time (by calibration)
            if(hitT < (nTS +1) * m_timeSliceWidth){
                nTrigMultiHits++;
                //  *****ChecKuma**** :: Calc Mean Time Consider Det Time resolution
                meanTimeDeno += timeReso*timeReso;
                meanTimeNume += hitT/(timeReso*timeReso);
            }else{
                m_trigCTRBarrelDetIniHitID[iDet] = iHit;
                break;
            }
        }
    }
    if(nTrigMultiHits > threNTrigMultiHits[0]) bTrig = true;
    // if(!bTrig) return bTrig;
    if(!bTrig) return -9999.;

    Double_t t0 = meanTimeNume/meanTimeDeno;
    //  *****ChecKuma**** :: Add hits overwrap the TS

    return t0;
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

void EventAna::FillEachSubDetRecDepE(const podio::Frame& frame){

    const auto& mcP = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    Int_t tempDetID = 0;
    for(size_t iDet = 0; iDet < InputDataConfig::kTrkRecCollections.size(); iDet++){
        Int_t repDetId = 6;
        if(tempDetID>7) repDetId = 5;
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
                    m_hDetRecEDep[repDetId][pKindId]->Fill(depE);
                }
            }

        }
        tempDetID++;
    }
}



void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;

    TString histName = "";
    TString histTitle = "";

    histName = "m_hTrigEfficiency";
    histTitle = TString::Format("%s;;count",histName.Data());
    m_hTrigEfficiency = new TH1D(histName.Data(), histTitle.Data(), 2, 0, 2);

    for(size_t iTrkDet = 0; iTrkDet < 7; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            histName = TString::Format("m_hDetRecDepE_%s_%s",m_trkShortDetName[iTrkDet].Data(),m_physKindShortName[iPKind].Data());
            histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
            m_hDetRecEDep[iTrkDet][iPKind] = new TH1D(histName.Data(), histTitle.Data(), 100, 0, 0.50);
        }
    }
}

void EventAna::EditHists() {
    for(size_t iTrkDet = 0; iTrkDet < 7; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hDetRecEDep[iTrkDet][iPKind]->SetLineColor(m_BKGColors[iPKind]);
            m_hDetRecEDep[iTrkDet][iPKind]->SetLineWidth(5);
        }
    }
}

void EventAna::OFileWrite() {
    std::cout << "OFileWrite" << std::endl;
    oFile->cd();

    m_hTrigEfficiency->Write();

    for(size_t iTrkDet = 0; iTrkDet < 7; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            m_hDetRecEDep[iTrkDet][iPKind]->Write();
        }
    }

    oFile->Close();
}

void EventAna::ResetValuesForEachEvent() {
    m_trkDetsHits.clear();
}
