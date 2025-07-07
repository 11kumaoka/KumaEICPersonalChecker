#include "podio/ROOTReader.h"
#include "podio/ROOTWriter.h"
#include "podio/Frame.h"

#include <edm4hep/EventHeaderCollection.h>
#include <edm4hep/MCParticleCollection.h>

#include "edm4hep/EventHeaderData.h"
#include "edm4hep/EventHeaderObj.h"
#include "edm4hep/EventHeader.h"

#include <edm4hep/SimCalorimeterHitCollection.h>
#include <edm4hep/SimTrackerHitCollection.h>
#include <edm4hep/CaloHitContributionCollection.h>

#include "edm4eic/CalorimeterHitCollection.h"

int main() {
    // open input
    podio::ROOTReader reader;
    reader.openFile("/Users/tkumaoka/eic/inputFiles/pythia83kHz_orig.root");

    // open output
    podio::ROOTWriter writer("output.root");

    size_t numEvents = reader.getEntries("events");

    std::vector<std::string> m_simtrackerhit_collection_names = {
        "B0TrackerHits",       "BackwardMPGDEndcapHits", "DIRCBarHits",
        "DRICHHits",           "ForwardMPGDEndcapHits",  "ForwardOffMTrackerHits",
        "ForwardRomanPotHits", "LumiSpecTrackerHits",    "MPGDBarrelHits",
        "OuterMPGDBarrelHits", "RICHEndcapNHits",        "SiBarrelHits",
        "TOFBarrelHits",       "TOFEndcapHits",          "TaggerTrackerHits",
        "TrackerEndcapHits",   "VertexBarrelHits"};

    std::vector<std::string> m_simcalorimeterhit_collection_names = {
        "B0ECalHits",      "EcalBarrelImagingHits", "EcalBarrelScFiHits",    "EcalEndcapNHits",
        "EcalEndcapPHits", "EcalEndcapPInsertHits", "EcalFarForwardZDCHits", "EcalLumiSpecHits",
        "HcalBarrelHits",  "HcalEndcapNHits",       "HcalEndcapPInsertHits", "HcalFarForwardZDCHits",
        "LFHCALHits",      "LumiDirectPCALHits"};

    std::vector<std::string> m_calohitcontribution_collection_names = {
        "B0ECalHitsContributions",
        "EcalBarrelImagingHitsContributions",
        "EcalBarrelScFiHitsContributions",
        "EcalEndcapNHitsContributions",
        "EcalEndcapPHitsContributions",
        "EcalEndcapPInsertHitsContributions",
        "EcalLumiSpecHitsContributions",
        "EcalFarForwardZDCHitsContributions",
        "HcalBarrelHitsContributions",
        "HcalEndcapNHitsContributions",
        "HcalEndcapPInsertHitsContributions",
        "HcalFarForwardZDCHitsContributions",
        "LFHCALHitsContributions",
        "LumiDirectPCALHitsContributions"};

    for (size_t i = 0; i < numEvents; ++i) {
        // Read input frame
        auto frameData = reader.readEntry("events", i);
        podio::Frame input_frame(std::move(frameData));
        
        // Output frame
        podio::Frame output_frame;

        
        // const auto& inParticles = input_frame.get<edm4hep::MCParticleCollection>("MCParticles");
        // const auto& inHeaders = input_frame.get<edm4hep::EventHeaderCollection>("EventHeader");

        // auto copiedParticles = std::make_unique<edm4hep::MCParticleCollection>();
        // for (const auto& p : inParticles) {
        //     copiedParticles->push_back(p.clone());
        // }

        // auto copiedHeaders = std::make_unique<edm4hep::EventHeaderCollection>();
        // for (const auto& h : inHeaders) {
        //     copiedHeaders->push_back(h.clone());
        // }
        // output_frame.put(std::move(copiedParticles), "MCParticles");
        // output_frame.put(std::move(copiedHeaders), "EventHeader");

    
        // Copy input collections to output frame
        for (const auto& name : m_simtrackerhit_collection_names) {
            // Get input collections
            const auto& hits = input_frame.get<edm4hep::SimTrackerHitCollection>(name);

            // Create output collections by cloning
            auto physHit_out = std::make_unique<edm4hep::SimTrackerHitCollection>();
            for (const auto& hit : hits) {
                edm4hep::MutableSimTrackerHit copiedHit;
                copiedHit.setPosition({hit.getPosition().x, hit.getPosition().y, hit.getPosition().z});
                copiedHit.setTime(hit.getTime());
                copiedHit.setCellID(hit.getCellID());
                copiedHit.setEDep(hit.getEDep());
                copiedHit.setMomentum({hit.getMomentum().x, hit.getMomentum().y, hit.getMomentum().z});
                copiedHit.setPathLength(hit.getPathLength());
                copiedHit.setQuality(hit.getQuality());

                physHit_out->push_back(copiedHit);
            }
            output_frame.put(std::move(physHit_out), name);
        }

        // Copy SimCalorimeterHit collections
        for (const auto& name : m_simcalorimeterhit_collection_names) {
            // Get input collections
            const auto& hits = input_frame.get<edm4hep::SimCalorimeterHitCollection>(name);

            // Create output collections by cloning
            auto physHit_out = std::make_unique<edm4hep::SimCalorimeterHitCollection>();
            for (const auto& hit : hits) {
                edm4hep::MutableSimCalorimeterHit copiedHit;
                copiedHit.setCellID(hit.getCellID());
                copiedHit.setEnergy(hit.getEnergy());
                copiedHit.setPosition(hit.getPosition());
                copiedHit.contributions_begin() = hit.contributions_begin();
                copiedHit.contributions_end() = hit.contributions_end();

                physHit_out->push_back(copiedHit);
            }
            output_frame.put(std::move(physHit_out), name);
        }
        // Copy CalorimeterHit collections
        for (const auto& name : m_calohitcontribution_collection_names) {
            // Get input collections
            const auto& hits = input_frame.get<edm4eic::CalorimeterHitCollection>(name);

            // Create output collections by cloning
            auto physHit_out = std::make_unique<edm4eic::CalorimeterHitCollection>();
            for (const auto& hit : hits) {
                edm4eic::MutableCalorimeterHit copiedHit;                
                // copiedHit.PDG() = hit.PDG();
                copiedHit.setEnergy(hit.getEnergy());
                copiedHit.setTime(hit.getTime());
                // copiedHit.stepPosition({hit.stepPosition().x, hit.stepPosition().y, hit.stepPosition().z}); //?????

                physHit_out->push_back(copiedHit);
            }
            output_frame.put(std::move(physHit_out), name);
        }
                
        writer.writeFrame(output_frame, "events");

        // Add dummy frames
        for (int j = 0; j < 5; ++j) {
            podio::Frame empty_frame;
            
            for (const auto& name : m_simtrackerhit_collection_names) {
                edm4hep::MutableSimTrackerHit emptyHit;
                emptyHit.setPosition({0.0, 0.0, 0.0});
                emptyHit.setTime(0.);
                emptyHit.setCellID(0.);
                emptyHit.setEDep(0.);
                emptyHit.setMomentum({0.0, 0.0, 0.0});
                emptyHit.setPathLength(0.);
                emptyHit.setQuality(0.);

                empty_frame.put(std::make_unique<edm4hep::SimTrackerHitCollection>(), name);
            }

            for (const auto& name : m_simcalorimeterhit_collection_names) {
                edm4hep::MutableSimCalorimeterHit emptyHit;
                emptyHit.setCellID(0);
                emptyHit.setEnergy(0.);
                emptyHit.setPosition({0.0, 0.0, 0.0});
                // emptyHit.contributions_begin(0);
                // emptyHit.contributions_end(0);

                empty_frame.put(std::make_unique<edm4hep::SimCalorimeterHitCollection>(), name);
            }

            for (const auto& name : m_calohitcontribution_collection_names) {
                edm4eic::MutableCalorimeterHit emptyHit;
                // emptyHit.setPDG(0);
                emptyHit.setEnergy(0.);
                emptyHit.setTime(0.);
                // emptyHit.stepPosition({0.0, 0.0, 0.0});

                empty_frame.put(std::make_unique<edm4eic::CalorimeterHitCollection>(), name);
            }


            // empty_frame.put(std::make_unique<edm4hep::SimTrackerHitCollection>(), "SiBarrelHits");
            // empty_frame.put(std::make_unique<edm4eic::CalorimeterHitCollection>(), "EcalBarrelHits");
            writer.writeFrame(empty_frame, "events");
        }
    }

    writer.finish();
    return 0;
}

