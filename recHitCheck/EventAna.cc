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
    m_vTargetEvents = {8, 10};

    nEvents = 1000;
    // nEvents= 5;
    if(bTargetEV) nEvents = m_vTargetEvents.size();

    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        unsigned tempIEvent = iEvent;
        if(bTargetEV) iEvent =  m_vTargetEvents.at(iEvent);
        m_pubEvNum = iEvent;

        if(iEvent%100==0) std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        m_trkDetsHits = LoadTrackerHitsFromFrame(frame);

        FillEachSubDetRecDepE(frame);
        // FillEachSubDetDepE();

        ResetValuesForEachEvent();

        iEvent = tempIEvent;
    }

    EditHists();
    OFileWrite();

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

        }
    }
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

    m_hBSiRecDepE = new TH1D("m_hBSiRecDepE", "m_hBSiRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hESiRecDepE = new TH1D("m_hESiRecDepE", "m_hBSiRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hBMPGDRecDepE = new TH1D("m_hBMPGDRecDepE", "m_hBMPGDRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hEMPGDRecDepE = new TH1D("m_hEMPGDRecDepE", "m_hEMPGDRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hBTOFRecDepE = new TH1D("m_hBTOFRecDepE", "m_hBTOFRecDepE; depE [MeV];count", 100, 0, 0.1);
    m_hETOFRecDepE = new TH1D("m_hETOFRecDepE", "m_hETOFRecDepE; depE [MeV];count", 100, 0, 0.1);

    for(size_t iTrkDet = 0; iTrkDet < 7; iTrkDet++){
        for(size_t iPKind = 0; iPKind < 6; iPKind++){
            TString histName = TString::Format("m_hDetRecDepE_%s_%s",m_trkShortDetName[iTrkDet].Data(),m_physKindShortName[iPKind].Data());
            TString histTitle = TString::Format("%s;eDep [MeV];count",histName.Data());
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

    m_hBSiRecDepE->Write();
    m_hESiRecDepE->Write();
    m_hBMPGDRecDepE->Write();
    m_hEMPGDRecDepE->Write();
    m_hBTOFRecDepE->Write();
    m_hETOFRecDepE->Write();

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
