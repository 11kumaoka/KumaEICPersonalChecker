#include "EventAna.h"
#include <iostream>
#include <algorithm>
#include <cmath>

#include <TVector3.h>
#include <TLorentzVector.h>


EventAna::EventAna(const std::string& inputFile, const std::string& outputFile) : 
    m_iFileName(inputFile), m_oFileName(outputFile)
{
    TH1::AddDirectory(kFALSE);
    m_reader.openFile(m_iFileName);
}


void EventAna::EventLoop() {
    OFileInit();
    auto nEvents = m_reader.getEntries("events");
    const bool bTargetEV = false;
    m_vTargetEvents = {};

    nEvents = std::min<decltype(nEvents)>(nEvents, 1000);
    // nEvents = 10;
    if(bTargetEV) nEvents = m_vTargetEvents.size();

    std::cout << "Number of events = " << nEvents << std::endl;

    int pureTrkCount(0);
    int mixTrkCount(0);
    int totalAssocCount(0);

    for (unsigned iEvent = 0; iEvent < nEvents; ++iEvent) {
        unsigned tempIEvent = iEvent;
        if(bTargetEV) iEvent =  m_vTargetEvents.at(iEvent);
        m_pubEvNum = iEvent;

        if(iEvent%10==0) std::cout << "== event " << iEvent << " ==" << std::endl;
        auto frame = podio::Frame(m_reader.readEntry("events", iEvent));

        const Double_t physCollTime = FindPhysCollTime(frame);
        
        const auto& physicsEventHeaders = frame.get<edm4hep::EventHeaderCollection>("EventHeader_PHY");

        const auto& mcParticles = frame.get<edm4hep::MCParticleCollection>("MCParticles");
        
        // Standard CKF tracks
        const auto& centralCKFTracks = frame.get<edm4eic::TrackCollection>("CentralCKFTracks");
        const auto& centralCKFTrackParameters = \
            frame.get<edm4eic::TrackParametersCollection>("CentralCKFTrackParameters");
        const auto& centralCKFTrajectories = \
            frame.get<edm4eic::TrajectoryCollection>("CentralCKFTrajectories");
        const auto& centralCKFTrackAssociations = \
            frame.get<edm4eic::MCRecoTrackParticleAssociationCollection>("CentralCKFTrackAssociations");

        // Unfiltered CKF tracks
        const auto& centralCKFTracksUnfiltered = \
            frame.get<edm4eic::TrackCollection>("CentralCKFTracksUnfiltered");
        const auto& centralCKFTrackParametersUnfiltered = \
            frame.get<edm4eic::TrackParametersCollection>("CentralCKFTrackParametersUnfiltered");
        const auto& centralCKFTrajectoriesUnfiltered = \
            frame.get<edm4eic::TrajectoryCollection>("CentralCKFTrajectoriesUnfiltered");
        const auto& centralCKFTrackUnfilteredAssociations =
            frame.get<edm4eic::MCRecoTrackParticleAssociationCollection>(
                "CentralCKFTrackUnfilteredAssociations"
            );


        // ============================================================
        // Truth-seeded CKF tracks
        // ============================================================
        const auto& centralCKFTruthSeededTracks = \
            frame.get<edm4eic::TrackCollection>("CentralCKFTruthSeededTracks");
        const auto& centralCKFTruthSeededTrackParameters =
            frame.get<edm4eic::TrackParametersCollection>("CentralCKFTruthSeededTrackParameters");
        const auto& centralCKFTruthSeededTrajectories =
            frame.get<edm4eic::TrajectoryCollection>("CentralCKFTruthSeededTrajectories");
        const auto& centralCKFTruthSeededTrackAssociations =
            frame.get<edm4eic::MCRecoTrackParticleAssociationCollection>(
                "CentralCKFTruthSeededTrackAssociations"
            );

        // Truth-seeded unfiltered CKF tracks
        const auto& centralCKFTruthSeededTracksUnfiltered = \
            frame.get<edm4eic::TrackCollection>(
                "CentralCKFTruthSeededTracksUnfiltered"
            );
        const auto& centralCKFTruthSeededTrackParametersUnfiltered = \
            frame.get<edm4eic::TrackParametersCollection>(
                "CentralCKFTruthSeededTrackParametersUnfiltered"
            );
        const auto& centralCKFTruthSeededTrajectoriesUnfiltered = \
            frame.get<edm4eic::TrajectoryCollection>(
                "CentralCKFTruthSeededTrajectoriesUnfiltered"
            );
        const auto& centralCKFTruthSeededTrackUnfilteredAssociations = \
            frame.get<edm4eic::MCRecoTrackParticleAssociationCollection>(
                "CentralCKFTruthSeededTrackUnfilteredAssociations"
            );

        // Tracker measurements and seeds
        const auto& centralTrackerMeasurements = \
            frame.get<edm4eic::Measurement2DCollection>("CentralTrackerMeasurements");
        const auto& centralTrackerTruthSeeds = \
            frame.get<edm4eic::TrackSeedCollection>("CentralTrackerTruthSeeds");
        const auto& centralTrackSeeds = frame.get<edm4eic::TrackSeedCollection>("CentralTrackSeeds");
        const auto& centralTrackSeedParameters = \
            frame.get<edm4eic::TrackParametersCollection>("CentralTrackSeedParameters");

        // Tracking hits and associations
        const auto& centralTrackingRecHits = \
            frame.get<edm4eic::TrackerHitCollection>("CentralTrackingRecHits");
        const auto& centralTrackingRawHitAssociations =
            frame.get<edm4eic::MCRecoTrackerHitAssociationCollection>(
                "CentralTrackingRawHitAssociations"
        );

        // Track segments and vertices
        const auto& centralTrackSegments = frame.get<edm4eic::TrackSegmentCollection>("CentralTrackSegments");
        const auto& centralTrackVertices = frame.get<edm4eic::VertexCollection>("CentralTrackVertices");
        const auto& centralAndB0TrackVertices = \
            frame.get<edm4eic::VertexCollection>("CentralAndB0TrackVertices");


        // Reconstructed charged particles
        const auto& reconstructedChargedParticles = \
            frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedParticles");
        const auto& reconstructedChargedParticleAssociations = \
            frame.get<edm4eic::MCRecoParticleAssociationCollection>(
                "ReconstructedChargedParticleAssociations"
            );

        // Reconstructed particles with real PID
        const auto& reconstructedChargedRealPIDParticles = \
            frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedChargedRealPIDParticles");
        const auto& reconstructedChargedRealPIDParticleIDs = \
            frame.get<edm4hep::ParticleIDCollection>("ReconstructedChargedRealPIDParticleIDs");


        // Reconstructed-electron subset
        const auto& reconstructedElectrons = \
            frame.get<edm4eic::ReconstructedParticleCollection>("ReconstructedElectrons");



        TLorentzVector rec_vec;
        TVector3 track_vec;
        for (const auto& mcParticle : mcParticles) {
            const int mcPGenStatus = mcParticle.getGeneratorStatus();
            const float mcPCharge  = mcParticle.getCharge();

            // Require final-state charged particle
            if (mcPGenStatus != 1 || std::abs(mcPCharge) <= 0.01) continue;

            const auto momentum = mcParticle.getMomentum();
            const auto vertex   = mcParticle.getVertex();

            TLorentzVector momVecMC;
            TVector3 vtxMC;

            momVecMC.SetXYZM(momentum.x, momentum.y, momentum.z, mcParticle.getMass());
            vtxMC.SetXYZ(vertex.x, vertex.y, vertex.z);

            const double eta = momVecMC.Eta();
            const double pt  = momVecMC.Pt();

            if (std::abs(eta) < 3.5) m_hPtDist_MC->Fill(pt);

            // For |eta| < 3.5, search for an associated reconstructed particle
            // with association weight > 0.8.
            if (std::abs(eta) >= 3.5) continue;

            for (const auto& association : reconstructedChargedParticleAssociations) {
                const auto associatedMCParticle = association.getSim();
                if (!associatedMCParticle.isAvailable()) continue;

                const bool sameMCParticle = associatedMCParticle.getObjectID() == mcParticle.getObjectID();
                if (sameMCParticle && association.getWeight() > 0.8) {
                    // std::cout << "pt = " << pt << std::endl;
                    m_hPtDist_Reco->Fill(pt);
                    break;  // A single reconstructed particle is sufficient for efficiency
                }
            }
        }

        // Loop over real-seeded hit-based associations
        for (size_t iAsso = 0; iAsso < centralCKFTrackAssociations.size(); ++iAsso) {
            const auto& association = centralCKFTrackAssociations[iAsso];
            const auto assoWeight = association.getWeight();
            m_hTrackPurity->Fill(assoWeight);

            const auto recTrack = association.getRec();
            const auto mcParticle = association.getSim();
            if (!recTrack.isAvailable() || !mcParticle.isAvailable()) continue;

            // Count pure and mixed tracks without counting the same mixed track more than once
            if (assoWeight > 0.99) pureTrkCount++;
            else if (iAsso == 0 || recTrack.getObjectID() != centralCKFTrackAssociations[iAsso - 1].getRec().getObjectID()) {
                mixTrkCount++;
            }

            // Assume that Track and TrackParameters use the same collection index
            const int iTrk = recTrack.getObjectID().index;
            if (iTrk < 0 || static_cast<size_t>(iTrk) >= centralCKFTrackParameters.size()) continue;

            const auto momentumMC = mcParticle.getMomentum();
            TLorentzVector momVecMC;
            momVecMC.SetXYZM(momentumMC.x, momentumMC.y, momentumMC.z, mcParticle.getMass());

            const auto qOverP = centralCKFTrackParameters[iTrk].getQOverP();
            if (qOverP == 0.) continue;

            const auto momMC = momVecMC.P();
            const auto momTrk = std::abs(1. / qOverP);
            if (momMC == 0.) continue;

            m_hPtCompMCVsReco->Fill(momMC, momTrk);
            m_hPtReso->Fill((momTrk - momMC) / momMC);
        }

        totalAssocCount += centralCKFTrackAssociations.size();

        // Fill track-quality histograms
        for (const auto& track : centralCKFTracks) {
            if (track.getNdf() > 0) m_hTrackChi2->Fill(track.getChi2() / track.getNdf());
        }

        for (const auto& vertex : centralTrackVertices) {
            if (vertex.getNdf() > 0) m_hVertexChi2->Fill(vertex.getChi2() / vertex.getNdf());
            m_hVertexPosiZ->Fill(vertex.getPosition().z);
        }


        iEvent = tempIEvent;
    }

    m_hTrkEfficiency = (TH1D*) m_hPtDist_Reco->Clone("m_hTrkEfficiency");
    m_hTrkEfficiency->Divide(m_hPtDist_MC);

    const int classifiedTrackCount = pureTrkCount + mixTrkCount;
    if (classifiedTrackCount > 0) {
        float totalPurity = static_cast<float>(pureTrkCount) / classifiedTrackCount;
        m_hTotalTrackPurity->Fill(totalPurity);
    }

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





void EventAna::OFileInit() {
    oFile = new TFile(m_oFileName.c_str(), "recreate");
    std::cout << "OFileInit" << std::endl;


    TString histName = "";
    TString histTitle = "";

    histName = "m_hTrackChi2";
    histTitle = "m_hTrackChi2; #chi^{2}/ndf; count";
    m_hTrackChi2 = new TH1D(histName, histTitle, 50,0,50);

    histName = "m_hVertexChi2";
    histTitle = "m_hVertexChi2; #chi^{2}/ndf; count";
    m_hVertexChi2 = new TH1D(histName, histTitle, 100,0,100);

    histName = "m_hVertexPosiZ";
    histTitle = "m_hVertexPosiZ; #chi^{2}/ndf; count";
    m_hVertexPosiZ = new TH1D(histName, histTitle, 200,-100,100);

    histName = "m_hPtDist_MC";
    histTitle = "MC charged particle pt distribution; #it{p}_{T} [GeV/c]; count";
    m_hPtDist_MC = new TH1D(histName, histTitle, 30,0,15);

    histName = "m_hPtDist_Reco";
    histTitle = "Reconstructed charged particle pt distribution; #it{p}_{T} [GeV/c]; count";
    m_hPtDist_Reco = new TH1D(histName, histTitle, 30,0,15);

    histName = "m_hPtCompMCVsReco";
    histTitle = "m_hPtCompMCVsReco; Associated generated particle momentum [GeV/c]; Reconstructed track momentum [GeV/c]";
    m_hPtCompMCVsReco = new TH2D(histName, histTitle, 100,0,50,100,0,50);

    histName = "m_hPtReso";
    histTitle = "m_hPtReso; #frac{#it{p}_{T, reco} - #it{p}_{T, MC}}{#it{p}_{T, MC}} ; count";
    m_hPtReso = new TH1D(histName, histTitle, 100, -1, 1);

    histName = "m_hTrackPurity";
    histTitle = "Fraction of track measurements from a given MC Particle; purity; Number of Tracks";
    m_hTrackPurity = new TH1D(histName, histTitle, 100,0,1.1);

    histName = "m_hTotalTrackPurity";
    histTitle = "m_hTotalTrackPurity; Total Evetn Purity";
    m_hTotalTrackPurity = new TH1D(histName, histTitle, 1,0,1);

    histName = "m_hTrkEfficiency";
    histTitle = "m_hTrkEfficiency; Tracking Efficiency; #it{p}_{T} [GeV/c]; Efficiency";
    m_hTrkEfficiency = new TH1D(histName, histTitle,30,0,15);
    
}

void EventAna::EditHists() {
    int a = 0;

    
}

void EventAna::OFileWrite() {
    std::cout << "OFileWrite" << std::endl;
    oFile->cd();

    m_hTrackChi2->Write();
    m_hVertexChi2->Write();
    m_hVertexPosiZ->Write();

    m_hPtDist_MC->Write();
    m_hPtDist_Reco->Write();

    m_hPtCompMCVsReco->Write();
    m_hPtReso->Write();

    m_hTrackPurity->Write();
    m_hTotalTrackPurity->Write();
    m_hTrkEfficiency->Write();


    oFile->cd();


    oFile->Close();
}
