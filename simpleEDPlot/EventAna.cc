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
    m_vTargetEvents = {};

    // 36, 119, 305, 359, 506, 585, 636, 666, 820,

    bWBKG = false;
    nEvents = 8;
    // nEvents= 5;
    m_SpeEventID = 0;
    if(bTargetEV) nEvents = m_vTargetEvents.size();

    drawEightEvents2D_ZR();
    drawEightEvents2D_XY();

    drawSpecialEvents3D();
    

    EditHists();
    OFileWrite();

   std::cout << "std::vector<Int_t > m_vTargetEvents = {";
   for(Int_t i = 0; i < m_vTargetEvents.size(); i++) std::cout << m_vTargetEvents.at(i) << ", ";
   std::cout << "};" << std::endl;
    
}




// === s === 2D event display
void EventAna::drawEightEvents2D_ZR() {

   for (int i = 0; i < numOfED; ++i) {
      m_hEventDisplays2D_ZR[i] = new TH2D(
         Form("hEventDisplay2D_ZR_%d", i),
         Form("Event %d;z [mm];x [mm]", i),
         100, -5000, 5000,
         100, -50, 4000
      );
   }

   auto* c = new TCanvas("c_events_2d_ZR", "Track Event Display 2D", 1800, 900);
   c->Divide(4, 2, 0.001, 0.001);
   gStyle->SetOptStat(0);
   for (int iEvent = 0; iEvent < numOfED; ++iEvent) {
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));
        c->cd(iEvent + 1);
        gStyle->SetOptStat(0);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.05);
        gPad->SetTopMargin(0.08);
        gPad->SetBottomMargin(0.12);
        drawOneEvent2D_ZR(frame, iEvent);
   }

   c->Update();

//    TFile fout("EventDisplaysZR.root", "RECREATE");
    oFile->cd();
   c->Write();
//    fout.Close();

   c->SaveAs("EventDisplaysZR.pdf");
}

void EventAna::drawOneEvent2D_ZR(const podio::Frame& frame, int eventIndex) {
    m_hEventDisplays2D_ZR[eventIndex]->SetStats(0);
    m_hEventDisplays2D_ZR[eventIndex]->Draw();
    gStyle->SetOptStat(0);

    const auto& mcPColle = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    for (const auto& mcP : mcPColle) {
        Int_t relMcPIdGenId = mcP.getGeneratorStatus();
        Int_t bPhys = 1;
        if(relMcPIdGenId < 1999) bPhys = 0;
        if(bWBKG==false && bPhys==1) continue;

        Double_t mcpVtxZ = mcP.getVertex().z;
        Double_t mcpEndZ = mcP.getEndpoint().z;
        Double_t mcpVtxX = mcP.getVertex().x;
        Double_t mcpEndX = mcP.getEndpoint().x;
        Double_t mcpVtxY = mcP.getVertex().y;
        Double_t mcpEndY = mcP.getEndpoint().y;
        Double_t mcpVtxR = std::sqrt(mcpVtxX*mcpVtxX + mcpVtxY*mcpVtxY);
        Double_t mcpEndR = std::sqrt(mcpEndX*mcpEndX + mcpEndY*mcpEndY);

        if (std::abs(mcpVtxR - mcpEndR) < 1e-12 && std::abs(mcpEndZ - mcpVtxZ) < 1e-12) continue;

        auto* line = new TLine(mcpVtxZ, mcpVtxR, mcpEndZ, mcpEndR);  // x-axis = z, y-axis = r
        line->SetLineColor(colorFromPDG(mcP.getPDG(), mcP.getCharge()));
        line->SetLineWidth(2);
        if(bPhys){
            line->SetLineColor(1);
            line->SetLineStyle(4);
            line->SetLineWidth(1);
        }
        line->Draw("same");
    }

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
                    Int_t relMcPIdGenId = mcPColle.at(relMcPId.index).getGeneratorStatus();

                    Int_t bPhys = 1;
                    if(relMcPIdGenId < 1999) bPhys = 0;
                    if(bWBKG==false && bPhys==1) continue;
                    
                    const auto pos = recHit.getPosition();
                    Double_t recHitR = std::sqrt(pos.x*pos.x + pos.y*pos.y);

                    auto* marker = new TMarker(pos.z, recHitR, 20);
                    marker->SetMarkerSize(0.5);
                    marker->SetMarkerStyle(20);
                    marker->SetMarkerColor(m_TrkDetColors[iDet]);
                    marker->Draw("same");
                }
            }

        }
        tempDetID++;
        
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
                Int_t relMcPIdGenId = mcP.getGeneratorStatus();

                Int_t bPhys = 1;
                if(relMcPIdGenId < 1999) bPhys = 0;
                if(bWBKG==false && bPhys==1) continue;
            
                const auto pos = clu.getPosition();
                Double_t cluR = std::sqrt(pos.x*pos.x + pos.y*pos.y);

                auto* marker = new TMarker(pos.z, cluR, 20);
                marker->SetMarkerSize(0.5);
                marker->SetMarkerStyle(20);
                marker->SetMarkerColor(m_CalDetColors[iCalDet]);
                marker->Draw("same");
                
            }

        }
        // tempDetID++;

    }// == e == CalDet loop ends ==

}

// === XY
// === s === 2D event display
void EventAna::drawEightEvents2D_XY() {

    for (int i = 0; i < numOfED; ++i) {
        m_hEventDisplays2D_XY[i] = new TH2D(
            Form("hEventDisplay2D_XY_%d", i),
            Form("Event %d;x [mm];y [mm]", i),
            100, -5000, 5000,
            100, -4000, 4000
        );
    }

    auto* c = new TCanvas("c_events_2d_xy", "Track Event Display 2D", 1800, 900);
    c->Divide(4, 2, 0.001, 0.001);
    gStyle->SetOptStat(0);
    for (int iEvent = 0; iEvent < numOfED; ++iEvent) {
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));
        c->cd(iEvent + 1);
        gStyle->SetOptStat(0);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.05);
        gPad->SetTopMargin(0.08);
        gPad->SetBottomMargin(0.12);
        drawOneEvent2D_XY(frame, iEvent);
    }

    c->Update();
    oFile->cd();
    c->Write();
    c->SaveAs("EventDisplaysXY.pdf");
}

void EventAna::drawOneEvent2D_XY(const podio::Frame& frame, int eventIndex) {
    m_hEventDisplays2D_XY[eventIndex]->SetStats(0);
    m_hEventDisplays2D_XY[eventIndex]->Draw();
    gStyle->SetOptStat(0);

    const auto& mcPColle = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    for (const auto& mcP : mcPColle) {
        Int_t relMcPIdGenId = mcP.getGeneratorStatus();
        Int_t bPhys = 1;
        if(relMcPIdGenId < 1999) bPhys = 0;
        if(bWBKG==false && bPhys==1) continue;

        Double_t mcpVtxX = mcP.getVertex().x;
        Double_t mcpEndX = mcP.getEndpoint().x;
        Double_t mcpVtxY = mcP.getVertex().y;
        Double_t mcpEndY = mcP.getEndpoint().y;

        if (std::abs(mcpVtxX - mcpEndX) < 1e-12 && std::abs(mcpVtxY - mcpEndY) < 1e-12) continue;

        auto* line = new TLine(mcpVtxX, mcpVtxY, mcpEndX, mcpEndY);  // x-axis = x, y-axis = y
        line->SetLineColor(colorFromPDG(mcP.getPDG(), mcP.getCharge()));
        line->SetLineWidth(2);
        if(bPhys){
            line->SetLineColor(1);
            line->SetLineStyle(4);
            line->SetLineWidth(1);
        }
        line->Draw("same");
    }

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
                    Int_t relMcPIdGenId = mcPColle.at(relMcPId.index).getGeneratorStatus();

                    Int_t bPhys = 1;
                    if(relMcPIdGenId < 1999) bPhys = 0;
                    if(bWBKG==false && bPhys==1) continue;
                    
                    const auto pos = recHit.getPosition();
                    auto* marker = new TMarker(pos.x, pos.y, 20);
                    marker->SetMarkerSize(0.5);
                    marker->SetMarkerStyle(20);
                    marker->SetMarkerColor(m_TrkDetColors[iDet]);
                    marker->Draw("same");
                }
            }

        }
        tempDetID++;
        
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
                Int_t relMcPIdGenId = mcP.getGeneratorStatus();

                Int_t bPhys = 1;
                if(relMcPIdGenId < 1999) bPhys = 0;
                if(bWBKG==false && bPhys==1) continue;
            
                const auto pos = clu.getPosition();

                auto* marker = new TMarker(pos.x, pos.y, 20);
                marker->SetMarkerSize(0.5);
                marker->SetMarkerStyle(20);
                marker->SetMarkerColor(m_CalDetColors[iCalDet]);
                marker->Draw("same");
                
            }

        }
        // tempDetID++;

    }// == e == CalDet loop ends ==

}
// == XY 


void EventAna::drawSpecialEvents3D(){
    m_hEventDisplay3D = new TH3D("hEventDisplay3D", "Event Display;z [mm];x [mm];y [mm]",\
         100, -5000, 5000, 100, -4000, 4000, 100, -4000, 4000);

    auto* c = new TCanvas("c_events_3d", "Track Event Display 3D", 1800, 900);
    m_hEventDisplay3D->SetStats(0);
    m_hEventDisplay3D->Draw();
    gStyle->SetOptStat(0);

    auto frame = podio::Frame(m_reader.readEntry("events", m_SpeEventID));
    const auto& mcPColle = frame.get<edm4hep::MCParticleCollection>("MCParticles");
    for (const auto& mcP : mcPColle) {
        Int_t relMcPIdGenId = mcP.getGeneratorStatus();
        Int_t bPhys = 1;
        if(relMcPIdGenId < 1999) bPhys = 0;
        if(bWBKG==false && bPhys==1) continue;

        Double_t mcpVtxZ = mcP.getVertex().z;
        Double_t mcpEndZ = mcP.getEndpoint().z;
        Double_t mcpVtxX = mcP.getVertex().x;
        Double_t mcpEndX = mcP.getEndpoint().x;
        Double_t mcpVtxY = mcP.getVertex().y;
        Double_t mcpEndY = mcP.getEndpoint().y;

        auto* line = new TPolyLine3D(2);
        line->SetPoint(0, mcpVtxZ, mcpVtxX, mcpVtxY);
        line->SetPoint(1, mcpEndZ, mcpEndX, mcpEndY);
        line->SetLineColor(colorFromPDG(mcP.getPDG(), mcP.getCharge()));
        line->SetLineWidth(2);
        if(bPhys){
            line->SetLineColor(1);
            line->SetLineStyle(4);
            line->SetLineWidth(1);
        }
        line->Draw("same");
    }

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
                    Int_t relMcPIdGenId = mcPColle.at(relMcPId.index).getGeneratorStatus();

                    Int_t bPhys = 1;
                    if(relMcPIdGenId < 1999) bPhys = 0;
                    if(bWBKG==false && bPhys==1) continue;
                    
                    const auto pos = recHit.getPosition();
                    auto* marker = new TPolyMarker3D(1);
                    marker->SetPoint(0, pos.z, pos.x, pos.y);
                    marker->SetMarkerSize(0.5);
                    marker->SetMarkerStyle(20);
                    marker->SetMarkerColor(m_TrkDetColors[iDet]);
                    marker->Draw("same");
                }
            }

        }
        tempDetID++;
        
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
                Int_t relMcPIdGenId = mcP.getGeneratorStatus();

                Int_t bPhys = 1;
                if(relMcPIdGenId < 1999) bPhys = 0;
                if(bWBKG==false && bPhys==1) continue;
            
                const auto pos = clu.getPosition();

                auto* marker = new TPolyMarker3D(1);
                marker->SetPoint(0, pos.z, pos.x, pos.y);
                marker->SetMarkerSize(0.5);
                marker->SetMarkerStyle(20);
                marker->SetMarkerColor(m_CalDetColors[iCalDet]);
                marker->Draw("same");
                
            }

        }
        // tempDetID++;

    }// == e == CalDet loop ends ==

    c->Update();
    oFile->cd();
    c->Write();
}


void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;

    TString histName = "";
    TString histTitle = "";


}

void EventAna::EditHists() {
    int a = 1;
}

void EventAna::OFileWrite() {
    std::cout << "OFileWrite" << std::endl;
    oFile->cd();
    
    oFile->Close();
}

